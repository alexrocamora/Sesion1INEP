#include <iostream>
#include "CapaDePresentacio.h"
#include "ConnexioBD.hpp"

void mostrarMenu() {
    std::cout << "\n=== Menu Principal ===" << std::endl;
    std::cout << "1. Registrar Usuari" << std::endl;
    std::cout << "2. Consultar Usuari" << std::endl;
    std::cout << "3. Modificar Usuari" << std::endl;
    std::cout << "4. Esborrar Usuari" << std::endl;
    std::cout << "5. Sortir" << std::endl;
    std::cout << "Selecciona una opcio: ";
}

int main() {
    try {
        // Inicializa la conexión con la base de datos (Singleton)
        ConnexioBD& connexio = ConnexioBD::getInstance();
        std::cout << "Connexio establerta correctament.\n";

        // Obtén la instancia de la capa de presentación
        CapaDePresentacio* capaPresentacio = CapaDePresentacio::getInstancia();

        int opcio = 0;
        while (opcio != 5) {
            mostrarMenu();
            std::cin >> opcio;

            switch (opcio) {
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
