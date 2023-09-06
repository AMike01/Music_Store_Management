#include "ProdottoInfoVisitor.h"

QWidget* ProdottoInfoVisitor::getWidget() const {
    return widget;
}

ProdottoInfoVisitor::ProdottoInfoVisitor() {}

void ProdottoInfoVisitor::visitVinile(vinile& vinile, Utente* u) {

    widget = new ProdottoWindow(&vinile);
    widget->CreaVinileWindow(u);
    widget->show();

}

void ProdottoInfoVisitor::visitCd(cd& cd, Utente* u) {

    widget = new ProdottoWindow(&cd);
    widget->CreaCdWindow(u);
    widget->show();
}

void ProdottoInfoVisitor::visitCassetta(cassetta& cassetta, Utente* u) {

    widget = new ProdottoWindow(&cassetta);
    widget->CreaCassettaWindow(u);
    widget->show();
}


