#pragma once
#include "bass.h"
#include "SoundManager.h"
#include <iostream>
#include "SDL.h"

void SoundManager::init()
{
	if (!BASS_Init(-1, 44100, 0, 0, NULL))
		std::cout << "Can't initialize device";

	 m_sample = new HSAMPLE[m_sizeofArray];

	 //sample[0] = loadSample(filename);
}


HSAMPLE SoundManager::loadSample(char* filename)
{

	if (m_sample[0] = BASS_SampleLoad(FALSE, filename, 0, 0, 3, BASS_SAMPLE_OVER_POS))
		std::cout << "sample " << filename << " loaded!" << std::endl;
	else
	{
		std::cout << "Can't load sample";
		exit(0);
	}
	return m_sample[0];

	// Dont know if this will work for later will need to consult peter - UA
}



void SoundManager::setAttributes(int point,HCHANNEL* ch,int freq, double vol, int panning)
{
	
	BASS_ChannelSetAttribute(ch[point],BASS_ATTRIB_FREQ, freq);
	BASS_ChannelSetAttribute(ch[point], BASS_ATTRIB_VOL, vol);
	BASS_ChannelSetAttribute(ch[point], BASS_ATTRIB_PAN, panning);
	

	
}



void SoundManager::play()
{
	const	Uint8 *keys = SDL_GetKeyboardState(NULL);
	if (keys[SDL_SCANCODE_P]) {
				BASS_Start();
			}
	if (keys[SDL_SCANCODE_S]) {
		BASS_Stop();
	}
}


