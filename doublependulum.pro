# -------------------------------------------------
# Project created by QtCreator 2009-01-19T20:51:54
# -------------------------------------------------
TARGET = doublependulum
TEMPLATE = app
DEPENDPATH += . \
    src
INCLUDEPATH += src
SOURCES += src/main.cpp \
    src/mainwindow.cpp \
    src/doublependulum.cpp \
    src/doublependulumeuler.cpp \
    src/doublependulumrk4.cpp \
    src/doublependulumwidget.cpp \
    src/colourpicker.cpp \
    src/doublependulumitem.cpp
HEADERS += src/mainwindow.h \
    src/doublependulum.h \
    src/doublependulumeuler.h \
    src/doublependulumrk4.h \
    src/doublependulumwidget.h \
    src/colourpicker.h \
    src/doublependulumitem.h
FORMS += src/mainwindow.ui
RESOURCES += resources.qrc

mac {
    ICON = icon.icns
    TARGET = "Double Pendulum"
}
