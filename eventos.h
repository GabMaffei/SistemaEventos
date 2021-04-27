#pragma once

#include <iostream>
#include <stdlib.h>
#include <time.h> 
#include <Windows.h>
#include "tads_lista.h"
#include "tads_lista_encadeada.h"
#include "tads_lista_duplamente_encadeada.h"

using namespace std;

//Data
struct TData {
    int dia;
    int mes;
    int ano;
};

TData cria_data(int dia, int mes, int ano) {
    if (dia < 0 || mes < 0 || ano < 0 || dia > 31 || mes > 12) {
        throw "DATA INVALIDA!";
    }
    TData data;
    data.ano = ano;
    data.mes = mes;
    data.dia = dia;
    return data;
}

string imprimir_dado(TData dado) {
    return (to_string(dado.dia) + "/" 
        + to_string(dado.mes) + "/" 
        + to_string(dado.ano));
}

//Horario
struct THorario {
    int hora;
    int minuto;
};

string imprimir_dado(THorario dado) {
    if (dado.hora < 10 && dado.minuto < 10) {
        return ("0" + to_string(dado.hora) + ":"
            + "0" + to_string(dado.minuto));
    }
    else if (dado.hora < 10) {
        return (" " + to_string(dado.hora) + ":"
            + to_string(dado.minuto));
    }
    else if (dado.minuto < 10) {
        return (to_string(dado.hora) + ":"
            + "0" + to_string(dado.minuto));
    }
    else {
        return (to_string(dado.hora) + ":"
            + to_string(dado.minuto));
    }
}

THorario cria_horario(int hora, int minuto) {

    if (hora < 0 || minuto < 0 || hora > 23 || minuto > 59) {
        throw "HORARIO INVALIDO!";
    };
    THorario horario;
    horario.hora = hora;
    horario.minuto = minuto;
    return horario;
}

//TPessoa
struct TPessoa {
    int id;
    string nome;
    double cpf;
};

string imprimir_elemento(TElemento_Encadeado<TPessoa>* evento) {
    return ("Nome: " + evento->dado.nome + " " +
        "CPF: " + to_string(evento->dado.cpf) + " " +
        "ID: " + to_string(evento->dado.id)) + "\n";
};

string imprimir_dado(TPessoa dado) {
    return ("Nome: " + dado.nome + " " +
        "CPF: " + to_string(dado.cpf) + " " +
        "ID: " + to_string(dado.id)) + "\n";
};

TPessoa cria_pessoa(string nome = "nome", double cpf = 11111111111) {
    TPessoa pessoa;
    pessoa.id = rand();
    pessoa.nome = nome;
    pessoa.cpf = cpf;
    return pessoa;
};

TPessoa cria_pessoa(int id, string nome = "nome", double cpf = 11111111111) {
    TPessoa pessoa;
    pessoa.id = id;
    pessoa.nome = nome;
    pessoa.cpf = cpf;
    return pessoa;
};

bool compara_igualdade(TPessoa dadoUm, TPessoa dadoDois) {
    if (dadoUm.id == dadoDois.id) {
        return true;
    }
    else {
        return false;
    }
};

//Subevento
struct TSubevento {
    //Cabeçalho:
    int id; //Identificador único randômico
    int numero;  //Identificador, baseado no último criado
    string titulo; //Nome do evento
    //Dados:
    TData data_inicio; //Data de inicio do evento
    THorario horario_inicio; //Hora de inicio do evento
    TData data_final; //Data de final do evento
    THorario horario_final; //Hora de final do evento
    int quantidade_maxima; //Número máximo de inscritos
    int quantidade_espera; //Número máximo na lista de espera (10% da cap. máx)
    TLista_Encadeada<TPessoa> lista_inscritos;
    TLista_Encadeada<TPessoa> lista_espera;
};

string imprimir_elemento(TElemento_Estatico<TSubevento> evento) {
    return (string("Imprimindo subevento - Subevento: ")
        + to_string(evento.dado.numero) + " - Titulo: "
        + (evento.dado.titulo) + "\nData Inicio: "
        + imprimir_dado(evento.dado.data_inicio) + " - Data Final: "
        + imprimir_dado(evento.dado.data_final) + "\nHorario Inicio: "
        + imprimir_dado(evento.dado.horario_inicio) + " - Horario Final: "
        + imprimir_dado(evento.dado.horario_final) + "\nQuantidade maxima: "
        + to_string(evento.dado.quantidade_maxima) + " - Quantidade maxima lista de espera: "
        + to_string(evento.dado.quantidade_espera) + "\nQuantidade lista de inscritos: "
        + to_string(conta_lista_encadeada(evento.dado.lista_inscritos)) + " - Quantidade lista de espera: "
        + to_string(conta_lista_encadeada(evento.dado.lista_espera)) + "\n");
};

string imprimir_dado(TSubevento dado) {
    return (string("Imprimindo evento - Evento: ")
        + to_string(dado.numero) + " - Titulo: "
        + (dado.titulo) + "\nData Inicio: "
        + imprimir_dado(dado.data_inicio) + " - Data Final: "
        + imprimir_dado(dado.data_final) + "\nHorario Inicio: "
        + imprimir_dado(dado.horario_inicio) + " - Horario Final: "
        + imprimir_dado(dado.horario_final) + "\nQuantidade maxima: "
        + to_string(dado.quantidade_maxima) + " - Quantidade maxima lista de espera: "
        + to_string(dado.quantidade_espera) + "\nQuantidade lista de inscritos: "
        + to_string(conta_lista_encadeada(dado.lista_inscritos)) + " - Quantidade lista de espera: "
        + to_string(conta_lista_encadeada(dado.lista_espera)) + "\n");
};

bool compara_igualdade(TSubevento dadoUm, TSubevento dadoDois) {
    if (dadoUm.id == dadoDois.id) {
        return true;
    }
    else if (dadoUm.numero == dadoDois.numero) {
        return true;
    }
    else {
        return false;
    }
};

template<typename T, int MAX>
TSubevento criar_subevento(TLista_Estatica<T, MAX> lista, string titulo,
    TData data_inicio, TData data_final, THorario horario_inicio, THorario horario_final,
    int quantidade_maxima) {
    TSubevento subevento;
    //Cabeçalho:
    subevento.id = rand(); //Identificador único randômico
    subevento.numero = lista.quantidade + 1;  //Identificador, baseado no último criado
    subevento.titulo = titulo; //Nome do evento
    //Dados:
    subevento.data_inicio = data_inicio; //Data de inicio do evento
    subevento.horario_inicio = horario_inicio; //Hora de inicio do evento
    subevento.data_final = data_final; //Data de final do evento
    subevento.horario_final = horario_final; //Hora de final do evento
    subevento.quantidade_maxima = quantidade_maxima; //Número máximo de inscritos
    subevento.quantidade_espera = quantidade_maxima * 0.1; //Número máximo na lista de espera (10% da cap. máx)
    //Listas:
    inicializar_lista_encadeada(subevento.lista_inscritos);
    inicializar_lista_encadeada(subevento.lista_espera);
    return subevento;
};

//Evento
struct TEvento_Novo {
    //Cabeçalho:
    int id; //Identificador único randômico
    int numero;  //Identificador, baseado no último criado
    string titulo; //Nome do evento
    //Dados:
    TData data_inicio; //Data de inicio do evento
    THorario horario_inicio; //Hora de inicio do evento
    TData data_final; //Data de final do evento
    THorario horario_final; //Hora de final do evento
    int quantidade_maxima; //Número máximo de inscritos
    int quantidade_espera; //Número máximo na lista de espera (10% da cap. máx)
    //Listas:
    TLista_Estatica<TSubevento, 10> lista_subeventos;
    TLista_Encadeada<TPessoa> lista_inscritos;
    TLista_Encadeada<TPessoa> lista_espera;
};

string imprimir_elemento(TElemento_Duplamente_Encadeado<TEvento_Novo>* evento) {
    return (string("Imprimindo evento - Evento: ")
        + to_string(evento->dado.numero) + " - Titulo: "
        + (evento->dado.titulo) + "\nData Inicio: "
        + imprimir_dado(evento->dado.data_inicio) + " - Data Final: "
        + imprimir_dado(evento->dado.data_final) + "\nHorario Inicio: "
        + imprimir_dado(evento->dado.horario_inicio) + " - Horario Final: "
        + imprimir_dado(evento->dado.horario_final) + "\nQuantidade maxima: " 
        + to_string(evento->dado.quantidade_maxima) + " - Quantidade maxima lista de espera: "
        + to_string(evento->dado.quantidade_espera) + "\nQuantidade lista de inscritos: "
        + to_string(conta_lista_encadeada(evento->dado.lista_inscritos)) + " - Quantidade lista de espera: "
        + to_string(conta_lista_encadeada(evento->dado.lista_espera)) + "\n"
        /*+ imprimir_lista_estatica(evento->dado.lista_subeventos) +
        + imprimir_lista_encadeada(evento->dado.lista_inscritos)
        + imprimir_lista_estatica(evento->dado.lista_espera)*/);
};

string imprimir_dado(TEvento_Novo dado) {
    return (string("Evento: ")
        + to_string(dado.numero) + " - Titulo: "
        + (dado.titulo) + "\nData Inicio: "
        + imprimir_dado(dado.data_inicio) + " - Data Final: "
        + imprimir_dado(dado.data_final) + "\nHorario Inicio: "
        + imprimir_dado(dado.horario_inicio) + " - Horario Final: "
        + imprimir_dado(dado.horario_final) + "\nQuantidade maxima: "
        + to_string(dado.quantidade_maxima) + " - Quantidade maxima lista de espera: "
        + to_string(dado.quantidade_espera) + "\nQuantidade lista de inscritos: "
        + to_string(conta_lista_encadeada(dado.lista_inscritos)) + " - Quantidade lista de espera: "
        + to_string(conta_lista_encadeada(dado.lista_espera)) + "\n");
};

bool compara_igualdade(TEvento_Novo dadoUm, TEvento_Novo dadoDois) {
    if (dadoUm.id == dadoDois.id) {
        return true;
    }
    else if (dadoUm.numero == dadoDois.numero) {
        return true;
    }
    else {
        return false;
    }
}

template<typename T>
TEvento_Novo criar_evento(TLista_Duplamente_Encadeada<T> lista, string titulo,
    TData data_inicio, TData data_final, THorario horario_inicio, THorario horario_final,
    int quantidade_maxima){
    //Verificação de entrada:
    try {
        if (quantidade_maxima < 0) {
            throw "QUANTIDADE MAXIMA INVALIDA!";
        };
    }
    catch (const char* msg){
        cout << msg << endl;
    }
    TEvento_Novo evento;
    //Cabeçalho:
    evento.id = rand(); //Identificador único randômico
    evento.numero = conta_lista_duplamente_encadeada(lista) + 1;  //Identificador, baseado no último criado
    evento.titulo =  titulo; //Nome do evento
    //Dados:
    evento.data_inicio = data_inicio; //Data de inicio do evento
    evento.horario_inicio = horario_inicio; //Hora de inicio do evento
    evento.data_final = data_final; //Data de final do evento
    evento.horario_final = horario_final; //Hora de final do evento
    evento.quantidade_maxima = quantidade_maxima; //Número máximo de inscritos
    evento.quantidade_espera = quantidade_maxima * 0.1; //Número máximo na lista de espera (10% da cap. máx)
    //Listas:
    inicializar_lista_estatica(evento.lista_subeventos);
    inicializar_lista_encadeada(evento.lista_inscritos);
    inicializar_lista_encadeada(evento.lista_espera);
    return evento;
};

//Comandos do Administrador

//Admin - Eventos
void admin_adicionar_novo_evento(TLista_Duplamente_Encadeada<TEvento_Novo>& lista, string titulo, TData data_inicio, TData data_final, 
    THorario horario_inicio, THorario horario_final, int quantidade_maxima) {
    try {
        inserir_final_lista_duplamente_encadeada(lista, criar_evento(lista, titulo, data_inicio, data_final,
            horario_inicio, horario_final, quantidade_maxima));
    }
    catch (const char* msg) {
        cout << msg << endl;
    }
};

//Admin - Imprimir
void admin_imprimir_evento(TLista_Duplamente_Encadeada<TEvento_Novo>& lista, int posicao_evento) {
    TEvento_Novo* evento = &obter_item_lista_duplamente_encadeada(lista, posicao_evento);
    cout << imprimir_dado(*evento);
};

//Bases para o admin_tentar
void admin_adicionar_novo_inscrito(TEvento_Novo& evento, TPessoa pessoa) {
    //evento.quantidade_maxima;
    //evento.quantidade_espera;
    int quantidade_atual_inscritos = conta_lista_encadeada(evento.lista_inscritos);
    //int quantidade_atual_espera = conta_lista_encadeada(evento.lista_espera);

    if (quantidade_atual_inscritos >= evento.quantidade_maxima) {
        throw "EVENTO LOTADO";
    }
    else if ( obter_existencia_lista_encadeada(evento.lista_inscritos, pessoa) ){
        throw "JA ESTA INSCRITO";
    }
    else {
        try {
            inserir_final_lista_encadeada(evento.lista_inscritos, pessoa);
        }
        catch (const char* msg) {
            cout << msg << endl;
        }
    }
};

void admin_adicionar_novo_inscrito(TLista_Duplamente_Encadeada<TEvento_Novo>& lista, int posicao_evento,
    TPessoa pessoa) {
    //evento.quantidade_maxima;
    //evento.quantidade_espera;
    int quantidade_atual_inscritos = conta_lista_encadeada(obter_item_lista_duplamente_encadeada(lista, posicao_evento).lista_inscritos);
    //int quantidade_atual_espera = conta_lista_encadeada(evento.lista_espera);

    if (quantidade_atual_inscritos >= obter_item_lista_duplamente_encadeada(lista, posicao_evento).quantidade_maxima) {
        throw "EVENTO LOTADO";
    }
    else if ( obter_existencia_lista_encadeada(obter_item_lista_duplamente_encadeada(lista, posicao_evento).lista_inscritos, pessoa)) {
        throw "JA ESTA INSCRITO";
    }
    else {
        try {
            inserir_final_lista_encadeada(obter_item_lista_duplamente_encadeada(lista, posicao_evento).lista_inscritos, pessoa);
        }
        catch (const char* msg) {
            cout << msg << endl;
        }
    }
};

void admin_adicionar_novo_espera(TEvento_Novo& evento, TPessoa pessoa) {
    //evento.quantidade_maxima;
    //evento.quantidade_espera;
    //int quantidade_atual_inscritos = conta_lista_encadeada(evento.lista_inscritos);
    int quantidade_atual_espera = conta_lista_encadeada(evento.lista_espera);

    if (quantidade_atual_espera >= evento.quantidade_espera) {
        throw "ESPERA LOTADA";
    }
    else if ( obter_existencia_lista_encadeada(evento.lista_inscritos, pessoa)) {
        throw "JA ESTA INSCRITO NA ESPERA";
    }
    else {
        try {
            inserir_final_lista_encadeada(evento.lista_espera, pessoa);
        }
        catch (const char* msg) {
            cout << msg << endl;
        }
    }
};

void admin_adicionar_novo_espera(TLista_Duplamente_Encadeada<TEvento_Novo>& lista, int posicao_evento,
    TPessoa pessoa) {
    //evento.quantidade_maxima;
    //evento.quantidade_espera;
    //int quantidade_atual_inscritos = conta_lista_encadeada(obter_item_lista_duplamente_encadeada(lista, posicao_evento).lista_inscritos);
    int quantidade_atual_espera = conta_lista_encadeada(obter_item_lista_duplamente_encadeada(lista, posicao_evento).lista_espera);

    if (quantidade_atual_espera >= obter_item_lista_duplamente_encadeada(lista, posicao_evento).quantidade_espera) {
        throw "ESPERA LOTADA";
    }
    else if (obter_existencia_lista_encadeada(obter_item_lista_duplamente_encadeada(lista, posicao_evento).lista_espera, pessoa)) {
        throw "JA ESTA INSCRITO NA ESPERA";
    }
    else {
        try {
            inserir_final_lista_encadeada(obter_item_lista_duplamente_encadeada(lista, posicao_evento).lista_espera, pessoa);
        }
        catch (const char* msg) {
            cout << msg << endl;
        }
    }
};

//Importante
void admin_tentar_adicionar_novo_inscrito(TLista_Duplamente_Encadeada<TEvento_Novo>& lista, int posicao_evento,
    TPessoa pessoa){
    try {
         admin_adicionar_novo_inscrito(lista, posicao_evento, pessoa);
    }
    catch (const char* msg) {
        cout << msg << endl;
        if (msg == "EVENTO LOTADO") {
            bool resposta = false;
            string respostaString;
            cout << "O evento " << obter_item_lista_duplamente_encadeada(lista, posicao_evento).titulo << " encontra-se lotado, gostaria de se inscrever na lista de espera?  (y/n)" << endl;
            cin >> respostaString;
            if (respostaString == "sim" || respostaString == "SIM" || respostaString == "y"
                || respostaString == "YES" || respostaString == "1") {
                resposta = true;
            }
            if (resposta) {
                try {
                    admin_adicionar_novo_espera(lista, posicao_evento, pessoa);
                }
                catch (const char* msg) {
                    cout << msg << endl;
                }
            }
        }
    };
} //Combinação de adicionar novo inscrito e espera

//Admin - Subeventos
void admin_adicionar_novo_subevento(TLista_Duplamente_Encadeada<TEvento_Novo>& lista, int posicao_evento,
    string titulo, TData data_inicio, TData data_final,
    THorario horario_inicio, THorario horario_final, int quantidade_maxima) {
    try {
        inserir_fim_lista_estatica((obter_item_lista_duplamente_encadeada(lista, posicao_evento).lista_subeventos),
            criar_subevento(obter_item_lista_duplamente_encadeada(lista, posicao_evento).lista_subeventos,
                titulo, data_inicio, data_final,
                horario_inicio, horario_final, quantidade_maxima));
    }
    catch (const char* msg) {
        cout << msg << endl;
    }
}

void admin_adicionar_novo_subevento(TEvento_Novo& evento,
    string titulo, TData data_inicio, TData data_final,
    THorario horario_inicio, THorario horario_final, int quantidade_maxima) {
    try {
        inserir_fim_lista_estatica(evento.lista_subeventos,
            criar_subevento(evento.lista_subeventos,
                titulo, data_inicio, data_final,
                horario_inicio, horario_final, quantidade_maxima));
    }
    catch (const char* msg) {
        cout << msg << endl;
    }
}

void admin_imprimir_subevento(TLista_Duplamente_Encadeada<TEvento_Novo>& lista, int posicao_evento, int posicao_subevento) {
    TEvento_Novo* evento = &obter_item_lista_duplamente_encadeada(lista, posicao_evento);
    TSubevento* subevento = &obter_item_lista_estatica(evento->lista_subeventos, posicao_subevento);
    cout << imprimir_dado(*subevento);
};

//Bases para o admin_tentar
void admin_adicionar_novo_inscrito(TEvento_Novo& evento, TSubevento& subevento, TPessoa pessoa) {
    //subevento.quantidade_maxima;
    //subevento.quantidade_espera;
    int quantidade_atual_inscritos = conta_lista_encadeada(subevento.lista_inscritos);
    //int quantidade_atual_espera = conta_lista_encadeada(evento.lista_espera);

    if (quantidade_atual_inscritos >= subevento.quantidade_maxima) {
        throw "SUBEVENTO LOTADO";
    }
    else if ( !(obter_existencia_lista_encadeada (evento.lista_inscritos, pessoa) ) ) {
        throw "NAO INSCRITO NO EVENTO PRINCIPAL";
    }
    else {
        try {
            inserir_final_lista_encadeada(evento.lista_inscritos, pessoa);
        }
        catch (const char* msg) {
            cout << msg << endl;
        }
    }
};

void admin_adicionar_novo_inscrito(TLista_Duplamente_Encadeada<TEvento_Novo>& lista,
    int posicao_evento, int posicao_subevento, TPessoa pessoa) {
    //evento.quantidade_maxima;
    //evento.quantidade_espera;
    TEvento_Novo* evento = &obter_item_lista_duplamente_encadeada(lista, posicao_evento);
    TSubevento* subevento = &obter_item_lista_estatica(evento->lista_subeventos, posicao_subevento);
    //obter_item_lista_estatica(obter_item_lista_duplamente_encadeada(lista, posicao_evento).lista_subeventos, posicao_subevento);
    int quantidade_atual_inscritos = conta_lista_encadeada(subevento->lista_inscritos);
    //int quantidade_atual_espera = conta_lista_encadeada(evento.lista_espera);

    if (quantidade_atual_inscritos >= subevento->quantidade_maxima) {
        throw "SUBEVENTO LOTADO";
    }
    else if (!(obter_existencia_lista_encadeada(evento->lista_inscritos, pessoa))) {
        throw "NAO INSCRITO NO EVENTO PRINCIPAL";
    }
    else {
        try {
            inserir_final_lista_encadeada(subevento->lista_inscritos, pessoa);
        }
        catch (const char* msg) {
            cout << msg << endl;
        }
    }
};

void admin_adicionar_novo_espera(TEvento_Novo& evento, TSubevento& subevento, TPessoa pessoa) {
    //evento.quantidade_maxima;
    //evento.quantidade_espera;
    //int quantidade_atual_inscritos = conta_lista_encadeada(evento.lista_inscritos);
    int quantidade_atual_espera = conta_lista_encadeada(subevento.lista_espera);

    if (quantidade_atual_espera >= subevento.quantidade_espera) {
        throw "ESPERA LOTADA";
    }
    else if (!(obter_existencia_lista_encadeada(evento.lista_inscritos, pessoa))) {
        throw "NAO INSCRITO NO EVENTO PRINCIPAL";
    }
    else {
        try {
            inserir_final_lista_encadeada(subevento.lista_espera, pessoa);
        }
        catch (const char* msg) {
            cout << msg << endl;
        }
    }
};

void admin_adicionar_novo_espera(TLista_Duplamente_Encadeada<TEvento_Novo>& lista,
    int posicao_evento, int posicao_subevento,
    TPessoa pessoa) {
    //evento.quantidade_maxima;
    //evento.quantidade_espera;
    TEvento_Novo* evento = &obter_item_lista_duplamente_encadeada(lista, posicao_evento);
    TSubevento* subevento = &obter_item_lista_estatica(evento->lista_subeventos, posicao_subevento);
    //int quantidade_atual_inscritos = conta_lista_encadeada(obter_item_lista_duplamente_encadeada(lista, posicao_evento).lista_inscritos);
    int quantidade_atual_espera = conta_lista_encadeada(subevento->lista_espera);

    if (quantidade_atual_espera >= subevento->quantidade_espera) {
        throw "ESPERA LOTADA";
    }
    else if (!(obter_existencia_lista_encadeada(evento->lista_inscritos, pessoa))) {
        throw "NAO INSCRITO NO EVENTO PRINCIPAL";
    }
    else {
        try {
            inserir_final_lista_encadeada(subevento->lista_espera, pessoa);
        }
        catch (const char* msg) {
            cout << msg << endl;
        }
    }
};

//Importante
void admin_tentar_adicionar_novo_inscrito(TLista_Duplamente_Encadeada<TEvento_Novo>& lista, 
    int posicao_evento, int posicao_subevento, TPessoa pessoa) {
    TEvento_Novo* evento = &obter_item_lista_duplamente_encadeada(lista, posicao_evento);
    TSubevento* subevento = &obter_item_lista_estatica(evento->lista_subeventos, posicao_subevento);
    try {
        admin_adicionar_novo_inscrito(lista, posicao_evento, posicao_subevento, pessoa);
    }
    catch (const char* msg) {
        cout << msg << endl;
        if (msg == "SUBEVENTO LOTADO") {
            bool resposta = false;
            string respostaString;
            cout << "O subevento " << subevento->titulo << " encontra-se lotado, gostaria de se inscrever na lista de espera?  (y/n)" << endl;
            cin >> respostaString;
            if (respostaString == "sim" || respostaString == "SIM" || respostaString == "y"
                || respostaString == "YES" || respostaString == "1") {
                resposta = true;
            }
            if (resposta) {
                try {
                    admin_adicionar_novo_espera(lista, posicao_evento, posicao_subevento, pessoa);
                }
                catch (const char* msg) {
                    cout << msg << endl;
                }
            }
        }
        else if (msg == "NAO INSCRITO NO EVENTO PRINCIPAL") {
            bool resposta = false;
            string respostaString;
            cout << "Voce nao esta inscrito no evento principal " << evento->titulo << ", gostaria de se inscrever?  (y/n)" << endl;
            cin >> respostaString;
            if (respostaString == "sim" || respostaString == "SIM" || respostaString == "y"
                || respostaString == "YES" || respostaString == "1") {
                resposta = true;
            }
            if (resposta) {
                try {
                    admin_tentar_adicionar_novo_inscrito(lista, posicao_evento, pessoa);
                    admin_tentar_adicionar_novo_inscrito(lista, posicao_evento, posicao_subevento, pessoa);
                }
                catch (const char* msg) {
                    cout << msg << endl;
                }
            }
        }
    };
}; //Combinação de adicionar novo inscrito e espera

//Admin - Excluir Espera/Inscritos - Subeventos

void admin_remover_espera(TLista_Duplamente_Encadeada<TEvento_Novo>& lista,
    int posicao_evento, int posicao_subevento,
    TPessoa pessoa) {
    TEvento_Novo* evento = &obter_item_lista_duplamente_encadeada(lista, posicao_evento);
    TSubevento* subevento = &obter_item_lista_estatica(evento->lista_subeventos, posicao_subevento);
    int posicao_pessoa = obter_posicao_lista_encadeada(subevento->lista_espera, pessoa);
    if (conta_lista_encadeada(subevento->lista_espera) == 0) {
        throw "LIST UNDERFLOW";
    }
    else if (!(obter_existencia_lista_encadeada(subevento->lista_espera, pessoa))) {
        throw "NAO ESTA NA LISTA DE ESPERA";
    }
    else {
        remover_posicao_lista_encadeada(subevento->lista_espera, posicao_pessoa);
    }
}

void admin_remover_espera(TLista_Duplamente_Encadeada<TEvento_Novo>& lista,
    int posicao_evento, int posicao_subevento,
    int posicao_pessoa) {
    TEvento_Novo* evento = &obter_item_lista_duplamente_encadeada(lista, posicao_evento);
    TSubevento* subevento = &obter_item_lista_estatica(evento->lista_subeventos, posicao_subevento);
    TPessoa* pessoa = &obter_item_lista_encadeada(subevento->lista_espera, posicao_pessoa);
    int tamanho_espera = conta_lista_encadeada(subevento->lista_espera);
    if (tamanho_espera == 0) {
        throw "LIST UNDERFLOW";
    }
    else if (tamanho_espera < posicao_pessoa) {
        throw "INVALID INDEX";
    }
    else {
        remover_posicao_lista_encadeada(subevento->lista_espera, posicao_pessoa);
    }
}

void admin_remover_inscrito(TLista_Duplamente_Encadeada<TEvento_Novo>& lista,
    int posicao_evento, int posicao_subevento,
    TPessoa pessoa) {
    TEvento_Novo* evento = &obter_item_lista_duplamente_encadeada(lista, posicao_evento);
    TSubevento* subevento = &obter_item_lista_estatica(evento->lista_subeventos, posicao_subevento);
    int posicao_pessoa = obter_posicao_lista_encadeada(subevento->lista_inscritos, pessoa);
    if (conta_lista_encadeada(subevento->lista_inscritos) == 0) {
        throw "LIST UNDERFLOW";
    }
    else if (!(obter_existencia_lista_encadeada(subevento->lista_inscritos, pessoa))) {
        throw "NAO ESTA NA LISTA DE INSCRITOS";
    }
    else {
        remover_posicao_lista_encadeada(subevento->lista_inscritos, posicao_pessoa);
        if (conta_lista_encadeada(subevento->lista_espera) > 0) {
            admin_adicionar_novo_inscrito(lista, posicao_evento, posicao_subevento,
                obter_item_lista_encadeada(subevento->lista_espera, 0));
            admin_remover_espera(lista, posicao_evento, posicao_subevento, 0);
        }
    }
}

void admin_remover_inscrito(TLista_Duplamente_Encadeada<TEvento_Novo>& lista,
    int posicao_evento, int posicao_subevento,
    int posicao_pessoa) {
    TEvento_Novo* evento = &obter_item_lista_duplamente_encadeada(lista, posicao_evento);
    TSubevento* subevento = &obter_item_lista_estatica(evento->lista_subeventos, posicao_subevento);
    TPessoa* pessoa = &obter_item_lista_encadeada(subevento->lista_inscritos, posicao_subevento);
    int tamanho_espera = conta_lista_encadeada(subevento->lista_inscritos);
    if (tamanho_espera == 0) {
        throw "LIST UNDERFLOW";
    }
    else if (tamanho_espera < posicao_pessoa) {
        throw "INVALID INDEX";
    }
    else {
        remover_posicao_lista_encadeada(subevento->lista_inscritos, posicao_pessoa);
        if (conta_lista_encadeada(subevento->lista_espera) > 0) {
            admin_adicionar_novo_inscrito(lista, posicao_evento, posicao_subevento,
                obter_item_lista_encadeada(subevento->lista_espera, 0));
            admin_remover_espera(lista, posicao_evento, posicao_subevento, 0);
        }
    }
}

//Admin - Excluir Espera/Inscritos - Eventos

void admin_remover_espera(TLista_Duplamente_Encadeada<TEvento_Novo>& lista,
    int posicao_evento, TPessoa pessoa) {
    TEvento_Novo* evento = &obter_item_lista_duplamente_encadeada(lista, posicao_evento);
    int posicao_pessoa = obter_posicao_lista_encadeada(evento->lista_espera, pessoa);
    if (conta_lista_encadeada(evento->lista_espera) == 0) {
        throw "LIST UNDERFLOW";
    }
    else if (!(obter_existencia_lista_encadeada(evento->lista_espera, pessoa))) {
        throw "NAO ESTA NA LISTA DE ESPERA";
    }
    else {
        remover_posicao_lista_encadeada(evento->lista_espera, posicao_pessoa);
    }
}

void admin_remover_espera(TLista_Duplamente_Encadeada<TEvento_Novo>& lista,
    int posicao_evento, int posicao_pessoa) {
    TEvento_Novo* evento = &obter_item_lista_duplamente_encadeada(lista, posicao_evento);
    TPessoa* pessoa = &obter_item_lista_encadeada(evento->lista_espera, posicao_pessoa);
    int tamanho_espera = conta_lista_encadeada(evento->lista_espera);
    if (tamanho_espera == 0) {
        throw "LIST UNDERFLOW";
    }
    else if (tamanho_espera < posicao_pessoa) {
        throw "INVALID INDEX";
    }
    else {
        remover_posicao_lista_encadeada(evento->lista_espera, posicao_pessoa);
    }
}

void admin_remover_inscrito(TLista_Duplamente_Encadeada<TEvento_Novo>& lista,
    int posicao_evento, TPessoa pessoa) {
    TEvento_Novo* evento = &obter_item_lista_duplamente_encadeada(lista, posicao_evento);
    int posicao_pessoa = obter_posicao_lista_encadeada(evento->lista_inscritos, pessoa);
    if (conta_lista_encadeada(evento->lista_inscritos) == 0) {
        throw "LIST UNDERFLOW";
    }
    else if (!(obter_existencia_lista_encadeada(evento->lista_inscritos, pessoa))) {
        throw "NAO ESTA NA LISTA DE INSCRITOS";
    }
    else {
        remover_posicao_lista_encadeada(evento->lista_inscritos, posicao_pessoa);
        if (conta_lista_encadeada(evento->lista_espera) > 0) {
            admin_adicionar_novo_inscrito(lista, posicao_evento, posicao_evento,
                obter_item_lista_encadeada(evento->lista_espera, 0));
            admin_remover_espera(lista, posicao_evento, posicao_evento, 0);
        }
    }
}

void admin_remover_inscrito(TLista_Duplamente_Encadeada<TEvento_Novo>& lista,
    int posicao_evento, int posicao_pessoa) {
    TEvento_Novo* evento = &obter_item_lista_duplamente_encadeada(lista, posicao_evento);
    TPessoa* pessoa = &obter_item_lista_encadeada(evento->lista_inscritos, posicao_evento);
    int tamanho_espera = conta_lista_encadeada(evento->lista_inscritos);
    if (tamanho_espera == 0) {
        throw "LIST UNDERFLOW";
    }
    else if (tamanho_espera < posicao_pessoa) {
        throw "INVALID INDEX";
    }
    else {
        remover_posicao_lista_encadeada(evento->lista_inscritos, posicao_pessoa);
        if (conta_lista_encadeada(evento->lista_espera) > 0) {
            admin_adicionar_novo_inscrito(lista, posicao_evento,
                obter_item_lista_encadeada(evento->lista_espera, 0));
            admin_remover_espera(lista, posicao_evento, 0);
        }
    }
}

//Admin - Excluir Subevento

void admin_remover_subevento(TLista_Duplamente_Encadeada<TEvento_Novo>& lista,
    int posicao_evento, int posicao_subevento, bool modo_automatico = false) {
    TEvento_Novo* evento = &obter_item_lista_duplamente_encadeada(lista, posicao_evento);
    TSubevento* subevento = &obter_item_lista_estatica(evento->lista_subeventos, posicao_subevento);
    int quantidade_inscritos = conta_lista_encadeada(subevento->lista_inscritos);
    int quantidade_espera = conta_lista_encadeada(subevento->lista_espera);
    if (quantidade_espera > 0 || quantidade_inscritos > 0) {//Exclusao dos inscritos e confirmacao
        if (!modo_automatico) {
            string resposta_string;
            cout << "Ha inscritos nesse subevento " << subevento->titulo << ". Confirma sua exclusao? (y/n)" << endl;
            cin >> resposta_string;
            if (resposta_string == "n" || resposta_string == "no" || resposta_string == "nao" || resposta_string == "NAO" || resposta_string == "NO") {
                throw "OPERATION ABORTED";
            }
        }
        if (quantidade_espera > 0) {//Exclusao dos inscritos e confirmacao
            for (int i = quantidade_espera - 1; i >= 0; i--) {
                admin_remover_espera(lista, posicao_evento, posicao_subevento, i);
            }
        }
        if (quantidade_inscritos > 0) {
            for (int i = quantidade_inscritos - 1; i >= 0; i--) {
                admin_remover_inscrito(lista, posicao_evento, posicao_subevento, i);
            }
        }
    }
    remover_posicao_lista_estatica(evento->lista_subeventos, posicao_subevento);
}


//Admin - Excluir Evento
void admin_remover_evento(TLista_Duplamente_Encadeada<TEvento_Novo>& lista,
    int posicao_evento, bool modo_automatico = false) {
    TEvento_Novo* evento = &obter_item_lista_duplamente_encadeada(lista, posicao_evento);
    int quantidade_inscritos = conta_lista_encadeada(evento->lista_inscritos);
    int quantidade_espera = conta_lista_encadeada(evento->lista_espera);
    if (quantidade_espera > 0 || quantidade_inscritos > 0) {//Exclusao dos inscritos e confirmacao
        if (!modo_automatico) {
            string resposta_string;
            cout << "Ha inscritos nesse evento " << evento->titulo << ". Confirma sua exclusao? (y/n)" << endl;
            cin >> resposta_string;
            if (resposta_string == "n" || resposta_string == "no" || resposta_string == "nao" || resposta_string == "NAO" || resposta_string == "NO") {
                throw "OPERATION ABORTED";
            }
        }
        if (evento->lista_subeventos.quantidade > 0) {
            for (int i = evento->lista_subeventos.quantidade - 1; i >= 0; i--) {
                admin_remover_subevento(lista, posicao_evento, i);
            }
        }
        if (quantidade_espera > 0) {//Exclusao dos inscritos e confirmacao
            for (int i = quantidade_espera - 1; i >= 0; i--) {
                admin_remover_espera(lista, posicao_evento, i);
            }
        }
        if (quantidade_inscritos > 0) {
            for (int i = quantidade_inscritos - 1; i >= 0; i--) {
                admin_remover_inscrito(lista, posicao_evento, i);
            }
        }
    }
    remover_posicao_lista_duplamente_encadeada(lista, posicao_evento);
}

//UI - Criar Evento

void ui_criar_evento(TLista_Duplamente_Encadeada<TEvento_Novo>& lista) {
    do {
        system("cls");
        cout << "Adicionar evento" << endl;
        cout << "---------------" << endl;
        cout << "Indice " << conta_lista_duplamente_encadeada(lista) << endl;
        cout << endl << "Nome:";
        string nome = "";
        cin >> nome;

        cout << endl << "Dia inicio:";
        int dia_in = 0;
        cin >> dia_in;
        cout << endl << "Mes inicio:";
        int mes_in = 0;
        cin >> mes_in;
        cout << endl << "Ano inicio:";
        int ano_in = 0;
        cin >> ano_in;

        cout << endl << "Dia final:";
        int dia_end = 0;
        cin >> dia_end;
        cout << endl << "Mes final:";
        int mes_end = 0;
        cin >> mes_end;
        cout << endl << "Ano final:";
        int ano_end = 0;
        cin >> ano_end;

        cout << endl << "Hora inicio:";
        int hr_in = 0;
        cin >> hr_in;
        cout << endl << "Minuto inicio:";
        int minuto_in = 0;
        cin >> minuto_in;

        cout << endl << "Hora final:";
        int hr_end = 0;
        cin >> hr_end;
        cout << endl << "Minuto final:";
        int minuto_end = 0;
        cin >> minuto_end;

        cout << endl << "Quantidade maxima de pessoas:";
        int qtd_max = 0;
        cin >> qtd_max;

        cout << endl << "Voce esta feliz com suas escolhas? (y/n)" << endl;

        string opcao = "";

        cin >> opcao;

        if (opcao == "y" || opcao == "yes" || opcao == "YES"
            || opcao == "s" || opcao == "sim" || opcao == "SIM") {
            try {
                TData data_in = cria_data(dia_in, mes_in, ano_in);
                TData data_end = cria_data(dia_end, mes_end, ano_end);
                THorario hora_in = cria_horario(hr_in, minuto_in);
                THorario hora_end = cria_horario(hr_end, minuto_end);
                admin_adicionar_novo_evento(lista, nome,
                    data_in, data_end, hora_in, hora_end, qtd_max);
                break;
            }
            catch (const char* msg) {
                cout << endl << "Ocorreu um erro na entrada de dados: " << msg << endl;
                system("pause");
            }
        }
        else if (opcao == "n" || opcao == "no" || opcao == "NO"
            || opcao == "nao" || opcao == "NAO") {
            cout << endl << "Deseja sair? (y/n)" << endl;

            string opcao = "";

            cin >> opcao;

            if (opcao == "y" || opcao == "yes" || opcao == "YES"
                || opcao == "s" || opcao == "sim" || opcao == "SIM") {
                break;
            }
        }
        else {
            cout << endl << "Opcao invalida" << endl;
            system("pause");

            cout << endl << "Deseja sair? (y/n)" << endl;

            string opcao = "";

            cin >> opcao;

            if (opcao == "y" || opcao == "yes" || opcao == "YES"
                || opcao == "s" || opcao == "sim" || opcao == "SIM") {
                break;
            }
        }
    } while (true);
};

void ui_criar_subevento(TLista_Duplamente_Encadeada<TEvento_Novo>& lista, int posicao_evento) {
    do {
        system("cls");
        TEvento_Novo* evento = &obter_item_lista_duplamente_encadeada(lista, posicao_evento);
        cout << "Adicionar subevento" << endl;
        cout << "---------------" << endl;
        cout << "Indice " << evento->lista_subeventos.quantidade << endl;
        cout << endl << "Nome:";
        string nome = "";
        cin >> nome;

        cout << endl << "Dia inicio:";
        int dia_in = 0;
        cin >> dia_in;
        cout << endl << "Mes inicio:";
        int mes_in = 0;
        cin >> mes_in;
        cout << endl << "Ano inicio:";
        int ano_in = 0;
        cin >> ano_in;

        cout << endl << "Dia final:";
        int dia_end = 0;
        cin >> dia_end;
        cout << endl << "Mes final:";
        int mes_end = 0;
        cin >> mes_end;
        cout << endl << "Ano final:";
        int ano_end = 0;
        cin >> ano_end;

        cout << endl << "Hora inicio:";
        int hr_in = 0;
        cin >> hr_in;
        cout << endl << "Minuto inicio:";
        int minuto_in = 0;
        cin >> minuto_in;

        cout << endl << "Hora final:";
        int hr_end = 0;
        cin >> hr_end;
        cout << endl << "Minuto final:";
        int minuto_end = 0;
        cin >> minuto_end;

        cout << endl << "Quantidade maxima de pessoas:";
        int qtd_max = 0;
        cin >> qtd_max;

        cout << endl << "Voce esta feliz com suas escolhas? (y/n)" << endl;

        string opcao = "";

        cin >> opcao;

        if (opcao == "y" || opcao == "yes" || opcao == "YES"
            || opcao == "s" || opcao == "sim" || opcao == "SIM") {
            try {
                TData data_in = cria_data(dia_in, mes_in, ano_in);
                TData data_end = cria_data(dia_end, mes_end, ano_end);
                THorario hora_in = cria_horario(hr_in, minuto_in);
                THorario hora_end = cria_horario(hr_end, minuto_end);
                admin_adicionar_novo_subevento(lista, posicao_evento, nome,
                    data_in, data_end, hora_in, hora_end, qtd_max);
                break;
            }
            catch (const char* msg) {
                cout << endl << "Ocorreu um erro na entrada de dados: " << msg << endl;
                system("pause");
            }
        }
        else if (opcao == "n" || opcao == "no" || opcao == "NO"
            || opcao == "nao" || opcao == "NAO") {
            cout << endl << "Deseja sair? (y/n)" << endl;

            string opcao = "";

            cin >> opcao;

            if (opcao == "y" || opcao == "yes" || opcao == "YES"
                || opcao == "s" || opcao == "sim" || opcao == "SIM") {
                break;
            }
        }
        else {
            cout << endl << "Opcao invalida" << endl;
            system("pause");

            cout << endl << "Deseja sair? (y/n)" << endl;

            string opcao = "";

            cin >> opcao;

            if (opcao == "y" || opcao == "yes" || opcao == "YES"
                || opcao == "s" || opcao == "sim" || opcao == "SIM") {
                break;
            }
        }
    } while (true);
};

void ui_criar_inscrito(TLista_Duplamente_Encadeada<TEvento_Novo>& lista, int posicao_evento) {
    do {
        system("cls");
        TEvento_Novo* evento = &obter_item_lista_duplamente_encadeada(lista, posicao_evento);
        cout << "Adicionar inscrito" << endl;
        cout << "---------------" << endl;
        cout << "Indice " << conta_lista_encadeada(evento->lista_inscritos) << endl;

        cout << endl << "Nome:";
        string nome = "0";
        cin >> nome;
        if (nome == "0") {
            nome == "nome";
        }

        cout << endl << "CPF:";
        double cpf = 0;
        cin >> cpf;
        if (cpf == 0) {
            cpf == 11111111111;
        }

        cout << endl << "Seus dados estao corretos? (y/n)" << endl;

        string opcao = "";

        cin >> opcao;

        if (opcao == "y" || opcao == "yes" || opcao == "YES"
            || opcao == "s" || opcao == "sim" || opcao == "SIM") {
            try {
                TPessoa pessoa = cria_pessoa(nome, cpf);
                admin_tentar_adicionar_novo_inscrito(lista, posicao_evento, pessoa);
                system("pause");
                break;
            }
            catch (const char* msg) {
                cout << endl << "Ocorreu um erro na entrada de dados: " << msg << endl;
                system("pause");
            }
        }
        else if (opcao == "n" || opcao == "no" || opcao == "NO"
            || opcao == "nao" || opcao == "NAO") {
            cout << endl << "Deseja sair? (y/n)" << endl;

            string opcao = "";

            cin >> opcao;

            if (opcao == "y" || opcao == "yes" || opcao == "YES"
                || opcao == "s" || opcao == "sim" || opcao == "SIM") {
                break;
            }
        }
        else {
            cout << endl << "Opcao invalida" << endl;
            system("pause");

            cout << endl << "Deseja sair? (y/n)" << endl;

            string opcao = "";

            cin >> opcao;

            if (opcao == "y" || opcao == "yes" || opcao == "YES"
                || opcao == "s" || opcao == "sim" || opcao == "SIM") {
                break;
            }
        }
    } while (true);
};

void ui_criar_inscrito(TLista_Duplamente_Encadeada<TEvento_Novo>& lista, int posicao_evento, int posicao_subevento) {
    do {
        system("cls");
        TEvento_Novo* evento = &obter_item_lista_duplamente_encadeada(lista, posicao_evento);
        TSubevento* subevento = &obter_item_lista_estatica(evento->lista_subeventos, posicao_subevento);
        cout << "Adicionar inscrito" << endl;
        cout << "---------------" << endl;
        cout << "Indice " << conta_lista_encadeada(subevento->lista_inscritos) << endl;

        cout << endl << "Nome:";
        string nome = "0";
        cin >> nome;
        if (nome == "0") {
            nome == "nome";
        }

        cout << endl << "CPF:";
        double cpf = 0;
        cin >> cpf;
        if (cpf == 0) {
            cpf == 11111111111;
        }

        cout << endl << "Seus dados estao corretos? (y/n)" << endl;

        string opcao = "";

        cin >> opcao;

        if (opcao == "y" || opcao == "yes" || opcao == "YES"
            || opcao == "s" || opcao == "sim" || opcao == "SIM") {
            try {
                TPessoa pessoa = cria_pessoa(nome, cpf);
                admin_tentar_adicionar_novo_inscrito(lista, posicao_evento, posicao_subevento, pessoa);
                system("pause");
                break;
            }
            catch (const char* msg) {
                cout << endl << "Ocorreu um erro na entrada de dados: " << msg << endl;
                system("pause");
            }
        }
        else if (opcao == "n" || opcao == "no" || opcao == "NO"
            || opcao == "nao" || opcao == "NAO") {
            cout << endl << "Deseja sair? (y/n)" << endl;

            string opcao = "";

            cin >> opcao;

            if (opcao == "y" || opcao == "yes" || opcao == "YES"
                || opcao == "s" || opcao == "sim" || opcao == "SIM") {
                break;
            }
        }
        else {
            cout << endl << "Opcao invalida" << endl;
            system("pause");

            cout << endl << "Deseja sair? (y/n)" << endl;

            string opcao = "";

            cin >> opcao;

            if (opcao == "y" || opcao == "yes" || opcao == "YES"
                || opcao == "s" || opcao == "sim" || opcao == "SIM") {
                break;
            }
        }
    } while (true);
};

void ui_visualizar_eventos(TLista_Duplamente_Encadeada<TEvento_Novo>& lista);
void ui_visualizar_subeventos(TLista_Duplamente_Encadeada<TEvento_Novo>& lista, int posicao_evento);

void ui_visualizar_inscritos(TLista_Duplamente_Encadeada<TEvento_Novo>& lista, int posicao_evento);
void ui_visualizar_inscritos(TLista_Duplamente_Encadeada<TEvento_Novo>& lista, int posicao_evento, int posicao_subevento);
void ui_visualizar_espera(TLista_Duplamente_Encadeada<TEvento_Novo>& lista, int posicao_evento);
void ui_visualizar_espera(TLista_Duplamente_Encadeada<TEvento_Novo>& lista, int posicao_evento, int posicao_subevento);

void ui_visualizar_eventos(TLista_Duplamente_Encadeada<TEvento_Novo>& lista) {
    do {
        system("cls");
        cout << "Eventos" << endl;
        cout << "---------------" << endl;
        if (lista.inicio == nullptr) { //Nao ha eventos
            cout << "Nao ha eventos cadastrados. Gostaria de cadastrar um novo? (y/n)" << endl;
            string opcao = "";
            cin >> opcao;
            if (opcao == "y" || opcao == "yes" || opcao == "YES"
                || opcao == "s" || opcao == "sim" || opcao == "SIM") {
                ui_criar_evento(lista);
            }
            else {
                break;
            }
        }
        else { //Ha eventos
            int i = 0;
            do {
                system("cls");
                cout << "Eventos" << endl;
                cout << "---------------" << endl;
                cout << "Indice " << i << endl;
                admin_imprimir_evento(lista, i);
                cout << endl << "Escolha a opcao desejada:" << endl << endl;
                cout << endl << "1. Adicionar novo evento";

                if (obter_item_lista_duplamente_encadeada(lista, i).lista_subeventos.quantidade == 10) {
                    cout << endl << "2. Adicionar novo subevento (lotado)";
                }
                else {
                    cout << endl << "2. Adicionar novo subevento";
                }

                cout << endl << "3. Visualizar lista de inscritos";

                if (obter_item_lista_duplamente_encadeada(lista, i).lista_subeventos.quantidade == 0) {
                    cout << endl << "4. Visualizar lista de subeventos (vazio)";
                }
                else {
                    cout << endl << "4. Visualizar lista de subeventos";
                }

                cout << endl << "5. Proximo evento";
                cout << endl << "6. Evento anterior";
                cout << endl << "7. Excluir evento";
                cout << endl << endl << endl << "9. Sair" << endl << endl;

                string opcao = "";

                cin >> opcao;
                if (opcao == "1") {
                    ui_criar_evento(lista);
                }
                else if (opcao == "2") {
                    if ((obter_item_lista_duplamente_encadeada(lista, i).lista_subeventos.quantidade == 10)) {
                        cout << endl << "A lista de subeventos esta lotada." << endl;
                    }
                    else {
                        ui_criar_subevento(lista, i);
                    }
                }
                else if (opcao == "3") {
                    ui_visualizar_inscritos(lista, i);
                }
                else if (opcao == "4") {
                    ui_visualizar_subeventos(lista, i);
                }
                else if (opcao == "5") { //Proximo evento
                    try {
                        obter_item_lista_duplamente_encadeada(lista, i + 1);
                        i++;
                    }
                    catch (const char* msg) {
                        i = 0;
                    }
                }
                else if (opcao == "6") { //Evento anterior
                    try {
                        obter_item_lista_duplamente_encadeada(lista, i - 1);
                        i--;
                    }
                    catch (const char* msg) {
                        i = conta_lista_duplamente_encadeada(lista) - 1;
                    }
                }
                else if (opcao == "7") { //Excluir evento
                    try {
                        admin_remover_evento(lista, i);
                        if (i != 0) {
                            i--;
                        }
                        if (lista.inicio == nullptr) {
                            break;
                        }
                    }
                    catch (const char* msg) {
                        cout << endl << "Operacao cancelada: " << msg << endl;
                        system("pause");
                    }
                }
                else if (opcao == "9") { //Sair
                    break;
                }
                else {
                    cout << endl << "Opcao invalida" << endl;
                    system("pause");
                }

            } while (true);
            break;
        }
    } while (true);
};

void ui_visualizar_subeventos(TLista_Duplamente_Encadeada<TEvento_Novo>& lista, int posicao_evento) {
    do {
        system("cls");
        TEvento_Novo* evento = &obter_item_lista_duplamente_encadeada(lista, posicao_evento);
        cout << "Subeventos" << endl;
        cout << "---------------" << endl;
        if (evento->lista_subeventos.quantidade == 0) { //Nao ha subeventos
            cout << "Nao ha subeventos cadastrados. Gostaria de cadastrar um novo? (y/n)" << endl;
            string opcao = "";
            cin >> opcao;
            if (opcao == "y" || opcao == "yes" || opcao == "YES"
                || opcao == "s" || opcao == "sim" || opcao == "SIM") {
                ui_criar_subevento(lista, posicao_evento);
            }
            else {
                break;
            }
        }
        else { //Ha eventos
            int i = 0;
            do {
                system("cls");
                cout << "Subventos" << endl;
                cout << "---------------" << endl;
                cout << "Indice " << i << "/" << (evento->lista_subeventos.quantidade - 1) << endl;
                admin_imprimir_subevento(lista, posicao_evento, i);
                cout << endl << "Escolha a opcao desejada:" << endl << endl;

                if (evento->lista_subeventos.quantidade == 10) {
                    cout << endl << "1. Adicionar novo subevento (lotado)";
                }
                else {
                    cout << endl << "1. Adicionar novo subevento";
                }

                cout << endl << "2. Excluir subevento";


                cout << endl << "3. Visualizar lista de inscritos";

                cout << endl << "4. Proximo subevento";
                cout << endl << "5. Subevento anterior";
                cout << endl << "6. Navegar ate o indice";
                cout << endl << endl << endl << "9. Sair" << endl << endl;

                string opcao = "";

                cin >> opcao;
                if (opcao == "1") {
                    ui_criar_subevento(lista, posicao_evento);
                }
                else if (opcao == "2") {
                    try {
                        admin_remover_subevento(lista, posicao_evento, i);
                        if (i != 0) {
                            i--;
                        }
                        if (evento->lista_subeventos.quantidade == 0) {
                            break;
                        }
                    }
                    catch (const char* msg) {
                        cout << endl << "Operacao cancelada: " << msg << endl;
                        system("pause");
                    }
                }
                else if (opcao == "3") {
                    ui_visualizar_inscritos(lista, posicao_evento, i);
                }
                else if (opcao == "4") { //Proximo subevento
                    try {
                        obter_item_lista_estatica(evento->lista_subeventos, i + 1);
                        i++;
                    }
                    catch (const char* msg) {
                        i = 0;
                    }
                }
                else if (opcao == "5") { //Subevento anterior
                    try {
                        obter_item_lista_estatica(evento->lista_subeventos, i - 1);
                        i--;
                    }
                    catch (const char* msg) {
                        i = evento->lista_subeventos.quantidade - 1;
                    }
                }
                else if (opcao == "6") { //Navegar ate o indice
                    cout << endl << "Digite o indice desejado:";

                    string opcao;
                    cin >> opcao;

                    try {
                        obter_item_lista_estatica(evento->lista_subeventos, stoi(opcao)); //converte string para inteiro
                        i = stoi(opcao);
                    }
                    catch (const char* msg) {
                        cout << endl << "Indice invalido: " << msg << endl;
                        system("pause");
                    }
                }
                else if (opcao == "9") { //Sair
                    break;
                }
                else {
                    cout << endl << "Opcao invalida" << endl;
                    system("pause");
                }

            } while (true);
            break;
        }
        break;
    } while (true);
};

void ui_visualizar_inscritos(TLista_Duplamente_Encadeada<TEvento_Novo>& lista, int posicao_evento) {
    do {
        system("cls");
        TEvento_Novo* evento = &obter_item_lista_duplamente_encadeada(lista, posicao_evento);
        cout << "Inscritos" << endl;
        cout << "---------------" << endl;
        if (evento->lista_inscritos.inicio == nullptr) { //Nao ha eventos
            cout << "Nao ha inscritos cadastrados. Gostaria de cadastrar um novo? (y/n)" << endl;
            string opcao = "";
            cin >> opcao;
            if (opcao == "y" || opcao == "yes" || opcao == "YES"
                || opcao == "s" || opcao == "sim" || opcao == "SIM") {
                ui_criar_inscrito(lista, posicao_evento);
            }
            else {
                break;
            }
        }
        else { //Ha inscritos
            do {
                system("cls");
                cout << "Inscritos" << endl;
                cout << "---------------" << endl;
                cout << "Indice Evento " << posicao_evento << endl;
                imprimir_lista_encadeada(evento->lista_inscritos);
                cout << endl << "Escolha a opcao desejada:" << endl << endl;
                cout << endl << "1. Adicionar novo inscrito";

                cout << endl << "2. Visuzalizar lista de espera";

                cout << endl << "3. Excluir inscrito da posicao";

                cout << endl << endl << endl << "9. Sair" << endl << endl;

                string opcao = "";

                cin >> opcao;
                if (opcao == "1") {
                    ui_criar_inscrito(lista, posicao_evento);
                }
                else if (opcao == "2") {
                    ui_visualizar_espera(lista, posicao_evento);
                }
                else if (opcao == "3") {
                    try {
                        int posicao_pessoa = 0;
                        cout << endl << "Digite a posicao do inscrito a ser removido:";
                        cin >> posicao_pessoa;
                        admin_remover_inscrito(lista, posicao_evento, posicao_pessoa);
                        if (evento->lista_inscritos.inicio == nullptr) {
                            break;
                        }
                    }
                    catch (const char* msg) {
                        cout << endl << "Operacao cancelada: " << msg << endl;
                        system("pause");
                    }
                }
                else if (opcao == "9") { //Sair
                    break;
                }
                else {
                    cout << endl << "Opcao invalida" << endl;
                    system("pause");
                }

            } while (true);
            break;
        }
    } while (true);
};

void ui_visualizar_inscritos(TLista_Duplamente_Encadeada<TEvento_Novo>& lista, int posicao_evento, int posicao_subevento) {
    do {
        system("cls");
        TEvento_Novo* evento = &obter_item_lista_duplamente_encadeada(lista, posicao_evento);
        TSubevento* subevento = &obter_item_lista_estatica(evento->lista_subeventos, posicao_subevento);
        cout << "Inscritos" << endl;
        cout << "---------------" << endl;
        if (subevento->lista_inscritos.inicio == nullptr) { //Nao ha eventos
            cout << "Nao ha inscritos cadastrados. Gostaria de cadastrar um novo? (y/n)" << endl;
            string opcao = "";
            cin >> opcao;
            if (opcao == "y" || opcao == "yes" || opcao == "YES"
                || opcao == "s" || opcao == "sim" || opcao == "SIM") {
                ui_criar_inscrito(lista, posicao_evento, posicao_subevento);
            }
            else {
                break;
            }
        }
        else { //Ha inscritos
            do {
                system("cls");
                cout << "Inscritos" << endl;
                cout << "---------------" << endl;
                cout << "Indice Subevento " << posicao_subevento << endl;
                imprimir_lista_encadeada(subevento->lista_inscritos);
                cout << endl << "Escolha a opcao desejada:" << endl << endl;
                cout << endl << "1. Adicionar novo inscrito";

                cout << endl << "2. Visuzalizar lista de espera";

                cout << endl << "3. Excluir inscrito da posicao";

                cout << endl << endl << endl << "9. Sair" << endl << endl;

                string opcao = "";

                cin >> opcao;
                if (opcao == "1") {
                    ui_criar_inscrito(lista, posicao_evento, posicao_subevento);
                }
                else if (opcao == "2") {
                    ui_visualizar_espera(lista, posicao_evento, posicao_subevento);
                }
                else if (opcao == "3") {
                    try {
                        int posicao_pessoa = 0;
                        cout << endl << "Digite a posicao do inscrito a ser removido:";
                        cin >> posicao_pessoa;
                        admin_remover_inscrito(lista, posicao_evento, posicao_subevento, posicao_pessoa);
                        if (subevento->lista_inscritos.inicio == nullptr) {
                            break;
                        }
                    }
                    catch (const char* msg) {
                        cout << endl << "Operacao cancelada: " << msg << endl;
                        system("pause");
                    }
                }
                else if (opcao == "9") { //Sair
                    break;
                }
                else {
                    cout << endl << "Opcao invalida" << endl;
                    system("pause");
                }

            } while (true);
            break;
        }
    } while (true);
};

void ui_visualizar_espera(TLista_Duplamente_Encadeada<TEvento_Novo>& lista, int posicao_evento) {
    do {
        system("cls");
        TEvento_Novo* evento = &obter_item_lista_duplamente_encadeada(lista, posicao_evento);
        cout << "Espera" << endl;
        cout << "---------------" << endl;
        if (evento->lista_espera.inicio == nullptr) { //Nao ha eventos
            cout << "Nao ha inscritos na lista de espera cadastrados." <<
                endl << "Voce so pode cadastrar um inscrito aqui, quando a lista de espera encontra-se lotada" << endl << endl;
            system("pause");
            break;
        }
        else { //Ha inscritos
            do {
                system("cls");
                cout << "Espera" << endl;
                cout << "---------------" << endl;
                cout << "Indice Evento " << posicao_evento << endl;
                imprimir_lista_encadeada(evento->lista_espera);
                cout << endl << "Escolha a opcao desejada:" << endl << endl;

                cout << endl << "1. Excluir inscrito da lista de espera da posicao";

                cout << endl << endl << endl << "9. Sair" << endl << endl;

                string opcao = "";

                cin >> opcao;
                if (opcao == "1") {
                    try {
                        int posicao_pessoa = 0;
                        cout << endl << "Digite a posicao do inscrito a ser removido da lista de espera:";
                        cin >> posicao_pessoa;
                        admin_remover_espera(lista, posicao_evento, posicao_pessoa);
                        if (evento->lista_espera.inicio == nullptr) {
                            break;
                        }
                    }
                    catch (const char* msg) {
                        cout << endl << "Operacao cancelada: " << msg << endl;
                        system("pause");
                    }
                }
                else if (opcao == "9") { //Sair
                    break;
                }
                else {
                    cout << endl << "Opcao invalida" << endl;
                    system("pause");
                }

            } while (true);
            break;
        }
    } while (true);
};

void ui_visualizar_espera(TLista_Duplamente_Encadeada<TEvento_Novo>& lista, int posicao_evento, int posicao_subevento) {
    do {
        system("cls");
        TEvento_Novo* evento = &obter_item_lista_duplamente_encadeada(lista, posicao_evento);
        TSubevento* subevento = &obter_item_lista_estatica(evento->lista_subeventos, posicao_subevento);
        cout << "Espera" << endl;
        cout << "---------------" << endl;
        if (subevento->lista_espera.inicio == nullptr) { //Nao ha eventos
            cout << "Nao ha inscritos na lista de espera cadastrados." <<
                endl << "Voce so pode cadastrar um inscrito aqui, quando a lista de espera encontra-se lotada" << endl << endl;
            system("pause");
            break;
        }
        else { //Ha inscritos
            do {
                system("cls");
                cout << "Espera" << endl;
                cout << "---------------" << endl;
                cout << "Indice Subevento " << posicao_subevento << endl;
                imprimir_lista_encadeada(subevento->lista_espera);
                cout << endl << "Escolha a opcao desejada:" << endl << endl;

                cout << endl << "1. Excluir inscrito da lista de espera da posicao";

                cout << endl << endl << endl << "9. Sair" << endl << endl;

                string opcao = "";

                cin >> opcao;
                if (opcao == "1") {
                    try {
                        int posicao_pessoa = 0;
                        cout << endl << "Digite a posicao do inscrito a ser removido da lista de espera:";
                        cin >> posicao_pessoa;
                        admin_remover_espera(lista, posicao_evento, posicao_subevento, posicao_pessoa);
                        if (subevento->lista_espera.inicio == nullptr) {
                            break;
                        }
                    }
                    catch (const char* msg) {
                        cout << endl << "Operacao cancelada: " << msg << endl;
                        system("pause");
                    }
                }
                else if (opcao == "9") { //Sair
                    break;
                }
                else {
                    cout << endl << "Opcao invalida" << endl;
                    system("pause");
                }

            } while (true);
            break;
        }
    } while (true);
};