#include"BaseLayer.h"
#include"PlayScene.h"



bool BaseLayer::init()
{
	if (!Layer::init()) 
	{
		return false;
	}
	visibleSize = Director::getInstance()->getVisibleSize();
	auto bg = Sprite::create("day.png");
	bg->setPosition(visibleSize / 2);
	this->addChild(bg);

	//Ìí¼ÓÐ¡Äñ
	Texture2D * cache = Director::getInstance()->getTextureCache()->addImage("bird.png");
	auto birdSize = cache->getContentSize();
	bird = Sprite::create();

	Animation *animation = Animation::create();
	for (int i = 0; i < 3; i++)
	{
		auto birdFrame = SpriteFrame::create("bird.png", Rect(0, i*birdSize.height / 3, birdSize.width, birdSize.height / 3));
		animation->addSpriteFrame(birdFrame);
	}
	animation->setDelayPerUnit(0.2f);

	this->addChild(bird);

	Animate *animate = Animate::create(animation);
	bird->runAction(RepeatForever::create(animate));

	return true;
}



/*
Scene * BaseLayer::createScene(BaseLayer &baseLayer)
{
	auto scene = Scene::create();
	auto layer = baseLayer.create();
	scene->addChild(layer);
	return scene;
}
*/

