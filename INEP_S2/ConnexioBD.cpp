#include "ConnexioBD.hpp"

ConnexioBD::ConnexioBD(const string& host, const string& user, const string& pass, const string& db) {
    driver = sql::mysql::get_mysql_driver_instance();
    con = driver->connect(host, user, pass);
    con->setSchema(db);
}

ConnexioBD::~ConnexioBD() {
    if (con) {
        con->close();
        delete con;
    }
}

sql::ResultSet* ConnexioBD::consulta(const string& sql) {
    sql::Statement* stmt = con->createStatement();
    return stmt->executeQuery(sql);
}

void ConnexioBD::executa(const string& sql) {
    sql::Statement* stmt = con->createStatement();
    stmt->execute(sql);
}