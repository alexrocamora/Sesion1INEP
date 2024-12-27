
#include "CapaDePresentacio.h"
#include "TxInfoVisualitzacions.h"
#include <iostream>
#include <string>
#include <conio.h>


// Inicializaci�n de la instancia �nica
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

    // Validar que el correo contiene '@', un punto despu�s de '@', y que termina en algo como ".com"
    return arrobaPos != std::string::npos &&    // Debe tener '@'
        puntoPos != std::string::npos &&     // Debe tener un '.'
        arrobaPos < puntoPos &&              // El '@' debe estar antes del �ltimo '.'
        puntoPos < correo.size() - 2;        // Debe haber al menos dos caracteres despu�s del '.'
}


std::string CapaDePresentacio::iniciSessio() {
    std::string sobrenom, contrasenya;

    // Mostrar t�tulo de la pantalla de inicio de sesi�n
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

        // Mensaje de �xito
        std::cout << "\nSessio iniciada correctament!\n";
        std::cout << "Prem <Intro> per continuar...\n";
        std::cin.ignore(); // Ignorar nueva l�nea
        std::cin.get();    // Esperar a que se presione Intro
        return sobrenom;   // Retornar el sobrenom si es correcto
    }
    catch (const std::exception& e) {
        // Escenario alternativo: mostrar error sin revelar la raz�n espec�fica
        std::cout << "\nError: Sobrenom o contrasenya incorrecte.\n";
        std::cout << "Prem <Intro> per continuar...\n";
        std::cin.ignore();
        std::cin.get();
        return ""; // Retornar cadena vac�a en caso de error
    }
}


bool CapaDePresentacio::tancaSessio(bool confirmacio) {
    if (confirmacio) {
        std::cout << "\n*************************\n";
        std::cout << "**     Tanca sessio    **\n";
        std::cout << "*************************\n";
        char respuesta;
        std::cout << "Vols tancar la sessio (S/N): ";
        std::cin >> respuesta;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Limpiar el buffer

        if (toupper(respuesta) != 'S') {
            return false; // El usuario cancel� el cierre
        }
    }

    // L�gica de cierre de sesi�n
    TxTancaSessio tx;
    try {
        tx.crear();
        tx.executar();
        std::cout << "\nSessio tancada correctament!\n";
        std::cout << "Prem <Intro> per continuar...\n";
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Limpieza extra
        std::cin.get(); // Espera a que el usuario presione Enter
        return true; // Indica que la sesi�n se ha cerrado
    }
    catch (const std::exception& e) {
        std::cerr << "\nError al tancar la sessio: " << e.what() << '\n';
        std::cout << "Prem <Intro> per continuar...\n";
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Limpieza extra
        std::cin.get(); // Espera a que el usuario presione Enter
        return false; // Error al cerrar sesi�n
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
        // Validar correo electr�nico
        while (true) {
            std::cout << "Correu electronic: ";
            std::cin >> correu;

            if (validarCorreo(correu)) {
                break; // Si el correo es v�lido, salimos del bucle
            }
            else {
                std::cerr << "Error: Correu electronic no es valid. Intenta-ho de nou.\n";
            }
        }
        std::cout << "Data naixement (DD/MM/YYYY): ";
        std::cin >> dataNaixement;

        // Convertir la fecha al formato YYYY-MM-DD
        dataNaixement = convertirFecha(dataNaixement);

        // Validar modalidad de suscripci�n
        while (true) {
            std::cout << "Modalitats de subscripcio disponibles:\n";
            std::cout << "  1. Completa\n";
            std::cout << "  2. Cinefil\n";
            std::cout << "  3. Infantil\n";
            std::cout << "Escull modalitat: ";
            int opcionModalitat;

            if (!(std::cin >> opcionModalitat)) {
                // Si la entrada no es un n�mero, limpiar el error y descartar la entrada
                std::cin.clear(); // Limpia el estado de error
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Descarta la entrada inv�lida
                std::cerr << "Error: Entrada no valida. Introdueix un numero entre 1 i 3.\n";
                continue; // Vuelve a solicitar la modalidad
            }

            switch (opcionModalitat) {
            case 1: modalitat = "Completa"; break;
            case 2: modalitat = "Cinefil"; break;
            case 3: modalitat = "Infantil"; break;
            default:
                std::cerr << "Error: Modalitat invalida. Introdueix un numero entre 1 i 3.\n";
                continue; // Reintenta la selecci�n
            }
            break; // Salir del bucle si la modalidad es v�lida
        }

        TxRegistraUsuari tx;
        tx.crear(nom, sobrenom, contrasenya, correu, dataNaixement, modalitat);
        tx.executar();
        std::cout << "Nou usuari registrat correctament!\n\n";
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Espera al usuario
        std::cin.get(); // Pausa hasta que el usuario presione Intro
    }
    catch (const std::exception& e) {
        // Traducir errores espec�ficos de la base de datos
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
        // T�tulo de la consulta
        std::cout << "** Consulta usuari **\n";

        // Consultar informaci�n del usuario
        TxConsultaUsuari txConsulta;
        txConsulta.crear(sobrenom);
        txConsulta.executar();
        DTOUsuari usuari = txConsulta.obteResultat();

        // Consultar estad�sticas de visualizaci�n
        TxInfoVisualitzacions txInfo;
        txInfo.crear(sobrenom);
        txInfo.executar();
        int peliculesVistes = txInfo.obteResultatPelicules();
        int capitolsVistos = txInfo.obteResultatSeries();

        // Mostrar informaci�n del usuario
        std::cout << "Nom complet: " << usuari.obteNom() << "\n";
        std::cout << "Sobrenom: " << usuari.obteSobrenom() << "\n";
        std::cout << "Correu electronic: " << usuari.obteCorreu() << "\n";

        // Convertir la fecha al formato DD/MM/YYYY
        std::string dataNaixement = usuari.obteDataNaixement();
        std::string dataFormatejada =
            dataNaixement.substr(8, 2) + "/" + dataNaixement.substr(5, 2) + "/" + dataNaixement.substr(0, 4);

        std::cout << "Data naixement (DD/MM/YYYY): " << dataFormatejada << "\n";
        std::cout << "Modalitat subscripcio: " << usuari.obteModalitat() << "\n";

        // Mostrar estad�sticas de visualizaci�n
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
        // Consultar informaci�n actual del usuario
        TxConsultaUsuari txConsulta;
        txConsulta.crear(sobrenom);
        txConsulta.executar();
        DTOUsuari usuariActual = txConsulta.obteResultat();

        // Convertir la fecha para mostrarla en formato DD/MM/YYYY
        std::string dataNaixementMostrar = convertirFechaMostrar(usuariActual.obteDataNaixement());

        // Mostrar la informaci�n actual del usuario
        std::cout << "** Modifica usuari **\n";
        std::cout << "Nom complet: " << usuariActual.obteNom() << "\n";
        std::cout << "Sobrenom: " << usuariActual.obteSobrenom() << "\n";
        std::cout << "Correu electronic: " << usuariActual.obteCorreu() << "\n";
        std::cout << "Data naixement (DD/MM/YYYY): " << dataNaixementMostrar << "\n";
        std::cout << "Modalitat subscripcio: " << usuariActual.obteModalitat() << "\n\n";

        // Solicitar los nuevos valores para cada atributo
        std::string nouNom, nouCorreu, novaDataNaixement, novaModalitat, novaContrasenya;

        std::cout << "Omplir la informacio que es vol modificar ...\n";

        // Solicitar nuevo nombre completo
        std::cout << "Nom complet (" << usuariActual.obteNom() << ") (deixar buit per no modificar): ";
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Limpiar buffer de entrada
        std::getline(std::cin, nouNom);
        if (nouNom.empty()) {
            nouNom = usuariActual.obteNom(); // Mantener valor actual si est� vac�o
        }

        // Solicitar nueva contrase�a
        std::cout << "Contrasenya (deixar buit per no modificar): ";
        std::getline(std::cin, novaContrasenya);
        if (novaContrasenya.empty()) {
            novaContrasenya = usuariActual.obteContrasenya(); // Mantener valor actual si est� vac�o
        }

        // Solicitar nuevo correo electr�nico
        while (true) {
            std::cout << "Correu electronic (" << usuariActual.obteCorreu() << ") (deixar buit per no modificar): ";
            std::getline(std::cin, nouCorreu);
            if (nouCorreu.empty() || validarCorreo(nouCorreu)) {
                if (nouCorreu.empty()) nouCorreu = usuariActual.obteCorreu(); // Mantener valor actual si est� vac�o
                break; // Salir del bucle si es v�lido o vac�o
            }
            else {
                std::cerr << "Error: Correu electronic no valid. Intenta-ho de nou.\n";
            }
        }

        // Solicitar nueva fecha de nacimiento
        while (true) {
            std::cout << "Data naixement (DD/MM/YYYY) (" << dataNaixementMostrar << ") (deixar buit per no modificar): ";
            std::getline(std::cin, novaDataNaixement);
            if (novaDataNaixement.empty()) {
                novaDataNaixement = usuariActual.obteDataNaixement(); // Mantener valor actual si est� vac�o
                break;
            }
            try {
                novaDataNaixement = convertirFecha(novaDataNaixement); // Convertir formato
                break; // Salir del bucle si es v�lida
            }
            catch (const std::exception& e) {
                std::cerr << "Error: " << e.what() << " Intenta-ho de nou.\n";
            }
        }

        // Solicitar nueva modalidad de suscripci�n
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
                std::cin.clear(); // Limpiar estado de error
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Limpiar buffer de entrada
                std::cerr << "Error: Entrada no valida. Intenta-ho de nou.\n";
            }
        }

        // Crear DTO con los valores nuevos o los actuales si no se modificaron
        DTOUsuari usuariModificat(
            usuariActual.obteSobrenom(),
            nouNom,
            nouCorreu,
            novaContrasenya,
            novaDataNaixement,
            novaModalitat
        );

        // Ejecutar modificaci�n
        CtrlModificarUsuari ctrlModificar;
        ctrlModificar.modificaUsuari(usuariModificat);

        // Mostrar la informaci�n actualizada
        std::cout << "** Dades usuari modificades **\n";
        std::cout << "Nom complet: " << usuariModificat.obteNom() << "\n";
        std::cout << "Sobrenom: " << usuariModificat.obteSobrenom() << "\n";
        std::cout << "Correu electronic: " << usuariModificat.obteCorreu() << "\n";
        std::cout << "Data naixement: " << convertirFechaMostrar(usuariModificat.obteDataNaixement()) << "\n";
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



void CapaDePresentacio::esborraUsuari(const std::string& sobrenom) {
    std::string contrasenya;

    // T�tulo de la acci�n
    std::cout << "** Esborrar usuari **\n";
    std::cout << "Per confirmar l'esborrat, s'ha d'entrar la contrasenya...\n";

    // Solicitar contrase�a oculta
    std::cout << "Contrasenya: ";
#ifdef _WIN32
    char c;
    while ((c = _getch()) != '\r') { // Leer hasta Enter
        if (c == '\b' && !contrasenya.empty()) { // Manejar retroceso
            contrasenya.pop_back();
            std::cout << "\b \b"; // Eliminar car�cter en pantalla
        }
        else if (c != '\b') {
            contrasenya.push_back(c);
            std::cout << '*'; // Mostrar asterisco
        }
    }
#else
    termios oldt, newt;
    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~ECHO; // Desactivar eco
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    std::getline(std::cin, contrasenya);
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt); // Restaurar eco
#endif
    std::cout << std::endl;

    TxEsborraUsuari tx;
    try {
        tx.crear(sobrenom, contrasenya);
        tx.executar();

        std::cout << "Usuari esborrat correctament!\n";
        std::cout << "Sessio finalitzada per aquest usuari.\n";

        // Cerrar sesi�n autom�ticamente sin confirmaci�n
        TxTancaSessio tancaTx;
        tancaTx.crear();
        tancaTx.executar();
    }
    catch (const std::runtime_error& e) {
        std::cerr << "Error: " << e.what() << "\n";
    }
    catch (const std::exception& e) {
        std::cerr << "Error inesperat: " << e.what() << "\n";
    }

    std::cout << "Prem <Intro> per tornar al menu principal...\n";
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cin.get();
}

 