#ifndef _CONNEXIO_BD_HPP
#define _CONNEXIO_BD_HPP

#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/statement.h>
#include <cppconn/resultset.h>
#include <mysql_driver.h>
#include <string>

class ConnexioBD {
public:
    static ConnexioBD& getInstance();

    sql::ResultSet* consulta(const std::string& sql);
    void executa(const std::string& sql);

private:
    ConnexioBD();
    ~ConnexioBD();
    ConnexioBD(const ConnexioBD&) = delete;
    ConnexioBD& operator=(const ConnexioBD&) = delete;

    sql::mysql::MySQL_Driver* driver;
    sql::Connection* con;

    void inicialitzaConnexio();
};

#endif
