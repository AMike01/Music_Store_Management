#include "vinile.h"


vinile::vinile(QString n, QString a, double p, unsigned int r) : prodotto(n,a,p), rpm(r) {}

// Get Methods

QString vinile::getNome() const { return nome;}

double vinile::getPrezzo() const { return prezzo;}

QString vinile::getAutore() const {return autore;}

QString vinile::getInfo () const { return QString::number(rpm);}

// Set Methods
void vinile::setRpm(unsigned int newRpm) {rpm = newRpm;}

bool vinile::operator==(const prodotto *u) const {
      return ((this->getNome() == u->getNome()) && (this->getPrezzo() == u->getPrezzo())
               && (this->getAutore() == u->getAutore()) && (this->getInfo() == u->getInfo()));
}

bool vinile::operator!=(const prodotto *u) const {
    return ((this->getNome() != u->getNome()) || (this->getPrezzo() != u->getPrezzo())
             || (this->getAutore() != u->getAutore()) || (this->getInfo() != u->getInfo()));
}

vinile* vinile::clone() const {
    return new vinile(*this);
}

void vinile::accept(ProdottoVisitorInterface& v, Utente* u)
{
    v.visitVinile(*this, u);
}

void vinile::loadProd(QXmlStreamReader& r){
    prodotto::loadProd(r);
     r.readNextStartElement();
    if(r.name().toString()=="rpm") this->setRpm(r.readElementText().toInt());
}

void vinile::saveProd(QXmlStreamWriter& w) const {
    w.writeStartElement("vinile");
    prodotto::saveProd(w);
    w.writeTextElement("rpm", this->getInfo());
    w.writeEndElement();
}
