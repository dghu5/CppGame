#pragma once
#include "IGameObject.h"

namespace GameMain::Actor {
    class Terrain : public IGameObject {
    public:
        Terrain(::GameMain::Core::GameCtrl& ctrl, float x, float y);

        void OnUpdate(float deltaTime) override;
        void OnDraw() override;

    private:
        float mSpeed = 200.0f; // 左への移動速度
    };
}