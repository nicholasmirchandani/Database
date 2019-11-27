#ifndef STUDENT_H
#define STUDENT_H
#include "Record.h"
#include <iostream>
class Student : public Record {
    private:
        std::string level;
        std::string major;
        double gpa;
        int advisor;
    public:
        Student();
        Student(int id, std::string name, std::string level, std::string major, double gpa, int advisor, std::string addedBy);
        Student(const Student& s);
        std::string getLevel() const;
        void setLevel(std::string level);
        std::string getMajor() const;
        void setMajor(std::string major);
        double getGPA() const;
        void setGPA(double gpa);
        int getAdvisor() const;
        void setAdvisor(int advisor);
        friend std::ostream& operator<<(std::ostream& os, const Student& s);
};
#endif