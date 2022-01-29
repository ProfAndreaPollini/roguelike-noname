//
// Created by pollini on 10/01/2022.
//

#ifndef RL_DA_ZERO_ENTITY_H
#define RL_DA_ZERO_ENTITY_H

class Item;

class Entity {
public:
    Entity(int x, int y) : x_(x), y_(y) {}
    virtual ~Entity() = default;
    int x() const { return x_; }
    int y() const { return y_; }

    void move(int dx, int dy) {
        x_ += dx;
        y_ += dy;
    }

    void setX(int x) { x_ = x; }
    void setY(int y) { y_ = y; }

    void set(int x, int y) {
        x_ = x;
        y_ = y;
    }


    virtual void pickUp(Item *item) {};
private:
    int x_;
    int y_;
};

#endif //RL_DA_ZERO_ENTITY_H
