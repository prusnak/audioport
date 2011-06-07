QT        += core gui
TARGET     = audioport
TEMPLATE   = app
SOURCES   += app.cpp mainwindow.cpp presetbutton.cpp audioport-common.cpp audioport-portaudio.cpp
HEADERS   += mainwindow.h presetbutton.h audioport-common.h audioport-portaudio.h
FORMS     += mainwindow.ui
RESOURCES += resources.rc

unix {
    CONFIG += link_pkgconfig
    PKGCONFIG += portaudio-2.0
}
