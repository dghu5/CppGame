#pragma once
#include "CollisionDef.h"

namespace GameMain::Collision {
    class BoxCollider {
    public:
        BoxCollider(EntityTag tag);
        ~BoxCollider() = default;

        /// <summary>
        /// 矩形の設定
        /// </summary>
        void SetRect(float centerX, float centerY, float halfW, float halfH);

        /// <summary>
        /// 判定
        /// </summary>
        HitResult CheckCollision(const BoxCollider& other) const;

        EntityTag GetTag() const { return mTag; }

#ifdef ENABLE_COLLISION_DEBUG
        void DrawDebug() const;
#endif

    private:
        float mLeft = 0.0f;
        float mRight = 0.0f;
        float mTop = 0.0f;
        float mBottom = 0.0f;
        EntityTag mTag;
    };
}