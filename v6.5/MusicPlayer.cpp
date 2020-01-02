#include <iostream>
#include "MusicPlayer.h"

using namespace std;

int MusicPlayer::instcnt = 0;

Music::Music(Mix_Music *music)
    : music(music)
{
    refcnt = new int(1);
}

Music::Music(const Music &src)
    : music(src.music), refcnt(src.refcnt)
{
    ++ *refcnt;
}

Music::~Music()
{
    if( -- *refcnt <= 0 )
    {
        if( music )
            Mix_FreeMusic(music);
        delete refcnt;
    }
}

Music& Music::operator=(const Music &src)
{
    if( -- *refcnt <= 0 )
    {
        if( music )
            Mix_FreeMusic(music);
        delete refcnt;
    }

    music = src.music;
    refcnt = src.refcnt;

    ++ *refcnt;

    return *this;
}


MusicPlayer::MusicPlayer()
{
    if( instcnt == 0 )
    {
        OpenDevice();
        ++instcnt;
    }
}

MusicPlayer::MusicPlayer(const MusicPlayer &src)
{
    pool = src.pool;
    ++instcnt;
}

MusicPlayer::~MusicPlayer()
{
    if( --instcnt <= 0 )
        CloseDevice();
}

MusicPlayer& MusicPlayer::operator=(const MusicPlayer &src)
{
    pool = src.pool;
    ++instcnt;

    return *this;
}

void MusicPlayer::OpenDevice()
{
    int requested_flags = MIX_INIT_FLAC | MIX_INIT_OGG | MIX_INIT_MP3;
    int result_flags = Mix_Init(requested_flags);
    if( !result_flags )
        throw runtime_error("SDL mixer initialise failed!");
    else if( result_flags != requested_flags )
        cerr << "WARNING: SDL mixer does not support some of the requested music formats!" << endl;

    if( Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 4096) )
    {
        Mix_Quit();
        throw runtime_error("SDL mixer audio device open failed!");
    }
}

void MusicPlayer::CloseDevice()
{
    Mix_CloseAudio();
    Mix_Quit();
}

Music MusicPlayer::GetMusic(const string &filename)
{
    // Find the music in the resource pool,
    // if found, then return the resource directly.
    auto iter = pool.find(filename);
    if( iter != pool.end() ) return iter->second;

    // If not found, then load it from file and push it to the pool.
    Music music(Mix_LoadMUS(filename.c_str()));
    if( !music )
        throw runtime_error("Load music file \"" + filename + "\" failed!");

    pool[filename] = music;
    return music;
}

void MusicPlayer::Play(const string &filename)
{
    Music music = GetMusic(filename);
    if( 0 > Mix_PlayMusic(music, 0) )
        cerr << "WARNING: Play music \"" << filename << "\" failed!" << endl;
}
