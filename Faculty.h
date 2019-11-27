#ifndef FACULTY_H
#define FACULTY_H
#include "DoublyLinkedList.cpp"
#include "Record.h"
class Faculty : public Record {
    private:
        std::string level;
        std::string department;
    public:
        Faculty();
        Faculty(int id, std::string name, std::string level, std::string department, std::string addedBy);
        Faculty(const Faculty& f);
        ~Faculty();
        std::string getLevel() const;
        void setLevel(std::string level);
        std::string getDepartment() const;
        void setDepartment(std::string department);
        void printAdvisees() const;
        void printAdvisees(std::ostream& os) const;
        void removeAdvisee(int studentID);
        void addAdvisee(int studentID);
        bool searchAdvisees(int studentID);
        friend std::ostream& operator<<(std::ostream& os, const Faculty& f);
        DoublyLinkedList<int> advisees;
};
#endif