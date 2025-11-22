#ifndef AST_H
#define AST_H

#include <string>
#include <list>
#include <ostream>
#include <vector>
using namespace std;

class Visitor;
class Decl;
class Block;
class Dec;

// Operadores binarios soportados
enum BinaryOp { 
    PLUS_OP, 
    MINUS_OP, 
    MUL_OP, 
    DIV_OP,
    POW_OP,
    LE_OP,
    GT_OP,
};

// Clase abstracta Exp
class Exp {
public:
    virtual int  accept(Visitor* visitor) = 0;
    virtual ~Exp() = 0;  // Destructor puro → clase abstracta
    static string binopToChar(BinaryOp op);  // Conversión operador → string
};

// Expresión binaria
class BinaryExp : public Exp {
public:
    Exp* left;
    Exp* right;
    BinaryOp op;
    int accept(Visitor* visitor);
    BinaryExp(Exp* l, Exp* r, BinaryOp op);
    ~BinaryExp();
};

class CondExp : public Exp {
public:
    Exp* condition;
    Exp* trueExp;
    Exp* falseExp;
    int accept(Visitor* visitor);
    CondExp(Exp* cond, Exp* tExp, Exp* fExp);
    ~CondExp();
};

// Expresión numérica
class NumberExp : public Exp {
public:
    int value;
    int accept(Visitor* visitor);
    NumberExp(int v);
    ~NumberExp();
};

// Expresión numérica
class IdExp : public Exp {
public:
    string value;
    int accept(Visitor* visitor);
    IdExp(string v);
    ~IdExp();
};


class Stm{
public:
    virtual int accept(Visitor* visitor) = 0;
    virtual ~Stm() = 0;
};

class StringExp : public Exp {
public:
    string value;
    int accept(Visitor* visitor);
    StringExp(string v);
    ~StringExp();
};


class Body{
public:
    vector<Dec*> decList;
    Body();
    ~Body();
    int accept(Visitor* visitor);
};




class IfStm: public Stm {
public:
    Exp* condition;
    Block* then;
    Block* els;
    IfStm(Exp* condition, Block* then, Block* els);
    int accept(Visitor* visitor);
    ~IfStm(){};
};

class CharExp : public Exp {
public:
    char value;
    int accept(Visitor* visitor);
    CharExp(char v);
    ~CharExp();
};

class BoolExp : public Exp {
public:
    bool value;
    int accept(Visitor* visitor);
    BoolExp(bool v);
    ~BoolExp();
};

class ArrayLiteral : public Exp {
public:
    vector<Exp*> elements;
    int accept(Visitor* visitor);
    ArrayLiteral();
    ~ArrayLiteral();
};

class LValueSuffix {
public:
    enum Type { FIELD, INDEX };
    Type type;
    string fieldName;
    Exp* index;

    LValueSuffix(string field);
    LValueSuffix(Exp* idx);
    ~LValueSuffix();
    int accept(Visitor* visitor);
};

class LValue : public Exp {
public:
    string id;
    vector<LValueSuffix*> suffixes;
    int accept(Visitor* visitor);
    LValue(string name);
    ~LValue();
};

class WhileStm: public Stm {
public:
    Exp* condition;
    Block* b;
    WhileStm(Exp* condition, Block* b);
    int accept(Visitor* visitor);
    ~WhileStm(){};
};



class AssignStm: public Stm {
public:
    LValue* lvalue;
    Exp* rvalue;
    AssignStm(LValue* lv, Exp* rv);
    ~AssignStm();
    int accept(Visitor* visitor);
};

class PrintStm: public Stm {
public:
    Exp* e;
    PrintStm(Exp*);
    ~PrintStm();
    int accept(Visitor* visitor);
};

class Block;

class ReturnStm: public Stm {
public:
    Exp* e;
    ReturnStm();
    ~ReturnStm();
    int accept(Visitor* visitor);
};

class FcallExp: public Exp {
public:
    string nombre;
    vector<Exp*> argumentos;
    int accept(Visitor* visitor);
    FcallExp();
    ~FcallExp();
};

class ArraySuffix {
public:
    bool hasSize;
    Exp* size;
    ArraySuffix();
    ArraySuffix(Exp* sz);
    ~ArraySuffix();
    int accept(Visitor* visitor);
};

class Param {
public:
    string type;
    vector<ArraySuffix*> arraySuffixes;
    string id;
    Param(string t, string name);
    ~Param();
    int accept(Visitor* visitor);
};

class Initializer {
public:
    Exp* value;
    Initializer(Exp* val);
    ~Initializer();
    int accept(Visitor* visitor);
};

class Declarator {
public:
    string id;
    vector<ArraySuffix*> arraySuffixes;
    Initializer* init;    
    Declarator(string name);
    ~Declarator();
    int accept(Visitor* visitor);
};


class FunDec{
public:
    string nombre;
    string tipo;
    vector<ArraySuffix*> returnArraySuffixes;
    vector<Param*> params;
    Block* body;
    FunDec();
    ~FunDec();
    int accept(Visitor* visitor);
};

class Decl {
public:
    string type;
    vector<Declarator*> declarators;
    Decl(string t);
    ~Decl();
    int accept(Visitor* visitor);
};

class FieldDeclarator {
public:
    string id;
    vector<ArraySuffix*> arraySuffixes;
    FieldDeclarator(string name);
    ~FieldDeclarator();
    int accept(Visitor* visitor);
};

class StructField {
    public:
        string type;
        vector<FieldDeclarator*> declarators;  
        StructField();
        ~StructField();
        int accept(Visitor* visitor);
};

class StructDec {
    public:
        string nombre;
        vector<StructField*> fields;
        StructDec(string n);
        ~StructDec();
        int accept(Visitor* visitor);
};

class Block {
public:
    vector<Decl*> declarations;
    vector<Stm*> statements;
    Block();
    ~Block();
    int accept(Visitor* visitor);
};

class Program{
public:
    Body* cuerpo;    
    Program(){};
    ~Program(){};
    int accept(Visitor* visitor);
};

class Dec {
public:
    enum Type { STRUCT_DECL, FUNC_DEF, DECL, STMT };
    Type type;
    StructDec* structDec;
    FunDec* funDec;
    Decl* decl;
    Stm* stmt;
    Dec(StructDec* sd);
    Dec(FunDec* fd);
    Dec(Decl* d);
    Dec(Stm* s);
    ~Dec();
    int accept(Visitor* visitor);
};


#endif // AST_H
