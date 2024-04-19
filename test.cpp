#include "Jewel.h"
#include "GameScene.h"
#include "GameLogic.h"
#include <vector>
using namespace std;


int main()
{
	if (Game::init(L"Demo1", 1024, 640))
	{
		// �޸Ľڵ�Ĭ�����ĵ㣬������ͼƬ������ʾ
		Node::setDefaultAnchor(0.5f, 0.5f);
		//�������棨Ĭ��Ϊ��һ�أ�
		auto scene = new GameScene(1, Mode::Fast);
		SceneManager::enter(scene);

		
		Game::start();
	}
	Game::destroy();
	return 0;
}