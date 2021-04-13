#pragma once
#include <string>
class Error {
private:
    std::string message;
public:
    Error(const std::string& message = "");
    std::string get_message() const;
};