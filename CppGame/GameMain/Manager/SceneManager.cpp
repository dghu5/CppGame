#include "SceneManager.h"

namespace GameMain::Manager {
    SceneManager::SceneManager()
        : mCurrentScene(nullptr)
    {
    }

    void SceneManager::ChangeScene(std::unique_ptr<GameMain::Scene::IScene> nextScene) {
        if (mCurrentScene) {
            // シーンの終了
            mCurrentScene->OnEnd();
        }
        // シーンの開始
        mCurrentScene = std::move(nextScene);
        mCurrentScene->OnStart();
    }

    void SceneManager::Update(float deltaTime) {
        if (mCurrentScene != nullptr) {
            mCurrentScene->OnUpdate(deltaTime);
        }
    }

    void SceneManager::Draw() {
        if (mCurrentScene != nullptr) {
            mCurrentScene->OnDraw();
        }
    }
}