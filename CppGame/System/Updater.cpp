#include "Updater.h"
#include "DxLib.h"
#include "../GameMain/Manager/Modules.h"
namespace System {
    Updater::Updater() {}

    Updater::~Updater() {}

    bool Updater::Update(float deltaTime) {
        // 入力更新
        auto& inputManager = GameMain::Manager::Modules::Get().GetInput();
        inputManager.Update();

        // シーン更新
        auto& sceneManager = GameMain::Manager::Modules::Get().GetScene();
        sceneManager.Update(deltaTime);

        // Escapeキーで終了を検知
        if (inputManager.IsKeyPressed(KEY_INPUT_ESCAPE)) {
            return false;
        }

        return true;
    }

    void Updater::Draw() const {
        // シーン描画
        auto& sceneManager = GameMain::Manager::Modules::Get().GetScene();
        sceneManager.Draw();

        // コリジョンデバッグ描画
        auto& collisionManager = GameMain::Manager::Modules::Get().GetCollision();
        collisionManager.DrawDebugAll();
    }
}