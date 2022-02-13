//
// Created by pollini on 02/02/2022.
//

#ifndef RL_DA_ZERO_SRC_ENTITY_COMPONENTS_VIEWPORT_H
#define RL_DA_ZERO_SRC_ENTITY_COMPONENTS_VIEWPORT_H

struct Viewport {
    float x;
    float y;
    float width;
    float height;

    bool contains(float x, float y) const {
        auto check = x >= this->x && x <= this->x + this->width && y >= this->y && y <= this->y + this->height;
        //        if (!check) {
        //            spdlog::info("Viewport not contains {} {} || {} {} {} {}", x, y, this->x, this->y, this->x +
        //            this->width,
        //                         this->height);
        //        }
        return check;
    }
};

#endif  // RL_DA_ZERO_SRC_ENTITY_COMPONENTS_VIEWPORT_H
