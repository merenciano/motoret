#ifndef __MOTORET_ECS_ENTITY_H__
#define __MOTORET_ECS_ENTITY_H__ 1

#include "core/common-defs.h"
#include "core/manager.h"

#include <stdint.h>

namespace motoret
{
    class Entity
    {
    public:
        Entity() { index_ = -1; }
        Entity(int32_t index) : index_(index) {}
        ~Entity() = default;

        static Entity CreateEntity(std::string name);
        static void RemoveEntity(std::string name);

        template<typename T>
        void addComponent()
        {
            MOTORET_CORE_ASSERT(index_ >= 0, "Invalid entity");
            std::shared_ptr<Component> comp;
            comp = std::make_shared<T>();
            GM.entities_[index_].components_.push_back(std::move(comp));
        }

        template<typename T>
        T& getComponent()
        {
            MOTORET_CORE_ASSERT(index_ >= 0, "Invalid entity");
            MOTORET_CORE_ASSERT(GM.entities_[index_].getComponent<T>(), "The entity doesn't have this component");
            return *(GM.entities_[index_].getComponent<T>());
            
        }
        
        /*bool hasComponents(uint64_t mask)
        {
            MOTORET_CORE_ASSERT(index_ >= 0, "Invalid entity");
            return (mask & GM.entities_[index_].componentMask()) == mask;
        }*/


    private:
        int32_t index_;
    };
}

#endif // __MOTORET_ECS_ENTITY_H__