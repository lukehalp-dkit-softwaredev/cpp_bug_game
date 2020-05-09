//
// Created by wildfire on 26/04/2020.
//

#include "Bug.h"

Bug::Bug(int id, const pair<int, int> &position, Direction direction, int size) {
    this->id = id;
    this->position = position;
    this->direction = direction;
    this->size = size;
    this->alive = true;
    this->path = vector<pair<int, int>>();
}

Bug::Bug(Bug &bug) {
    this->id = bug.id;
    this->position = bug.position;
    this->direction = bug.direction;
    this->size = bug.size;
    this->alive = bug.alive;
    this->path = bug.path;
}

bool Bug::isWayBlocked() {
    if(this->direction == Direction::NORTH) {
        return this->position.second <= 0;
    }
    if(this->direction == Direction::EAST) {
        return this->position.first >= 9;
    }
    if(this->direction == Direction::SOUTH) {
        return this->position.second >= 9;
    }
    if(this->direction == Direction::WEST) {
        return this->position.first <= 0;
    }
    return false;
}

Bug::~Bug() {

}

int Bug::getId() const {
    return id;
}

const pair<int, int>& Bug::getPosition() const {
    return position;
}

Direction Bug::getDirection() const {
    return direction;
}

int Bug::getSize() const {
    return size;
}

bool Bug::isAlive() const {
    return alive;
}

const vector<pair<int, int>>& Bug::getPath() const {
    return path;
}


string Bug::dirString(Direction direction) {
    switch(direction) {
        case Direction::NORTH: {
            return "North";
        }
        case Direction::EAST: {
            return "East";
        }
        case Direction::SOUTH: {
            return "South";
        }
        case Direction::WEST: {
            return "West";
        }
        default: {
            return "";
        }
    }
}

Direction Bug::intToDir(int dirNum) {
    switch(dirNum) {
        case 1: {
            return Direction::NORTH;
        }
        case 2: {
            return Direction::EAST;
        }
        case 3: {
            return Direction::SOUTH;
        }
        case 4: {
            return Direction::WEST;
        }
    }
}