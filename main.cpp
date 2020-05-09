//
// Created by Luke Halpenny on 26/04/2020.
//

#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include "Bug.cpp"
#include "Crawler.cpp"
#include "Hopper.cpp"


using namespace std;

void menu();
void printMenu();

void initializeBoard();
void load();
int parseLine(const string& str);
void displayBugs();
string dirString(Direction direction);
void findBug();
void tapBoard();
void displayLife();
void displayCells();

//void save();

vector<Bug*> bugs;
int bugId = 1;

int main() {
    menu();
//    save();
    cout << "Goodbye." << endl;
    return 0;
}

void menu() {
    bool running = true;
    while (running) {
        string ans;
        int num;
        printMenu();
        cout << ">> ";
        getline(cin, ans);
        try {
            num = stoi(ans);
            switch(num) {
                case 1: {
                    initializeBoard();
                    break;
                }
                case 2: {
                    displayBugs();
                    break;
                }
                case 3: {
                    findBug();
                    break;
                }
                case 4: {
                    tapBoard();
                    break;
                }
                case 5: {
                    displayLife();
                    break;
                }
                case 6: {
                    displayCells();
                    break;
                }
                case 0: {
                    running = false;
                    break;
                }
                default: {
                    cout << "Invalid option" << endl;
                }
            }
        } catch (invalid_argument &e) {
            cout << "Invalid option" << endl;
        }
    }
}

void printMenu() {
    cout << "BUGS: " << endl;
    cout << "1. Initialize Bugs" << endl;
    cout << "2. Display Bugs" << endl;
    cout << "3. Find Bug" << endl;
    cout << "4. Tap Board" << endl;
    cout << "5. Display Bugs Life" << endl;
    cout << "6. Display Cells" << endl;
    cout << "0. Quit" << endl;
}

//void addStudent() {
//    cout << "Student Title: ";
//    string title;
//    getline(cin, title);
//    cout << "Student Name: ";
//    string name;
//    getline(cin, name);
//    cout << "Student Course: ";
//    string course;
//    getline(cin, course);
//    string grade;
//    int grades[4];
//    for(int i=0;i<4;i++) {
//        grades[i] = -1;
//        while(grades[i] == -1) {
//            cout << "Student Grade " << i+1 << ": ";
//            getline(cin, grade);
//            try {
//                grades[i] = stoi(grade);
//                if(grades[i] < 0 || grades[i] > 100) {
//                    cout << "Invalid grade" << endl;
//                    grades[i] = -1;
//                }
//            } catch (invalid_argument &e) {
//                cout << "Invalid grade" << endl;
//            }
//        }
//    }
//    Student student(studentId, title, name, grades, course);
//    // Check for duplicate
//    if(find(students.begin(), students.end(), student) != students.end()) {
//        cout << "Student already in database." << endl;
//        return;
//    }
//    students.push_back(student);
//    cout << "Added student" << endl;
//}
//
//void showStudentsCourse() {
//    cout << "Course Name: ";
//    string course;
//    getline(cin, course);
//    cout << "Sort by:\n1. Student Name\n2. Student Grade\n>> ";
//    string sort;
//    int num;
//    getline(cin, sort);
//    try {
//        num = stoi(sort);
//        if(num < 1 || num > 2) {
//            cout << "Invalid option, sorting by Name" << endl;
//            num = 1;
//        }
//    } catch (invalid_argument &e) {
//        cout << "Invalid option, sorting by Name" << endl;
//        num = 1;
//    }
//    if(num == 1) {
//        showStudentsCourseByName(course);
//    } else {
//        showStudentsCourseByGrade(course);
//    }
//}
//
///*
// * Sorting functions for students.
// */
//bool sortById(Student &a, Student &b) {
//    return a.getId() < b.getId();
//}
//
//bool sortByName(Student &a, Student &b) {
//    return a.getName() < b.getName();
//}
//
//bool sortByGrade(Student &a, Student &b) {
//    return a.getAverage() < b.getAverage();
//}
//
//void showStudentsCourseByName(string &course) {
//    sort(students.begin(), students.end(), sortByName);
//    for(const Student& student: students) {
//        if(student.getCourse() == course) {
//            cout << student << endl;
//        }
//    }
//}
//
//void showStudentsCourseByGrade(string &course) {
//    sort(students.begin(), students.end(), sortByGrade);
//    for(const Student& student: students) {
//        if(student.getCourse() == course) {
//            cout << student << endl;
//        }
//    }
//}
//
//void findStudent() {
//    cout << "Student ID: ";
//    string id;
//    int num;
//    getline(cin, id);
//    try {
//        num = stoi(id);
//        sort(students.begin(), students.end(), sortById);
//        for(const Student& student: students) {
//            if(student.getId() == num) {
//                cout << student << endl;
//            }
//        }
//    } catch (invalid_argument &e) {
//        cout << "Invalid ID" << endl;
//    }
//}
//
//void showFailingStudents() {
//    sort(students.begin(), students.end(), sortById);
//    for(Student &student: students) {
//        if(student.getAverage() < 40) {
//            cout << student << endl;
//        }
//    }
//}

void initializeBoard() {
    load();
    cout << "Loaded bugs." << endl;
}

/*
 * Loads bugs from file bugs.txt into the program.
 */
void load() {
    string line;
    ifstream fin("bugs.txt");
    int max = 0;
    int id = 0;
    if (fin.good()) {
        while (getline(fin, line)) {
            id = parseLine(line);
            if(id > max) {
                max = id; // keep track of used ids
            }
        }
        fin.close();
        bugId = id + 1;
    }
    else {
        cout << "[Error] Unable to load bugs." << endl;
    }
}

/*
 * Parses and individual line of students.txt .
 */
int parseLine(const string& str) {
    try {
        stringstream input(str);
        string typeStr;
        getline(input, typeStr, ';');
        string idStr;
        getline(input, idStr, ';');
        int id = stoi(idStr);
        string xStr;
        getline(input, xStr, ';');
        int x = stoi(xStr);
        string yStr;
        getline(input, yStr, ';');
        int y = stoi(yStr);
        pair<int, int> position(x, y);
        string dirStr;
        getline(input, dirStr, ';');
        int dirInt = stoi(dirStr);
        Direction dir;
        switch(dirInt) {
            case 1: {
                dir = Direction::NORTH;
                break;
            }
            case 2: {
                dir = Direction::EAST;
                break;
            }
            case 3: {
                dir = Direction::SOUTH;
                break;
            }
            case 4: {
                dir = Direction::WEST;
                break;
            }
            default: {
                throw invalid_argument("Invalid direction '"+to_string(dirInt)+"'.");
            }
        }
        string sizeStr;
        getline(input, sizeStr, ';');
        int size = stoi(sizeStr);
        if(typeStr == "H") {
            string hopStr;
            getline(input, hopStr, ';');
            int hopLength = stoi(hopStr);
            Hopper* hopper = new Hopper(id, position, dir, size, hopLength);
            bugs.push_back(hopper);
        } else if (typeStr == "C") {
            Crawler* crawler = new Crawler(id, position, dir, size);
            bugs.push_back(crawler);
        }
        return id;
    }
    catch (std::invalid_argument const& e)
    {
        cout << "[Error] Ignoring bad bug in file: " << str << endl;
    }
    catch (std::out_of_range const& e)
    {
        cout << "[Error] Ignoring bad bug in file: " << str << endl;
    }
    return 0;
}

void displayBugs() {
    cout <<"ID\tType\tPos\t\tSize\tDir\t\tStatus\tHop" << endl;
    for(Bug* bug: bugs) {
        cout << bug->toString() << endl;
    }
}

void findBug() {
    cout << "Bug ID: ";
    string ans;
    int num;
    getline(cin, ans);
    try {
        num = stoi(ans);
        for(Bug* bug : bugs) {
            if(bug->getId() == num) {
                cout << "ID\tType\tPos\t\tSize\tDir\t\tStatus\tHop" << endl;
                cout << bug->toString() << endl;
            }
        }
        cout << "Bug not found." << endl;
    } catch (invalid_argument &e) {
        cout << "Invalid option" << endl;
    }
}

void tapBoard() {
    for(Bug* bug: bugs) {
        bug->move();
    }
}

void displayLife() {

}

void displayCells() {

}

///*
// * Saves students to the file students.txt.
// */
//void save() {
//    sort(students.begin(), students.end(), sortById); // sort by id before saving
//    ofstream fout("students.txt");
//    if (fout.good()) {
//        for(Student student : students) {
//            fout << student.save();
//        }
//        fout.close();
//    } else {
//        cout << "[Error] Unable to save students to file" << endl;
//    }
//}