
#ifndef RUN_H
#define RUN_H

#include <string>

class Run {
public:
    static void runPrompt();
    static void run(std::string &source);
    static void run_file(std::string source);
};
#endif //RUN_H
