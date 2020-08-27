//
// Created by Luke Halpenny on 09/05/2020.
//

#include "Hopper.h"

Hopper::Hopper(int id, const pair<int, int> &position, Direction direction, int size, int hopLength)
        : Bug(id, position, direction, size) {
    this->hopLength = hopLength;
}

Hopper::Hopper(Hopper &hopper) : Bug(hopper) {
    this->hopLength = hopper.hopLength;
}

int Hopper::getHopLength() const {
    return hopLength;
}

void Hopper::move() {
    if(!alive) {
        return;
    }
    if(isWayBlocked()) {
        int seed = chrono::system_clock::now().time_since_epoch().count();
        default_random_engine generator(seed);
        uniform_int_distribution<int> distribution(1,4);
        auto randDir = std::bind ( distribution, generator );
        while(isWayBlocked()) {
            int dir = randDir();
            direction = intToDir(dir);
        }
    }
    if(direction == Direction::NORTH) {
        position.second -= hopLength;
    } else if (direction == Direction::EAST) {
        position.first += hopLength;
    } else if (direction == Direction::SOUTH) {
        position.second += hopLength;
    } else if (direction == Direction::WEST) {
        position.first -= hopLength;
    }
    if(position.first < 0) {
        position.first = 0;
    }
    if(position.first > 9) {
        position.first = 9;
    }
    if(position.second < 0) {
        position.second = 0;
    }
    if(position.second > 9) {
        position.second = 9;
    }
    path.push_back(position);
}

string Hopper::toString() {
    return to_string(id) + "\t" + "Hopper"
           + "\t(" + to_string(position.first) + "," + to_string(position.second) + ")\t"
           + to_string(size) + "\t\t" + dirString(direction) + "\t" + (alive ? "Alive" : "Dead")
           + "\t" + to_string(hopLength);
}

string Hopper::displayLife() {
    string life = to_string(id) + "\tHopper\t";
    for(pair<int, int> position : path) {
        life += "(" + to_string(position.first) + "," + to_string(position.second) + "),";
    }
    life += (alive ? "Alive" : "Dead");
    return life;
}

string Hopper::displayName() {
    return to_string(id) + " Hopper";
}

string Hopper::getGridMarker() {
    return alive ? "H" : "X";
}