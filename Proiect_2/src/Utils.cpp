#include "Utils.hpp"
#include <ctime>
#include <iomanip>
#include <sstream>

std::string getCurrentDate() {
    std::time_t t = std::time(nullptr);
    std::tm tm = *std::localtime(&t);
    std::ostringstream oss;
    oss << std::put_time(&tm, "%Y-%m-%d");
    return oss.str();
}
