#include "modificaPasswordWindow.h"

modificaPasswordWindow::modificaPasswordWindow(Utente* us) : u(us) {

    setMinimumSize(200,150);
    vecchiaPasswordlabel = new QLabel("Inserisci vecchia password:");
    vecchiaPassword = new QLineEdit();

    nuovaPasswordlabel = new QLabel("Inserisci nuova password:");
    nuovaPassword = new QLineEdit();

    nuovaPasswordRipetilabel = new QLabel("Ripeti password:");
    nuovaPasswordRipeti = new QLineEdit();

    vecchiaPassword->setEchoMode(QLineEdit::Password);
    nuovaPassword->setEchoMode(QLineEdit::Password);
    nuovaPasswordRipeti->setEchoMode(QLineEdit::Password);

    bCambia = new QPushButton("Cambia password");

    gridLayout = new QGridLayout();

    gridLayout->addWidget(vecchiaPasswordlabel,1,0);
    gridLayout->addWidget(vecchiaPassword,1,1);
    gridLayout->addWidget(nuovaPasswordlabel,2,0);
    gridLayout->addWidget(nuovaPassword,2,1);
    gridLayout->addWidget(nuovaPasswordRipetilabel,3,0);
    gridLayout->addWidget(nuovaPasswordRipeti,3,1);
    gridLayout->addWidget(bCambia,4,Qt::AlignLeft);

    modPassLayout = new QVBoxLayout();
    modPassLayout->addLayout(gridLayout);
    setLayout(modPassLayout);

    connect(bCambia,SIGNAL(clicked(bool)),this,SLOT(tryCambiaPassword()));
}

// controlla se tutti i campi sono stati inseriti e se
// la vecchia password inserita è uguale alla vecchia password
void modificaPasswordWindow::tryCambiaPassword() {

    if(vecchiaPassword->text() != "" && nuovaPassword->text() != "" && nuovaPasswordRipeti->text() != "") {
        if(nuovaPassword->text() == nuovaPasswordRipeti->text()) {
            if(vecchiaPassword->text() == u->GetPassword())
            {
                emit CambiaPassword(u->GetUsername(), nuovaPassword->text());
                this->close();
            }
            else {
                QMessageBox::critical(this,"Errore","La vecchia password non è corretta!");
                clearF();
            }
        }
        else {
            QMessageBox::critical(this,"Errore","Nuova password e ripeti password non coincidono!");
            clearF();
        }

     }
    else
        QMessageBox::critical(this,"Errore","Alcuni campi sono stati omessi!");

}

void modificaPasswordWindow::clearF() {
    vecchiaPassword->clear();
    nuovaPassword->clear();
    nuovaPasswordRipeti->clear();
}
