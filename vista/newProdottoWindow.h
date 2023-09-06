#ifndef NEWPRODOTTOWINDOW_H
#define NEWPRODOTTOWINDOW_H

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

class newProdottoWindow : public QDialog {

private:
    Q_OBJECT

    QGridLayout * gridlayout;
    QVBoxLayout * layoutProd;
    prodotto * p;
    QLabel* prod_class_label;
    QComboBox* prod_class;
    QLabel* nomeLabel;
    QLineEdit* nome;
    QLabel* autoreLabel;
    QLineEdit* autore;
    QLabel* prezzoLabel;
    QDoubleSpinBox * prezzo;
    QLabel* tipoLabel;
    QComboBox* tipo;
    QLabel* riscLabel;
    QRadioButton* risc_si;
    QRadioButton* risc_no;
    QLabel* rpmLabel;
    QComboBox* rpm;
    QLabel* error;

    QPushButton* salva;
    QAction* salvaProd;

    void VinileWindow();
    void CdWindow();
    void CassettaWindow();
    void resetComboBox();

public:
    newProdottoWindow();

signals:
    void newProdotto(prodotto *p);
    void ComboBoxChanged();

public slots:
    void checkComboBox();
    void trySalvaProdotto();

};

#endif // NEWPRODOTTOWINDOW_H
