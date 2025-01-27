#include "DTOUsuari.h"
#include "PassarellaUsuari.h"

class TxConsultaUsuari {
public:
    TxConsultaUsuari();
    void crear(const std::string& sobrenom);
    void executar();
    DTOUsuari obteResultat() const;
    PassarellaUsuari obteUsuari() const;

private:
    DTOUsuari resultat;
    PassarellaUsuari usuari;
};
