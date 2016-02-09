#ifndef __PLAY_SCENE_H__
#define __PLAY_SCENE_H__

#include"cocos2d.h"
USING_NS_CC;

class PlayScene :Layer
{
public:
	static Scene* createScene();
	virtual bool init();
	static float myRandom();
	bool isLoseGame();
	void createMenu();
	void startGame(Ref *pSender);
	void scoreMenu(Ref * pSender);
	
	virtual bool onTouchBegan(Touch * touch, Event * event);
	virtual void onTouchMoved(Touch * touch, Event * event);
	virtual void onTouchEnded(Touch * touch, Event * event);

	void update(float delay);

	virtual void onExit();

	CREATE_FUNC(PlayScene)
private:
	Sprite * bird;
	Sprite * ground1;
	Sprite * ground2;
	Sprite * pipe1;
	Sprite * pipe2;
	Sprite * pipe3;
	Sprite * pipe4;
	Size visibleSize;
	Sprite * startGameTeach;

	bool getScoreFlag;
	int currentScore;
	Label *score;
};

#endif
