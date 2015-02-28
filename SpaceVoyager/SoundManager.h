
#ifndef _soundManager_
#define _soundManager_


#include "SoundData.h"


class SoundManager
{


private:
	std::vector<SoundData*> _trackList;
	ISoundEngine* engine2D;

public:
	SoundManager();
	~SoundManager();

	int findBySoundConst(soundConstant sc);
	
	void addCurrentPlayList(const char* name , bool l , soundConstant sc);

	void startPlayList();


	void resumeFromPlayList(soundConstant sc);

	void removeFromPlayList(soundConstant sc);
	void pauseFromPlayList(soundConstant sc);

	void setVolFromPlayList(soundConstant sc , int vol);

	void dropAll();

};

#endif