#pragma once
#include <vector>
#include <memory>
#include <random>
#include "../Actor/IGameObject.h"

// 前方宣言
namespace GameMain::Actor {
    class PlayerObj;
}

namespace GameMain::Core {

    class GameCtrl {
    public:
        GameCtrl();
        ~GameCtrl() = default;

        /// <summary>
        /// 更新処理
        /// </summary>
        void Update(float deltaTime);

        /// <summary>
        /// 描画処理
        /// </summary>
        void Draw() const;

        /// <summary>
        /// ゲームオーバー管理
        /// </summary>
        bool IsGameOver() const { return mIsGameOver; }

        /// <summary>
        /// スコア取得
        /// </summary>
        int GetScore() const { return mScore; }

        /// <summary>
        /// スコア加算
        /// </summary>
        void AddScore(int amount);

        /// <summary>
        /// ゲームオーバー
        /// </summary>
        void SetIsGameOver();

    private:
        void UpdateSpawnLogic(float deltaTime);

        int mScore;
        bool mIsGameOver;

        std::vector<std::unique_ptr<Actor::IGameObject>> mGameObjects;
        Actor::PlayerObj* mPlayer;

        // 生成用管理データ
        float mNextSpawnX = 640.0f;
        int mRemainingTiles = 0;
        bool mIsGeneratingGap = false;
        std::mt19937 mRandomEngine{ std::random_device{}() };
    };
}