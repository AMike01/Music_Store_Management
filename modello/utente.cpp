#include "utente.h"

Utente::Utente() {}

Utente::Utente(QString u, QString p) : username(u), password(p) {}

Utente::~Utente() {}

QString Utente::GetUsername() const {return username;}

QString Utente::GetPassword() const {return password;}

void Utente::setUsername(QString newUsername) { username = newUsername;}

void Utente::setPassword(QString newPassword) { password = newPassword;}

void Utente::saveUser(QXmlStreamWriter &xmlWriter) const {
    xmlWriter.writeTextElement("username",this->GetUsername());
    xmlWriter.writeTextElement("password",this->GetPassword());
}

void Utente::loadUser(QXmlStreamReader &xmlReader) {
    xmlReader.readNextStartElement();
    if(xmlReader.name().toString()=="username")
        this->setUsername(xmlReader.readElementText());

    xmlReader.readNextStartElement();
    if(xmlReader.name().toString()=="password")
        this->setPassword(xmlReader.readElementText());
}
