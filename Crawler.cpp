//
// Created by wildfire on 26/04/2020.
//

#include "Crawler.h"

Crawler::Crawler(int id, const pair<int, int> &position, Direction direction, int size)
        : Bug(id, position, direction, size) {

}

Crawler::Crawler(Crawler &crawler) : Bug(crawler) {

}

void Crawler::move() {
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
        position.second -= 1;
    } else if (direction == Direction::EAST) {
        position.first += 1;
    } else if (direction == Direction::SOUTH) {
        position.second += 1;
    } else if (direction == Direction::WEST) {
        position.first -= 1;
    }
    path.push_back(position);
}

string Crawler::toString() {
    return to_string(id) + "\t" + "Crawler"
           + "\t(" + to_string(position.first) + "," + to_string(position.second) + ")\t"
           + to_string(size) + "\t\t" + dirString(direction) + "\t" + (alive ? "Alive" : "Dead");
}
