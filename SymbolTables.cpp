//
// Created by user on 19/12/2021.
//

#include "SymbolTables.hpp"

Symbol::Symbol(string name, int offset, string type) : name(name), offset(offset), type(type) {};
void Symbol::print(string) {}
void Symbol::print(int) {}
//======================================================================================
Variable::Variable(string name, int offset, string type, string type_annotation) : Symbol(name, offset, type), type_annotation(type_annotation) {}
void Variable::print() {
    output::printID(name, offset, type);
}

//======================================================================================
Function::Function(string name, string return_type, ArgVec& args) : Symbol(name, 0, "FUNCTION"), return_type(return_type), args(args){}

Function::~Function() {
    delete this->args;
}

void Function::print() {
    output::printID(name, offset, output::makeFunctionType(this->return_type, this->arguments_types));
}

//======================================================================================

TablesList::TablesList() {
    this->offsets = stack<int>();
    this->tables = TableVec();
    this->OpenGlobal();

    StringVecto print_args_types;
    StringVecto print_args_names;
    print_args.push_back("INT");
    print_args.push_back("arguments");
    add_func_symbol("print", "VOID", print_args_names, print_args_types);
    AddSymbol("print", "VOID",)
    StringVecto printi_args_types;
    StringVecto printi_args_names;
    printi_args.push_back("INT");
    printi_args.push_back("arguments");
    AddSymbol("printi", "VOID", print_args_names, print_args_types);
}

void TablesList::OpenGlobal() {
    Symbol_Table first_table = new Symbol_Table(nullptr);
    this->tables.push_back(first_table);
    this->offsets.push(0)
}

void TablesList::OpenScope() {
    Symbol_Table new_table = new Symbol_Table(this->tables.back());
    this->tables.push_back(new_table);
    this->offsets.push(this->offsets.top());
}

void TablesList::CloseScope() {
    output::endScope();
    for (Symbol* symbol : this->tables.back()->symbols) {
        symbol->print();
    }
    delete this->tables.back();
    this->tables.pop_back();
    this->offsets.pop();
}

void TablesList::CloseGlobal() {
    Symbol* main_symbol = GetSymbol("main", true);
    (Function*) main_func_symbol = (Function*) main_symbol;
    if(main_symbol == nullptr || main_func_symbol->return_type != "VOID"
       || !main_func_symbol->arguments_types.empty()) {
        output::errorMainMissing();
        exit(1);
    }
    CloseScope();
}


Symbol* TablesList::GetSymbol(const string& name, bool is_func) {
    for (vector<Symbol_Table>::iterator table_it = this->tables.rbegin(); table_it != this->tables.rend(); table_it++) {
        for (vector<Symbol_Table>::iterator symbol_it = (*table_it)->symbols.rbegin(); symbol_it != (*table_it)->symbols.rend(); symbol_it++) {
            if(is_func) {
                if ((*symbol_it)->name == name && (*symbol_it)->type == "FUNC") {
                    return (*symbol_it);
                }
            }
            else {
                if ((*symbol_it)->name == name && (*symbol_it)->type != "FUNC") {
                    return (*symbol_it);
                }
            }
        }
    }
    return nullptr;
}


void TablesList::AddSymbol(const string& name, const string& type) {
    IsNameExists(name, false);
    Variable* variable_symbol = new Variable(name, type, this->offsets.top());
    this->tables.back()->symbols.push_back(variable_symbol);
    this->offsets.top() += 1;
}

void TablesList::AddSymbol(const string& name, const string& return_type, ArgVec& args) {
    IsNameExists(name, true);

    ArgVec* args_to_push = new ArgVec();

    for(ArgVec::iterator arg_it = args.rbegin(); arg_it != args.rend(); arg_it++) {
        IsNameExists((arg_it->name, false);
        args_to_push->push_back(*arg_it);
    }
    Function* function_symbol = new Function(name, return_type, args_to_push);
    this->tables.back()->symbols.push_back(function_symbol);
}

void TablesList::AddArgsSymbols(ArgVec& args) {
    int args_offset = -1;

    for(ArgVec::iterator arg_it = args.rbegin(); arg_it != args.rend(); arg_it++) {
        IsNameExists((arg_it->name, false);
        Variable* symbol = new VarSymbol((arg_it->name), (arg_it->type, args_offset));
        this->tables.back()->symbols.push_back(symbol);
        args_offset -= 1;
    }
}

void TablesList::IsNameExists(const string& name, bool is_func) {
    if(GetSymbol(name, is_func) != nullptr || GetSymbol(name, !is_func) != nullptr) {
        output::errorDef(yylineno ,name);
        exit(1);
    }
}