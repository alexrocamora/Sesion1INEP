#include <iostream>
#include <locale>
#include "CapaDePresentacio.h"
#include "ConnexioBD.hpp"
#include "TxInfoVisualitzacions.h"

#ifdef _WIN32
#define CLEAR "CLS"
#else
#define CLEAR "clear"
#endif

// Función para limpiar la consola
void limpiarConsola() {
    std::system(CLEAR);
}

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

// Validar entrada del usuario
int obtenerOpcion() {
    int opcion;
    while (!(std::cin >> opcion)) {
        std::cin.clear(); // Limpia el estado de error
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Descarta la entrada inválida
        std::cout << "Entrada no valida. Selecciona una opcion valida: ";
    }
    return opcion;
}

// Función para gestionar consultas
void gestionarConsultas() {
    int opcionConsulta = 0;
    while (opcionConsulta != 4) {
        limpiarConsola();
        mostrarMenuConsultas();
        opcionConsulta = obtenerOpcion();
        limpiarConsola();

        switch (opcionConsulta) {
        case 1:
            std::cout << "Properes estrenes: Pendiente de implementar.\n\n";
            break;
        case 2:
            std::cout << "Ultimes novetats: Pendiente de implementar.\n\n";
            break;
        case 3:
            std::cout << "Pelicules mes vistes: Pendiente de implementar.\n\n";
            break;
        case 4:
            std::cout << "Tornant al menu principal...\n\n";
            break;
        default:
            std::cout << "Opcio no valida. Torna-ho a provar.\n\n";
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
        limpiarConsola();
        std::cout << "\n=== Consultar Visualitzacions ===" << std::endl;
        std::cout << "1. Visualitzacions de Pelicules" << std::endl;
        std::cout << "2. Visualitzacions de Series" << std::endl;
        std::cout << "3. Tornar" << std::endl;
        std::cout << "Selecciona una opcio: ";
        opcionVisualitzacions = obtenerOpcion();
        limpiarConsola();

        switch (opcionVisualitzacions) {
        case 1:
            txInfo.mostrarDetallsPelicules();
            break;
        case 2:
            txInfo.mostrarDetallsSeries();
            break;
        case 3:
            std::cout << "Tornant al menu principal...\n\n";
            break;
        default:
            std::cout << "Opcio no valida. Torna-ho a provar.\n\n";
        }
    }
}

// Función para gestionar visualizaciones
void gestionarVisualitzacions(const std::string& sobrenomUsuari) {
    int opcionVisualizar = 0;
    while (opcionVisualizar != 4) {
        limpiarConsola();
        mostrarMenuVisualizacion();
        opcionVisualizar = obtenerOpcion();
        limpiarConsola();

        switch (opcionVisualizar) {
        case 1:
            std::cout << "Visualitzar pelicula: Pendiente de implementar.\n\n";
            break;
        case 2:
            std::cout << "Visualitzar capitol: Pendiente de implementar.\n\n";
            break;
        case 3:
            consultarVisualitzacions(sobrenomUsuari);
            break;
        case 4:
            std::cout << "Tornant al menu principal...\n\n";
            break;
        default:
            std::cout << "Opcio no valida. Torna-ho a provar.\n\n";
        }
    }
}

// Función para gestionar usuarios
void gestionarUsuaris(CapaDePresentacio* capaPresentacio, const std::string& sobrenomUsuari) {
    int opcion = 0;
    while (opcion != 5) {
        limpiarConsola();
        std::cout << "\n=== Gestio Usuaris ===" << std::endl;
        std::cout << "1. Consulta usuari" << std::endl;
        std::cout << "2. Modificar usuari" << std::endl;
        std::cout << "3. Modificar contrasenya" << std::endl;
        std::cout << "4. Esborrar usuari" << std::endl;
        std::cout << "5. Tornar" << std::endl;
        std::cout << "Selecciona una opcio: ";
        opcion = obtenerOpcion();
        limpiarConsola();

        switch (opcion) {
        case 1:
            capaPresentacio->consultaUsuari(sobrenomUsuari);
            break;
        case 2:
            capaPresentacio->modificarUsuari(sobrenomUsuari); 
            break;
        case 3:
            std::cout << "Modificar contrasenya: Pendiente de implementar.\n\n";
            break;
        case 4:
            capaPresentacio->esborraUsuari(sobrenomUsuari);
            break;
        case 5:
            std::cout << "Tornant al menu de sessio.\n\n";
            break;
        default:
            std::cout << "Opcio no valida. Torna-ho a provar.\n\n";
        }
    }
}

// Función principal
int main() {
    try {
        ConnexioBD& connexio = ConnexioBD::getInstance();
        std::cout << "Connexio establerta correctament.\n";

        std::string sobrenomUsuari; // Almacena el usuario activo
        CapaDePresentacio* capaPresentacio = CapaDePresentacio::getInstancia();

        int opcionPrincipal = 0;

        while (true) { // Bucle infinito para mantener la aplicación activa
            limpiarConsola();

            if (sobrenomUsuari.empty()) { // Menú principal
                mostrarMenuPrincipal();
                opcionPrincipal = obtenerOpcion();
                limpiarConsola();

                switch (opcionPrincipal) {
                case 1: { // Iniciar Sessio
                    sobrenomUsuari = capaPresentacio->iniciSessio();
                    break;
                }
                case 2: // Registrar Usuari
                    capaPresentacio->registrarUsuari();
                    break;
                case 3: // Consultas desde el menú inicial
                    gestionarConsultas();
                    break;
                case 4: // Salir de la aplicación
                    std::cout << "Sortint de l'aplicacio. Adeu!\n\n";
                    return 0;
                default:
                    std::cout << "Opcio no valida. Torna-ho a provar.\n\n";
                }
            }
            else { // Menú de sesión iniciada
                mostrarMenuSesionIniciada();
                opcionPrincipal = obtenerOpcion();
                limpiarConsola();

                switch (opcionPrincipal) {
                case 1: // Gestionar usuarios
                    gestionarUsuaris(capaPresentacio, sobrenomUsuari);
                    break;
                case 2: // Gestionar visualizaciones
                    gestionarVisualitzacions(sobrenomUsuari);
                    break;
                case 3: // Consultas
                    gestionarConsultas();
                    break;
                case 4: // Tancar Sessió
                    if (capaPresentacio->tancaSessio()) {
                        sobrenomUsuari.clear(); // Limpiar el usuario si la sesión fue cerrada
                        std::cout << "Sessió tancada correctament. Tornant al menú principal...\n\n";
                    }
                    else {
                        std::cout << "Operació cancel·lada. Sessió no tancada.\n\n";
                    }
                    break;
                case 5: // Salir de la aplicación
                    std::cout << "Sortint de l'aplicacio. Adeu!\n\n";
                    return 0;
                default:
                    std::cout << "Opcio no valida. Torna-ho a provar.\n\n";
                }
            }
        }
    }
    catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }

    return 0;
}

