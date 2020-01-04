#ifndef _MUSIC_PLAYER_H_
#define _MUSIC_PLAYER_H_
 
#include <memory>
#include <vector>
#include <map>
#include <SDL2/SDL.h>
 
class MusicPlayer
{
private:
    static int instcnt;
    static SDL_AudioDeviceID devid;
    static std::map< std::string, std::shared_ptr<std::vector<uint8_t> > > sounds;
 
public:
    MusicPlayer();
    MusicPlayer(const MusicPlayer &src);
    ~MusicPlayer();
 
    MusicPlayer& operator=(const MusicPlayer &src);
 
private:
    static std::vector<std::string> GenDeviceListFile();
    static int GetDeviceSelection();
    static std::string GetSelectedDeviceName();
 
    static void OpenDevice();
    static void CloseDevice();
 
    std::shared_ptr<std::vector<uint8_t> > GetMusic(const std::string &filename);
 
public:
    void Play(const std::string &filename);
};
 
#endif
