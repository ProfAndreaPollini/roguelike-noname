//
// Created by pollini on 28/01/2022.
//

#include "LogOverlay.h"

#include "EventStore.h"
#include "Services.h"

void LogOverlay::draw() const {
    DrawRectangle(position_.x, position_.y, size_.x, size_.y, bgColor_);
    raylib::DrawText(TextFormat("LOG"), position_.x + 10, position_.y + 10, 20,
                     GREEN);
    //    const auto& events = EventStore::getInstance().events();
    auto& ecs = Services::Ecs::ref();

    const auto& events = ecs.registry.ctx().at<EventStore>().events();
    int offset = 10;
    for (unsigned i = events.size(); i-- > 0;) {
        raylib::DrawText(TextFormat(events[i]->str().c_str()), position_.x + 10,
                         position_.y + 20 + offset, 16, WHITE);
        offset += 20;
    }
}
