#pragma once
#include <array>
#include "DxLib.h"

namespace GameMain::Manager {
    class InputManager {
    public:
        InputManager();

        /// <summary>
        /// 更新処理
        /// </summary>
        void Update();

        /// <summary>
        /// 押されているか
        /// </summary>
        bool IsKeyDown(int keyCode) const;


        /// <summary>
        /// 押された瞬間か
        /// </summary>
        bool IsKeyPressed(int keyCode) const;


        /// <summary>
        /// 離された瞬間か
        /// </summary>
        bool IsKeyReleased(int keyCode) const;

    private:
        std::array<char, 256> mCurrBuffer; // 現在の入力
        std::array<char, 256> mPrevBuffer; // 1フレーム前の入力
    };
}