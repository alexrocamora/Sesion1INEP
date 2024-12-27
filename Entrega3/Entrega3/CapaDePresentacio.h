#ifndef CAPADEPRESENTACIO_HP
#define CAPADEPRESENTACIO_HP

#include <string>
#include "TxIniciSessio.h"
#include "TxTancaSessio.h"
#include "TxRegistraUsuari.h"
#include "TxConsultaUsuari.h"
#include "CtrlModificarUsuari.h"
#include "TxEsborraUsuari.h"
#include "DTOUsuari.h"

class CapaDePresentacio {
private:
    static CapaDePresentacio* instancia;
    CapaDePresentacio() {}

public:
    static CapaDePresentacio* getInstancia();
    std::string iniciSessio();
    bool tancaSessio(bool confirmacio = true);
    void registrarUsuari();
    void consultaUsuari(const std::string& sobrenom);
    void modificarUsuari(const std::string& sobrenom);
    void esborraUsuari(const std::string& sobrenom);
    void visualitzaPelicula(const std::string& sobrenom); 
};

#endif
