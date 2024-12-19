#include "CercadoraUsuari.h"
#include "ConnexioBD.hpp"

PassarellaUsuari CercadoraUsuari::cercaPerSobrenom(const std::string& sobrenom) {
    ConnexioBD& con = ConnexioBD::getInstance();
    std::string query = "SELECT * FROM usuari WHERE sobrenom = '" + sobrenom + "'";
    sql::ResultSet* res = con.consulta(query);

    if (!res->next()) {
        delete res;
        throw std::runtime_error("Usuari no existeix.");
    }

    PassarellaUsuari usuari(res->getString("sobrenom"), res->getString("nom"),
        res->getString("correu_electronic"), res->getString("contrasenya"),
        res->getString("data_naixement"), res->getString("subscripcio"));
    delete res;
    return usuari;
}

std::vector<PassarellaUsuari> CercadoraUsuari::cercaTots() {
    ConnexioBD& con = ConnexioBD::getInstance();
    std::string query = "SELECT * FROM usuari";
    sql::ResultSet* res = con.consulta(query);

    std::vector<PassarellaUsuari> usuaris;
    while (res->next()) {
        usuaris.emplace_back(res->getString("sobrenom"), res->getString("nom"),
            res->getString("correu_electronic"), res->getString("contrasenya"),
            res->getString("data_naixement"), res->getString("subscripcio"));
    }
    delete res;
    return usuaris;
}
