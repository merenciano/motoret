// Lucas Merenciano Martinez  <lucasmermar@gmail.com>

#ifndef __LEEP_CORE_MEMORY_ENTITY_CONTAINER_H__
#define __LEEP_CORE_MEMORY_ENTITY_CONTAINER_H__ 1

#include "core/memory/entity-chunk.h"

#include <string>
#include <deque>
#include <unordered_map>

namespace leep
{
    template <typename T>
    struct EntityContainer
    {
        EntityContainer() { chunks_.emplace_back(); chunks_.back().index_ = 0; }
        std::deque<T> chunks_;
        std::unordered_map<std::string, uint32_t> dictionary_;
        std::unordered_map<uint32_t, std::string> reverse_dictionary_;
    };
}
#endif // __LEEP_CORE_MEMORY_ENTITY_CONTAINER_H__