#include "CursObligatoriu.hpp"
#include "Utils.hpp"
#include <iomanip>
#include <sstream>
#include <iostream>
#include "Exceptii.hpp"

CursObligatoriu::CursObligatoriu(const std::string& n, const std::string& p, int c, int ns, int nc, int np, int na)
    : Curs(n, p, c)
{
    ++nrCursuri;

    if (ns < 0 || ns > 10) throw ExceptieNotaInvalida();
    if (nc < 0 || nc > 10) throw ExceptieNotaInvalida();
    if (np < 0 || np > 10) throw ExceptieNotaInvalida();
    if (na < 0 || na > 10) throw ExceptieNotaInvalida();

    nota_scris = ns;
    nota_colocviu = nc;
    nota_proiect = np;
    nota_activitate = na;
}

void CursObligatoriu::setNotaScris(int nota)
{
    if (nota < 0 || nota > 10) throw ExceptieNotaInvalida();
    nota_scris = nota;
    setDataModificare(getCurrentDate());
}

void CursObligatoriu::setNotaColocviu(int nota)
{
    if (nota < 0 || nota > 10) throw ExceptieNotaInvalida();
    nota_colocviu = nota;
    setDataModificare(getCurrentDate());
}

void CursObligatoriu::setNotaProiect(int nota)
{
    if (nota < 0 || nota > 10) throw ExceptieNotaInvalida();
    nota_proiect = nota;
    setDataModificare(getCurrentDate());
}

void CursObligatoriu::setNotaActivitate(int nota)
{
    if (nota < 0 || nota > 10) throw ExceptieNotaInvalida();
    nota_activitate = nota;
    setDataModificare(getCurrentDate());
}

Curs* CursObligatoriu::clone() const
{
    return new CursObligatoriu(*this);
}

double CursObligatoriu::nota_finala() const
{
    double nota_laborator = 0.5 * nota_colocviu + 0.3 * nota_proiect + 0.2 * nota_activitate;
    return 0.5 * (nota_laborator + nota_scris);
}

void CursObligatoriu::afiseaza() const
{
    std::cout << "Cursul: " << nume_curs << '\n';
    std::cout << "Profesor: " << profesor << '\n';
    std::cout << "Numar credite: " << credite << '\n';
    std::cout << "Nota examen scris: " << nota_scris << '\n';
    std::cout << "Nota colocviu : " << nota_colocviu << '\n';
    std::cout << "Nota proiect: " << nota_proiect << '\n';
    std::cout << "Nota activitate: " << nota_activitate << '\n';
    std::cout << "Nota finala: " << std::fixed << std::setprecision(2) << nota_finala() << '\n';
    std::cout << "Data ultimei modificari: " << getDataModificare() << '\n';
    std::cout << "Status: " << (nota_finala() >= 5 ? "Promovat" : "Nepromovat") << "\n";
    std::cout << "Metoda de calcul: 0.5 * (0.5 * colocviu + 0.3 * proiect + 0.2 * activitate) + 0.5 * scris\n";

}

std::string CursObligatoriu::getNume() const
{
    return nume_curs;
}

void CursObligatoriu::setNote(int ns, int nc, int np, int na)
{
    if (ns < 0 || ns > 10) throw ExceptieNotaInvalida();
    if (nc < 0 || nc > 10) throw ExceptieNotaInvalida();
    if (np < 0 || np > 10) throw ExceptieNotaInvalida();
    if (na < 0 || na > 10) throw ExceptieNotaInvalida();

    nota_scris = ns;
    nota_colocviu = nc;
    nota_proiect = np;
    nota_activitate = na;
}

std::string CursObligatoriu::toCSV() const
{
    double nota_laborator = 0.5 * nota_colocviu + 0.3 * nota_proiect + 0.2 * nota_activitate;

    std::ostringstream oss_laborator;
    oss_laborator << std::fixed << std::setprecision(2) << nota_laborator;

    std::ostringstream oss_finala;
    oss_finala << std::fixed << std::setprecision(2) << nota_finala();

    return nume_curs + "," + profesor + "," + std::to_string(credite) + "," +
           std::to_string(nota_scris) + "," + std::to_string(nota_colocviu) + "," +
           std::to_string(nota_proiect) + "," + std::to_string(nota_activitate) + "," +
           oss_laborator.str() + "," + oss_finala.str() + "," + data_modificare;
}

std::string CursObligatoriu::toJSON() const
{
    std::ostringstream oss;
    oss << std::fixed << std::setprecision(2) << nota_finala();

    return "{\n" +
        std::string("\"nume_curs\": \"") + nume_curs + "\",\n" +
        "\"profesor\": \"" + profesor + "\",\n" +
        "\"credite\": " + std::to_string(credite) + ",\n" +
        "\"nota_scris\": " + std::to_string(nota_scris) + ",\n" +
        "\"nota_colocviu\": " + std::to_string(nota_colocviu) + ",\n" +
        "\"nota_proiect\": " + std::to_string(nota_proiect) + ",\n" +
        "\"nota_activitate\": " + std::to_string(nota_activitate) + ",\n" +
        "\"nota_finala\": " + oss.str() + data_modificare + "\n"
        "}";
}
