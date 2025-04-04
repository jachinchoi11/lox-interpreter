#include "Environment.h"


void Environment::define(std::string name, std::any value) {
    variables[name] = value;
}

std::any Environment::get(std::string name) {
    if (variables.count(name) > 0) {
        return variables[name];
    }
    throw std::runtime_error("Environment variable " + name + " not defined");
}