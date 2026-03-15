#include "GameCtrl.h"
#include "../Manager/Modules.h"
#include "../Actor/Terrain.h"
#include "../Actor/PlayerObj.h"
#include "../Collision/CollisionDef.h"
#include "DxLib.h"

namespace GameMain::Core {

    GameCtrl::GameCtrl() :
        mScore(0), 
        mIsGameOver(false)
    {
        mPlayer = new ::GameMain::Actor::PlayerObj(*this);

        // 初期配置
        float startX = 0.0f;
        float startY = 450.0f;
        float tileWidth = 32.0f;
        int screenWidth = 640;

        // 画面幅を埋めるまでTerrainを生成
        for (float x = startX; x < screenWidth; x += tileWidth) {
            mGameObjects.push_back(std::make_unique<GameMain::Actor::Terrain>(
                *this, x, startY
            ));
        }

        // 生成用管理データ
        float mNextSpawnX = 640.0f;
        int mRemainingTiles = 0;
        bool mIsGeneratingGap = false;
        std::mt19937 mRandomEngine{ std::random_device{}() };
    }

    void GameCtrl::Update(float deltaTime)
    {
        // ゲームオーバー後は更新無し
        if (mIsGameOver) {
            return;
        }

        UpdateSpawnLogic(deltaTime);

        mPlayer->OnUpdate(deltaTime);

        //  全オブジェクトの更新
        for (auto& obj : mGameObjects) {
            obj->OnUpdate(deltaTime);
        }

        // 衝突判定
        bool isGroundHit = false;
        float landingY = 0.0f;
        for (auto& obj : mGameObjects) {
            if (!isGroundHit && obj->GetCollider().GetTag() == Collision::EntityTag::Ground) {
                auto hitData = mPlayer->GetCollider().CheckCollision(obj->GetCollider());
                if (hitData.isHit && hitData.hitSide == GameMain::Collision::HitSide::Bottom) {
                    isGroundHit = true;
                    landingY = obj->GetPosition().y - 32.0f; // 足場の高さ
                    break;
                }
            }
        }

        // プレイヤーの接地判定
        mPlayer->SetGrounded(isGroundHit, landingY);

        // 不要なオブジェクトの削除 (RequestToDispose)
        mGameObjects.erase(
            std::remove_if(mGameObjects.begin(), mGameObjects.end(),
                [](const std::unique_ptr<Actor::IGameObject>& obj) {
            return obj->IsRequestToDispose();
        }),
            mGameObjects.end()
        );

        // 時間経過スコア　ざっくり目の加算
        mScore += (int)(deltaTime * 1000);
    }

    void GameCtrl::UpdateSpawnLogic(float deltaTime) {
        while (mNextSpawnX < 640.0f + 32.0f) {
            if (mRemainingTiles <= 0) {
                mIsGeneratingGap = !mIsGeneratingGap;
                std::uniform_int_distribution<int> dist(
                    mIsGeneratingGap ? 2 : 5,
                    mIsGeneratingGap ? 4 : 10
                );
                mRemainingTiles = dist(mRandomEngine);
            }

            if (!mIsGeneratingGap) {
                mGameObjects.push_back(std::make_unique<GameMain::Actor::Terrain>(
                    *this, mNextSpawnX, 450.0f
                ));
            }
            mNextSpawnX += 32.0f;
            mRemainingTiles--;
        }
        // 足場全体を左に流すため、生成位置も徐々に移動させる
        mNextSpawnX -= 200.0f * deltaTime;
    }

    void GameCtrl::Draw() const
    {
        auto& resourceManager = Manager::Modules::Get().GetResource();

        // 背景描画(今回は1枚絵にしておく)
        int imageHandle = resourceManager.GetImage("Asset/Image/Bg.png");
        if (imageHandle != -1) {
            DrawGraph(0, 0, imageHandle, TRUE);
        }

        mPlayer->OnDraw();

        // オブジェクト描画
        for (auto& obj : mGameObjects) {
            obj->OnDraw();
        }

        // スコア表示
        int fontHandle24 = resourceManager.GetFont("GameFont24");
        if (fontHandle24 != -1) {
            DrawFormatStringToHandle(10, 10, GetColor(255, 255, 255), fontHandle24, "Score: %d", mScore);
        }
    }

    void GameCtrl::AddScore(int amount) {
        mScore += amount;
    }

    void GameCtrl::SetIsGameOver()
    {
        mIsGameOver = true;
    }
}