#include "libhttpserver/src/libhttpserver/libhttpserver.h"
//using rs::httpserver;
#include "bass/bass.h"
#include <iostream>
#include <thread>
#include <boost/chrono.hpp>
#include "commandHandler.hpp"
#include "bassPlugins.hpp"
#include "bassJointAudioStream.hpp"
#include "index.hpp"

bool running;
std::thread updateThread;

int main() {
    BASS_Init(-1, 44100, 0, 0, 0);
    loadPlugins();
    que = audioQue();
    que.addTrack(new mediaFile("V01D.mp3"));
    running = true;
    updateThread = std::thread(queUpdate, &running);
    //HSTREAM stream;
    // create the server object
    auto server = rs::httpserver::HttpServer::Create("0.0.0.0", 10024);
    
    // create a router
    auto router = rs::httpserver::RequestRouter();
    
    // if the client asks for / then redirect
    router.Add("GET", "/", [](rs::httpserver::request_ptr, const rs::httpserver::RequestRouter::CallbackArgs&, rs::httpserver::response_ptr response) {
	std::cout<<"got base path, redirecting to index"<<std::endl;
        response->Redirect("/index.html");
        return true;
    });

    router.Add("GET", "/index.html", [](rs::httpserver::request_ptr, const rs::httpserver::RequestRouter::CallbackArgs&, rs::httpserver::response_ptr response) {
        auto& stream = response->setContentType("text/html").getResponseStream();
	std::string fileContents = getIndex();
        char* lorem = new char[fileContents.length() + 1];
	strcpy(lorem, fileContents.c_str());
	lorem[fileContents.length()+1] = 0;
        stream.Write(reinterpret_cast<rs::httpserver::Stream::byte*>(lorem), 0, fileContents.length());
        stream.Flush();
	delete(lorem);
        return true;
    });
    
    // if the client asks for /image= then respond with the image if we find it
    router.Add("GET", R"(/cmd=(?<command>.*))", [](rs::httpserver::request_ptr request, const rs::httpserver::RequestRouter::CallbackArgs& args, rs::httpserver::response_ptr response) {
        auto filename = args.find("command");
        std::string uri(""); uri += filename->second;
	//std::cout<<"recieved cmd of " + uri<<std::endl;
	response->Redirect("/index.html");
	if(uri == "exit"){
		//exit the server
		std::cout<<"User exited."<<std::endl;
		running = false;
		updateThread.join();
		BASS_Free();
		exit(0);
	}else{
		//std::thread commandThread = std::thread(handleCommand, uri, &stream);
		handleCommand(uri);
	}
        
        return true;
    });

auto defaultHandler = [](rs::httpserver::socket_ptr socket, rs::httpserver::request_ptr request, rs::httpserver::response_ptr response) {
	std::cout<<"got default handler, redirecting to index"<<std::endl;
        response->Redirect("/index.html");
};    
    
    server->Start(router, defaultHandler);
    running = false;
    updateThread.join();
    BASS_Free();
    return 0;
}

