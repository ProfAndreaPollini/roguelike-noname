//
// Created by pollini on 27/01/2022.
//

#ifndef RL_DA_ZERO_SRC_UTILS_UTIL_H
#define RL_DA_ZERO_SRC_UTILS_UTIL_H

#include <memory>

template<typename T>
using Rc = std::shared_ptr<T>;

template<typename T>
using Ptr = std::unique_ptr<T>;

template<typename T>
using RcWeak = std::weak_ptr<T>;

#endif  // RL_DA_ZERO_SRC_UTILS_UTIL_H
