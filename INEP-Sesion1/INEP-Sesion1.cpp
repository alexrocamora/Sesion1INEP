#include <iostream>
#include <string>
using namespace std;

// Funció per registrar un usuari
void procesarRegistreUsuari() {
    string sobrenom, nomComplet;

    cout << "Introdueix el sobrenom: ";
    getline(cin >> ws, sobrenom);  // cin >> ws per eliminar espais en blanc abans de getline
    cout << "Introdueix el nom complet: ";
    getline(cin, nomComplet);

    if (sobrenom.empty() || nomComplet.empty()) {
        cout << "Error al registrar usuari.\n";
    }
    else {
        cout << "El registre de l'usuari " << nomComplet << " (" << sobrenom << ") s'ha processat correctament.\n";
    }
}

// Funció per consultar un usuari
void procesarConsultaUsuari() {
    cout << "Operacio de consulta de usuari processada.\n";
}

// Funció per modificar un usuari
void procesarModificaUsuari() {
    cout << "Operacio de modificacio de usuari processada.\n";
}

// Funció per esborrar un usuari
void procesarEsborraUsuari() {
    cout << "Operacio de esborrat de usuari processada.\n";
}

// Funció per gestionar pel·lícules
void procesarGestioPelicules() {
    cout << "Operacio de gestio de pelicules processada.\n";
}

// Funció per gestionar sèries
void procesarGestioSeries() {
    cout << "Operacio de gestio de series processada.\n";
}

// Funció per consultar per qualificació d'edat
void procesarConsultaPerQualificacio() {
    cout << "Operacio de consulta per qualificacio d'edat processada.\n";
}

// Funció per consultar últimes novetats
void procesarUltimesNovetats() {
    cout << "Operacio de consulta de les ultimes novetats processada.\n";
}

// Funció per consultar pròximes estrenes
void procesarProximesEstrenes() {
    cout << "Operacio de consulta de proximes estrenes processada.\n";
}

// Menú de gestió d'usuaris
void menuGestioUsuaris() {
    int opcio;
    do {
        cout << "1. Registre usuari\n";
        cout << "2. Consulta usuari\n";
        cout << "3. Modifica usuari\n";
        cout << "4. Esborra usuari\n";
        cout << "5. Tornar\n";
        cout << "Escull una opcio: ";
        cin >> opcio;

        switch (opcio) {
        case 1:
            procesarRegistreUsuari();
            break;
        case 2:
            procesarConsultaUsuari();
            break;
        case 3:
            procesarModificaUsuari();
            break;
        case 4:
            procesarEsborraUsuari();
            break;
        case 5:
            cout << "Tornant al menu principal...\n";
            break;
        default:
            cout << "Opcio invalida.\n";
            break;
        }
    } while (opcio != 5);
}

// Menú de gestió de continguts
void menuGestioContinguts() {
    int opcio;
    do {
        cout << "1. Gestio pelicules\n";
        cout << "2. Gestio series\n";
        cout << "3. Tornar\n";
        cout << "Escull una opcio: ";
        cin >> opcio;

        switch (opcio) {
        case 1:
            procesarGestioPelicules();
            break;
        case 2:
            procesarGestioSeries();
            break;
        case 3:
            cout << "Tornant al menu principal...\n";
            break;
        default:
            cout << "Opcio invalida.\n";
            break;
        }
    } while (opcio != 3);
}

// Menú de consultes
void menuConsultes() {
    int opcio;
    do {
        cout << "1. Consulta per qualificacio d'edat\n";
        cout << "2. Ultimes novetats\n";
        cout << "3. Proximes estrenes\n";
        cout << "4. Tornar\n";
        cout << "Escull una opcio: ";
        cin >> opcio;

        switch (opcio) {
        case 1:
            procesarConsultaPerQualificacio();
            break;
        case 2:
            procesarUltimesNovetats();
            break;
        case 3:
            procesarProximesEstrenes();
            break;
        case 4:
            cout << "Tornant al menu principal...\n";
            break;
        default:
            cout << "Opcio invalida.\n";
            break;
        }
    } while (opcio != 4);
}

int main() {
    int opcio;
    do {
        cout << "Menu Principal:\n";
        cout << "1. Gestio usuaris\n";
        cout << "2. Gestio continguts\n";
        cout << "3. Consultes\n";
        cout << "4. Sortir\n";
        cout << "Escull una opcio: ";
        cin >> opcio;

        switch (opcio) {
        case 1:
            menuGestioUsuaris();
            break;
        case 2:
            menuGestioContinguts();
            break;
        case 3:
            menuConsultes();
            break;
        case 4:
            cout << "Sortint de la aplicacio...\n";
            break;
        default:
            cout << "Opcio invalida. Torna a intentar-ho.\n";
            break;
        }
    } while (opcio != 4);

    return 0;
}
