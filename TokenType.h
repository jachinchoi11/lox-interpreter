//
// Created by Jachin Choi on 1/31/25.
//

#ifndef TOKENTYPE_H
#define TOKENTYPE_H

enum TokenType {
  // singe character tokens
  LEFT_PAREN, RIGHT_PAREN, LEFT_BRACE, RIGHT_BRACE,
  COMMA, DOT, MINUS, PLUS, SEMICOLON, SLASH, STAR,

  // one or two character tokens
  BANG, BANG_EQUAL, EQUAL, EQUAL_EQUAL,
  GREATER, GREATER_EQUAL, LESS, LESS_EQUAL,

  // literals
  IDENTIFIER, STRING, NUMBER,

  // keywords
  AND, CLASS, ELSE, FOR, FUN, IF, NIL, OR,
  PRINT, RETURN, SUPER, THIS, TRUE, VAR, WHILE,
  EOF
};
#endif //TOKENTYPE_H
