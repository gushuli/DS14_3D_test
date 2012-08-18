#ifndef DS14_3D_AUDIO_H
#define DS14_3D_AUDIO_H
#include <SDL/SDL_mixer.h>
#include <list>
#include <string>

class AudioOperation
{
public:
	AudioOperation(){}
	~AudioOperation(){}

	virtual void FileLoadIn(std::string& strFileName) =0;
	
	virtual void Play(int iLoops) =0;

protected:
private:
	
};

class DS14_3D_Music:public AudioOperation
{
public:
	DS14_3D_Music(){}
	~DS14_3D_Music(){}


	virtual void FileLoadIn(std::string& strFileName) ;

	virtual void Play(int iLoops = -1);
	void Pause();
	void Continue();
	void Halt();

	std::string strMusicName;
	Mix_Music* pMusic_mp3;
protected:
private:


};

class DS14_3D_Chunk : public AudioOperation
{
public:
	DS14_3D_Chunk(){}
	~DS14_3D_Chunk(){}

	virtual void FileLoadIn(std::string& strFileName);
	virtual void Play(int iLoops = 1);

	std::string strChunkName;
	Mix_Chunk* pChunk_wav;
protected:
private:

};

class DS14_3D_Audio
{
public:
	DS14_3D_Audio(){}
	~DS14_3D_Audio(){}

	void MusicLoadIn(std::string& strMusicName);
	void ChunkListLoadIn(std::list<std::string> & FileNameList);

	void DS14_3D_MusicOperate(int iOperation);
	void DS14_3D_ChunkPlay(int iChunk ,int iLoop);


	DS14_3D_Music Music;
	std::list<DS14_3D_Chunk> ChunkList;
protected:
private:

};

#endif