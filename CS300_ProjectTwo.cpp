/* 
* CS-300 Project Two
* Noelle Bishop
* February 17, 2025
* 
* This is a program that reads college courses' data from a .csv file into a binary search tree (BST).
* The user can interact with a menu to view the courses' data through the BST.
* 
*/

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>

using namespace std;

// For storing courses' information
struct Course {
    string courseNumber;
    string courseTitle;
    vector<string> prerequisites;
};

// For use with the BST class
struct Node {
    Course course;
    Node* left;
    Node* right;

    Node() {
        left = nullptr;
        right = nullptr;
    }

    Node(Course aCourse) : Node() {
        course = aCourse;
    }
};

// The data structure in use for storing courses
class BinarySearchTree {
    private:
        Node* root;
        void addNode(Node* node, Course course);
        void deleteTree(Node* node);
    public:
        BinarySearchTree() {
            root = nullptr;
        }
        ~BinarySearchTree() {
            deleteTree(root);
        }
        void Insert(Course course);
        void inOrder(Node* node);
        void printSortedCourses();
        void searchCourses(string courseNumber);
};

// Recursively delete all nodes in BST
void BinarySearchTree::deleteTree(Node* node) {
    if (node != nullptr) {
        deleteTree(node->left);
        deleteTree(node->right);
        delete node;
    }
}

// Recursively add nodes to BST
void BinarySearchTree::addNode(Node* node, Course course) {
    // BST is sorted by course number to put lower-level courses first
    if (course.courseNumber < node->course.courseNumber) {
        if (node->left == nullptr) {
            node->left = new Node(course);
        }
        else {
            addNode(node->left, course);
        }
    }
    else {
        if (node->right == nullptr) {
            node->right = new Node(course);
        }
        else {
            addNode(node->right, course);
        }
    }
}

// Establish root node, add nodes to BST using addNode()
void BinarySearchTree::Insert(Course course) {
    if (root == nullptr) {
        root = new Node(course);
    }
    else {
        addNode(root, course);
    }
}

// Print all nodes in BST using inOrder()
void BinarySearchTree::printSortedCourses() {
    if (root == nullptr) {
        cout << "Nothing to sort; no courses loaded.\n" << endl;
        return;
    }
    else {
        inOrder(root);
        cout << "\n" << endl;
    }
}

// Output nodes' information in the order nodes are stored in the BST
void BinarySearchTree::inOrder(Node* node) {
    if (node != nullptr) {
        inOrder(node->left);
        
        // Output each course's information
        cout << "Number: " << node->course.courseNumber << " | Title: " << node->course.courseTitle << " | Prerequisite(s): ";
        if (node->course.prerequisites.empty()) {
            cout << "None" << endl;
        }
        else {
            for (string prereq : node->course.prerequisites) {
                cout << prereq << " ";
            }
            cout << "" << endl;
        }

        inOrder(node->right);
    }
}

// Search the BST for a specific course
void BinarySearchTree::searchCourses(string courseNumber) {
    Node* currentCourse = root;

    // Output each course's information
    while (currentCourse != nullptr) {
        if (currentCourse->course.courseNumber == courseNumber) {
            cout << "Number: " << currentCourse->course.courseNumber << " | Title: " << currentCourse->course.courseTitle << " | Prerequisite(s): ";

            if (currentCourse->course.prerequisites.empty()) {
                cout << "None\n" << endl;
            }
            else {
                for (string prereq : currentCourse->course.prerequisites) {
                    cout << prereq << " ";
                }
                cout << "\n" << endl;
            }

            return;  // Because the course was found
        }
        else if (courseNumber < currentCourse->course.courseNumber) {
            currentCourse = currentCourse->left;
        }
        else {
            currentCourse = currentCourse->right;
        }
    }

    cout << "Course not found." << endl;
}

// Split each CSV line into its appropriate parts of a Course struct
Course readCourseData(string line, char delimiter) {
    Course course;

    string token;
    stringstream lineToParse(line);
    int index = 0;

    // NOTE: I referenced https://www.geeksforgeeks.org/how-to-split-string-by-delimiter-in-cpp/ for this
    while (getline(lineToParse, token, delimiter)) {
        if (index == 0) {  // Course number appears in first column
            course.courseNumber = token;
        }
        else if (index == 1) {  // Course title appears in second column
            course.courseTitle = token;
        } 
        else {  // Prerequisites appear in column three and beyond
            // This stops the program from reading empty spaces as prerequisites
            if (token != "") {
                course.prerequisites.push_back(token);
            }
        }
        index += 1;
    }

    return course;
}

// Load courses into BST from CSV file, perform error checks
void loadCoursesFromFile(string filename, BinarySearchTree* bst) {
    vector<string> validCourses;

    ifstream coursesFile(filename);
    char delimiter = ',';
    string line;

    // First pass: read CSV file, populate validCourses
    try {
        if (!coursesFile.is_open()) {  // If the file isn't opening...
            throw runtime_error("Error opening file.");
        }

        while (getline(coursesFile, line)) {
            Course course = readCourseData(line, delimiter);
            validCourses.push_back(course.courseNumber);
        }

        coursesFile.close();
        if (coursesFile.is_open()) {  // If the file isn't closing...
            throw runtime_error("Error closing file.");
        }

    }
    catch (const runtime_error& e) {
        cout << e.what() << endl;
        return;
    }

    // Second pass: read CSV file, validate prerequisites with validCourses
    try {
        coursesFile.open(filename);
        if (!coursesFile.is_open()) {  // If the file isn't opening...
            throw runtime_error("Error opening file.");
        }

        while (getline(coursesFile, line)) {
            Course course = readCourseData(line, delimiter);

            if (course.courseNumber.empty() || course.courseTitle.empty()) {
                throw runtime_error("Invalid format: missing number or title.");
            }

            // Validate prerequisites
            for (string prereq : course.prerequisites) {
                if (prereq.empty()) {
                    continue; // Skip blank prerequisites to avoid erroneous error throwing
                }

                // NOTE: I referenced https://www.geeksforgeeks.org/std-find-in-cpp/
                if (find(validCourses.begin(), validCourses.end(), prereq) == validCourses.end()) {
                    throw runtime_error("Invalid prerequisite: " + prereq);
                }
            }

            bst->Insert(course);
        }

        coursesFile.close();
        if (coursesFile.is_open()) {  // If the file isn't closing...
            throw runtime_error("Error closing file.");
        }
    }
    catch (const runtime_error& e) {
        cout << e.what() << endl;
        return;
    }
}

// Interact with the program's menu
int main()
{
    BinarySearchTree* bst;
    bst = new BinarySearchTree();

    Course course;
    string fileName = "CS 300 ABCU_Advising_Program_Input.csv";

    int choice = 0;
    bool coursesLoaded = false;

    while (choice != 9) {
        cout << "Menu:" << endl;
        cout << "1. Load courses" << endl;
        cout << "2. Print a sorted list of all courses" << endl;
        cout << "3. Print a specific course and its prerequisite(s)" << endl;
        cout << "9. Exit\n" << endl;
        cout << "Please enter a number: " << endl;

        cin >> choice;

        // NOTE: I had to refresh my memory on C++ input validation; I referenced https://www.geeksforgeeks.org/cin-clear-function-in-cpp/
        while (cin.fail()) {
            cout << "Invalid input: please enter a number." << endl;
            cin.clear();  // Clear error state
            cin.ignore(1000, '\n');  // Ignore invalid input in the buffer

            cin >> choice;  // Try again
        }

        if (choice != 1 && choice != 2 && choice != 3 && choice != 9) {
            cout << "Invalid choice: please enter a number 1-3 or 9.\n" << endl;
            continue;  // Restart the loop
        }

        switch (choice) {
            // Load courses from .csv file
            case 1:
                cout << "Loading " << fileName << "..." << endl;
                loadCoursesFromFile(fileName, bst);
                coursesLoaded = true;
                cout << "Courses loaded.\n" << endl;
                break;
            // Print a list of courses sorted by their courseNumber
            case 2:
                if (coursesLoaded == false) {
                    cout << "Please load courses first!\n" << endl;
                    break;
                }
                else {
                    bst->printSortedCourses();
                    break;
                }
            // Search for a specific course, print its information
            case 3:
                string courseNumber;

                if (coursesLoaded == false) {
                    cout << "Please load courses first!\n" << endl;
                    break;
                }
                else {
                    cout << "\nPlease enter the course number of the one you're looking for: " << endl;
                    cin >> courseNumber;

                    while (cin.fail()) {
                        cout << "\nInvalid input: please enter a series of characters such as CSCI200." << endl;
                        cin.clear();  // Clear error state
                        cin.ignore(1000, '\n');  // Ignore invalid input in the buffer

                        cin >> courseNumber;  // Try again
                    }

                    bst->searchCourses(courseNumber);
                    break;
                }
        }
    }
    cout << "Closing the program... Goodbye!" << endl;
    return 0;
}

