#include "Database.h"
//TODO: Rollback

/*
    Kinds of rollback:
    Inserting student/faculty
    Deleting student/faculty
    Changing advisor
*/

/*
    Empty default constructor
*/
Database::Database() {
    masterFaculty = new BST<Faculty>();
    masterStudent = new BST<Student>();
}

/*
    Destructor: Empty default destructor; masterStudent and masterFaculty are destructed as desired in BST's destructor
*/
Database::~Database() {
    delete(masterFaculty);
    delete(masterStudent);
}

/*
    Prints all students
*/
void Database::printStudents() {
    masterStudent->printTree();
}

/*
    Prints all faculty
*/
void Database::printFaculty() {
    masterFaculty->printTree();
}

/*
    Prints all students to file
*/
void Database::printStudents(std::ofstream& os) {
    masterStudent->printTree(os);
}

/*
    Prints all faculty to file
*/
void Database::printFaculty(std::ofstream& os) {
    masterFaculty->printTree(os);
}

/*
    Prints student given id
*/
void Database::printStudent(int id) {
    Student temp;   //Uses temp because BST is only checking ids when searching but requires student object
    temp.setID(id);
    TreeNode<Student>* studentNode = masterStudent->search(temp);
    if(studentNode != nullptr) {
        std::cout << studentNode->key << std::endl;
    } else {
        std::cerr << "Student with id " << id << " does not exist in the database." << std::endl;
    }
}

/*
    Prints faculty given id
*/
void Database::printFaculty(int id) {
    Faculty temp; //Uses temp because BST is only checking ids when searching but requires faculty object
    temp.setID(id);
    TreeNode<Faculty>* facultyNode = masterFaculty->search(temp);
    if(facultyNode != nullptr) {
        std::cout << facultyNode->key << std::endl;
    } else {
        std::cerr << "Faculty with id " << id << " does not exist in the database." << std::endl;
    }
}

/*
    Prints advisor given student id
*/
void Database::printAdvisor(int id) {
    Student temp; //Uses temp because BST is only checking ids when searching but requires student object
    temp.setID(id);
    TreeNode<Student>* studentNode = masterStudent->search(temp);
    if(studentNode != nullptr) {
        int advisorID = studentNode->key.getAdvisor();
        Faculty advisor;
        advisor.setID(advisorID);
        std::cout << masterFaculty->search(advisor)->key << std::endl;
    } else {
        std::cerr << "Student with id " << id << " does not exist in the database." << std::endl;
    }
}

/*
    Prints advisees given faculty id
*/
void Database::printAdvisees(int id) {
    Faculty temp; //Uses temp because BST is only checking ids when searching but requires faculty object
    temp.setID(id);
    TreeNode<Faculty>* facultyNode = masterFaculty->search(temp);
    if(facultyNode != nullptr) {
        ListNode<int>* adviseeNode = facultyNode->key.advisees.front;
        while(adviseeNode != nullptr) {
            Student temp2;
            temp2.setID(adviseeNode->data);
            std::cout << masterStudent->search(temp2)->key << std::endl;
            adviseeNode = adviseeNode->next;
        }
    } else {
        std::cerr << "Faculty with id " << id << " does not exist in the database." << std::endl;
    }
}

/*
    Adds new student to masterStudent
    Fails if no faculty present
    Returns false if failed, true otherwise
*/
void Database::addStudent(Student s, bool trackRollback) {
    if(masterFaculty->isEmpty()) {
        std::cerr << "Cannot add student: no faculty present" << std::endl;
    } else {
        Faculty temp; //Uses temp because BST is only checking ids when searching but requires faculty object
        temp.setID(s.getAdvisor());
        TreeNode<Faculty>* facultyNode = masterFaculty->search(temp);
        if(facultyNode == nullptr) {
            std::cerr << "Cannot add student: advisor doesn't exist" << std::endl;
            return;
        }
        if(masterStudent->search(s) == nullptr) {
            facultyNode->key.addAdvisee(s.getID());
            masterStudent->insert(s);
            if(trackRollback) {
                RollbackInfo rb;
                rb.type = Database::INSERT_STUDENT;
                rb.student = s;
                rollbackStack.push(rb);
            }
        } else {
            std::cerr << "Cannot add Student to database because student with id " << s.getID() << " already exists" << std::endl;
        }

    }
}

/*
    Deletes student given id
*/
void Database::deleteStudent(int id, bool trackRollback) {
    Student temp; //Uses temp because BST is only checking ids when deleting but requires student object
    temp.setID(id);
    TreeNode<Student>* studentNode = masterStudent->search(temp);
    Student backup(studentNode->key);
    if(studentNode != nullptr) {
        Faculty temp2;
        temp2.setID(studentNode->key.getAdvisor());
        masterStudent->deleteNode(temp);
        masterFaculty->search(temp2)->key.removeAdvisee(id);
        if(trackRollback) {
            RollbackInfo rb;
            rb.type = Database::DELETE_STUDENT;
            rb.student = backup;
            rollbackStack.push(rb);
        }
    } else {
        std::cerr << "Cannot remove Student with id " << id << " because no student with that id exists in the database" << std::endl;
    }

}

/*
    Adds new faculty to masterFaculty
*/
void Database::addFaculty(Faculty f, bool trackRollback) {
    if(masterFaculty->search(f) == nullptr) {
        masterFaculty->insert(f);
        if(trackRollback) {
            RollbackInfo rb;
            rb.type = Database::INSERT_FACULTY;
            rb.faculty = f;
            rollbackStack.push(rb);
        }
    } else {
        std::cerr << "Cannot add faculty to database because faculty with id " << f.getID() << " already exists" << std::endl;
    }
}

/*
    Deletes faculty given id
    Fails if is last faculty and students exist
    Returns false if fails, true otherwise
*/
void Database::deleteFaculty(int id, bool trackRollback) {
    Faculty temp;
    temp.setID(id);
    Faculty backup(masterFaculty->search(temp)->key);
    if((masterFaculty->numItems == 1) && !masterStudent->isEmpty()) {
        std::cerr << "Cannot remove last faculty member if students present" << std::endl;
    } else if(backup.advisees.getSize() > 0) {
        std::cerr << "Cannot remove faculty member with advisees" << std::endl;
    } else {
        masterFaculty->deleteNode(temp);
        if(trackRollback) {
            RollbackInfo rb;
            rb.type = Database::DELETE_FACULTY;
            rb.faculty = backup;
            rollbackStack.push(rb);
        }   
    }
}

/*
    Changes student advisor to given faculty id
    Fails if facultyID is not a faculty in masterFaculty or if studentID is not a student in masterStudent
    Returns false if fails, true otherwise
*/
void Database::changeAdvisor(int studentID, int facultyID, bool trackRollback) {
    Student temp; //Uses temp because BST is only checking ids when searching but requires student object
    temp.setID(studentID);
    TreeNode<Student>* studentNode = masterStudent->search(temp);
    if(studentNode != nullptr) {
        Faculty temp2; //Uses temp2 because BST is only checking ids when searching but requires faculty object
        temp2.setID(facultyID);
        TreeNode<Faculty>* facultyNode = masterFaculty->search(temp2);
        if(facultyNode != nullptr) { 
            temp2.setID(studentNode->key.getAdvisor()); //Reusing temp2 because it's no longer needed and need to remove student from advisees of original advisor
            Faculty oldAdvisor = masterFaculty->search(temp2)->key;
            masterFaculty->search(temp2)->key.removeAdvisee(studentID);
            studentNode->key.setAdvisor(facultyID);
            facultyNode->key.addAdvisee(studentID);
            if(trackRollback) {
                RollbackInfo rb;
                rb.type = Database::ADVISOR_CHANGE;
                Student studentBackup;
                studentBackup.setID(studentID);
                rb.student = studentBackup;
                Faculty facultyBackup;
                facultyBackup.setID(oldAdvisor.getID());
                rb.faculty = facultyBackup;
                Faculty advisorBackup;
                advisorBackup.setID(facultyID);
                rb.newAdvisor = advisorBackup;
                rollbackStack.push(rb);
            }
        } else {
            std::cerr << "Cannot change advisor of student to faculty that does not exist" << std::endl;
        }
    } else {
        std::cerr << "Cannot change advisor of student that does not exist" << std::endl;
    }
}

/*
    Removes advisee from faculty and gives it new advisor
    Fails if newAdvisorID or facultyID is not a faculty in masterFaculty, or if studentID isn't in masterStudent
    Returns false if fails, true otherwise
*/
void Database::removeAdvisee(int facultyID, int studentID, int newAdvisorID, bool trackRollback) {
    Faculty temp;
    temp.setID(facultyID);
    TreeNode<Faculty>* facultyNode = masterFaculty->search(temp);
    if(facultyNode != nullptr) {
        if(facultyNode->key.searchAdvisees(studentID)) {
            temp.setID(newAdvisorID); //Reusing temp since it's no longer needed but we need another temp
            TreeNode<Faculty>* newAdvisorNode = masterFaculty->search(temp);
            if(newAdvisorNode != nullptr) {
                facultyNode->key.removeAdvisee(studentID);
                newAdvisorNode->key.addAdvisee(studentID);
                Student temp2;
                temp2.setID(studentID);
                masterStudent->search(temp2)->key.setAdvisor(newAdvisorID);
                if(trackRollback) {
                    RollbackInfo rb;
                    rb.type = Database::ADVISOR_CHANGE;
                    Student rollbackStudent;
                    rollbackStudent.setID(studentID);
                    rb.student = rollbackStudent;
                    rb.faculty = facultyNode->key;
                    rb.newAdvisor = newAdvisorNode->key;
                    rollbackStack.push(rb);
                }
            } else {
                std::cerr << "You can't change a student's advisee to an advisee that doesn't exist when removing them from an advisor" << std::endl;
            }
        } else {
            std::cerr << "You can't remove an advisee from a faculty that isn't their advisee" << std::endl;
        }
    } else {
        std::cerr << "You can't remove an advisee from a nonexistent faculty" << std::endl;
    }
}

/*
    Rolls back BSTS based on previous states stored in rollbackStack
*/
void Database::rollback() {
    if(rollbackStack.isEmpty()) {
        std::cout << "Nothing to rollback." << std::endl;
        return;
    }
    RollbackInfo ri = rollbackStack.pop();
    switch(ri.type) {
        case Database::INSERT_STUDENT:
            deleteStudent(ri.student.getID(), false);
            std::cout << "Rolled back add student " << ri.student.getID() << std::endl;
            break;
        case Database::DELETE_STUDENT:
            addStudent(ri.student, false);
            std::cout << "Rolled back delete student " << ri.student.getID() << std::endl;
            break;
        case Database::INSERT_FACULTY:
            deleteFaculty(ri.faculty.getID(), false);
            std::cout << "Rolled back add faculty " << ri.faculty.getID() << std::endl;
            break;
        case Database::DELETE_FACULTY:
            addFaculty(ri.faculty, false);
            std::cout << "Rolled back delete faculty " << ri.faculty.getID() << std::endl;
            break;
        case Database::ADVISOR_CHANGE:
            removeAdvisee(ri.newAdvisor.getID(), ri.student.getID(), ri.faculty.getID(), false);
            std::cout << "Rolled back changing student " << ri.student.getID() << "'s advisor from " << ri.faculty.getID() << " to " << ri.newAdvisor.getID();
            break;
        default:
            std::cout << "CASE: " << ri.type << "Unaccounted for" << std::endl;
    }
}