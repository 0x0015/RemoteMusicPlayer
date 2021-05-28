#pragma once
#include <iostream>
#include "SimpleCppTextFileHandler/file.hpp"

std::string getIndex(){
	std::string text = readFile("index.html");
	return(text);
}
