#pragma once
namespace GameMain::Core {
    struct TerrainConfig {
        static constexpr int MinGapSize = 2;   // 穴の最小幅
        static constexpr int MaxGapSize = 4;   // 穴の最大幅
        static constexpr int MinBridgeSize = 5; // 足場の最小連続数
        static constexpr int MaxBridgeSize = 10; // 足場の最大連続数
    };
}