//
// Created by user on 19/12/2021.
//

#include "SymbolTables.hpp"

Symbol::Symbol(string name, int offset, string type) : this.name(name), this.offset(offset), this.type(type) {};
void Symbol::print(string) {}
void Symbol::print(int) {}
//======================================================================================
Variable::Variable(string name, int offset, string type, string type_annotation) : Symbol(name, offset, type), this.type_annotation(type_annotation) {}
void Variable::print(string) {
    output::printID(name, offset, type);
}
void Variable::printi(int) { //TODO wtf?
    output::printID(name, offset, type);
}
//======================================================================================
Function::Function(string name, string return_type, std::vector<string>& arguments_types) : Symbol(name, 0, "FUNCTION"), this.return_type(return_type), this.arguments_types(arguments_types){}

void Function::print(string) {
    output::printID(name, offset, output::makeFunctionType(this->return_type, this->arguments_types));
}
void Function::printi(int) {
    output::printID(name, offset, output::makeFunctionType(this->return_type, this->arguments_types));
}
//======================================================================================

Symbol_Table::Symbol_Table(Symbol_Table* parent) {
    this->parent = parent;
}


SymbolTables::Function()