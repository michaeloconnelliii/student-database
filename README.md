# Student Database

## Project Overview
* The goal of the project is to implement a student database using a binary search tree (BST). The BST is ordered with respect to a student's ID number, which is a key set by the amount of students in a school after each addition. For example, if student1 is added first their ID is 1, if student2 is added second their ID is 2 and so on. The program will insert an assortment of student data and test the database's correctness.

* The program will allow a user to enter a student roster file (a .txt input file) containing a student's first name, last name, and age. Each student's information will be converted to a Node which will be inserted into the student database (the BST).

* The BST supports the following standard methods: insertion, deletion, search, inorder traversal, minimum, and maximum.

* The project uses the following Object-Oriented Programming (OOP) concepts: Classes, Inheritance, and Composition. 

* My contribution was adding the implementing the bst and SNode classes, as well as their associated methods.

## What's in this repository
* Binary Search Trees (BST).pdf
  * Original specifications for the project.
* Makefile
  * Makefile recipe. Creates an executable named 'bst'.
* bst.h, bst.cc
  * BST and Node class implementation.
* db.h, db.cc
  * SNode (student node) class implementation.
* main.cc
  * Main program. Ensures user input is correct, reads and adds student data to student database from input file, and tests the correctness of the student database and the BST class.
* out.txt, out1.txt
  * sample output which contains database information.
* students_1.txt, students_1_ans.txt
  * sample input and output file.

## Implementation details
SNode inherits from Node and num_students in SNode is key in Node.

## How to use
* To compile: $make 
* To run
  * Using a student roster file: $ ./bst -i students_1.txt -o out.txt
  * To run a BST unit test with 100 elements: $ ./bst -n 100
* More information regarding the flags used above
  * Options
	  * -h or --help            Display flag information
	  * -t or --test n          BST Unit Test with n elements
	  * -i or --input ifname    Input file
	  * -o or --output ofname   Output file


## System Information
* The program was tested and run on a virtual machine (VirtualBox Version 6.0.24) running Linux Mint 19.3 MATE.

## Acknowledgements
* This project was for CIS 330, C, C++ and Unix at University of Oregon, Winter 2020.

* Professor Jee Choi created the initial version (skeleton code and tests) and project specifications.
