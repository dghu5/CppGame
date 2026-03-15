#pragma once
#include <string>
#include <unordered_map>
#include "DxLib.h"

namespace GameMain::Manager {
    class ResourceManager {
    public:
        ResourceManager() = default;
        ~ResourceManager() { ReleaseAll(); }

        /// <summary>
        /// 画像ロード
        /// </summary>
        bool LoadImageResource(const std::string& path);

        /// <summary>
        /// サウンドロード
        /// </summary>
        bool LoadSoundResource(const std::string& path);

        /// <summary>
        /// フォントロード
        /// </summary>
        bool LoadFontResource(const std::string& key, const std::string& fontName, int size, int thick);

        /// <summary>
        /// ファイルからのフォントロード
        /// </summary>
        bool LoadFontFileResource(const std::string& key, const std::string& path, const std::string& fontName, int size, int thick);

        /// <summary>
        /// 画像ハンドルの取得
        /// </summary>
        int GetImage(const std::string& path) const;

        /// <summary>
        /// サウンドハンドルの取得
        /// </summary>
        int GetSound(const std::string& path) const;

        /// <summary>
        /// フォントバンドルの取得
        /// </summary>
        int GetFont(const std::string& key) const;

        /// <summary>
        /// 全解放
        /// </summary>
        void ReleaseAll();

    private:
        std::unordered_map<std::string, int> mImageMap;
        std::unordered_map<std::string, int> mSoundMap;
        std::unordered_map<std::string, int> mFontMap;
        std::vector<std::string> mLoadedFontPaths;
    };
}