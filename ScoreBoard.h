#pragma once
#include "QNumber.h"
#define BITSNUM 6

class ScoreBoard:
	public Node
{
public:
	QNumber* score_bits[BITSNUM];//�Ʒְ���ʱ��Ϊ��λ��
	ScoreBoard();
	~ScoreBoard();
	//�����¾ɷ������¼Ʒְ���ʾ
	void UpdateBoard(int old_score, int new_score);
};

