#pragma once
#include "bass/bass.h"
#include "getBassError.hpp"

void loadPlugins(){
#if defined( _WIN32) || defined(_WIN64) // Windows/CE
    std::cout<<"Loading plugin: bassflac.dll"<<std::endl;
    BASS_PluginLoad("bassflac.dll", 0);
    getBassError();
#else // Linux
    std::cout<<"Loading plugin:  libbassflac.so"<<std::endl;
    BASS_PluginLoad("libbassflac.so", 0);
    getBassError();
#endif

}
