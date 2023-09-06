#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    setMinimumSize(650,600);
    x = new xml_handler();
    prodotti = x->getProdotti();

    this->launchlogin();
    visualizzaMenu();

    interfaccia= new QWidget(this);
    layout= new QVBoxLayout();
    layout2=new QHBoxLayout();
    layout->addLayout(layout2);
    visualizzaRicerca();
    visualizzaPulsantiera();
    visualizzaTabella();
    interfaccia->setLayout(layout);

    setCentralWidget(interfaccia);
}

//LOGIN

void MainWindow::launchlogin()
{
    wlogin = new loginwindow();

    wlogin->setWindowTitle(QString::fromStdString("Login"));
    connect(wlogin,SIGNAL(trylogin(QString,QString)),this,SLOT(login(QString,QString)));
    connect(wlogin,SIGNAL(tryRegister(QString,QString)),this,SLOT(addUtente(QString,QString)));
    connect(this,SIGNAL(registrazioneRiuscita()),wlogin,SIGNAL(regRiuscita()));
    connect(this,SIGNAL(registrazioneNonRiuscita()),wlogin,SIGNAL(regNonRiuscita()));

    wlogin->exec();
}

// fa il check se il login va a buon fine e lo invia a loginwindow
void MainWindow::login(const QString& us, const QString& pa)
{
    x = new xml_handler();
    loggeduser = x->checkUtente(us,pa);

    if(loggeduser != nullptr)
        wlogin->close();
    else {
        wlogin->clearF();
        wlogin->errorLogin();
    }
}

// crea finestra per modifica profilo
void MainWindow::LaunchModificaProfilo() {
    modificaPasswordWindow* modP = new modificaPasswordWindow(loggeduser);
    connect(modP,SIGNAL(CambiaPassword(QString,QString)),this,SLOT(ModificaProfilo(QString,QString)));
    modP->show();
}

void MainWindow::ModificaProfilo(QString u, QString p) {
    Utente* err = x->modificaPassword(u,p);

    if(err!=nullptr) {
        QMessageBox::information(this,"Riuscito", "Password modificata correttamente");
        loggeduser = err;
    }
    else
        QMessageBox::critical(this,"Errore", "Password non modficiata!");
}

// chiama la funzione aggiungiUtente su xml_handler e invia il signal
// a registrazionewindow se è riuscito o meno ad effettuare la registrazione
void MainWindow::addUtente(const QString& u, const QString& p) {

    bool addU = x->aggiungiUtente(u,p);

    if(addU)
        emit registrazioneRiuscita();
    else
        emit registrazioneNonRiuscita();
}

//MENU

void MainWindow::visualizzaMenu(){
    menu_utente= new QMenu("Utente", this);
    modProfilo= new QAction("Modifica password",this);

    menu_utente->addAction(modProfilo);

    //PULSANTI DA FINIRE
    connect(modProfilo,SIGNAL(triggered(bool)),this,SLOT(LaunchModificaProfilo()));
    menuBar()->addMenu(menu_utente);
}

//PULSANTIERA

void MainWindow::visualizzaPulsantiera(){

    pulsantiera=new QGridLayout();

       messaggio=new QLabel("Pulsantiera filtri:");
       pushAzzeraFiltri= new QPushButton("Azzera filtri");
       pushVedivinili= new QPushButton("Vedi i Vinili");
       pushVedicd= new QPushButton("Vedi i CD");
       pushVedicassetta= new QPushButton("Vedi le Cassette");

       pulsantiera->addWidget(messaggio,0,0,1,3,Qt::AlignCenter);
       pulsantiera->addWidget(pushVedivinili,1,0,1,1);
       pulsantiera->addWidget(pushVedicd,1,1,1,1);
       pulsantiera->addWidget(pushVedicassetta,1,2,1,1);
       pulsantiera->addWidget(pushAzzeraFiltri,2,0,1,3);

       connect(pushAzzeraFiltri,SIGNAL(clicked(bool)),this,SLOT(azzeraFiltri()));
       connect(pushVedivinili,SIGNAL(clicked(bool)),this,SLOT(vediVinili()));
       connect(pushVedicd,SIGNAL(clicked(bool)),this,SLOT(vediCD()));
       connect(pushVedicassetta,SIGNAL(clicked(bool)),this,SLOT(vediCassette()));

       if(loggeduser->isAdmin()){
            messaggio2=new QLabel("oppure");
            pushAddprodotto= new QPushButton("Aggiungi prodotto");
            pulsantiera->addWidget(messaggio2,3,0,1,3,Qt::AlignCenter);
            pulsantiera->addWidget(pushAddprodotto,4,0,1,3);

           connect(pushAddprodotto,SIGNAL(clicked()),this,SLOT(launchNewProdotto()));
       }

       layout2->addLayout(pulsantiera);
}

void MainWindow::visualizzaRicerca(){

    setStyleSheet("QGroupBox{ border: 1px solid gray;  margin-top: 5px;}"
                  "QGroupBox::title{ subcontrol-origin: margin; subcontrol-position:top center;}");
    labelAutore=new QLabel("Autore:");
    labelTitolo=new QLabel("Nome:");
    textAutore=new QLineEdit();
    textTitolo= new QLineEdit();
    avviaRicerca= new QPushButton("Ricerca");

    tabellaRicerca=new QFormLayout();
    tabellaRicerca->addRow(labelAutore);
    tabellaRicerca->addRow(textAutore);
    tabellaRicerca->addRow(labelTitolo);
    tabellaRicerca->addRow(textTitolo);
    tabellaRicerca->addRow(avviaRicerca);

    ricerca=new QGroupBox(tr("Inserisci parametri ricerca"));
    layout2->addWidget(ricerca);
    ricerca->setLayout(tabellaRicerca);

    connect(avviaRicerca,SIGNAL(clicked(bool)),this,SLOT(RicercaProdotti()));
}

void MainWindow::visualizzaTabella(){

    tablelayout=new QGridLayout();
    tablelayout->setAlignment(Qt::AlignCenter | Qt::AlignCenter);
    table = new Tabella(prodotti,this);
    table->setLista(prodotti);
    tablelayout->addWidget(table);

    connect(this,SIGNAL(RicercaPerNome(QString)),table,SLOT(RicercaPerNome(QString)));
    connect(this,SIGNAL(RicercaPerAutore(QString)),table,SLOT(RicercaPerAutore(QString)));
    connect(this,SIGNAL(Ricerca(QString,QString)),table,SLOT(Ricerca(QString,QString)));
    connect(table,SIGNAL(schedaProdotto(prodotto*)),this,SLOT(visualizzaProdotto(prodotto*)));
    table->show();
    layout->addLayout(tablelayout);
}

// funzioni di filtraggio tabella
void MainWindow::vediVinili() {
    table->vediVinili();
    table->show();
}

void MainWindow::vediCassette() {
    table->vediCassetta();
    table->show();
}

void MainWindow::vediCD() {
    table->vediCd();
    table->show();
}

void MainWindow::azzeraFiltri(){
    table->vedituttiProdotti(prodotti);
    table->show();
}

// chiama il visitor per la creazione di ProdottoWindow
void MainWindow::visualizzaProdotto(prodotto *p) {

    ProdottoInfoVisitor *visitor = new ProdottoInfoVisitor();
    p->accept((*visitor),loggeduser);

    connect(visitor->getWidget(),SIGNAL(deleteProdotto(prodotto*)),this,SLOT(eliminaProdotto(prodotto*)));
    connect(visitor->getWidget(),SIGNAL(salvaProdotto()),this,SLOT(salvaProdotto()));
    connect(visitor->getWidget(),SIGNAL(modificaProdotto(prodotto*,prodotto*)),this,SLOT(modificaProdotto(prodotto*,prodotto*)));
}

// crea la window per la creazione di un nuovo prodotto
void MainWindow::launchNewProdotto() {
    newP = new newProdottoWindow();
    connect(newP, SIGNAL(newProdotto(prodotto*)), this, SLOT(addProdotto(prodotto*)));
    newP->exec();
}

// chiama la funzione aggiungi prodotto su xml_handler e aggiorna i prodotti salvati su mainwindow
void MainWindow::addProdotto(prodotto* p) {

    bool err= x->aggiungiProdotto(p);
    prodotti = x->getProdotti();
    table->setLista(prodotti);
    table->vedituttiProdotti(prodotti);
    table->show();

    if(err)
        QMessageBox::information(this,"Riuscito", "Prodotto aggiunto correttamente");
    else
        QMessageBox::critical(this,"Errore","Prodotto già presente");
}

// come sopra solo per eliminazione
void MainWindow::eliminaProdotto(prodotto *p) {
    x->setProdotti(prodotti);
    bool err = x->deleteProdotto(p);
    if(prodotti->nProd() == 0){
        table->clearContents();
        table->menuGenerale();
        table->show();
    }
    else{
    table->setLista(prodotti);
    table->vedituttiProdotti(prodotti);
    table->show();
    }
    if(err)
        QMessageBox::information(this,"Riuscito", "Prodotto eliminato correttamente");
    else
        QMessageBox::critical(this,"Errore","Prodotto non eliminato");
}

// come sopra ma per modifica
void MainWindow::modificaProdotto(prodotto* oldp, prodotto* newp) {

    x->setProdotti(prodotti);
    x->salvaProdotti();
    bool err = x->modificaProdotto(oldp,newp);

    prodotti = x->getProdotti();
    table->setLista(prodotti);
    table->vedituttiProdotti(prodotti);
    table->show();

    if(err)
        QMessageBox::information(this,"Riuscito", "Prodotto modificato correttamente");
    else
        QMessageBox::critical(this,"Errore","Prodotto non modificato");
}

void MainWindow::salvaProdotto() {
    QMessageBox::information(this,"Riuscito", "Prodotto salvato correttamente");
}

// controlla se Titolo e/o Autore sono stati inseriti per la ricerca
void MainWindow::RicercaProdotti() {

    QString n = textTitolo->text();
    QString a = textAutore->text();

    if(n == "" && a == "")
        QMessageBox::critical(this,"Errore","Nessun campo di ricerca inserito!");
    else {

        if(n != "" && a =="")
            emit RicercaPerNome(n);
        else if(n=="" && a!="")
            emit RicercaPerAutore(a);
        else
            emit Ricerca(n,a);
    }
}
