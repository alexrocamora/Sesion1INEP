#ifndef PASSARELLA_USUARI_H
#define PASSARELLA_USUARI_H

#include <string>

class PassarellaUsuari {
public:
    PassarellaUsuari(); // Constructor predeterminado
    PassarellaUsuari(const std::string& sobrenom, const std::string& nom,
        const std::string& correu, const std::string& contrasenya,
        const std::string& dataNaixement, const std::string& modalitatSubscripcio);

    void insereix();
    void modifica();
    void esborra();

    std::string obteSobrenom() const;
    void posaSobrenom(const std::string& sobrenom);

    std::string obteNom() const;
    void posaNom(const std::string& nom);

    std::string obteCorreuElectronic() const;
    void posaCorreuElectronic(const std::string& correu);

    std::string obteContrasenya() const;
    void posaContrasenya(const std::string& contrasenya);

    std::string obteDataNaixement() const;
    void posaDataNaixement(const std::string& dataNaixement);

    std::string obteModalitatSubscripcio() const;
    void posaModalitatSubscripcio(const std::string& modalitatSubscripcio);

private:
    std::string sobrenom;
    std::string nom;
    std::string correuElectronic;
    std::string contrasenya;
    std::string dataNaixement;
    std::string modalitatSubscripcio;
};

#endif
