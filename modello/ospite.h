#ifndef OSPITE_H
#define OSPITE_H

#include "utente.h"

class Ospite : public Utente {

public:

    Ospite();
    Ospite(QString username, QString password);

    bool isAdmin() const override;

    Ospite* clone() const override;

    virtual void saveUser(QXmlStreamWriter& r) const override;
};

#endif // OSPITE_H
