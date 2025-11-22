#include "ast.h"
#include <iostream>

using namespace std;

// ------------------ Exp ------------------
Exp::~Exp() {}

string Exp::binopToChar(BinaryOp op) {
    switch (op) {
        case PLUS_OP:  return "+";
        case MINUS_OP: return "-";
        case MUL_OP:   return "*";
        case DIV_OP:   return "/";
        case POW_OP:   return "**";
        case LE_OP:   return "<";
        case GT_OP:    return ">";
        default:       return "?";
    }
}

// ------------------ BinaryExp ------------------
BinaryExp::BinaryExp(Exp* l, Exp* r, BinaryOp o)
    : left(l), right(r), op(o) {}

    
BinaryExp::~BinaryExp() {
    delete left;
    delete right;
}

CondExp::CondExp(Exp* cond, Exp* tExp, Exp* fExp)
    : condition(cond), trueExp(tExp), falseExp(fExp) {}

CondExp::~CondExp() {}

// ------------------ NumberExp ------------------
NumberExp::NumberExp(int v) : value(v) {}

NumberExp::~NumberExp() {}


// ------------------idExp ------------------
IdExp::IdExp(string v) : value(v) {}

IdExp::~IdExp() {}


Stm::~Stm(){}

PrintStm::~PrintStm(){}

AssignStm::~AssignStm(){}

IfStm::IfStm(Exp* c, Block* t, Block* e) 
    : condition(c), then(t), els(e) {}

WhileStm::WhileStm(Exp* c, Block* b) 
    : condition(c), b(b) {}

PrintStm::PrintStm(Exp* expresion){
    e = expresion;
}

AssignStm::AssignStm(LValue* lv, Exp* rv) 
    : lvalue(lv), rvalue(rv) {}

Body::Body(){}
Body::~Body(){}

StructDec::StructDec(string n) : nombre(n) {}
StructDec::~StructDec() {}

StructField::StructField() {}
StructField::~StructField() {}

StringExp::StringExp(string v) : value(v) {}
StringExp::~StringExp() {}

CharExp::CharExp(char v) : value(v) {}
CharExp::~CharExp() {}

BoolExp::BoolExp(bool v) : value(v) {}
BoolExp::~BoolExp() {}

ArrayLiteral::ArrayLiteral() {}
ArrayLiteral::~ArrayLiteral() {}

LValueSuffix::LValueSuffix(string field) 
    : type(FIELD), fieldName(field), index(nullptr) {}
LValueSuffix::LValueSuffix(Exp* idx) 
    : type(INDEX), index(idx) {}
LValueSuffix::~LValueSuffix() {}

LValue::LValue(string name) : id(name) {}
LValue::~LValue() {}

FcallExp::FcallExp() {}
FcallExp::~FcallExp() {}

ReturnStm::ReturnStm() {}
ReturnStm::~ReturnStm() {}

ArraySuffix::ArraySuffix() : hasSize(false), size(nullptr) {}
ArraySuffix::ArraySuffix(Exp* sz) : hasSize(true), size(sz) {}
ArraySuffix::~ArraySuffix() {}

Initializer::Initializer(Exp* val) : value(val) {}
Initializer::~Initializer() {}

Declarator::Declarator(string name) : id(name), init(nullptr) {}
Declarator::~Declarator() {}

Decl::Decl(string t) : type(t) {}
Decl::~Decl() {}

FieldDeclarator::FieldDeclarator(string name) : id(name) {}
FieldDeclarator::~FieldDeclarator() {}

Block::Block() {}
Block::~Block() {}

Param::Param(string t, string name) : type(t), id(name) {}
Param::~Param() {}

FunDec::FunDec() 
    : tipo(""), nombre(""), body(nullptr) {}
FunDec::~FunDec() {}

Dec::Dec(StructDec* sd) 
    : type(STRUCT_DECL), structDec(sd), funDec(nullptr), decl(nullptr), stmt(nullptr) {}
Dec::Dec(FunDec* fd) 
    : type(FUNC_DEF), structDec(nullptr), funDec(fd), decl(nullptr), stmt(nullptr) {}
Dec::Dec(Decl* d) 
    : type(DECL), structDec(nullptr), funDec(nullptr), decl(d), stmt(nullptr) {}
Dec::Dec(Stm* s) 
    : type(STMT), structDec(nullptr), funDec(nullptr), decl(nullptr), stmt(s) {}
Dec::~Dec() {}