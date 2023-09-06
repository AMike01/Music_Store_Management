 #ifndef XML_HANDLER_H
#define XML_HANDLER_H

#include <QtXml>
#include <QDebug>
#include <QFile>
#include <QXmlStreamReader>
#include <QXmlStreamWriter>
#include <QIODevice>
#include <QTextStream>
#include <QDir>
#include "modello/utente.h"
#include "modello/lista_utenti.h"
#include "modello/prodotto.h"
#include "modello/lista_prodotti.h"
#include "modello/admin.h"
#include "modello/ospite.h"
#include "modello/cassetta.h"
#include "modello/cd.h"
#include "modello/vinile.h"


class xml_handler {
private:

    static QString fileprod;
    static QString fileuser;
    lista_prodotti* prodotti;
    lista_utenti* utenti;

public:
    xml_handler();

    void loadUtenti();
    void salvaUtenti() const;
    Utente* checkUtente(QString, QString) const;
    bool aggiungiUtente(QString, QString);
    Utente* modificaPassword(QString, QString);


    void loadProdotti();
    void salvaProdotti() const;
    bool aggiungiProdotto(prodotto* u);
    bool deleteProdotto(prodotto* u);
    bool modificaProdotto(prodotto* oldp, prodotto* newp);
    lista_prodotti* getProdotti() const;
    void setProdotti(lista_prodotti*);
};

#endif // XML_HANDLER_H
