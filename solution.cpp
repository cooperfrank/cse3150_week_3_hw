#include <iostream>
#include <cstring>   // for strlen, strcpy

void addStudent(char* name, double gpa, char* names[], double gpas[], int& size, int capacity);
void updateGPA(double* gpaPtr, double newGpa);
void printStudent(const char* name, const double& gpa);
double averageGPA(const double gpas[], int size);

void addStudent(char* name, double gpa, char* names[], double gpas[], int& size, int capacity) {
    if (size == capacity) {
        throw "List full";
    }

    names[size] = new char[std::strlen(name) + 1];
    std::strcpy(names[size], name);
    gpas[size] = gpa;

    size++;
}

void updateGPA(double* gpaPtr, double newGpa) {
    *gpaPtr = newGpa;
}

void printStudent(const char* name, const double& gpa) {
    std::cout << name << ": " << gpa << std::endl;
}

double averageGPA(const double gpas[], int size) {
    if (size == 0) {
        throw "No students";
    }

    double total = 0.0;

    for (int i = 0; i < size; i++) {
        total += gpas[i];
    }

    return total / size;
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cout << "Usage: ./program <capacity>" << std::endl;
        return 1;
    }

    int capacity = std::stoi(argv[1]);
    char* names[capacity];
    double gpas[capacity];
    int size = 0;

    int choice;
    do {
        std::cout << "Menu:\n";
        std::cout << "1. Add student\n";
        std::cout << "2. Update GPA\n";
        std::cout << "3. Print all students\n";
        std::cout << "4. Compute average GPA\n";
        std::cout << "5. Quit\n";
        std::cout << "Enter choice: ";
        std::cin >> choice;

        switch (choice) {
            case 1: {
                // Add student
                std::cout << "Enter student name: ";
                char name[100];
                std::cin >> name;

                std::cout << "Enter student GPA: ";
                double gpa;
                std::cin >> gpa;

                try {
                    addStudent(name, gpa, names, gpas, size, capacity);
                }
                catch (const char* msg) {
                    std::cout << "Add Student Error: " << msg << std::endl;
                }

                break;
            }
            case 2: {
                // Update GPA
                std::cout << "Enter index of GPA to update: ";
                int index;
                std::cin >> index;

                std::cout << "Enter new GPA: ";
                double gpa;
                std::cin >> gpa;

                updateGPA(&gpas[index], gpa);

                break;
            }
            case 3: {
                // Print all students
                for (int i = 0; i < size; i++) {
                    printStudent(names[i], gpas[i]);
                }

                break;
            }
            case 4: {
                // Average GPA
                try {
                    double avg = averageGPA(gpas, size);
                    int avg_int = static_cast<int>(avg);
                    std::cout << "Average GPA: " << avg_int << std::endl;
                }
                catch (const char* msg) {
                    std::cout << "Average GPA Error: " << msg << std::endl;
                }

                break;
            }
            case 5: {
                std::cout << "Goodbye!" << std::endl;
                break;
            }
            default: {
                std::cout << "Invalid choice" << std::endl;
            }
        }
    } while (choice != 5);

    // Free memory
    for (int i = 0; i < size; i++) {
        delete[] names[i];
    }

    return 0;
}
