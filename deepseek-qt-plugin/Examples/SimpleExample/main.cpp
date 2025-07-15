#include <QApplication>
#include <QMainWindow>
#include <QTextEdit>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QComboBox>
#include <QInputDialog>
#include <QMessageBox>
#include <QPluginLoader>
#include "deepseekinterface.h"

class SimpleDeepSeekApp : public QMainWindow {
    Q_OBJECT
    
public:
    SimpleDeepSeekApp(QWidget *parent = nullptr) : QMainWindow(parent) {
        // Create UI
        QWidget *centralWidget = new QWidget(this);
        QVBoxLayout *mainLayout = new QVBoxLayout(centralWidget);
        
        // Model selection
        QHBoxLayout *modelLayout = new QHBoxLayout();
        QLabel *modelLabel = new QLabel("Model:", this);
        modelComboBox = new QComboBox(this);
        modelComboBox->addItem("deepseek-chat");
        modelComboBox->addItem("deepseek-coder");
        
        QPushButton *apiKeyButton = new QPushButton("Set API Key", this);
        
        modelLayout->addWidget(modelLabel);
        modelLayout->addWidget(modelComboBox);
        modelLayout->addWidget(apiKeyButton);
        modelLayout->addStretch();
        
        // Prompt input
        QLabel *promptLabel = new QLabel("Prompt:", this);
        promptEdit = new QTextEdit(this);
        promptEdit->setPlaceholderText("Enter your prompt here...");
        
        // Send button
        sendButton = new QPushButton("Send to DeepSeek", this);
        
        // Response output
        QLabel *responseLabel = new QLabel("Response:", this);
        responseEdit = new QTextEdit(this);
        responseEdit->setReadOnly(true);
        responseEdit->setPlaceholderText("Response will appear here...");
        
        // Add widgets to layout
        mainLayout->addLayout(modelLayout);
        mainLayout->addWidget(promptLabel);
        mainLayout->addWidget(promptEdit);
        mainLayout->addWidget(sendButton);
        mainLayout->addWidget(responseLabel);
        mainLayout->addWidget(responseEdit);
        
        setCentralWidget(centralWidget);
        
        // Load the plugin
        loadPlugin();
        
        // Connect signals and slots
        connect(sendButton, &QPushButton::clicked, this, &SimpleDeepSeekApp::onSendClicked);
        connect(apiKeyButton, &QPushButton::clicked, this, &SimpleDeepSeekApp::onSetApiKeyClicked);
        
        // Set window properties
        setWindowTitle("DeepSeek API Simple Example");
        resize(800, 600);
        
        // Status bar
        statusBar()->showMessage("Ready");
    }
    
private slots:
    void onSendClicked() {
        if (!deepSeekPlugin) {
            QMessageBox::warning(this, "Error", "Plugin not loaded");
            return;
        }
        
        if (apiKey.isEmpty()) {
            QMessageBox::warning(this, "Warning", "API key not set. Please set your API key first.");
            return;
        }
        
        QString prompt = promptEdit->toPlainText();
        if (prompt.isEmpty()) {
            QMessageBox::warning(this, "Warning", "Please enter a prompt");
            return;
        }
        
        statusBar()->showMessage("Sending request to DeepSeek API...");
        responseEdit->clear();
        
        // Get the selected model
        QString model = modelComboBox->currentText();
        
        // Send the prompt
        QString response = deepSeekPlugin->sendPrompt(prompt, model);
        
        if (response.isEmpty()) {
            QMessageBox::warning(this, "Error", "Failed to get response: " + deepSeekPlugin->lastError());
            statusBar()->showMessage("Error: " + deepSeekPlugin->lastError());
        } else {
            responseEdit->setPlainText(response);
            statusBar()->showMessage("Response received");
        }
    }
    
    void onSetApiKeyClicked() {
        bool ok;
        QString newApiKey = QInputDialog::getText(this, "API Key", 
                                              "Enter your DeepSeek API key:", 
                                              QLineEdit::Password, 
                                              apiKey, &ok);
        if (ok && !newApiKey.isEmpty()) {
            apiKey = newApiKey;
            if (deepSeekPlugin) {
                deepSeekPlugin->setApiKey(apiKey);
                statusBar()->showMessage("API key set");
            }
        }
    }
    
private:
    void loadPlugin() {
        QPluginLoader loader("../../build/libDeepSeekPlugin.so");
        QObject *instance = loader.instance();
        
        if (!instance) {
            QMessageBox::critical(this, "Error", "Failed to load plugin: " + loader.errorString());
            statusBar()->showMessage("Error: Failed to load plugin");
            return;
        }
        
        deepSeekPlugin = qobject_cast<DeepSeekInterface*>(instance);
        if (!deepSeekPlugin) {
            QMessageBox::critical(this, "Error", "Failed to cast plugin to DeepSeekInterface");
            statusBar()->showMessage("Error: Failed to cast plugin");
            return;
        }
        
        statusBar()->showMessage("DeepSeek plugin loaded successfully");
    }
    
    QTextEdit *promptEdit;
    QTextEdit *responseEdit;
    QPushButton *sendButton;
    QComboBox *modelComboBox;
    DeepSeekInterface *deepSeekPlugin = nullptr;
    QString apiKey;
};

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    SimpleDeepSeekApp window;
    window.show();
    return app.exec();
}

#include "main.moc"