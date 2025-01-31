//
// Created by Jachin Choi on 1/24/25.
//

#include <iostream>
#include "Run.h"

int main(int argc, char *argv[]) {
    if (argc > 1) {
        std::cout << "Incorrect number of arguments" << std::endl;
        exit(64); // terminates the program and returns code 64 to OS
    }
    else if (argc == 1) {
        Run::runFile(argv[0]);
    }
    else {
        Run::runPrompt();
    }
    return 0;
    
}