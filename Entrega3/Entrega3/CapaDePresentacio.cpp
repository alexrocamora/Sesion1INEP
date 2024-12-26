#include "CapaDePresentacio.h"
#include "TxInfoVisualitzacions.h"
#include <iostream>
#include <string>

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

std::string convertirFechaMostrar(const std::string& fecha) {
    if (fecha.size() != 10 || fecha[4] != '-' || fecha[7] != '-') {
        throw std::invalid_argument("El formato de la fecha debe ser YYYY-MM-DD.");
    }

    std::string anio = fecha.substr(0, 4);
    std::string mes = fecha.substr(5, 2);
    std::string dia = fecha.substr(8, 2);

    return dia + "/" + mes + "/" + anio;
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


void CapaDePresentacio::consultaUsuari(const std::string& sobrenom) {
    try {
        // Título de la consulta
        std::cout << "** Consulta usuari **\n";

        // Consultar información del usuario
        TxConsultaUsuari txConsulta;
        txConsulta.crear(sobrenom);
        txConsulta.executar();
        DTOUsuari usuari = txConsulta.obteResultat();

        // Consultar estadísticas de visualización
        TxInfoVisualitzacions txInfo;
        txInfo.crear(sobrenom);
        txInfo.executar();
        int peliculesVistes = txInfo.obteResultatPelicules();
        int capitolsVistos = txInfo.obteResultatSeries();

        // Mostrar información del usuario
        std::cout << "Nom complet: " << usuari.obteNom() << "\n";
        std::cout << "Sobrenom: " << usuari.obteSobrenom() << "\n";
        std::cout << "Correu electronic: " << usuari.obteCorreu() << "\n";

        // Convertir la fecha al formato DD/MM/YYYY
        std::string dataNaixement = usuari.obteDataNaixement();
        std::string dataFormatejada =
            dataNaixement.substr(8, 2) + "/" + dataNaixement.substr(5, 2) + "/" + dataNaixement.substr(0, 4);

        std::cout << "Data naixement (DD/MM/YYYY): " << dataFormatejada << "\n";
        std::cout << "Modalitat subscripcio: " << usuari.obteModalitat() << "\n";

        // Mostrar estadísticas de visualización
        std::cout << "\n" << peliculesVistes << " pelicules visualitzades\n";
        std::cout << capitolsVistos << " capitols visualitzats\n";

        // Pausar antes de volver
        std::cout << "\nPrem <Intro> per tornar al menu principal...\n";
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cin.get();
    }
    catch (const std::exception& e) {
        // Manejar errores en la consulta
        std::cerr << "Error: " << e.what() << " (Potser l'usuari no existeix o hi ha un problema)\n";
        std::cout << "Prem <Intro> per continuar...\n";
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cin.get();
    }
}


void CapaDePresentacio::modificarUsuari(const std::string& sobrenom) {
    try {
        TxConsultaUsuari txConsulta;
        txConsulta.crear(sobrenom);
        txConsulta.executar();
        DTOUsuari usuariActual = txConsulta.obteResultat();

        // Convertir la fecha para mostrarla en formato DD/MM/YYYY
        std::string dataNaixementMostrar = convertirFechaMostrar(usuariActual.obteDataNaixement());

        // Mostrar la información actual del usuario
        std::cout << "** Modifica usuari **\n";
        std::cout << "Nom complet: " << usuariActual.obteNom() << "\n";
        std::cout << "Sobrenom: " << usuariActual.obteSobrenom() << "\n";
        std::cout << "Correu electronic: " << usuariActual.obteCorreu() << "\n";
        std::cout << "Data naixement (DD/MM/YYYY): " << dataNaixementMostrar << "\n";
        std::cout << "Modalitat subscripcio: " << usuariActual.obteModalitat() << "\n\n";

        // Solicitar los nuevos valores para cada atributo
        std::string nouNom, nouCorreu, novaDataNaixement, novaModalitat, novaContrasenya;

        std::cout << "Omplir la informacio que es vol modificar ...\n";
        std::cout << "Nom complet (" << usuariActual.obteNom() << ") (deixar buit per no modificar): ";
        std::getline(std::cin >> std::ws, nouNom);
        if (nouNom.empty()) {
            // Si está vacío, conserva el valor actual
           nouNom = usuariActual.obteNom();
        }
        std::cout << "Contrasenya (deixar buit per no modificar): ";
        std::getline(std::cin >> std::ws, novaContrasenya);

        // Validar correo electrónico
        while (true) {
            std::cout << "Correu electronic (" << usuariActual.obteCorreu() << ") (deixar buit per no modificar): ";
            std::getline(std::cin >> std::ws, nouCorreu);

            if (nouCorreu.empty() || validarCorreo(nouCorreu)) {
                break; // Si está vacío o válido, salir del bucle
            }
            else {
                std::cerr << "Error: Correu electronic no valid. Intenta-ho de nou.\n";
            }
        }

        // Validar y convertir fecha
        while (true) {
            std::cout << "Data naixement (DD/MM/YYYY) (" << usuariActual.obteDataNaixement() << ") (deixar buit per no modificar): ";
            std::getline(std::cin >> std::ws, novaDataNaixement);

            if (novaDataNaixement.empty()) {
                break;
            }

            try {
                novaDataNaixement = convertirFecha(novaDataNaixement);
                break;
            }
            catch (const std::exception& e) {
                std::cerr << "Error: " << e.what() << " Intenta-ho de nou.\n";
            }
        }

        // Validar modalidad
        while (true) {
            std::cout << "Modalitats de subscripcio disponibles:\n";
            std::cout << "  1. Completa\n";
            std::cout << "  2. Cinefil\n";
            std::cout << "  3. Infantil\n";
            std::cout << "Escull modalitat (" << usuariActual.obteModalitat() << "): ";
            int opcionModalitat;
            if (std::cin >> opcionModalitat) {
                switch (opcionModalitat) {
                case 1: novaModalitat = "Completa"; break;
                case 2: novaModalitat = "Cinefil"; break;
                case 3: novaModalitat = "Infantil"; break;
                default:
                    std::cerr << "Error: Modalitat invalida.\n";
                    continue;
                }
                break;
            }
            else {
                std::cin.clear(); // Limpia el estado de error
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Ignorar entrada inválida
                std::cerr << "Error: Entrada no valida. Intenta-ho de nou.\n";
            }
        }

        // Crear DTO con los nuevos valores o los actuales si no se modificaron
        DTOUsuari usuariModificat(
            usuariActual.obteSobrenom(),
            nouNom.empty() ? usuariActual.obteNom() : nouNom,
            nouCorreu.empty() ? usuariActual.obteCorreu() : nouCorreu,
            novaContrasenya.empty() ? usuariActual.obteContrasenya() : novaContrasenya,
            novaDataNaixement.empty() ? usuariActual.obteDataNaixement() : novaDataNaixement,
            novaModalitat.empty() ? usuariActual.obteModalitat() : novaModalitat
        );

        // Ejecutar modificación
        CtrlModificarUsuari ctrlModificar;
        ctrlModificar.modificaUsuari(usuariModificat);

        // Mostrar la información actualizada
        std::cout << "** Dades usuari modificades **\n";
        std::cout << "Nom complet: " << usuariModificat.obteNom() << "\n";
        std::cout << "Sobrenom: " << usuariModificat.obteSobrenom() << "\n";
        std::cout << "Correu electronic: " << usuariModificat.obteCorreu() << "\n";
        std::cout << "Data naixement: " << usuariModificat.obteDataNaixement() << "\n";
        std::cout << "Modalitat subscripcio: " << usuariModificat.obteModalitat() << "\n\n";
        std::cout << "Prem <Intro> per tornar al menu de sessio...\n";
        std::cin.ignore();
        std::cin.get();

    }
    catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << "\n";
        std::cout << "Prem <Intro> per tornar al menu de sessio...\n";
        std::cin.ignore();
        std::cin.get();
    }
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

