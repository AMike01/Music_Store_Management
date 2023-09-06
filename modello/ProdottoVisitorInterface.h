#ifndef PRODOTTOVISITORINTERFACE_H
#define PRODOTTOVISITORINTERFACE_H

class vinile;
class cd;
class cassetta;
class Utente;
class MainWindow;

class ProdottoVisitorInterface {
    public:
        virtual ~ProdottoVisitorInterface() = default;
        virtual void visitVinile(vinile& vinile, Utente* u) = 0;
        virtual void visitCd(cd& cd,  Utente* u) = 0;
        virtual void visitCassetta(cassetta& cassetta,  Utente* u) = 0;
};

#endif // PRODOTTOVISITORINTERFACE_H
