#include "PlayerObj.h"
#include "../Manager/Modules.h"
#include "../Manager/ResourceManager.h"
#include "../Core/GameCtrl.h"
#include "DxLib.h"
#include <algorithm>

namespace GameMain::Actor {
    PlayerObj::PlayerObj(::GameMain::Core::GameCtrl& ctrl)
        : IGameObject(
            ctrl,
            Manager::Modules::Get().GetResource().GetImage("Asset/Image/Player_Run.png"),
            ::GameMain::Draw::AnimationData{ 32, 32, 4, 4, 0.1f },
            Collision::EntityTag::Player
        )
    {
        mPosition.x = 300.0f;
        mPosition.y = 300.0f;

        // コリジョンの登録
        Manager::Modules::Get().GetCollision().AddCollider(&mCollider);

        // コライダーの初期サイズ設定
        mCollider.SetRect(mPosition.x + 16.0f, mPosition.y + 16.0f, 16.0f, 16.0f);
    }

    void PlayerObj::OnUpdate(float deltaTime) {
        auto& mods = Manager::Modules::Get();
        if (mods.GetInput().IsKeyDown(KEY_INPUT_LEFT)) {
            mPosition.x -= mSpeed * deltaTime;
        }

        if (mods.GetInput().IsKeyDown(KEY_INPUT_RIGHT)) {
            mPosition.x += mSpeed * deltaTime;
        }

        // 移動範囲制限
        mPosition.x = std::clamp(mPosition.x, 0.0f, 608.0f);

        // 重力
        if (!mIsGrounded) {
            mVelocityY += Gravity * deltaTime;
        }

        if (mIsGrounded && mods.GetInput().IsKeyDown(KEY_INPUT_SPACE)) {
            mVelocityY = JumpPower;
            mIsGrounded = false;

            int seHandle = mods.GetResource().GetSound("Asset/Sound/Se_Jump.ogg");
            PlaySoundMem(seHandle, DX_PLAYTYPE_BACK, TRUE);

            // ジャンプアニメ
            mSprite.SetAnimation(mods.GetResource().GetImage("Asset/Image/Player_Jump.png"), ::GameMain::Draw::AnimationData{ 32, 32, 4, 4, 0.1f });
        }

        mPosition.y += mVelocityY * deltaTime;

        mSprite.Update(deltaTime);

        // コライダーを座標に追従させる
        mCollider.SetRect(mPosition.x + 16.0f, mPosition.y + 16.0f, 16.0f, 16.0f);

        // 落下死判定
        if (mPosition.y > 600.0f) {
            mGameCtrl.SetIsGameOver();
        }
    }

    void PlayerObj::OnDraw() {
        mSprite.Draw(mPosition.x, mPosition.y);
    }

    void PlayerObj::SetGrounded(bool isGrounded, float landingY) {
        if (isGrounded) {
            if (!mIsGrounded) {
                // 着地した瞬間：Y座標を補正
                mPosition.y = landingY;
                mVelocityY = 0.0f;
                mIsGrounded = true;

                mSprite.SetAnimation(Manager::Modules::Get().GetResource().GetImage("Asset/Image/Player_Run.png"), ::GameMain::Draw::AnimationData{ 32, 32, 4, 4, 0.1f });
            }
        } else {
            mIsGrounded = false;
        }
    }
}