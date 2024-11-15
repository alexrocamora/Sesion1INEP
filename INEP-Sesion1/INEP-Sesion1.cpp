// Repositori de: Alex Rocamora

#include <iostream>
#include <string>
#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/statement.h>
#include <mysql_connection.h>
#include <mysql_driver.h>

using namespace std;

// Funció per registrar un usuari
void RegistreUsuari() {
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
void ConsultaUsuari() {
    sql::mysql::MySQL_Driver* driver = NULL;
    sql::Connection* con = NULL;
    sql::Statement* stmt = NULL;
    try {
        driver = sql::mysql::get_mysql_driver_instance();
        con = driver->connect("ubiwan.epsevg.upc.edu:3306", "inep20", "xahquoh2eeBieK");
        con->setSchema("inep20");
        stmt = con->createStatement();
        // Sentència SQL per obtenir totes les files de la taula usuari.
        // S’ha de posar el nom de la taula tal i com el teniu a la base
        // de dades respectant minúscules i majúscules
        string sql = "SELECT * FROM Usuari";
        sql::ResultSet* res = stmt->executeQuery(sql);
        // Bucle per recórrer les dades retornades mostrant les dades de cada fila
        while (res->next()) {
            // a la funció getString es fa servir el nom de la columna de la taula
            cout << "Sobrenom: " << res->getString("sobrenom") << endl;
            cout << "Nom: " << res->getString("nom") << endl;
            cout << "Correu: " << res->getString("correu_electronic") << endl;
        }
        con->close();
    }
    catch (sql::SQLException& e) {
        std::cerr << "SQL Error: " << e.what() << std::endl;
        // si hi ha un error es tanca la connexió (si esta oberta)
        if (con != NULL) con->close();
    }
    //cout << "Operacio de consulta de usuari processada.\n";
}

// Funció per modificar un usuari
void ModificaUsuari() {
    cout << "Operacio de modificacio de usuari processada.\n";
}

// Funció per esborrar un usuari
void EsborraUsuari() {
    cout << "Operacio de esborrat de usuari processada.\n";
}

// Funció per registrar pel·lícules
void RegistrePelicula() {
    cout << "Operacio de registre de pelicules processada.\n";
}

// Funció per consultar una pel·licula
void ConsultaPelis() {
    cout << "Operacio de consulta de pelicules processada.\n";
}

// Funció per modificar una pel·licula
void ModificaPelis() {
    cout << "Operacio de modificacio de pelicules processada.\n";
}

// Funció per esborrar una pel·licula
void EsborraPelis() {
    cout << "Operacio d'esborrat de pelicules processada.\n";
}

// Funció per gestionar pel·lícules
void GestioPelicules() {
    int opcio;
    do {
        cout << "1. Registre pelicules\n";
        cout << "2. Consulta pelicules\n";
        cout << "3. Modifica pelicules\n";
        cout << "4. Esborra pelicules\n";
        cout << "5. Tornar\n";
        cout << "Escull una opcio: ";
        cin >> opcio;

        switch (opcio) {
        case 1:
            RegistrePelicula();
            break;
        case 2:
            ConsultaPelis();
            break;
        case 3:
            ModificaPelis();
            break;
        case 4:
            EsborraPelis();
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

// Funció per registrar series
void RegistreSeries() {
    cout << "Operacio de registre de series processada.\n";
}

// Funció per consultar una series
void ConsultaSeries() {
    cout << "Operacio de consulta de series processada.\n";
}

// Funció per modificar una series
void ModificaSeries() {
    cout << "Operacio de modificacio de series processada.\n";
}

// Funció per esborrar una series
void EsborraSeries() {
    cout << "Operacio d'esborrat de series processada.\n";
}

// Funció per gestionar sèries
void GestioSeries() {
    int opcio;
    do {
        cout << "1. Registre series\n";
        cout << "2. Consulta series\n";
        cout << "3. Modifica series\n";
        cout << "4. Esborra series\n";
        cout << "5. Tornar\n";
        cout << "Escull una opcio: ";
        cin >> opcio;

        switch (opcio) {
        case 1:
            RegistreSeries();
            break;
        case 2:
            ConsultaSeries();
            break;
        case 3:
            ModificaSeries();
            break;
        case 4:
            EsborraSeries();
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

// Funció per consultar per qualificació d'edat
void ConsultaPerQualificacio() {
    cout << "Operacio de consulta per qualificacio d'edat processada.\n";
}

// Funció per consultar últimes novetats
void UltimesNovetats() {
    cout << "Operacio de consulta de les ultimes novetats processada.\n";
}

// Funció per consultar pròximes estrenes
void ProximesEstrenes() {
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
            RegistreUsuari();
            break;
        case 2:
            ConsultaUsuari();
            break;
        case 3:
            ModificaUsuari();
            break;
        case 4:
            EsborraUsuari();
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
            GestioPelicules();
            break;
        case 2:
            GestioSeries();
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
            ConsultaPerQualificacio();
            break;
        case 2:
            UltimesNovetats();
            break;
        case 3:
            ProximesEstrenes();
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

// Linia modificada per Roger Hurtado