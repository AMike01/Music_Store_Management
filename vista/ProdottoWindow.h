#ifndef PRODUCTWINDOW_H
#define PRODUCTWINDOW_H

#include <QDialog>
#include <QLabel>
#include <QLineEdit>
#include <QWidget>
#include <QPushButton>
#include <QGridLayout>
#include <QAction>
#include <QString>
#include <QComboBox>
#include <QRadioButton>
#include <QMessageBox>
#include <QDoubleSpinBox>
#include "../modello/prodotto.h"
#include "../modello/vinile.h"
#include "../modello/cd.h"
#include "../modello/cassetta.h"
#include "../modello/utente.h"
#include "confermaWindow.h"


class ProdottoWindow : public QDialog
{

private:
    Q_OBJECT

    QGridLayout * gridlayout;
    QVBoxLayout * layoutProd;
    prodotto* p;
    QString* tipo_prodotto;
    QLabel* nomeLabel;
    QLineEdit* nome;
    QLabel* autoreLabel;
    QLineEdit* autore;
    QLabel* prezzoLabel;
    QDoubleSpinBox * prezzo;
    QLabel* imgLabel;

    // cassetta
    QLabel* tipoLabel;
    QLineEdit* tipo;
    QComboBox* tipoCombo;

    // cd
    QLabel* riscLabel;
    QLineEdit* risc;
    QRadioButton* risc_si;
    QRadioButton* risc_no;

    // vinile
    QLabel* rpmLabel;
    QLineEdit* rpm;
    QComboBox* rpmCombo;

    QPushButton* salva;
    QPushButton* elimina;

    void bloccaModifica();

public:

    ProdottoWindow(prodotto *p);
    void CreaVinileWindow(Utente* u);
    void CreaCdWindow(Utente* u);
    void CreaCassettaWindow(Utente* u);

signals:
    void salvaProdotto();
    void modificaProdotto(prodotto *oldp, prodotto* newp);
    void deleteProdotto(prodotto *p);

private slots:
    void trySalvaProdotto();
    void tryEliminaProdotto();
    void confermaEliminaProdotto();
};

#endif // PRODUCTWINDOW_H
