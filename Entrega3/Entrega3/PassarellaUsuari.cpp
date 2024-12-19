#include "PassarellaUsuari.h"
#include "ConnexioBD.hpp"

PassarellaUsuari::PassarellaUsuari(const std::string& sobrenom, const std::string& nom,
    const std::string& correu, const std::string& contrasenya,
    const std::string& dataNaixement, const std::string& modalitatSubscripcio)
    : sobrenom(sobrenom), nom(nom), correuElectronic(correu), contrasenya(contrasenya),
    dataNaixement(dataNaixement), modalitatSubscripcio(modalitatSubscripcio) {}

void PassarellaUsuari::insereix() {
    ConnexioBD& con = ConnexioBD::getInstance();
    std::string query = "INSERT INTO usuari (sobrenom, nom, correu_electronic, contrasenya, data_naixement, subscripcio) "
        "VALUES ('" + sobrenom + "', '" + nom + "', '" + correuElectronic + "', '" + contrasenya + "', '" +
        dataNaixement + "', '" + modalitatSubscripcio + "')";
    con.executa(query);
}

void PassarellaUsuari::modifica() {
    ConnexioBD& con = ConnexioBD::getInstance();
    std::string query = "UPDATE usuari SET nom = '" + nom + "', correu_electronic = '" + correuElectronic +
        "', contrasenya = '" + contrasenya + "', data_naixement = '" + dataNaixement +
        "', subscripcio = '" + modalitatSubscripcio + "' WHERE sobrenom = '" + sobrenom + "'";
    con.executa(query);
}

void PassarellaUsuari::esborra() {
    ConnexioBD& con = ConnexioBD::getInstance();
    std::string query = "DELETE FROM usuari WHERE sobrenom = '" + sobrenom + "'";
    con.executa(query);
}

// Métodos "obte" y "posa"
std::string PassarellaUsuari::obteSobrenom() const { return sobrenom; }
void PassarellaUsuari::posaSobrenom(const std::string& sobrenom) { this->sobrenom = sobrenom; }

std::string PassarellaUsuari::obteNom() const { return nom; }
void PassarellaUsuari::posaNom(const std::string& nom) { this->nom = nom; }

std::string PassarellaUsuari::obteCorreuElectronic() const { return correuElectronic; }
void PassarellaUsuari::posaCorreuElectronic(const std::string& correu) { this->correuElectronic = correu; }

std::string PassarellaUsuari::obteContrasenya() const { return contrasenya; }
void PassarellaUsuari::posaContrasenya(const std::string& contrasenya) { this->contrasenya = contrasenya; }

std::string PassarellaUsuari::obteDataNaixement() const { return dataNaixement; }
void PassarellaUsuari::posaDataNaixement(const std::string& dataNaixement) { this->dataNaixement = dataNaixement; }

std::string PassarellaUsuari::obteModalitatSubscripcio() const { return modalitatSubscripcio; }
void PassarellaUsuari::posaModalitatSubscripcio(const std::string& modalitatSubscripcio) { this->modalitatSubscripcio = modalitatSubscripcio; }
