#-------------------------------------------------
#
# Project created by QtCreator 2017-04-18T18:57:06
#
#-------------------------------------------------

QT  += core gui
QT  += widgets
QT  += network


greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = m3u_editor
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += main.cpp\
        mainwindow.cpp \
    input_output.cpp \
    edit_list.cpp \
    channel.cpp \
    m3u.cpp \
    m3u_element_gui.cpp

HEADERS  += mainwindow.h \
    input_output.h \
    edit_list.h \
    channel.h \
    m3u.h \
    global_settings.h \
    m3u_element_gui.h

FORMS    += mainwindow.ui \
    m3u_element_gui.ui

RESOURCES += \
    icons.qrc
