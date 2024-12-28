#ifndef PASSARELLA_PROPERES_ESTRENES_H
#define PASSARELLA_PROPERES_ESTRENES_H

#include <string>

class PassarellaProperesEstrenes {
public:
    PassarellaProperesEstrenes(const std::string& titol, const std::string& dataEstrena, 
        const std::string& qualificacioEdat, int duracio, const std::string& tipus);

    std::string obteTitol() const;
    std::string obteDataEstrena() const;
    std::string obteQualificacioEdat() const;
    int obteDuracio() const;
    std::string obteTipus() const;

private:
    std::string titol;
    std::string dataEstrena;
    std::string qualificacioEdat;
    int duracio;
    std::string tipus;
};

#endif
