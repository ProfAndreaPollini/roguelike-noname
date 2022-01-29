//
// Created by pollini on 13/01/2022.
//

#ifndef RL_DA_ZERO_ITEM_H
#define RL_DA_ZERO_ITEM_H

#include "MapPosition.h"
class Item {
public:
 using ItemPtr = std::shared_ptr<Item>;
    Item(const char* name, int value, int weight): name_(name), value_(value), weight_(weight){}

    const char* name() const { return name_; }
    virtual int value() const { return value_; }
    virtual int weight() const { return weight_; }

    virtual const char* getDrawInfo() = 0;
    virtual ~Item() {}

private:
    const char* name_;
    int value_;
    int weight_;

};

#endif //RL_DA_ZERO_ITEM_H
