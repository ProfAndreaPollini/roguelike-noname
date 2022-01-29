//
// Created by pollini on 13/01/2022.
//

#ifndef RL_DA_ZERO_ITEMCONTAINER_H
#define RL_DA_ZERO_ITEMCONTAINER_H

#include <vector>
#include <numeric>

#include "Item.h"

class ItemContainer : public Item {
public:
    virtual int value() const override { return std::accumulate(std::begin(items_),
                                                                std::end(items_),
                                                                0,
                                                                [](int acc, const auto& v){
        return acc + v->value();
    }); }
    virtual int weight() const override { return 0; }

    virtual void add(Item* item)  { items_.push_back(item); }

    virtual const char* getDrawInfo() = 0;
    virtual ~ItemContainer() override = default;
private:
    std::vector<Item*> items_;
};


#endif //RL_DA_ZERO_ITEMCONTAINER_H
