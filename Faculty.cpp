/*
Name: Nicholas Mirchandani
ID: 2317024
Email: nmirchandani@chapman.edu
Course: CPSC350-02
Assignment 5: Database

Faculty.cpp is the core implementation of a faculty record.
*/

#include "Faculty.h"

/*
    Default Constructor: Empty but exists as good coding practice
*/
Faculty::Faculty() {
    //Empty default constructor
}

/*
    Overloaded Constructor: Properly initializes attributes
    id: Desired faculty id
    name: Desired faculty name
    level: Desired faculty level
    department: Desired faculty department
*/
Faculty::Faculty(int id, std::string name, std::string level, std::string department, std::string addedBy) : Record(id, name, addedBy) {
    this->level = level;
    this->department = department;
}

/*
    Copy Constructor: Used to make deep copy of faculty
    f: faculty to base this copy off of
*/
Faculty::Faculty(const Faculty& f) : Record(f.getID(), f.getName(), f.getAddedBy()) {
    this->level = f.level;
    this->department = f.department;
    this->advisees = DoublyLinkedList<int>();
    ListNode<int>* curr = f.advisees.front;
    while(curr != nullptr) {
        advisees.insertBack(curr->data);
        curr = curr->next;
    }
}

/*
    Default Destructor: Empty but exists as good coding practice
*/
Faculty::~Faculty() {
    //Empty default destructor
}

/*
    Accessor for level
    Returns faculty level
*/
std::string Faculty::getLevel() const{
    return level;
}

/*
    Mutator for level
    level: Desired faculty level
*/
void Faculty::setLevel(std::string level) {
    this->level = level;
}

/*
    Accessor for department
    Returns faculty department
*/
std::string Faculty::getDepartment() const{
    return department;
}

/*
    Mutator for department
    department: Desired faculty department
*/
void Faculty::setDepartment(std::string department) {
    this->department = department;
}

/*
    Adds advisee to advisees
    studentID: ID of student to add
*/
void Faculty::addAdvisee(int studentID) {
    advisees.insertBack(studentID);
}

/*
    Removes advisee from advisees
    studentID: ID of student to remove
*/
void Faculty::removeAdvisee(int studentID) {
    advisees.remove(studentID);
}

/*
    Prints all advisees
*/
void Faculty::printAdvisees() const{
    advisees.printList();
}

/*
    Prints all advisees to file
*/
void Faculty::printAdvisees(std::ostream& os) const{
    advisees.printList(os);
}

/*
    Searches all advisees for advisee with respective id
    studentID: ID of student to be checked if is an advisee
    Returns true if student is advisee, false otherwise
*/
bool Faculty::searchAdvisees(int studentID) {
    ListNode<int>* curr = advisees.front;
    while(curr != nullptr) {
        if(curr->data == studentID) {
            return true;
        }
        curr = curr->next;
    }
    return false;
}

/*
    Operator overload for cout: allows faculty's information to be printed
*/
std::ostream& operator<<(std::ostream& os, const Faculty& f) { //Operator Overload for cout
    os << "Faculty ID: " << f.getID() << std::endl;
    os << "Name: " << f.getName() << std::endl;
    os << "Level: " << f.level << std::endl;
    os << "Department: " << f.department << std::endl;
    os << "Advisees: ";
    f.printAdvisees(os);
    os << "Added by: " << f.getAddedBy() << std::endl;
    return os;
}