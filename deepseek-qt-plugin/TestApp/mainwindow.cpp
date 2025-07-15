#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QInputDialog>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    m_deepSeekPlugin(nullptr)
{
    ui->setupUi(this);
    loadPlugin();
}

MainWindow::~MainWindow()
{
    delete ui;
    m_pluginLoader.unload();
}

void MainWindow::loadPlugin()
{
    // Load the DeepSeek plugin
    m_pluginLoader.setFileName("../build/libDeepSeekPlugin.so");
    
    if (!m_pluginLoader.load()) {
        QMessageBox::critical(this, "Error", "Failed to load DeepSeek plugin: " + m_pluginLoader.errorString());
        return;
    }
    
    QObject *pluginInstance = m_pluginLoader.instance();
    if (!pluginInstance) {
        QMessageBox::critical(this, "Error", "Failed to create plugin instance");
        return;
    }
    
    m_deepSeekPlugin = qobject_cast<DeepSeekInterface*>(pluginInstance);
    if (!m_deepSeekPlugin) {
        QMessageBox::critical(this, "Error", "Failed to cast plugin to DeepSeekInterface");
        return;
    }
    
    ui->statusbar->showMessage("DeepSeek plugin loaded successfully");
}

void MainWindow::on_sendButton_clicked()
{
    if (!m_deepSeekPlugin) {
        QMessageBox::warning(this, "Warning", "Plugin not loaded");
        return;
    }
    
    if (m_apiKey.isEmpty()) {
        QMessageBox::warning(this, "Warning", "API key not set. Please set your API key first.");
        return;
    }
    
    QString prompt = ui->promptTextEdit->toPlainText();
    if (prompt.isEmpty()) {
        QMessageBox::warning(this, "Warning", "Please enter a prompt");
        return;
    }
    
    ui->statusbar->showMessage("Sending request to DeepSeek API...");
    ui->responseTextEdit->clear();
    
    // Get the selected model
    QString model = ui->modelComboBox->currentText();
    
    // Send the prompt to DeepSeek API
    QString response = m_deepSeekPlugin->sendPrompt(prompt, model);
    
    if (response.isEmpty()) {
        QMessageBox::warning(this, "Error", "Failed to get response: " + m_deepSeekPlugin->lastError());
        ui->statusbar->showMessage("Error: " + m_deepSeekPlugin->lastError());
    } else {
        ui->responseTextEdit->setPlainText(response);
        ui->statusbar->showMessage("Response received");
    }
}

void MainWindow::on_apiKeyButton_clicked()
{
    bool ok;
    QString apiKey = QInputDialog::getText(this, "API Key", 
                                          "Enter your DeepSeek API key:", 
                                          QLineEdit::Password, 
                                          m_apiKey, &ok);
    if (ok && !apiKey.isEmpty()) {
        m_apiKey = apiKey;
        if (m_deepSeekPlugin) {
            m_deepSeekPlugin->setApiKey(m_apiKey);
            ui->statusbar->showMessage("API key set");
        }
    }
}