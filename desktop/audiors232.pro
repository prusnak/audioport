QT        += core gui
TARGET     = audiors232
TEMPLATE   = app
SOURCES   += app.cpp mainwindow.cpp presetbutton.cpp audiors232-common.cpp audiors232-portaudio.cpp
HEADERS   += mainwindow.h presetbutton.h audiors232-common.h audiors232-portaudio.h
FORMS     += mainwindow.ui
RESOURCES += resources.rc

unix {
    CONFIG += link_pkgconfig
    PKGCONFIG += portaudio-2.0
}
