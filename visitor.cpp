#include <iostream>
#include <sstream>
#include "ast.h"
#include "visitor.h"
#include <unordered_map>
using namespace std;

///////////////////////////////////////////////////////////////////////////////////

int BinaryExp::accept(Visitor* visitor) {
    return visitor->visit(this);
}

int NumberExp::accept(Visitor* visitor) {
    return visitor->visit(this);
}


int Program::accept(Visitor* visitor) {
    return visitor->visit(this);
}

int IdExp::accept(Visitor* visitor) {
    return visitor->visit(this);
}


int PrintStm::accept(Visitor* visitor) {
    return visitor->visit(this);
}

int AssignStm::accept(Visitor* visitor) {
    return visitor->visit(this);
}

int IfStm::accept(Visitor* visitor) {
    return visitor->visit(this);
}

int WhileStm::accept(Visitor* visitor) {
    return visitor->visit(this);
}

int Body::accept(Visitor* visitor){
    return visitor->visit(this);
}

int FcallExp::accept(Visitor* visitor) {
    return visitor->visit(this);
}

int ReturnStm::accept(Visitor* visitor){
    return visitor->visit(this);
}

int TCondExp::accept(Visitor* visitor) {
    return visitor->visit(this);
}

int StringExp::accept(Visitor* visitor) {
    return visitor->visit(this);
}

int CharExp::accept(Visitor* visitor) {
    return visitor->visit(this);
}

int BoolExp::accept(Visitor* visitor) {
    return visitor->visit(this);
}

int ArrayLiteral::accept(Visitor* visitor) {
    return visitor->visit(this);
}

int LValueSuffix::accept(Visitor* visitor) {
    return visitor->visit(this);
}

int LValue::accept(Visitor* visitor) {
    return visitor->visit(this);
}

int ArraySuffix::accept(Visitor* visitor) {
    return visitor->visit(this);
}

int Param::accept(Visitor* visitor) {
    return visitor->visit(this);
}

int Initializer::accept(Visitor* visitor) {
    return visitor->visit(this);
}

int Declarator::accept(Visitor* visitor) {
    return visitor->visit(this);
}

int FunDec::accept(Visitor* visitor) {
    return visitor->visit(this);
}

int Decl::accept(Visitor* visitor) {
    return visitor->visit(this);
}

int FieldDeclarator::accept(Visitor* visitor) {
    return visitor->visit(this);
}

int StructField::accept(Visitor* visitor) {
    return visitor->visit(this);
}

int StructDec::accept(Visitor* visitor) {
    return visitor->visit(this);
}

int Block::accept(Visitor* visitor) {
    return visitor->visit(this);
}

int Dec::accept(Visitor* visitor) {
    return visitor->visit(this);
}

int Libreria::accept(Visitor* visitor) {
    return visitor->visit(this);
}

///////////////////////////////////////////////////////////////////////////////////

int GenCodeVisitor::generar(Program* program) {
    program->accept(this);
    return 0;
}

int GenCodeVisitor::visit(Program* program) {
    out << ".section .data\n";
    out << "print_fmt: .asciz \"%d\\n\"\n";
    out << ".section .text\n";
    program->cuerpo->accept(this);
    out << ".section note.GNU-stack,\"\",@progbits\n" << endl;
    return 0;
}



int GenCodeVisitor::visit(NumberExp* exp) {
    if (entornoFuncion) {
        out << " movq $" << exp->value << ", %rax" << endl;
    } else {
        out << exp->value << endl;
    }
    return 0;
}

int GenCodeVisitor::visit(IdExp* exp) {
    if (memoriaGlobal.count(exp->value))
        out << " movq " << exp->value << "(%rip), %rax"<<endl;
    else
        out << " movq " << memoria.lookup(exp->value) << "(%rbp), %rax"<<endl;
    return 0;
}

int GenCodeVisitor::visit(BinaryExp* exp) {
    exp->left->accept(this);
    out << " pushq %rax\n";
    exp->right->accept(this);
    out << " movq %rax, %rcx\n popq %rax\n";

    switch (exp->op) {
        case PLUS_OP:  out << " addq %rcx, %rax\n"; break;
        case MINUS_OP: out << " subq %rcx, %rax\n"; break;
        case MUL_OP:   out << " imulq %rcx, %rax\n"; break;
        case LE_OP:
            out << " cmpq %rcx, %rax\n"
                      << " movl $0, %eax\n"
                      << " setle %al\n"
                      << " movzbq %al, %rax\n";
            break;
    }
    return 0;
}


int GenCodeVisitor::visit(AssignStm* stm) {
    stm->rvalue->accept(this);
    out << " pushq %rax\n";
    
    LValue* lv = stm->lvalue;
    
    if (lv->suffixes.empty()) {
        if (memoriaGlobal.count(lv->id)) {
            out << " popq %rax\n";
            out << " movq %rax, " << lv->id << "(%rip)\n";
        } else if (memoria.check(lv->id)) {
            out << " popq %rax\n";
            out << " movq %rax, " << memoria.lookup(lv->id) << "(%rbp)\n";
        }
    } else {
        if (memoriaGlobal.count(lv->id)) {
            out << " leaq " << lv->id << "(%rip), %rcx\n";
        } else if (memoria.check(lv->id)) {
            out << " leaq " << memoria.lookup(lv->id) << "(%rbp), %rcx\n";
        }
        for (auto suffix : lv->suffixes) {
            if (suffix->type == LValueSuffix::FIELD) {
                out << " addq $8, %rcx\n";
            } else if (suffix->type == LValueSuffix::INDEX) {
                out << " pushq %rcx\n";
                suffix->index->accept(this);
                out << " imulq $8, %rax\n";
                out << " popq %rcx\n";
                out << " addq %rax, %rcx\n";
            }
        }
        out << " popq %rax\n";
        out << " movq %rax, (%rcx)\n";
    }
    return 0;
}

int GenCodeVisitor::visit(PrintStm* stm) {
    stm->e->accept(this);
    out <<
        " movq %rax, %rsi\n"
        " leaq print_fmt(%rip), %rdi\n"
        " movl $0, %eax\n"
        " call printf@PLT\n";
            return 0;
}



int GenCodeVisitor::visit(Body* b) {
    for (auto dec : b->decList){
        dec->accept(this);
    }
    return 0;
}

int GenCodeVisitor::visit(IfStm* stm) {
    int label = labelcont++;
    int prev_offset;
    stm->condition->accept(this);
    out << " cmpq $0, %rax"<<endl;
    out << " je else_" << label << endl;
    prev_offset = offset;
    stm->then->accept(this);
    out << " jmp endif_" << label << endl;
    out << " else_" << label << ":"<< endl;
    if (stm->els) stm->els->accept(this);
    out << "endif_" << label << ":"<< endl;
    return 0;
}

int GenCodeVisitor::visit(WhileStm* stm) {
    int label = labelcont++;
    out << "while_" << label << ":"<<endl;
    stm->condition->accept(this);
    out << " cmpq $0, %rax" << endl;
    out << " je endwhile_" << label << endl;
    stm->b->accept(this);
    out << " jmp while_" << label << endl;
    out << "endwhile_" << label << ":"<< endl;
    return 0;
}


int GenCodeVisitor::visit(ReturnStm* stm) {
    stm->e->accept(this);
    out << " jmp .end_"<<nombreFuncion << endl;
    return 0;
}

int GenCodeVisitor::visit(FcallExp* exp) {
    vector<std::string> argRegs = {"%rdi", "%rsi", "%rdx", "%rcx", "%r8", "%r9"};
    int size = exp->argumentos.size();
    for (int i = 0; i < size; i++) {
        exp->argumentos[i]->accept(this);
        out << " mov %rax, " << argRegs[i] <<endl;
    }
    out << "call " << exp->nombre << endl;
    return 0;
}

int GenCodeVisitor::visit(TCondExp* exp) {
    return 0;
}

int GenCodeVisitor::visit(StringExp* exp) {
    return 0;
}

int GenCodeVisitor::visit(CharExp* exp) {
    return 0;
}

int GenCodeVisitor::visit(BoolExp* exp) {
    return 0;
}

int GenCodeVisitor::visit(ArrayLiteral* exp) {
    return 0;
}

int GenCodeVisitor::visit(LValueSuffix* s) {
    return 0;
}

int GenCodeVisitor::visit(LValue* lv) {
    if (lv->suffixes.empty()) {
        if (memoriaGlobal.count(lv->id)) {
            out << " movq " << lv->id << "(%rip), %rax\n";
        } else if (memoria.check(lv->id)) {
            out << " movq " << memoria.lookup(lv->id) << "(%rbp), %rax\n";
        }
    } else {
        if (memoriaGlobal.count(lv->id)) {
            out << " leaq " << lv->id << "(%rip), %rax\n";
        } else if (memoria.check(lv->id)) {
            out << " leaq " << memoria.lookup(lv->id) << "(%rbp), %rax\n";
        }
        for (auto suffix : lv->suffixes) {
            if (suffix->type == LValueSuffix::FIELD) {
                out << " addq $8, %rax\n";
            } else if (suffix->type == LValueSuffix::INDEX) {
                out << " pushq %rax\n";
                suffix->index->accept(this);
                out << " imulq $8, %rax\n";
                out << " popq %rcx\n";
                out << " addq %rcx, %rax\n";
            }
        }
        out << " movq (%rax), %rax\n";
    }
    return 0;
}

int GenCodeVisitor::visit(ArraySuffix* s) {
    return 0;
}

int GenCodeVisitor::visit(Param* param) {
    return 0;
}

int GenCodeVisitor::visit(Initializer* i) {
    if (i->value) {
        i->value->accept(this);
    }
    return 0;
}

int GenCodeVisitor::visit(Declarator* decl) {
    return 0;
}

int GenCodeVisitor::visit(FunDec* fd) {
    nombreFuncion = fd->nombre;
    entornoFuncion = true;
    memoria.clear();
    memoria.add_level();
    offset = -8;
    
    out << "\n.globl " << fd->nombre << "\n";
    out << fd->nombre << ":\n";
    out << " pushq %rbp\n";
    out << " movq %rsp, %rbp\n";
    
    vector<string> argRegs = {"%rdi", "%rsi", "%rdx", "%rcx", "%r8", "%r9"};
    int size = fd->params.size();
    for (int i = 0; i < size; i++) {
        memoria.add_var(fd->params[i]->id, offset);
        offset -= 8;
    }
    
    // Calcular el offset
    stringstream bodyCode;
    streambuf* oldBuf = out.rdbuf(bodyCode.rdbuf());
    
    for (int i = 0; i < size; i++) {
        out << " movq " << argRegs[i] << ", " << memoria.lookup(fd->params[i]->id) << "(%rbp)\n";
    }
    
    if (fd->body) {
        fd->body->accept(this);
    }
    
    out.rdbuf(oldBuf);
    
    int espNecesario = -(offset);
    espNecesario = (espNecesario + 15) & ~15;
    
    out << " subq $" << espNecesario << ", %rsp\n";
    out << bodyCode.str();
    out << ".end_" << fd->nombre << ":\n";
    out << " leave\n";
    out << " ret\n";

    entornoFuncion = false;
    memoria.remove_level();
    return 0;
}

int GenCodeVisitor::visit(Decl* decl) {
    for (auto declarator : decl->declarators) {
        if (entornoFuncion) {
            int varSize = 8;
            if (decl->type.find("struct") == 0) {
                string structName = decl->type.substr(7);
                if (struct_campos.count(structName)) {
                    varSize = struct_campos[structName].size() * 8;
                }
            }
            for (auto suffix : declarator->arraySuffixes) {
                if (suffix->hasSize) {
                    varSize *= 10;
                }
            }
            memoria.add_var(declarator->id, offset);
            offset -= varSize;
            
            if (declarator->init) {
                declarator->init->accept(this);
                out << " movq %rax, " << memoria.lookup(declarator->id) << "(%rbp)\n";
            }
        } else {
            memoriaGlobal[declarator->id] = true;
            out << ".section .data\n";
            out << declarator->id << ": .quad 0\n";
            out << ".section .text\n";
        }
    }
    return 0;
}

int GenCodeVisitor::visit(FieldDeclarator* fdecl) {
    return 0;
}

int GenCodeVisitor::visit(StructField* sfield) {
    return 0;
}

int GenCodeVisitor::visit(StructDec* sdec) {
    unordered_map<string, int> campos;
    int currentOffset = 0;
    
    for (auto field : sdec->fields) {
        for (auto declarator : field->declarators) {
            campos[declarator->id] = currentOffset;
            currentOffset += 8;
        }
    }
    struct_campos[sdec->nombre] = campos;
    return 0;
}

int GenCodeVisitor::visit(Block* b) {
    // Procesar declaraciones
    for (auto decl : b->declarations) {
        decl->accept(this);
    }
    // Procesar sentencias
    for (auto stmt : b->statements) {
        stmt->accept(this);
    }
    return 0;
}

int GenCodeVisitor::visit(Dec* d) {
    switch (d->type) {
        case Dec::STRUCT_DECL:
            if (d->structDec) d->structDec->accept(this);
            break;
        case Dec::FUNC_DEF:
            if (d->funDec) d->funDec->accept(this);
            break;
        case Dec::DECL:
            if (d->decl) d->decl->accept(this);
            break;
        case Dec::STMT:
            if (d->stmt) d->stmt->accept(this);
            break;
    }
    return 0;
}

int GenCodeVisitor::visit(Libreria* l) {
    return 0;
}