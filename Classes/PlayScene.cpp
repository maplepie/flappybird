#include"PlayScene.h"
#define BACKGROUNGSPEED 0.9f

Scene * PlayScene::createScene()
{
	auto scene = Scene::create();
	auto layer = PlayScene::create();
	scene->addChild(layer);
	return scene;
}

bool PlayScene::init()
{
	if (!Layer::init())
	{
		return false;
	}

	visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	//背景
	auto bg = Sprite::create("day.png");
	bg->setPosition(visibleSize / 2);
	this->addChild(bg);
	//添加小鸟
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

	bird->setPosition(visibleSize.width/4,visibleSize.height / 2);
	this->addChild(bird);

	Animate *animate = Animate::create(animation);
	bird->runAction(RepeatForever::create(animate));

	//添加地面
	ground1 = Sprite::create("ground.png");
	ground1->setAnchorPoint(Vec2::ZERO);
	ground1->setPosition(Vec2::ZERO);
	ground1->setLocalZOrder(1);
	this->addChild(ground1);

	ground2 = Sprite::create("ground.png");
	ground2->setAnchorPoint(Vec2::ZERO);
	ground2->setPosition(Vec2(ground1->getContentSize().width,0));
	ground2->setLocalZOrder(1);
	this->addChild(ground2);

	//添加水管
	pipe1 = Sprite::create("down.png");
	pipe1->setAnchorPoint(Vec2::ZERO);
	pipe1->setPosition(Vec2(visibleSize.width,ground1->getContentSize().height/2*myRandom()));
	pipe1->setLocalZOrder(0);
	this->addChild(pipe1);

	pipe2 = Sprite::create("up.png");
	pipe2->setAnchorPoint(Vec2::ZERO);
	pipe2->setPosition(Vec2(visibleSize.width, pipe1->getPositionY()+pipe1->getContentSize().height+visibleSize.height/5));
	pipe2->setLocalZOrder(0);
	this->addChild(pipe2);

	pipe3 = Sprite::create("down.png");
	pipe3->setAnchorPoint(Vec2::ZERO);
	pipe3->setPosition(Vec2(visibleSize.width*3/2+pipe3->getContentSize().width/2, ground1->getContentSize().height / 2 * myRandom()));
	pipe3->setLocalZOrder(0);
	this->addChild(pipe3);

	pipe4 = Sprite::create("up.png");
	pipe4->setAnchorPoint(Vec2::ZERO);
	pipe4->setPosition(Vec2(visibleSize.width*3/2 + pipe3->getContentSize().width/2, pipe3->getPositionY() + pipe3->getContentSize().height + visibleSize.height / 5));
	pipe4->setLocalZOrder(0);
	this->addChild(pipe4);

	//添加计时器
	this->scheduleUpdate();

	this->setTouchEnabled(true);
	this->setTouchMode(Touch::DispatchMode::ONE_BY_ONE);
	

	return true;
}

float PlayScene::myRandom()
{
	struct timeval nowTimeval;
	gettimeofday(&nowTimeval, NULL);
	long second = nowTimeval.tv_sec;
	long microsecond = nowTimeval.tv_usec;
//	log("%d,%d", second, microsecond);
	unsigned int seed = second * 1000 + microsecond / 1000 + rand();
	srand(seed);

	return CCRANDOM_0_1()*2-1;
}

bool PlayScene::isLoseGame()
{
	if (bird->getBoundingBox().intersectsRect(pipe1->getBoundingBox()) || bird->getBoundingBox().intersectsRect(pipe3->getBoundingBox()) || bird->getBoundingBox().intersectsRect(pipe2->getBoundingBox()) || bird->getBoundingBox().intersectsRect(pipe4->getBoundingBox()))
	{
		return true;
	}
	return false;
}

bool PlayScene::onTouchBegan(Touch * touch, Event * event)
{

	return false;
}

void PlayScene::onTouchMoved(Touch * touch, Event * event)
{

}

void PlayScene::onTouchEnded(Touch * touch, Event * event)
{

}


void PlayScene::update(float delay)
{
//	log("update");
	Vec2 groundPosition = ground1->getPosition();
	if (groundPosition.x > -ground1->getContentSize().width)
	{
		ground1->setPositionX(ground1->getPositionX() - BACKGROUNGSPEED);
		ground2->setPositionX(ground2->getPositionX() - BACKGROUNGSPEED);
	}
	else
	{
		ground1->setPositionX(ground2->getPositionX());
		ground2->setPositionX(ground1->getPositionX()+ground1->getContentSize().width);
//		log("back");
	}

	float pipePositionX = pipe1->getPositionX();
	if (pipePositionX > -pipe1->getContentSize().width)
	{
		pipe1->setPositionX(pipe1->getPositionX() - BACKGROUNGSPEED);
		pipe2->setPositionX(pipe2->getPositionX() - BACKGROUNGSPEED);
	}
	else
	{
		pipe1->setPositionX(visibleSize.width);
		pipe2->setPositionX(visibleSize.width);
		//TODO 添加随机高度
		pipe1->setPositionY(ground1->getContentSize().height / 2 * myRandom());
		pipe2->setPositionY(pipe1->getPositionY() + pipe1->getContentSize().height + visibleSize.height / 5);
	}

	float otherpipePositionX = pipe3->getPositionX();
	if (otherpipePositionX > -pipe3->getContentSize().width)
	{
		pipe3->setPositionX(pipe3->getPositionX() - BACKGROUNGSPEED);
		pipe4->setPositionX(pipe4->getPositionX() - BACKGROUNGSPEED);
	}
	else
	{
		pipe3->setPositionX(visibleSize.width);
		pipe4->setPositionX(visibleSize.width);
		//TODO 添加随机高度
		pipe3->setPositionY(ground1->getContentSize().height / 2 * myRandom());
		pipe4->setPositionY(pipe3->getPositionY() + pipe3->getContentSize().height + visibleSize.height / 5);
	}

//判断是否碰撞
	if (isLoseGame())
	{
		this->unscheduleAllSelectors();
		bird->stopAllActions();
//		auto dead = Director::getInstance()->getTextureCache()->addImage("bird3.png");
		bird->setTexture("bird3.png");
		bird->setAnchorPoint(Vec2(1, 0.5));
		bird->setPositionX(bird->getPositionX()+bird->getContentSize().width/2);

		bird->runAction(MoveTo::create(1,Vec2(bird->getPositionX(),ground1->getContentSize().height+bird->getContentSize().height/2)));
	}

}

void PlayScene::onExit()
{
	Layer::onExit();
	log("onExit");
	this->unscheduleAllSelectors();
}
