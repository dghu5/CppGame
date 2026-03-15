#include "Modules.h"

namespace GameMain::Manager {
    Modules::Modules()
        : mInputManager(std::make_unique<InputManager>())
        , mResourceManager(std::make_unique<ResourceManager>())
        , mCollisionManager(std::make_unique<CollisionManager>())
        , mSceneManager(std::make_unique<SceneManager>())
    {}
}