#include "ResourceManager.h"
#include <DxLib.h>

namespace GameMain::Manager {

    bool ResourceManager::LoadImageResource(const std::string& path) {
        // すでに読み込まれているか確認
        if (mImageMap.find(path) != mImageMap.end()) {
            return true; // 既に存在するのでロード不要
        }

        int handle = LoadGraph(path.c_str());
        if (handle == -1) {
            return false;
        }

        mImageMap[path] = handle;
        return true;
    }

    bool ResourceManager::LoadSoundResource(const std::string& path) {
        if (mSoundMap.find(path) != mSoundMap.end()) {
            return true;
        }

        int handle = LoadSoundMem(path.c_str());
        if (handle == -1) {
            return false;
        }

        mSoundMap[path] = handle;
        return true;
    }

    bool ResourceManager::LoadFontResource(const std::string& key, const std::string& fontName, int size, int thick) {
        if (mFontMap.find(key) != mFontMap.end()) return true;

        // フォント作成関数
        int handle = CreateFontToHandle(fontName.c_str(), size, thick);
        if (handle == -1) return false;

        mFontMap[key] = handle;
        return true;
    }

    int ResourceManager::GetImage(const std::string& path) const {
        auto it = mImageMap.find(path);
        if (it != mImageMap.end()) {
            return it->second;
        }
        return -1; // 見つからない場合は -1 を返す
    }

    int ResourceManager::GetSound(const std::string& path) const {
        auto it = mSoundMap.find(path);
        if (it != mSoundMap.end()) {
            return it->second;
        }
        return -1;
    }

    int ResourceManager::GetFont(const std::string& path) const {
        auto it = mFontMap.find(path);
        if (it != mFontMap.end()) {
            return it->second;
        }
        return -1;
    }

    bool ResourceManager::LoadFontFileResource(const std::string& key, const std::string& path, const std::string& fontName, int size, int thick) {
        if (mFontMap.find(key) != mFontMap.end()) return true;

        // フォントファイルをWindowsに一時登録
        if (AddFontResourceEx(path.c_str(), FR_PRIVATE, NULL) > 0) {
            mLoadedFontPaths.push_back(path);
        } else {
            return false;
        }

        // 登録されたフォント名を使ってハンドルを作成
        int handle = CreateFontToHandle(fontName.c_str(), size, thick);
        if (handle == -1) return false;

        mFontMap[key] = handle;
        return true;
    }

    void ResourceManager::ReleaseAll() {
        for (auto& pair : mImageMap) {
            DeleteGraph(pair.second);
        }
        mImageMap.clear();

        for (auto& pair : mSoundMap) {
            DeleteSoundMem(pair.second);
        }
        mSoundMap.clear();

        for (auto& pair : mFontMap) {
            DeleteFontToHandle(pair.second);
        }
        mFontMap.clear();

        for (const auto& path : mLoadedFontPaths) {
            RemoveFontResourceEx(path.c_str(), FR_PRIVATE, NULL);
        }
        mLoadedFontPaths.clear();
    }
}