#ifndef PRODOTTO_H
#define PRODOTTO_H
#include <QString>
#include "ProdottoVisitorInterface.h"
#include "utente.h"
#include <QXmlStreamReader>
#include <QXmlStreamWriter>

class prodotto {

    protected:
        QString nome;
        QString autore;
        double prezzo;
        
    public:
        prodotto(QString n= "", QString a="", double p=0);

        virtual ~prodotto() =0;

        virtual QString getNome() const =0;
        virtual QString getAutore() const =0;
        virtual double getPrezzo() const =0;
        virtual QString getInfo() const =0;

        virtual void setNome(QString newNome);
        virtual void setAutore(QString newAutore);
        virtual void setPrezzo(double newPrezzo);

        virtual bool operator==(const prodotto* p) const =0;
        virtual bool operator!=(const prodotto* p) const =0;

        virtual prodotto *clone() const =0;

        virtual void loadProd(QXmlStreamReader &r);
        virtual void saveProd(QXmlStreamWriter &w) const;
        virtual void accept(ProdottoVisitorInterface& visitor, Utente* u) =0;

};

#endif // PRODOTTO_H
