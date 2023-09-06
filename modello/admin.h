#ifndef ADMIN_H
#define ADMIN_H

#include "utente.h"

class Admin : public Utente {

public:
    Admin();
    Admin(QString u, QString p);

    bool isAdmin() const override;

    Admin* clone() const override;

    virtual void saveUser(QXmlStreamWriter& r) const override;

};

#endif // ADMIN_H
