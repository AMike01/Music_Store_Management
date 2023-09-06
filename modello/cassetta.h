#ifndef CASSETTA_H
#define CASSETTA_H

#include "prodotto.h"

class cassetta : public prodotto {

    private:
        QString tipo;  // C60, C90 or C120

    public:
        cassetta(QString n="",QString a="", double p=0, QString t="");

        // GETTERS
        QString getNome() const override;
        QString getAutore() const override;
        double getPrezzo() const override;

        QString getInfo() const override;

        // SETTERS
        void setTipo(QString newTipo);

        virtual bool operator==(const prodotto* u) const override;
        virtual bool operator!=(const prodotto* u) const override;

        cassetta* clone() const override;

        virtual void loadProd(QXmlStreamReader &r) override;
        virtual void saveProd(QXmlStreamWriter &w) const override;
        void accept(ProdottoVisitorInterface& visitor, Utente* u) override;
};

#endif  // cassetta_H

