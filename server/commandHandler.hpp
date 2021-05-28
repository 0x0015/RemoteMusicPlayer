#pragma once
#include <iostream>
#include "bass/bass.h"
#include "getBassError.hpp"
#include "bassJointAudioStream.hpp"
#include "urlEncode.hpp"
#include "filePicker.hpp"

bool stringBeginsWith(std::string s, std::string subs){
	if(s.length() < subs.length()){
		return(false);
	}
	return(s.substr(0, subs.length()) == subs);
}

void handleCommand(std::string c){
	std::string command = urlDecode(c);
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
	}else if(command == "skip"){
		que.skip();
	}else if(stringBeginsWith(command, "navigateDirectory")){
		std::string file = command.substr(17, command.length()-17);
		fileSelect.navigateDirectory(file);
	}else if(stringBeginsWith(command, "addFile")){
		std::string file = command.substr(7, command.length()-7);
		que.addTrack(new mediaFile(file));
	}else{
		std::cout<<"Unknown command!"<<std::endl;
	}
	return;
}
