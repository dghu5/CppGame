#pragma once
#include <vector>
#include "../Collision/BoxCollider.h"

namespace GameMain::Manager {
    class CollisionManager {
    public:
        /// <summary>
        /// コリジョン追加
        /// </summary>
        void AddCollider(const GameMain::Collision::BoxCollider* collider);

        /// <summary>
        /// リセット
        /// </summary>
        void Clear();

        /// <summary>
        /// デバッグ描画実行
        /// </summary>
        void DrawDebugAll() const;

    private:
        std::vector<const GameMain::Collision::BoxCollider*> mColliders;
    };
}