/**********************/
/*
*�ļ�˵�������ļ�������Ϸ�����Ƕ��������
*���ߣ���Ǭ
*ʱ�䣺2017-5-29 
*/
/**********************/
#ifndef _PLAYER_H_
#define _PLAYER_H_

#include"cocos2d.h"
#include "BaseDef.h"
#include <string>

class CPlayer :public cocos2d::CCNode
{
public:
	//��ʼ����ɫ
	CPlayer();
	//��ȡ����
	cocos2d::CCSprite* getSprite();
	//�߶�����
	void move(EControlType);
	//ͣ��
	void stop(EControlType);
	//����ը��
	void setBomb();
	//��ɫ����
	void dead();
	//���̿���
	void handleInput(EControlType,EPressState);
//����retain����
	~CPlayer();

private:

	//handleInput�ڵ���,���ڽ��ܰ��µĲ���
	void handleDown(EControlType);
	//handleInput�ڵ���,���ڽ��ܷſ��Ĳ���
	void handleUp(EControlType);
	//�ı�����״̬
	bool changeState(EPlayerLogicState);
	


	int m_iMaxBombNum;//���ը��������
	int m_iSettledBobNum;//�ѷ���ը����
	int m_iBombScale;//ը����Χ
	int m_iSpeed;//�ƶ��ٶ�
	
	/****״̬�����******/
	EPlayerLogicState m_currentState;//��ǰ״̬
	bool m_rgStateTable[EPLS_NUM][EPLS_NUM];//״̬��
	/*************/


	cocos2d::CCSprite* m_pHero;//���Ǿ���ָ��
	cocos2d::CCAnimate* m_pAnimate;//��ǰ����
	cocos2d::CCMoveBy* m_pMoveBy;//��ǰ�ƶ�����

	

};





#endif // !_PLAYER_H_
