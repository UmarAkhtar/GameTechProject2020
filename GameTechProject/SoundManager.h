#ifndef SOUNDMANAGER_H
#define SOUNDMANAGER_H
#include "bass.h"
#include <iostream>

class SoundManager
{
private:
		HSAMPLE *m_sample = NULL;
		int m_sizeofArray;
		HCHANNEL* m_ch = NULL;
		
public:
	SoundManager(int m_sizeofArray) : m_sizeofArray(m_sizeofArray) {};
	virtual ~SoundManager() {};


	HSAMPLE loadSample(char* filename);
	void init();
	void setAttributes(int point, HCHANNEL* ch, int freq, double vol, int panning);
	void Load(int point);
	void play();
};
#endif // !SOUNDMANAGER_H