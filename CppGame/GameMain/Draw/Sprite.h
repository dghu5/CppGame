#pragma once
#include <vector>
#include "DxLib.h"

namespace GameMain::Draw {
    /// <summary>
    /// アニメーション単位の定義データ（スプライト画像1毎に対応）
    /// </summary>
    struct AnimationData {
        /// <summary>
        /// コマの横幅
        /// </summary>
        int frameWidth;

        /// <summary>
        /// コマの高さ
        /// </summary>
        int frameHeight;

        /// <summary>
        /// 全コマ数
        /// </summary>
        int totalFrames;

        /// <summary>
        /// 横に何個並ぶか
        /// </summary>
        int cols;

        /// <summary>
        /// 1コマの秒数
        /// </summary>
        float frameDuration;
    };

    class Sprite {
    public:
        Sprite(int handle, const AnimationData& animData); // 値しか持たないのでデストラクタは不要

        /// <summary>
        /// 更新処理
        /// </summary>
        void Update(float deltaTime);

        /// <summary>
        /// 描画処理
        /// </summary>
        void Draw(float x, float y) const;

        /// <summary>
        /// アニメーション指定
        /// </summary>
        void SetAnimation(int handle, const AnimationData& animData);

    private:
        int mHandle;
        AnimationData mAnimData;

        int mCurrentFrame = 0;
        float mElapsedTime = 0.0f;
    };
}