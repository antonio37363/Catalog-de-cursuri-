#pragma once
#include "Curs.hpp"
#include "Serializable.hpp"

class CursOptional : public Curs, public Serializable {
private:
    int proiect1, proiect2, proiect3;

public:
    CursOptional(const std::string& n, const std::string& p, int c, int p1, int p2, int p3);

    void setProiect1(int nota);
    void setProiect2(int nota);
    void setProiect3(int nota);
    void setProiecte(int p1, int p2, int p3); // !!! lipsea si asta

    Curs* clone() const override;
    double nota_finala() const override;
    void afiseaza() const override;
    std::string getNume() const override;
    std::string toCSV() const override;
    std::string toJSON() const override;
};
