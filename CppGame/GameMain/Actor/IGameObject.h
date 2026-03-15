#pragma once
#include <memory>
#include "../Util/Vector2.h"
#include "../Draw/Sprite.h"
#include "../Collision/BoxCollider.h"

// 前方宣言（クラスが存在することだけ伝える）
namespace GameMain::Core {
    class GameCtrl;
}

namespace GameMain::Actor {

    class IGameObject {
    public:
        virtual ~IGameObject() = default;

        /// <summary>
        /// 更新
        /// </summary>
        virtual void OnUpdate(float deltaTime) = 0;

        /// <summary>
        /// 描画
        /// </summary>
        virtual void OnDraw() = 0;

        /// <summary>
        /// 破棄指定
        /// </summary>
        void RequestToDispose() {
            mIsRequestToDispose = true;
        }

        /// <summary>
        /// 破棄フラグ確認
        /// </summary>
        bool IsRequestToDispose() const {
            return mIsRequestToDispose;
        }

        /// <summary>
        /// コリジョン
        /// </summary>
        const Collision::BoxCollider& GetCollider() const {
            return mCollider;
        }

        /// <summary>
        /// 位置
        /// </summary>
        const Util::Vector2& GetPosition() const {
            return mPosition;
        }

        /// <summary>
        /// Spriteのアニメ切り替え
        /// </summary>
        void ChangeAnimation(int handle, const Draw::AnimationData& animData) {
            mSprite.SetAnimation(handle, animData);
        }

    protected:
        explicit IGameObject(::GameMain::Core::GameCtrl& ctrl, int spriteHandle, const ::GameMain::Draw::AnimationData& animData, ::GameMain::Collision::EntityTag collisionTag) :
            mGameCtrl(ctrl),
            mSprite(spriteHandle, animData),
            mCollider(collisionTag)
        {}

        ::GameMain::Core::GameCtrl& mGameCtrl;
        ::GameMain::Util::Vector2 mPosition;
        ::GameMain::Draw::Sprite mSprite;
        ::GameMain::Collision::BoxCollider mCollider;

        int mCurrentSpriteIndex = 0;
        bool mIsRequestToDispose = false;
    };
}