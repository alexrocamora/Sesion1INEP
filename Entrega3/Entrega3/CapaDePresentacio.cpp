#include "CapaDePresentacio.h"
#include <iostream>

// Inicializaci�n de la instancia �nica
CapaDePresentacio* CapaDePresentacio::instancia = nullptr;

CapaDePresentacio* CapaDePresentacio::getInstancia() {
    if (!instancia) {
        instancia = new CapaDePresentacio();
    }
    return instancia;
}

/*
void CapaDePresentacio::iniciSessio() {
    std::string sobrenom, contrasenya;
    std::cout << "Introdueix el sobrenom: ";
    std::cin >> sobrenom;
    std::cout << "Introdueix la contrasenya: ";
    std::cin >> contrasenya;

    TxIniciSessio tx;
    try {
        tx.crear(sobrenom, contrasenya);
        tx.executar();
        std::cout << "Sessi� iniciada correctament.\n";
    }
    catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << '\n';
    }
}

void CapaDePresentacio::tancaSessio() {
    char confirmacio;
    std::cout << "Est�s segur de voler tancar la sessi�? (S/N): ";
    std::cin >> confirmacio;

    if (toupper(confirmacio) == 'S') {
        TxTancaSessio tx;
        tx.crear();
        tx.executar();
        std::cout << "Sessi� tancada correctament.\n";
    }
    else {
        std::cout << "Operaci� cancel�lada.\n";
    }
}
*/
void CapaDePresentacio::registrarUsuari() {
    std::string nom, sobrenom, contrasenya, correu, modalitat;
    std::string dataNaixement;

    std::cout << "Nom complet: ";
    std::cin >> nom;
    std::cout << "Sobrenom: ";
    std::cin >> sobrenom;
    std::cout << "Contrasenya: ";
    std::cin >> contrasenya;
    std::cout << "Correu electr�nic: ";
    std::cin >> correu;
    std::cout << "Data de naixement (YYYY-MM-DD): ";
    std::cin >> dataNaixement;
    std::cout << "Modalitat de subscripci�: ";
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
        txConsulta.crear(); // Si se necesita pasar el sobrenom aqu�, se ha de modificar en TxConsultaUsuari
        txConsulta.executar();
        DTOUsuari usuari = txConsulta.obteResultat();

        std::cout << "=== Informaci� de l'usuari ===\n";
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

    std::cout << "Introduce el sobrenom del usuario a modificar: ";
    std::cin >> sobrenom;

    DTOUsuari usuariActual = ctrl.consultaUsuari(sobrenom);

    std::cout << "Informaci�n actual:\n"
        << "Nom: " << usuariActual.obteNom() << "\n"
        << "Correu: " << usuariActual.obteCorreu() << "\n"
        << "Data de naixement: " << usuariActual.obteDataNaixement() << "\n"
        << "Modalitat: " << usuariActual.obteModalitat() << "\n";

    std::cout << "Introduce el nuevo nombre (dejar vac�o para mantener): ";
    std::getline(std::cin >> std::ws, nom);

    std::cout << "Introduce el nuevo correo (dejar vac�o para mantener): ";
    std::getline(std::cin >> std::ws, correu);

    std::cout << "Introduce la nueva data de naixement (dejar vac�o para mantener): ";
    std::getline(std::cin >> std::ws, dataNaixement);

    std::cout << "Introduce la nueva modalitat (dejar vac�o para mantener): ";
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
