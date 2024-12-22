#include "ConnexioBD.hpp"
#include <fstream>
#include <sstream>
#include <iostream>

ConnexioBD::ConnexioBD() {
    inicialitzaConnexio();
}

ConnexioBD::~ConnexioBD() {
    if (con) {
        con->close();
        delete con;
    }
}

ConnexioBD& ConnexioBD::getInstance() {
    static ConnexioBD instance;
    return instance;
}

void ConnexioBD::inicialitzaConnexio() {
    std::ifstream config("config.txt");
    if (!config) {
        throw std::runtime_error("Error al obrir el fitxer de configuraci�.");
    }

    std::string host, user, pass, db;
    std::string line;
    while (std::getline(config, line)) {
        std::istringstream iss(line);
        std::string key, value;
        if (std::getline(iss, key, '=') && std::getline(iss, value)) {
            if (key == "host") host = value;
            else if (key == "user") user = value;
            else if (key == "password") pass = value;
            else if (key == "database") db = value;
        }
    }

    driver = sql::mysql::get_mysql_driver_instance();
    con = driver->connect(host, user, pass);
    con->setSchema(db);
}

sql::ResultSet* ConnexioBD::consulta(const std::string& sql) {
    sql::Statement* stmt = con->createStatement();
    return stmt->executeQuery(sql);
}

void ConnexioBD::executa(const std::string& sql) {
    sql::Statement* stmt = con->createStatement();
    stmt->execute(sql);
}
