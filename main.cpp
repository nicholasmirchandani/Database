#include "Database.h"
#include <iostream>
#include <fstream>
#include <limits> //For std::numeric_limits <std::streamsize>::max()

double getDoubleFromUser(std::string message);
int getIntFromUser(std::string message);
void printCommands();
void printInfo(std::string command);
void parseInput(std::string input, DoublyLinkedList<std::string>& arguments);

int main(int argc, char** argv) {
    std::cout << "\033[2J\033[1;1H"; //Faking a clear screen using ANSI escape codes
    std::string username = "";
    while(username == "") {
        std::cout << "Please enter a username: ";
        std::getline(std::cin, username);
    }
    std::cout << "Type 'help' for a list of commands" << std::endl;
    std::string input;
    std::string command;
    std::string argument;
    DoublyLinkedList<std::string> arguments;
    Database myDatabase;
    //Reading from file
    std::ifstream is("facultyTable");
    if(!is.fail()) {
        while(!is.eof()) {
            std::string id_string;
            getline(is, id_string);
            if(id_string == "") {   //End of file if ""
                break;
            }
            int id = stoi(id_string.substr(12)); //Discard first 12 chars
            std::string name;
            getline(is, name);
            name = name.substr(6); //Discard first 6 chars
            std::string level;
            getline(is, level);
            level = level.substr(7); //Discard first 7 chars
            std::string department;
            getline(is, department);
            department = department.substr(12); //Discard first 12 chars
            Faculty f(id, name, level, department);
            myDatabase.addFaculty(f, false);
            getline(is, id_string); //Getting rid of extra lines: advisors are accounted for when students are added
            getline(is, id_string); //Getting rid of extra lines
        }
    }
    is.close();
    std::ifstream is2("studentTable");
    if(!is2.fail()) {
        while(!is2.eof()) {
            std::string id_string;
            getline(is2, id_string);
            if(id_string == "") {   //End of file if ""
                break;
            }
            int id = stoi(id_string.substr(12)); //Discard first 12 chars
            std::string name;
            getline(is2, name);
            name = name.substr(6); //Discard first 6 chars
            std::string level;
            getline(is2, level);
            level = level.substr(7); //Discard first 7 chars
            std::string major;
            getline(is2, major);
            major = major.substr(7); //Discard first 7 chars
            std::string gpa_string;
            getline(is2, gpa_string);
            double gpa = stod(gpa_string.substr(5)); //Discard first 5 chars
            std::string advisor_string;
            getline(is2, advisor_string);
            int advisor = stoi(advisor_string.substr(9)); //Disard first 9 chars

            Student s(id, name, level, major, gpa, advisor);
            myDatabase.addStudent(s, false);
            getline(is2, id_string); //Getting rid of extra line
        }
    }
    is2.close();
    while(true) {
        std::cout << "$" << username << ": ";
        std::getline(std::cin, input);
        parseInput(input, arguments);
        if(arguments.front != nullptr) {        //If arguments is empty, treat command as empty, otherwise command is first argument
            command = arguments.front->data;
        } else {
            command = "";
        }
        if(command == "addFaculty") {
            int id = getIntFromUser("Faculty id: ");
            std::string name = "";
            while(name == "") {
                std::cout << "Faculty name: ";
                std::getline(std::cin, name);
            }
            std::string level = "";
            while(level == "") {
                std::cout << "Faculty level: ";
                std::getline(std::cin, level);
            }
            std::string department = "";
            while(department == "") {
                std::cout << "Faculty department: ";
                std::getline(std::cin, department);
            }
            Faculty f(id, name, level, department);
            myDatabase.addFaculty(f, true);
        } else if(command == "addStudent") {
            int id = getIntFromUser("Student id: ");
            std::string name = "";
            while(name == "") {
                std::cout << "Student name: ";
                std::getline(std::cin, name);
            }
            std::string level = "";
            while(level == "") {
                std::cout << "Student level: ";
                std::getline(std::cin, level);
            }
            std::string major = "";
            while(major == "") {
                std::cout << "Student major: ";
                std::getline(std::cin, major);
            }
            double gpa = getDoubleFromUser("Student gpa: ");
            int advisor = getIntFromUser("Student advisor faculty id: ");
            Student s(id, name, level, major, gpa, advisor);
            myDatabase.addStudent(s, true);
        } else if(command == "changeAdvisor") {
            if(arguments.front->next == nullptr || arguments.front->next->next == nullptr) {  //if arguments[1] or arguments[2] does not exist
                std::cout << "changeAdvisor requires 2 arguments: [Student id] and [Faculty id]" << std::endl;
            } else {
                try {
                    int studentID = stoi(arguments.front->next->data);
                    int facultyID = stoi(arguments.front->next->next->data);
                    myDatabase.changeAdvisor(studentID, facultyID, true);
                } catch(const std::invalid_argument& ia) {
                    std::cout << "Invalid argument(s)." << std::endl;
                }
            }
        } else if(command == "deleteFaculty") {
            if(arguments.front->next == nullptr) {
                std::cout << "deleteFaculty requires 1 argument: [Faculty id]" << std::endl;
            } else {
                try {
                    int facultyID = stoi(arguments.front->next->data);
                    myDatabase.deleteFaculty(facultyID, true);
                } catch(const std::invalid_argument& ia) {
                    std::cout << "Invalid argument." << std::endl;
                }
            }
        } else if(command == "deleteStudent") {
            if(arguments.front->next == nullptr) {
                std::cout << "deleteStudent requires 1 argument: [Student id]" << std::endl;
            } else {
                try {
                    int studentID = stoi(arguments.front->next->data);
                    myDatabase.deleteStudent(studentID, true);
                } catch(const std::invalid_argument& ia) {
                    std::cout << "Invalid argument." << std::endl;
                }
            }
        } else if(command == "exit") {
            break;
        } else if(command == "help") {
            if(arguments.front->next == nullptr) {  //if arguments[1] does not exist
                printCommands();
            } else {
                printInfo(arguments.front->next->data); //arguments.front->next->data = arguments[1]
            }
        } else if(command == "printAdvisees") {
            if(arguments.front->next == nullptr) {
                std::cout << "printAdvisees requires 1 argument: [Faculty id]" << std::endl;
            } else {
                try {
                    int facultyID = stoi(arguments.front->next->data); //arguments.front->next->data = arguments[1]
                    myDatabase.printAdvisees(facultyID);
                } catch(const std::invalid_argument& ia) {
                    std::cout << "Invalid argument." << std::endl;
                }
            }
        } else if(command == "printAdvisor") {
            if(arguments.front->next == nullptr) {
                std::cout << "printAdvisor requires 1 argument: [Student id]" << std::endl;
            } else {
                try {
                    int studentID = stoi(arguments.front->next->data); //arguments.front->next->data = arguments[1]
                    myDatabase.printAdvisor(studentID);
                } catch(const std::invalid_argument& ia) {
                    std::cout << "Invalid argument." << std::endl;
                }
            }
        } else if(command == "printFaculty") {
            if(arguments.front->next == nullptr) {  //if arguments[1] does not exist
                myDatabase.printFaculty();
            } else {
                try {
                    int facultyID = stoi(arguments.front->next->data); //arguments.front->next->data = arguments[1]
                    myDatabase.printFaculty(facultyID);
                } catch(const std::invalid_argument& ia) {
                    std::cout << "Invalid argument." << std::endl;
                }
            }        
        } else if(command == "printStudent") {
            if(arguments.front->next == nullptr) {
                std::cout << "printStudent requires 1 argument: [Student id]" << std::endl;
            } else {
                try {
                    int studentID = stoi(arguments.front->next->data); //arguments.front->next->data = arguments[1]
                    myDatabase.printStudent(studentID);
                } catch(const std::invalid_argument& ia) {
                    std::cout << "Invalid argument." << std::endl;
                }
            }
        } else if(command == "printStudents") {
            myDatabase.printStudents();
        } else if(command == "removeAdvisee") {
            if(arguments.front->next == nullptr || arguments.front->next->next == nullptr || arguments.front->next->next->next == nullptr) {  //if arguments[1] or arguments[2] or arguments[3] does not exist
                std::cout << "removeAdvisee requires 3 arguments: [Faculty id] [Student id] and [New advisor id]" << std::endl;
            } else {
                try {
                    int facultyID = stoi(arguments.front->next->data);
                    int studentID = stoi(arguments.front->next->next->data);
                    int newAdvisorID = stoi(arguments.front->next->next->next->data);
                    myDatabase.removeAdvisee(facultyID, studentID, newAdvisorID, true);
                } catch(const std::invalid_argument& ia) {
                    std::cout << "Invalid argument(s)." << std::endl;
                }
            }
        } else if (command == "rollback") {
            myDatabase.rollback();
        } else if(command == "") {
            //Intentionally doing nothing on an empty command
            continue;
        } else {
            std::cout << "'" << command << "' is not recognized as a valid command.  Type 'help' for a list of commands." << std::endl;
        }
        std::cout << "\n"; //Formatting!!!
    }
    std::cout << "Closing." << std::endl;
    std::ofstream os;
    os.open("facultyTable", std::ofstream::out | std::ofstream::trunc);
    myDatabase.printFaculty(os);
    os.close();

    os.open("studentTable", std::ofstream::out | std::ofstream::trunc);
    myDatabase.printStudents(os);
    os.close();
}

/*
    Handles double input from users; if non-double value is typed in, it'll take another input
    message: Message to reprompt with for another input
    Returns double value user typed in
*/
double getDoubleFromUser(std::string message)
{
    std::string input; //Declaring input inside the while loop would cause an error
    double result;
    while(true) //Going to keep looping this until they enter valid input
    {
        std::cout << message;
        std::getline(std::cin, input);
        try {
            result = stod(input);
            break;
        } catch(const std::invalid_argument& ia) {
            //Silently catches invalid argument and loop continues
        }
    }
    return result;
}

/*
    Handles int input from users; if non-int value is typed in, it'll take another input
    message: Message to reprompt with for another input
    Returns int value user typed in
*/
int getIntFromUser(std::string message)
{
    std::string input; //Declaring input inside the while loop would cause an error
    int result;
    while(true) //Going to keep looping this until they enter valid input
    {
        std::cout << message;
        std::getline(std::cin, input);
        try {
            result = stoi(input);
            break;
        } catch(const std::invalid_argument& ia) {
            //Silently catches invalid argument and loop continues
        }
    }
    return result;
}

/*
    Procedure to print all available commands
*/
void printCommands() {
    std::cout << "For more information on a specific command, type 'help [command]':" << std::endl;
    std::cout << "addFaculty" << std::endl;
    std::cout << "addStudent" << std::endl;
    std::cout << "changeAdvisor [Student id] [Faculty id]" << std::endl;
    std::cout << "deleteFaculty [Faculty id]" << std::endl;
    std::cout << "deleteStudent [Student id]" << std::endl;
    std::cout << "exit" << std::endl;
    std::cout << "help" << std::endl;
    std::cout << "help [command]" << std::endl;
    std::cout << "printAdvisees [Faculty id]" << std::endl;
    std::cout << "printAdvisor [Student id]" << std::endl;
    std::cout << "printFaculty" << std::endl;
    std::cout << "printFaculty [Faculty id]" << std::endl;
    std::cout << "printStudent [Student id]" << std::endl;
    std::cout << "printStudents" << std::endl;
    std::cout << "removeAdvisee [Faculty id] [Student id] [New advisor id]" << std::endl;
    std::cout << "rollback" << std::endl;
}

/*
    Prints detailed info about a specified command
    command: command to give additional detail about.
*/
void printInfo(std::string command) {
    std::cout << command << ": " << std::endl;
    if(command == "addFaculty") {
        std::cout << "addFaculty allows you to add a faculty member to the database.  It has no required arguments," <<\
        "as you will be prompted for all the required information." << std::endl;
    } else if(command == "addStudent") {
        std::cout << "addStudent allows you to add a student to the database.  It has no required arguments, " <<\
        "as you will be prompted for all the required information.  A student cannot be added with an advisor that" <<\
        "does not already exist in the database, meaning that a student cannot be added without a faculty." << std::endl;
    } else if(command == "changeAdvisor") {
        std::cout << "changeAdvisor allows you to change a student's advisor.  Usage: changeAdvisor [Student id] [Faculty id]." <<\
        "Changes the student with id [Student id]'s advisor to the faculty member with id [Faculty id].  Both the student and" <<\
        "faculty must exist in the database for this command to work.  Additionally, removes student from advisees of old advisor," <<\
        "as would be most logical when executing a command of this sort." << std::endl;
    } else if(command == "deleteFaculty") {
        std::cout << "deleteFaculty allows you to delete a faculty from the database.  Usage: deleteFaculty [Faculty id]." <<\
        "Deletes the faculty with id [Faculty id].  Does not allow you to remove faculty with any advisees." << std::endl;
    } else if(command == "deleteStudent") {
        std::cout << "deleteStudent allows you to delete a student from the database.  Usage: deleteStudent [Student id]." <<\
        "Deletes the student with id [Student id].  Removes student as advisee from its advisor when deleting student." << std::endl;
    } else if(command == "exit") {
        std::cout << "exit exits the program.  Saves faculty and students to respective txt files to be used on next login." << std::endl;
    } else if(command == "help") {
        std::cout << "help can be used with or without arguments.  Without arguments, it simply provides a list of commands.  With" <<\
        "a single argument, it can be used as such: help [command].  Displays detailed info on that command" << std::endl;
    } else if(command == "printAdvisees") {
        std::cout << "printAdvisees prints the advisees of a given faculty member.  Usage: printAdvisees [Faculty id]." <<\
        "Prints all the advisees of [Faculty id]." << std::endl;
    } else if(command == "printAdvisor") {
        std::cout << "printAdvisor prints information of a specific advisor given id.  Usage: printAdvisor [Student id]." <<\
        "Prints the information of the student with id [Student id]'s advisor." << std::endl;
    } else if(command == "printFaculty") {
        std::cout << "printFaculty can be used with or without arguments.  Without arguments, it simply prints all faculty in the" <<\
        "database, sorted by ascending id #.  With a single argument, it can be used as such: printFaculty [Faculty id].  Displays" <<\
        "information of the faculty member in the database with that id, if they exist in the databse." << std::endl;
    } else if(command == "printStudent") {
        std::cout << "printStudent prints information of a specific student given id.  Usage: printStudent [Student id]." <<\
        "Prints the information of the student with id [Student id]." << std::endl;
    } else if(command == "printStudents") {
        std::cout << "printStudents prints all students' information in the database, sorted by ascending id #." << std::endl;
    } else if(command == "removeAdvisee") {
        std::cout << "removeAdvisee removes an advisee from an advisor.  Usage: removeAdvisee [Faculty id] [Student id]" <<\
        " [New advisor id].  Removes student with id [Student id] as an advisee from faculty with id [Faculty id] and replaces" <<\
        " their advisor with [New advisor id] and adds them as an advisee to faculty with id [New advisor id].  Requires new advisor" <<\
        " id to be specified when using command to preserve referential integrity.  The student and both faculty members must exist in" <<\
        " the database." << std::endl;
    } else if(command == "rollback") {
        std::cout << "rollback rolls back events that directly modified the database and echoes back to the user what was rolled back." <<\
        "Can roll back insertions, deletions, and advisor changes.  Will not rollback past initial state upon login." << std::endl;
    } else {
        std::cout << "Command " << command << " not found." << std::endl;
    }
}

/*
    Parses user input and breaks it into arguments
    input: string input to parse
    arguments: output parameter with each argument stored as an element in the doubly linked list
*/
void parseInput(std::string input, DoublyLinkedList<std::string>& arguments) {
    while(!arguments.isEmpty()) {   //Empties arguments before parsing input with it
        arguments.removeFront();
    }
    bool wasSpace = false;      //Keeping track of whether or not the last character was a space to ensure spacing doesn't matter
    std::string argument = "";
    for(char c : input) {
        if(c == ' ') {
            if(!wasSpace) {
                arguments.insertBack(argument);
                argument = "";                
            }
            wasSpace = true;
        } else {
            wasSpace = false;
            argument += c;
        }
    }
    if(argument != "") { //If the input didn't end in a space, still save it to arguments
        arguments.insertBack(argument);
        argument = "";
    }
}