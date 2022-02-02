//
// Created by pollini on 01/02/2022.
//

#ifndef RL_DA_ZERO_SRC_LIB_SERVICES_H
#define RL_DA_ZERO_SRC_LIB_SERVICES_H

#include "Renderer.h"
#include "SceneManager.h"
#include "entt/entity/registry.hpp"
#include "entt/locator/locator.hpp"

struct Ecs {
    Ecs() : registry(entt::registry()) {}

    entt::registry registry;
};

struct Services {
    using Renderer = entt::service_locator<Renderer>;
    using SceneManager = entt::service_locator<SceneManager>;
    using Ecs = entt::service_locator<Ecs>;
};

#endif  // RL_DA_ZERO_SRC_LIB_SERVICES_H
