QT       += core gui
TARGET    = audiors232
TEMPLATE  = app
SOURCES  += app.cpp mainwindow.cpp audiors232-common.cpp audiors232-portaudio.cpp
HEADERS  += mainwindow.h audiors232-common.h audiors232-portaudio.h
FORMS    += mainwindow.ui

unix {
    CONFIG += link_pkgconfig
    PKGCONFIG += portaudio-2.0
}
