QT       += core gui
TARGET    = prototype
TEMPLATE  = app
SOURCES  += main.cpp mainwindow.cpp audio.cpp
HEADERS  += mainwindow.h audio.h
FORMS    += mainwindow.ui

unix {
    CONFIG += link_pkgconfig
    PKGCONFIG += portaudio-2.0
}
