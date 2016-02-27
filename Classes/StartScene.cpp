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
	if (!BaseLayer::init())
	{
		return false;
	}

	//设置小鸟初始位置
	bird->setPosition(visibleSize / 2);
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
	if (ranks&&ranks->isVisible())
	{
		ranks->setVisible(false);
	}
	else if (ranks&&!ranks->isVisible())
	{
		ranks->setVisible(true);
	}
	else
	{
		ranks = MenuItemImage::create("ranks.png", "ranks.png");
		ranks->setPosition(Vec2(visibleSize.width / 2, visibleSize.height * 9 / 20));

		auto menu = Menu::create(ranks, NULL);
		menu->setAnchorPoint(Vec2::ZERO);
		menu->setPosition(Vec2::ZERO);
		this->addChild(menu);

		int bestScore = UserDefault::getInstance()->getIntegerForKey("bestscore", 0);
		auto b = __String::createWithFormat("%d", bestScore);
		auto mBestScore = Label::createWithSystemFont(b->getCString(), "Arial", 30);
		mBestScore->setPosition(ranks->getContentSize().width * 10 / 19, ranks->getContentSize().height * 5 / 4);
		ranks->addChild(mBestScore);

		int secondScore = UserDefault::getInstance()->getIntegerForKey("secondScore", 0);
		auto c = __String::createWithFormat("%d", secondScore);
		auto mSecondScore = Label::createWithSystemFont(c->getCString(), "Arial", 28);
		mSecondScore->setPosition(ranks->getContentSize().width * 1 / 6, ranks->getContentSize().height * 1);
		ranks->addChild(mSecondScore);

		int thirdScore = UserDefault::getInstance()->getIntegerForKey("thirdScore", 0);
		auto d = __String::createWithFormat("%d", thirdScore);
		auto mThirdScore = Label::createWithSystemFont(d->getCString(), "Arial", 27);
		mThirdScore->setPosition(ranks->getContentSize().width * 6 / 7, ranks->getContentSize().height * 6 / 7);
		ranks->addChild(mThirdScore);
	}
}
