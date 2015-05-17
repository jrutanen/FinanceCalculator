#-------------------------------------------------
#
# Project created by QtCreator 2015-05-12T00:56:41
#
#-------------------------------------------------

QT       += core gui
QMAKE_LIBDIR += "glu32_location"

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = FinanceCalculator
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    investment.cpp \
    lsbarchart.cpp

HEADERS  += mainwindow.h \
    investment.h \
    lsbarchart.h

FORMS    += mainwindow.ui
