#include"StartScene.h"
#include"PlayScene.h"

Scene * StartScene::createScene()
{
	auto scene = Scene::create();
	auto layer = StartScene::create();
	scene->addChild(layer);
	return scene;
}

bool StartScene::init()
{
	if (!Layer::init())
	{
		return false;
	}
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	//背景
	auto bg = Sprite::create("day.png");
	bg->setPosition(visibleSize/2);
	this->addChild(bg);
	//添加小鸟
	Texture2D * cache = Director::getInstance()->getTextureCache()->addImage("bird.png");
	auto birdSize = cache->getContentSize();
	auto bird = Sprite::create();

	Animation *animation = Animation::create();
	for (int i = 0; i < 3; i++)
	{
		auto birdFrame = SpriteFrame::create("bird.png", Rect(0, i*birdSize.height / 3, birdSize.width,birdSize.height/3));
		animation->addSpriteFrame(birdFrame);
	}
	animation->setDelayPerUnit(0.2f);

	bird->setPosition(visibleSize / 2);
	this->addChild(bird);

	Animate *animate = Animate::create(animation);
	bird->runAction(RepeatForever::create(animate));

	//添加文字
	auto label = Sprite::create("flappybird.png");
	label->setPosition(visibleSize.width / 2, visibleSize.height / 2 + 100);
	this->addChild(label);

	//添加地面
	auto ground = Sprite::create("ground.png");
	ground->setAnchorPoint(Vec2::ZERO);
	ground->setPosition(Vec2::ZERO);
	this->addChild(ground);

	//添加开始菜单
	auto startMenuItem = MenuItemImage::create("restart.png","restart.png",CC_CALLBACK_1(StartScene::startGame,this));
	startMenuItem->setAnchorPoint(Vec2(0.5,0));
	startMenuItem->setPosition(Vec2(visibleSize.width/4,ground->getContentSize().height));

	//添加成绩菜单
	auto scoreMenuItem = MenuItemImage::create("rank.png", "rank.png", CC_CALLBACK_1(StartScene::scoreMenu, this));
	scoreMenuItem->setAnchorPoint(Vec2(0.5, 0));
	scoreMenuItem->setPosition(Vec2(visibleSize.width *3/ 4, ground->getContentSize().height));

	Menu *menu = Menu::create(startMenuItem,scoreMenuItem, NULL);
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu);

	return true;
}

void StartScene::startGame(Ref *pSender)
{
	log("start");
	auto scene = PlayScene::createScene();
	Director::getInstance()->replaceScene(scene);
}

void StartScene::scoreMenu(Ref * pSender)
{
	log("score");
}
