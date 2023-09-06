#include "newProdottoWindow.h"

newProdottoWindow::newProdottoWindow() {

    QString title = QString("Creazione nuovo prodotto:");
    setWindowTitle(title);
    setMinimumSize(320,180);

    prod_class_label = new QLabel("Tipo prodotto:");
    prod_class = new QComboBox();
    prod_class->addItem("Vinile");
    prod_class->addItem("Cd");
    prod_class->addItem("Cassetta");


    nomeLabel = new QLabel("Nome:");
    nome = new QLineEdit();
    autoreLabel = new QLabel("Autore:");
    autore = new QLineEdit();
    prezzoLabel = new QLabel("Prezzo:");
    prezzo = new QDoubleSpinBox();
    prezzo->setMaximum(999999.99);


    //vinile
    rpmLabel = new QLabel("Giri per minuto:");
    rpm = new QComboBox();
    rpm->addItem("33");
    rpm->addItem("45");
    rpm->addItem("78");

    // cd
    riscLabel = new QLabel("Riscrivibile:");
    risc_si = new QRadioButton("Si");
    risc_no = new QRadioButton("No");
    risc_no->setChecked(true);

    // cassetta
    tipoLabel = new QLabel("Tipo cassetta:");
    tipo = new QComboBox();
    tipo->addItem("c60");
    tipo->addItem("c90");
    tipo->addItem("c120");

    error = new QLabel();

    salva = new QPushButton("Salva");

    gridlayout = new QGridLayout();
    gridlayout->setAlignment(Qt :: AlignCenter | Qt :: AlignTop);


    gridlayout->addWidget(prod_class_label,0,0);
    gridlayout->addWidget(prod_class,0,1);

    gridlayout->addWidget(nomeLabel,1,0);
    gridlayout->addWidget(nome,1,1,1,2);
    gridlayout->addWidget(autoreLabel,2,0);
    gridlayout->addWidget(autore,2,1,1,2);
    gridlayout->addWidget(prezzoLabel,3,0);
    gridlayout->addWidget(prezzo,3,1,1,2);

    gridlayout->addWidget(rpmLabel,4,0);
    gridlayout->addWidget(rpm,4,1,1,2);

    gridlayout->addWidget(riscLabel,4,0);
    gridlayout->addWidget(risc_si,4,1);
    gridlayout->addWidget(risc_no,4,2);

    gridlayout->addWidget(tipoLabel,4,0);
    gridlayout->addWidget(tipo,4,1,1,2);

    gridlayout->addWidget(salva,5,1,Qt::AlignCenter);
    gridlayout->addWidget(error,6,1,Qt::AlignCenter);

    layoutProd = new QVBoxLayout();
    layoutProd->addLayout(gridlayout);
    setLayout(layoutProd);

    resetComboBox();
    VinileWindow();

    connect(prod_class, SIGNAL(currentTextChanged(QString)), this, SLOT(checkComboBox()));
    connect(salva,SIGNAL(clicked()),this,SLOT(trySalvaProdotto()));
}

// queste funzioni vengono chiamate da "CheckComboBox" 
//e cambiano i campi di inserimento per il prodotto
void newProdottoWindow::VinileWindow() {
    resetComboBox();
    rpmLabel->show();
    rpm->show();
}

void newProdottoWindow::CdWindow() {
    resetComboBox();
    riscLabel->show();
    risc_si->show();
    risc_no->show();
}

void newProdottoWindow::CassettaWindow() {
    resetComboBox();
    tipoLabel->show();
    tipo->show();
}

// nasconde tutti i campi specifici dei prodotti
void newProdottoWindow::resetComboBox() {
    rpmLabel->hide();
    rpm->hide();
    riscLabel->hide();
    risc_si->hide();
    risc_no->hide();
    tipoLabel->hide();
    tipo->hide();
}

// SLOTS

// controlla che tipo di prodotto è selezionato
void newProdottoWindow::checkComboBox() {

    if(prod_class->currentText()=="Vinile")
        VinileWindow();
    else if(prod_class->currentText()=="Cd")
        CdWindow();
    else
        CassettaWindow();
}

// controllo che tutti i campi siano stati inseriti
void newProdottoWindow::trySalvaProdotto() {

   if(nome->text()!="" && autore->text()!="" && prezzo->value()!=0) {
        if(prod_class->currentText()=="Vinile")
        {
            vinile* v = new vinile(nome->text(),autore->text(),prezzo->value(),rpm->currentText().toInt());
            emit newProdotto(v);
            this->close();
        }
        else if(prod_class->currentText()=="Cd") {
            bool is_risc = 0;
        
            if(risc_si->isChecked())
                    is_risc = 1;

            cd *c = new cd(nome->text(),autore->text(),prezzo->value(),is_risc);
            emit newProdotto(c);
            this->close();
        }
        else
        {
            cassetta* ca = new cassetta(nome->text(),autore->text(),prezzo->value(),tipo->currentText());
            emit newProdotto(ca);
            this->close();
        }
    }
    else
       QMessageBox::critical(this,"Errore","Alcuni campi sono stati omessi!");
}
