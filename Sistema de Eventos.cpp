// Sistema de Eventos.cpp : Este arquivo contém a função 'main'. A execução do programa começa e termina ali.
//

#include <iostream>
#include <stdlib.h>
#include <time.h> 
#include <string>
#include <Windows.h>
#include "tads_lista.h"
#include "tads_lista_encadeada.h"
#include "tads_lista_duplamente_encadeada.h"
#include "eventos.h"

using namespace std;

int main()
{
    srand(time(NULL));

    TLista_Duplamente_Encadeada<TEvento_Novo> sistema_eventos;
    inicializar_lista_duplamente_encadeada(sistema_eventos);

    admin_adicionar_novo_evento(sistema_eventos, "Show de Rock",
        cria_data(12, 04, 2021), cria_data(12, 04, 2021),
        cria_horario(19, 00), cria_horario(23, 30), 20);

    admin_adicionar_novo_evento(sistema_eventos, "Show de MPB",
        cria_data(17, 05, 2021), cria_data(14, 05, 2021),
        cria_horario(12, 10), cria_horario(22, 30), 6);

    admin_adicionar_novo_evento(sistema_eventos, "Show de Pop",
        cria_data(12, 03, 2021), cria_data(12, 03, 2021),
        cria_horario(14, 00), cria_horario(16, 30), 2);

    for (int i = 0; i < 20; i++) {
        admin_tentar_adicionar_novo_inscrito(sistema_eventos, 0, cria_pessoa(i));
    }

    admin_adicionar_novo_subevento(sistema_eventos, 0,
        "Show do Blink 182",
        cria_data(12, 04, 2021), cria_data(12, 04, 2021),
        cria_horario(19, 00), cria_horario(23, 30), 10);

    admin_adicionar_novo_subevento(obter_item_lista_duplamente_encadeada(sistema_eventos, 1),
        "Show do Lulu Santos",
        cria_data(17, 05, 2021), cria_data(17, 05, 2021),
        cria_horario(12, 10), cria_horario(22, 30), 60);

    admin_adicionar_novo_subevento(sistema_eventos, 2,
        "Show do Maroon 5",
        cria_data(12, 03, 2021), cria_data(12, 03, 2021),
        cria_horario(14, 00), cria_horario(16, 30), 150);


    for (int i = 0; i < 10; i++) {
        admin_tentar_adicionar_novo_inscrito(sistema_eventos, 0, 0, cria_pessoa(i));
    }

    admin_adicionar_novo_espera(sistema_eventos,0, 0, cria_pessoa(11));

    do {
        system("cls");
        cout << "Bem-vindo!" << endl;
        cout << "---------------" << endl;
        cout << "Escolha a opcao desejada:" << endl << endl;
        cout << "1. Modo de administrador do sistema" << endl << endl << endl;
        //cout << "2. Modo de usuario do sistema" << endl << endl << endl;
        cout << "9. Sair" << endl << endl;

        string opcao = "";

        cin >> opcao;

        if (opcao == "1") {
            do {
                system("cls");
                cout << "Gerenciador de eventos" << endl;
                cout << "---------------" << endl;
                cout << "Escolha a opcao desejada:" << endl << endl;
                cout << "1. Ver lista de eventos" << endl << endl << endl;
                cout << "9. Sair" << endl << endl;

                string opcao = "";

                cin >> opcao;

                if (opcao == "1") {
                    ui_visualizar_eventos(sistema_eventos);
                }
                else if (opcao == "9") {
                    break;
                }
                else {
                    cout << endl << "Opcao invalida" << endl;
                    system("pause");
                }
            } while (true);
        }
        /*else if (opcao == "2") {
            
        }*/
        else if (opcao == "9") {
            break;
        }
        else {
            cout << endl << "Opcao invalida" << endl;
            system("pause");
        }
    } while (true);

    return 0;
}
