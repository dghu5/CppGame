#include "GameScene.h"
#include "GameOverScene.h"
#include "../Manager/Modules.h"
#include "DxLib.h"

namespace GameMain::Scene {
    void GameScene::OnStart() {
        // 先にリソースロード
        auto& resourceManager = Manager::Modules::Get().GetResource();
        resourceManager.LoadImageResource("Asset/Image/Bg.png");
        resourceManager.LoadImageResource("Asset/Image/Player_Run.png");
        resourceManager.LoadImageResource("Asset/Image/Player_Jump.png");
        resourceManager.LoadImageResource("Asset/Image/Terrain.png");
        resourceManager.LoadSoundResource("Asset/Sound/Bgm_InGame.ogg");
        resourceManager.LoadSoundResource("Asset/Sound/Se_Jump.ogg");
        resourceManager.LoadFontFileResource("GameFont24", "Asset/Font/GameFont.ttf", "GameFont24", 24, 3);

        // ゲーム操作ロジック初期化（リソースの初期化後にする）
        mGameCtrl = std::make_unique<Core::GameCtrl>();

        // BGM再生
        int bgmHandle = resourceManager.GetSound("Asset/Sound/Bgm_InGame.ogg");
        PlaySoundMem(bgmHandle, DX_PLAYTYPE_LOOP, TRUE);
    }

    void GameScene::OnEnd() {
        auto& resourceManager = Manager::Modules::Get().GetResource();

        // BGM停止
        int bgmHandle = resourceManager.GetSound("Asset/Sound/Bgm_InGame.ogg");
        StopSoundMem(bgmHandle);

        // リソースの解放
        resourceManager.ReleaseAll();
    }

    void GameScene::OnUpdate(float deltaTime) {
        // 初期化前は処理しない
        if (mGameCtrl == nullptr) {
            return;
        }

        mGameCtrl->Update(deltaTime);

        // ゲームオーバー時にシーン遷移
        auto& mods = Manager::Modules::Get();
        if (mGameCtrl->IsGameOver()) {
            mods.GetScene().ChangeScene(std::make_unique<GameOverScene>());
        }
    }

    void GameScene::OnDraw() {
        // 初期化前は処理しない
        if (mGameCtrl == nullptr) {
            return;
        }

        mGameCtrl->Draw();
    }
}