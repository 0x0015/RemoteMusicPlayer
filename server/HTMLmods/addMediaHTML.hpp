#pragma once
#include <iostream>
//#include "../que.hpp"
#include "../index.hpp"
#include "../filePicker.hpp"
#include "../urlEncode.hpp"

void addSelectHtmlMod(){
	std::function<std::string()> selectionCode = [](){
		std::string output = "<p>Add Files:</p>";
		output += fileSelect.currentDirectory + "<br>";
		std::vector<std::string> dirs = fileSelect.getDirsInDirectory();
		std::vector<std::string> files = fileSelect.getFilesInDirectory();
		for(int i=0;i<dirs.size();i++){
			output += "<a href='cmd=navigateDirectory" + urlEncode(dirs[i]) + "'>" + dirs[i] + "</a><br>";
		}
		for(int i=0;i<files.size();i++){
			output += "<a href='cmd=addFile" + urlEncode(fileSelect.currentDirectory + "/" + files[i]) + "'>" + files[i] + "</a><br>";
		}
		output += "<a href='cmd=navigateDirectory..'>..</a><br>";
		return(output);
	};
	indexHTML.addMod("(!SELECT!)", selectionCode);
}
