#ifndef TABLE_LISTS_H
#define TABLE_LISTS_H

#include <QWidget>
#include <QTableWidget>
#include <QHeaderView>
#include <QTableWidgetItem>
#include <QMessageBox>
#include <QVBoxLayout>
#include "../modello/lista_prodotti.h"
#include "../modello/prodotto.h"

class Tabella : public QTableWidget
{

private:
    Q_OBJECT
    lista_prodotti* listaprodotti;
    lista_prodotti* listaRicerca;

public:

    Tabella(lista_prodotti*, QWidget* =0);
    void menuGenerale();
    void vedituttiProdotti(lista_prodotti *);
    void vediVinili();
    void vediCd();
    void vediCassetta();
    void resetListaRicerca();
    void setLista(lista_prodotti* );

public slots:
    void slSchedaProdotto(int);
    void RicercaPerNome(QString);
    void RicercaPerAutore(QString);
    void Ricerca(QString,QString);

signals:
    void schedaProdotto(prodotto*);
};

#endif // TABLE_LISTS_H
