#include "TitleScene.h"
#include "GameScene.h"
#include "../Manager/Modules.h"
#include "DxLib.h"

namespace GameMain::Scene {
    void TitleScene::OnStart() {
        // 先にリソースロード
        auto& resourceManager = Manager::Modules::Get().GetResource();
        resourceManager.LoadImageResource("Asset/Image/Title.png");
        resourceManager.LoadSoundResource("Asset/Sound/Bgm_Title.ogg");
        resourceManager.LoadSoundResource("Asset/Sound/Se_Select.ogg");
        resourceManager.LoadFontFileResource("GameFont48", "Asset/Font/GameFont.ttf", "GameFont48", 48, 3);
        resourceManager.LoadFontFileResource("GameFont24", "Asset/Font/GameFont.ttf", "GameFont24", 24, 3);

        // BGM再生
        int bgmHandle = resourceManager.GetSound("Asset/Sound/Bgm_Title.ogg");
        PlaySoundMem(bgmHandle, DX_PLAYTYPE_LOOP, TRUE);
    }

    void TitleScene::OnEnd() {
        auto& resourceManager = Manager::Modules::Get().GetResource();

        // BGM停止
        int bgmHandle = resourceManager.GetSound("Asset/Sound/Bgm_Title.ogg");
        StopSoundMem(bgmHandle);

        // リソースの解放
        resourceManager.ReleaseAll();
    }

    void TitleScene::OnUpdate(float deltaTime) {
        // スペースキーが押されたらゲーム本編へ
        auto& mods = Manager::Modules::Get();
        if (mods.GetInput().IsKeyPressed(KEY_INPUT_SPACE)) {
            int seHandle = mods.GetResource().GetSound("Asset/Sound/Se_Select.ogg");
            PlaySoundMem(seHandle, DX_PLAYTYPE_NORMAL, TRUE);
            mods.GetScene().ChangeScene(std::make_unique<GameScene>());
        }
    }

    void TitleScene::OnDraw() {
        auto& resourceManager = Manager::Modules::Get().GetResource();
        int imageHandle = resourceManager.GetImage("Asset/Image/Title.png");

        if (imageHandle != -1) {
            // タイトル画像描画
            DrawGraph(0, 0, imageHandle, TRUE);
        }

        // 文字描画
        int fontHandle48 = resourceManager.GetFont("GameFont48");
        if (fontHandle48 != -1) {
            DrawStringToHandle(100, 180, "RUN GAME", GetColor(255, 255, 255), fontHandle48);
        }

        int fontHandle24 = resourceManager.GetFont("GameFont24");
        if (fontHandle24 != -1) {
            DrawStringToHandle(200, 400, "PRESS SPACE START", GetColor(255, 255, 255), fontHandle24);
        }
    }
}