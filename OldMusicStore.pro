#-------------------------------------------------
#
# Project created by QtCreator 2023-060-05T18:52:11
#
#-------------------------------------------------

QT       += gui
QT += xml
QT += core

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = OldMusicStore
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
        main.cpp \
    modello/admin.cpp \
    modello/lista_prodotti.cpp \
    modello/lista_utenti.cpp \
    modello/xml_handler.cpp \
    modello/utente.cpp \
    modello/ospite.cpp \
    modello/cassetta.cpp \
    modello/cd.cpp \
    modello/prodotto.cpp \
    modello/vinile.cpp  \
    modello/ProdottoInfoVisitor.cpp \
    vista/confermaWindow.cpp \
    vista/Tabella.cpp \
    vista/loginwindow.cpp \
    vista/mainwindow.cpp \
    vista/ProdottoWindow.cpp \
    vista/modificaPasswordWindow.cpp \
    vista/newProdottoWindow.cpp \
    vista/registrazionewindow.cpp
   

HEADERS += \
    modello/admin.h \
    modello/lista_prodotti.h \
    modello/lista_utenti.h \
    modello/ospite.h \
    modello/xml_handler.h \
    modello/utente.h \
    modello/cassetta.h \
    modello/cd.h \
    modello/prodotto.h \
    modello/vinile.h  \
    modello/ProdottoInfoVisitor.h \
    modello/ProdottoVisitorInterface.h \
    vista/confermaWindow.h \
    vista/loginwindow.h \
    vista/mainwindow.h \
    vista/ProdottoWindow.h \
    vista/Tabella.h \
    vista/modificaPasswordWindow.h \
    vista/newProdottoWindow.h \
    vista/registrazioneWindow.h
    
   
FORMS +=

RESOURCES += 
