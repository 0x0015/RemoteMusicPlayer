#pragma once
#include <iostream>
#include <filesystem>
#include <string>
#include <vector>
#include "SimpleCppTextFileHandler/file.hpp"

class filePicker{
public:
	std::string currentDirectory = ".";
	void navigateDirectory(std::string directory){
		if(directory == "" || directory == "."){
			return;
		}
		auto newPath = std::filesystem::path(currentDirectory) / directory;
		std::filesystem::path normalPath = newPath.lexically_normal();
		currentDirectory = normalPath.string();
	}
	void resetDirector(){
		currentDirectory = getCWD();
	}
	std::vector<std::string> getFilesInDirectory(){
		std::vector<std::string> files;
		for (const auto & entry : std::filesystem::directory_iterator(currentDirectory)){
        		//std::cout << entry.path() << std::endl;
			if(!entry.is_directory()){
				std::string p = entry.path();
				if(p.length() > currentDirectory.length()){
					if(p.substr(0, currentDirectory.length()) == currentDirectory){
						p.erase(0,currentDirectory.length());
					}
				}
				if(p.substr(0,1) == "/"){
					p.erase(0,1);
				}
				files.push_back(p);
			}
		}
		return(files);
	}
	std::vector<std::string> getDirsInDirectory(){
		std::vector<std::string> files;
		for (const auto & entry : std::filesystem::directory_iterator(currentDirectory)){
        		//std::cout << entry.path() << std::endl;
			if(entry.is_directory()){
				std::string p = entry.path();
				if(p.length() > currentDirectory.length()){
					if(p.substr(0, currentDirectory.length()) == currentDirectory){
						p.erase(0,currentDirectory.length());
					}
				}
				if(p.substr(0,1) == "/"){
					p.erase(0,1);
				}
				files.push_back(p);
			}
		}
		return(files);
	}
};

filePicker fileSelect;
