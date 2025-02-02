#include "songLoader.hpp"

namespace fs = std::filesystem;

songLoader::songLoader(string filepath)
:filepath(filepath){
    updateSongs();
}

songLoader::~songLoader(){
    songs.clear();
}

void songLoader::updateSongs(){
    // We looking for all the beatmaps. Windows path ONLY
    try {
            if (fs::exists(filepath) && fs::is_directory(filepath)) {
                for (const auto& entry : fs::recursive_directory_iterator(filepath)) {
                    if (entry.is_regular_file() && entry.path().extension() == ".mp3") {
                        songs.push_back(entry.path().string());
                    }
                }
            } else {
                std::cerr << "Invalid directory path: " << filepath << std::endl;
            }
        } catch (const fs::filesystem_error& e) {
            std::cerr << "Filesystem error: " << e.what() << std::endl;
    }

}

void songLoader::debugSongs(){
    cout << "Liste des musiques actuelles : " << endl;
    for (string str : songs){
        cout << str << endl;
    }
}

void songLoader::listenSong(size_t index){
    if (index < 0 || index >= songs.size()){
        std::cerr << "Invalid Song Index, cannot play the song" << endl;
        return;
    }
    if (!currentSong.openFromFile(songs[index])){
        std::cerr << "Error SFML : Cannot open the .mp3 file " << songs[index] << endl;
        return;
    }

    cout << "Now playing : " << getSongName(songs[index]) << endl;
    currentSong.play();

    
}