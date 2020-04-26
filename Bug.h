//
// Created by Luke Halpenny on 26/04/2020.
//

#ifndef CA4_BUG_H
#define CA4_BUG_H

#include <vector>

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
    virtual void move() = 0;
    bool isWayBlocked();
    virtual ~Bug();
};


#endif //CA4_BUG_H
