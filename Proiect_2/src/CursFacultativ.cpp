#include "CursFacultativ.hpp"
#include <iomanip>
#include <sstream>
#include <iostream>
#include "Exceptii.hpp"

CursFacultativ::CursFacultativ(const std::string& n, const std::string& p, int c, int e, int pr, int prez)
    : Curs(n, p, c)
{
    ++nrCursuri;

    if (e < 0 || e > 10) throw ExceptieNotaInvalida();
    if (pr < 0 || pr > 10) throw ExceptieNotaInvalida();
    if (prez < 0 || prez > 100) throw ExceptiePrezentaInvalida();

    nota_eseu = e;
    nota_proiect = pr;
    procent_prezenta = prez;
}

void CursFacultativ::setNotaEseu(int nota)
{
    if (nota < 0 || nota > 10) throw ExceptieNotaInvalida();
    nota_eseu = nota;
}

void CursFacultativ::setNotaProiect(int nota)
{
    if (nota < 0 || nota > 10) throw ExceptieNotaInvalida();
    nota_proiect = nota;
}

void CursFacultativ::setPrezenta(int procent)
{
    if (procent < 0 || procent > 100) throw ExceptiePrezentaInvalida();
    procent_prezenta = procent;
}

Curs* CursFacultativ::clone() const
{
    return new CursFacultativ(*this);
}

double CursFacultativ::nota_finala() const
{
    return 0.4 * nota_eseu + 0.4 * nota_proiect + 0.2 * (procent_prezenta / 10.0);
}

void CursFacultativ::afiseaza() const
{
    std::cout << "Curs: " << nume_curs << '\n';
    std::cout << "Profesor: " << profesor << '\n';
    std::cout << "Credite: " << credite << '\n';
    std::cout << "Nota eseu: " << nota_eseu << '\n';
    std::cout << "Nota proiect: " << nota_proiect << '\n';
    std::cout << "Prezenta: " << procent_prezenta << "%\n";
    std::cout << "Nota finala: " << std::fixed << std::setprecision(2) << nota_finala() << '\n';
}

std::string CursFacultativ::getNume() const
{
    return nume_curs;
}

void CursFacultativ::setEvaluare(int e, int p, int prez)
{
    if (e < 0 || e > 10) throw ExceptieNotaInvalida();
    if (p < 0 || p > 10) throw ExceptieNotaInvalida();
    if (prez < 0 || prez > 100) throw ExceptiePrezentaInvalida();

    nota_eseu = e;
    nota_proiect = p;
    procent_prezenta = prez;
}

std::string CursFacultativ::toCSV() const
{
    std::ostringstream oss;
    oss << std::fixed << std::setprecision(2) << nota_finala();

    return nume_curs + "," + profesor + "," + std::to_string(credite) + "," +
           std::to_string(nota_eseu) + "," + std::to_string(nota_proiect) + "," +
           std::to_string(procent_prezenta) + "%," + oss.str();
}

std::string CursFacultativ::toJSON() const
{
    std::ostringstream oss;
    oss << std::fixed << std::setprecision(2) << nota_finala();

    return "{\n"
           "\"nume_curs\": \"" + nume_curs + "\",\n"
           "\"profesor\": \"" + profesor + "\",\n"
           "\"credite\": " + std::to_string(credite) + ",\n"
           "\"nota_eseu\": " + std::to_string(nota_eseu) + ",\n"
           "\"nota_proiect\": " + std::to_string(nota_proiect) + ",\n"
           "\"prezenta\": " + std::to_string(procent_prezenta) + ",\n"
           "\"nota_finala\": " + oss.str() + "\n"
           "}";
}
