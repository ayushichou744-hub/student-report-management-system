#include <iostream>
#include <fstream>
#include <iomanip>
using namespace std;

class Student {
    int roll;
    string name;
    float marks;
public:
    void input() {
        cout << "\nEnter Roll No: ";
        cin >> roll;
        cout << "Enter Name: ";
        cin >> ws; // to handle spaces in name
        getline(cin, name);
        cout << "Enter Marks: ";
        cin >> marks;
    }

    void displayRow() {
        cout << left << setw(10) << roll 
             << setw(20) << name 
             << setw(10) << marks << endl;
    }

    int getRoll() { return roll; }
    float getMarks() { return marks; }
    string getName() { return name; }
};

void header() {
    cout << "\n==================== STUDENT REPORT ====================\n";
    cout << left << setw(10) << "Roll No"
         << setw(20) << "Name"
         << setw(10) << "Marks" << endl;
    cout << "---------------------------------------------------------\n";
}

int main() {
    Student s;
    fstream file;
    int choice;

    do {
        cout << "\n========== STUDENT MANAGEMENT MENU ==========\n";
        cout << "1. Add Student Record\n";
        cout << "2. Display All Students Report\n";
        cout << "3. Search Student Report by Roll No\n";
        cout << "4. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        if (choice == 1) {
            s.input();
            file.open("student.txt", ios::app | ios::binary);
            file.write((char*)&s, sizeof(s));
            file.close();
            cout << "\n✅ Record Added Successfully!\n";
        }

        else if (choice == 2) {
            file.open("student.txt", ios::in | ios::binary);
            if (!file) {
                cout << "\n❌ No records found!\n";
            } else {
                header();
                while (file.read((char*)&s, sizeof(s))) {
                    s.displayRow();
                }
                file.close();
                cout << "=========================================================\n";
            }
        }

        else if (choice == 3) {
            int searchRoll;
            bool found = false;
            cout << "\nEnter Roll No to Search: ";
            cin >> searchRoll;

            file.open("student.txt", ios::in | ios::binary);
            while (file.read((char*)&s, sizeof(s))) {
                if (s.getRoll() == searchRoll) {
                    cout << "\n********** STUDENT REPORT CARD **********\n";
                    cout << "Roll No: " << s.getRoll() << endl;
                    cout << "Name:    " << s.getName() << endl;
                    cout << "Marks:   " << s.getMarks() << endl;

                    if (s.getMarks() >= 90) cout << "Grade:   A+ (Excellent)\n";
                    else if (s.getMarks() >= 75) cout << "Grade:   A (Very Good)\n";
                    else if (s.getMarks() >= 60) cout << "Grade:   B (Good)\n";
                    else if (s.getMarks() >= 50) cout << "Grade:   C (Average)\n";
                    else cout << "Grade:   F (Fail)\n";

                    cout << "*\n";
                    found = true;
                    break;
                }
            }
            file.close();
            if (!found) cout << "\n❌ No student found with Roll No " << searchRoll << endl;
        }

        else if (choice == 4) {
            cout << "\nExiting... Thank you!\n";
        }

        else {
            cout << "\n❌ Invalid choice! Try again.\n";
        }

    } while (choice != 4);

    return 0;
}