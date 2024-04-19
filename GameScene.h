#pragma once
#include <easy2d/easy2d.h>
#include "GameTask.h"
#include "HintButton.h"
#include "ScoreBoard.h"
#include "WashButton.h"
#include "GameStatus.h"
#include "Jewel.h"
#include <mutex>
using namespace easy2d;

enum class Mode {
	Classic,
	Fast
};

class GameScene :
	public Scene
{
public:
	//Ĭ�Ϲ��캯��
	GameScene();
	//���캯����ָ����Ϸ�ؿ�����Ϸģʽ
	GameScene(int l, Mode mode = Mode::Classic);
	//��֡��ˢ����Ϸ�����������������Ϸ�߼���������Ӧ�Ķ���
	void onUpdate() override;
	//����/�ָ�����Button
	static void SetBtnEnabled(bool status);
	//��Ϸģʽ
	Mode game_mode;
	//����
	int steps;
	//#############################################################
	//����ģʽ��Ҫ������
	// ��ʼ��ʱ����
	void startTiming();
	// ������ʱ����
	void endTiming();
	//����Ϸ��ͣʱ���ã���ͣ��ʱ
	void pauseTiming();
	//����Ϸ�ָ�ʱ���ã��ָ���ʱ
	void resumeTiming();
	// ��ʱ����
	void timing();
	//������ʾ��ʣʱ��ĺ���
	void setTimeLastSeconds(int seconds);
	//���Ӵ�����ͣ�İ�ť�ĺ���
	void addPauseBtn();
	//��¼��ʱ�Ƿ�ʼ/����������
	//��ʼΪtrue
	bool _timingStarted = false;
	//��¼��ʱ�Ƿ���ͣ������
	//��ͣΪtrue
	bool _timingPaused = false;
	//��¼��ǰ��ʣʱ������ԣ���ʼ״̬Ϊ100s
	int _timeLast = 100;
	//��ʾʱ����ı���
	Text* _timeLastText = nullptr;
	Text* _stepText = nullptr;
	

	~GameScene();
	//����ѡ�����ʱ��Ҫ�ĺ���
	static int get_selected_jewels_numbers();
	static void add_selected_jewels_numbers();
	static void init_selected_jewels_numbers();
	static void minu_selected_jewels_numbers();
	//�洢��ʯ����������
	static Jewel* map[8][8];
	//�ж�onupdate��Сtrick
	static bool canResume;
	//��Ϸ�߼�����ʵ��
	GameTask* gt;
	//��Ϸ״̬����ʵ��
	GameStatus* gst;
	//��ʾ��ť
	HintButton* hint_btn;
	//������
	ScoreBoard* score_board;
	//�����˵�
	//SubMenu* submenu;
	//����ϴ�Ƶĺ���
	void WashJews();
	
protected:
	//����ѡ��ʯ��Ŀ�ľ�̬����
	static int selected_jewels_numbers;
	//˽�к����������ڹ��캯���г�ʼ����������
	void Initialize();
};

