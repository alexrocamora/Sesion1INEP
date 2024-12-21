#include "CercadoraVisualitzaSerie.h"
#include "ConnexioBD.hpp"

PassarellaVisualitzaSerie CercadoraVisualitzaSerie::cercaPerTitol(const std::string& titolSerie, int temporada, int capitol) {
    ConnexioBD& connexio = ConnexioBD::getInstance();
    std::string sql = "SELECT * FROM visualitzacio_capitol WHERE titol_serie = '" + titolSerie +
        "' AND num_temporada = " + std::to_string(temporada) +
        " AND num_capitol = " + std::to_string(capitol);
    auto res = connexio.consulta(sql);

    if (res->next()) {
        return PassarellaVisualitzaSerie(res->getString("sobrenom_usuari"),
            res->getString("titol_serie"),
            res->getInt("num_temporada"),
            res->getInt("num_capitol"),
            res->getString("data"),
            res->getInt("num_visualitzacions"));
    }
    else {
        throw std::runtime_error("No s'ha trobat el capítol.");
    }
}

int CercadoraVisualitzaSerie::cercaNumVisualitzacions(const std::string& sobrenomUsuari) {
    ConnexioBD& connexio = ConnexioBD::getInstance();
    std::string sql = "SELECT SUM(num_visualitzacions) AS total FROM visualitzacio_capitol WHERE sobrenom_usuari = '" + sobrenomUsuari + "'";
    auto res = connexio.consulta(sql);

    if (res->next()) {
        return res->getInt("total");
    }
    else {
        return 0;
    }
}

std::vector<PassarellaVisualitzaSerie> CercadoraVisualitzaSerie::cercaTopVisualitzacions() {
    ConnexioBD& connexio = ConnexioBD::getInstance();
    std::string sql = "SELECT titol_serie, num_temporada, num_capitol, SUM(num_visualitzacions) AS num_visualitzacions "
        "FROM visualitzacio_capitol "
        "GROUP BY titol_serie, num_temporada, num_capitol "
        "ORDER BY num_visualitzacions DESC LIMIT 5";
    auto res = connexio.consulta(sql);

    std::vector<PassarellaVisualitzaSerie> series;
    while (res->next()) {
        series.emplace_back("", res->getString("titol_serie"), res->getInt("num_temporada"),
            res->getInt("num_capitol"), "", res->getInt("num_visualitzacions"));
    }

    return series;
}
