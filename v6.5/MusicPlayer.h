#ifndef _MUSIC_PLAYER_H_
#define _MUSIC_PLAYER_H_

#include <memory>
#include <map>
#include <SDL_mixer.h>

class Music
{
private:
    Mix_Music *music;
    int *refcnt;

public:
    Music(Mix_Music *music = NULL);
    Music(const Music &src);
    ~Music();

    Music& operator=(const Music &src);

public:
    operator Mix_Music*() { return music; }
    operator bool() const { return !!music; }
};

class MusicPlayer
{
private:
    static int instcnt;
    std::map<std::string, Music> pool;

public:
    MusicPlayer();
    MusicPlayer(const MusicPlayer &src);
    ~MusicPlayer();

    MusicPlayer& operator=(const MusicPlayer &src);

private:
    static void OpenDevice();
    static void CloseDevice();

    Music GetMusic(const std::string &filename);

public:
    void Play(const std::string &filename);
};

#endif
