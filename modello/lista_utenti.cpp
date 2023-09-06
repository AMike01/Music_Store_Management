#include "lista_utenti.h"

lista_utenti::nodo::nodo() {}
lista_utenti::nodo::nodo(Utente* p, nodo* n) : info(p), next(n) {}
lista_utenti::nodo::nodo(nodo *t) {
    if(t) {
        while(t->next != nullptr){
            this->info = t->info;
            this->next = t->next;
        }
    }
}

lista_utenti::nodo::~nodo() {
    delete info;
}

lista_utenti::lista_utenti(): first(nullptr) {}

lista_utenti::lista_utenti(const lista_utenti& d): first(nullptr) {
        copy(d.first, first);
    }
lista_utenti::~lista_utenti() {if(first) destroy(first); }

 void lista_utenti::destroy(nodo* t) {
    if(t) {destroy(t->next); delete t;}
}

void lista_utenti::copy(nodo* f, nodo* &n ) const {
    if(f==nullptr) {return;}  //lista_utentia vuota
        // lista_utentia non vuota

    nodo* ptr = f;
    n=new nodo(ptr->info, nullptr);
        while(ptr->next != nullptr) {
            ptr = ptr->next;
            n->next= new nodo(ptr->info, nullptr);
            n = n->next;
        }

    }

void lista_utenti::pushFront(Utente* t) {
    first = new nodo(t, first);
}

void lista_utenti::pushBack(Utente* t) {
    if(first == 0) {
        this->first = new nodo(t, 0);
    }
    else {
        nodo* tmp = first;
            while(tmp->next!=0)
                tmp = tmp->next;

            tmp->next = new nodo(t,0);
        }
    }

void lista_utenti::svuota() {
    delete first;
    first = nullptr;
}

bool lista_utenti::is_empty() const {
    return first ==nullptr;
}
bool lista_utenti::iterator::operator==(const iterator& it) const
{
    return punt==it.punt;
}

bool lista_utenti::iterator::operator!=(const iterator& it) const
{
    return punt!=it.punt;
}

lista_utenti::iterator& lista_utenti::iterator::operator++()
{
    if (punt)
        punt=punt->next;
    return *this;
}

lista_utenti::iterator lista_utenti::iterator::operator++(int)
{
    iterator it=*this;
    if (punt)
        punt=punt->next;
    return it;
}

lista_utenti::iterator lista_utenti::begin() const
{
    lista_utenti::iterator it;
    it.punt=first; //amicizia
    return it;
}

lista_utenti::iterator lista_utenti::end() const
{
    iterator it;
    it.punt=0;
    return it;
}

Utente* lista_utenti::operator[](const lista_utenti::iterator& it) const {
    return it.punt->info;
}

