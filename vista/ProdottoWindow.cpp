#include "ProdottoWindow.h"

// COSTRUTTORE
ProdottoWindow::ProdottoWindow(prodotto* pr) : p(pr)
{

    setMinimumSize(320,180);

    imgLabel=new QLabel();
    imgLabel->setAlignment(Qt::AlignCenter);
    nomeLabel = new QLabel("Nome:");
    nome = new QLineEdit(p->getNome());
    autoreLabel = new QLabel("Autore:");
    autore = new QLineEdit(p->getAutore());
    prezzoLabel = new QLabel("Prezzo:");
    prezzo = new QDoubleSpinBox();
    prezzo->setMaximum(999999.99);
    prezzo->setValue(QString::number(p->getPrezzo()).toDouble());
    salva = new QPushButton("Salva");
    elimina = new QPushButton("Elimina");

    gridlayout= new QGridLayout();
    gridlayout-> setAlignment(Qt :: AlignCenter | Qt :: AlignTop );


    gridlayout->addWidget(nomeLabel,0,0);
    gridlayout->addWidget(nome,0,1,1,2);
    gridlayout->addWidget(autoreLabel,1,0);
    gridlayout->addWidget(autore,1,1,1,2);
    gridlayout->addWidget(prezzoLabel,2,0);
    gridlayout->addWidget(prezzo,2,1,1,2);
    gridlayout->addWidget(salva,5,1,Qt::AlignLeft);
    gridlayout->addWidget(elimina,5,2,Qt::AlignLeft);

    layoutProd = new QVBoxLayout();
    layoutProd->addWidget(imgLabel);
    layoutProd->addLayout(gridlayout);
    setLayout(layoutProd);

    connect(salva, SIGNAL(clicked(bool)), this, SLOT(trySalvaProdotto()));
    connect(elimina, SIGNAL(clicked(bool)), this, SLOT(tryEliminaProdotto()));
}

// funzioni specifiche che vanno a creare la giusta window in base al tipo di prodotto
void ProdottoWindow::CreaCassettaWindow(Utente* u) {

    QPixmap image("./resources/cassetta.png");
    imgLabel->setPixmap(image.scaled(200,190,Qt::KeepAspectRatio));
    QString title = QString::fromStdString("Cassetta: ") + p->getNome();
    setWindowTitle(title);
    tipo_prodotto = new QString("cassetta");
    tipoLabel = new QLabel("Tipo cassetta:");
    tipo = new QLineEdit(p->getInfo());
    tipo->hide();

    tipoCombo = new QComboBox();
    tipoCombo->addItem("c60");
    tipoCombo->addItem("c90");
    tipoCombo->addItem("c120");
    tipoCombo->setCurrentText(p->getInfo());

    // controlla se l'utente è admin, se non lo è blocca la modifica
    if(!u->isAdmin()) {
        this->bloccaModifica();
        tipo->setReadOnly(true);
        tipo->show();
        tipoCombo->hide();
    }

    gridlayout->addWidget(tipoLabel,3,0);
    gridlayout->addWidget(tipo,3,1);
    gridlayout->addWidget(tipoCombo,3,1);
}

void ProdottoWindow::CreaVinileWindow(Utente* u) {

    QPixmap image("./resources/vinile.png");
    imgLabel->setPixmap(image.scaled(200,190,Qt::KeepAspectRatio));
    QString title = QString::fromStdString("Vinile: ") + p->getNome();
    setWindowTitle(title);
    tipo_prodotto = new QString("vinile");
    rpmLabel = new QLabel("Giri per minuto:");
    rpm = new QLineEdit(p->getInfo());
    rpm->hide();

    rpmCombo = new QComboBox();
    rpmCombo->addItem("33");
    rpmCombo->addItem("45");
    rpmCombo->addItem("78");
    rpmCombo->setCurrentText(p->getInfo());

    if(!u->isAdmin()) {
        this->bloccaModifica();
        rpm->setReadOnly(true);
        rpm->show();
        rpmCombo->hide();
    }

    gridlayout->addWidget(rpmLabel,3,0);
    gridlayout->addWidget(rpm,3,1);
    gridlayout->addWidget(rpmCombo,3,1);
}


void ProdottoWindow::CreaCdWindow(Utente* u) {

    QPixmap image("./resources/cd.png");
    imgLabel->setPixmap(image.scaled(200,190,Qt::KeepAspectRatio));
    QString title = QString::fromStdString("Cd: ") + p->getNome();
    setWindowTitle(title);
    tipo_prodotto = new QString("cd");
    riscLabel = new QLabel("Cd riscrivibile:");
    risc = new QLineEdit((p->getInfo()=="1") ? "Si" : "No");
    risc->hide();
    risc_si = new QRadioButton("Si");
    risc_no = new QRadioButton("No");

    if(!u->isAdmin()) {
        this->bloccaModifica();
        risc->setReadOnly(true);
        risc->show();
        risc_si->hide();
        risc_no->hide();
    }

    gridlayout->addWidget(riscLabel,3,0);
    gridlayout->addWidget(risc,3,1);
    gridlayout->addWidget(risc_si,3,1);
    gridlayout->addWidget(risc_no,3,2);

    if(p->getInfo() == "1")
        risc_si->setChecked(true);
    else
        risc_no->setChecked(true);
}

// blocca la modifica e nasconde i pulsanti di modifica ed eliminazionw
void ProdottoWindow::bloccaModifica() {
    nome->setReadOnly(true);
    autore->setReadOnly(true);
    prezzo->setReadOnly(true);
    salva->hide();
    elimina->hide();
}

// crea conferma window
void ProdottoWindow::tryEliminaProdotto() {

    confermaWindow* conf = new confermaWindow();
    connect(conf,SIGNAL(confermaElimina()), this, SLOT(confermaEliminaProdotto()));
    conf->exec();
}

// eliminazione confermata
void ProdottoWindow::confermaEliminaProdotto() {
    emit deleteProdotto(p);
    this->hide();
    this->close();
}

// controlla che tutti i campi siano stati inseriti
// se non ci sono state modifiche chiudi la finestra
void ProdottoWindow::trySalvaProdotto() {

    if(nome->text()!="" && autore->text()!="" && prezzo->value()!=0) {
         if(tipo_prodotto->toStdString()=="vinile")
         {
             vinile* v = new vinile(nome->text(),autore->text(),prezzo->value(),rpmCombo->currentText().toInt());

             if(p->getNome()==v->getNome() && p->getAutore() == v->getAutore()
                    && p->getPrezzo() == v->getPrezzo() && p->getInfo() == v->getInfo()) {
                emit salvaProdotto();
                this->close();
             }
             else {
                emit modificaProdotto(p,v);
                this->close();
             }
         }
         else if(tipo_prodotto->toStdString()=="cd") {
             bool risc = 0;

             if(risc_si->isChecked())
                    risc = 1;

             cd *c = new cd(nome->text(),autore->text(),prezzo->value(),risc);

             if(p->getNome()==c->getNome() && p->getAutore() == c->getAutore()
                    && p->getPrezzo() == c->getPrezzo() && p->getInfo() == c->getInfo()) {
                emit salvaProdotto();
                this->close();
             }
             else {
                emit modificaProdotto(p,c);
                this->close();
             }
         }
         else
         {
             cassetta* ca = new cassetta(nome->text(),autore->text(),prezzo->value(),tipoCombo->currentText());

             if(p->getNome()==ca->getNome() && p->getAutore() == ca->getAutore()
                    && p->getPrezzo() == ca->getPrezzo() && p->getInfo() == ca->getInfo()) {
                emit salvaProdotto();
                this->close();
             }
             else {
                emit modificaProdotto(p,ca);
                this->close();
             }
         }
    }
    else
        QMessageBox::critical(this,"Errore","Alcuni campi sono stati omessi!");
}



