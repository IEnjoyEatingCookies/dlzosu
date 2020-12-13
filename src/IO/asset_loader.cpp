#include "IO/asset_loader.h"

namespace final_project {
AssetLoader::AssetLoader(const std::string &osu_path, const std::string &songs_path, const std::string &skins_path, const std::string& skin_name) {
    osu_path_ = osu_path;
    songs_path_ = songs_path;
    skins_path_ = skins_path;
    skin_name_ = skin_name;
    reload();
}

AssetLoader::~AssetLoader() {
    cached_images_.clear();
    cached_audio_.clear();
}

void AssetLoader::reload() {
    song_list_ = getSongList();
}
void AssetLoader::setSkin(const std::string &skin_name) {
    skin_name_ = skin_name;
}

const std::string AssetLoader::getAssetsPath(bool relative) const {
    if (relative) {
        return "..\\..\\assets\\" + osu_path_;
    } else {
        return osu_path_;
    }
}
const std::string AssetLoader::getSongsPath(bool relative) const {
    if (relative) {
        return "..\\..\\assets\\" + osu_path_ + "\\" + songs_path_;
    } else {
        return osu_path_ + "\\" + songs_path_;
    }
}
const std::string AssetLoader::getSkinsPath(bool relative) const {
    if (relative) {
        return "..\\..\\assets\\" + osu_path_ + "\\" + skins_path_;
    } else {
        return osu_path_ + "\\" + skins_path_;
    }
}

ci::gl::Texture2dRef & AssetLoader::requestImage(size_t song_index, const std::string &image_name, bool recache) {
    return requestImage(song_list_.at(song_index).at(0), image_name, recache);
}
ci::gl::Texture2dRef& AssetLoader::requestImage(const std::string &song_name, const std::string &image_name, bool recache) {
    std::string key = song_name + "\\" + image_name;
    if (recache || cached_images_.find(key) == cached_images_.end()) { // store images for later use
        ci::gl::Texture2dRef image;
        try {
            auto img = loadImage(ci::app::loadAsset( getSongsPath(false) + "\\" + key));
            image = ci::gl::Texture2d::create(img);
            cached_images_[key] = image;
        } catch (...) {
            throw std::out_of_range("image file (" + key + ") not found!");
        }
    }
    return cached_images_[key];
}
ci::gl::Texture2dRef & AssetLoader::requestImage(const std::string& skin_name, bool recache) {
    std::string key = skin_name_ + "\\" + skin_name;
    if (recache || cached_images_.find(key) == cached_images_.end()) { // store images for later use
        ci::gl::Texture2dRef image;
        try {
            auto img = loadImage(ci::app::loadAsset( getSkinsPath(false) + "\\" + key));
            image = ci::gl::Texture2d::create(img);
            cached_images_[key] = image;
        } catch (...) {
            throw std::out_of_range("image file (" + key + ") not found!");
        }
    }
    return cached_images_[key];
}

ci::audio::VoiceRef & AssetLoader::requestAudio(const std::string &song_name, const std::string &audio_name, bool recache) {
    std::string key = song_name + "\\" + audio_name;
    if (recache || cached_audio_.find(key) == cached_audio_.end()) {
        ci::audio::VoiceRef audio;
        try {
            ci::audio::SourceFileRef song_file = ci::audio::load(ci::app::loadAsset(getSongsPath(false) + "\\" + key));
            audio = ci::audio::Voice::create(song_file);
            cached_audio_[key] = audio;
        } catch (...) {
            throw std::out_of_range("audio file (" + key + ") not found!");
        }
    }
    return cached_audio_[key];
}
ci::audio::VoiceRef & AssetLoader::requestAudio(const std::string &skin_audio_name, bool recache) {
    std::string key = skin_name_ + "\\" + skin_audio_name;
    if (recache || cached_audio_.find(key) == cached_audio_.end()) {
        ci::audio::VoiceRef audio;
        try {
            ci::audio::SourceFileRef song_file = ci::audio::load(ci::app::loadAsset(getSkinsPath(false) + "\\" + key));
            audio = ci::audio::Voice::create(song_file);
            cached_audio_[key] = audio;
        } catch (...) {
            throw std::out_of_range("audio file (" + key + ") not found!");
        }
    }
    return cached_audio_[key];
}


std::vector<std::string> AssetLoader::getMapList(const std::string &song) const {
    std::vector<std::string> song_names;
    for(auto& p : std::experimental::filesystem::recursive_directory_iterator(getSongsPath(true) + "\\" + song)) {
        std::string filename = p.path().filename().string();
        if (filename.substr(filename.length() - 4) == ".osu") { // only grab osu files
            song_names.push_back(filename);
        }
    }
    return song_names;
}
std::vector<std::vector<std::string>> AssetLoader::getSongList() const {
    std::vector<std::vector<std::string>> song_list;
    for(auto& p : std::experimental::filesystem::recursive_directory_iterator(getSongsPath(true))) { // iterate over the whole songs folder
        if (p.status().type() == std::experimental::filesystem::file_type::directory) { // only grab directories
            std::vector<std::string> map_list = getMapList(p.path().filename().string());
            if (!map_list.empty()) { // if it finds no maps in the song, then we skip it
                map_list.insert(map_list.begin(), p.path().filename().string());
                song_list.push_back(map_list);
            }
        };
    }
    return song_list;
}

}