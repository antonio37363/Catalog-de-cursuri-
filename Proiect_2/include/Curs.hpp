#pragma once
#include <string>

class Curs {
protected:
    std::string nume_curs, profesor;
    int credite;
    static int nrCursuri;

public:
    Curs(const std::string& n, const std::string& p, int c);
    virtual void afiseaza() const = 0;
    virtual double nota_finala() const = 0;
    virtual std::string getNume() const = 0;
    virtual ~Curs() {}
    virtual Curs* clone() const = 0;

    int getCredite() const;
    std::string getProfesor() const;
    static int getNrCursuri();
    void setNume(const std::string& numeNou);
    void setProfesor(const std::string& profesorNou);
};
