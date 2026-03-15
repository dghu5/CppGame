#pragma once
#include "IScene.h"

namespace GameMain::Scene {
    class GameOverScene : public IScene {
    public:
        void OnStart() override;
        void OnEnd() override;
        void OnUpdate(float deltaTime) override;
        void OnDraw() override;
    };
}