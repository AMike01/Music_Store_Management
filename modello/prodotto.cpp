#include "prodotto.h"

prodotto::prodotto(QString n, QString a, double p): nome(n), autore(a), prezzo(p) {}
prodotto::~prodotto() {}

// Set Methods

void prodotto::setNome(QString newNome) { nome = newNome;}
void prodotto::setAutore(QString newAutore) {autore = newAutore;}
void prodotto::setPrezzo(double newPrezzo) { prezzo = newPrezzo;}

void prodotto::loadProd(QXmlStreamReader& r) {
    r.readNextStartElement();
    if(r.name().toString()=="nome") this->setNome(r.readElementText());
    r.readNextStartElement();
    if(r.name().toString()=="autore") this->setAutore(r.readElementText());
    r.readNextStartElement();
    if(r.name().toString()=="prezzo") this->setPrezzo(r.readElementText().toDouble());
}

void prodotto::saveProd(QXmlStreamWriter& w) const {
    w.writeTextElement("nome", this->getNome());
    w.writeTextElement("autore", this->getAutore());
    w.writeTextElement("prezzo", QString::number(this->getPrezzo(),'f',2));
}

