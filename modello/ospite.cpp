#include "ospite.h"

Ospite::Ospite() : Utente() {}
Ospite::Ospite(QString username,QString password): Utente(username,password) {}

bool Ospite::isAdmin() const {return false;}

void Ospite::saveUser(QXmlStreamWriter &r) const {
    r.writeStartElement("ospite");
    Utente::saveUser(r);
    r.writeEndElement();
}

Ospite* Ospite::clone() const {
    return new Ospite(*this);
}


