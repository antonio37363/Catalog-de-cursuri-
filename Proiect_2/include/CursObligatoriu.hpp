#pragma once
#include "Curs.hpp"
#include "Serializable.hpp"

class CursObligatoriu : public Curs, public Serializable {
private:
    int nota_scris, nota_colocviu, nota_proiect, nota_activitate;

public:
    CursObligatoriu(const std::string& n, const std::string& p, int c, int ns, int nc, int np, int na);

    void setNotaScris(int nota);
    void setNotaColocviu(int nota);
    void setNotaProiect(int nota);
    void setNotaActivitate(int nota);
    void setNote(int ns, int nc, int np, int na); // !!! lipsea si asta

    Curs* clone() const override;
    double nota_finala() const override;
    void afiseaza() const override;
    std::string getNume() const override;
    std::string toCSV() const override;
    std::string toJSON() const override;
};
