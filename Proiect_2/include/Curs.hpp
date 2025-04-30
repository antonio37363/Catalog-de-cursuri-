#pragma once
#include <string>

class Curs {
protected:
    std::string nume_curs, profesor;
    int credite;
    static int nrCursuri;
    std::string data_modificare;
    std::string id_student;

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
    void setDataModificare(const std::string& data);
    std::string getDataModificare() const;
    void setIdStudent(const std::string& id);
    std::string getIdStudent() const;
};
