#include "libhttpserver/src/libhttpserver/libhttpserver.h"
//using rs::httpserver;
#include "bass/bass.h"
/*
int main() {
	BASS_Init(-1, 44100, 0, 0, 0);
	HSTREAM stream;
	auto server = rs::httpserver::HttpServer::Create("0.0.0.0", 1080);
	auto func = [stream](rs::httpserver::socket_ptr socket, rs::httpserver::request_ptr request, rs::httpserver::response_ptr response) mutable {
		stream = BASS_StreamCreateFile(false, (void*)"test.wav", 0, 0, BASS_STREAM_AUTOFREE);
		BASS_ChannelPlay(stream, true);
		response->setContentType("text/html").Send("<html><body><h1>Hello from libhttpserver</h1></body></html>");
	};
	server->Start(func);
	
}
*/
#include <iostream>
#include <thread>
#include <boost/chrono.hpp>
#include "commandHandler.hpp"
#include "bassPlugins.hpp"
#include "bassJointAudioStream.hpp"
//#include "libhttpserver/src/libhttpserver/libhttpserver.h"

int main() {
    BASS_Init(-1, 44100, 0, 0, 0);
    loadPlugins();
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
        char lorem[] = "<html><body>This file here is index.html<br><a href='cmd=play'>play</a><br><a href='cmd=stop'>stop</a><br><a href='cmd=exit'>exit</a></body></html>";
        stream.Write(reinterpret_cast<rs::httpserver::Stream::byte*>(lorem), 0, sizeof(lorem));
        stream.Flush();
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
      
    BASS_Free();
    return 0;
}

