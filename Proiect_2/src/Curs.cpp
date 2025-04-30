#include "Curs.hpp"

int Curs::nrCursuri = 0;

Curs::Curs(const std::string& n, const std::string& p, int c) 
    : nume_curs(n), profesor(p), credite(c) {}


int Curs::getCredite() const { return credite; }
std::string Curs::getProfesor() const { return profesor; }
int Curs::getNrCursuri() { return nrCursuri; }
void Curs::setNume(const std::string& numeNou) { nume_curs = numeNou; }
void Curs::setProfesor(const std::string& profesorNou) { profesor = profesorNou; }

void Curs::setDataModificare(const std::string& data) {
    data_modificare = data;
}

std::string Curs::getDataModificare() const {
    return data_modificare;
}

void Curs::setIdStudent(const std::string& id) { id_student = id; }
std::string Curs::getIdStudent() const { return id_student; }
