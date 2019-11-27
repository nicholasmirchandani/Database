/*
Name: Nicholas Mirchandani
ID: 2317024
Email: nmirchandani@chapman.edu
Course: CPSC350-02
Assignment 5: Database

Student.cpp is the core implementation of a student record.
*/

#include "Student.h"


/*
    Default Constructor: Empty but exists as good coding practice
*/
Student::Student() {
    //Empty default constructor
}

/*
    Overloaded Constructor: Properly initializes attributes
    id: Desired id of student
    name: Desired name of student
    level: Desired level of student
    major: Desired major of student
    gpa: Desired gpa of student
    advisor: Desired advisor's id of student
*/
Student::Student(int id, std::string name, std::string level, std::string major, double gpa, int advisor) : Record(id, name){ //Initializer list for calling superclass
    this->level = level;
    this->major = major;
    this->gpa = gpa;
    this->advisor = advisor;
}


/*
    Copy Constructor: Make a deep copy of a student
    s: student to base this copy off of
*/
Student::Student(const Student& s) : Record(s.getID(), s.getName()){
    this->level = s.level;
    this->major = s.major;
    this->gpa = s.gpa;
    this->advisor = s.advisor;
}


/*
    Accessor for level
    Returns student level
*/
std::string Student::getLevel() const{
    return level;
}

/*
    Mutator for level
    level: Desired student level
*/
void Student::setLevel(std::string level) {
    this->level = level;
}

/*
    Accessor for major
    Returns student major
*/
std::string Student::getMajor() const{
    return major;
}

/*
    Mutator for major
    major: Desired student major
*/  
void Student::setMajor(std::string major) {
    this->major = major;
}

/*
    Accessor for GPA
    Returns student GPA
*/
double Student::getGPA() const{
    return gpa;
}

/*
    Mutator for GPA
    gpa: Desired student gpa
*/
void Student::setGPA(double gpa) {
    this->gpa = gpa;
}

/*
    Accessor for advisor
    Returns id of student's advisor
*/
int Student::getAdvisor() const{
    return advisor;
}

/*
    Mutator for advisor
    advisor: Desired advisor id
*/
void Student::setAdvisor(int advisor) {
    this->advisor = advisor;
}

/*
    Operator overload for cout: allows student's information to be printed
*/
std::ostream& operator<<(std::ostream& os, const Student& s) { //Operator Overload for cout
    os << "Student ID: " << s.getID() << std::endl;
    os << "Name: " << s.getName() << std::endl;
    os << "Level: " << s.level << std::endl;
    os << "Major: " << s.major << std::endl;
    os << "GPA: " << s.gpa << std::endl;
    os << "Advisor: " << s.advisor << std::endl;
    return os;
}