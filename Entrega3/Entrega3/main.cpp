#include <iostream>
#include "ConnexioBD.hpp"
#include "PassarellaUsuari.h"
#include "CercadoraUsuari.h"

int main() {
    try {
        // Inicializa la conexión con la base de datos
        ConnexioBD& connexio = ConnexioBD::getInstance();

        // **1. Probar inserción de un usuario**
        std::cout << "=== Inserir un usuari ===" << std::endl;
        PassarellaUsuari usuari("sobrenom2", "Nom Exemple1", "correu1@example.com", "contrasenya123", "2000-01-01", "Infantil");
        usuari.insereix();
        std::cout << "Usuari inserit correctament." << std::endl;

        // **2. Probar modificación del usuario**
        std::cout << "=== Modificar un usuari ===" << std::endl;
        usuari.posaNom("Nom Modificat");
        usuari.posaModalitatSubscripcio("Cinefil");
        usuari.modifica();
        std::cout << "Usuari modificat correctament." << std::endl;

        // **3. Probar búsqueda por sobrenom**
        std::cout << "=== Cercar un usuari pel sobrenom ===" << std::endl;
        CercadoraUsuari cercadora;
        PassarellaUsuari usuariTrobat = cercadora.cercaPerSobrenom("sobrenom2");
        std::cout << "Usuari trobat: " << usuariTrobat.obteNom() << " (" << usuariTrobat.obteCorreuElectronic() << ")" << std::endl;

        // **4. Probar eliminación del usuario**
        std::cout << "=== Esborrar un usuari ===" << std::endl;
        usuari.esborra();
        std::cout << "Usuari esborrat correctament." << std::endl;

        // **5. Probar búsqueda de todos los usuarios**
        std::cout << "=== Cercar tots els usuaris ===" << std::endl;
        std::vector<PassarellaUsuari> usuaris = cercadora.cercaTots();
        for (const auto& u : usuaris) {
            std::cout << "Usuari: " << u.obteSobrenom() << " - " << u.obteNom() << std::endl;
        }

    }
    catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }

    return 0;
}
