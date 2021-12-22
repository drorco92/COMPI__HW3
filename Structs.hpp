//
// Created by user on 19/12/2021.
//

#ifndef COMPI__HW3_STRUCTS_HPP
#define COMPI__HW3_STRUCTS_HPP


#include <iostream>
#include <string>
#include <vector>

struct Argument {
    string annotation;
    string name;
    string type;
    Argument(const string& annotation, const string& name, const string& type) : annotation(annotation), name(name), type(type) {};
};

typedef std::vector<Argument> ArgVector;
typedef std::vector<Argument> TypeVector;
typedef std::vector<string> StringVector;

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
    explicit Id(const string& name): name(name);
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
    Argument* argument;
    ArgumentList* argument_list;
    TypeList* type_list;
    int val;
} STYPE;

#define YYSTYPE STYPE


#endif //COMPI__HW3_STRUCTS_HPP
