//
// Created by user on 19/12/2021.
//

#ifndef COMPI__HW3_STRUCTS_HPP
#define COMPI__HW3_STRUCTS_HPP


#include <iostream>
#include <string>
#include <vector>

typedef std::vector<Argument> ArgVector;
typedef std::vector<Argument> TypeVector;

struct Exp {
    string name;
    string type;
    int val;

    explicit Exp(const string& type) {
        this->type = /*string(type)*/type;
    }
    Exp(const Exp& exp, const string& type) {
        this->name = exp.name;
        this->type = /*string(type)*/type;
        this->val = exp.val;
    }
};

struct Id {
    string name;
    explicit Id(const string& name): this.name(name);
};

struct Argument {
    string name;
    string type;
    Argument(const string& name, const string& type) : this.name(name), this.type(type) {};
};

struct ArgumentList {
    ArgVector arg_vec;
    ArgumentList() = default;
};

struct TypeList {
    TypeVector type_vector;
    TypeList() = default;
};


typedef union Node
{
    Exp* exp;
    Id* id;
    FuncArg* funcArg;
    FuncArgsList* funcArgsList;
    TypeList* typeList;
    int val;
} STYPE;

#define YYSTYPE STYPE


#endif //COMPI__HW3_STRUCTS_HPP
