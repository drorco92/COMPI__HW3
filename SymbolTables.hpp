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
    string name;
    int offset;
    string type;

public:
    Symbol(string name, int offset, string type);
    virtual void print();
};



class Symbol_Table {
public:
    Symbol_Table* parent = nullptr;
    SymbolsVector symbols ;
    Symbol_Table() = default;
    explicit Symbol_Table(Symbol_Table* parent) : parent(parent) {}
    ~Symbol_Table() = default;
};


typedef std::vector<Argument> ArgVec;
typedef std::vector<Symbol> SymbolsVector;
typedef std::vector<Symbol_Table> TableVector;
typedef stack<int> OffsetStack;




class Variable : public Symbol {
    string type_annotation;
public:
    Variable(string name, int offset, string type, string type_annotation);
    void print() override;
};

class Function : public Symbol {
    ArgVec* args;
    string return_type;
public:
    Function(string name, string return_type, ArgVec& args);
    ~Function();
    void print() override;
};





class TablesList {
public:
    OffsetStack offsets;
    TableVector tables;
    Symbol_Table sym_table;
    Symbol* GetSymbol(const string& name, bool is_func);
    void OpenScope();
    void OpenGlobal();
    void CloseScope();
    void CloseGlobal();
    void AddSymbol(const string& name, const string& type);                                     //variable symbol
    void AddSymbol(string name, string return_type, ArgVec& args);       //function symbol
    void AddArgsSymbols(StringVector& args_names, ArgVec& args);
    void IsNameExists(const string& name, bool is_func);
};

#endif //COMPI__HW3_SYMBOLTABLES_HPP
