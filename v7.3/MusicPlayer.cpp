#include <iostream>
#include <fstream>
#include "MusicPlayer.h"
 
using namespace std;
 
int MusicPlayer::instcnt = 0;
SDL_AudioDeviceID MusicPlayer::devid = 0;
std::map< std::string, std::shared_ptr<std::vector<uint8_t> > > MusicPlayer::sounds;
 
MusicPlayer::MusicPlayer()
{
    if( instcnt == 0 )
    {
        OpenDevice();
        ++instcnt;
    }
    else
    {
        ++instcnt;
    }
}
 
MusicPlayer::MusicPlayer(const MusicPlayer &src)
{
    ++instcnt;
}
 
MusicPlayer::~MusicPlayer()
{
    if( --instcnt <= 0 )
        CloseDevice();
}
 
MusicPlayer& MusicPlayer::operator=(const MusicPlayer &src)
{
    ++instcnt;
    return *this;
}
 
vector<string> MusicPlayer::GenDeviceListFile()
{
    fstream file("audio-device-list", ios::out);
    if( !file.is_open() )
        throw runtime_error("Create file \"audio-device-list\" failed!");
 
    vector<string> devlist;
 
    int devnum = SDL_GetNumAudioDevices(false);
    for(int i = 0; i < devnum; ++i)
    {
        const char *devname = SDL_GetAudioDeviceName(i, false);
        file << i << ": \"" << devname << "\"" << endl;
        devlist.push_back(devname);
    }
 
    return devlist;
}
 
int MusicPlayer::GetDeviceSelection()
{
    fstream file("audio-device-selection", ios::in);
    if( !file.is_open() )
    {
        cerr << "WARNING: Load file \"audio-device-selection\" failed!" << endl;
        return 0;
    }
 
    int value;
    file >> value;
 
    return file.fail() ? 0 : value;
}
 
string MusicPlayer::GetSelectedDeviceName()
{
    vector<string> devlist = GenDeviceListFile();
    if( !devlist.size() )
        throw runtime_error("No audio device be found!");
 
    unsigned index = GetDeviceSelection();
    if( index >= devlist.size() )
        index = 0;
 
    return devlist[index];
}
 
void MusicPlayer::OpenDevice()
{
    static const SDL_AudioSpec spec_wanted =
    {
        .freq       = 44100,
        .format     = AUDIO_S16LSB,
        .channels   = 1,
        .silence    = 0,
        .samples    = 4096,
    };
 
    SDL_AudioSpec spec_got;
 
    string devname = GetSelectedDeviceName();
    devid = SDL_OpenAudioDevice(devname.c_str(), false, &spec_wanted, &spec_got, false);
    if( !devid ) throw runtime_error("Open audio device (" + devname + ") failed!");
 
    SDL_PauseAudioDevice(devid, false);
}
 
void MusicPlayer::CloseDevice()
{
    if( devid )
        SDL_CloseAudioDevice(devid);
}
 
shared_ptr<vector<uint8_t> > MusicPlayer::GetMusic(const string &filename)
{
    // Find the music in the resource pool,
    // if found, then return the resource directly.
    auto iter = sounds.find(filename);
    if( iter != sounds.end() ) return iter->second;
 
    // If not found, then load it from file and push to the pool.
 
    SDL_AudioSpec spec;
    Uint8 *buf;
    Uint32 len;
    if( !SDL_LoadWAV(filename.c_str(), &spec, &buf, &len) )
        throw runtime_error("Load music file \"" + filename + "\" failed!");
 
    shared_ptr<vector<uint8_t> > sample(new vector<uint8_t>(len));
    memcpy(sample->data(), buf, len);
    sounds[filename] = sample;
 
    SDL_FreeWAV(buf);
 
    return sample;
}
 
void MusicPlayer::Play(const string &filename)
{
    auto sample = GetMusic(filename);
 
    SDL_ClearQueuedAudio(devid);
    if( SDL_QueueAudio(devid, sample->data(), sample->size()) )
        cerr << "WARNING: Play music \"" << filename << "\" failed!" << endl;
}
