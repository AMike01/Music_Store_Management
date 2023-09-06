#ifndef LISTA_H
#define LISTA_H

#include "prodotto.h"
#include "modello/cassetta.h"
#include "modello/cd.h"
#include "modello/vinile.h"

class lista_prodotti {

    friend class iterator;
    private:
        class nodo
        {
            public:
                prodotto* info;
                nodo *next;
                nodo();
                nodo(prodotto*, nodo* n=nullptr);
                nodo(nodo*);
                ~nodo();
        };

    nodo* first; // list

    public:

        class iterator {
            friend class lista_prodotti;
            private:
                lista_prodotti::nodo* punt;
            public:
                bool operator==(const iterator&) const;
                bool operator!=(const iterator&) const;
                iterator& operator++(); //++ prefisso
                iterator operator++(int); //++ postfisso
        };

        iterator begin() const;
        iterator end() const;
        prodotto* operator[](const iterator&) const;

        // fine iteratore

        void pushFront(prodotto*); // inserisce all'inizio della lista
        void pushBack(prodotto*); // inserisce alla fine della lista
        prodotto* popFront();
        prodotto* popBack();
        void svuota();
        bool is_empty() const;
        bool deleteProd(prodotto*);
        int nProd() const;

        lista_prodotti();
        lista_prodotti(const lista_prodotti&);
        ~lista_prodotti();
        void copy(nodo*, nodo* &n) const;
        static void destroy(nodo*);

        static bool isCassetta(prodotto* p);
        static bool isCd(prodotto* p);
        static bool isVinile(prodotto* p);
        static lista_prodotti* searchByName(lista_prodotti*, QString);
        static lista_prodotti* searchByAutore(lista_prodotti*, QString);
};


#endif // LISTA_H

