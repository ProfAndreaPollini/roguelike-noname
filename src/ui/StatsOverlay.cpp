//
// Created by pollini on 06/02/2022.
//

#include "StatsOverlay.h"

#include "Services.h"
#include "components/Stats.h"

void StatsOverlay::draw() const {
    DrawRectangle(position_.x, position_.y, size_.x, size_.y, bgColor_);
    raylib::DrawText(TextFormat("STATS"), position_.x + 10, position_.y + 10, 20, GREEN);
    //    const auto& events = EventStore::getInstance().events();
    auto& ecs = Services::Ecs::ref();

    const auto e = ecs.registry.view<Health, HeroTag>().front();
    const auto& health = ecs.registry.get<Health>(e);
    raylib::DrawText(TextFormat("%d/%d", health.currentHealth, health.maxHealth), position_.x + 10, position_.y + 40,
                     18, WHITE);
}