#include<iostream>
#include "token.h"
#include "scanner.h"
#include "ast.h"
#include "parser.h"

using namespace std;

// =============================
// Métodos de la clase Parser
// =============================

Parser::Parser(Scanner* sc) : scanner(sc) {
    previous = nullptr;
    current = scanner->nextToken();
    if (current->type == Token::ERR) {
        throw runtime_error("Error léxico");
    }
}

bool Parser::match(Token::Type ttype) {
    if (check(ttype)) {
        advance();
        return true;
    }
    return false;
}

bool Parser::check(Token::Type ttype) {
    if (isAtEnd()) return false;
    return current->type == ttype;
}

bool Parser::advance() {
    if (!isAtEnd()) {
        Token* temp = current;
        if (previous) delete previous;
        current = scanner->nextToken();
        previous = temp;

        if (check(Token::ERR)) {
            throw runtime_error("Error lexico");
        }
        return true;
    }
    return false;
}

bool Parser::isAtEnd() {
    return (current->type == Token::END);
}


// =============================
// Reglas gramaticales
// =============================

Program* Parser::parseProgram() {
    Program* p = new Program();
    p->cuerpo = parseBody();
    cout << "Parser exitoso" << endl;
    return p;
}

Dec* Parser::parseDec() {
    if (check(Token::STRUCT)) {
        return new Dec(parseStructDec());
    }
    if (check(Token::ID)) {
        string type = current->text;
        advance();
        vector<ArraySuffix*> arraySuffixes;
        while (check(Token::CORL)) {
            arraySuffixes.push_back(parseArraySuffix());
        }
        string name = current->text;
        advance();
        if (check(Token::LPAREN)) {
            FunDec* fd = new FunDec();
            fd->tipo = type;
            fd->nombre = name;
            fd->returnArraySuffixes = arraySuffixes;
            match(Token::LPAREN);
            if (!check(Token::RPAREN)) {
                fd->params.push_back(parseParam());
                while (match(Token::COMA)) {
                    fd->params.push_back(parseParam());
                }
            }
            match(Token::RPAREN);
            fd->body = parseFuncBody();
            return new Dec(fd);
        }
        else {
            Decl* decl = new Decl(type);
            Declarator* declarator = new Declarator(name);
            declarator->arraySuffixes = arraySuffixes;
            while (check(Token::CORL)) {
                declarator->arraySuffixes.push_back(parseArraySuffix());
            }   
            if (check(Token::ASSIGN)) {
                declarator->init = parseInit();
            }
            decl->declarators.push_back(declarator);
            while (match(Token::COMA)) {
                decl->declarators.push_back(parseDeclarator());
            }
            match(Token::SEMICOL);
            return new Dec(decl);
        }
    }
    if (check(Token::PRINT) || check(Token::IF) || 
        check(Token::WHILE) || check(Token::RETURN)) {
        return new Dec(parseStm());
    }
}

Body* Parser::parseBody(){
    Body* b = new Body();
    while (!isAtEnd() && (check(Token::STRUCT) || check(Token::ID) || 
           check(Token::PRINT) || check(Token::IF) || check(Token::WHILE) || 
           check(Token::RETURN))) {
        b->decList.push_back(parseDec());
    }
    return b;
}

Stm* Parser::parseStm() {
    Stm* a;
    Exp* e;
    if (check(Token::ID)) {
        LValue* lv = parseLValue();
        match(Token::ASSIGN);
        e = parseCE();
        return new AssignStm(lv, e);
    }
    else if(match(Token::PRINT)){
        match(Token::LPAREN);
        e = parseCE();
        match(Token::RPAREN);
        return new PrintStm(e);
    }
    else if(match(Token::RETURN)) {
        ReturnStm* r  = new ReturnStm();
        r->e = parseCE();
        match(Token::SEMICOL);
        return r;
    }
    else if (match(Token::IF)) {
        match(Token::LPAREN);
        Exp* cond = parseCE();
        match(Token::RPAREN);
        match(Token::LLAVEL);
        Block* t = parseBlock();
        match(Token::LLAVER);
        match(Token::ELSE);
        match(Token::LLAVEL);
        Block* e = parseBlock();
        match(Token::LLAVER);        
        return new IfStm(cond, t, e);
    }
    else if (match(Token::WHILE)) {
        match(Token::LPAREN);
        e = parseCE();
        match(Token::RPAREN);
        match(Token::LLAVEL);
        Block* body = parseBlock();
        match(Token::LLAVER);
        a = new WhileStm(e, body);
    }
    else{
        throw runtime_error("Error sintáctico");
    }
    return a;
}

StructDec* Parser::parseStructDec() {
    match(Token::STRUCT);
    string name = current->text;
    advance();
    StructDec* sd = new StructDec(name);
    match(Token::LLAVEL);
    while (!check(Token::LLAVER) && !isAtEnd()) {
        sd->fields.push_back(parseStructField());
    }
    match(Token::LLAVER);
    match(Token::SEMICOL);
    
    return sd;
}

StructField* Parser::parseStructField() {
    string type = parseType();
    StructField* sf = new StructField();
    sf->type = type;
    sf->declarators.push_back(parseFieldDeclarator());
    while (match(Token::COMA)) {
        sf->declarators.push_back(parseFieldDeclarator());
    }
    match(Token::SEMICOL);
    return sf;
}

FieldDeclarator* Parser::parseFieldDeclarator() {
    string name = current->text;
    advance();    
    FieldDeclarator* fd = new FieldDeclarator(name);
    while (check(Token::CORL)) {
        fd->arraySuffixes.push_back(parseArraySuffix());
    }
    return fd;
}

Decl* Parser::parseDecl() {
    string type = parseType();
    Decl* decl = new Decl(type);    
    decl->declarators.push_back(parseDeclarator());
    while (match(Token::COMA)) {
        decl->declarators.push_back(parseDeclarator());
    }
    match(Token::SEMICOL);
    return decl;
}

Declarator* Parser::parseDeclarator() {
    string name = current->text;
    advance();    
    Declarator* declarator = new Declarator(name);
    while (check(Token::CORL)) {
        declarator->arraySuffixes.push_back(parseArraySuffix());
    }
    if (check(Token::ASSIGN)) {
        declarator->init = parseInit();
    }
    return declarator;
}

vector<ArraySuffix*> Parser::parseArraySuffixList() {
    vector<ArraySuffix*> suffixes;    
    do {
        suffixes.push_back(parseArraySuffix());
    } while (check(Token::CORL));
    return suffixes;
}

ArraySuffix* Parser::parseArraySuffix() {
    match(Token::CORL);
    if (check(Token::CORR)) {
        match(Token::CORR);
        return new ArraySuffix();
    } else {
        Exp* size = parseCE();
        match(Token::CORR);
        return new ArraySuffix(size);
    }
}

Initializer* Parser::parseInit() {
    match(Token::ASSIGN);
    return new Initializer(parseInitializer());
}

Exp* Parser::parseInitializer() {
    if (check(Token::LLAVEL)) {
        return parseArrayLiteral();
    } else {
        return parseCE();
    }
}

Param* Parser::parseParam() {
    string type = parseType();
    vector<ArraySuffix*> arraySuffixes;
    while (check(Token::CORL)) {
        arraySuffixes.push_back(parseArraySuffix());
    }
    string name = current->text;
    advance();
    Param* param = new Param(type, name);
    param->arraySuffixes = arraySuffixes;
    return param;
}

Block* Parser::parseFuncBody() {
    match(Token::LLAVEL);
    Block* block = parseBlock();
    match(Token::LLAVER);
    return block;
}

Block* Parser::parseBlock() {
    Block* block = new Block();
    while (check(Token::ID)) {
        Token* saved = current;
        string possibleType = current->text;
        advance();
        if (check(Token::ID) || check(Token::COMA) || check(Token::CORL)) {
            delete previous;
            previous = nullptr;
            current = saved;
            
            block->declarations.push_back(parseDecl());
        } else {
            delete previous;
            previous = nullptr;
            current = saved;
            break;
        }
    }
    if (!check(Token::LLAVER) && !isAtEnd()) {
        block->statements.push_back(parseStm());
        while (match(Token::SEMICOL)) {
            if (!check(Token::LLAVER) && !isAtEnd()) {
                block->statements.push_back(parseStm());
            }
        }
    }
    return block;
}

LValue* Parser::parseLValue() {
    string name = current->text;
    advance();
    LValue* lv = new LValue(name);
    while (check(Token::PUNTO) || check(Token::CORL)) {
        lv->suffixes.push_back(parseLValueSuffix());
    }
    return lv;
}

LValueSuffix* Parser::parseLValueSuffix() {
    if (match(Token::PUNTO)) {
        string field = current->text;
        advance();
        return new LValueSuffix(field);
    } 
    else if (match(Token::CORL)) {
        Exp* index = parseCE();
        match(Token::CORR);
        return new LValueSuffix(index);
    }
}

Exp* Parser::parseCEondExp() {
    Exp* condition = parseCE();
    if (match(Token::QUESTION)) {
        Exp* trueExp = parseCE();
        match(Token::DOSPUNTOS);
        Exp* falseExp = parseCE();
        return new CondExp(condition, trueExp, falseExp);
    }
    return condition;
}

Exp* Parser::parseCE() {
    Exp* l = parseBE();
    if (match(Token::LE) || match(Token::GT)) {
        BinaryOp op;
        if (previous->type == Token::LE){
            op = LE_OP;
        }
        else{
            op = GT_OP;
        }
        Exp* r = parseBE();
        l = new BinaryExp(l, r, op);
    }
    return l;
}


Exp* Parser::parseBE() {
    Exp* l = parseE();
    while (match(Token::PLUS) || match(Token::MINUS)) {
        BinaryOp op;
        if (previous->type == Token::PLUS){
            op = PLUS_OP;
        }
        else{
            op = MINUS_OP;
        }
        Exp* r = parseE();
        l = new BinaryExp(l, r, op);
    }
    return l;
}


Exp* Parser::parseE() {
    Exp* l = parseT();
    while (match(Token::MUL) || match(Token::DIV)) {
        BinaryOp op;
        if (previous->type == Token::MUL){
            op = MUL_OP;
        }
        else{
            op = DIV_OP;
        }
        Exp* r = parseT();
        l = new BinaryExp(l, r, op);
    }
    return l;
}


Exp* Parser::parseT() {
    Exp* l = parseF();
    if (match(Token::POW)) {
        BinaryOp op = POW_OP;
        Exp* r = parseF();
        l = new BinaryExp(l, r, op);
    }
    return l;
}

Exp* Parser::parseF() {
    Exp* e;
    string nom;
    if (match(Token::NUM)) {
        return new NumberExp(stoi(previous->text));
    }
    else if (match(Token::TRUE)) {
        return new BoolExp(true);
    }
    else if (match(Token::FALSE)) {
        return new BoolExp(false);
    }
    else if (match(Token::LPAREN))
    {
        e = parseCE();
        match(Token::RPAREN);
        return e;
    }
    else if (check(Token::ID)) {
        return parseLValue();
    }
    else if (check(Token::LLAVEL)) {
        return parseArrayLiteral();
    }
    else {
        throw runtime_error("Error sintáctico");
    }
}

ArrayLiteral* Parser::parseArrayLiteral() {
    match(Token::LLAVEL);
    ArrayLiteral* al = new ArrayLiteral();
    if (!check(Token::LLAVER)) {
        al->elements.push_back(parseCE());
        
        while (match(Token::COMA)) {
            al->elements.push_back(parseCE());
        }
    }    
    match(Token::LLAVER);
    return al;
}

string Parser::parseType() {
    string type = current->text;
    advance();
    return type;
}