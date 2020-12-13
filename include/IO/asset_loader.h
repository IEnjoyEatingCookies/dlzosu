#ifndef OSU_ASSET_LOADER_H
#define OSU_ASSET_LOADER_H

#include "cinder/gl/gl.h"
#include "cinder/app/App.h"
#include "cinder/audio/audio.h"

namespace final_project {

class AssetLoader {
public:
    /**
     * Constructor with path
     */
    AssetLoader(const std::string& osu_path, const std::string& songs_path, const std::string& skins_path, const std::string& skin_name);
    /**
     * Destructor
     */
    ~AssetLoader();

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
     * Requests an image (song)
     * @param song_index index of song path
     * @param image_name filename of the image
     * @param recache to recache the image if already cached
     * @return ci::gl::Texture2dRef image
     */
    ci::gl::Texture2dRef& requestImage(size_t song_index, const std::string& image_name, bool recache = false);
    /**
     * Requests an image (song)
     * @param song_name filename of the song
     * @param image_name filename of the image
     * @param recache to recache the image if already cached
     * @return ci::gl::Texture2dRef image
     */
    ci::gl::Texture2dRef& requestImage(const std::string& song_name, const std::string& image_name, bool recache = false);
    /**
     * Requests an image (skin)
     * @param skin_name filename of the skin image
     * @param recache to recache the image if already cached
     * @return ci::gl::Texture2dRef image
     */
    ci::gl::Texture2dRef& requestImage(const std::string& skin_name, bool recache = false);

    /**
     * Requests audio (song)
     * @param song_name filename of the song
     * @param audio_name filename of the audio file
     * @param recache to recache the audio if already cached
     * @return ci::audio::VoiceRef audio
     */
    ci::audio::VoiceRef& requestAudio(const std::string& song_name, const std::string& audio_name, bool recache = false);
    /**
     * Requests Audio (skin)
     * @param skin_audio_name filename of the skin audio
     * @param recache to recache the audio if already cached
     * @return ci::audio::VoiceRef audio
     */
    ci::audio::VoiceRef& requestAudio(const std::string& skin_audio_name, bool recache = false);

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

    /**
     * Setters
     */
    void setSkin(const std::string& skin_name);
private:
    std::string osu_path_;
    std::string songs_path_;
    std::string skins_path_;
    std::string skin_name_;

    std::map<std::string, ci::gl::Texture2dRef> cached_images_;
    std::map<std::string, ci::audio::VoiceRef> cached_audio_;

    std::vector<std::vector<std::string>> song_list_;
};

}

#endif //OSU_ASSE