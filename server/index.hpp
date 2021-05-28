#pragma once
#include <iostream>
#include <vector>
#include <functional>
#include <unordered_map>
#include "SimpleCppTextFileHandler/file.hpp"

class indexHTMLClass{
public:
	std::unordered_map<std::string, std::function<std::string()>> mapkeys;
	void addMod(std::string key, std::function<std::string()> value){
		mapkeys[key] = value;
	}
	std::string getIndex(){
		std::string text = readFile("index.html");
		for(auto x: mapkeys){
			int keylen = x.first.length();
			for(int i=0;i<text.length()-keylen;i++){
				if(text.substr(i, keylen) == x.first){
					text.replace(i, keylen, x.second());
				}
			}
		}
		return(text);
	}
};
indexHTMLClass indexHTML;
