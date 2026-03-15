#pragma once

// デバッグビルド時のみ有効にする設定
#ifdef _DEBUG
#define ENABLE_COLLISION_DEBUG
#endif

namespace GameMain::Collision {
    enum class EntityTag {
        None,
        Player,
        Item,
        Obstacle,
        Ground
    };

    enum class HitSide {
        None,
        Top,
        Bottom,
        Left,
        Right
    };

    struct HitResult {
        bool isHit = false;
        EntityTag hitTag = EntityTag::None;
        HitSide hitSide = HitSide::None;
        float overlap = 0.0f;
    };
}