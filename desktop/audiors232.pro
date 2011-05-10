QT       += core gui
TARGET    = audiors232
TEMPLATE  = app
SOURCES  += app.cpp mainwindow.cpp audiors232.cpp
HEADERS  += mainwindow.h audiors232.h
FORMS    += mainwindow.ui

unix {
    CONFIG += link_pkgconfig
    PKGCONFIG += portaudio-2.0
}
