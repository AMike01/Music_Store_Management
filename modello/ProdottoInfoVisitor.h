#ifndef PRODOTTOINFOVISITOR_H
#define PRODOTTOINFOVISITOR_H
#include <QWidget>
#include <QLabel>
#include <QString>
#include "ProdottoVisitorInterface.h"
#include "../vista/ProdottoWindow.h"
#include "../modello/cd.h"
#include "../modello/cassetta.h"
#include "../modello/vinile.h"


class ProdottoInfoVisitor : public ProdottoVisitorInterface {
private:

    ProdottoWindow *widget;

public:

    ProdottoInfoVisitor();
    QWidget* getWidget() const;

    virtual void visitVinile(vinile& vinile, Utente* u);
    virtual void visitCd(cd& cd, Utente* u);
    virtual void visitCassetta(cassetta& cassetta, Utente* u);
};

#endif // PRODOTTOINFOVISITOR_H
