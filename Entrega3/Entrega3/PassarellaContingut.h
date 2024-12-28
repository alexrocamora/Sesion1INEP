#ifndef PASSARELLA_CONTINGUT_H
#define PASSARELLA_CONTINGUT_H

#include <string>

class PassarellaContingut {
public:
    PassarellaContingut(const std::string& titol, const std::string& dataEstrena, 
        const std::string& qualificacioEdat, int duracio, const std::string& tipus);

    std::string obteTitol() const;
    std::string obteDataEstrena() const;
    std::string obteQualificacioEdat() const;
    int obteDuracio() const;
    std::string obteTipus() const;

private:
    std::string titolPelicula;
    std::string dataEstrena;
    std::string qualificacioEdat;
    int duracio;
    std::string tipus;
};

#endif
