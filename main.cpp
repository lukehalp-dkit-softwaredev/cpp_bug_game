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
void save();

vector<Bug*> bugs;
int bugId = 1;

int main() {
    menu();
    save();
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
    for(int i=0;i<bugs.size();i++) {
        for(int j=i;j<bugs.size();j++) {
            if(bugs[i]->getPosition() == bugs[j]->getPosition()) {
                if(bugs[i]->getSize() > bugs[j]->getSize() && bugs[i]->isAlive() && bugs[j]->isAlive()) {
                    bugs[i]->eat(*bugs[j]);
                } else if(bugs[j]->getSize() > bugs[i]->getSize() && bugs[i]->isAlive() && bugs[j]->isAlive()) {
                    bugs[j]->eat(*bugs[i]);
                }
            }
        }
    }
}

void displayLife() {
    cout <<"ID\tType\tPath" << endl;
    for(Bug* bug: bugs) {
        cout << bug->displayLife() << endl;
    }
}

void displayCells() {
    // This is bad code, too many loops. It works tho!
    for(int x=0;x<=9;x++) {
        for(int y=0;y<=9;y++) {
            cout << "(" << x << "," << y << "):\t";
            for(Bug* bug : bugs) {
                if(bug->getPosition().first == x && bug->getPosition().second == y) {
                    cout << bug->displayName() << ",\t";
                }
            }
            cout << endl;
        }
    }
}

/*
 * Saves bugs life to the file bugslife.txt.
 */
void save() {
    ofstream fout("bugslife.txt");
    if (fout.good()) {
        fout <<"ID\tType\tPath" << endl;
        for(Bug* bug: bugs) {
            fout << bug->displayLife() << endl;
        }
        fout.close();
    } else {
        cout << "[Error] Unable to save bugs to file" << endl;
    }
}