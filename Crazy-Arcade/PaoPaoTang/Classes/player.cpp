/**********************/
/*
*�ļ�˵�������ļ�������Ϸ�����Ƕ���Ķ���
*���ߣ���Ǭ
*ʱ�䣺2017-5-29
*/
/**********************/

#include "player.h"
using namespace cocos2d;


CPlayer::CPlayer():
	m_iMaxBombNum(1),
	m_iSettledBobNum(0),
	m_iBombScale(1),
	m_iSpeed(2),
	m_pHero(NULL),
	m_pAnimate(NULL),
	m_currentState(EPLS_STAND)
{
	
	CCSize size = CCDirector::sharedDirector()->getWinSize();
	m_pHero = CCSprite::create("Pic/Role1.png", CCRectMake(0, 256 / 4, 288 / 6, 256 / 4));
	m_pHero->retain();
	m_pHero->setPosition(ccp(size.width / 2, size.height / 2));

	/******״̬�����******/
	for (int i = 0; i < EPLS_NUM; i++)
		for (int j = 0; j < EPLS_NUM; j++)
			m_rgStateTable[i][j] = 0;

	m_rgStateTable[EPLS_STAND][EPLS_MOVE] = 1;
	m_rgStateTable[EPLS_MOVE][EPLS_STAND] = 1;
	m_rgStateTable[EPLS_PAOPAO][EPLS_MOVE] = 1;
	m_rgStateTable[EPLS_PAOPAO][EPLS_STAND] = 1;
	m_rgStateTable[EPLS_DEAD][EPLS_PAOPAO] = 1;

	
	
}

CCSprite * CPlayer::getSprite()
{
	return m_pHero;
}

void CPlayer::move(EControlType eCtrlType)
{
	if (!changeState(EPLS_MOVE))
		return;

	std::string aniName = ROLE;
	char order = '0' + eCtrlType;
	aniName += order;
	m_pAnimate = CCAnimate::create(CCAnimationCache::sharedAnimationCache()->animationByName(aniName.c_str()));
	m_pHero->runAction(m_pAnimate);

	int dir[EPLS_NUM][2] = { {0,1},{0,-1},{-1,0},{1,0} };
	m_pMoveBy = CCMoveBy::create(m_iSpeed, ccp(dir[eCtrlType][0] * FRAME_WIDTH, dir[eCtrlType][1] * FRAME_HEIGHT));
	m_pHero->runAction(m_pMoveBy);
}

void CPlayer::stop(EControlType eCtrlType)
{
	if (!changeState(EPLS_STAND))
		return;

	m_pHero->stopAction(m_pAnimate);
	m_pHero->setTextureRect(CCRectMake(0 * 288 / 6, eCtrlType * 256 / 4, 288 / 6, 256 / 4));
	m_pHero->stopAction(m_pMoveBy);
}

void CPlayer::handleInput(EControlType eCtrlType, EPressState ePrsState)
{
	switch (ePrsState)
	{
	case EPS_DOWN:
		handleDown(eCtrlType);
		break;
	case EPS_UP:
		handleUp(eCtrlType);
		break;
	default:
		return;
	}
}

void CPlayer::handleDown(EControlType eCtrlType)
{

	switch (eCtrlType)
	{
	case ECT_UP:
		move(eCtrlType);
		break;
	case ECT_DOWN:
		move(eCtrlType);
		break;
	case ECT_LEFT:
		move(eCtrlType);
		break;
	case ECT_RIGHT:
		move(eCtrlType);
		break;
	
	}
}

void CPlayer::handleUp(EControlType eCtrlType)
{

	switch (eCtrlType)
	{
	case ECT_UP:
		stop(eCtrlType);
		break;
	case ECT_DOWN:
		stop(eCtrlType);
		break;
	case ECT_LEFT:
		stop(eCtrlType);
		break;
	case ECT_RIGHT:
		stop(eCtrlType);
		break;

	}
}

bool CPlayer::changeState(EPlayerLogicState toState)
{
	if(!m_rgStateTable[toState][m_currentState])
	return false;

	m_currentState = toState;
	return true;
}

CPlayer::~CPlayer()
{
	m_pHero->release();
}
