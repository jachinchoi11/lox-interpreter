//
// Created by Jachin Choi on 1/30/25.
//

#ifndef RUN_H
#define RUN_H

#include <string>

class Run {
public:
    static void runFile(std::string path);
    static void runPrompt();
    static void run(std::string source);
};
#endif //RUN_H
