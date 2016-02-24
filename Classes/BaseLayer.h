#ifndef __BASE_LAYER_H__
#define __BASE_LAYER_H__

#include "cocos2d.h"
USING_NS_CC;


class BaseLayer : public Layer
{
public:

	virtual bool init();
//	static Scene * createScene(BaseLayer *baseLayer);

	CREATE_FUNC(BaseLayer);
protected:
	Size visibleSize;
	Sprite * bird;
};

#endif
