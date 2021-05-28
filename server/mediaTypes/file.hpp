#pragma once
#include <iostream>
#include "../bass/bass.h"
#include "../bassJointAudioStream.hpp"

class mediaFile : public mediaType{
public:
	std::string filename;
	void load(){

	}
	void initialize(){
		stream = BASS_StreamCreateFile(false, (void*)(filename.c_str()),0,0,BASS_STREAM_AUTOFREE);
	}
	mediaFile(){}
	mediaFile(std::string f){
		filename = f;
		name = f;
	}
};
