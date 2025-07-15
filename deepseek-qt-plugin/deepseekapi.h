#ifndef DEEPSEEKAPI_H
#define DEEPSEEKAPI_H

#include <QObject>
#include <QString>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>

class DeepSeekApi : public QObject
{
    Q_OBJECT

public:
    explicit DeepSeekApi(QObject *parent = nullptr);
    ~DeepSeekApi();

    // Set the API key for DeepSeek
    void setApiKey(const QString &apiKey);
    
    // Send a prompt to DeepSeek API and get a response
    QString sendPrompt(const QString &prompt, const QString &model = "deepseek-chat");
    
    // Get the last error message
    QString lastError() const;

private:
    QString m_apiKey;
    QString m_lastError;
    QNetworkAccessManager *m_networkManager;
    
    // Helper method to create the request JSON
    QJsonDocument createRequestJson(const QString &prompt, const QString &model);
};

#endif // DEEPSEEKAPI_H