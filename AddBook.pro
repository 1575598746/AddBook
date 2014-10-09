#-------------------------------------------------
#
# Project created by QtCreator 2013-04-08T19:08:58
#
#-------------------------------------------------

QT       += core gui sql

TARGET = AddBook
TEMPLATE = app


SOURCES +=src/main.cpp \
    src/dialog.cpp \
    src/getdatabase.cpp \
    src/qmessage_dialog.cpp \
    src/qmessage2_dialog.cpp \
    src/qmessage3_dialog.cpp \
    src/modifymessage_dialog.cpp

HEADERS  +=\
    src/getdatabase.h \
    src/qmessage_dialog.h \
    src/qmessage2_dialog.h \
    src/qmessage3_dialog.h \
    src/modifymessage_dialog.h \
    src/dialog.h

FORMS    += dialog.ui \
    qmessage_dialog.ui \
    qmessage2_dialog.ui \
    qmessage3_dialog.ui \
    modifymessage_dialog.ui

RESOURCES += \
    source.qrc
