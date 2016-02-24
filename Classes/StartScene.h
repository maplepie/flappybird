#ifndef __START_SCENE_H__
#define __START_SCENE_H__

#include "cocos2d.h"
#include "BaseLayer.h"
USING_NS_CC;

class StartScene: BaseLayer
{
public:
	static Scene * createScene();
	virtual bool init();

	void startGame(Ref *pSender);
	void scoreMenu(Ref * pSender);

	CREATE_FUNC(StartScene);
};

#endif
