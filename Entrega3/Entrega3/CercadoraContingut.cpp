#include "CercadoraContingut.h"
#include "ConnexioBD.hpp"

std::vector<PassarellaProperesEstrenes> CercadoraContingut::cercaProperesEstrenes(const std::string& subscripcio) {
    ConnexioBD& connexio = ConnexioBD::getInstance();
    if (subscripcio == "Completa") {
        std::string sql = 
            "SELECT pelicula.titol, pelicula.data_estrena, contingut.qualificacio AS qualificacio_edat, "
            "pelicula.duracio, contingut.tipus "
            "FROM pelicula "
            "JOIN contingut ON pelicula.titol = contingut.titol "
            "WHERE pelicula.data_estrena > CURDATE() "

            "UNION "

            "SELECT capitol.titol_serie AS titol, MIN(capitol.data_estrena) AS data_estrena, contingut.qualificacio AS qualificacio_edat, " 
            "temporada.numero AS duracio, contingut.tipus "
            "FROM capitol "
            "JOIN temporada ON capitol.titol_serie = temporada.titol_serie AND capitol.numero_temporada = temporada.numero "
            "JOIN contingut ON capitol.titol_serie = contingut.titol "
            "WHERE capitol.data_estrena > CURDATE() "
            "GROUP BY capitol.titol_serie, temporada.numero, contingut.qualificacio, contingut.tipus "

            "ORDER BY data_estrena ASC";

        auto res = connexio.consulta(sql);
        std::vector<PassarellaProperesEstrenes> contingut;
        while(res->next()) {
            contingut.emplace_back(
                res->getString("titol"),
                res->getString("data_estrena"),
                res->getString("qualificacio_edat"),
                res->getInt("duracio"),
                res->getString("tipus")
            );
        }

        return contingut;

    } else if (subscripcio == "Cinefil") {
        std::string sql = 
            "SELECT pelicula.titol, pelicula.data_estrena, contingut.qualificacio AS qualificacio_edat, "
            "pelicula.duracio, contingut.tipus "
            "FROM pelicula JOIN contingut ON pelicula.titol = contingut.titol "
            "AND pelicula.data_estrena > CURDATE()"
            "ORDER BY data_estrena ASC";
        
        auto res = connexio.consulta(sql);
        std::vector<PassarellaProperesEstrenes> contingut;
        while(res->next()) {
            contingut.emplace_back(
                res->getString("titol"),
                res->getString("data_estrena"),
                res->getString("qualificacio_edat"),
                res->getInt("duracio"),
                res->getString("tipus")
            );
        }

        return contingut;

    } else if (subscripcio == "Infantil") {
        std::string sql = 
            "SELECT pelicula.titol, pelicula.data_estrena, contingut.qualificacio AS qualificacio_edat, "
            "pelicula.duracio, contingut.tipus "
            "FROM pelicula "
            "JOIN contingut ON pelicula.titol = contingut.titol "
            "WHERE pelicula.data_estrena > CURDATE() "
            "AND (contingut.qualificacio = '7+' OR contingut.qualificacio = '12+' OR contingut.qualificacio = 'TP')"

            "UNION "

            "SELECT capitol.titol_serie AS titol, MIN(capitol.data_estrena) AS data_estrena, contingut.qualificacio AS qualificacio_edat, " 
            "temporada.numero AS duracio, contingut.tipus "
            "FROM capitol "
            "JOIN temporada ON capitol.titol_serie = temporada.titol_serie AND capitol.numero_temporada = temporada.numero "
            "JOIN contingut ON capitol.titol_serie = contingut.titol "
            "WHERE capitol.data_estrena > CURDATE() "
            "AND (contingut.qualificacio = '7+' OR contingut.qualificacio = '12+' OR contingut.qualificacio = 'TP') "
            "GROUP BY capitol.titol_serie, temporada.numero, contingut.qualificacio, contingut.tipus "

            "ORDER BY data_estrena ASC";

        auto res = connexio.consulta(sql);
        std::vector<PassarellaProperesEstrenes> contingut;
        while(res->next()) {
            contingut.emplace_back(
                res->getString("titol"),
                res->getString("data_estrena"),
                res->getString("qualificacio_edat"),
                res->getInt("duracio"),
                res->getString("tipus")
            );
        }

        return contingut;

    } else {
        throw std::runtime_error("No s'ha trobat la modalitat de subscripcio.");
    }
}