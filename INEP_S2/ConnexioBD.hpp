#ifndef _CONNEXIO_BD_HPP
#define _CONNEXIO_BD_HPP

#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/statement.h>
#include <cppconn/resultset.h>
#include <mysql_driver.h>
#include <string>

using namespace std;

class ConnexioBD {
public:
    ConnexioBD(const string& host, const string& user, const string& pass, const string& db);
    ~ConnexioBD();

    sql::ResultSet* consulta(const string& sql);
    void executa(const string& sql);

private:
    sql::mysql::MySQL_Driver* driver;
    sql::Connection* con;
};

#endif