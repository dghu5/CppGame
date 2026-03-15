#pragma once

namespace System {
    /// <summary>
    /// 更新処理
    /// </summary>
    class Updater {
    public:
        Updater();  // コンストラクタ（初期化）
        ~Updater(); // デストラクタ（後片付け）

        /// <summary>
        /// ゲームロジック更新
        /// </summary>
        /// <returns>falseの場合ゲーム終了</returns>
        bool Update(float deltaTime);

        /// <summary>
        /// 描画処理
        /// </summary>
        void Draw() const;

    private:
    };
}