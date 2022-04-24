/*
 * DATE: April 2022
 * NAME: Katelyn Perry
 * 
 * SNHU CS300 Data Structures and Algorithms
 * Project Two
 */

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>

using namespace std;

// structure to hold course information
struct Course {
    string courseName;
    string courseNumber;
    vector<string> prerequisites;
};

// Internal structure for tree node
struct Node {
    Course course;
    Node* left = NULL;
    Node* right = NULL;
};

// Method declarations
class BinarySearchTree {

private:
    Node* root;

    void addNode(Node* node, Course course);
    void inOrder(Node* node);

public:
    BinarySearchTree();
    virtual ~BinarySearchTree();
    void InOrder();
    void Insert(Course course);
    Course Search(string courseNumber);
};

// Constructor
BinarySearchTree::BinarySearchTree() {
    // root is equal to nullptr
    root = nullptr;
}

// Destructor
BinarySearchTree::~BinarySearchTree() {
}

void BinarySearchTree::InOrder() {
    // passes tree root into inOrder function
    inOrder(root);
}

void BinarySearchTree::Insert(Course course) {
    /* If there is no root data,
     * assign root to new node.
     * Otherwise, add Node root and course to tree.
     */
    if (root == nullptr) {
        root = new Node(course);
    }
    else {
        addNode(root, course);
    }

}

Course BinarySearchTree::Search(string courseNumber) {

    // Starts with the root
    Node* current = root;

    /* If the courNumber in the node matches the search 
     * courseNumber, return the course info in node.
     * If search num is less than node's num, traverse
     * to the left. Otherwise, traverse down right until
     * course is found or end of tree.
     */
    while (current != nullptr) {
        if (courseNumber.compare(current->course.courseNumber) == 0) {
            return current->course;
        }
        if (courseNumber.compare(current->course.courseNumber) < 0) {
            current = current->left;
        }
        else {
            current = current->right;
        }
    }

    // return course info
    Course course;
    return course;
}

void BinarySearchTree::addNode(Node* node, Course course) {
    // if search courseNum is < node's courseNum
    if (node->course.courseNumber.compare(course.courseNumber) > 0) {
        // if left node is empty, create new node and assign
        if (node->left == nullptr) {
            node->left = new Node(course);
        }
        // Otherwise call addNode and pass in left child to recurse
        else {
            this->addNode(node->left, course);
        }
    }
    else {
        // if right node is empty, create new node and assign
        if (node->right == nullptr) {
            node->right = new Node(course);
        }
        else {
            this->addNode(node->right, course);
        }
    }
}

void BinarySearchTree::inOrder(Node* node) {
    /* If node contains data, call inOrder function starting with 
    * left side of tree and print course information.
    * Then call in inOrder function, passing in the right side
    */
    if (node != nullptr) {
        inOrder(node->left);
        cout << node->course.courseNumber << ", " << node->course.courseName << endl;
        inOrder(node->right);
    }
}

void loadCourses(string csvPath, BinarySearchTree* bst) {
    cout << "Loading Courses. . ." << csvPath << endl;

    string line;
    string substr;
    vector <string> tokens; // vector to hold substrings of line

    /* If the file opens properly, collect a line.
    * Create a new string stream, and use getline to
    * parse at each comma on line.
    * Add each substring to end of token vector.
    */
    ifstream file(csvPath);
    if (file.is_open()) { 

        while(file.good()) {
            getline(file, line);
            stringstream ss(line); // creates string stream from line string
            Course course;

            while (ss.good()) {
                while(getline(ss, substr, ',')); // while there are sections to parse in line
                tokens.push_back(substr);
            }

           /* Assign course numberand name, check for
            * any prerequisite. If more than 2 tokens exist,
            * then prerequisites exist. Use loop to assign to
            * prequisites vector.
            */
            course.courseNumber = tokens[0];
            course.courseName = tokens[1];
            if (tokens.size() > 2) {
                for (int i = 2; i < tokens.size(); i++) {
                    course.prerequisites.push_back(tokens[i]);
                }
            }
            
            // Inserts course into binary search tree
            bst->Insert(course);
            // Clears tokens for next line
            tokens.clear();
        }
        file.close();
    }
    else {

        cout << "File not found." << endl;
    }

}



int main()
{
    // Define a binary search tree to hold courses
    BinarySearchTree* bst;

    string courseNum;
    string fileName;

    Course course;

    cout << "Welcome to the course planner." << endl;
    int selection = 0;
    while (selection != 9) {
        cout << "1. Load Data Structure" << endl;
        cout << "2. Print Course List" << endl;
        cout << "3. Print Course" << endl;
        cout << "Exit" << endl;
        cout << "What would you like to do?" << endl;
        cin >> selection;

        switch (selection) {
        case 1:

            bst = new BinarySearchTree(); // Creates new tree

            cout << "Enter file name: " << endl;
            cin >> fileName;

            loadCourses(fileName, bst); // Calls to load courses function to parse file
            break;

        case 2:

            cout << "Here is a sample schedule: " << endl;
            bst->InOrder(); // traverses tree and prints courses 
            break;

        case 3:

            cout << "What course do you want to know about?" << endl;
            cin >> courseNum;

            bst->Search(courseNum); // Calls to search function, looks for course by course number

            cout << endl;
            break;

        default:
            cout << "Selection invalid." << endl;
            break;
        }
    }
    cout << "Thank you for using the course planner!" << endl;

    return 0;
}