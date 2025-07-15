#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPluginLoader>
#include "../deepseekinterface.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_sendButton_clicked();
    void on_apiKeyButton_clicked();

private:
    Ui::MainWindow *ui;
    QPluginLoader m_pluginLoader;
    DeepSeekInterface *m_deepSeekPlugin;
    QString m_apiKey;
    
    void loadPlugin();
};

#endif // MAINWINDOW_H