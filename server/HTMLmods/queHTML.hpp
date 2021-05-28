#pragma once
#include <iostream>
#include "../que.hpp"
#include "../index.hpp"

void addQueHtmlMod(){
	std::function<std::string()> queCode = [](){
		std::string output = "<p>Playing:  ";
		std::cout<<que.playing<<std::endl;
		if(que.playing != 0){
			output += que.playing->name + "</p>";
		}else{
			output += "Not currently playing</p>";
		}
		output += "<p>QUE:</p>";
		for(int i=0;i<que.media.size();i++){
			output += "<p>" + std::to_string(i) + "  " + que.media[i]->name + "</p>";
		}
		if(que.media.size() == 0){
			output += "<p>No songs currently in que</p>";
		}
		return(output);
	};
	indexHTML.addMod("(!QUE!)", queCode);
}
