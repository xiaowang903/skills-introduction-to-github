#include "deepseekplugin.h"

DeepSeekPlugin::DeepSeekPlugin(QObject *parent)
    : QObject(parent)
    , m_api(new DeepSeekApi(this))
{
}

DeepSeekPlugin::~DeepSeekPlugin()
{
}

QString DeepSeekPlugin::sendPrompt(const QString &prompt, const QString &model)
{
    return m_api->sendPrompt(prompt, model);
}

void DeepSeekPlugin::setApiKey(const QString &apiKey)
{
    m_api->setApiKey(apiKey);
}

QString DeepSeekPlugin::lastError() const
{
    return m_api->lastError();
}