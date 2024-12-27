#ifndef PASSARELLA_VISUALITZA_SERIE_H
#define PASSARELLA_VISUALITZA_SERIE_H

#include <string>

class PassarellaVisualitzaSerie {
public:
    PassarellaVisualitzaSerie(const std::string& sobrenom, const std::string& titol,
        int temporada, int capitol, const std::string& data,
        int numVisualitzacions, const std::string& titolCapitol,
        const std::string& dataEstrena, int qualificacio);

    std::string obteSobrenom() const;
    std::string obteTitol() const;
    int obteTemporada() const;
    int obteCapitol() const;
    std::string obteData() const;
    int obteNumVisualitzacions() const;
    std::string obteTitolCapitol() const;
    std::string obteDataEstrena() const;
    int obteQualificacio() const;

private:
    std::string sobrenomUsuari;
    std::string titolSerie;
    int numTemporada;
    int numCapitol;
    std::string data;
    int numVisualitzacions;
    std::string titolCapitol;
    std::string dataEstrena;
    int qualificacio;
};

#endif
