#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <algorithm>
#include "Curs.hpp"
#include "CursObligatoriu.hpp"
#include "CursOptional.hpp"
#include "CursFacultativ.hpp"
#include "Serializable.hpp"
#include "Exceptii.hpp"



void adaugaCurs(std::vector<Curs*>& cursuri)
{
    int tip;
    std::cout << "Ce tip de curs doresti sa adaugi?\n";
    std::cout << "1. Curs Obligatoriu\n";
    std::cout << "2. Curs Optional\n";
    std::cout << "3. Curs Facultativ\n";
    std::cout << "Alege tipul: ";
    std::cin >> tip;

    std::string nume, profesor;
    int credite;
    std::cout << "Introdu numele cursului: ";
    std::cin.ignore();
    std::getline(std::cin, nume);
    std::cout << "Introdu numele profesorului: ";
    std::getline(std::cin, profesor);
    std::cout << "Introdu numarul de credite: ";
    std::cin >> credite;

    std::string idStudent;
    std::cout << "Introdu ID-ul studentului: ";
    std::cin >> idStudent;


    try
    {
        if (tip == 1)
        {
            int scris, colocviu, proiect, activitate;
            std::cout << "Nota examen scris: ";
            std::cin >> scris;
            std::cout << "Nota colocviu: ";
            std::cin >> colocviu;
            std::cout << "Nota proiect: ";
            std::cin >> proiect;
            std::cout << "Nota activitate laborator: ";
            std::cin >> activitate;

            auto* curs = new CursObligatoriu(nume, profesor, credite, scris, colocviu, proiect, activitate);
            curs->setIdStudent(idStudent);
            cursuri.push_back(curs);
        }
        else if (tip == 2)
        {
            int p1, p2, p3;
            std::cout << "Nota proiect 1: ";
            std::cin >> p1;
            std::cout << "Nota proiect 2: ";
            std::cin >> p2;
            std::cout << "Nota proiect 3: ";
            std::cin >> p3;

            auto* curs = new CursOptional(nume, profesor, credite, p1, p2, p3);
            curs->setIdStudent(idStudent);
            cursuri.push_back(curs);
        }
        else if (tip == 3)
        {
            int eseu, proiect, prezenta;
            std::cout << "Nota eseu: ";
            std::cin >> eseu;
            std::cout << "Nota proiect: ";
            std::cin >> proiect;
            std::cout << "Procent prezenta: ";
            std::cin >> prezenta;

            auto* curs = new CursFacultativ(nume, profesor, credite, eseu, proiect, prezenta);
            curs->setIdStudent(idStudent);
            cursuri.push_back(curs);
        }
        else
        {
            std::cout << "Tip invalid.\n";
        }
    }
    catch (const std::exception& e)
    {
        std::cout << "Eroare: " << e.what() << '\n';
    }
}

void afiseazaCursuri(const std::vector<Curs*>& cursuri)
{
    if (cursuri.empty())
    {
        std::cout << "Nu exista cursuri adaugate.\n";
        return;
    }

    for (const auto& curs : cursuri)
    {
        curs->afiseaza();
        std::cout << "-------------------------\n"; // separator intre cursuri
    }
}



void salvareCSV(const std::vector<Curs*>& vector_cursuri)
{
    std::ofstream fout("cursuri.csv");

    if (!fout.is_open())
    {
        std::cout << "Eroare: Nu am putut deschide fisierul cursuri.csv\n";
        return;
    }

    for (auto& curs : vector_cursuri)
    {
        Serializable* serial = dynamic_cast<Serializable*>(curs);
        if (serial)
        {
            fout << serial->toCSV() << '\n';
        }
    }

    fout.close();
    std::cout << "Salvare in cursuri.csv finalizata cu succes!\n";
}


void salvareJSON(const std::vector<Curs*>& cursuri)
{
    std::ofstream fout("cursuri.json");

    if (!fout.is_open())
    {
        std::cout << "Eroare: Nu am putut deschide fisierul cursuri.json\n";
        return;
    }

    fout << "[\n";
    for (size_t i = 0; i < cursuri.size(); ++i)
    {
        Serializable* serial = dynamic_cast<Serializable*>(cursuri[i]);
        if (serial)
        {
            fout << serial->toJSON();
            if (i != cursuri.size() - 1)
                fout << ",\n"; // punem virgula intre obiecte
        }
    }
    fout << "\n]\n";

    fout.close();
    std::cout << "Salvare in cursuri.json finalizata cu succes!\n";
}




void afiseazaCrediteTotale(const std::vector<Curs*>& cursuri)
{
    int total = 0;

    for (const auto& curs : cursuri)
        total += curs->getCredite();

    std::cout << "Numar total de credite: " << total << "\n";
}


void stergeCurs(std::vector<Curs*>& cursuri)
{
    std::string numeCautat;
    std::cout << "Introdu numele cursului de sters: ";
    std::getline(std::cin >> std::ws, numeCautat);

    bool gasit = false;
    for (size_t i = 0; i < cursuri.size(); ++i)
    {
        if (cursuri[i]->getNume() == numeCautat)
        {
            delete cursuri[i]; // stergi cursul din memorie
            cursuri.erase(cursuri.begin() + i); // il scoti din vector
            gasit = true;
            std::cout << "Cursul a fost sters cu succes!\n";
            break;
        }
    }

    if (!gasit)
    {
        std::cout << "Cursul nu a fost gasit.\n";
    }


}



void modificaCurs(std::vector<Curs*>& cursuri)
{
    std::string numeCautat;
    std::cout << "Introdu numele cursului pe care vrei sa il modifici: ";
    std::getline(std::cin >> std::ws, numeCautat);

    bool gasit = false;
    for (auto& curs : cursuri)
    {
        if (curs->getNume() == numeCautat)
        {
            gasit = true;
            // Verificam ce tip de curs este
            if (auto* oblig = dynamic_cast<CursObligatoriu*>(curs))
            {
                std::cout << "Ce vrei sa modifici?\n";
                std::cout << "1. Nota scris\n";
                std::cout << "2. Nota colocviu\n";
                std::cout << "3. Nota proiect\n";
                std::cout << "4. Nota activitate\n";
                int alegere;
                std::cin >> alegere;
                int nouaNota;
                std::cout << "Introdu noua nota: ";
                std::cin >> nouaNota;

                if (alegere == 1) oblig->setNotaScris(nouaNota);
                else if (alegere == 2) oblig->setNotaColocviu(nouaNota);
                else if (alegere == 3) oblig->setNotaProiect(nouaNota);
                else if (alegere == 4) oblig->setNotaActivitate(nouaNota);
                else std::cout << "Optiune invalida!\n";
            }
            else if (auto* opt = dynamic_cast<CursOptional*>(curs))
            {
                std::cout << "Ce vrei sa modifici?\n";
                std::cout << "1. Nota proiect 1\n";
                std::cout << "2. Nota proiect 2\n";
                std::cout << "3. Nota proiect 3\n";
                int alegere;
                std::cin >> alegere;
                int nouaNota;
                std::cout << "Introdu noua nota: ";
                std::cin >> nouaNota;

                if (alegere == 1) opt->setProiect1(nouaNota);
                else if (alegere == 2) opt->setProiect2(nouaNota);
                else if (alegere == 3) opt->setProiect3(nouaNota);
                else std::cout << "Optiune invalida!\n";
            }
            else if (auto* facult = dynamic_cast<CursFacultativ*>(curs))
            {
                std::cout << "Ce vrei sa modifici?\n";
                std::cout << "1. Nota eseu\n";
                std::cout << "2. Nota proiect\n";
                std::cout << "3. Prezenta\n";
                int alegere;
                std::cin >> alegere;
                
                if (alegere == 1)
                {
                    int nouaNota;
                    std::cout << "Introdu noua nota la eseu: ";
                    std::cin >> nouaNota;
                    facult->setNotaEseu(nouaNota);
                }
                else if (alegere == 2)
                {
                    int nouaNota;
                    std::cout << "Introdu noua nota la proiect: ";
                    std::cin >> nouaNota;
                    facult->setNotaProiect(nouaNota);
                }
                else if (alegere == 3)
                {
                    int nouProcent;
                    std::cout << "Introdu noul procent de prezenta: ";
                    std::cin >> nouProcent;
                    facult->setPrezenta(nouProcent);
                }
                else
                {
                    std::cout << "Optiune invalida!\n";
                }
            }
            else
            {
                std::cout << "Tip de curs necunoscut!\n";
            }

            break; // am gasit si modificat, iesim
        }
    }

    if (!gasit)
    {
        std::cout << "Cursul nu a fost gasit.\n";
    }
}




void sorteazaCursuri(std::vector<Curs*>& cursuri)
{
    if (cursuri.empty())
    {
        std::cout << "Nu exista cursuri de sortat.\n";
        return;
    }

    std::cout << "Cum doresti sa sortezi cursurile?\n";
    std::cout << "1. Dupa nume (A-Z)\n";
    std::cout << "2. Dupa nota finala (descrescator)\n";
    std::cout << "3. Dupa numarul de credite (descrescator)\n";
    std::cout << "Alege optiunea: ";

    int alegere;
    std::cin >> alegere;

    if (alegere == 1)
    {
        std::sort(cursuri.begin(), cursuri.end(), [](Curs* a, Curs* b)
        {
            return a->getNume() < b->getNume();
        });
        std::cout << "Sortare dupa nume realizata cu succes!\n";
    }
    else if (alegere == 2)
    {
        std::sort(cursuri.begin(), cursuri.end(), [](Curs* a, Curs* b)
        {
            return a->nota_finala() > b->nota_finala();
        });
        std::cout << "Sortare dupa nota finala realizata cu succes!\n";
    }
    else if (alegere == 3)
    {
        std::sort(cursuri.begin(), cursuri.end(), [](Curs* a, Curs* b)
        {
            return a->getCredite() > b->getCredite();
        });
        std::cout << "Sortare dupa numar credite realizata cu succes!\n";
    }
    else
    {
        std::cout << "Optiune invalida!\n";
    }
}


void cautaCursAvansat(const std::vector<Curs*>& cursuri)
{
    if (cursuri.empty())
    {
        std::cout << "Nu exista cursuri inregistrate.\n";
        return;
    }

    std::cout << "Criterii de cautare:\n";
    std::cout << "1. Cauta dupa nume curs\n";
    std::cout << "2. Cauta dupa profesor\n";
    std::cout << "3. Cauta cursuri cu nota finala peste o valoare\n";
    std::cout << "Alege optiunea: ";

    int alegere;
    std::cin >> alegere;
    std::cin.ignore(); // curata bufferul ca sa mearga getline()

    if (alegere == 1)
    {
        std::string nume;
        std::cout << "Introdu numele cursului: ";
        std::getline(std::cin, nume);

        bool gasit = false;
        for (const auto& curs : cursuri)
        {
            if (curs->getNume() == nume)
            {
                curs->afiseaza();
                gasit = true;
            }
        }
        if (!gasit)
            std::cout << "Nu s-a gasit niciun curs cu acest nume.\n";
    }
    else if (alegere == 2)
    {
        std::string numeProfesor;
        std::cout << "Introdu numele profesorului: ";
        std::getline(std::cin, numeProfesor);

        bool gasit = false;
        for (const auto& curs : cursuri)
        {

            if (curs->getProfesor() == numeProfesor)
            {
                curs->afiseaza();
                gasit = true;
            }
        }
        if (!gasit)
            std::cout << "Nu s-a gasit niciun curs predat de acest profesor.\n";
    }
    else if (alegere == 3)
    {
        double prag;
        std::cout << "Introdu pragul minim al notei finale: ";
        std::cin >> prag;

        bool gasit = false;
        for (const auto& curs : cursuri)
        {
            if (curs->nota_finala() >= prag)
            {
                curs->afiseaza();
                gasit = true;
            }
        }
        if (!gasit)
            std::cout << "Nu s-au gasit cursuri cu nota peste pragul dat.\n";
    }
    else
    {
        std::cout << "Optiune invalida!\n";
    }
}



void incarcareCSV(std::vector<Curs*>& cursuri)
{
    std::ifstream fin("cursuri.csv");

    if (!fin.is_open())
    {
        std::cout << "Eroare: Nu am putut deschide fisierul cursuri.csv\n";
        return;
    }

    std::string linie;
    while (std::getline(fin, linie))
    {
        std::istringstream ss(linie);
        std::vector<std::string> campuri;
        std::string camp;

        while (std::getline(ss, camp, ','))
        {
            campuri.push_back(camp);
        }

        try
        {
            if (campuri.empty()) continue;

            std::string tip = campuri[0];

            if (tip == "obligatoriu" && campuri.size() == 10)
            {
                auto* curs = new CursObligatoriu(
                    campuri[1], campuri[2], std::stoi(campuri[3]),
                    std::stoi(campuri[4]), std::stoi(campuri[5]),
                    std::stoi(campuri[6]), std::stoi(campuri[7])
                );
                curs->setDataModificare(campuri[8]);
                curs->setIdStudent(campuri[9]);
                cursuri.push_back(curs);
            }
            else if (tip == "optional" && campuri.size() == 9)
            {
                auto* curs = new CursOptional(
                    campuri[1], campuri[2], std::stoi(campuri[3]),
                    std::stoi(campuri[4]), std::stoi(campuri[5]),
                    std::stoi(campuri[6])
                );
                curs->setDataModificare(campuri[7]);
                curs->setIdStudent(campuri[8]);
                cursuri.push_back(curs);
            }
            else if (tip == "facultativ" && campuri.size() == 9)
            {
                int procent_prezenta = std::stoi(campuri[6].substr(0, campuri[6].size() - 1));
                auto* curs = new CursFacultativ(
                    campuri[1], campuri[2], std::stoi(campuri[3]),
                    std::stoi(campuri[4]), std::stoi(campuri[5]),
                    procent_prezenta
                );
                curs->setDataModificare(campuri[7]);
                curs->setIdStudent(campuri[8]);
                cursuri.push_back(curs);
            }
            else
            {
                std::cout << "Linie invalida ignorata.\n";
            }
        }
        catch (const std::exception& e)
        {
            std::cout << "Eroare la incarcare: " << e.what() << "\n";
        }
    }

    fin.close();
    std::cout << "Incarcare din cursuri.csv finalizata cu succes!\n";
}




void vizualizareCursuriStudent(const std::vector<Curs*>& cursuri) {
    std::string id;
    std::cout << "Introdu ID-ul tau: ";
    std::cin >> id;

    bool gasit = false;
    for (const auto& curs : cursuri) {
        if (curs->getIdStudent() == id) {
            curs->afiseaza();
            std::cout << "------------------------\n";
            gasit = true;
        }
    }

    if (!gasit)
        std::cout << "Nu ai niciun curs inregistrat.\n";
}




void afiseazaCreditePromovate(const std::vector<Curs*>& cursuri) {
    int totalCredite = 0, creditePromovate = 0;

    for (const auto& curs : cursuri) {
        totalCredite += curs->getCredite();
        if (curs->nota_finala() >= 5)
            creditePromovate += curs->getCredite();
    }

    std::cout << "Ai promovat " << creditePromovate << " din " << totalCredite << " credite.\n";
}







int main()
{
    std::vector<Curs*> cursuri; // vector in care adaugam cursurile

    bool esteSecretar;
    std::cout << "Esti:\n1. Secretar\n2. Student\nAlege: ";
    int rol;
    std::cin >> rol;
    esteSecretar = (rol == 1);
    
// Încarcă cursurile din CSV imediat după alegerea rolului
    incarcareCSV(cursuri);

    try
    {
        while (true)
        {
            if (!esteSecretar)
            {
                std::cout << "===== MENIU STUDENT =====\n";
                std::cout << "1. Vezi cursurile tale\n";
                std::cout << "2. Vezi cate credite ai promovat\n";
                std::cout << "0. Iesire\n";

                int opt;
                std::cin >> opt;

                if (opt == 1)
                {
                    vizualizareCursuriStudent(cursuri);
                }
                else if (opt == 2) {
                    std::string id;
                    std::cout << "Introdu ID-ul tau: ";
                    std::cin >> id;
                
                    std::vector<Curs*> cursuriStudent;
                    for (auto& curs : cursuri)
                        if (curs->getIdStudent() == id)
                            cursuriStudent.push_back(curs);
                
                    if (cursuriStudent.empty())
                        std::cout << "Nu ai cursuri inregistrate.\n";
                    else
                        afiseazaCreditePromovate(cursuriStudent);
                }                
                else if (opt == 0)
                {
                    std::cout << "La revedere!\n";
                    break;
                }
                else
                {
                    std::cout << "Optiune invalida!\n";
                }
                continue; // sari peste meniul de secretar
            }




            std::cout << "\n===== MENIU CATALOG =====\n";
            std::cout << "1. Adauga curs\n";
            std::cout << "2. Afiseaza toate cursurile\n";
            std::cout << "3. Salveaza in fisier CSV\n";
            std::cout << "4. Afiseaza numarul total de cursuri\n";
            std::cout << "5. Sterge un curs dupa nume\n";
            std::cout << "6. Salveaza in fisier JSON\n"; 
            std::cout << "7. Modifica Curs\n";
            std::cout << "8. Sorteaza cursurile\n";
            std::cout << "9. Cauta curs avansat\n";
            std::cout << "10. Incarca cursuri din fisier CSV\n";
            std::cout << "0. Iesire\n";
            std::cout << "Alege optiunea: ";

            int optiune;
            std::cin >> optiune;

            if (optiune == 1)
            {
                adaugaCurs(cursuri);
            }
            else if (optiune == 2)
            {
                afiseazaCursuri(cursuri);
            }
            else if (optiune == 3)
            {
                salvareCSV(cursuri);
            }
            else if (optiune == 4)
            {
                std::cout << "Numar total de cursuri create: " << Curs::getNrCursuri() << "\n";
            }
            else if (optiune == 5)
            {
                stergeCurs(cursuri);
                salvareCSV(cursuri);
                salvareJSON(cursuri);
            }
            else if (optiune == 6)
            {
                salvareJSON(cursuri);
            }
            else if (optiune == 7)
            {
                modificaCurs(cursuri);
            }
            else if (optiune == 8)
            {
                sorteazaCursuri(cursuri);
            }
            else if (optiune == 9)
            {
                cautaCursAvansat(cursuri);
            }
            else if (optiune == 10)
            {
                incarcareCSV(cursuri);
            }            
            else if (optiune == 0)
            {
                salvareCSV(cursuri); // salvam cursurile inainte sa iesim
                std::cout << "La revedere!\n";
                break;
            }
            else
            {
                std::cout << "Optiune invalida. Incearca din nou.\n";
            }
        }

        // Distrugem memoria
        for (auto& curs : cursuri)
            delete curs;
    }
    catch (const ExceptieNotaInvalida& e)
    {
        std::cout << "Eroare la nota: " << e.what() << '\n';
    }
    catch (const ExceptiePrezentaInvalida& e)
    {
        std::cout << "Eroare la prezenta: " << e.what() << '\n';
    }
    catch (const std::exception& e)
    {
        std::cout << "Alta eroare: " << e.what() << '\n';
    }

    return 0;
}