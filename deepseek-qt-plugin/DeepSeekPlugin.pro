QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

TARGET = DeepSeekPlugin
TEMPLATE = lib
CONFIG += plugin

DEFINES += QT_DEPRECATED_WARNINGS

SOURCES += \
    deepseekplugin.cpp \
    deepseekapi.cpp

HEADERS += \
    deepseekplugin.h \
    deepseekapi.h \
    deepseekinterface.h

DISTFILES += DeepSeekPlugin.json

# Default rules for deployment.
unix {
    target.path = /usr/lib/qt/plugins
    INSTALLS += target
}