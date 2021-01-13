#include "entity-chunk.h"

#include "core/manager.h"
#include "core/scene-graph.h"
#include "ecs/components/drawable.h"
#include "ecs/components/ltransform.h"
#include "ecs/components/gtransform.h"
#include "ecs/components/fall-speed.h"
#include "ecs/components/infinite-falling-limits.h"

namespace leep
{
/*
 *      FALLING CUBE ENTITY CHUNK
 */
    FallingCubeEntities::FallingCubeEntities() : EntityChunk(s_type)
    {
        comps_.emplace_back(new LTransform[kEntitiesPerChunk]());
        comps_.emplace_back(new Drawable[kEntitiesPerChunk]());
        comps_.emplace_back(new FallSpeed[kEntitiesPerChunk]());
        comps_.emplace_back(new InfiniteFallingLimits[kEntitiesPerChunk]());
        comps_.emplace_back(new GTransform[kEntitiesPerChunk]());
    }

    FallingCubeEntities::~FallingCubeEntities()
    {
        delete[] static_cast<LTransform*>(comps_[0]);
        delete[] static_cast<Drawable*>(comps_[1]);
        delete[] static_cast<FallSpeed*>(comps_[2]);
        delete[] static_cast<InfiniteFallingLimits*>(comps_[3]);
        delete[] static_cast<GTransform*>(comps_[4]);
    }

    void FallingCubeEntities::relocateLast(EntityChunk *a, uint32_t i)
    {
        LEEP_ASSERT(a && i < kEntitiesPerChunk, "Wrong parameters");
        FallingCubeEntities *chunk = static_cast<FallingCubeEntities*>(a);
        // Update pointers in the scene graph
        GM.scene_graph().changeTransform(static_cast<LTransform*>(&(comps_[0][last_ - 1])),
                                            static_cast<LTransform*>(&(chunk->comps_[0][i])),
                                            static_cast<GTransform*>(&(chunk->comps_[4][i])));
        // Do the relocation
        static_cast<LTransform*>(chunk->comps_[0])[i] = static_cast<LTransform*>(comps_[0])[last_ - 1];
        static_cast<Drawable*>(chunk->comps_[1])[i] = static_cast<Drawable*>(comps_[1])[last_ - 1];
        static_cast<FallSpeed*>(chunk->comps_[2])[i] = static_cast<FallSpeed*>(comps_[2])[last_ - 1];
        static_cast<InfiniteFallingLimits*>(chunk->comps_[3])[i] = static_cast<InfiniteFallingLimits*>(comps_[3])[last_ - 1];
        static_cast<GTransform*>(chunk->comps_[4])[i] = static_cast<GTransform*>(comps_[4])[last_ - 1];
#ifdef LEEP_DEBUG
        static_cast<LTransform*>(comps_[0])[last_ - 1] = LTransform();
        static_cast<Drawable*>(comps_[1])[last_ - 1] = Drawable();
        static_cast<FallSpeed*>(comps_[2])[last_ - 1] = FallSpeed();
        static_cast<InfiniteFallingLimits*>(comps_[3])[last_ - 1] = InfiniteFallingLimits();
        static_cast<GTransform*>(comps_[4])[last_ - 1] = GTransform();
#endif

    }

/*
 *      RENDERABLE ENTITY CHUNK
 */
    RenderableEC::RenderableEC() : EntityChunk(s_type)
    {
        comps_.emplace_back(new LTransform[kEntitiesPerChunk]());
        comps_.emplace_back(new GTransform[kEntitiesPerChunk]());
        comps_.emplace_back(new Drawable[kEntitiesPerChunk]());
    }

    RenderableEC::~RenderableEC()
    {
        delete[] static_cast<LTransform*>(comps_[0]);
        delete[] static_cast<GTransform*>(comps_[1]);
        delete[] static_cast<Drawable*>(comps_[2]);
    }

    void RenderableEC::relocateLast(EntityChunk *a, uint32_t i)
    {
        LEEP_ASSERT(a && i < kEntitiesPerChunk, "Wrong parameters");
        RenderableEC *chunk = static_cast<RenderableEC*>(a);
        // Update pointers in the scene graph
        GM.scene_graph().changeTransform(static_cast<LTransform*>(&(comps_[0][last_ - 1])),
                                         static_cast<LTransform*>(&(chunk->comps_[0][i])),
                                         static_cast<GTransform*>(&(chunk->comps_[1][i])));
        // Do the relocation
        static_cast<LTransform*>(chunk->comps_[0])[i] = static_cast<LTransform*>(comps_[0])[last_ - 1];
        static_cast<GTransform*>(chunk->comps_[1])[i] = static_cast<GTransform*>(comps_[1])[last_ - 1];
        static_cast<Drawable*>(chunk->comps_[2])[i] = static_cast<Drawable*>(comps_[2])[last_ - 1];
#ifdef LEEP_DEBUG
        static_cast<LTransform*>(comps_[0])[last_ - 1] = LTransform();
        static_cast<GTransform*>(comps_[1])[last_ - 1] = GTransform();
        static_cast<Drawable*>(comps_[2])[last_ - 1] = Drawable();
#endif
    }
}