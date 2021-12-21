//
// Created by user on 19/12/2021.
//

#ifndef COMPI__HW3_SYMBOLTABLES_HPP
#define COMPI__HW3_SYMBOLTABLES_HPP


#include <vector>
#include <string>
#include <stack>
#include "hw3_output.hpp"

typedef std::vector<Symbol> SymbolsVector;
typedef std::vector<Symbol_Table> TableVector;
typedef stack<int> OffsetStack;


class Symbol() {
    string name;
    int offset;
    string type;

public:
    Symbol(string name, int offset, string type);
    virtual void print(string);
    virtual void printi(int);
}

class Variable : public Symbol {
    string type_annotation;
public:
    Variable(string name, int offset, string type, string type_annotation);
    void print(string) override;
    void print(int) override;
};

class Function : public Symbol {
    std::vector<string> argument_types;
    string return_type;
public:
    Function(string name, string return_type, std::vector<string> arguments_types);
    void print(string) override;
    void print(int) override;
};



class Symbol_Table {
public:
    Symbol_Table* parent = nullptr;
    SymbolsVector symbols ;
    Symbol_Table() = default;
    explicit Symbol_Table(Symbol_Table* parent) : this.parent(parent) {}
    ~Symbol_Table() = default;
};


class TablesList {
public:
    OffsetStack offsets;
    TableVector tables;
    Symbol_Table();
    Symbol* GetSymbol(const string& name, bool is_func);
    void OpenScope();
    void OpenGlobal();
    void CloseScope();
    void CloseGlobal();
    void AddSymbol(const string& name, const string& type);                                     //variable symbol
    void AddSymbol(string name, string return_type, std::vector<string> arguments_types);       //function symbol
    void AddArgsSymbols(std::vector<string> arguments_types);
    void IsNameExists(const string& name, bool is_func);
};

#endif //COMPI__HW3_SYMBOLTABLES_HPP
