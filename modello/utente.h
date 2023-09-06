#ifndef UTENTE_H
#define UTENTE_H

#include <QString>
#include <QXmlStreamReader>
#include <QXmlStreamWriter>

class Utente
{

private:
    QString username;
    QString password;

public:
    Utente();
    Utente(QString, QString);

    virtual ~Utente() =0;

    QString GetUsername() const;
    QString GetPassword() const;

    void setUsername(const QString u);
    void setPassword(QString p);

    virtual bool isAdmin() const=0;

    virtual Utente *clone() const=0;

    virtual void saveUser(QXmlStreamWriter& xmlWriter) const;
    void loadUser(QXmlStreamReader& xmlReader);

};

#endif // UTENTE_H
