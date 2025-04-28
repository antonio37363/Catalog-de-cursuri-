#pragma once
#include <string>

class Serializable {
public:
    virtual std::string toCSV() const = 0;
    virtual std::string toJSON() const = 0;
    virtual ~Serializable() {}
};
