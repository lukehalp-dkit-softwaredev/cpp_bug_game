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
    return false;
}

Bug::~Bug() {

}
