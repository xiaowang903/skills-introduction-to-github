#ifndef DEEPSEEKINTERFACE_H
#define DEEPSEEKINTERFACE_H

#include <QtPlugin>
#include <QString>

class DeepSeekInterface
{
public:
    virtual ~DeepSeekInterface() {}
    
    // Method to send a prompt to DeepSeek API and get a response
    virtual QString sendPrompt(const QString &prompt, const QString &model = "deepseek-chat") = 0;
    
    // Method to set the API key
    virtual void setApiKey(const QString &apiKey) = 0;
    
    // Method to get the last error message
    virtual QString lastError() const = 0;
};

#define DeepSeekInterface_iid "com.example.DeepSeekInterface"
Q_DECLARE_INTERFACE(DeepSeekInterface, DeepSeekInterface_iid)

#endif // DEEPSEEKINTERFACE_H