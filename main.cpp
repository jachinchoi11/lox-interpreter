

#include <iostream>
#include "Run.h"
#include "Scanner.h"
#include "Error.h"
#include "AstPrinter.h"
#include "Interpreter.h"
#include "Parser.h"
int main(int argc, char *argv[]) {

    // if (argc > 1) {
    //     std::cout << "Incorrect number of arguments" << std::endl;
    //     exit(64);
    // }
    // else if (argc == 2) {
    //     Run::run_file(argv[1]);
    // }
    // else {
    //     Run::runPrompt();
    //     Error::hasError = false;
    // }
    // return 0;

    std::string source;
    std::cout << "Enter an expression: ";
    std::getline(std::cin, source);

    Scanner scanner(source);
    std::vector<Token> tokens = scanner.scanTokens();

    Parser parser(tokens);
    std::unique_ptr<Expr> expression = parser.parse();

    AstPrinter printer;
    std::cout << "AST: " << std::any_cast<std::string>(expression->accept(printer)) << std::endl;

    Interpreter interpreter;
    std::any result = interpreter.interpret(*expression);

    if (result.type() == typeid(double)) {
        std::cout << "Result: " << std::any_cast<double>(result) << std::endl;
    } else if (result.type() == typeid(int)) {
        std::cout << "Result: " << std::any_cast<int>(result) << std::endl;
    } else if (result.type() == typeid(bool)) {
        std::cout << "Result: " << (std::any_cast<bool>(result) ? "true" : "false") << std::endl;
    } else if (result.type() == typeid(std::string)) {
        std::cout << "Result: " << std::any_cast<std::string>(result) << std::endl;
    } else {
        std::cout << "Result: [unknown type]" << std::endl;
    }
}