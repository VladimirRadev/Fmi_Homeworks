#pragma once
#include "Object.hpp"
#include <string>
#include <vector>
#include <stdexcept>
#include <iostream>
class Document:public Object {
    std::vector<std::string>lines;
    int readingLine;
public:
    Document(const std::string& name, const std::string& location, const std::string& extension);

    void write_line(const std::string& line);

    std::string read_line();
    std::string read_line(const unsigned line);

    Object* clone()const;
    std::string to_string()const override;
    void from_string(const std::string& source)override;
    std::string debug_print()const override;
    bool operator==(const Comparable*)const override;
    bool operator!=(const Comparable*)const override;
};