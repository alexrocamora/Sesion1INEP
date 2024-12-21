#ifndef PASSARELLA_VISUALITZA_PEL_H
#define PASSARELLA_VISUALITZA_PEL_H

#include <string>

class PassarellaVisualitzaPel {
public:
    PassarellaVisualitzaPel(const std::string& sobrenom, const std::string& titol,
        const std::string& data, int numVisualitzacions);

    std::string obteSobrenom() const;
    std::string obteTitol() const;
    std::string obteData() const;
    int obteNumVisualitzacions() const;

private:
    std::string sobrenomUsuari;
    std::string titolPelicula;
    std::string data;
    int numVisualitzacions;
};

#endif
