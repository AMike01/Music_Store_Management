#include "cd.h"

// Constructor

cd::cd(QString n, QString a, double p, bool r) : prodotto(n,a,p), riscrivibile(r) {}

// Get Methods

QString cd::getNome() const { return nome;}
QString cd::getAutore() const { return autore;}
double cd::getPrezzo() const { return prezzo;}

QString cd::getInfo() const {
    if(riscrivibile)
        return QString::fromStdString("1");
    else
        return QString::fromStdString("0");
}

// Set Methods
void cd::setRisc(bool newR) {riscrivibile = newR ;}

bool cd::operator==(const prodotto *u) const {
      return ((this->getNome() == u->getNome()) && (this->getPrezzo() == u->getPrezzo())
               && (this->getAutore() == u->getAutore()) && (this->getInfo() == u->getInfo()));
}

bool cd::operator!=(const prodotto *u) const {
      return ((this->getNome() != u->getNome()) || (this->getPrezzo() != u->getPrezzo())
               || (this->getAutore() != u->getAutore()) || (this->getInfo() != u->getInfo()));
}

cd* cd::clone() const {
    return new cd(*this);
}

void cd::accept(ProdottoVisitorInterface &v, Utente* u)
{
    v.visitCd(*this, u);
}

void cd::loadProd(QXmlStreamReader& r){
    prodotto::loadProd(r);
    r.readNextStartElement();

    if(r.name().toString()=="risc") {
        if(r.readElementText()=="1")
            this->setRisc(1);
        else
            this->setRisc(0);
    }
}

void cd::saveProd(QXmlStreamWriter& w) const {
    w.writeStartElement("cd");
    prodotto::saveProd(w);
    w.writeTextElement("risc", this->getInfo());
    w.writeEndElement();
}

