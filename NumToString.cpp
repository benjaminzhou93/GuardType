#include "NumToString.h"

//----------------------------NumToString--------------------------------------------
//                         The members of NumToString

const std::string NumToString::Transform(const char& data) {
    std::string result;
    result += data;
    return result;
}

const std::string NumToString::Transform(const unsigned char& data) {
    std::string result;
    result += data;
    return result;
}

const std::string NumToString::Transform(const short& data) {
    std::string result;
    char str_num[32];
    sprintf(str_num, "%hd", data);
    result += str_num;
    return result;
}

const std::string NumToString::Transform(const unsigned short& data) {
    std::string result;
    char str_num[32];
    sprintf(str_num, "%hu", data);
    result += str_num;
    return result;
}

const std::string NumToString::Transform(const int& data) {
    std::string result;
    char str_num[32];
    sprintf(str_num, "%d", data);
    result += str_num;
    return result;
}

const std::string NumToString::Transform(const unsigned int& data) {
    std::string result;
    char str_num[32];
    sprintf(str_num, "%u", data);
    result += str_num;
    return result;
}

const std::string NumToString::Transform(const long& data) {
    std::string result;
    char str_num[32];
    sprintf(str_num, "%ld", data);
    result += str_num;
    return result;
}

const std::string NumToString::Transform(const unsigned long& data) {
    std::string result;
    char str_num[32];
    sprintf(str_num, "%lu", data);
    result += str_num;
    return result;
}

const std::string NumToString::Transform(const float& data) {
    std::string result;
    char str_num[32];
    sprintf(str_num, "%f", data);
    result += str_num;
    while(!result.empty() && result.back() == '0')
        result.pop_back();
    if(result.back() == '.')
        result.push_back('0');
    return result;
}

const std::string NumToString::Transform(const double& data) {
    std::string result;
    char str_num[32];
    sprintf(str_num, "%lf", data);
    result += str_num;
    while(!result.empty() && result.back() == '0')
        result.pop_back();
    if(result.back() == '.')
        result.push_back('0');
    return result;
}

const std::string NumToString::Transform(const long double& data) {
    std::string result;
    char str_num[32];
    sprintf(str_num, "%LF", data);
    result += str_num;
    while(!result.empty() && result.back() == '0')
        result.pop_back();
    if(result.back() == '.')
        result.push_back('0');
    return result;
}


