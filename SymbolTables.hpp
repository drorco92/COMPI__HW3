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
    std::vector<string> arguments_types;
    string return_type;
public:
    Function(string name, string return_type, std::vector<string> arguments_types);
    void print(string) override;
    void print(int) override;
};



class Symbol_Table {
public:
    Symbol_Table* parent = nullptr;
    SymbolsVector symbols = SymbolsVector() ;
    Symbol_Table() = default;
    explicit Symbol_Table(Symbol_Table* parent) : this.parent(parent) {}
    ~Symbol_Table() = default;
};


class TablesList {
public:
    OffsetStack offsets;
    TableVector tables;
    Symbol_Table();
    Symbol* search_symbol(const string& name, bool is_func);
    Symbol* search_symbol_in_all_scopes(const string& name, bool is_func);
    void open_scope();
    void open_first_scope();
    void close_scope();
    void close_global_scope();
    void add_var_symbol(const string& name, const string& type);
    void add_func_symbol(const string& name, const string& return_type, StrPairVec& args);
    void add_func_args(StrPairVec& args);
    void check_name_not_exists_in_scope(const string& name, bool is_func);
};

#endif //COMPI__HW3_SYMBOLTABLES_HPP
