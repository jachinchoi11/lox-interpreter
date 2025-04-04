

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

    // Prompt the user to input a source expression.
    std::cout << "Enter an expression: ";
    std::getline(std::cin, source);

    // Initialize the Scanner and tokenize the input expression.
    Scanner scanner(source);
    std::vector<Token> tokens = scanner.scanTokens();
    for (const auto& token : tokens) {
        std::cout << "Token: " << tokenTypeToString(token.type)
                  << ", Lexeme: \"" << token.lexeme << "\"" << std::endl;
    }


    // Initialize the Parser and parse the tokens into statements (AST).
    Parser parser(tokens);
    std::vector<std::unique_ptr<Stmt>> statements = parser.parse();

    // Initialize the AstPrinter to print the AST.
    AstPrinter printer;
    for (const auto& stmt : statements) {
        std::cout << "AST: " << std::any_cast<std::string>(stmt->accept(printer)) << std::endl;
    }

    // Initialize the Interpreter to evaluate the expression and print the result.
    Interpreter interpreter;
    interpreter.interpret(statements);

    return 0;
}