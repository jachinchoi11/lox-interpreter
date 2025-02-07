

#include <iostream>
#include "Run.h"

int main(int argc, char *argv[]) {
    if (argc > 1) {
        std::cout << "Incorrect number of arguments" << std::endl;
        exit(64);
    }
    else {
        Run::runPrompt();
    }
    return 0;
    
}