#pragma once
#include <exception>

class ExceptieNotaInvalida : public std::exception {
public:
    const char* what() const noexcept override {
        return "Nota introdusa este invalida! Trebuie sa fie intre 0 si 10.";
    }
};

class ExceptiePrezentaInvalida : public std::exception {
public:
    const char* what() const noexcept override {
        return "Procentul de prezenta trebuie sa fie intre 0 si 100.";
    }
};

class ExceptieDateIncomplete : public std::exception {
public:
    const char* what() const noexcept override {
        return "Datele introduse sunt incomplete sau invalide.";
    }
};
