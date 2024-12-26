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

std::string convertirFecha(const std::string& fecha) {
    if (fecha.size() != 10 || fecha[2] != '/' || fecha[5] != '/') {
        throw std::invalid_argument("El formato de la fecha debe ser DD/MM/YYYY.");
    }

    std::string dia = fecha.substr(0, 2);
    std::string mes = fecha.substr(3, 2);
    std::string anio = fecha.substr(6, 4);

    return anio + "-" + mes + "-" + dia;
}

bool validarCorreo(const std::string& correo) {
    size_t arrobaPos = correo.find('@');
    size_t puntoPos = correo.find_last_of('.');

    // Validar que el correo contiene '@', un punto después de '@', y que termina en algo como ".com"
    return arrobaPos != std::string::npos &&    // Debe tener '@'
        puntoPos != std::string::npos &&     // Debe tener un '.'
        arrobaPos < puntoPos &&              // El '@' debe estar antes del último '.'
        puntoPos < correo.size() - 2;        // Debe haber al menos dos caracteres después del '.'
}


std::string CapaDePresentacio::iniciSessio() {
    std::string sobrenom, contrasenya;

    // Mostrar título de la pantalla de inicio de sesión
    std::cout << "\n*************************\n";
    std::cout << "**     Inici sessio    **\n";
    std::cout << "*************************\n";

    // Solicitar sobrenom
    std::cout << "Sobrenom: ";
    std::cin >> sobrenom;

    // Solicitar contrasenya
    std::cout << "Contrasenya: ";
    std::cin >> contrasenya;

    TxIniciSessio tx;
    try {
        tx.crear(sobrenom, contrasenya);
        tx.executar();

        // Mensaje de éxito
        std::cout << "\nSessio iniciada correctament!\n";
        std::cout << "Prem <Intro> per continuar...\n";
        std::cin.ignore(); // Ignorar nueva línea
        std::cin.get();    // Esperar a que se presione Intro
        return sobrenom;   // Retornar el sobrenom si es correcto
    }
    catch (const std::exception& e) {
        // Escenario alternativo: mostrar error sin revelar la razón específica
        std::cout << "\nError: Sobrenom o contrasenya incorrecte.\n";
        std::cout << "Prem <Intro> per continuar...\n";
        std::cin.ignore();
        std::cin.get();
        return ""; // Retornar cadena vacía en caso de error
    }
}


bool CapaDePresentacio::tancaSessio() {
    // Mostrar título de la pantalla de cerrar sesión
    std::cout << "\n*************************\n";
    std::cout << "**    Tancar sessio    **\n";
    std::cout << "*************************\n";

    // Solicitar confirmación del usuario
    char confirmacio;
    std::cout << "Vols tancar la sessio (S/N): ";
    std::cin >> confirmacio;

    if (toupper(confirmacio) == 'S') {
        TxTancaSessio tx;
        try {
            tx.crear();
            tx.executar();

            // Mensaje de éxito
            std::cout << "\nSessio tancada correctament!\n";
            std::cout << "Prem <Intro> per continuar...\n";
            std::cin.ignore();
            std::cin.get();
            return true; // Indica que la sesión se ha cerrado
        }
        catch (const std::exception& e) {
            std::cerr << "\nError al tancar la sessio: " << e.what() << '\n';
            std::cout << "Prem <Intro> per continuar...\n";
            std::cin.ignore();
            std::cin.get();
            return false; // Error, no se cerró la sesión
        }
    }
    else {
        // Escenario alternativo: No se cierra la sesión
        std::cout << "\nOperacio cancel·lada. Sessio no tancada.\n";
        std::cout << "Prem <Intro> per continuar...\n";
        std::cin.ignore();
        std::cin.get();
        return false; // Usuario decidió no cerrar la sesión
    }
}


void CapaDePresentacio::registrarUsuari() {
    std::string nom, sobrenom, contrasenya, correu, modalitat;
    std::string dataNaixement;

    try {
        std::cout << "** Registrar usuari **\n";
        std::cout << "Nom complet: ";
        std::getline(std::cin >> std::ws, nom);
        std::cout << "Sobrenom: ";
        std::cin >> sobrenom;
        std::cout << "Contrasenya: ";
        std::cin >> contrasenya;
        // Validar correo electrónico
        while (true) {
            std::cout << "Correu electronic: ";
            std::cin >> correu;

            if (validarCorreo(correu)) {
                break; // Si el correo es válido, salimos del bucle
            }
            else {
                std::cerr << "Error: Correu electronic no es valid. Intenta-ho de nou.\n";
            }
        }
        std::cout << "Data naixement (DD/MM/YYYY): ";
        std::cin >> dataNaixement;

        // Convertir la fecha al formato YYYY-MM-DD
        dataNaixement = convertirFecha(dataNaixement);

        // Validar modalidad de suscripción
        while (true) {
            std::cout << "Modalitats de subscripcio disponibles:\n";
            std::cout << "  1. Completa\n";
            std::cout << "  2. Cinefil\n";
            std::cout << "  3. Infantil\n";
            std::cout << "Escull modalitat: ";
            int opcionModalitat;

            if (!(std::cin >> opcionModalitat)) {
                // Si la entrada no es un número, limpiar el error y descartar la entrada
                std::cin.clear(); // Limpia el estado de error
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Descarta la entrada inválida
                std::cerr << "Error: Entrada no valida. Introdueix un numero entre 1 i 3.\n";
                continue; // Vuelve a solicitar la modalidad
            }

            switch (opcionModalitat) {
            case 1: modalitat = "Completa"; break;
            case 2: modalitat = "Cinefil"; break;
            case 3: modalitat = "Infantil"; break;
            default:
                std::cerr << "Error: Modalitat invalida. Introdueix un numero entre 1 i 3.\n";
                continue; // Reintenta la selección
            }
            break; // Salir del bucle si la modalidad es válida
        }

        TxRegistraUsuari tx;
        tx.crear(nom, sobrenom, contrasenya, correu, dataNaixement, modalitat);
        tx.executar();
        std::cout << "Nou usuari registrat correctament!\n\n";
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Espera al usuario
        std::cin.get(); // Pausa hasta que el usuario presione Intro
    }
    catch (const std::exception& e) {
        // Traducir errores específicos de la base de datos
        std::string mensajeError = e.what();
        if (mensajeError.find("Duplicate entry") != std::string::npos) {
            if (mensajeError.find(sobrenom) != std::string::npos) {
                mensajeError = "Error: El sobrenom '" + sobrenom + "' ja existeix.";
            }
            else if (mensajeError.find(correu) != std::string::npos) {
                mensajeError = "Error: El correu electronic '" + correu + "' ja existeix.";
            }
        }
        else if (mensajeError == "Modalitat invalida.") {
            mensajeError = "Error: La modalitat seleccionada no es valida.";
        }

        // Mostrar el mensaje de error traducido
        std::cerr << mensajeError << "\n\n";
        std::cout << "Prem Intro per tornar al menu principal...\n";
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Esperar al usuario
        std::cin.get(); // Pausar hasta que presione Intro
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

