#pragma once
#include "IGameObject.h"

namespace GameMain::Actor {
    class PlayerObj : public IGameObject {
    public:
        PlayerObj(::GameMain::Core::GameCtrl& ctrl);
        void OnUpdate(float deltaTime) override;
        void OnDraw() override;

        /// <summary>
        /// 着地状態の更新
        /// </summary>
        void SetGrounded(bool isGrounded, float landingY = 0.0f);

    private:
        float mVelocityY = 0.0f;     // 現在の縦方向速度
        bool  mIsGrounded = false;  // 地面に立っているか

        static constexpr float Gravity = 250.0f; // 重力加速度
        static constexpr float JumpPower = -300.0f; // ジャンプ初速
        float mSpeed = 50.0f;
    };
}