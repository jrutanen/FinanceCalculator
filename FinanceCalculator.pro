#-------------------------------------------------
#
# Project created by QtCreator 2015-05-12T00:56:41
#
#-------------------------------------------------

QT       += core gui
QT       += testlib
QT       += sql
QMAKE_LIBDIR += "glu32_location"

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = FinanceCalculator
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    investment.cpp \
    lsbarchart.cpp \
    test/testinterestcalc.cpp \
    mortage.cpp \
    dataset.cpp \
    infobox.cpp \
    chartview.cpp \
    budgettreeview.cpp \
    dbmanager.cpp \
    budgetrow.cpp

HEADERS  += mainwindow.h \
    investment.h \
    lsbarchart.h \
    test/testinterestcalc.h \
    mortage.h \
    dataset.h \
    infobox.h \
    chartview.h \
    budgettreeview.h \
    dbmanager.h \
    budgetrow.h

FORMS    += mainwindow.ui
