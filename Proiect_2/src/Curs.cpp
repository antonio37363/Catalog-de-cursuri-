#include "Curs.hpp"

int Curs::nrCursuri = 0;

Curs::Curs(const std::string& n, const std::string& p, int c) 
    : nume_curs(n), profesor(p), credite(c) {}


int Curs::getCredite() const { return credite; }
std::string Curs::getProfesor() const { return profesor; }
int Curs::getNrCursuri() { return nrCursuri; }
void Curs::setNume(const std::string& numeNou) { nume_curs = numeNou; }
void Curs::setProfesor(const std::string& profesorNou) { profesor = profesorNou; }
