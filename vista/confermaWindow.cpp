#include "confermaWindow.h"

confermaWindow::confermaWindow() {
    setWindowTitle("Conferma");
    setMinimumSize(50,80);

    gridConferma = new QGridLayout;
    label = new QLabel("Vuoi veramente eliminare questo prodotto?");
    annulla = new QPushButton("Annulla");
    conferma = new QPushButton("Conferma");

    gridConferma->addWidget(label, 0,0, Qt::AlignCenter);
    gridConferma->addWidget(annulla, 1,0);
    gridConferma->addWidget(conferma, 1,1);

    layoutConferma = new QVBoxLayout();
    layoutConferma->addLayout(gridConferma);
    setLayout(layoutConferma);

    connect(annulla,SIGNAL(clicked(bool)), this, SLOT(slAnnulla()));
    connect(conferma,SIGNAL(clicked(bool)), this, SLOT(slConferma()));
}

void confermaWindow::slConferma() {
    emit confermaElimina();
    this->close();
}

void confermaWindow::slAnnulla() {
    emit annullaElimina();
    this->close();
}
