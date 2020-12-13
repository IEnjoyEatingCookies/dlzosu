#ifndef OSU_MAP_LOADER_H
#define OSU_MAP_LOADER_H

#include "core/map.h"
#include "IO/global_configurations.h"

namespace final_project {

class MapLoader {
public:
    /**
     * Default Constructor
     */
    MapLoader();

    /**
     * Updates files
     */
    void reload();

    /**
     * Returns the osu assets path
     * @param relative - true for path from runtime, false for path from cinder assets
     * @return std::string path
     */
    const std::string getAssetsPath(bool relative) const;
    /**
     * Returns the osu Songs assets path
     * @param relative - true for path from runtime, false for path from cinder assets
     * @return std::string path
     */
    const std::string getSongsPath(bool relative) const;
    /**
     * Returns the osu Skins assets path
     * @param relative - true for path from runtime, false for path from cinder assets
     * @return std::string path
     */
    const std::string getSkinsPath(bool relative) const;

    /**
     * Requests a map
     * @param song_index index of song path
     * @param map_index index of map
     * @param recache to recache the map if already cached
     * @return Map map
     */
    Map& requestMap(size_t song_index, size_t map_index, bool recache = false);
    /**
     * Requests a map
     * @param song_name filename of song
     * @param map_name filename of map
     * @param recache to recache the map if already cached
     * @return Map map
     */
    Map& requestMap(const std::string& song_name, const std::string& map_name, bool recache = false);


    /**
     * Returns a list of maps of a song
     * @param song filename of the song
     * @return std::vector<std::string> list of maps
     */
    std::vector<std::string> getMapList(const std::string& song) const;
    /**
     * Returns a list of songs (and maps)
     * @return std::vector<std::vector<std::string>> 2d array of songs where the first index is song name
     */
    /*
     * Map not used since I would like to go through order
     */
    std::vector<std::vector<std::string>> getSongList() const;
private:
    std::map<std::string, Map> cached_maps_;
    std::vector<std::vector<std::string>> song_list_;
};

}




#endif //OSU_MAP_LOADER_H
