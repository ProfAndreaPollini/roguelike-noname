//
// Created by pollini on 13/02/2022.
//

#include "AttackEvent.h"

#include "fmt/format.h"

std::string AttackEvent::str() const {
    auto ret = fmt::format("{} is attacking {}", static_cast<int>(attacker), static_cast<int>(target));
    return ret;
}
