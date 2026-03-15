#include "Sprite.h"

namespace GameMain::Draw {
    Sprite::Sprite(int handle, const AnimationData& animData)
        : mHandle(handle), mAnimData(animData) {}

    void Sprite::Update(float deltaTime) {
        if (mAnimData.totalFrames <= 1) return;

        mElapsedTime += deltaTime;
        if (mElapsedTime >= mAnimData.frameDuration) {
            mElapsedTime -= mAnimData.frameDuration;
            mCurrentFrame = (mCurrentFrame + 1) % mAnimData.totalFrames;
        }
    }

    void Sprite::Draw(float x, float y) const {
        if (mHandle == -1) return;

        // 現在のフレームから「横何番目」「縦何番目」かを算出
        int colIndex = mCurrentFrame % mAnimData.cols;
        int rowIndex = mCurrentFrame / mAnimData.cols;

        int srcX = colIndex * mAnimData.frameWidth;
        int srcY = rowIndex * mAnimData.frameHeight;

        DrawRectGraphF(x, y, srcX, srcY,
            mAnimData.frameWidth, mAnimData.frameHeight,
            mHandle, TRUE);
    }

    void Sprite::SetAnimation(int handle, const AnimationData& animData) {
        // 同じアニメーションなら再設定しない
        if (mHandle == handle && 
            mAnimData.frameWidth == animData.frameWidth &&
            mAnimData.frameHeight == animData.frameHeight &&
            mAnimData.totalFrames == animData.totalFrames &&
            mAnimData.cols == animData.cols &&
            mAnimData.frameDuration == animData.frameDuration) {
            return;
        }

        mHandle = handle;
        mAnimData = animData;
        mCurrentFrame = 0;      // 状態が変わったらフレームをリセット
        mElapsedTime = 0.0f;    // タイマーもリセット
    }
}