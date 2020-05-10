//
// Created by wildfire on 09/05/2020.
//

#ifndef CA4_HOPPER_H
#define CA4_HOPPER_H


class Hopper: public Bug {
private:
    int hopLength;
public:
    Hopper(int id, const pair<int, int> &position, Direction direction, int size, int hopLength);
    Hopper(Hopper &hopper);
    int getHopLength() const;
    void move() override;
    string displayLife() override;
    string displayName() override;
    string toString() override;
};


#endif //CA4_HOPPER_H
