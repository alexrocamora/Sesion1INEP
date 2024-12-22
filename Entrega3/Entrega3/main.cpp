#include <iostream>
#include "CapaDePresentacio.h"
#include "ConnexioBD.hpp"
#include "TxInfoVisualitzacions.h"

// Funciones para mostrar menús
void mostrarMenuPrincipal() {
    std::cout << "\n=== Menu Principal ===" << std::endl;
    std::cout << "1. Iniciar Sessio" << std::endl;
    std::cout << "2. Registrar Usuari" << std::endl;
    std::cout << "3. Consultes" << std::endl;
    std::cout << "4. Sortir" << std::endl;
    std::cout << "Selecciona una opcio: ";
}

void mostrarMenuSesionIniciada() {
    std::cout << "\n=== Menu Sessio Iniciada ===" << std::endl;
    std::cout << "1. Gestio Usuaris" << std::endl;
    std::cout << "2. Visualitzar" << std::endl;
    std::cout << "3. Consultes" << std::endl;
    std::cout << "4. Tancar Sessio" << std::endl;
    std::cout << "5. Sortir" << std::endl;
    std::cout << "Selecciona una opcio: ";
}

void mostrarMenuConsultas() {
    std::cout << "\n=== Consultes ===" << std::endl;
    std::cout << "1. Properes estrenes" << std::endl;
    std::cout << "2. Ultimes novetats" << std::endl;
    std::cout << "3. Pelicules mes vistes" << std::endl;
    std::cout << "4. Tornar" << std::endl;
    std::cout << "Selecciona una opcio: ";
}

void mostrarMenuVisualizacion() {
    std::cout << "\n=== Visualitzar ===" << std::endl;
    std::cout << "1. Visualitzar pel·lícula" << std::endl;
    std::cout << "2. Visualitzar capítol" << std::endl;
    std::cout << "3. Consulta visualitzacions" << std::endl;
    std::cout << "4. Tornar" << std::endl;
    std::cout << "Selecciona una opcio: ";
}

// Función para gestionar consultas
void gestionarConsultas() {
    int opcionConsulta = 0;
    while (opcionConsulta != 4) {
        mostrarMenuConsultas();
        std::cin >> opcionConsulta;

        switch (opcionConsulta) {
        case 1:
            std::cout << "Properes estrenes: Pendiente de implementar.\n";
            break;
        case 2:
            std::cout << "Ultimes novetats: Pendiente de implementar.\n";
            break;
        case 3:
            std::cout << "Pelicules mes vistes: Pendiente de implementar.\n";
            break;
        case 4:
            std::cout << "Tornant al menu principal...\n";
            break;
        default:
            std::cout << "Opcio no valida. Torna-ho a provar.\n";
        }
    }
}

// Función para consultar visualizaciones usando TxInfoVisualitzacions
void consultarVisualitzacions(const std::string& sobrenomUsuari) {
    TxInfoVisualitzacions txInfo;
    txInfo.crear(sobrenomUsuari);
    txInfo.executar();

    int opcionVisualitzacions = 0;
    while (opcionVisualitzacions != 3) {
        std::cout << "\n=== Consultar Visualitzacions ===" << std::endl;
        std::cout << "1. Visualitzacions de Pelicules" << std::endl;
        std::cout << "2. Visualitzacions de Series" << std::endl;
        std::cout << "3. Tornar" << std::endl;
        std::cout << "Selecciona una opcio: ";
        std::cin >> opcionVisualitzacions;

        switch (opcionVisualitzacions) {
        case 1:
            txInfo.mostrarDetallsPelicules();
            break;
        case 2:
            txInfo.mostrarDetallsSeries();
            break;
        case 3:
            std::cout << "Tornant al menu principal...\n";
            break;
        default:
            std::cout << "Opcio no valida. Torna-ho a provar.\n";
        }
    }
}

// Función para gestionar visualizaciones
void gestionarVisualitzacions(const std::string& sobrenomUsuari) {
    int opcionVisualizar = 0;
    while (opcionVisualizar != 4) {
        mostrarMenuVisualizacion();
        std::cin >> opcionVisualizar;

        switch (opcionVisualizar) {
        case 1:
            std::cout << "Visualitzar pel·lícula: Pendiente de implementar.\n";
            break;
        case 2:
            std::cout << "Visualitzar capítol: Pendiente de implementar.\n";
            break;
        case 3: {
            consultarVisualitzacions(sobrenomUsuari);
            break;
        }
        case 4:
            std::cout << "Tornant al menú principal...\n";
            break;
        default:
            std::cout << "Opció no vàlida. Torna-ho a provar.\n";
        }
    }
}

// Función para gestionar usuarios
void gestionarUsuaris(CapaDePresentacio* capaPresentacio) {
    int opcion = 0;
    while (opcion != 5) {
        std::cout << "\n=== Gestio Usuaris ===" << std::endl;
        std::cout << "1. Consulta usuari" << std::endl;
        std::cout << "2. Modificar usuari" << std::endl;
        std::cout << "3. Modificar contrasenya" << std::endl;
        std::cout << "4. Esborrar usuari" << std::endl;
        std::cout << "5. Tornar" << std::endl;
        std::cout << "Selecciona una opcio: ";
        std::cin >> opcion;

        switch (opcion) {
        case 1:
            capaPresentacio->consultaUsuari();
            break;
        case 2:
            capaPresentacio->modificarUsuari();
            break;
        case 3:
            std::cout << "Modificar contrasenya: Pendiente de implementar.\n";
            break;
        case 4:
            capaPresentacio->esborraUsuari();
            break;
        case 5:
            std::cout << "Tornant al menu de sessio.\n";
            break;
        default:
            std::cout << "Opcio no valida. Torna-ho a provar.\n";
        }
    }
}

// Función principal
int main() {
    try {
        ConnexioBD& connexio = ConnexioBD::getInstance();
        std::cout << "Connexio establerta correctament.\n";

        std::string sobrenomUsuari;
        CapaDePresentacio* capaPresentacio = CapaDePresentacio::getInstancia();

        int opcionPrincipal = 0;
        while (opcionPrincipal != 4) {
            if (sobrenomUsuari.empty()) {
                mostrarMenuPrincipal();
                std::cin >> opcionPrincipal;

                switch (opcionPrincipal) {
                case 1:
                    sobrenomUsuari = capaPresentacio->iniciSessio();
                    break;
                case 2:
                    capaPresentacio->registrarUsuari();
                    break;
                case 3:
                    gestionarConsultas();
                    break;
                case 4:
                    std::cout << "Sortint de l'aplicacio. Adeu!\n";
                    return 0;
                default:
                    std::cout << "Opcio no valida. Torna-ho a provar.\n";
                }
            }
            else {
                mostrarMenuSesionIniciada();
                std::cin >> opcionPrincipal;

                switch (opcionPrincipal) {
                case 1:
                    gestionarUsuaris(capaPresentacio);
                    break;
                case 2:
                    gestionarVisualitzacions(sobrenomUsuari);
                    break;
                case 3:
                    gestionarConsultas();
                    break;
                case 4:
                    capaPresentacio->tancaSessio();
                    sobrenomUsuari.clear();
                    break;
                case 5:
                    std::cout << "Sortint de l'aplicacio. Adeu!\n";
                    return 0;
                default:
                    std::cout << "Opcio no valida. Torna-ho a provar.\n";
                }
            }
        }
    }
    catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }

    return 0;
}
