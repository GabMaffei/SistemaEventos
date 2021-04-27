#pragma once

#include<iostream>

using namespace std;

//Lista Encadeada Genérica
template<typename T>
struct TElemento_Encadeado {
    T dado;
    TElemento_Encadeado<T>* proximo;
};

template<typename T>
struct TLista_Encadeada {
    TElemento_Encadeado<T>* inicio;
};

template<typename T>
void inicializar_lista_encadeada(TLista_Encadeada<T> & lista) {
    lista.inicio= nullptr;
}

template<typename T>
TElemento_Encadeado<T>* criar_elemento_encadeada(T dado){
    TElemento_Encadeado<T>* novo= new TElemento_Encadeado<T>;
    novo->dado= dado;
    novo->proximo= nullptr;
    return novo;
}
//--------
//Inserir
template<typename T>
void inserir_final_lista_encadeada(TLista_Encadeada<T>& lista, T dado){

        TElemento_Encadeado<T>* novo = criar_elemento_encadeada(dado);
        if (lista.inicio == nullptr) {
            lista.inicio = novo;
        }
        else {
            TElemento_Encadeado<T>* nav = lista.inicio;
            while (nav->proximo != nullptr) {
                nav = nav->proximo;
            }
            nav->proximo = novo;
        }
}

template<typename T>
void inserir_posicao_lista_encadeada(TLista_Encadeada<T>& lista, T dado, int posicao) {
    if (posicao > conta_lista_encadeada(lista)) {
        throw "INVALID INDEX";
    };

    TElemento_Encadeado<T>* novo = criar_elemento_encadeada(dado);
    if (lista.inicio == nullptr || posicao == 0) {
        novo->proximo = lista.inicio;
        lista.inicio = novo;
    }
    else {
        int i = 0;
        TElemento_Encadeado<T>* nav = lista.inicio;
        while ((nav->proximo != nullptr) && (i < posicao - 1)) {
            nav = nav->proximo;
            i++;
        }
        novo->proximo = nav->proximo;
        nav->proximo = novo;
    }
}

template<typename T>
void inserir_inicio_lista_encadeada(TLista_Encadeada<T>& lista, T dado) {
    inserir_posicao_lista_encadeada(lista, dado, 0);
}
//--------
//Remover
template<typename T>
void remover_inicio_lista_encadeada(TLista_Encadeada<T> &lista) {
    if(lista.inicio== nullptr) {
        throw "LIST UNDERFLOW";
    }

    TElemento_Encadeado<T>* apagar= lista.inicio;
    lista.inicio= apagar->proximo;
    delete apagar;

}

template<typename T>
void remover_posicao_lista_encadeada(TLista_Encadeada<T>& lista, int posicao) {
    if (posicao > conta_lista_encadeada(lista)) {
        throw "INVALID INDEX";
    };
    
    if (lista.inicio == nullptr) {
        throw "LIST UNDERFLOW";
    }
    else if (posicao == 0) {
        remover_inicio_lista_encadeada(lista);
    }
    else {
        int i = 0;
        TElemento_Encadeado<T>* nav = lista.inicio;
        while ((nav->proximo->proximo != nullptr) && (i < posicao - 1)) { //Proteção de indice inválido
            nav = nav->proximo;
            i++;
        }
        TElemento_Encadeado<T>* apagar = nav->proximo;
        nav->proximo = nav->proximo->proximo;
        delete apagar;
        apagar = nullptr;
    }
}

template<typename T>
void remover_final_lista_encadeada(TLista_Encadeada<T>& lista) {
    if (lista.inicio == nullptr) {
        throw "LIST UNDERFLOW";
    }
    else if (lista.inicio->proximo == nullptr){
        remover_inicio_lista_encadeada(lista);
    }
    else {
        TElemento_Encadeado<T>* nav = lista.inicio;
        while (nav->proximo->proximo != nullptr) {
            nav = nav->proximo;
        }
        TElemento_Encadeado<T>* apagar = nav->proximo;
        nav->proximo = nav->proximo->proximo;
        delete apagar;
        apagar = nullptr;
    }
}
//--------
//Obter/Busca
template<typename T>
T& obter_item_lista_encadeada(TLista_Encadeada<T> lista, int posicao) {
    if (posicao < 0 || posicao > conta_lista_encadeada(lista)) {
        throw "INVALID INDEX";
    }
    else {
        int i = 0;
        TElemento_Encadeado<T>* nav = lista.inicio;
        while ((nav->proximo != nullptr) && (i < posicao)) {
            nav = nav->proximo;
            i++;
        }
        return nav->dado;
    }
}

bool compara_igualdade(int dadoUm, int dadoDois) {
    return dadoUm == dadoDois;
}

template<typename T>
int obter_posicao_lista_encadeada(TLista_Encadeada<T>& lista, T dado_para_buscar) {
    int i = 0;
    TElemento_Encadeado<T>* nav = lista.inicio;
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
bool obter_existencia_lista_encadeada(TLista_Encadeada<T>& lista, T dado_para_buscar) {
    if (obter_posicao_lista_encadeada(lista, dado_para_buscar) == -1) {
        return false;
    }
    else {
        return true;
    }
}

template<typename T>
int conta_lista_encadeada(TLista_Encadeada<T> lista) {
    int i = 0;
    for (TElemento_Encadeado<T>* nav = lista.inicio;
        nav != nullptr; nav = nav->proximo) {
        i++;
    }
    return i;
}

//--------
//Imprimir
string imprimir_elemento(TElemento_Encadeado<int>* elemento) {
    return to_string(elemento->dado);
}

template<typename T>
void imprimir_lista_encadeada(TLista_Encadeada<T> lista){
    
   for (TElemento_Encadeado<T>* nav= lista.inicio;
      nav!= nullptr; nav= nav->proximo){
       cout << imprimir_elemento(nav);
   }

 }
