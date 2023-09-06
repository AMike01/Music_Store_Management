#include "admin.h"

Admin::Admin() : Utente() {}
Admin::Admin(QString u, QString p) : Utente(u,p) {}

bool Admin::isAdmin() const {return 1;}

void Admin::saveUser(QXmlStreamWriter &r) const {
    r.writeStartElement("admin");
    Utente::saveUser(r);
    r.writeEndElement();
}

Admin* Admin::clone() const {
    return new Admin(*this);
}
