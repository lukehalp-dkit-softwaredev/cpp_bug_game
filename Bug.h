//
// Created by Luke Halpenny on 26/04/2020.
//

#ifndef CA4_BUG_H
#define CA4_BUG_H

#include <vector>
#include <random>
#include <functional>
#include <chrono>

using namespace std;

enum class Direction {
    NORTH,
    EAST,
    SOUTH,
    WEST
};

class Bug {
protected:
    int id;
    pair<int, int> position;
    Direction direction;
    int size;
    bool alive;
    vector<pair<int, int>> path;
public:
    Bug(int id, const pair<int, int> &position, Direction direction, int size);
    Bug(Bug &bug);
    int getId() const;
    const pair<int, int>& getPosition() const;
    Direction getDirection() const;
    int getSize() const;
    bool isAlive() const;
    const vector<pair<int, int>>& getPath() const;
    virtual void move() = 0;
    virtual string toString() = 0;
    string dirString(Direction direction);
    Direction intToDir(int dirNum);
    bool isWayBlocked();

    virtual ~Bug();
};


#endif //CA4_BUG_H
