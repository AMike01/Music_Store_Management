#ifndef CD_H
#define CD_H

#include "prodotto.h"

class cd : public prodotto {

    private:
        bool riscrivibile;
    public:

        cd(QString n="", QString a="", double p=0, bool r=0);

        // GETTERS
        QString getNome() const override;
        QString getAutore() const override;
        double getPrezzo() const override;

        QString getInfo() const override;

        // SETTERS
        void setRisc(bool newR);

        virtual bool operator==(const prodotto* u) const override;
        virtual bool operator!=(const prodotto* u) const override;
        cd* clone() const override;

        virtual void loadProd(QXmlStreamReader &r) override;
        virtual void saveProd(QXmlStreamWriter &w) const override;
        void accept(ProdottoVisitorInterface &visitor, Utente* u) override;
};

#endif  // CD_H


