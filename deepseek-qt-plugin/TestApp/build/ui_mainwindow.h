/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.15.8
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QComboBox *modelComboBox;
    QPushButton *apiKeyButton;
    QLabel *label_2;
    QTextEdit *promptTextEdit;
    QPushButton *sendButton;
    QLabel *label_3;
    QTextEdit *responseTextEdit;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(800, 600);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        verticalLayout = new QVBoxLayout(centralwidget);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        label = new QLabel(centralwidget);
        label->setObjectName(QString::fromUtf8("label"));

        horizontalLayout->addWidget(label);

        modelComboBox = new QComboBox(centralwidget);
        modelComboBox->addItem(QString());
        modelComboBox->addItem(QString());
        modelComboBox->setObjectName(QString::fromUtf8("modelComboBox"));

        horizontalLayout->addWidget(modelComboBox);

        apiKeyButton = new QPushButton(centralwidget);
        apiKeyButton->setObjectName(QString::fromUtf8("apiKeyButton"));

        horizontalLayout->addWidget(apiKeyButton);


        verticalLayout->addLayout(horizontalLayout);

        label_2 = new QLabel(centralwidget);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        verticalLayout->addWidget(label_2);

        promptTextEdit = new QTextEdit(centralwidget);
        promptTextEdit->setObjectName(QString::fromUtf8("promptTextEdit"));

        verticalLayout->addWidget(promptTextEdit);

        sendButton = new QPushButton(centralwidget);
        sendButton->setObjectName(QString::fromUtf8("sendButton"));

        verticalLayout->addWidget(sendButton);

        label_3 = new QLabel(centralwidget);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        verticalLayout->addWidget(label_3);

        responseTextEdit = new QTextEdit(centralwidget);
        responseTextEdit->setObjectName(QString::fromUtf8("responseTextEdit"));
        responseTextEdit->setReadOnly(true);

        verticalLayout->addWidget(responseTextEdit);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 800, 22));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "DeepSeek API Test", nullptr));
        label->setText(QCoreApplication::translate("MainWindow", "Model:", nullptr));
        modelComboBox->setItemText(0, QCoreApplication::translate("MainWindow", "deepseek-chat", nullptr));
        modelComboBox->setItemText(1, QCoreApplication::translate("MainWindow", "deepseek-coder", nullptr));

        apiKeyButton->setText(QCoreApplication::translate("MainWindow", "Set API Key", nullptr));
        label_2->setText(QCoreApplication::translate("MainWindow", "Prompt:", nullptr));
        promptTextEdit->setPlaceholderText(QCoreApplication::translate("MainWindow", "Enter your prompt here...", nullptr));
        sendButton->setText(QCoreApplication::translate("MainWindow", "Send", nullptr));
        label_3->setText(QCoreApplication::translate("MainWindow", "Response:", nullptr));
        responseTextEdit->setPlaceholderText(QCoreApplication::translate("MainWindow", "Response will appear here...", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
