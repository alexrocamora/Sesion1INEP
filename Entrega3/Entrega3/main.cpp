#include <iostream>
#include "CapaDePresentacio.h"
#include "ConnexioBD.hpp"
#include "CercadoraVisualitzaPel.h"
#include "CercadoraVisualitzaSerie.h"

void mostrarMenuPrincipal() {
    std::cout << "\n=== Menu Principal ===" << std::endl;
    std::cout << "1. Iniciar Sessio" << std::endl;
    std::cout << "2. Registrar Usuari" << std::endl;
    std::cout << "3. Sortir" << std::endl;
    std::cout << "Selecciona una opcio: ";
}

void mostrarMenuSesionIniciada() {
    std::cout << "\n=== Menu Sessio Iniciada ===" << std::endl;
    std::cout << "1. Gestio Usuaris" << std::endl;
    std::cout << "2. Consultar Visualitzacions" << std::endl;
    std::cout << "3. Tancar Sessio" << std::endl;
    std::cout << "4. Sortir" << std::endl;
    std::cout << "Selecciona una opcio: ";
}

void consultarVisualitzacions(const std::string& sobrenomUsuari) {
    int opcion = 0;
    while (opcion != 3) {
        std::cout << "\n=== Consultar Visualitzacions ===" << std::endl;
        std::cout << "1. Visualitzacions de Pel·lícules (per usuari)" << std::endl;
        std::cout << "2. Visualitzacions de Sèries (per usuari)" << std::endl;
        std::cout << "3. Tornar" << std::endl;
        std::cout << "Selecciona una opció: ";
        std::cin >> opcion;

        switch (opcion) {
        case 1: { // Visualitzacions de Pel·lícules
            CercadoraVisualitzaPel cercadora;
            int totalPel = cercadora.cercaNumVisualitzacions(sobrenomUsuari);

            std::cout << "=== Visualitzacions de Pel·lícules ===\n";
            std::cout << "Usuari: " << sobrenomUsuari
                << " - Total visualitzacions: " << totalPel << "\n";
            break;
        }
        case 2: { // Visualitzacions de Sèries
            CercadoraVisualitzaSerie cercadora;
            int totalSerie = cercadora.cercaNumVisualitzacions(sobrenomUsuari);

            std::cout << "=== Visualitzacions de Sèries ===\n";
            std::cout << "Usuari: " << sobrenomUsuari
                << " - Total visualitzacions: " << totalSerie << "\n";
            break;
        }
        case 3:
            std::cout << "Tornant al menú de sessió iniciada...\n";
            break;
        default:
            std::cout << "Opció no vàlida. Torna-ho a provar." << std::endl;
        }
    }
}

void gestionarUsuaris(CapaDePresentacio* capaPresentacio) {
    int opcion = 0;
    while (opcion != 5) {
        std::cout << "\n=== Gestio Usuaris ===" << std::endl;
        std::cout << "1. Registrar Usuari" << std::endl;
        std::cout << "2. Consultar Usuari" << std::endl;
        std::cout << "3. Modificar Usuari" << std::endl;
        std::cout << "4. Esborrar Usuari" << std::endl;
        std::cout << "5. Tornar" << std::endl;
        std::cout << "Selecciona una opcio: ";
        std::cin >> opcion;

        switch (opcion) {
        case 1:
            capaPresentacio->registrarUsuari();
            break;
        case 2:
            capaPresentacio->consultaUsuari();
            break;
        case 3:
            capaPresentacio->modificarUsuari();
            break;
        case 4:
            capaPresentacio->esborraUsuari();
            break;
        case 5:
            std::cout << "Tornant al menú de sessió iniciada.\n";
            break;
        default:
            std::cout << "Opcio no valida. Torna-ho a provar." << std::endl;
        }
    }
}

int main() {
    try {
        // Inicializa la conexión con la base de datos (Singleton)
        ConnexioBD& connexio = ConnexioBD::getInstance();
        std::cout << "Connexio establerta correctament.\n";

        std::string sobrenomUsuari; // Variable para almacenar el usuario activo
        // Obtén la instancia de la capa de presentación
        CapaDePresentacio* capaPresentacio = CapaDePresentacio::getInstancia();

        int opcionPrincipal = 0;
        while (opcionPrincipal != 3) {
            mostrarMenuPrincipal();
            std::cin >> opcionPrincipal;

            switch (opcionPrincipal) {
            case 1: { // Iniciar Sessio
                sobrenomUsuari = capaPresentacio->iniciSessio(); // Capturamos el sobrenom del usuario
                if (!sobrenomUsuari.empty()) { // Si la sesión fue exitosa
                    int opcionSesion = 0;
                    while (opcionSesion != 4) {
                        mostrarMenuSesionIniciada();
                        std::cin >> opcionSesion;

                        switch (opcionSesion) {
                        case 1: // Gestio Usuaris
                            gestionarUsuaris(capaPresentacio);
                            break;
                        case 2: // Consultar Visualitzacions
                            consultarVisualitzacions(sobrenomUsuari);
                            break;
                        case 3: // Tancar Sessio
                            capaPresentacio->tancaSessio();
                            opcionSesion = 4; // Salimos del menú de sesión
                            break;
                        case 4: // Sortir
                            std::cout << "Sortint de l'aplicacio. Adeu!" << std::endl;
                            return 0;
                        default:
                            std::cout << "Opcio no valida. Torna-ho a provar." << std::endl;
                        }
                    }
                }
                else {
                    std::cout << "Error en l'inici de sessió. Torna-ho a provar.\n";
                }
                break;
            }
            case 2: // Registrar Usuari
                capaPresentacio->registrarUsuari();
                break;
            case 3: // Sortir
                std::cout << "Sortint de l'aplicacio. Adeu!" << std::endl;
                break;
            default:
                std::cout << "Opcio no valida. Torna-ho a provar." << std::endl;
            }
        }
    }
    catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }

    return 0;
}

