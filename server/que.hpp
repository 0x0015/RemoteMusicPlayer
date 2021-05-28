#pragma once
#include <iostream>
#include "mediaTypes/mediaType.hpp"
#include "mediaTypes/file.hpp"
#include <vector>
#include "bassJointAudioStream.hpp"
#include <unistd.h>
//#include <chrono>

class audioQue{
public:
	std::vector<mediaType*> media;//item 0 is the next song
	std::vector<mediaType*> backlist;//item 0 was the song that was played first(the last item is the song that was played last)
	mediaType* playing = 0;//the currently playing song
	void play(){
		if(playing == 0){
			return;
		}
		auto activity = BASS_ChannelIsActive(stream);
		if(activity == BASS_ACTIVE_PLAYING){
			return;
		}
		BASS_ChannelPlay(stream, false);
		//playing->play();		
	}
	void stop(){
		if(playing == 0){
			return;
		}
		auto activity = BASS_ChannelIsActive(stream);
		if(activity == BASS_ACTIVE_PAUSED){
			return;
		}
		BASS_ChannelPause(stream);
	}
	void skip(){
		if(playing == 0){
			return;
		}
		backlist.push_back(playing);
		if(media.size() < 1){
			playing = 0;
			return;
		}
		playing = media[0];
		media.erase(media.begin());
		playing->initialize();
		playing->load();
		BASS_ChannelPlay(stream, false);
		//playing->play();
	}
	void update(){
		//auto positionBytes = BASS_ChannelGetPosition(stream, BASS_POS_BYTE);
		//double position = BASS_ChannelBytes2Seconds(stream, positionBytes);
		auto activity = BASS_ChannelIsActive(stream);
		if(activity == BASS_ACTIVE_STOPPED){
			if(playing != 0){
				backlist.push_back(playing);
			}
			if(media.size() < 1){
				playing = 0;
				return;
			}
			playing = media[0];
			media.erase(media.begin());
			playing->initialize();
			playing->load();
			BASS_ChannelPlay(stream, false);
		}
	}
	void addTrack(mediaType* track){
		media.push_back(track);
	}
	void insertTrack(mediaType* track, int position){
		media.insert(media.begin()+position, track);
	}
	audioQue(){

	}
};

audioQue que;

void queUpdate(bool* running){
	while(*running){
		std::cout<<"update"<<std::endl;
		que.update();
		unsigned int microsecond = 1000000;
		usleep(microsecond/8);		
	}
}
