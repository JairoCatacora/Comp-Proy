#ifndef PARSER_H       
#define PARSER_H

#include "scanner.h"    // Incluye la definición del escáner (provee tokens al parser)
#include "ast.h"        // Incluye las definiciones para construir el Árbol de Sintaxis Abstracta (AST)

class Parser {
private:
    Scanner* scanner;       // Puntero al escáner, de donde se leen los tokens
    Token *current, *previous; // Punteros al token actual y al anterior
    bool match(Token::Type ttype);   // Verifica si el token actual coincide con un tipo esperado y avanza si es así
    bool check(Token::Type ttype);   // Comprueba si el token actual es de cierto tipo, sin avanzar
    bool advance();                  // Avanza al siguiente token
    bool isAtEnd();                  // Comprueba si ya se llegó al final de la entrada
public:
    Parser(Scanner* scanner);       
    Program* parseProgram();
    Body* parseBody();
    Dec* parseDec();
    StructDec* parseStructDec();
    StructField* parseStructField();
    FieldDeclarator* parseFieldDeclarator();
    Decl* parseDecl();
    Declarator* parseDeclarator();
    ArraySuffix* parseArraySuffix();
    Initializer* parseInit();
    Exp* parseInitializer();
    FunDec* parseFunDec();
    Param* parseParam();
    Block* parseFuncBody();
    Block* parseBlock();
    Stm* parseStm();
    AssignStm* parseAssignStmt();
    ReturnStm* parseReturnStmt();
    LValue* parseLValue();
    LValueSuffix* parseLValueSuffix();
    Exp* parseTCondExp();
    Exp* parseCE();
    Exp* parseBE();
    Exp* parseE();
    Exp* parseT();
    Exp* parseF();
    ArrayLiteral* parseArrayLiteral();
    string parseType();
};

#endif // PARSER_H      