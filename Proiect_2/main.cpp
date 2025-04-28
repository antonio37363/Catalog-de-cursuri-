#include<iostream>

class Curs
{
    protected:
    std::string nume_curs, profesor;
    int credite;

    public:
    virtual void afiseaza() const = 0;
    virtual double nota_finala() const = 0;
    virtual std::string getNume() const = 0;
    virtual ~Curs() {}
};

class Serializable {
    public:
        virtual std::string toCSV() const = 0;
        virtual std::string toJSON() const = 0;
        virtual ~Serializable() {}
};
   

class CursObligatoriu : public Curs, public Serializable
{
    private:
    int nota_scris, nota_colocviu, nota_proiect, nota_activitate;

    public:
    double nota_finala() const override
    {
        double nota_laborator = 0.5 * nota_colocviu + 0.3 * nota_proiect + 0.2 * nota_activitate;
        return 0.5 * (nota_laborator + nota_scris);
    }

    void afiseaza() const override
    {
        std::cout << "Cursul: " << nume_curs << '\n';
        std::cout << "Profesor: " << profesor << '\n';
        std::cout << "Numar credite: " << credite << '\n';
        std::cout << "Nota examen scris: " << nota_scris << '\n';
        std::cout << "Nota colocviu : " << nota_colocviu << '\n';
        std::cout << "Nota proiect: " << nota_proiect << '\n';
        std::cout << "Nota activitate: " << nota_activitate << '\n';
        std::cout << "Nota finala: " << nota_finala() << '\n';
    }

    std::string getNume() const override
    {
        return nume_curs;
    }

    std::string toCSV() const override
    {
        double nota_laborator = 0.5 * nota_colocviu + 0.3 * nota_proiect + 0.2 * nota_activitate;
        return nume_curs + "," + profesor + "," + std::to_string(credite) + "," +
           std::to_string(nota_scris) + "," + std::to_string(nota_colocviu) + "," +
           std::to_string(nota_proiect) + "," + std::to_string(nota_activitate) + "," +
           std::to_string(nota_laborator) + "," + std::to_string(nota_finala());

    }

    std::string toJSON() const override 
    {
        return "{\n" +
        std::string("\"nume_curs\": \"") + nume_curs + "\",\n" +
        "\"profesor\": \"" + profesor + "\",\n" +
        "\"credite\": " + std::to_string(credite) + ",\n" +
        "\"nota_scris\": " + std::to_string(nota_scris) + ",\n" +
        "\"nota_colocviu\": " + std::to_string(nota_colocviu) + ",\n" +
        "\"nota_proiect\": " + std::to_string(nota_proiect) + ",\n" +
        "\"nota_activitate\": " + std::to_string(nota_activitate) + ",\n" +
        "\"nota_finala\": " + std::to_string(nota_finala()) + "\n"
        "}";
    }
};
