#include "Tabella.h"

Tabella::Tabella(lista_prodotti* prodotti, QWidget *parent):
    QTableWidget(parent),listaprodotti(prodotti){
    listaRicerca = new lista_prodotti();
    menuGenerale();
    vedituttiProdotti(prodotti);
    connect(this,SIGNAL(cellDoubleClicked(int,int)),this,SLOT(slSchedaProdotto(int)));
}

void Tabella::menuGenerale(){
    this->setRowCount(0);
    QStringList tableHeader;
    setColumnCount(4);
    setColumnWidth(0,150);
    setColumnWidth(1,150);
    setColumnWidth(2,150);
    setColumnWidth(3,150);
    setMaximumWidth(1200);
    tableHeader<<"Tipologia"<<"Nome"<<"Autore"<<"Prezzo";
    setHorizontalHeaderLabels(tableHeader);
    setEditTriggers(QAbstractItemView::NoEditTriggers);
    QTableWidget::horizontalHeader()->setStretchLastSection(true);
}


// crea la tabella con i prodotti che sono passati
void Tabella::vedituttiProdotti(lista_prodotti* p) {

    listaRicerca=p;
    int row = 0;

    lista_prodotti::iterator i = p->begin();

    for(; i!=p->end(); ++i) {
        prodotto* prod = (*p)[i];
        setRowCount(row+1);
        if(lista_prodotti::isVinile(prod))
            setItem(row,0,new QTableWidgetItem(QString::fromStdString("Vinile")));
        else if(lista_prodotti::isCd(prod))
            setItem(row,0,new QTableWidgetItem(QString::fromStdString("Cd")));
        else
            setItem(row,0,new QTableWidgetItem(QString::fromStdString("Cassetta")));

        setItem(row,1,new QTableWidgetItem(prod->getNome()));
        setItem(row,2,new QTableWidgetItem(prod->getAutore()));
        setItem(row,3,new QTableWidgetItem(QString::fromStdString("€ ")+QString::number(prod->getPrezzo(),'f',2)));
        row++;
    }
}

// double click su una scheda, chiama schedaProdotto di mainwindow
// che crea ProdottoWindow con Visitor
void Tabella::slSchedaProdotto(int row) {

    int i = 0;
    if(listaRicerca->is_empty())
    {
        lista_prodotti::iterator it = listaprodotti->begin();

        // prendo il prodotto giusto
        for(;i<row && it!=listaprodotti->end();it++,i++)
            ;
        emit schedaProdotto((*listaprodotti)[it]);
    }
    else
    {
        lista_prodotti::iterator it = listaRicerca->begin();
        // prendo il prodotto giusto
        for(;i<row && it!=listaRicerca->end();it++,i++)
            ;
        emit schedaProdotto((*listaRicerca)[it]);
    }
}

// funzioni specifiche che mostrano solo i prodotti di un certo tipo
void Tabella::vediVinili(){

    lista_prodotti* temp = new lista_prodotti();
    bool is_vin = 0;
    lista_prodotti::iterator i = listaprodotti->begin();

    for(;i!=listaprodotti->end();++i){
        is_vin = lista_prodotti::isVinile((*listaprodotti)[i]);
        if(is_vin)
            temp->pushBack((*listaprodotti)[i]);
    }
    listaRicerca=temp;
    vedituttiProdotti(listaRicerca);
}

void Tabella::vediCd(){

    lista_prodotti* temp = new lista_prodotti();
    bool is_cd = 0;
    lista_prodotti::iterator i = listaprodotti->begin();

    for(;i!=listaprodotti->end();++i){
        is_cd = lista_prodotti::isCd((*listaprodotti)[i]);
        if(is_cd)
            temp->pushBack((*listaprodotti)[i]);
    }
    listaRicerca=temp;
    vedituttiProdotti(listaRicerca);

}

void Tabella::vediCassetta(){

    lista_prodotti* temp = new lista_prodotti();
    bool is_cas = 0;
    lista_prodotti::iterator i = listaprodotti->begin();

    for(;i!=listaprodotti->end();++i){
        is_cas = lista_prodotti::isCassetta((*listaprodotti)[i]);
        if(is_cas)
            temp->pushBack((*listaprodotti)[i]);
    }
    listaRicerca=temp;
    vedituttiProdotti(listaRicerca);
}

void Tabella::setLista(lista_prodotti* list){
    this->listaprodotti=list;
}


// RICERCA

// chiama la ricerca di lista_prodotti
void Tabella::RicercaPerNome(QString n) {

   listaRicerca = lista_prodotti::searchByName(listaprodotti,n);

    if(listaRicerca->is_empty())
       QMessageBox::critical(this,"Errore","Non ho trovato prodotti con quel nome!");
    else
        vedituttiProdotti(listaRicerca);
}

void Tabella::RicercaPerAutore(QString a) {

    listaRicerca = lista_prodotti::searchByAutore(listaprodotti,a);

    if(listaRicerca->is_empty())
        QMessageBox::critical(this,"Errore","Non ho trovato alcun prodotto di quell'autore!");
    else
        vedituttiProdotti(listaRicerca);
}

void Tabella::Ricerca(QString n,QString a) {

    listaRicerca = lista_prodotti::searchByName(listaprodotti,n);
    listaRicerca = lista_prodotti::searchByAutore(listaRicerca,a);

    if(listaRicerca->is_empty())
        QMessageBox::critical(this,"Errore","La ricerca non ha avuto risultati!");
    else{
        vedituttiProdotti(listaRicerca);
    }
}
