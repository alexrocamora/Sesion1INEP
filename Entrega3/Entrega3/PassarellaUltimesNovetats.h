#ifndef PASSARELLA_ULTIMES_NOVETATS_H
#define PASSARELLA_ULTIMES_NOVETATS_H

#include <string>

class PassarellaUltimesNovetats {
public:
    PassarellaUltimesNovetats(const std::string& titol, const std::string& dataEstrena, 
        const std::string& qualificacioEdat, const std::string& temporada,
        const std::string& capitol, const std::string& tipus);

    std::string obteTitol() const;
    std::string obteDataEstrena() const;
    std::string obteQualificacioEdat() const;
    std::string obteTemporada() const;
    std::string obteCapitol() const;
    std::string obteTipus() const;

private:
    std::string titol;
    std::string dataEstrena;
    std::string qualificacioEdat;
    std::string temporada;
    std::string capitol;
    std::string tipus;
};

#endif
