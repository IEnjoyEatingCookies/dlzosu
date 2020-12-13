#ifndef OSU_SETTINGS_H
#define OSU_SETTINGS_H
#endif //OSU_SETTINGS_H
#include "IO/asset_loader.h"

namespace final_project {
    // Input
    extern const int kKeyOne;
    extern const int kKeyTwo;

    extern const int kKeyNextMap;
    extern const int kKeyPrevMap;
    extern const int kKeyNextSong;
    extern const int kKeyPrevSong;
    extern const int kKeyPlaySong;
    extern const int kKeyReturn;
    extern const int kKeyReload;
    extern const int kKeyQuit;

    // Paths
    extern const std::string kOsuPath;
    extern const std::string kSongsPath;
    extern const std::string kSkinsPath;
    extern const std::string kSkinName;

    // Game
    extern const glm::vec2 kOsuPixelResolution;
    extern const glm::vec2 kPlayfieldResolution;
    extern const long kSongEnd;
    extern const std::string kHitSoundAudio;
    extern const float kSongVolume;
    extern const float kHitSoundVolume;
    extern const long kSongStartBuffer;

    extern const std::string kFont;
    extern const size_t kScoreLength;

    // Menu
    extern const double kMapWidth;
    extern const double kMapHeight;
    extern const double kSelectedMult;

    // End Screen
    extern const glm::vec2 kIconSize;
    extern const std::string kHit0;
    extern const std::string kHit50;
    extern const std::string kHit100;
    extern const std::string kHit300;
    extern const std::string kRankingA;
    extern const std::string kRankingB;
    extern const std::string kRankingC;
    extern const std::string kRankingD;
    extern const std::string kRankingS;
    extern const std::string kRankingX;

    // HUD
    extern const glm::vec2 kProgressDim;

    // Cursor
    extern const std::string kCursorImage;
    extern const std::string kCursorTrailImage;

    extern const size_t kCursorTrailPoints;
    extern const double kCursorSize;
    extern const double kCursorExpansionMultiplier;

    // Circle
    extern const float kCircleWidth;
    extern const float kCircleApproach;
    extern const float kCircleDissipate;
    extern const float kCircleMarkerSize;
    extern const float kCircleMarkerLength;

    extern const ci::Color kCircleMissColor;
    extern const ci::Color kCircle100Color;
    extern const ci::Color kCircle50Color;

    // Spinner
    extern const std::string kSpinnerApproachCircle;
    extern const std::string kSpinnerMiddle;
    extern const std::string kSpinnerTop;
    extern const std::string kSpinnerClear;

    extern const glm::vec2 kSpinnerClearDim;
    extern const float kSpinnerSize;
    extern const float kSpinnerMiddleSize;

    extern const long kSpinnerMissLength;
    extern const ci::Color kSpinnerMissColor;
    extern const double kSpinnerRPM;
    extern const double kSpinnerExtraRPM;
    extern const long kSpinnerApproachRate;

    extern const std::string kSpinnerSpin;
    extern const std::string kSpinnerComplete;

    // Assets
    extern AssetLoader asset_loader;

    /**
     * Delimits a string by comma
     * @param string
     * @return std::vector<std::string>
     */
    std::vector<std::string> delimit(const std::string& string);
}