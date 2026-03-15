#include "InputManager.h"
#include <algorithm> // std::copy用

namespace GameMain::Manager {
    InputManager::InputManager() {
        mCurrBuffer.fill(0);
        mPrevBuffer.fill(0);
    }

    void InputManager::Update() {
        // 前フレームのキャッシュ
        mPrevBuffer = mCurrBuffer;

        // 現在の状況を保持
        GetHitKeyStateAll(mCurrBuffer.data());
    }

    bool InputManager::IsKeyDown(int keyCode) const {
        return mCurrBuffer[keyCode] != 0;
    }

    bool InputManager::IsKeyPressed(int keyCode) const {
        return (mCurrBuffer[keyCode] != 0) && (mPrevBuffer[keyCode] == 0);
    }

    bool InputManager::IsKeyReleased(int keyCode) const {
        return (mCurrBuffer[keyCode] == 0) && (mPrevBuffer[keyCode] != 0);
    }
}