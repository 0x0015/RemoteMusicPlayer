#pragma once
#include <iostream>
#include "bass/bass.h"
#include "getBassError.hpp"
#include "bassJointAudioStream.hpp"

void handleCommand(std::string command){
	if(command == "play"){
		std::cout<<"playing";
		//stream = BASS_StreamCreateFile(false, (void*)"test.wav", 0, 0, BASS_STREAM_AUTOFREE);
		//getBassError();
		//BASS_ChannelPlay(stream, false);
		//getBassError();
		que.play();
		std::cout<<" on channel "<<stream<<std::endl;
	}else if(command == "stop"){
		std::cout<<"stoping stream "<<stream<<std::endl;
		//BASS_ChannelPause(stream);
		//getBassError();
		que.stop();
	}else{
		std::cout<<"Unknown command!"<<std::endl;
	}
	return;
}
