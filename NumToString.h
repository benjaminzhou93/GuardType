#ifndef NUMTOSTRING_H
#define NUMTOSTRING_H

#include <iostream>

struct NumToString {
    static const std::string    Transform(const std::string& data) { return data; }
    static const std::string    Transform(const char& data);
    static const std::string    Transform(const unsigned char& data);
    static const std::string    Transform(const short& data);
    static const std::string    Transform(const unsigned short& data);
    static const std::string    Transform(const int& data);
    static const std::string    Transform(const unsigned int& data);
    static const std::string    Transform(const long& data);
    static const std::string    Transform(const unsigned long& data);
    static const std::string    Transform(const float& data);
    static const std::string    Transform(const double& data);
    static const std::string    Transform(const long double& data);
};

#endif // NUMTOSTRING_H
