//============================================================================
// Name        : ProjectTwo.cpp
// Author      : Stockton Toronto
// Version     : 1.0
//============================================================================

#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <random>

using namespace std;

//============================================================================
// Global definitions visible to all methods and classes
//============================================================================

// struct to hold course information
struct Course {
    string num;
    string name;
    vector<string> prereqs;

    Course() {}

    Course(string aNum, string aName, vector<string> aPrereqs) {
        num = aNum;
        name = aName;
        prereqs = aPrereqs;
    }
};

// structure for tree node
struct Node {
    Course course;

    Node* left = nullptr;
    Node* right = nullptr;

    Node() {}

    Node(Course aCourse) {
        course = aCourse;
    }
};

//============================================================================
// Binary Search Tree class definition
//============================================================================

class BinarySearchTree {
    
private:
    Node* root;
    unsigned int size = 0;

    void addNode(Node* aNode, Course aCourse);
    const void inOrder(Node* aNode);

public:
    unsigned int Size();
    
    BinarySearchTree();
    const void InOrder();
    void Insert(Course aCourse);
    const Course Search(string aCourseNum);

    const void displayCourse(Course aCourse, bool aPrereqs = false);
};

// Default constructor
BinarySearchTree::BinarySearchTree() {
    // set root to nullptr
    root = nullptr;
}

// Size getter
unsigned int BinarySearchTree::Size() {
    return size;
}

// in order tree traversal
const void BinarySearchTree::InOrder() {
    // call inOrder function and pass root
    inOrder(root);
}

// insert a new course
void BinarySearchTree::Insert(Course aCourse) {
    // if tree is empty, new course becomes root
    if (root == nullptr) {
        root = new Node(aCourse);
        size++;
    }
    // else, call the addNode function and pass root and course
    else
        addNode(root, aCourse);
}

// search for course given course num
const Course BinarySearchTree::Search(string aCourseNum) {
    // start search at root node
    Node* curr = root;
    int comparison;

    // keep looping downwards until either bottom is reached or match
    while (curr != nullptr) {
        
        // compare strings and store result
        comparison = curr->course.num.compare(aCourseNum);
        
        // if matching course is found, return it
        if (comparison == 0)
            return curr->course;

        // else if course num is less than current node, travese left
        else if (comparison > 0)
            curr = curr->left;

        // else, traverse right
        else
            curr = curr->right;
    }

    // if no match is found, return empty course
    return Course();
}

// add course to tree
void BinarySearchTree::addNode(Node* aNode, Course aCourse) {
     
    // if node is larger than add to left
    if (aNode->course.num.compare(aCourse.num) > 0) {
        // if there is no left node, this course becomes left
        if (aNode->left == nullptr) {
            aNode->left = new Node(aCourse);
            size++;
        }
        // else, recurse down the left node
        else
            addNode(aNode->left, aCourse);
    }
    // else add to right
    else {
        // if there is no right node, this course becomes right
        if (aNode->right == nullptr) {
            aNode->right = new Node(aCourse);
            size++;
        }
        // else, recurse down the right node
        else
            addNode(aNode->right, aCourse);
    }
}

// recursive function for in order traversal
const void BinarySearchTree::inOrder(Node* aNode) {
    
    if (aNode != nullptr) {
        
        // recursive call, left
        inOrder(aNode->left);

        // display course info
        displayCourse(aNode->course);

        // recursive call, right
        inOrder(aNode->right);
    }
}

// display function, set second arg to true if prereqs are desired
const void BinarySearchTree::displayCourse(Course aCourse, bool aPrereqs) {
    cout << aCourse.num << ": " << aCourse.name << endl;

    // print prereqs is passed bool is true
    if (aPrereqs) {

        cout << "Prerequisites: " << flush;

        // if prereqs is empty, print none
        if (aCourse.prereqs.size() == 0)
            cout << "none" << endl;

        // else, loop through prereqs and print each item
        else {
            for (unsigned int i = 0; i < aCourse.prereqs.size() - 1; i++) {
                cout << aCourse.prereqs.at(i) << ", " << flush;
            }
            // print last prereq and end with new line
            cout << aCourse.prereqs.at(aCourse.prereqs.size() - 1) << endl;
        }
    }
}

// method to fill binary search tree from file data
void loadCourses(const string& aPath, BinarySearchTree* aBst) {

    // vector object to store courses before using bst
    vector<Course> coursesList;

    // use stream in object to load file lines
    ifstream streamIn;
    string inLine;
    streamIn.open(aPath);
    streamIn.ignore(3);

    // checks that input file has been opened properly
    if (!streamIn.is_open()) {
        cout << "\nError: Failed to open input file\n" <<
            "Make sure the file is in the same folder as this program!" << endl;
        return;
    }

    // loop through file while until end is reached
    while (!streamIn.eof() && streamIn.good()) {
        // vector object to store substrings for each input line
        vector<string> substrings;

        // get line from file
        getline(streamIn, inLine);

        // create string stream to split string into substrings
        stringstream s_stream(inLine);

        // iterate through string stream and add substrings to vector
        while (s_stream.good()) {
            string substr;
            getline(s_stream, substr, ',');
            substrings.push_back(substr);
        }

        // check substrings vector size
        if (substrings.size() < 2)
            continue;

        // iterate though courses list to check for duplicates
        bool valid = true;
        for (unsigned int i = 0; i < coursesList.size() && valid; i++) {
            if (coursesList.at(i).num.compare(substrings.at(0)) == 0)
                valid = false;
        }
        if (!valid)
            continue;

        //create prerequisistes subvector
        vector<string> prereqs(substrings.begin() + 2, substrings.end());

        // create course object
        Course newCourse = Course(substrings.at(0), substrings.at(1), prereqs);
        // add course to courses list
        coursesList.push_back(newCourse);
    }

    // Check each item in courses list has prereqs also in list
    bool valid = true;
    bool itemRemoved = false;
    do {
        itemRemoved = false;
        
        // loop through each course
        for (unsigned int i = 0; i < coursesList.size(); i++) {
            valid = true;

            // loop through each course's prereqs
            for (unsigned int j = 0; j < coursesList.at(i).prereqs.size() && valid; j++) {
                valid = false;

                // loop through each course k and compare
                // to each prereq of course i
                for (unsigned int k = 0; k < coursesList.size() && !valid; k++) {
                    if (coursesList.at(k).num.compare(coursesList.at(i).prereqs.at(j)) == 0)
                        valid = true;
                }
            }

            if (valid == false) {
                coursesList.erase(coursesList.begin() + i);
                itemRemoved = true;
            }
        }
    
    // repeat if an item was removed, the removed item could
    // have been a prereq for another item
    } while (itemRemoved == true);
    
    // populate bst with the courses list
    for (unsigned int i = 0; i < coursesList.size(); i++) {
        aBst->Insert(coursesList.at(i));
    }
}

// main method
int main()
{
    // file name to be loaded
    const string filePath = "ABCU_Advising_Program_Input.txt";

    // create binary search tree to hold courses
    BinarySearchTree* bst = new BinarySearchTree();

    Course course;

    // code for menu
    cout << "Welcome to the course planner." << endl;
    
    string input;
    int choice = 0;
    string searchNum;
    while (choice != 9) {
        cout << "\n  1. Load Courses Data" << endl;
        cout << "  2. Print Course List" << endl;
        cout << "  3. Print Course" << endl;
        cout << "  9. Exit" << endl;
        cout << "\nWhat would you like to do? " << flush;
        getline(cin, input);

        //try to change input from string to int
        try { choice = stoi(input); }
        catch (...) {
            choice = 0;
        }
        
        // perform operation based on choice
        switch (choice) {
        
        case 1:
            loadCourses(filePath, bst);
            break;

        case 2:
            if (bst->Size() == 0) {
                cout << "\nThere are no courses loaded" << endl;
                break;
            }
            
            cout << "\nHere is a sample list:\n" << endl;

            bst->InOrder();
            break;

        case 3:
            if (bst->Size() == 0) {
                cout << "\nThere are no courses loaded" << endl;
                break;
            }
            
            cout << "\nWhat course number would you like to print? " << flush;
            getline(cin, searchNum);

            // change search number to upper case
            for (unsigned int i = 0; i < searchNum.length(); i++) {
                searchNum.at(i) = toupper(searchNum.at(i));
            }
            
            // search for course matching search number
            course = bst->Search(searchNum);

            // if return course is empty, no match was found
            if (course.num.empty())
                cout << "\nCourse number " << "\"" << searchNum << "\"" << " was not found." << endl;
            // else, use display function to print info, including prereqs
            else {
                cout << endl;
                bst->displayCourse(course, true);
            }
            break;

        case 9:
            return 0;

        default:
            cout << "\n" << "\"" << input << "\"" << " is not a valid option." << endl;
        }
    }
}
