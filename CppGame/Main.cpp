#include "DxLib.h"
#include "System/Updater.h"
#include "GameMain/Manager/Modules.h"
#include "GameMain/Scene/TitleScene.h"
#include <memory>

/// <summary>
/// メイン関数
/// </summary>
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
    // --- DXライブラリの初期設定 ---
    ChangeWindowMode(TRUE);             // ウィンドウモードで起動
    SetGraphMode(640, 480, 32);         // 画面解像度の設定
    SetWaitVSyncFlag(FALSE);             // 垂直同期の待機をしない
    if (DxLib_Init() == -1) return -1;  // 初期化失敗したら終了
    SetDrawScreen(DX_SCREEN_BACK);      // 裏画面（ダブルバッファリング）の設定

    {
        // Updaterを生成
        auto updater = std::make_unique<System::Updater>();

        const int TARGET_FRAME = 60;
        const LONGLONG TARGET_FRAME_TIME = 1000000 / TARGET_FRAME;

        // 時間計測
        auto lastTime = GetNowHiPerformanceCount();
        auto deltaTime = 0.0f;

        // 初期シーン指定
        GameMain::Manager::Modules::Get().GetScene().ChangeScene(std::make_unique<GameMain::Scene::TitleScene>());

        // --- メインループ ---
        while (ProcessMessage() == 0 && ClearDrawScreen() == 0) {

            // ゲームロジックの更新
            if (!updater->Update(deltaTime)) {
                break;
            }

            // 描画処理
            updater->Draw();

            // 裏画面の内容を反映
            ScreenFlip();

            auto nowTime = GetNowHiPerformanceCount();
            auto elapsedTime = nowTime - lastTime;
            
            // フレーム待機
            if (elapsedTime < TARGET_FRAME_TIME) {
                // 残り時間を計算
                int waitTime = static_cast<int>((TARGET_FRAME_TIME - elapsedTime) / 1000);

                // 1ms以上余裕があるなら、OSに処理を逃がしてCPU負荷を抑える
                if (waitTime > 0) {
                    WaitTimer(waitTime);
                }

                // 待機後に再度正確な時間を計測
                while (GetNowHiPerformanceCount() - lastTime < TARGET_FRAME_TIME) {
                    // 微調整の待機
                }
            }

            nowTime = GetNowHiPerformanceCount();
            // 実際の経過時間を秒単位に変換
            deltaTime = static_cast<float>(nowTime - lastTime) / 1000000.0f;
            lastTime = nowTime;
        }
    }

    // DXライブラリの終了処理
    DxLib_End();
    return 0;
}