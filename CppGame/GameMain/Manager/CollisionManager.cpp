#include "CollisionManager.h"

namespace GameMain::Manager {

    void CollisionManager::AddCollider(const GameMain::Collision::BoxCollider* collider) {
        mColliders.push_back(collider);
    }

    void CollisionManager::Clear() {
        mColliders.clear();
    }

    void CollisionManager::DrawDebugAll() const {
#ifdef ENABLE_COLLISION_DEBUG
        for (const auto* col : mColliders) {
            if (col) col->DrawDebug();
        }
#endif
    }
}