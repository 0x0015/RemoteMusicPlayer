#pragma once
#include <iostream>
#include "bass/bass.h"

int getBassError(){
	int error = BASS_ErrorGetCode();
	if(error == 0){
		return(0);
	}else{
		std::cout<<"Got bass error:  "<<error<<std::endl;
		return(error);
	}
	return(error);
}
