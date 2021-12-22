//
// Created by user on 19/12/2021.
//

#ifndef COMPI__HW3_STRUCTS_HPP
#define COMPI__HW3_STRUCTS_HPP


#include <iostream>
#include <string>
#include <vector>

struct Argument {
    std::string name;
    std::string type;
    std::string annotation;
    Argument(const std::string& annotation, const std::string& name, const std::string& type) : name(name), type(type) ,annotation(annotation){};
};

typedef std::vector<Argument> ArgVector;
typedef std::vector<Argument> TypeVector;
typedef std::vector<std::string> std::stringVector;

struct Exp {
    std::string name;
    std::string type;
    int val;
    std::string annotation;

    explicit Exp(const std::string& type) {
        this->type = /*string(type)*/type;
    }
    Exp(const Exp& exp, const std::string& type) {
        this->name = exp.name;
        this->type = /*string(type)*/type;
        this->val = exp.val;
    }
};

struct Id {
    std::string name;
    explicit Id(const std::string& name): name(name) {};
};



struct ArgumentList {
    ArgVector arguments;
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
