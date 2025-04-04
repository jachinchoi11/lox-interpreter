#pragma once

#include <unordered_map>
#include <any>

class Environment {
    std::unordered_map<std::string, std::any> variables;
public:
    void define(std::string name, std::any value);
    std::any get(std::string name);
};