/*
Name: Nicholas Mirchandani
ID: 2317024
Email: nmirchandani@chapman.edu
Course: CPSC350-02
Assignment 5: Database

Record.cpp is the core implementation of a record, the parent class of both student and faculty.
*/

#include <iostream>
#include "Record.h"

/*
    Default Constructor: Empty but exists as good coding practice
*/
Record::Record() {
}

/*
    Overloaded Constructor: Properly initializes attributes
    id: Desired id of record
    name: Desired name of record
*/
Record::Record(int id, std::string name) {
    this->id = id;
    this->name = name;
}

/*
    Accessor for id
    Returns record id
*/
int Record::getID() const{
    return id;
}

/*
    Mutator for id
    id: Desired record id
*/
void Record::setID(int id) {
    this->id = id;
}

/*
    Accessor for name
    Returns name associated with the record
*/
std::string Record::getName() const{
    return name;
}

/*
    Mutator for name
    name: Desired name for the record
*/
void Record::setName(std::string name) {
    this->name = name;
}

/*
    Overloads < to compare record ids
*/
bool operator<(const Record& r1, const Record& r2) {
    return r1.id < r2.id;
}

/*
    Overloads > to compare record ids
*/
bool operator>(const Record& r1, const Record& r2) {
    return r1.id > r2.id;
}

/*
    Overloads == to compare record ids
*/
bool operator==(const Record& r1, const Record& r2) {
    return r1.id == r2.id;
}


/*
    Overloads != to compare record ids
*/
bool operator!=(const Record& r1, const Record& r2) {
    return r1.id != r2.id;
}
