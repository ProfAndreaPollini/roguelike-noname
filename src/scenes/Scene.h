//
// Created by pollini on 27/01/2022.
//

#ifndef RL_DA_ZERO_SRC_SCENES_SCENE_H
#define RL_DA_ZERO_SRC_SCENES_SCENE_H

#include "CommandQueue.h"
#include "util.h"

class Scene {
   public:
    Scene();
    virtual void handleInput() = 0;
    virtual void update() = 0;
    virtual void render() = 0;
    virtual void onLoad(){};
    virtual void onUnload(){};

    virtual ~Scene() = default;

    // push a command to the command queue
    void pushCommand(Rc<Command> command);

   private:
    CommandQueue& commandQueue_;
};

#endif  // RL_DA_ZERO_SRC_SCENES_SCENE_H
