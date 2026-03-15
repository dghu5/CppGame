#pragma once

namespace GameMain::Scene {
    class IScene {
    public:
        virtual ~IScene() = default;

        /// <summary>
        /// シーン開始時処理
        /// </summary>
        virtual void OnStart() = 0;

        /// <summary>
        /// シーン終了時処理
        /// </summary>
        virtual void OnEnd() = 0;

        /// <summary>
        /// 更新処理
        /// </summary>
        virtual void OnUpdate(float deltaTime) = 0;

        /// <summary>
        /// 描画処理
        /// </summary>
        virtual void OnDraw() = 0;
    };
}