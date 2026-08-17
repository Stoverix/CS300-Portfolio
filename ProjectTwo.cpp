#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>
#include <cctype>

using namespace std;

// Stores information about one course
struct Course {
    string courseNumber;
    string courseTitle;
    vector<string> prerequisites;
};

// Node used for the binary search tree
struct Node {
    Course course;
    Node* left;
    Node* right;

    Node(Course aCourse) {
        course = aCourse;
        left = nullptr;
        right = nullptr;
    }
};

// Binary search tree used to store courses
class BinarySearchTree {
private:
    Node* root;

    Node* insertNode(Node* node, Course course) {
        if (node == nullptr) {
            return new Node(course);
        }

        if (course.courseNumber < node->course.courseNumber) {
            node->left = insertNode(node->left, course);
        }
        else {
            node->right = insertNode(node->right, course);
        }

        return node;
    }

    void printInOrder(Node* node) {
        if (node != nullptr) {
            printInOrder(node->left);

            cout << node->course.courseNumber << ", "
                << node->course.courseTitle << endl;

            printInOrder(node->right);
        }
    }
    

public:
    BinarySearchTree() {
        root = nullptr;
    }

    void insert(Course course) {
        root = insertNode(root, course);
    }

    void printCourseList() {
        cout << "Here is a sample schedule:" << endl;
        printInOrder(root);
    }

    Course* search(string courseNumber) {
        Node* current = root;

        while (current != nullptr) {
            if (courseNumber == current->course.courseNumber) {
                return &current->course;
            }

            if (courseNumber < current->course.courseNumber) {
                current = current->left;
            }
            else {
                current = current->right;
            }
        }

        return nullptr;
    }
};


void loadCourses(string fileName, BinarySearchTree& courseTree) {

    ifstream file(fileName);

    if (!file.is_open()) {
        cout << "Error opening file." << endl;
        return;
    }

    string line;

    while (getline(file, line)) {

        stringstream ss(line);
        string item;

        Course course;

        getline(ss, course.courseNumber, ',');
        getline(ss, course.courseTitle, ',');

        while (getline(ss, item, ',')) {
            course.prerequisites.push_back(item);
        }

        courseTree.insert(course);
    }

    file.close();

    cout << "Course data loaded successfully." << endl;
}

int main() {

    BinarySearchTree courseTree;

    int choice = 0;

    cout << "Welcome to the course planner." << endl;

    while (choice != 9) {

        cout << endl;
        cout << "1. Load Data Structure." << endl;
        cout << "2. Print Course List." << endl;
        cout << "3. Print Course." << endl;
        cout << "9. Exit" << endl;
        cout << "What would you like to do? ";

        if (!(cin >> choice)) {
            cout << "Invalid input. Please enter a number." << endl;
            cin.clear();
            cin.ignore(1000, '\n');
            continue;
        }

        if (choice == 1) {
            string fileName;

            cout << "Enter the course data file name: ";
            cin.ignore();
            getline(cin, fileName);

            loadCourses(fileName, courseTree);
        }

        else if (choice == 2) {
            courseTree.printCourseList();
        }

        else if (choice == 3) {

            string courseNumber;

            cout << "What course do you want to know about? ";
            cin >> courseNumber;

            transform(courseNumber.begin(), courseNumber.end(),
                courseNumber.begin(), ::toupper);

            Course* course = courseTree.search(courseNumber);

            if (course != nullptr) {

                cout << course->courseNumber << ", "
                    << course->courseTitle << endl;

                cout << "Prerequisites: ";

                for (int i = 0; i < course->prerequisites.size(); i++) {

                    cout << course->prerequisites[i];

                    if (i < course->prerequisites.size() - 1) {
                        cout << ", ";
                    }
                }

                cout << endl;
            }
            else {
                cout << "Course not found." << endl;
            }
        }

        else if (choice == 9) {
            cout << "Thank you for using the course planner!" << endl;
        }

        else {
            cout << choice << " is not a valid option." << endl;
        }

    }

    return 0;
}
        
