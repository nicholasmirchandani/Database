# Database
Assignment 5 for Data Structures

Name: Nicholas Mirchandani <br/>

ID: 2317024 <br/>

Email: nmirchandani@chapman.edu <br/>

CPSC 350-02 <br/>

Assignment 5: Database
<br/>

Source Files: BST.cpp, BST.h, Database.cpp, Database.h, DoublyLinkedList.cpp, DoublyLinkedList.h, Faculty.cpp, Faculty.h, GenStack.cpp, GenStack.h, ListNode.cpp, ListNode.h, Record.cpp, Record.h, Student.cpp, Student.h, TreeNode.cpp, TreeNode.h, main.cpp<br/>

Limitations/Deviations: If invalid facultyTable/studentTable is supplied, program will crash.  Does not occur under normal use, as facultyTable/studentTable are auto-generated

Extra Work: Functions as a terminal to the database.  Rollbacks can rollback add/delete/change advisor, which means that any change can be rolled back.  Keeps track of who added each record between sessions by username and displays that when printing as well.

References: 
https://www.learncpp.com/cpp-tutorial/810-const-class-objects-and-member-functions/<br/>
https://www.learncpp.com/cpp-tutorial/92-overloading-the-arithmetic-operators-using-friend-functions/<br/>
https://www.tutorialspoint.com/substring-in-cplusplus<br/>
Code from interterm: faking screen clear with proper escape codes<br/>
http://www.cplusplus.com/reference/string/stod/<br/>
http://www.cplusplus.com/reference/string/stoi/<br/>

Instructions for running the assignment:
1) make
2) ./Database.out
