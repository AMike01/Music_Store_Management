#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFormLayout>
#include <QMenuBar>
#include <QLabel>
#include <QLineEdit>
#include <QGridLayout>
#include <QPushButton>
#include <QGroupBox>
#include <QWidget>
#include <QtXml>
#include <QTextStream>
#include <QMessageBox>
#include <QSizePolicy>
#include <QAction>
#include "loginwindow.h"
#include "newProdottoWindow.h"
#include "modificaPasswordWindow.h"
#include "../modello/lista_prodotti.h"
#include "../modello/prodotto.h"
#include "../modello/xml_handler.h"
#include "../modello/ProdottoInfoVisitor.h"
#include "../vista/Tabella.h"



class MainWindow : public QMainWindow
{
    Q_OBJECT

private:

    lista_prodotti *prodotti;
    Utente *loggeduser;
    ProdottoInfoVisitor v;
    loginwindow *wlogin;
    newProdottoWindow * newP;
    xml_handler* x;

    //MENU

    QMenu* menu_utente;
    QAction* modProfilo;
    QWidget * interfaccia;
    QVBoxLayout * layout;

    // RICERCA
    QHBoxLayout * layout2;
    QGroupBox* ricerca;
    QFormLayout* tabellaRicerca;
    QLabel* labelAutore;
    QLabel* labelTitolo;
    QLineEdit* textAutore;
    QLineEdit* textTitolo;
    QPushButton* avviaRicerca;

    //PULSANTIERA
    QGridLayout * pulsantiera;
    QLabel * messaggio;
    QLabel * messaggio2;
    QPushButton* pushAzzeraFiltri;
    QPushButton* pushVedivinili;
    QPushButton* pushVedicd;
    QPushButton* pushVedicassetta;
    QPushButton* pushAddprodotto;
    QPushButton* pushRicerca;

    //TABELLA
    Tabella * table;
    QGridLayout * layoutTabella;
    QWidget * boxtabella;
    QGridLayout* tablelayout;

    void launchlogin();
    void visualizzaMenu();
    void visualizzaPulsantiera();
    void visualizzaRicerca();
    void visualizzaTabella();

public:
    MainWindow(QWidget *parent = nullptr);

private slots:
    void login(const QString&, const QString&);
    void visualizzaProdotto(prodotto*);
    void launchNewProdotto();
    void addProdotto(prodotto*);
    void modificaProdotto(prodotto*,prodotto*);
    void salvaProdotto();
    void eliminaProdotto(prodotto*);
    void addUtente(const QString&, const QString&);
    void azzeraFiltri();
    void vediVinili();
    void vediCassette();
    void vediCD();
    void RicercaProdotti();
    void LaunchModificaProfilo();
    void ModificaProfilo(QString,QString);

signals:
    void registrazioneRiuscita();
    void registrazioneNonRiuscita();
    void RicercaPerNome(QString);
    void RicercaPerAutore(QString);
    void Ricerca(QString,QString);

};
#endif // MAINWINDOW_H


