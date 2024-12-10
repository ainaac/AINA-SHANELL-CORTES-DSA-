#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <map>

using namespace std;

// Struct to store student information
struct Student {
    string name;
    string course;
    string school;
    int studentNumber;
    int score;
};

// Function to display the contents of a heap for each course
void displayHeap(const map<string, vector<Student>>& section) {
    for (const auto& entry : section) {
        cout << "Course: " << entry.first << "\n";
        for (const auto& student : entry.second) {
            cout << "Name: " << student.name << ", Score: " << student.score << "\n";
        }
    }
    cout << endl;
}

// Function to assign students to sections based on their scores
void assignToSections(map<string, vector<Student>>& giftedSection,
                      map<string, vector<Student>>& mediocreSection,
                      map<string, vector<Student>>& averageSection,
                      const Student& student) {
    if (student.score >= 85 && student.score <= 100) {
        giftedSection[student.course].push_back(student);
        cout << "Student " << student.name << " (" << student.course << ") is assigned to the Gifted Section.\n";
    } else if (student.score >= 0 && student.score <= 30) {
        averageSection[student.course].push_back(student);
        cout << "Student " << student.name << " (" << student.course << ") is assigned to the Average Section.\n";
    } else {
        mediocreSection[student.course].push_back(student);
        cout << "Student " << student.name << " (" << student.course << ") is assigned to the Mediocre Section.\n";
    }

    // Apply heap to each section based on scores
    make_heap(giftedSection[student.course].begin(), giftedSection[student.course].end(),
              [](const Student& a, const Student& b) { return a.score < b.score; }); // Max-Heap for Gifted
    make_heap(mediocreSection[student.course].begin(), mediocreSection[student.course].end(),
              [](const Student& a, const Student& b) { return a.score < b.score; }); // Max-Heap for Mediocre
    make_heap(averageSection[student.course].begin(), averageSection[student.course].end(),
              [](const Student& a, const Student& b) { return a.score > b.score; }); // Min-Heap for Average
}

// Main function
int main() {
    map<string, vector<Student>> giftedSection;  // Max-heap for Gifted Section
    map<string, vector<Student>> mediocreSection; // Max-heap for Mediocre Section
    map<string, vector<Student>> averageSection; // Min-heap for Average Section
    map<int, Student> studentRecords; // Maps student number to student info
    bool isRegistered = false;
    Student currentStudent;

    cout << "=== Entrance Exam Score System ===\n";
    cout << "1. Register a new student\n";
    cout << "2. View a student's section\n";
    cout << "3. Display all class sections\n";
    cout << "4. Exit\n";

    int choice;
    do {
        cout << "\nEnter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1: {
                // Registration process
                cout << "=== Registering Student ===\n";
                cin.ignore(); // Clear newline left by previous input
                cout << "Enter the student's full name: ";
                getline(cin, currentStudent.name);
                cout << "Enter the student's course: ";
                getline(cin, currentStudent.course);
                cout << "Enter the school where the student graduated: ";
                getline(cin, currentStudent.school);
                cout << "Enter the student's number: ";
                cin >> currentStudent.studentNumber;

                // Register the student
                studentRecords[currentStudent.studentNumber] = currentStudent;
                isRegistered = true;

                cout << "Student " << currentStudent.name << " (" << currentStudent.course << ") is successfully registered.\n";
                break;
            }
            case 2: {
                // Viewing the student's section (asking for score in Case 2)
                if (!isRegistered) {
                    cout << "Please register first (Case 1) before proceeding.\n";
                    break;
                }

                string name, course;
                int score;
                cin.ignore(); // Clear newline left by previous input
                cout << "Enter the student's full name: ";
                getline(cin, name);
                cout << "Enter the student's course: ";
                getline(cin, course);
                cout << "Enter the student's score (0-100): ";
                cin >> score;

                // Create a student object with the input data
                Student student;
                student.name = name;
                student.course = course;
                student.score = score;
                student.studentNumber = currentStudent.studentNumber;

                // Assign to sections based on score
                assignToSections(giftedSection, mediocreSection, averageSection, student);
                break;
            }
            case 3: {
                // Display all class sections
                cout << "\n=== Displaying All Class Sections ===\n";
                cout << "Gifted Section:\n";
                displayHeap(giftedSection);
                cout << "Mediocre Section:\n";
                displayHeap(mediocreSection);
                cout << "Average Section:\n";
                displayHeap(averageSection);
                break;
            }
            case 4:
                cout << "Exiting the program.\n";
                break;
            default:
                cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 4);

    return 0;
}
