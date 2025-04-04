

#include <iostream>
#include "Run.h"
#include "Scanner.h"
#include "Error.h"
#include "AstPrinter.h"
#include "Interpreter.h"
#include "Parser.h"


int main(int argc, char *argv[]) {

    Interpreter interpreter;
    std::string source;

    std::cout << "Lox Interpreter (type 'exit' to quit)\n";

    while (true) {
        std::cout << "> "; // Prompt

        if (!std::getline(std::cin, source) || source == "exit") {
            break;
        }

        if (source.empty()) {
            continue;
        }

        Scanner scanner(source);
        std::vector<Token> tokens = scanner.scanTokens();

        for (const auto& token : tokens) {
            std::cout << "Token: " << tokenTypeToString(token.type)
                      << ", Lexeme: \"" << token.lexeme << "\"" << std::endl;
        }

        Parser parser(tokens);
        std::vector<std::unique_ptr<Stmt>> statements = parser.parse();

        AstPrinter printer;
        for (const auto& stmt : statements) {
            std::cout << "AST: " << std::any_cast<std::string>(stmt->accept(printer)) << std::endl;
        }

        interpreter.interpret(statements);
    }

    return 0;
}