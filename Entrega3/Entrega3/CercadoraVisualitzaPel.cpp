#include "CercadoraVisualitzaPel.h"
#include "ConnexioBD.hpp"

PassarellaVisualitzaPel CercadoraVisualitzaPel::cercaPerTitol(const std::string& titol) {
    ConnexioBD& connexio = ConnexioBD::getInstance();
    std::string sql =
        "SELECT pelicula.titol, contingut.descripcio, contingut.qualificacio AS qualificacio_edat, "
        "pelicula.duracio, pelicula.data_estrena "
        "FROM pelicula "
        "JOIN contingut ON pelicula.titol = contingut.titol "
        "WHERE pelicula.titol = '" + titol + "'";

    auto res = connexio.consulta(sql);

    if (res->next()) {
        return PassarellaVisualitzaPel(
            "",  // sobrenom (no relevante para esta consulta)
            res->getString("titol"),
            "",  // data (no relevante en esta consulta)
            0,   // num_visualitzacions (no relevante en esta consulta)
            res->getString("descripcio"),
            res->getInt("qualificacio_edat"),
            res->getInt("duracio"),
            res->getString("data_estrena")
        );
    }
    else {
        throw std::runtime_error("No s'ha trobat la pel·lícula.");
    }
}


int CercadoraVisualitzaPel::cercaNumVisualitzacions(const std::string& sobrenomUsuari) {
    ConnexioBD& connexio = ConnexioBD::getInstance();
    std::string sql =
        "SELECT SUM(num_visualitzacions) AS total "
        "FROM visualitzacio_pelicula "
        "WHERE sobrenom_usuari = '" + sobrenomUsuari + "'";

    auto res = connexio.consulta(sql);

    if (res->next() && !res->isNull("total")) {
        return res->getInt("total");
    }
    else {
        return 0;  // Si no hay visualizaciones, retorna 0
    }
}


std::vector<PassarellaVisualitzaPel> CercadoraVisualitzaPel::cercaTopVisualitzacions() {
    ConnexioBD& connexio = ConnexioBD::getInstance();
    std::string sql =
        "SELECT pelicula.titol, contingut.descripcio, contingut.qualificacio AS qualificacio_edat, "
        "pelicula.duracio, pelicula.data_estrena, "
        "SUM(visualitzacio_pelicula.num_visualitzacions) AS num_visualitzacions "
        "FROM visualitzacio_pelicula "
        "JOIN pelicula ON visualitzacio_pelicula.titol_pelicula = pelicula.titol "
        "JOIN contingut ON pelicula.titol = contingut.titol "
        "GROUP BY pelicula.titol "
        "ORDER BY num_visualitzacions DESC LIMIT 5";
     
    auto res = connexio.consulta(sql);

    std::vector<PassarellaVisualitzaPel> pelicules;
    while (res->next()) {
        pelicules.emplace_back(
            "",  // sobrenom (no relevante aquí)
            res->getString("titol"),
            "",  // data (no relevante aquí)
            res->getInt("num_visualitzacions"),
            res->getString("descripcio"),
            res->getInt("qualificacio_edat"),
            res->getInt("duracio"),
            res->getString("data_estrena")
        );
    }

    return pelicules;
}



std::vector<PassarellaVisualitzaPel> CercadoraVisualitzaPel::cercaVisualitzacionsPerUsuari(const std::string& sobrenomUsuari) {
    ConnexioBD& connexio = ConnexioBD::getInstance();
    std::string sql =
        "SELECT pelicula.titol, contingut.descripcio, contingut.qualificacio AS qualificacio_edat, "
        "pelicula.duracio, pelicula.data_estrena, visualitzacio_pelicula.data, "
        "SUM(visualitzacio_pelicula.num_visualitzacions) AS num_visualitzacions "
        "FROM visualitzacio_pelicula "
        "JOIN pelicula ON visualitzacio_pelicula.titol_pelicula = pelicula.titol "
        "JOIN contingut ON pelicula.titol = contingut.titol "
        "WHERE visualitzacio_pelicula.sobrenom_usuari = '" + sobrenomUsuari + "' "
        "GROUP BY pelicula.titol "
        "ORDER BY num_visualitzacions DESC";

    auto res = connexio.consulta(sql);

    std::vector<PassarellaVisualitzaPel> pelicules;
    while (res->next()) {
        pelicules.emplace_back(
            sobrenomUsuari,
            res->getString("titol"),
            res->getString("data"),
            res->getInt("num_visualitzacions"),
            res->getString("descripcio"),
            res->getInt("qualificacio_edat"),
            res->getInt("duracio"),
            res->getString("data_estrena")
        );
    }

    return pelicules;
}



PassarellaVisualitzaPel CercadoraVisualitzaPel::cercaPerTitolComplet(const std::string& titol) {
    ConnexioBD& connexio = ConnexioBD::getInstance();
    std::string sql =
        "SELECT pelicula.titol, contingut.descripcio, contingut.qualificacio AS qualificacio_edat, "
        "pelicula.duracio, pelicula.data_estrena, visualitzacio_pelicula.data, "
        "visualitzacio_pelicula.num_visualitzacions "
        "FROM visualitzacio_pelicula "
        "JOIN pelicula ON visualitzacio_pelicula.titol_pelicula = pelicula.titol "
        "JOIN contingut ON pelicula.titol = contingut.titol "
        "WHERE pelicula.titol = '" + titol + "'";

    auto res = connexio.consulta(sql);

    if (res->next()) {
        return PassarellaVisualitzaPel(
            "",  // sobrenom (no relevante para esta consulta)
            res->getString("titol"),
            res->getString("data"),
            res->getInt("num_visualitzacions"),
            res->getString("descripcio"),
            res->getInt("qualificacio_edat"),
            res->getInt("duracio"),
            res->getString("data_estrena")
        );
    }
    else {
        throw std::runtime_error("La pelicula no existeix.");
    }
}

void CercadoraVisualitzaPel::registraVisualitzacio(const std::string& sobrenomUsuari, const std::string& titol, const std::string& data) {
    ConnexioBD& connexio = ConnexioBD::getInstance();
    std::string sql =
        "INSERT INTO visualitzacio_pelicula (sobrenom_usuari, titol_pelicula, data, num_visualitzacions) "
        "VALUES ('" + sobrenomUsuari + "', '" + titol + "', '" + data + "', 1) "
        "ON DUPLICATE KEY UPDATE num_visualitzacions = num_visualitzacions + 1";
    connexio.executa(sql);
}




