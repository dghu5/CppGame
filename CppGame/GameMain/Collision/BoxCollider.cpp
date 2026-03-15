#include <algorithm>
#include "BoxCollider.h"
#include "DxLib.h"

namespace GameMain::Collision {

    BoxCollider::BoxCollider(EntityTag tag)
        : mTag(tag)
    {}

    void BoxCollider::SetRect(float centerX, float centerY, float halfW, float halfH) {
        mLeft = centerX - halfW;
        mRight = centerX + halfW;
        mTop = centerY - halfH;
        mBottom = centerY + halfH;
    }

    HitResult BoxCollider::CheckCollision(const BoxCollider& other) const {
        HitResult result;

        // @memo この辺りの判定は調べながら作りました

        // AABBの重なりチェック
        if (!(mLeft < other.mRight && mRight > other.mLeft &&
            mTop < other.mBottom && mBottom > other.mTop)) {
            return result;
        }

        result.isHit = true;
        result.hitTag = other.mTag;

        // 各軸の重なり量を計算
        float overlapX = std::min<float>(mRight, other.mRight) - std::max<float>(mLeft, other.mLeft);
        float overlapY = std::min<float>(mBottom, other.mBottom) - std::max<float>(mTop, other.mTop);

        // 中心座標による衝突面判定
        float centerX = (mLeft + mRight) / 2.0f;
        float centerY = (mTop + mBottom) / 2.0f;
        float otherCenterX = (other.mLeft + other.mRight) / 2.0f;
        float otherCenterY = (other.mTop + other.mBottom) / 2.0f;

        float deltaX = centerX - otherCenterX;
        float deltaY = centerY - otherCenterY;

        if (overlapX < overlapY) {
            // 横方向の衝突
            result.hitSide = (deltaX > 0) ? HitSide::Left : HitSide::Right;
            result.overlap = overlapX;
        }
        else {
            // 縦方向の衝突
            result.hitSide = (deltaY > 0) ? HitSide::Top : HitSide::Bottom;
            result.overlap = overlapY;
        }

        return result;
    }

#ifdef ENABLE_COLLISION_DEBUG && true
    void BoxCollider::DrawDebug() const {
        unsigned int color = GetColor(0, 255, 0);
        if (mTag == EntityTag::Player)   color = GetColor(255, 255, 0);
        if (mTag == EntityTag::Obstacle) color = GetColor(255, 0, 0);
        if (mTag == EntityTag::Ground)   color = GetColor(0, 0, 255);

        DrawBox(static_cast<int>(mLeft), static_cast<int>(mTop),
            static_cast<int>(mRight), static_cast<int>(mBottom), color, FALSE);
    }
#endif
}