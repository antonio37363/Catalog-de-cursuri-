#include "CursOptional.hpp"
#include <iomanip>
#include <sstream>
#include <iostream>
#include "Exceptii.hpp"

CursOptional::CursOptional(const std::string& n, const std::string& p, int c, int p1, int p2, int p3)
    : Curs(n, p, c)
{
    ++nrCursuri;

    if (p1 < 0 || p1 > 10) throw ExceptieNotaInvalida();
    if (p2 < 0 || p2 > 10) throw ExceptieNotaInvalida();
    if (p3 < 0 || p3 > 10) throw ExceptieNotaInvalida();

    proiect1 = p1;
    proiect2 = p2;
    proiect3 = p3;
}

void CursOptional::setProiect1(int nota)
{
    if (nota < 0 || nota > 10) throw ExceptieNotaInvalida();
    proiect1 = nota;
}

void CursOptional::setProiect2(int nota)
{
    if (nota < 0 || nota > 10) throw ExceptieNotaInvalida();
    proiect2 = nota;
}

void CursOptional::setProiect3(int nota)
{
    if (nota < 0 || nota > 10) throw ExceptieNotaInvalida();
    proiect3 = nota;
}

Curs* CursOptional::clone() const
{
    return new CursOptional(*this);
}

double CursOptional::nota_finala() const
{
    return (proiect1 + proiect2 + proiect3) / 3.0;
}

void CursOptional::afiseaza() const
{
    std::cout << "Cursul: " << nume_curs << '\n';
    std::cout << "Profesor: " << profesor << '\n';
    std::cout << "Numar credite: " << credite << '\n';
    std::cout << "Nota proiect 1: " << proiect1 << '\n';
    std::cout << "Nota proiect 2: " << proiect2 << '\n';
    std::cout << "Nota proiect 3: " << proiect3 << '\n';
    std::cout << "Nota finala: " << std::fixed << std::setprecision(2) << nota_finala() << '\n';
}

std::string CursOptional::getNume() const
{
    return nume_curs;
}

void CursOptional::setProiecte(int p1, int p2, int p3)
{
    if (p1 < 0 || p1 > 10) throw ExceptieNotaInvalida();
    if (p2 < 0 || p2 > 10) throw ExceptieNotaInvalida();
    if (p3 < 0 || p3 > 10) throw ExceptieNotaInvalida();

    proiect1 = p1;
    proiect2 = p2;
    proiect3 = p3;
}

std::string CursOptional::toCSV() const
{
    std::ostringstream oss;
    oss << std::fixed << std::setprecision(2) << nota_finala();

    return nume_curs + "," + profesor + "," + std::to_string(credite) + "," +
           std::to_string(proiect1) + "," + std::to_string(proiect2) + "," +
           std::to_string(proiect3) + "," + oss.str();
}

std::string CursOptional::toJSON() const
{
    std::ostringstream oss;
    oss << std::fixed << std::setprecision(2) << nota_finala();

    return "{\n" +
        std::string("\"nume_curs\": \"") + nume_curs + "\",\n" +
        "\"profesor\": \"" + profesor + "\",\n" +
        "\"credite\": " + std::to_string(credite) + ",\n" +
        "\"nota_proiect_1\": " + std::to_string(proiect1) + ",\n" +
        "\"nota_proiect_2\": " + std::to_string(proiect2) + ",\n" +
        "\"nota_proiect_3\": " + std::to_string(proiect3) + ",\n" +
        "\"nota_finala\": " + oss.str() + "\n"
        "}";
}
