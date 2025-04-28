#pragma once
#include "Curs.hpp"
#include "Serializable.hpp"

class CursFacultativ : public Curs, public Serializable {
private:
    int nota_eseu, nota_proiect;
    int procent_prezenta;

public:
    CursFacultativ(const std::string& n, const std::string& p, int c, int e, int pr, int prez);

    void setNotaEseu(int nota);
    void setNotaProiect(int nota);
    void setPrezenta(int procent);
    void setEvaluare(int e, int p, int prez); // !!! lipsea si asta

    Curs* clone() const override;
    double nota_finala() const override;
    void afiseaza() const override;
    std::string getNume() const override;
    std::string toCSV() const override;
    std::string toJSON() const override;
};
