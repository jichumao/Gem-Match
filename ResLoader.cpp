#pragma once
#include "ResLoader.h"
#include "resource.h"

std::map<String, Image*> ResLoader::imageMap;
std::map<MusicType, Music*> ResLoader::musicMap;

void ResLoader::init()
{
	// 预加载图片
	//1.开始界面图片
	Image::preload(L"res\\StartScene.png");
	Image* startScene = new Image(L"res\\StartScene.png");
	//2.游戏标题
	Image::preload(L"res\\MainTopic.png");
	Image* mainTopic = new Image(L"res\\MainTopic.png");
	//3.开始按钮正常状态
	Image::preload(L"res\\StartGame.png");
	Image* startGame = new Image(L"res\\StartGame.png");
	//4. 模式选择界面图片
	Image::preload(L"res\\PatternScene.png");
	Image* patternScene = new Image(L"res\\PatternScene.png");
	////5.停止播放音乐按钮正常状态
	//Image::preload(L"res\\soundoff.png");
	//Image* stopMusic = new Image(L"res\\soundoff.png");
	//6.加载背景音乐
	// 循环播放背景音乐，-1 表示循环播放
	MusicPlayer::preload(L"res\\background.wav");
	MusicPlayer::play(L"res\\background.wav", -1);
	//7.返回上一个界面按钮
	Image::preload(L"res\\ReturnScene.png");
	Image* returnScene = new Image(L"res\\ReturnScene.png");
	//8. 经典模式背景
	Image::preload(L"res\\BG03.png");
	Image* classicScene = new Image(L"res\\BG03.png");
	//9. 排行榜按钮
	Image::preload(L"res\\rankBtn.png");
	Image* rankBtn = new Image(L"res\\rankBtn.png");
	//10.设置按钮
	Image::preload(L"res\\setBtn.png");
	Image* setBtn = new Image(L"res\\setBtn.png");

	// 保存到映射
	imageMap.insert(std::make_pair(L"StartScene", startScene));
	imageMap.insert(std::make_pair(L"MainTopic", mainTopic));
	imageMap.insert(std::make_pair(L"StartGame", startGame));
	imageMap.insert(std::make_pair(L"Pattern", patternScene));
	/*imageMap.insert(std::make_pair(L"StopMusic", stopMusic));*/
	imageMap.insert(std::make_pair(L"ReturnScene", returnScene));
	imageMap.insert(std::make_pair(L"ClassicScene", classicScene));
	imageMap.insert(std::make_pair(L"RankBtn", rankBtn));
	imageMap.insert(std::make_pair(L"SetBtn", setBtn));
}

Image* ResLoader::getImage(String imageName)
{
	auto iter = imageMap.find(imageName);
	if (iter == imageMap.end())
	{
		return nullptr;
	}
	return iter->second;
}

void ResLoader::playMusic(MusicType musicType)
{
	Music* music = musicMap[musicType];
	if (music)
	{
		music->play();
	}
}
