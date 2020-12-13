#include "IO/map_loader.h"

namespace final_project {
MapLoader::MapLoader() {
    reload();
}

void MapLoader::reload() {
    song_list_ = getSongList();
}

const std::string MapLoader::getAssetsPath(bool relative) const {
    if (relative) {
        return "..\\..\\assets\\" + kOsuPath;
    } else {
        return kOsuPath;
    }
}
const std::string MapLoader::getSongsPath(bool relative) const {
    if (relative) {
        return "..\\..\\assets\\" + kOsuPath + "\\" + kSongsPath;
    } else {
        return kOsuPath + "\\" + kSongsPath;
    }
}
const std::string MapLoader::getSkinsPath(bool relative) const {
    if (relative) {
        return "..\\..\\assets\\" + kOsuPath + "\\" + kSkinsPath;
    } else {
        return kOsuPath + "\\" + kSkinsPath;
    }
}

Map& MapLoader::requestMap(size_t song_index, size_t map_index, bool recache) {
    return requestMap(song_list_.at(song_index).at(0), song_list_.at(song_index).at(map_index + 1), recache);
}
Map& MapLoader::requestMap(const std::string &song_name, const std::string &map_name, bool recache) {
    std::string key = song_name + "\\" + map_name;
    if (recache || cached_maps_.find(key) == cached_maps_.end()) { // store maps for later use
        std::string song_name_copy = song_name;
        Map map(song_name_copy);
        std::ifstream map_file;
        map_file.open(getSongsPath(true) + "\\" + key);
        if (!map_file.is_open()) {
            std::cout << "map file (" + key + ") not found!" << std::endl;
            throw std::out_of_range("map file (" + key + ") not found!");
        }
        map_file >> map;
        cached_maps_[key] = map;
    }
    return cached_maps_[key];
}

std::vector<std::string> MapLoader::getMapList(const std::string& song) const {
    std::vector<std::string> song_names;
    for(auto& p : std::experimental::filesystem::recursive_directory_iterator(getSongsPath(true) + "\\" + song)) {
        std::string filename = p.path().filename().string();
        if (filename.substr(filename.length() - 4) == ".osu") { // only grab osu files
            song_names.push_back(filename);
        }
    }
    return song_names;
}
std::vector<std::vector<std::string>> MapLoader::getSongList() const {
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