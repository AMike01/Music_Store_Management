#include "registrazioneWindow.h"

registrazionewindow::registrazionewindow() {

    setWindowTitle("Registrazione");
    setMinimumSize(280,130);

    rUsername = new QLabel("Username:");
    rPassword = new QLabel("Password:");
    rPassword_repeat = new QLabel("Ripeti password:");

    UsernameRegister = new QLineEdit();
    PasswordRegister = new QLineEdit();
    Password_repeatRegister = new QLineEdit();

    PasswordRegister->setEchoMode(QLineEdit::Password);
    Password_repeatRegister->setEchoMode(QLineEdit::Password);

    UsernameRegister->setPlaceholderText("Inserire username");
    PasswordRegister->setPlaceholderText("Inserire password");
    Password_repeatRegister->setPlaceholderText("Ripeti password");
    rPassword_repeat = new QLabel("Ripeti password:");

    QRegularExpression rx("[A-Za-z0-9]{1,16}");
    QValidator *validator = new QRegularExpressionValidator(rx, this);
    UsernameRegister->setValidator(validator);

    bRegister = new QPushButton("Registrati");

    gridRegister = new QGridLayout();
    gridRegister->addWidget(rUsername,1,0);
    gridRegister->addWidget(UsernameRegister,1,1);
    gridRegister->addWidget(rPassword,2,0);
    gridRegister->addWidget(PasswordRegister,2,1);
    gridRegister->addWidget(rPassword_repeat,3,0);
    gridRegister->addWidget(Password_repeatRegister,3,1);
    gridRegister->addWidget(bRegister,4,Qt::AlignLeft);

    layoutRegister = new QVBoxLayout();
    layoutRegister->addLayout(gridRegister);
    setLayout(layoutRegister);

    connect(bRegister,SIGNAL(clicked()),this,SLOT(slRegister()));
}

// controlla che i campi non siano stati omessi
// e che le password coincidano
void registrazionewindow::slRegister() {
    if(UsernameRegister->text()!="" && PasswordRegister->text()!=""
            && Password_repeatRegister->text()!="") {
        if(PasswordRegister->text()!=Password_repeatRegister->text()) {
            QMessageBox::critical(this,"Errore","I due campi password non corrispondono!");
            clearPasswords();
            return;
        }
        else
            emit tryRegistrazione(UsernameRegister->text(), PasswordRegister->text());
    }
    else
        QMessageBox::critical(this,"Errore","Alcuni campi sono stati omessi!");
}

// nel caso in cui le password non coincidano le cancella entrambe
void registrazionewindow::clearPasswords() {
    PasswordRegister->clear();
    Password_repeatRegister->clear();
}

// slot che ricevono signal da loginwindow
void registrazionewindow::regRiuscita() {
    QMessageBox::information(this,"Riuscito", "Iscrizione effettuata correttamente");
    emit UsernamePerLogin(UsernameRegister->text());
    this->close();
}

void registrazionewindow::regNonRiuscita() {
    QMessageBox::critical(this,"Errore","Username già presente!");
}
