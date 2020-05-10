//
// Created by wildfire on 26/04/2020.
//

#ifndef CA4_CRAWLER_H
#define CA4_CRAWLER_H


class Crawler: public Bug {
public:
    Crawler(int id, const pair<int, int> &position, Direction direction, int size);
    Crawler(Crawler &crawler);
    void move() override;
    string displayLife() override;
    string displayName() override;
    string toString() override;
};


#endif //CA4_CRAWLER_H
