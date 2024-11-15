#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include "ConnexioBD.hpp"

using namespace std;

// Llegir credencials 
void dbConfig(const string& path, string& host, string& user, string& password, string& database) {
    ifstream fitxer(path);
    if (!fitxer) {
        cerr << "No s'ha trobat el fitxer de configuració." << endl;
        exit(1);
    }

    string line;
    while (getline(fitxer, line)) {
        istringstream iss(line);
        string clau, valor;
        if (getline(iss, clau, '=') && getline(iss, valor)) {
            if (clau == "host") host = valor;
            else if (clau == "user") user = valor;
            else if (clau == "password") password = valor;
            else if (clau == "database") database = valor;
        }
    }

    fitxer.close();
}

// Funció per a evitar SQL Injection
string escape_string(const string& input) {
    string result = "";
    for (char c : input) {
        if (c == '\\') { 
            result += "\\\\";
        } else if (c == '\'') {
            result += "\\\'";
        } else if (c == '\"') {
            result += "\\\"";
        } else {
            result += c;
        }
    }

    return result;
}

void registre_usuari(ConnexioBD& connexio) {
	string sobrenom;
	cout << "Sobrenom: ";
	cin >> sobrenom;
    string nom;
    cout << "Nom: ";
    cin >> nom;
    string correu;
    cout << "Correu electrònic: ";
    cin >> correu;
    cout << endl;

    try {
        string sql = "INSERT INTO Usuari (sobrenom, nom, correu_electronic) VALUES ('" + escape_string(sobrenom) + "', '" + escape_string(nom) + "', '" + escape_string(correu) + "')";
        connexio.executa(sql);
        cout << "Registre realitzat correctament" << endl;
        cout << endl;
    } catch (sql::SQLException& e) {
        cerr << "SQL Error: " << e.what() << endl;
        registre_usuari(connexio);
    }	
}

void consulta_usuari(ConnexioBD& connexio) {
    string sobrenom;
	cout << "Sobrenom: ";
	cin >> sobrenom;
    cout << endl;
    try {
        string sql = "SELECT * FROM Usuari WHERE sobrenom='" + sobrenom + "'";
        sql::ResultSet* res = connexio.consulta(sql);
        if (res->next()) {
            cout << "Sobrenom: " << res->getString("sobrenom") << endl;
            cout << "Nom: " << res->getString("nom") << endl;
            cout << "Correu: " << res->getString("correu_electronic") << endl;
            cout << endl;
        } else {
            cout << "No s'ha trobat cap usuari amb aquest sobrenom." << endl;
            cout << endl;
        }
    } catch (sql::SQLException& e) {
        cerr << "SQL Error: " << e.what() << endl;
    }
}

void modifica_usuari(ConnexioBD& connexio) {
    string sobrenom;
	cout << "Sobrenom: ";
	cin >> sobrenom;
    cout << endl;
    try {
        string sql = "SELECT * FROM Usuari WHERE sobrenom='" + sobrenom + "'";
        sql::ResultSet* res = connexio.consulta(sql);
        if (res->next()) {
            string nom;
            cout << "Nom nou: ";
            cin >> nom;
            string correu;
            cout << "Correu electrònic nou: ";
            cin >> correu;
            sql = "UPDATE Usuari set nom='" + escape_string(nom) + "', correu_electronic='" + escape_string(correu) + "' WHERE sobrenom='" + sobrenom + "'";
            connexio.executa(sql);
            cout << "Usuari " << sobrenom << " modificat correctament." << endl;
            cout << endl;
        } else {
            cout << "No s'ha trobat cap usuari amb aquest sobrenom." << endl;
            cout << endl;
        }
    } catch (sql::SQLException& e) {
        cerr << "SQL Error: " << e.what() << endl;
    }
}

void esborra_usuari(ConnexioBD& connexio) {
    string sobrenom;
	cout << "Sobrenom: ";
	cin >> sobrenom;
    cout << endl;
    try {
        string sql = "SELECT * FROM Usuari WHERE sobrenom='" + sobrenom + "'";
        sql::ResultSet* res = connexio.consulta(sql);
        if (res->next()) {
            sql = "DELETE FROM Usuari WHERE sobrenom='" + sobrenom + "'";
            connexio.executa(sql);
            cout << "Usuari " << sobrenom << " eliminat correctament." << endl;
            cout << endl;
        } else {
            cout << "No s'ha trobat cap usuari amb aquest sobrenom." << endl;
            cout << endl;
        }
    } catch (sql::SQLException& e) {
        cerr << "SQL Error: " << e.what() << endl;
    }
}

void gestio_pelicules(ConnexioBD& connexio) {
    cout << "---------------------------------------------------" << endl;
    cout << "S'han gestionat les pel·lícules correctament" << endl;
    cout << "---------------------------------------------------" << endl;
	cout << endl;
}

void gestio_series(ConnexioBD& connexio) {
    cout << "---------------------------------------------------" << endl;
    cout << "S'han gestionat les sèries correctament" << endl;
    cout << "---------------------------------------------------" << endl;
	cout << endl;
}

void consulta_qualificacio_edat(ConnexioBD& connexio) {
    cout << "---------------------------------------------------" << endl;
    cout << "S'ha consultat la qualificació d'edat correctament" << endl;
    cout << "---------------------------------------------------" << endl;
	cout << endl;
}

void ultimes_novetats(ConnexioBD& connexio) {
    cout << "---------------------------------------------------" << endl;
    cout << "S'han consultat les últimes novetats correctament" << endl;
    cout << "---------------------------------------------------" << endl;
	cout << endl;
}

void proximes_estrenes(ConnexioBD& connexio) {
    cout << "---------------------------------------------------" << endl;
    cout << "S'han consultat les pròximes estrenes correctament" << endl;
    cout << "---------------------------------------------------" << endl;
	cout << endl;
}

void gestio_usuari(ConnexioBD& connexio) {
	while (true) {
		cout << "1. Registre usuari" << endl;
		cout << "2. Consulta usuari" << endl;
		cout << "3. Modifica usuari" << endl;
		cout << "4. Esborra usuari" << endl;
		cout << "5. Tornar" << endl;
		cout << endl;

		int op1;
		cout << "Sel·leccioni una opció: ";
		cin >> op1;
        cout << endl;

		switch (op1) {
		case 1:
			registre_usuari(connexio);
			break;
		case 2:
			consulta_usuari(connexio);
			break;
		case 3:
			modifica_usuari(connexio);
			break;
		case 4:
			esborra_usuari(connexio);
			break;
		case 5:
			break;
		default:
			cout << "Opció incorrecta" << endl;
			cout << endl;
			continue;
		}
		break;
	}
}

void gestio_continguts(ConnexioBD& connexio) {
	while (true) {
		cout << "1. Gestió pel·lícules" << endl;
		cout << "2. Gestió sèries" << endl;
		cout << "3. Tornar" << endl;
		cout << endl;

		int op2;
		cout << "Sel·leccioni una opció: ";
		cin >> op2;
        cout << endl;

		switch (op2) {
		case 1:
			gestio_pelicules(connexio);
			break;
		case 2:
			gestio_series(connexio);
			break;
		case 3:
			break;
		default:
			cout << "Opció incorrecta" << endl;
			cout << endl;
			continue;
		}
		break;
	}
}

void consultes(ConnexioBD& connexio) {
	while (true) {
		cout << "1. Consulta per qualificació d'edat" << endl;
		cout << "2. Últimes novetats" << endl;
		cout << "3. Pròximes estrenes" << endl;
		cout << "4. Tornar" << endl;
		cout << endl;

		int op3;
		cout << "Sel·leccioni una opció: ";
		cin >> op3;
        cout << endl;

		switch (op3) {
		case 1:
			consulta_qualificacio_edat(connexio);
			break;
		case 2:
			ultimes_novetats(connexio);
			break;
		case 3:
			proximes_estrenes(connexio);
			break;
		case 4:
			break;
		default:
			cout << "Opció incorrecta" << endl;
			cout << endl;
			continue;
		}
		break;
	}
}

int main() {
    string host, user, password, database;
    dbConfig("config.txt", host, user, password, database);

    try {
        ConnexioBD connexio(host, user, password, database);

        while (true) {
            cout << "1. Gestió usuaris" << endl;
            cout << "2. Gestió continguts" << endl;
            cout << "3. Consultes" << endl;
            cout << "4. Sortir" << endl;
            cout << endl;

            int op;
            cout << "Sel·leccioni una opció: ";
            cin >> op;
            cout << endl;

            switch (op) {
            case 1:
                gestio_usuari(connexio);
                break;
            case 2:
                gestio_continguts(connexio);
                break;
            case 3:
                consultes(connexio);
                break;
            case 4:
                exit(0);
            default:
                cout << "Opció incorrecta" << endl;
                cout << endl;
            }
        }
    } catch (sql::SQLException& e) {
        cerr << "SQL Error: " << e.what() << endl;
    }
}
