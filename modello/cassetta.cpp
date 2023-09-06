#include "cassetta.h"


// Constructor

cassetta::cassetta(QString n, QString a, double p, QString t) : prodotto(n,a,p), tipo(t) {}

// Get Methods

QString cassetta::getNome() const { return nome;}
QString cassetta::getAutore() const { return autore;}
double cassetta::getPrezzo() const { return prezzo;}

QString cassetta::getInfo() const { return tipo;}


// Set Methods
void cassetta::setTipo(QString newTipo) {tipo = newTipo;}


bool cassetta::operator==(const prodotto *u) const {
      return ((this->getNome() == u->getNome()) && (this->getPrezzo() == u->getPrezzo())
               && (this->getAutore() == u->getAutore()) && (this->getInfo() == u->getInfo()));
}

bool cassetta::operator!=(const prodotto *u) const {
      return ((this->getNome() != u->getNome()) || (this->getPrezzo() != u->getPrezzo())
               || (this->getAutore() != u->getAutore()) || (this->getInfo() != u->getInfo()));
}


cassetta* cassetta::clone() const {
    return new cassetta(*this);
}

void cassetta::accept(ProdottoVisitorInterface& v, Utente* u)
{
    v.visitCassetta(*this, u);
}

void cassetta::loadProd(QXmlStreamReader& r){
    prodotto::loadProd(r);
    r.readNextStartElement();
    if(r.name().toString()=="tipo") this->setTipo(r.readElementText());
}


void cassetta::saveProd(QXmlStreamWriter& w) const {
    w.writeStartElement("cassetta");
    prodotto::saveProd(w);
    w.writeTextElement("tipo", this->getInfo());
    w.writeEndElement();
}
