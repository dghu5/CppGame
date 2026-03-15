#pragma once
#include <memory>
#include "../Scene/IScene.h"

namespace GameMain::Manager {
    class SceneManager {
    public:
        SceneManager();

        /// <summary>
        /// シーン変更
        /// </summary>
        void ChangeScene(std::unique_ptr<GameMain::Scene::IScene> nextScene);

        /// <summary>
        /// 更新処理
        /// </summary>
        void Update(float deltaTime);

        /// <summary>
        /// 描画処理
        /// </summary>
        void Draw();

    private:
        std::unique_ptr<GameMain::Scene::IScene> mCurrentScene;
    };
}