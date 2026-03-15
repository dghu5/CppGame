#pragma once
#include "IScene.h"
#include "../Core/GameCtrl.h"

namespace GameMain::Scene {
    class GameScene : public IScene {
    private:
        std::unique_ptr<Core::GameCtrl> mGameCtrl;
    public:
        void OnStart() override;
        void OnEnd() override;
        void OnUpdate(float deltaTime) override;
        void OnDraw() override;
    };
}