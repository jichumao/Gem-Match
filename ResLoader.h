#pragma once
#include "common.h"
#include <map>

// 音频类型
enum class MusicType
{
	//各种声音
	Click

};

//资源管理工具
class ResLoader
{
public:
	//预加载图片
	static void init();

	//获取图片
	static Image* getImage(String imagename);

	//播放音频
	static void playMusic(MusicType musicType);

private:
	//图片映射
	static std::map<String, Image*> imageMap;
	//音频映射
	static std::map<MusicType, Music*> musicMap;
};

