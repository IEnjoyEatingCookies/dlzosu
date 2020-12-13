#include "IO/global_configurations.h"

namespace final_project {
    // Input
    const int kKeyOne = ci::app::KeyEvent::KEY_z;
    const int kKeyTwo = ci::app::KeyEvent::KEY_x;

    const int kKeyNextMap = ci::app::KeyEvent::KEY_s;
    const int kKeyPrevMap = ci::app::KeyEvent::KEY_w;
    const int kKeyNextSong = ci::app::KeyEvent::KEY_d;
    const int kKeyPrevSong = ci::app::KeyEvent::KEY_a;
    const int kKeyPlaySong = ci::app::KeyEvent::KEY_SPACE;
    const int kKeyReturn = ci::app::KeyEvent::KEY_ESCAPE;
    const int kKeyReload = ci::app::KeyEvent::KEY_r;
    const int kKeyQuit = ci::app::KeyEvent::KEY_F1;

    // Paths
    const std::string kOsuPath = "dlzosu!";
    const std::string kSongsPath = "Songs";
    const std::string kSkinsPath = "Skins";
    const std::string kSkinName = "Lucid Elegance";

    // Game
    const glm::vec2 kOsuPixelResolution = glm::vec2(640, 480);
    const glm::vec2 kPlayfieldResolution = glm::vec2(512, 384);
    const long kSongEnd = 1500;
    const std::string kHitSoundAudio = "hitsound.wav";
    const float kSongVolume = 0.15f;
    const float kHitSoundVolume = 0.1f;
    const long kSongStartBuffer = 1000;

    const std::string kFont = "arial";
    const size_t kScoreLength = 9;

    // Menu
    const double kMapWidth = 530;
    const double kMapHeight = 300;
    const double kSelectedMult = 1.3;

    // End Screen
    const glm::vec2 kIconSize(150, 150);
    const std::string kHit0 = "hit0.png";
    const std::string kHit50 = "hit50.png";
    const std::string kHit100 = "hit100.png";
    const std::string kHit300 = "hit300.png";
    const std::string kRankingA = "ranking-a.png";
    const std::string kRankingB = "ranking-b.png";
    const std::string kRankingC = "ranking-c.png";
    const std::string kRankingD = "ranking-d.png";
    const std::string kRankingS = "ranking-s.png";
    const std::string kRankingX = "ranking-x.png";

    // HUD
    const glm::vec2 kProgressDim(250, 30);

    // Cursor
    const std::string kCursorImage = "cursor.png";
    const std::string kCursorTrailImage = "cursor-trail.png";

    const size_t kCursorTrailPoints = 10;
    const double kCursorSize = 30;
    const double kCursorExpansionMultiplier = 1.3;

    // Circle
    const float kCircleWidth = 10;
    const float kCircleApproach = 5;
    const float kCircleDissipate = 0.3f;
    const float kCircleMarkerSize = 0.5f;
    const float kCircleMarkerLength = 2;

    const ci::Color kCircleMissColor(1, 0, 0);
    const ci::Color kCircle100Color(0, (float) 160 / 255, (float) 40/ 255);
    const ci::Color kCircle50Color((float) 200 / 255, (float) 160 / 255, 0);

    // Spinner
    const std::string kSpinnerApproachCircle = "spinner-approach-circle.png";
    const std::string kSpinnerMiddle = "spinner-middle.png";
    const std::string kSpinnerTop = "spinner-top.png";
    const std::string kSpinnerClear = "spinner-clear.png";

    const glm::vec2 kSpinnerClearDim(150, 384);
    const float kSpinnerSize = 190;
    const float kSpinnerMiddleSize = 16;

    const long kSpinnerMissLength = 200;
    const ci::Color kSpinnerMissColor(1, 0, 0);
    const double kSpinnerRPM = 250;
    const double kSpinnerExtraRPM = 75;
    const long kSpinnerApproachRate = 600;

    const std::string kSpinnerSpin = "spinnerspin.wav";
    const std::string kSpinnerComplete = "spinnerbonus.wav";

    // Assets
    AssetLoader asset_loader = AssetLoader(kOsuPath, kSongsPath, kSkinsPath, kSkinName);

    std::vector<std::string> delimit(const std::string &string) {
        std::vector<std::string> result;
        std::stringstream sstream(string);
        while(sstream.good()) {
            std::string str;
            getline(sstream, str, ','); //get first string delimited by comma
            result.push_back(str);
        }
        return result;
    }
}