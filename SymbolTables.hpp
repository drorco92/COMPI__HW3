//
// Created by user on 19/12/2021.
//

#ifndef COMPI__HW3_SYMBOLTABLES_HPP
#define COMPI__HW3_SYMBOLTABLES_HPP


#include <vector>
#include <string>
#include <stack>
#include "Structs.hpp"


class Symbol {
public:
    std::string name;
    int offset;
    std::string type;
    Symbol(std::string name, int offset, std::string type);
    virtual void print();
};

typedef std::vector<Symbol> SymbolsVector;

class Symbol_Table {
public:
    Symbol_Table* parent = nullptr;
    SymbolsVector symbols ;
    Symbol_Table() = default;
    explicit Symbol_Table(Symbol_Table* parent) : parent(parent) {}
    ~Symbol_Table() = default;
};


typedef std::vector<Argument> ArgVec;
typedef std::vector<Symbol_Table> TableVector;
typedef std::stack<int> OffsetStack;




class Variable : public Symbol {
public:
    std::string type_annotation;
    Variable(std::string name, int offset, std::string type, std::string type_annotation);
    void print() override;
};

class Function : public Symbol {
public:
    ArgVec* args;
    std::string return_type;
    Function(std::string name, std::string return_type, ArgVec& args);
    ~Function();
    void print() override;
};





class TablesList {
public:
    TablesList();
    OffsetStack offsets;
    TableVector tables;
    Symbol_Table sym_table;
    Symbol* GetSymbol(const std::string& name, bool is_func);
    void OpenScope();
    void OpenGlobal();
    void CloseScope();
    void CloseGlobal();
    void AddSymbol(const std::string& annotation, const std::string& name, const std::string& type);                                     //variable symbol
    void AddSymbol(std::string name, std::string return_type, ArgVec& args);       //function symbol
    void AddArgsSymbols(ArgVec& args);
    void IsNameExists(const std::string& name, bool is_func);
};

#endif //COMPI__HW3_SYMBOLTABLES_HPP
