#include "CapaDePresentacio.h"
#include <iostream>

// Inicialización de la instancia única
CapaDePresentacio* CapaDePresentacio::instancia = nullptr;

CapaDePresentacio* CapaDePresentacio::getInstancia() {
    if (!instancia) {
        instancia = new CapaDePresentacio();
    }
    return instancia;
}


void CapaDePresentacio::iniciSessio() {
    std::string sobrenom, contrasenya;
    std::cout << "Introdueix el sobrenom: ";
    std::cin >> sobrenom;
    std::cout << "Introdueix la contrasenya: ";
    std::cin >> contrasenya;

    try {
        TxIniciSessio tx; // Crear el objeto
        tx.crear(sobrenom, contrasenya); // Configurar los datos
        tx.executar(); // Ejecutar la transacción
        std::cout << "Sessio iniciada correctament.\n";
    }
    catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << '\n';
    }
}

void CapaDePresentacio::tancaSessio() {
    char confirmacio;
    std::cout << "Estàs segur de voler tancar la sessió? (S/N): ";
    std::cin >> confirmacio;

    if (toupper(confirmacio) == 'S') {
        TxTancaSessio tx;
        tx.crear();
        tx.executar();
        std::cout << "Sessió tancada correctament.\n";
    }
    else {
        std::cout << "Operació cancel·lada.\n";
    }
}

void CapaDePresentacio::registrarUsuari() {
    std::string nom, sobrenom, contrasenya, correu, modalitat;
    std::string dataNaixement;

    std::cout << "Nom complet: ";
    std::getline(std::cin >> std::ws, nom);
    std::cout << "Sobrenom: ";
    std::cin >> sobrenom;
    std::cout << "Contrasenya: ";
    std::cin >> contrasenya;
    std::cout << "Correu electrònic: ";
    std::cin >> correu;
    std::cout << "Data de naixement (YYYY-MM-DD): ";
    std::cin >> dataNaixement;
    std::cout << "Modalitat de subscripció: ";
    std::cin >> modalitat;

    TxRegistraUsuari tx;
    try {
        tx.crear(nom, sobrenom, contrasenya, correu, dataNaixement, modalitat);
        tx.executar();
        std::cout << "Usuari registrat correctament.\n";
    }
    catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << '\n';
    }
}

void CapaDePresentacio::consultaUsuari() {
    std::string sobrenom;
    std::cout << "Introdueix el sobrenom de l'usuari a consultar: ";
    std::cin >> sobrenom;

    try {
        TxConsultaUsuari txConsulta;
        txConsulta.crear(sobrenom);
        txConsulta.executar();
        DTOUsuari usuari = txConsulta.obteResultat();

        std::cout << "=== Informacio del usuari ===\n";
        std::cout << "Nom: " << usuari.obteNom() << "\n"
            << "Sobrenom: " << usuari.obteSobrenom() << "\n"
            << "Correu: " << usuari.obteCorreu() << "\n"
            << "Data de naixement: " << usuari.obteDataNaixement() << "\n"
            << "Modalitat: " << usuari.obteModalitat() << "\n";
    }
    catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << " (Potser l'usuari no existeix)\n";
    }
}

void CapaDePresentacio::modificarUsuari() {
    std::string sobrenom, nom, correu, modalitat, dataNaixement;
    CtrlModificarUsuari ctrl;

    std::cout << "Introdueix el sobrenom del usuari a modificar: ";
    std::cin >> sobrenom;

    DTOUsuari usuariActual = ctrl.consultaUsuari(sobrenom);

    std::cout << "Informacio actual:\n"
        << "Nom: " << usuariActual.obteNom() << "\n"
        << "Correu: " << usuariActual.obteCorreu() << "\n"
        << "Data de naixement: " << usuariActual.obteDataNaixement() << "\n"
        << "Modalitat: " << usuariActual.obteModalitat() << "\n";

    std::cout << "Introduce el nuevo nombre (dejar vacio para mantener): ";
    std::getline(std::cin >> std::ws, nom);

    std::cout << "Introduce el nuevo correo (dejar vacio para mantener): ";
    std::getline(std::cin >> std::ws, correu);

    std::cout << "Introduce la nueva data de naixement (dejar vacio para mantener): ";
    std::getline(std::cin >> std::ws, dataNaixement);

    std::cout << "Introduce la nueva modalitat (dejar vacio para mantener): ";
    std::getline(std::cin >> std::ws, modalitat);

    DTOUsuari usuarioModificado(
        usuariActual.obteSobrenom(),
        nom.empty() ? usuariActual.obteNom() : nom,
        correu.empty() ? usuariActual.obteCorreu() : correu,
        "", // Contrasenya no se modifica
        dataNaixement.empty() ? usuariActual.obteDataNaixement() : dataNaixement,
        modalitat.empty() ? usuariActual.obteModalitat() : modalitat);

    ctrl.modificaUsuari(usuarioModificado);

    std::cout << "Usuario modificado correctamente.\n";
}

void CapaDePresentacio::esborraUsuari() {
    std::string contrasenya;
    std::cout << "Confirma la teva contrasenya per esborrar l'usuari: ";
    std::cin >> contrasenya;

    TxEsborraUsuari tx;
    try {
        tx.crear(contrasenya);
        tx.executar();
        std::cout << "Usuari esborrat correctament.\n";
    }
    catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << '\n';
    }
}
