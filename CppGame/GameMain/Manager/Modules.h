#pragma once
#include <memory>
#include "InputManager.h"
#include "ResourceManager.h"
#include "CollisionManager.h"
#include "SceneManager.h"

namespace GameMain::Manager {
    class Modules {
    public:
        // シングルトンのインスタンスを取得
        static Modules& Get() {
            static Modules instance;
            return instance;
        }

        // 各マネージャーへのアクセス用（ゲッター）
        GameMain::Manager::InputManager& GetInput() const { return *mInputManager; }
        GameMain::Manager::ResourceManager& GetResource() const { return *mResourceManager; }
        GameMain::Manager::CollisionManager& GetCollision() const { return *mCollisionManager; }
        GameMain::Manager::SceneManager& GetScene() const { return *mSceneManager; }

    private:
        Modules(); // コンストラクタをprivateにして外部から作れないようにする
        ~Modules() = default;

        // シングルトンなのでコピー禁止
        Modules(const Modules&) = delete;
        Modules& operator=(const Modules&) = delete;

        // 各マネージャーの保持
        std::unique_ptr<GameMain::Manager::InputManager> mInputManager;
        std::unique_ptr<GameMain::Manager::ResourceManager> mResourceManager;
        std::unique_ptr<GameMain::Manager::CollisionManager> mCollisionManager;
        std::unique_ptr<GameMain::Manager::SceneManager> mSceneManager;
    };
}