#include "lista_prodotti.h"

lista_prodotti::nodo::nodo() {}
lista_prodotti::nodo::nodo(prodotto* p, nodo* n) : info(p), next(n) {}
lista_prodotti::nodo::nodo(nodo *t) {
    if(t) {
        while(t->next != nullptr){
            this->info = t->info;
            this->next = t->next;
        }
    }
}

lista_prodotti::nodo::~nodo() {
    delete info;
}

lista_prodotti::lista_prodotti(): first(nullptr) {}

lista_prodotti::lista_prodotti(const lista_prodotti& d): first(nullptr) {
        copy(d.first, first);
    }
lista_prodotti::~lista_prodotti() {if(first) destroy(first); }

 void lista_prodotti::destroy(nodo* t) {
    if(t) {destroy(t->next); delete t;}
}

void lista_prodotti::copy(nodo* f, nodo* &n ) const {
    if(f==nullptr) {return;}  //lista_prodottia vuota

    nodo* ptr = f;
    n=new nodo(ptr->info, nullptr);
        while(ptr->next != nullptr) {
            ptr = ptr->next;
            n->next= new nodo(ptr->info, nullptr);
            n = n->next;
        }

    }

void lista_prodotti::pushFront(prodotto* t) {
    first = new nodo(t, first);
}

void lista_prodotti::pushBack(prodotto* t) {
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

prodotto* lista_prodotti::popFront() {
    if (first==0)
        return 0;
    prodotto* b=first->info->clone();
    first=first->next;
    return b;
}

prodotto* lista_prodotti::popBack()  {
    if (first==nullptr)
        return nullptr;
    if (first->next==nullptr)
    {
        prodotto* b=first->info->clone();
        first=nullptr;
        return b;
    }
    return nullptr;
}

void lista_prodotti::svuota() {
    delete first;
    first = nullptr;
}

bool lista_prodotti::is_empty() const {
    return first == nullptr;
}

bool lista_prodotti::iterator::operator==(const iterator& it) const
{
    return punt==it.punt;
}

bool lista_prodotti::iterator::operator!=(const iterator& it) const
{
    return punt!=it.punt;
}

lista_prodotti::iterator& lista_prodotti::iterator::operator++()
{
    if (punt)
        punt=punt->next;
    return *this;
}

lista_prodotti::iterator lista_prodotti::iterator::operator++(int)
{
    iterator it=*this;
    if (punt)
        punt=punt->next;
    return it;
}

lista_prodotti::iterator lista_prodotti::begin() const
{
    lista_prodotti::iterator it;
    it.punt=first; //amicizia
    return it;
}

lista_prodotti::iterator lista_prodotti::end() const
{
    iterator it;
    it.punt=0;
    return it;
}

prodotto* lista_prodotti::operator[](const lista_prodotti::iterator& it) const {
    return it.punt->info;
}

bool lista_prodotti::deleteProd(prodotto *p) {

    if(!this->is_empty()) {

        nodo* tmp = this->first;

        if(tmp->info == p) {
            nodo* daEliminare = tmp;
            first = first->next;
            delete daEliminare;
            return 1;
        }
        else
        {
            while(tmp->next!=nullptr) {
                if(tmp->next->info == p) {
                    nodo* daEliminare = tmp->next;
                    tmp->next = tmp->next->next;
                    delete daEliminare;
                    return 1;
                }
                tmp = tmp->next;
            }
            return 0;
        }
    }
    return 0;
}


// ricerca
lista_prodotti* lista_prodotti::searchByName(lista_prodotti* list, QString nome) {
    lista_prodotti::iterator it = list->begin();
    lista_prodotti* res = new lista_prodotti();

    for(; it!=list->end(); ++it) {
        if((*list)[it]->getNome()==nome){
            res->pushFront((*list)[it]);
        }
    }
    return res;
}

lista_prodotti* lista_prodotti::searchByAutore(lista_prodotti* list, QString autore) {
    lista_prodotti::iterator it = list->begin();
    lista_prodotti* res = new lista_prodotti();

    for(; it!=list->end(); ++it) {
        if((*list)[it]->getAutore()==autore){
            res->pushFront((*list)[it]);
        }
    }
    return res;
}


bool lista_prodotti::isCassetta(prodotto *p) {
    if(dynamic_cast<cassetta*>(p))
        return true;
    return false;
}

bool lista_prodotti::isCd(prodotto *p) {
    if(dynamic_cast<cd*>(p))
        return true;
    return false;
}

bool lista_prodotti::isVinile(prodotto *p) {
    if(dynamic_cast<vinile*>(p))
        return true;
    return false;
}

int lista_prodotti::nProd() const{
    if(first==0)
        return 0;
    int count=1;
    lista_prodotti::iterator it = this->begin();
    nodo* temp=first;
    for(; it!=this->end(); ++it) {
        if(temp->next==nullptr){
            count++;
            return count;
        }
        count++;
        temp=temp->next;
    }
    return count;
}
