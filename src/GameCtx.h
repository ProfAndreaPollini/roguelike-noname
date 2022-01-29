//
// Created by pollini on 27/01/2022.
//

#ifndef RL_DA_ZERO_SRC_GAMECTX_H
#define RL_DA_ZERO_SRC_GAMECTX_H

#include <memory>

#include "Map.h"
#include "util.h"

class GameCtx {
   public:
    static GameCtx& getInstance() {
        static GameCtx instance;
        return instance;
    }

    void map(Map* map) { map_.reset(std::move(map)); }

    // map
    auto& map() { return map_; }

    const auto& map() const { return map_; }

    // hero
    auto& hero() { return hero_; }

    const auto& hero() const { return hero_; }

    void hero(Hero* hero) { hero_.reset(std::move(hero)); }

   private:
    // singleton
    GameCtx() {
        map_.reset(new Map(800, 600));
        //        renderer_.reset(new Renderer());
        hero_.reset(new Hero());
    }

    GameCtx(const GameCtx&) = delete;
    GameCtx& operator=(const GameCtx&) = delete;

    // private members

    Rc<Map> map_;    // world map
    Rc<Hero> hero_;  // hero

    //    Rc<Game> game_; //game
    //    Ptr<Renderer> renderer_;
};

#endif  // RL_DA_ZERO_SRC_GAMECTX_H
