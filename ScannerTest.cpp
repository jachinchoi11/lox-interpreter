//
// Created by Jachin Choi on 2/27/25.
//
#include "Scanner.h"
#include "TokenType.h"
#include "Token.h"
#include "gtest/gtest.h"
#include <vector>
#include <string>
#include <any>

std::vector<TokenType> extractTokenTypes(const std::vector<Token>& tokens) {
    std::vector<TokenType> types;
    for (const auto& token : tokens) {
        types.push_back(token.type);
    }
    return types;
}

TEST(ScannerTest, SimpleTokens) {
    std::string source = "(){};,.+-*/";
    Scanner scanner(source);
    std::vector<Token> tokens = scanner.scanTokens();

    std::vector<TokenType> expected = {
        TokenType::LEFT_PAREN, TokenType::RIGHT_PAREN,
        TokenType::LEFT_BRACE, TokenType::RIGHT_BRACE,
        TokenType::SEMICOLON, TokenType::COMMA, TokenType::DOT,
        TokenType::PLUS, TokenType::MINUS, TokenType::STAR, TokenType::SLASH,
        TokenType::END_OF
    };

    ASSERT_EQ(extractTokenTypes(tokens), expected);
}

TEST(ScannerTest, IdentifiersAndKeywords) {
    std::string source = "var x = 10; if (x > 5) print x;";
    Scanner scanner(source);
    std::vector<Token> tokens = scanner.scanTokens();

    std::vector<TokenType> expected = {
        TokenType::VAR, TokenType::IDENTIFIER, TokenType::EQUAL, TokenType::NUMBER,
        TokenType::SEMICOLON, TokenType::IF, TokenType::LEFT_PAREN, TokenType::IDENTIFIER,
        TokenType:: GREATER, TokenType::NUMBER, TokenType::RIGHT_PAREN,
        TokenType::PRINT, TokenType::IDENTIFIER, TokenType::SEMICOLON,
        TokenType::END_OF
    };

    ASSERT_EQ(extractTokenTypes(tokens), expected);
}

TEST(ScannerTest, StringLiterals) {
    std::string source = "\"hello world\"";
    Scanner scanner(source);
    std::vector<Token> tokens = scanner.scanTokens();

    ASSERT_EQ(tokens.size(), 2);  // String + EOF
    ASSERT_EQ(tokens[0].type, TokenType::STRING);
    ASSERT_EQ(std::any_cast<std::string>(tokens[0].literal), "hello world");
}

TEST(ScannerTest, NumberLiterals) {
    std::string source = "123";
    Scanner scanner(source);
    std::vector<Token> tokens = scanner.scanTokens();

    ASSERT_EQ(tokens.size(), 2);  // Two numbers + EOF
    ASSERT_EQ(tokens[0].type, TokenType::NUMBER);
    ASSERT_EQ(std::any_cast<int>(tokens[0].literal), 123);
}


// Test for unexpected characters
TEST(ScannerTest, UnexpectedCharacter) {
    std::string source = "$";
    Scanner scanner(source);

    testing::internal::CaptureStderr();
    std::vector<Token> tokens = scanner.scanTokens();
    std::string error_message = testing::internal::GetCapturedStderr();

    ASSERT_TRUE(error_message.find("Scanner error: unexpected character") != std::string::npos);
}

