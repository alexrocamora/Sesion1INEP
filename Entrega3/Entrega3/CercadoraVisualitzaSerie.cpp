#include "CercadoraVisualitzaSerie.h"
#include "ConnexioBD.hpp"

PassarellaVisualitzaSerie CercadoraVisualitzaSerie::cercaPerTitol(const std::string& titolSerie, int temporada, int capitol) {
    ConnexioBD& connexio = ConnexioBD::getInstance();
    std::string sql =
        "SELECT vc.sobrenom_usuari, vc.titol_serie, vc.num_temporada, vc.num_capitol, vc.data, "
        "vc.num_visualitzacions, c.titol AS titol_capitol, c.data_estrena, c.qualificacio "
        "FROM visualitzacio_capitol vc "
        "JOIN capitol c ON vc.titol_serie = c.titol_serie AND vc.num_temporada = c.numero_temporada AND vc.num_capitol = c.numero "
        "WHERE vc.titol_serie = '" + titolSerie + "' AND vc.num_temporada = " + std::to_string(temporada) +
        " AND vc.num_capitol = " + std::to_string(capitol);

    auto res = connexio.consulta(sql);

    if (res->next()) {
        return PassarellaVisualitzaSerie( 
            res->getString("sobrenom_usuari"),
            res->getString("titol_serie"),
            res->getInt("num_temporada"),
            res->getInt("num_capitol"),
            res->getString("data"),
            res->getInt("num_visualitzacions"),
            res->getString("titol_capitol"),
            res->getString("data_estrena"),
            res->getInt("qualificacio")
        );

    }
    else {
        throw std::runtime_error("No s'ha trobat el capitol.");
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
    std::string sql =
        "SELECT vc.titol_serie, vc.num_temporada, vc.num_capitol, SUM(vc.num_visualitzacions) AS num_visualitzacions, "
        "c.titol AS titol_capitol, c.data_estrena, c.qualificacio "
        "FROM visualitzacio_capitol vc "
        "JOIN capitol c ON vc.titol_serie = c.titol_serie AND vc.num_temporada = c.numero_temporada AND vc.num_capitol = c.numero "
        "GROUP BY vc.titol_serie, vc.num_temporada, vc.num_capitol "
        "ORDER BY num_visualitzacions DESC LIMIT 5";
    auto res = connexio.consulta(sql);

    std::vector<PassarellaVisualitzaSerie> series;
    while (res->next()) {
        series.emplace_back( 
            "",  // sobrenom no está en este contexto
            res->getString("titol_serie"),
            res->getInt("num_temporada"),
            res->getInt("num_capitol"),
            "",  // data no relevante aquí
            res->getInt("num_visualitzacions"),
            res->getString("titol_capitol"),
            res->getString("data_estrena"),
            res->getInt("qualificacio")
        );
    }

    return series;
}

std::vector<PassarellaVisualitzaSerie> CercadoraVisualitzaSerie::cercaVisualitzacionsPerUsuari(const std::string& sobrenomUsuari) {
    ConnexioBD& connexio = ConnexioBD::getInstance();
    std::string sql =
        "SELECT vc.titol_serie, vc.num_temporada, vc.num_capitol, SUM(vc.num_visualitzacions) AS num_visualitzacions, "
        "c.titol AS titol_capitol, c.data_estrena, c.qualificacio "
        "FROM visualitzacio_capitol vc "
        "JOIN capitol c ON vc.titol_serie = c.titol_serie AND vc.num_temporada = c.numero_temporada AND vc.num_capitol = c.numero "
        "WHERE vc.sobrenom_usuari = '" + sobrenomUsuari + "' "
        "GROUP BY vc.titol_serie, vc.num_temporada, vc.num_capitol "
        "ORDER BY num_visualitzacions DESC";
    auto res = connexio.consulta(sql);

    std::vector<PassarellaVisualitzaSerie> series;
    while (res->next()) {
        series.emplace_back(
            sobrenomUsuari,
            res->getString("titol_serie"),
            res->getInt("num_temporada"),
            res->getInt("num_capitol"),
            "",  // data no relevante aquí
            res->getInt("num_visualitzacions"),
            res->getString("titol_capitol"),
            res->getString("data_estrena"),
            res->getInt("qualificacio")
        );
    }

    return series;
}

std::vector<int> CercadoraVisualitzaSerie::obteTemporades(const std::string& titolSerie) { 
    ConnexioBD& connexio = ConnexioBD::getInstance();
    std::string sql = "SELECT numero FROM temporada WHERE titol_serie = '" + titolSerie + "'";
    auto res = connexio.consulta(sql);

    std::vector<int> temporades;
    while (res->next()) {
        temporades.push_back(res->getInt("numero"));
    }

    if (temporades.empty()) {
        throw std::runtime_error("No s'han trobat temporades per a la serie indicada.");
    }

    return temporades;
}

std::vector<PassarellaVisualitzaSerie> CercadoraVisualitzaSerie::obteCapitols(const std::string& titolSerie, int numTemporada) {
    ConnexioBD& connexio = ConnexioBD::getInstance();
    std::string sql =
        "SELECT c.numero, c.titol AS titol_capitol, c.data_estrena, c.qualificacio "
        "FROM capitol c "
        "WHERE c.titol_serie = '" + titolSerie + "' AND c.numero_temporada = " + std::to_string(numTemporada);
    auto res = connexio.consulta(sql);

    std::vector<PassarellaVisualitzaSerie> capitols;
    while (res->next()) {
        capitols.emplace_back(
            "",  // sobrenom no está en este contexto
            titolSerie,
            numTemporada,
            res->getInt("numero"),
            "",  // data no relevante aquí
            0,   // num_visualitzacions no relevante aquí
            res->getString("titol_capitol"),
            res->getString("data_estrena"),
            res->getInt("qualificacio")
        );
    }

    if (capitols.empty()) {
        throw std::runtime_error("No s'han trobat capitols per a la temporada indicada.");
    }

    return capitols;
}

std::vector<std::string> CercadoraVisualitzaSerie::cercaSeriesRelacionades(const std::string& titolSerie) {
    ConnexioBD& connexio = ConnexioBD::getInstance();

    // Consulta SQL para encontrar las series relacionadas
    std::string sql =
        "SELECT DISTINCT "
        "CASE WHEN r.titol_x = '" + titolSerie + "' THEN r.titol_y ELSE r.titol_x END AS serieRelacionada "
        "FROM relacionat r "
        "WHERE r.titol_x = '" + titolSerie + "' OR r.titol_y = '" + titolSerie + "'";

    auto res = connexio.consulta(sql);

    std::vector<std::string> seriesRelacionades;
    while (res->next()) {
        seriesRelacionades.push_back(res->getString("serieRelacionada"));
    }

    return seriesRelacionades;
}

// Nueva función para registrar visualización
void CercadoraVisualitzaSerie::registraVisualitzacio(const std::string& sobrenom,
    const std::string& titolSerie,
    int temporada, int capitol) {
    ConnexioBD& connexio = ConnexioBD::getInstance();

    std::string sql = "INSERT INTO visualitzacio_capitol (sobrenom_usuari, titol_serie, num_temporada, num_capitol, data, num_visualitzacions) "
        "VALUES ('" + sobrenom + "', '" + titolSerie + "', " + std::to_string(temporada) + ", " +
        std::to_string(capitol) + ", CURDATE(), 1) "
        "ON DUPLICATE KEY UPDATE num_visualitzacions = num_visualitzacions + 1";

    connexio.executa(sql); 
}


