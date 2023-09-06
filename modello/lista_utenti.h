#ifndef LISTA_UTENTI_H
#define LISTA_UTENTI_H

#include "utente.h"

class lista_utenti {

    friend class iterator;
    private:
        class nodo
        {
            public:
                Utente* info;
                nodo *next;
                nodo();
                nodo(Utente*, nodo* n=nullptr);
                nodo(nodo*);
                ~nodo();
        };

    nodo* first; // list

    public:

        class iterator {
            friend class lista_utenti;
            private:
                lista_utenti::nodo* punt;
            public:
                bool operator==(const iterator&) const;
                bool operator!=(const iterator&) const;
                iterator& operator++(); //++ prefisso
                iterator operator++(int); //++ postfisso
        };

        iterator begin() const;
        iterator end() const;
        Utente* operator[](const iterator&) const;

        // fine iteratore

        void pushFront(Utente*); // inserisce all'inizio della lista
        void pushBack(Utente*); // inserisce alla fine della lista
        void svuota();
        bool is_empty() const;

        lista_utenti();
        lista_utenti(const lista_utenti&);
        ~lista_utenti();
        void copy(nodo*, nodo* &n) const;
        static void destroy(nodo*);

};

#endif // LISTA_UTENTI_H
