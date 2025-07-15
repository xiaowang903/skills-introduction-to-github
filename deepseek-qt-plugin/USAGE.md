# DeepSeek Qt Plugin Usage Guide

This guide explains how to integrate and use the DeepSeek Qt Plugin in your Qt applications.

## Integration Steps

### 1. Add the Plugin to Your Project

First, you need to add the plugin to your project. You can do this by:

1. Adding the plugin as a dependency in your `.pro` file:

```qmake
# Path to the DeepSeek plugin
INCLUDEPATH += /path/to/deepseek-qt-plugin
LIBS += -L/path/to/build -lDeepSeekPlugin
```

2. Including the plugin interface in your code:

```cpp
#include "deepseekinterface.h"
```

### 2. Loading the Plugin

To load the plugin in your application:

```cpp
#include <QPluginLoader>
#include "deepseekinterface.h"

// ...

QPluginLoader pluginLoader("/path/to/libDeepSeekPlugin.so");
QObject *pluginInstance = pluginLoader.instance();

if (!pluginInstance) {
    qDebug() << "Failed to load plugin:" << pluginLoader.errorString();
    return;
}

DeepSeekInterface *deepSeekPlugin = qobject_cast<DeepSeekInterface*>(pluginInstance);
if (!deepSeekPlugin) {
    qDebug() << "Failed to cast plugin to DeepSeekInterface";
    return;
}
```

### 3. Setting the API Key

Before using the plugin, you need to set your DeepSeek API key:

```cpp
deepSeekPlugin->setApiKey("your-deepseek-api-key");
```

### 4. Sending Prompts and Receiving Responses

To send a prompt to the DeepSeek API and get a response:

```cpp
QString prompt = "Write a short story about a robot learning to paint.";
QString model = "deepseek-chat"; // or "deepseek-coder" for code-related tasks

QString response = deepSeekPlugin->sendPrompt(prompt, model);

if (response.isEmpty()) {
    qDebug() << "Error:" << deepSeekPlugin->lastError();
} else {
    qDebug() << "Response:" << response;
}
```

### 5. Error Handling

Always check for errors when using the plugin:

```cpp
if (response.isEmpty()) {
    QString errorMessage = deepSeekPlugin->lastError();
    // Handle the error
}
```

## Complete Example

Here's a complete example of using the DeepSeek plugin in a Qt application:

```cpp
#include <QApplication>
#include <QMainWindow>
#include <QTextEdit>
#include <QPushButton>
#include <QVBoxLayout>
#include <QPluginLoader>
#include <QMessageBox>
#include "deepseekinterface.h"

class MainWindow : public QMainWindow {
    Q_OBJECT
    
public:
    MainWindow(QWidget *parent = nullptr) : QMainWindow(parent) {
        // Create UI
        QWidget *centralWidget = new QWidget(this);
        QVBoxLayout *layout = new QVBoxLayout(centralWidget);
        
        promptEdit = new QTextEdit(this);
        promptEdit->setPlaceholderText("Enter your prompt here...");
        
        sendButton = new QPushButton("Send", this);
        
        responseEdit = new QTextEdit(this);
        responseEdit->setReadOnly(true);
        responseEdit->setPlaceholderText("Response will appear here...");
        
        layout->addWidget(promptEdit);
        layout->addWidget(sendButton);
        layout->addWidget(responseEdit);
        
        setCentralWidget(centralWidget);
        
        // Load the plugin
        loadPlugin();
        
        // Connect signals and slots
        connect(sendButton, &QPushButton::clicked, this, &MainWindow::onSendClicked);
        
        // Set window properties
        setWindowTitle("DeepSeek API Demo");
        resize(800, 600);
    }
    
private slots:
    void onSendClicked() {
        if (!deepSeekPlugin) {
            QMessageBox::warning(this, "Error", "Plugin not loaded");
            return;
        }
        
        QString prompt = promptEdit->toPlainText();
        if (prompt.isEmpty()) {
            QMessageBox::warning(this, "Warning", "Please enter a prompt");
            return;
        }
        
        // Set your API key (should be done once, preferably at startup)
        deepSeekPlugin->setApiKey("your-api-key-here");
        
        // Send the prompt
        QString response = deepSeekPlugin->sendPrompt(prompt, "deepseek-chat");
        
        if (response.isEmpty()) {
            QMessageBox::warning(this, "Error", "Failed to get response: " + deepSeekPlugin->lastError());
        } else {
            responseEdit->setPlainText(response);
        }
    }
    
private:
    void loadPlugin() {
        QPluginLoader loader("/path/to/libDeepSeekPlugin.so");
        QObject *instance = loader.instance();
        
        if (!instance) {
            QMessageBox::critical(this, "Error", "Failed to load plugin: " + loader.errorString());
            return;
        }
        
        deepSeekPlugin = qobject_cast<DeepSeekInterface*>(instance);
        if (!deepSeekPlugin) {
            QMessageBox::critical(this, "Error", "Failed to cast plugin to DeepSeekInterface");
            return;
        }
    }
    
    QTextEdit *promptEdit;
    QTextEdit *responseEdit;
    QPushButton *sendButton;
    DeepSeekInterface *deepSeekPlugin = nullptr;
};

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    MainWindow window;
    window.show();
    return app.exec();
}

#include "main.moc"
```

## Supported Models

The plugin currently supports the following DeepSeek models:

- `deepseek-chat`: General-purpose chat model
- `deepseek-coder`: Specialized for code-related tasks

## Troubleshooting

1. **Plugin fails to load**: Make sure the plugin library is in the correct location and has the correct permissions.

2. **API key issues**: Ensure your API key is valid and has been set correctly.

3. **Network errors**: Check your internet connection and firewall settings.

4. **Empty responses**: Check the error message using `lastError()` to diagnose the issue.