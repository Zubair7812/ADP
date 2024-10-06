#include <iostream>
#include <vector>
#include <iomanip>
#include <algorithm>
#include <fstream>

class Student {
public:
    std::string name;
    int rollNumber;
    double marks;

    Student(std::string n, int roll, double m)
        : name(n), rollNumber(roll), marks(m) {}
};

class StudentRecordSystem {
private:
    std::vector<Student> students;

public:
    // Add student to the system
    void addStudent(const Student& student) {
        students.push_back(student);
    }

    // Display all students
    void displayStudents() const {
        if (students.empty()) {
            std::cout << "No students to display.\n";
            return;
        }

        std::cout << std::setw(20) << "Name" << std::setw(15) << "Roll Number"
                  << std::setw(10) << "Marks" << std::endl;

        for (const auto& student : students) {
            std::cout << std::setw(20) << student.name
                      << std::setw(15) << student.rollNumber
                      << std::setw(10) << student.marks << std::endl;
        }
    }

    // Search for a student by roll number
    void searchStudent(int rollNumber) const {
        auto it = std::find_if(students.begin(), students.end(),
            [rollNumber](const Student& student) { return student.rollNumber == rollNumber; });

        if (it != students.end()) {
            std::cout << "Student found:\n";
            std::cout << std::setw(20) << "Name" << std::setw(15) << "Roll Number"
                      << std::setw(10) << "Marks" << std::endl;
            std::cout << std::setw(20) << it->name
                      << std::setw(15) << it->rollNumber
                      << std::setw(10) << it->marks << std::endl;
        } else {
            std::cout << "Student not found.\n";
        }
    }

    // Update a student's record
    void updateStudent(int rollNumber) {
        auto it = std::find_if(students.begin(), students.end(),
            [rollNumber](const Student& student) { return student.rollNumber == rollNumber; });

        if (it != students.end()) {
            std::string newName;
            double newMarks;

            std::cout << "Enter new name for student: ";
            std::cin.ignore();
            std::getline(std::cin, newName);

            std::cout << "Enter new marks for student: ";
            std::cin >> newMarks;

            it->name = newName;
            it->marks = newMarks;

            std::cout << "Student updated successfully.\n";
        } else {
            std::cout << "Student not found.\n";
        }
    }

    // Delete a student's record
    void deleteStudent(int rollNumber) {
        auto it = std::remove_if(students.begin(), students.end(),
            [rollNumber](const Student& student) { return student.rollNumber == rollNumber; });

        if (it != students.end()) {
            students.erase(it, students.end());
            std::cout << "Student deleted successfully.\n";
        } else {
            std::cout << "Student not found.\n";
        }
    }

    // Sort students by marks or name
    void sortStudents(bool byMarks = true) {
        if (byMarks) {
            std::sort(students.begin(), students.end(),
                [](const Student& a, const Student& b) { return a.marks > b.marks; });
            std::cout << "Students sorted by marks.\n";
        } else {
            std::sort(students.begin(), students.end(),
                [](const Student& a, const Student& b) { return a.name < b.name; });
            std::cout << "Students sorted by name.\n";
        }
    }

    // Save student records to a file
    void saveToFile(const std::string& filename) const {
        std::ofstream outFile(filename);
        if (outFile.is_open()) {
            for (const auto& student : students) {
                outFile << student.name << "," << student.rollNumber << "," << student.marks << "\n";
            }
            outFile.close();
            std::cout << "Data saved to file.\n";
        } else {
            std::cout << "Error opening file.\n";
        }
    }

    // Load student records from a file
    void loadFromFile(const std::string& filename) {
        std::ifstream inFile(filename);
        if (inFile.is_open()) {
            students.clear();
            std::string name;
            int rollNumber;
            double marks;

            while (inFile >> std::ws && std::getline(inFile, name, ',') &&
                   inFile >> rollNumber >> std::ws && inFile.get() &&
                   inFile >> marks >> std::ws) {
                students.push_back(Student(name, rollNumber, marks));
            }
            inFile.close();
            std::cout << "Data loaded from file.\n";
        } else {
            std::cout << "Error opening file.\n";
        }
    }
};

int main() {
    StudentRecordSystem recordSystem;

    int choice;
    do {
        std::cout << "\nOptions:\n";
        std::cout << "1. Display Students\n";
        std::cout << "2. Search Student\n";
        std::cout << "3. Add Student\n";
        std::cout << "4. Update Student\n";
        std::cout << "5. Delete Student\n";
        std::cout << "6. Sort Students by Marks\n";
        std::cout << "7. Sort Students by Name\n";
        std::cout << "8. Save to File\n";
        std::cout << "9. Load from File\n";
        std::cout << "10. Exit\n";
        std::cout << "Enter your choice: ";
        std::cin >> choice;

        switch (choice) {
            case 1:
                recordSystem.displayStudents();
                break;
            case 2: {
                int rollNumber;
                std::cout << "Enter the roll number of the student: ";
                std::cin >> rollNumber;
                recordSystem.searchStudent(rollNumber);
                break;
            }
            case 3: {
                std::string name;
                int rollNumber;
                double marks;
                std::cout << "Enter name: ";
                std::cin.ignore();
                std::getline(std::cin, name);
                std::cout << "Enter roll number: ";
                std::cin >> rollNumber;
                std::cout << "Enter marks: ";
                std::cin >> marks;
                recordSystem.addStudent(Student(name, rollNumber, marks));
                break;
            }
            case 4: {
                int rollNumber;
                std::cout << "Enter the roll number of the student to update: ";
                std::cin >> rollNumber;
                recordSystem.updateStudent(rollNumber);
                break;
            }
            case 5: {
                int rollNumber;
                std::cout << "Enter the roll number of the student to delete: ";
                std::cin >> rollNumber;
                recordSystem.deleteStudent(rollNumber);
                break;
            }
            case 6:
                recordSystem.sortStudents(true); // Sort by marks
                break;
            case 7:
                recordSystem.sortStudents(false); // Sort by name
                break;
            case 8: {
                std::string filename;
                std::cout << "Enter filename to save to: ";
                std::cin >> filename;
                recordSystem.saveToFile(filename);
                break;
            }
            case 9: {
                std::string filename;
                std::cout << "Enter filename to load from: ";
                std::cin >> filename;
                recordSystem.loadFromFile(filename);
                break;
            }
            case 10:
                std::cout << "Exiting program.\n";
                break;
            default:
                std::cout << "Invalid choice. Try again.\n";
        }

    } while (choice != 10);

    return 0;
}
