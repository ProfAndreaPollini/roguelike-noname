//
// Created by pollini on 13/02/2022.
//

#ifndef RL_DA_ZERO_SRC_COMMANDS_ATTACKCOMMAND_H
#define RL_DA_ZERO_SRC_COMMANDS_ATTACKCOMMAND_H

#include "Command.h"

class AttackCommand : public Command {
   public:
    AttackCommand(entt::entity attacker, entt::entity target);

    virtual ~AttackCommand() = default;

    void execute() override;

    entt::entity attacker;
    entt::entity target;
    bool isHeroAttack = false;
};

#endif  // RL_DA_ZERO_SRC_COMMANDS_ATTACKCOMMAND_H
