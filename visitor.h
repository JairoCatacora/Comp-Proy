#ifndef VISITOR_H
#define VISITOR_H
#include "ast.h"
#include <list>
#include <vector>
#include <unordered_map>
#include <string>
#include "environment.h"

using namespace std;

class BinaryExp;
class NumberExp;
class Program;
class PrintStm;
class WhileStm;
class IfStm;
class AssignStm;
class Body;
class FcallExp;
class ReturnStm;

class Visitor {
public:
    // 
    virtual int visit(BinaryExp* exp) = 0;
    virtual int visit(NumberExp* exp) = 0;
    virtual int visit(IdExp* exp) = 0;
    virtual int visit(Program* p) = 0;
    virtual int visit(PrintStm* stm) = 0;
    virtual int visit(WhileStm* stm) = 0;
    virtual int visit(IfStm* stm) = 0;
    virtual int visit(AssignStm* stm) = 0;
    virtual int visit(Body* body) = 0;
    virtual int visit(FcallExp* fcall) = 0;
    virtual int visit(ReturnStm* r) = 0;
    virtual int visit(TCondExp* exp) = 0;
    virtual int visit(StringExp* exp) = 0;
    virtual int visit(CharExp* exp) = 0;
    virtual int visit(BoolExp* exp) = 0;
    virtual int visit(ArrayLiteral* exp) = 0;
    virtual int visit(LValueSuffix* s) = 0;
    virtual int visit(LValue* lv) = 0;
    virtual int visit(ArraySuffix* s) = 0;
    virtual int visit(Param* param) = 0;
    virtual int visit(Initializer* i) = 0;
    virtual int visit(Declarator* decl) = 0;
    virtual int visit(FunDec* fd) = 0;
    virtual int visit(Decl* decl) = 0;
    virtual int visit(FieldDeclarator* fdecl) = 0;
    virtual int visit(StructField* sfield) = 0;
    virtual int visit(StructDec* sdec) = 0;
    virtual int visit(Block* b) = 0;
    virtual int visit(Dec* d) = 0;
    virtual int visit(Libreria* l) = 0;
};


class GenCodeVisitor : public Visitor {
private:
    std::ostream& out;
public:
    unordered_map<string, int> reserva_memoria;
    GenCodeVisitor(std::ostream& out) : out(out) {}
    int generar(Program* program);
    Environment<int> memoria;
    unordered_map<string, bool> memoriaGlobal;
    unordered_map<string, unordered_map<string, int>> struct_campos;
    int offset = -8;
    int labelcont = 0;
    bool entornoFuncion = false;
    string nombreFuncion;
    int visit(BinaryExp* exp) override;
    int visit(NumberExp* exp) override;
    int visit(IdExp* exp) override;
    int visit(Program* p) override ;
    int visit(PrintStm* stm) override;
    int visit(AssignStm* stm) override;
    int visit(WhileStm* stm) override;
    int visit(IfStm* stm) override;
    int visit(Body* body) override;
    int visit(FcallExp* fcall) override;
    int visit(ReturnStm* r) override;
    int visit(TCondExp* exp) override;
    int visit(StringExp* exp) override;
    int visit(CharExp* exp) override;
    int visit(BoolExp* exp) override;
    int visit(ArrayLiteral* exp) override;
    int visit(LValueSuffix* s) override;
    int visit(LValue* lv) override;
    int visit(ArraySuffix* s) override;
    int visit(Param* param) override;
    int visit(Initializer* i) override;
    int visit(Declarator* decl) override;
    int visit(FunDec* fd) override;
    int visit(Decl* decl) override;
    int visit(FieldDeclarator* fdecl) override;
    int visit(StructField* sfield) override;
    int visit(StructDec* sdec) override;
    int visit(Block* b) override;
    int visit(Dec* d) override;
    int visit(Libreria* l) override;
};

#endif // VISITOR_H