#include "DS14_3D_Audio.h"
#include <iostream>

void DS14_3D_Music::FileLoadIn(std::string& strFileName)
{
	strMusicName = strFileName;
	pMusic_mp3 = Mix_LoadMUS(strMusicName.c_str());
	if (pMusic_mp3 == NULL)
	{
		std::cout << "ERROR: " << Mix_GetError() << std::endl;
	}
	return ;
}

void DS14_3D_Music::Play(int iLoops /* = -1 */)
{
	Mix_PlayMusic(pMusic_mp3, iLoops);
	return ;
}

void DS14_3D_Music::Halt()
{
	Mix_HaltMusic();
	return ;
}

void DS14_3D_Music::Pause()
{
	Mix_PauseMusic();
	return ;
}

void DS14_3D_Music::Continue()
{
	Mix_ResumeMusic();
	return ;
}

void DS14_3D_Chunk::FileLoadIn(std::string& strFileName)
{
	strChunkName = strFileName;
	pChunk_wav = Mix_LoadWAV(strChunkName.c_str());
	if (pChunk_wav == NULL)
	{
		std::cout << "ERROR: " << Mix_GetError() << std::endl;
	}
	return ;
}

void DS14_3D_Chunk::Play(int iLoops /* = 1 */)
{
	Mix_PlayChannel(-1,pChunk_wav,iLoops);
	return ;
}

void DS14_3D_Audio::MusicLoadIn(std::string& strMusicName)
{
	Music.FileLoadIn(strMusicName);
	return;
}

void DS14_3D_Audio::ChunkListLoadIn(std::list<std::string> & FileNameList)
{
	for (std::list<std::string>::iterator iter_string = FileNameList.begin();iter_string != FileNameList.end();iter_string ++)
	{
		DS14_3D_Chunk Chunktemp;
		Chunktemp.FileLoadIn(*iter_string);
		ChunkList.push_back(Chunktemp);
	}
	return ;
}

void DS14_3D_Audio::DS14_3D_MusicOperate(int iOperation)
{
	switch (iOperation)
	{
	case 1:
		Music.Play();
		break;
	case 2:
		Music.Pause();
		break;
	case 3:
		Music.Continue();
		break;
	case 4:
		Music.Halt();
		break;
	default:
		std::cout << "Invalid Operation Number" << std::endl;
	}
	return ;
}

void DS14_3D_Audio::DS14_3D_ChunkPlay(int iChunk,int iLoop)
{
	if (iChunk > ChunkList.size())
	{
		std::cout << "Invalid Chunk Number" << std::endl;
		return;
	}
	std::list<DS14_3D_Chunk>::iterator iterChunk = ChunkList.begin();
	iChunk--;
	while (iChunk)
		iterChunk ++;
	iterChunk->Play(iLoop);
	return ;
}