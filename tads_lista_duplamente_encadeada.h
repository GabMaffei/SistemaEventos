#pragma once

#include <iostream>

using namespace std;

//Lista Duplamente Encadeada
template<typename T>
struct TElemento_Duplamente_Encadeado {
    T dado;
    TElemento_Duplamente_Encadeado<T>* proximo;
    TElemento_Duplamente_Encadeado<T>* anterior;
};

template<typename T>
struct TLista_Duplamente_Encadeada {
    TElemento_Duplamente_Encadeado<T>* inicio;
    TElemento_Duplamente_Encadeado<T>* fim;
};

template<typename T>
void inicializar_lista_duplamente_encadeada(TLista_Duplamente_Encadeada<T> & lista) {
    lista.inicio= nullptr;
    lista.fim= nullptr;
}

template<typename T>
TElemento_Duplamente_Encadeado<T>* criar_elemento_duplamente_encadeada(T dado){
    TElemento_Duplamente_Encadeado<T>* novo= new TElemento_Duplamente_Encadeado<T>;
    novo->dado= dado;
    novo->proximo= nullptr;
    novo->anterior= nullptr;
    return novo;
}

//--------
//Inserir
template<typename T>
void inserir_final_lista_duplamente_encadeada(TLista_Duplamente_Encadeada<T>& lista, T dado){
    TElemento_Duplamente_Encadeado<T>* novo= criar_elemento_duplamente_encadeada(dado);
    if (lista.inicio == nullptr && lista.fim == nullptr) {
        lista.inicio = novo;
        lista.fim = novo;
    }
    else {
        novo->anterior = lista.fim;
        novo->anterior->proximo = novo;
        lista.fim = novo;
    }
}

template<typename T>
void inserir_posicao_lista_duplamente_encadeada(TLista_Duplamente_Encadeada<T>& lista, T dado, int posicao) {
    if (posicao > conta_lista_duplamente_encadeada(lista)) {
        throw "INVALID INDEX";
    };

    TElemento_Duplamente_Encadeado<T>* novo = criar_elemento_duplamente_encadeada(dado);
    if (lista.inicio == nullptr && lista.fim == nullptr) { //Caso lista vazia
        lista.inicio = novo;
        lista.fim = novo;
    }
    else if (posicao == 0) { //Inserir no inicio
        TElemento_Duplamente_Encadeado<T>* nav = lista.inicio;
        nav->anterior = novo;
        novo->proximo = nav;
        lista.inicio = novo;
    }
    else { //Inserir nas demais posições, podendo ser no final também
        int i = 0;
        TElemento_Duplamente_Encadeado<T>* nav = lista.inicio;
        while ((nav->proximo != nullptr) && (i < posicao - 1)) {
            nav = nav->proximo;
            i++;
        }
        novo->proximo = nav->proximo;
        nav->proximo = novo;
        novo->anterior = nav;
        if (novo->proximo == nullptr) { //Caso seja no final
            lista.fim = novo;
        }
        else { //Caso seja no meio
            novo->proximo->anterior = novo;
        }
    }
}

template<typename T>
void inserir_inicio_lista_duplamente_encadeada(TLista_Duplamente_Encadeada<T>& lista, T dado) {
    inserir_posicao_lista_duplamente_encadeada(lista, dado, 0);
}
//--------
//Remover
template<typename T>
void remover_inicio_lista_duplamente_encadeada(TLista_Duplamente_Encadeada<T> &lista) {
    if (lista.inicio == nullptr && lista.fim == nullptr) {
        throw "LIST UNDERFLOW";
    }
    else {
        TElemento_Duplamente_Encadeado<T>* apagar = lista.inicio;
        lista.inicio = apagar->proximo; //Inicio é o próximo
        if (lista.inicio == nullptr) {
            lista.fim = nullptr;
        }
        else {
            lista.inicio->anterior = nullptr; //Anterior do novo inicio (que era o próximo) é nullptr
        }
        delete apagar; //limpa memória
        apagar = nullptr;
    }
}

template<typename T>
void remover_posicao_lista_duplamente_encadeada(TLista_Duplamente_Encadeada<T>& lista, int posicao) {
    if (posicao > conta_lista_duplamente_encadeada(lista)) {
        throw "INVALID INDEX";
    };
    
    if (lista.inicio== nullptr && lista.fim == nullptr) {
        throw "LIST UNDERFLOW";
    }
    else if (posicao == 0) {
        remover_inicio_lista_duplamente_encadeada(lista);
    }
    else {
        cout << "Chegou aqui 1" << endl;
        int i = 0;
        TElemento_Duplamente_Encadeado<T>* nav = lista.inicio;
        while ((nav->proximo->proximo != nullptr) && (i < posicao - 1)) {
            nav = nav->proximo;
            i++;
        }
        TElemento_Duplamente_Encadeado<T>* apagar = nav->proximo;
        nav->proximo = nav->proximo->proximo;
        if (apagar->proximo == nullptr) { //Caso seja no final
            lista.fim = nav;
        }
        else {
            nav->proximo->anterior = nav;
        }
        delete apagar;
        apagar = nullptr;
    }
}


template<typename T>
void remover_final_lista_duplamente_encadeada(TLista_Duplamente_Encadeada<T> &lista) {
    if (lista.inicio == nullptr && lista.fim == nullptr) {
        throw "LIST UNDERFLOW";
    }
    else {
        TElemento_Duplamente_Encadeado<T>* apagar = lista.fim;
        lista.fim = apagar->anterior;
        lista.fim->proximo = nullptr;
        delete apagar;
        apagar = nullptr;
    }
}
//--------
//Obter/Busca
template<typename T>
T& obter_item_lista_duplamente_encadeada(TLista_Duplamente_Encadeada<T> lista, int posicao) {
    if (posicao < 0 || posicao >= conta_lista_duplamente_encadeada(lista)) {
        throw "INVALID INDEX";
    }
    else {
        int i = 0;
        TElemento_Duplamente_Encadeado<T>* nav = lista.inicio;
        while ((nav->proximo != nullptr) && (i < posicao)) {
            nav = nav->proximo;
            i++;
        }
        return nav->dado;
    }
}

template<typename T>
int obter_posicao_lista_duplamente_encadeada(TLista_Duplamente_Encadeada<T>& lista, T dado_para_buscar) {
    int i = 0;
    TElemento_Duplamente_Encadeado<T>* nav = lista.inicio;
    while (nav != nullptr) {
        if (compara_igualdade(nav->dado, dado_para_buscar)) {
            return i;
        }
        else {
            nav = nav->proximo;
            i++;
        }
    }
    return -1;
}

template<typename T>
bool obter_existencia_lista_duplamente_encadeada(TLista_Duplamente_Encadeada<T>& lista, T dado_para_buscar) {
    if (obter_posicao_lista_duplamente_encadeada(lista, dado_para_buscar) == -1) {
        return false;
    }
    else {
        return true;
    }
}

//--------
//Imprimir
string imprimir_elemento(TElemento_Duplamente_Encadeado<int>* elemento) {
    return to_string(elemento->dado);
}

template<typename T>
void imprimir_lista_duplamente_encadeada(TLista_Duplamente_Encadeada<T> lista, bool ordem_reverso = false){
    if (ordem_reverso == false) {
        for (TElemento_Duplamente_Encadeado<T>* nav = lista.inicio;
            nav != nullptr; nav = nav->proximo) {
            cout << imprimir_elemento(nav) << endl;
        }
        //cout << "Ordem normal" << endl;
    }
    else {
        for (TElemento_Duplamente_Encadeado<T>* nav = lista.fim;
            nav != nullptr; nav = nav->anterior) {
            cout << imprimir_elemento(nav);
        }
        //cout << "Ordem reversa" << endl;
    }
}

template<typename T>
int conta_lista_duplamente_encadeada(TLista_Duplamente_Encadeada<T> lista) {
    int i = 0;
    for (TElemento_Duplamente_Encadeado<T>* nav = lista.inicio;
        nav != nullptr; nav = nav->proximo) {
        i++;
    }
    return i;
}
