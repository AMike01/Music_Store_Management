#include "loginwindow.h"

// Costruttore
loginwindow::loginwindow(){
    setWindowTitle("Login");
    setMinimumSize(280,130);

    lImmagine = new QLabel();
    lImmagine->setAlignment(Qt::AlignCenter);

    QPixmap image("./resources/icon.png");
    lImmagine->setPixmap(image.scaled(210,190,Qt::KeepAspectRatio));

    lMain= new QLabel("Benvenuto in OldMusicStore");
    lMain->setStyleSheet("font: bold 16px; color: dark brown");
    lUsername = new QLabel("Username");
    lPassword = new QLabel("Password");
    lOppure = new QLabel("oppure");
    tUsername = new QLineEdit();
    tPassword = new QLineEdit();

    tUsername->setPlaceholderText("Inserire username");
    tPassword->setPlaceholderText("Inserire password");

    QRegularExpression rx("[A-Za-z0-9]{1,16}");
    QValidator *validator = new QRegularExpressionValidator(rx, this);
    tUsername->setValidator(validator);

    tPassword->setEchoMode(QLineEdit::Password);

    bLogin = new QPushButton("Accedi");
    bRegister = new QPushButton("Registrati");

    gridLogin=new QGridLayout;
    gridLogin -> setAlignment (Qt :: AlignVCenter | Qt :: AlignHCenter );
    gridLogin->addWidget(lMain,0,0,1,2, Qt::AlignCenter);
    gridLogin->addWidget(lUsername,1,0);
    gridLogin->addWidget(tUsername,1,1);
    gridLogin->addWidget(lPassword,2,0);
    gridLogin->addWidget(tPassword,2,1);
    gridLogin->addWidget(bLogin,3,1);
    gridLogin->addWidget(lOppure,4,0,1,2,Qt::AlignCenter);
    gridLogin->addWidget(bRegister,5,0,1,2);


    layoutLogin= new QHBoxLayout();
    layoutLogin -> setAlignment (Qt :: AlignVCenter | Qt :: AlignHCenter );
    layoutLogin->addWidget(lImmagine);
    layoutLogin->addLayout(gridLogin);

    setLayout(layoutLogin);

    setWindowFlags(windowFlags() & ~Qt::WindowCloseButtonHint);

    connect(bLogin,SIGNAL(clicked()),this,SLOT(emitlogin()));
    connect(bRegister,SIGNAL(clicked()),this,SLOT(launchRegistrazione()));
}


// cancella i campi immessi
void loginwindow::clearF(){
    tPassword->clear();
    tUsername->clear();
}


// funziona chiamata da mainwindow in caso di errore nel login
void loginwindow::errorLogin() {
    QMessageBox::critical(this,"Errore","Credenziali non esatte");
}

// Slot
void loginwindow::emitlogin(){
    emit trylogin(tUsername->text(),tPassword->text());
}

// crea window per la registrazione
void loginwindow::launchRegistrazione() {

    registrazionewindow* r = new registrazionewindow();
    connect(r,SIGNAL(tryRegistrazione(QString,QString)),this,SIGNAL(tryRegister(QString,QString)));
    connect(r,SIGNAL(UsernamePerLogin(QString)),this,SLOT(UsernameDaReg(QString)));
    connect(this,SIGNAL(regRiuscita()),r,SLOT(regRiuscita()));
    connect(this,SIGNAL(regNonRiuscita()),r,SLOT(regNonRiuscita()));

    r->exec();
}

// riceve dalla registrazione l'username dell'account appena creato
void loginwindow::UsernameDaReg(QString u) {
    tUsername->setText(u);
}


