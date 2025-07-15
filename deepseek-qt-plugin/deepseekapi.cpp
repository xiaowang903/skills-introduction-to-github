#include "deepseekapi.h"
#include <QNetworkRequest>
#include <QEventLoop>
#include <QUrlQuery>
#include <QDebug>

DeepSeekApi::DeepSeekApi(QObject *parent)
    : QObject(parent)
    , m_networkManager(new QNetworkAccessManager(this))
{
}

DeepSeekApi::~DeepSeekApi()
{
}

void DeepSeekApi::setApiKey(const QString &apiKey)
{
    m_apiKey = apiKey;
}

QString DeepSeekApi::lastError() const
{
    return m_lastError;
}

QJsonDocument DeepSeekApi::createRequestJson(const QString &prompt, const QString &model)
{
    QJsonObject jsonObject;
    jsonObject["model"] = model;
    
    QJsonArray messagesArray;
    QJsonObject messageObject;
    messageObject["role"] = "user";
    messageObject["content"] = prompt;
    messagesArray.append(messageObject);
    
    jsonObject["messages"] = messagesArray;
    jsonObject["temperature"] = 0.7;
    jsonObject["max_tokens"] = 2048;
    
    return QJsonDocument(jsonObject);
}

QString DeepSeekApi::sendPrompt(const QString &prompt, const QString &model)
{
    if (m_apiKey.isEmpty()) {
        m_lastError = "API key is not set";
        return QString();
    }
    
    // Create the network request
    QNetworkRequest request(QUrl("https://api.deepseek.com/v1/chat/completions"));
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    request.setRawHeader("Authorization", QString("Bearer %1").arg(m_apiKey).toUtf8());
    
    // Create the request body
    QJsonDocument jsonDoc = createRequestJson(prompt, model);
    QByteArray jsonData = jsonDoc.toJson();
    
    // Send the request
    QEventLoop loop;
    QNetworkReply *reply = m_networkManager->post(request, jsonData);
    
    connect(reply, &QNetworkReply::finished, &loop, &QEventLoop::quit);
    loop.exec(); // Wait for the request to complete
    
    if (reply->error() != QNetworkReply::NoError) {
        m_lastError = QString("Network error: %1").arg(reply->errorString());
        reply->deleteLater();
        return QString();
    }
    
    // Parse the response
    QByteArray responseData = reply->readAll();
    reply->deleteLater();
    
    QJsonDocument responseDoc = QJsonDocument::fromJson(responseData);
    if (responseDoc.isNull() || !responseDoc.isObject()) {
        m_lastError = "Invalid JSON response";
        return QString();
    }
    
    QJsonObject responseObj = responseDoc.object();
    
    // Check for errors in the response
    if (responseObj.contains("error")) {
        QJsonObject errorObj = responseObj["error"].toObject();
        m_lastError = QString("API error: %1").arg(errorObj["message"].toString());
        return QString();
    }
    
    // Extract the response text
    if (responseObj.contains("choices") && responseObj["choices"].isArray()) {
        QJsonArray choices = responseObj["choices"].toArray();
        if (!choices.isEmpty()) {
            QJsonObject choice = choices.first().toObject();
            QJsonObject message = choice["message"].toObject();
            return message["content"].toString();
        }
    }
    
    m_lastError = "Could not extract response from API";
    return QString();
}