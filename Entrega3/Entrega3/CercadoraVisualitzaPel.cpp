#include "CercadoraVisualitzaPel.h"
#include "ConnexioBD.hpp"

PassarellaVisualitzaPel CercadoraVisualitzaPel::cercaPerTitol(const std::string& titol) {
    ConnexioBD& connexio = ConnexioBD::getInstance();
    std::string sql = "SELECT * FROM visualitzacio_pelicula WHERE titol_pelicula = '" + titol + "'";
    auto res = connexio.consulta(sql);

    if (res->next()) {
        return PassarellaVisualitzaPel(res->getString("sobrenom_usuari"),
            res->getString("titol_pelicula"),
            res->getString("data"),
            res->getInt("num_visualitzacions"));
    }
    else {
        throw std::runtime_error("No s'ha trobat la pel·lícula.");
    }
}

int CercadoraVisualitzaPel::cercaNumVisualitzacions(const std::string& sobrenomUsuari) {
    ConnexioBD& connexio = ConnexioBD::getInstance();
    std::string sql = "SELECT SUM(num_visualitzacions) AS total FROM visualitzacio_pelicula WHERE sobrenom_usuari = '" + sobrenomUsuari + "'";
    auto res = connexio.consulta(sql);

    if (res->next()) {
        return res->getInt("total");
    }
    else {
        return 0;
    }
}

std::vector<PassarellaVisualitzaPel> CercadoraVisualitzaPel::cercaTopVisualitzacions() {
    ConnexioBD& connexio = ConnexioBD::getInstance();
    std::string sql = "SELECT titol_pelicula, SUM(num_visualitzacions) AS num_visualitzacions "
        "FROM visualitzacio_pelicula "
        "GROUP BY titol_pelicula "
        "ORDER BY num_visualitzacions DESC LIMIT 5";
    auto res = connexio.consulta(sql);

    std::vector<PassarellaVisualitzaPel> pelicules;
    while (res->next()) {
        pelicules.emplace_back("", res->getString("titol_pelicula"), "", res->getInt("num_visualitzacions"));
    }

    return pelicules;
}
