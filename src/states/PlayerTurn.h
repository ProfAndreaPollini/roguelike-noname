//
// Created by pollini on 11/01/2022.
//

#ifndef RL_DA_ZERO_PLAYERTURN_H
#define RL_DA_ZERO_PLAYERTURN_H


#include "GameState.h"

class PlayerTurn : public GameState {
public:



    Command* handleInput() override;

    void update() override {}

    ~PlayerTurn() override = default;



};


#endif //RL_DA_ZERO_PLAYERTURN_H
