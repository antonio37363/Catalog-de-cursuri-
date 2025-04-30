# 📚 Catalog de Cursuri

## 🔍 Descriere

Acest proiect, realizat în C++, simulează un catalog de cursuri universitare (obligatorii, opționale și facultative). Utilizatorul poate fi **secretar** (care are acces complet) sau **student** (care își poate vizualiza propriile cursuri).



## 🛠️ Tehnologii folosite

- **C++** (OOP, STL, fișiere, excepții)
- STL: `vector`, `fstream`, `sstream`, `algorithm`
- Serializare în **CSV** și **JSON**
- Git & GitHub



## ✅ Funcționalități implementate

- [x] Adăugare curs (cu ID student)
- [x] Afișare cursuri
- [x] Salvare/încărcare fișiere `.csv` și `.json`
- [x] Sortare (nume, note, credite)
- [x] Căutare avansată (nume/profesor/prag)
- [x] Modificare note
- [x] Ștergere curs
- [x] **Verificare promovare**
- [x] **Afișare metodă calcul notă finală**
- [x] **Afișare dată ultimă modificare notă**
- [x] Vizualizare cursuri proprii (mod student)
- [x] Număr total de credite promovate



## 📁 Structura proiectului

Catalog-de-cursuri/ ├── include/ ├── src/ ├── cursuri.csv ├── cursuri.json ├── catalog.exe (opțional) ├── README.md


## ▶️ Cum rulezi proiectul?

1. Compilează:
g++ -std=c++17 -Wall -Iinclude src/*.cpp -o catalog.exe

Rulează:

./catalog.exe

# 👤 Autor
Antonio Păun
Facultatea de Matematică și Informatică, UB