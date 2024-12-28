#include <iostream>
#include <locale>
#include "CapaDePresentacio.h"
#include "ConnexioBD.hpp"
#include "TxInfoVisualitzacions.h"
#include <limits>


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
    std::cout << "1. Visualitzar pelicula" << std::endl;
    std::cout << "2. Visualitzar capitol" << std::endl;
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
void gestionarConsultas(CapaDePresentacio* capaPresentacio, const std::string& sobrenomUsuari) {
    int opcionConsulta = 0;
    while (opcionConsulta != 4) {
        limpiarConsola();
        mostrarMenuConsultas();
        opcionConsulta = obtenerOpcion();
        limpiarConsola();

        switch (opcionConsulta) {
        case 1:
            capaPresentacio->properesEstrenes(sobrenomUsuari);
            break;
        case 2:
            capaPresentacio->ultimesNovetats(sobrenomUsuari);
            break;
        case 3:
            capaPresentacio->peliculesMesVistes();
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
void gestionarVisualitzacions(CapaDePresentacio* capaPresentacio, const std::string& sobrenomUsuari) {
    int opcionVisualizar = 0;
    while (opcionVisualizar != 4) {
        limpiarConsola();
        mostrarMenuVisualizacion();
        opcionVisualizar = obtenerOpcion();
        limpiarConsola();

        switch (opcionVisualizar) {
        case 1:
            capaPresentacio->visualitzaPelicula(sobrenomUsuari); 
            break;
        case 2:
            capaPresentacio->visualitzaCapitol(sobrenomUsuari); 
            break;
        case 3:
            capaPresentacio->consultaVisualitzacions(sobrenomUsuari); 
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
void gestionarUsuaris(CapaDePresentacio* capaPresentacio, std::string& sobrenomUsuari) {
    int opcion = 0;
    bool usuarioEliminado = false; // Indicador para saber si se eliminó el usuario

    while (opcion != 4 && !usuarioEliminado) {
        limpiarConsola();
        std::cout << "\n=== Gestio Usuaris ===" << std::endl;
        std::cout << "1. Consulta usuari" << std::endl;
        std::cout << "2. Modificar usuari" << std::endl;
        std::cout << "3. Esborrar usuari" << std::endl;
        std::cout << "4. Tornar" << std::endl;
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
            if (capaPresentacio->esborraUsuari(sobrenomUsuari)) {
                usuarioEliminado = true; // Eliminar el usuario activa este indicador
                sobrenomUsuari.clear(); // Limpiar el usuario activo solo si fue eliminado
            }
            break;
        case 4:
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

        while (true) {
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
                    gestionarConsultas(capaPresentacio, sobrenomUsuari);
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
                    if (sobrenomUsuari.empty()) {
                        // Si se cerró sesión automáticamente, volver al menú principal
                        continue;
                    }
                    break;
                case 2: // Gestionar visualizaciones
                    gestionarVisualitzacions(capaPresentacio, sobrenomUsuari);
                    break;
                case 3: // Consultas
                    gestionarConsultas(capaPresentacio, sobrenomUsuari);
                    break;
                case 4: // Tancar Sessió (pedir confirmación)
                    if (capaPresentacio->tancaSessio(true)) {
                        sobrenomUsuari.clear(); // Limpiar el usuario si la sesión fue cerrada
                        std::cout << "Tornant al menu principal...\n\n";
                        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Limpieza extra
                        std::cin.get(); // Esperar para continuar
                    }
                    else {
                        std::cout << "Operacio cancelada. Sessio no tancada.\n\n";
                        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Limpieza extra
                        std::cin.get(); // Esperar para continuar
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