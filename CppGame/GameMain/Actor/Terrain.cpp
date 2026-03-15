#include "Terrain.h"
#include "../Manager/Modules.h"

namespace GameMain::Actor {
    Terrain::Terrain(::GameMain::Core::GameCtrl& ctrl, float x, float y)
        : IGameObject(
            ctrl,
            Manager::Modules::Get().GetResource().GetImage("Asset/Image/Terrain.png"),
            ::GameMain::Draw::AnimationData{ 32, 32, 1, 1, 0.1f },
            Collision::EntityTag::Ground
        )
    {
        mPosition = { x, y };
        mCollider.SetRect(x + 16.0f, y + 16.0f, 16.0, 16.0);

        // コリジョンの登録
        Manager::Modules::Get().GetCollision().AddCollider(&mCollider);
    }

    void Terrain::OnUpdate(float deltaTime) {
        // 破棄決定時は処理停止
        if (mIsRequestToDispose) {
            return;
        }

        // 左に移動
        mPosition.x -= mSpeed * deltaTime;

        // 画面外に行ったら破棄
        if (mPosition.x < -100.0f) {
            RequestToDispose();
        }

        // コライダーも追従させる
        mCollider.SetRect(mPosition.x + 16.0f, mPosition.y + 16.0f, 16.0f, 16.0f);
    }

    void Terrain::OnDraw() {
        mSprite.Draw(mPosition.x, mPosition.y);
    }
}