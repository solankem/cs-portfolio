#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <map>
#include <algorithm>

using namespace std;

// ==============================
// Course Structure
// ==============================
struct Course {
    string courseNumber;
    string courseTitle;
    vector<string> prerequisites;
};

// ==============================
// Global Data Structure
// ==============================
map<string, Course> courseMap;

// ==============================
// Helper: Convert to Uppercase
// ==============================
string toUpper(string str) {
    for (char& c : str) {
        c = toupper(c);
    }
    return str;
}

// ==============================
// Load Data From File
// ==============================
void loadDataStructure(string fileName) {
    ifstream file(fileName);

    if (!file.is_open()) {
        cout << "Error: Could not open file." << endl;
        return;
    }

    courseMap.clear();

    string line;

    while (getline(file, line)) {
        stringstream ss(line);
        string token;

        Course course;

        // Course Number
        getline(ss, token, ',');
        course.courseNumber = toUpper(token);

        // Course Title
        getline(ss, token, ',');
        course.courseTitle = token;

        // Prerequisites
        while (getline(ss, token, ',')) {
            course.prerequisites.push_back(toUpper(token));
        }

        // Store in map
        courseMap[course.courseNumber] = course;
    }

    file.close();
    cout << "Data successfully loaded." << endl;
}

// ==============================
// Print Sorted Course List
// ==============================
void printCourseList() {
    if (courseMap.empty()) {
        cout << "No data loaded. Please load a file first." << endl;
        return;
    }

    vector<Course> courses;

    // Move map data to vector
    for (auto& pair : courseMap) {
        courses.push_back(pair.second);
    }

    // Sort alphanumerically by course number
    sort(courses.begin(), courses.end(), [](Course a, Course b) {
        return a.courseNumber < b.courseNumber;
        });

    cout << "\nCourse List:\n";

    for (Course& c : courses) {
        cout << c.courseNumber << ", " << c.courseTitle << endl;
    }
}

// ==============================
// Print Course Information
// ==============================
void printCourseInformation(string courseNumber) {
    courseNumber = toUpper(courseNumber);

    if (courseMap.find(courseNumber) == courseMap.end()) {
        cout << "Course not found." << endl;
        return;
    }

    Course course = courseMap[courseNumber];

    cout << "\n" << course.courseNumber << ", " << course.courseTitle << endl;

    if (course.prerequisites.empty()) {
        cout << "Prerequisites: None" << endl;
    }
    else {
        cout << "Prerequisites: ";

        for (size_t i = 0; i < course.prerequisites.size(); i++) {
            string pre = course.prerequisites[i];

            if (courseMap.find(pre) != courseMap.end()) {
                cout << pre << " (" << courseMap[pre].courseTitle << ")";
            }
            else {
                cout << pre;
            }

            if (i < course.prerequisites.size() - 1) {
                cout << ", ";
            }
        }
        cout << endl;
    }
}

// ==============================
// Display Menu
// ==============================
void displayMenu() {
    cout << "\nMenu:\n";
    cout << "1. Load Data Structure\n";
    cout << "2. Print Course List\n";
    cout << "3. Print Course\n";
    cout << "9. Exit\n";
}

// ==============================
// Main Function
// ==============================
int main() {
    int choice = 0;
    string fileName;
    string courseNumber;

    cout << "Welcome to the Advising Assistance Program!" << endl;

    while (choice != 9) {
        displayMenu();
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {
        case 1:
            cout << "Enter file name: ";
            cin >> fileName;
            loadDataStructure(fileName);
            break;

        case 2:
            printCourseList();
            break;

        case 3:
            cout << "Enter course number: ";
            cin >> courseNumber;
            printCourseInformation(courseNumber);
            break;

        case 9:
            cout << "Exiting program. Goodbye!" << endl;
            break;

        default:
            cout << "Invalid choice. Please try again." << endl;
        }
    }

    return 0;
}