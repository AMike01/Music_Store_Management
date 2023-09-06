#ifndef VINILE_H
#define VINILE_H

#include "prodotto.h"

class vinile : public prodotto {


    private:
        unsigned int rpm; // 33, 45, 78 giri

    public:
            vinile(QString n="", QString a="", double p=0, unsigned int r=33);


            // GETTERS
            QString getNome() const override;
            QString getAutore() const override;
            double getPrezzo() const override;
            QString getInfo() const override;

            // SETTERS
            void setRpm(unsigned int newRpm);

            virtual bool operator==(const prodotto* u) const override;
            virtual bool operator!=(const prodotto* u) const override;

            vinile* clone() const override;

            virtual void loadProd(QXmlStreamReader &r) override;
            virtual void saveProd(QXmlStreamWriter &w) const override;
            void accept(ProdottoVisitorInterface &visitor,  Utente* u) override;
};

#endif // VINILE_H
