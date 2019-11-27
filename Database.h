#ifndef DATABASE_H
#define DATABASE_H
#include "BST.cpp"
#include "GenStack.cpp"
#include "Student.h"
#include "Faculty.h"
class Database {
    public:
    enum RollbackType {
        INSERT_STUDENT,
        DELETE_STUDENT,
        INSERT_FACULTY,
        DELETE_FACULTY,
        ADVISOR_CHANGE
    };

    struct RollbackInfo {
        RollbackType type;
        Student student;
        Faculty faculty;
        Faculty newAdvisor;
    };

    private:
        BST<Student>* masterStudent;
        BST<Faculty>* masterFaculty;
        GenStack<RollbackInfo> rollbackStack;
    public:
        Database();
        ~Database();
        void printStudents();
        void printFaculty();
        void printStudents(std::ofstream& os);
        void printFaculty(std::ofstream& os);
        void printStudent(int id);
        void printFaculty(int id);
        void printAdvisor(int id);
        void printAdvisees(int id);
        void addStudent(Student s, bool trackRollback);
        void deleteStudent(int id, bool trackRollback);
        void addFaculty(Faculty f, bool trackRollback);
        void deleteFaculty(int id, bool trackRollback);
        void changeAdvisor(int studentID, int facultyID, bool trackRollback);
        void removeAdvisee(int facultyID, int studentID, int newAdvisorID, bool trackRollback);
        void rollback();
};
#endif