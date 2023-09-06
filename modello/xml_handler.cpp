#include "xml_handler.h"

QString xml_handler::fileprod = "prodotti.xml";
QString xml_handler::fileuser = "utenti.xml";

// COSTRUTTORE
xml_handler::xml_handler() {
    prodotti = new lista_prodotti();
    utenti = new lista_utenti();
    loadProdotti();
    loadUtenti();
}


// FUNZIONI UTENTI

// carica gli utenti dall'XML
void xml_handler::loadUtenti() {
    QFile file(fileuser);
    utenti->svuota();

    if(file.open(QIODevice::ReadOnly | QIODevice::Text)){

        QXmlStreamReader xmlReader;
        xmlReader.setDevice(&file);
        xmlReader.readNextStartElement();

        while(!xmlReader.atEnd())
        {
            Utente* us = nullptr;

            if(xmlReader.name().toString() == "admin")
                us = new Admin;
            else if(xmlReader.name().toString() == "ospite")
                us = new Ospite;

            if(us)
            {
                us->loadUser(xmlReader);
                utenti->pushFront(us);
                xmlReader.readNextStartElement();
            }
            xmlReader.readNextStartElement();
        }
    }
    else
        qDebug() << "Errore! File XML Utenti non presente!";
}

// salva utenti sull'XML
void xml_handler::salvaUtenti() const {

    QFile file(fileuser);
    file.open(QFile::WriteOnly);
    QXmlStreamWriter xmlWriter(&file);
    xmlWriter.setAutoFormatting(true);
    xmlWriter.writeStartDocument();
    xmlWriter.writeStartElement("utenti");

    lista_utenti::iterator i=utenti->begin();
    for(;i!=utenti->end();++i){
        (*utenti)[i]->saveUser(xmlWriter);
    }
    xmlWriter.writeEndElement();
    xmlWriter.writeEndDocument();
    file.close();
}

// controlla che l'utente che sta facendo il login sia presente nella lista
Utente* xml_handler::checkUtente(QString username, QString password) const {
    Utente* loggeduser = nullptr;
    lista_utenti::iterator i = utenti->begin();

    for(; i!=utenti->end(); ++i) {
        if((*utenti)[i]->GetUsername() == username && (*utenti)[i]->GetPassword() == password) {
            loggeduser=(*utenti)[i];

            if(loggeduser->isAdmin()) {
                return new Admin(loggeduser->GetUsername(),loggeduser->GetPassword());
            }
            else
                return new Ospite(loggeduser->GetUsername(),loggeduser->GetPassword());
        }
    }
    return loggeduser;
}

// aggiunge nuovo utente se non è già presente
bool xml_handler::aggiungiUtente(QString username, QString password) {
    bool present = 0;
    Utente* us = nullptr;

    lista_utenti::iterator it = utenti->begin();
    for(; it!=utenti->end(); it++) {
        us = (*utenti)[it];

        if(us->GetUsername() == username)
            present = 1;
    }

    if(!present) {
        utenti->pushFront(new Ospite(username,password));
        salvaUtenti();
        return 1;
    }
    else
        return 0;
}

Utente* xml_handler::modificaPassword(QString u, QString p) {

    lista_utenti::iterator it = utenti->begin();
    Utente* us;

    for(; it!=utenti->end(); ++it) {
        us = (*utenti)[it];

        if(us->GetUsername() == u) {
            us->setPassword(p);
            salvaUtenti();
            return us;
        }
    }
    return nullptr;
}


// FUNZIONI PRODOTTI
lista_prodotti* xml_handler::getProdotti() const { return prodotti; }

void xml_handler::setProdotti(lista_prodotti* list) { prodotti = list;}

// carica i prodotti dall'XML
void xml_handler::loadProdotti()
{
    prodotti->svuota();
    QFile file(fileprod);

    if(!file.open(QIODevice::ReadOnly | QIODevice::Text))
        qDebug() << "Errore! File XML Prodotti non presente!";
    else {
        QXmlStreamReader xmlReader;
        xmlReader.setDevice(&file);

        xmlReader.readNextStartElement();

        while(!xmlReader.atEnd()) {

            prodotto* p = nullptr;

            if(xmlReader.name().toString() == "vinile")
                p = new vinile;
            else if(xmlReader.name().toString() == "cd")
                p = new cd;
            else if(xmlReader.name().toString() == "cassetta")
                p = new cassetta;

            if(p)
            {
                p->loadProd(xmlReader); // chiamata polimorfica
                prodotti->pushFront(p);
                xmlReader.readNextStartElement();
            }
            xmlReader.readNextStartElement();
        }
    }
}

// salva i prodotti sull'XML
void xml_handler::salvaProdotti() const {

    QFile file(fileprod);
    file.open(QIODevice::WriteOnly);

    QXmlStreamWriter xmlWriter(&file);
    xmlWriter.setAutoFormatting(true);
    xmlWriter.writeStartDocument();
    xmlWriter.writeStartElement("catalogo");

    if(!prodotti->is_empty()) {
        for(lista_prodotti::iterator i=prodotti->begin(); i!=prodotti->end(); ++i) {
            (*prodotti)[i]->saveProd(xmlWriter);
        }
    }
    xmlWriter.writeEndElement();
    xmlWriter.writeEndDocument();
    file.close();
}

// aggiunge un prodotto alla lista prodotti, controllando che non sia già presente
bool xml_handler::aggiungiProdotto(prodotto* p) {
    bool present = 0;
    prodotto* t=nullptr;

    lista_prodotti::iterator it=prodotti->begin();
    for(; it!=prodotti->end(); ++it){

        t = (*prodotti)[it];
        if(t->getNome()==p->getNome() && t->getAutore() == p->getAutore()
                && t->getPrezzo() == p->getPrezzo() && t->getInfo() == p->getInfo())
            present = 1;
    }

    if(!present) {
        prodotti->pushFront(p);
        salvaProdotti();
        return 1; // "Prodotto aggiunto correttamente";
    }
    else
        return 0; //"Errore: prodotto già presente";
}

// elimina un prodotto
bool xml_handler::deleteProdotto(prodotto* p) {

    bool el = prodotti->deleteProd(p);
    salvaProdotti();
    return el;
}

// elimina il vecchio prodotto e aggiunge quello nuovo
bool xml_handler::modificaProdotto(prodotto* oldp, prodotto* newp) {

    prodotto* t = nullptr;

    lista_prodotti::iterator it=prodotti->begin();
    for(; it!=prodotti->end(); ++it){

        t = (*prodotti)[it];

        if(t == oldp) {
            prodotti->deleteProd(t);
            prodotti->pushFront(newp);
            salvaProdotti();
            return 1;
        }
    }
    return 0;
}
