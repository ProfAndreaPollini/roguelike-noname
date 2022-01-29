//
// Created by pollini on 27/01/2022.
//

#ifndef RL_DA_ZERO_SRC_SCENES_SCENE_H
#define RL_DA_ZERO_SRC_SCENES_SCENE_H

class Scene {
public:
    virtual void handleInput() = 0;
    virtual void update() = 0;
    virtual void render() = 0;
    virtual void onLoad() {};
    virtual void onUnload() {};

    virtual ~Scene() = default;
};

#endif  // RL_DA_ZERO_SRC_SCENES_SCENE_H
