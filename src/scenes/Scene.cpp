//
// Created by pollini on 27/01/2022.
//

#include "Scene.h"

#include "Services.h"

Scene::Scene() : commandQueue_{Services::Ecs::ref().registry.ctx().at<CommandQueue>()} {}
void Scene::pushCommand(Rc<Command> command) { commandQueue_.push(command); }
