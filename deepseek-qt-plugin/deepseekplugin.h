#ifndef DEEPSEEKPLUGIN_H
#define DEEPSEEKPLUGIN_H

#include <QObject>
#include <QtPlugin>
#include "deepseekinterface.h"
#include "deepseekapi.h"

class DeepSeekPlugin : public QObject, public DeepSeekInterface
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "com.example.DeepSeekInterface" FILE "DeepSeekPlugin.json")
    Q_INTERFACES(DeepSeekInterface)

public:
    explicit DeepSeekPlugin(QObject *parent = nullptr);
    ~DeepSeekPlugin();

    // DeepSeekInterface implementation
    QString sendPrompt(const QString &prompt, const QString &model = "deepseek-chat") override;
    void setApiKey(const QString &apiKey) override;
    QString lastError() const override;

private:
    DeepSeekApi *m_api;
};

#endif // DEEPSEEKPLUGIN_H