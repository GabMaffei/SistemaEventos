#pragma once

#include <string>

using namespace std;

//Lista Estática Genérica
template<typename T>
struct TElemento_Estatico { //Ou container
    T dado;
};

template<typename T, int MAX>
struct TLista_Estatica {
    TElemento_Estatico<T> elementos[MAX];
    int quantidade;
};

template<typename T, int MAX>
void inicializar_lista_estatica(TLista_Estatica<T, MAX>& lista) {
    lista.quantidade = 0;
}
//--------
//Inserir
template<typename T, int MAX>
void inserir_fim_lista_estatica(TLista_Estatica<T, MAX>& lista, T dado_para_inserir) {
    if (lista.quantidade >= MAX) {
        throw "LIST OVERFLOW";
    }
    else {
        TElemento_Estatico<T> container; //Precisa acomodar como container, pois a lista espera esse tipo de dado
        container.dado = dado_para_inserir;
        lista.elementos[lista.quantidade] = container;
        lista.quantidade++;
    }
}

template<typename T, int MAX>
void inserir_posicao_lista_estatica(TLista_Estatica<T, MAX>& lista, T dado_para_inserir, int posicao) {

    if (lista.quantidade >= MAX) {
        throw "LIST OVERFLOW";
    }
    else if (posicao < 0 || posicao > lista.quantidade) {
        throw "INVALID INDEX";
    }
    else {
        for (int i = lista.quantidade; i > posicao; i--) {
            lista.elementos[i].dado = lista.elementos[i - 1].dado;
        }
        TElemento_Estatico<T> container; //Precisa acomodar como container, pois a lista espera esse tipo de dado
        container.dado = dado_para_inserir;
        lista.elementos[posicao] = container;
        lista.quantidade++;
    }
}

template<typename T, int MAX>
void inserir_inicio_lista_estatica(TLista_Estatica<T, MAX>& lista, T dado_para_inserir) {
    inserir_posicao_lista_estatica(lista, dado_para_inserir, 0);
}
//--------
//Remover
template<typename T, int MAX>
void remover_fim_lista_estatica(TLista_Estatica<T, MAX>& lista) {
    if (lista.quantidade == 0) {
        throw "LIST UNDERFLOW";
    }
    else {
        lista.quantidade--;
    }
}

template<typename T, int MAX>
void remover_posicao_lista_estatica(TLista_Estatica<T, MAX>& lista, int posicao) {

    if (lista.quantidade <= 0) {
        throw "LIST UNDERFLOW";
    }
    else if (posicao < 0 || posicao > lista.quantidade) {
        throw "INVALID INDEX";
    }
    else {
        for (int i = posicao; i < lista.quantidade; i++) {
            lista.elementos[i].dado = lista.elementos[i + 1].dado;
        }
        lista.quantidade--;
    }
}

template<typename T, int MAX>
void remover_inicio_lista_estatica(TLista_Estatica<T, MAX>& lista) {
    remover_posicao_lista_estatica(lista, 0);
}
//--------
//Obter/Busca
template<typename T, int MAX>
T& obter_item_lista_estatica(TLista_Estatica<T, MAX>& lista, int posicao) {
    if (posicao < 0 || posicao >= lista.quantidade) {
        throw "INVALID INDEX";
    }
    else {
        return lista.elementos[posicao].dado;
    }
}

template<typename T, int MAX>
int obter_posicao_lista_estatica(TLista_Estatica<T, MAX>& lista, T dado_para_buscar) {
    for (int i = 0; i < lista.quantidade; i++) {
        if (lista.elementos[i].dado == dado_para_buscar) {
            return i;
        }
    }
    return -1;
}

template<typename T, int MAX>
bool obter_existencia_lista_estatica(TLista_Estatica<T, MAX>& lista, T dado_para_buscar) {
    if (obter_posicao_lista_estatica(lista, dado_para_buscar) == -1) {
        return false;
    }
    else {
        return true;
    }
}

//--------
//Imprimir

//template<typename T>
//string imprimir_elemento(T elemento) {
//    if (is_same<T, int>::value) {
//        return to_string(elemento);
//    }
//    return "";
//}

string imprimir_elemento(TElemento_Estatico<int> elemento) {
    return to_string(elemento.dado);
}

template<typename T, int MAX>
void imprimir_lista_estatica(TLista_Estatica<T, MAX>& lista) {
    for (int i = 0; i < lista.quantidade; i++) {
        cout << "Elemento [" << i << "]: " << imprimir_elemento(lista.elementos[i]) << endl;
    }
}