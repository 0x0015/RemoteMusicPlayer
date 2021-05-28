#pragma once
#include <iostream>
#include "../bass/bass.h"
#include "../bassJointAudioStream.hpp"

class mediaType{
public:
	std::string name;
	std::string artist;
	virtual void load(){}
	virtual void initialize(){}
	mediaType(){}
	mediaType(std::string n){
		name = n;
	}
};
