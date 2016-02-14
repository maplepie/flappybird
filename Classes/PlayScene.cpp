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

	currentScore = 0;

	visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	//����
	auto bg = Sprite::create("day.png");
	bg->setPosition(visibleSize / 2);
	this->addChild(bg);
	//���С��
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

	//��ӵ���
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

	//���ˮ��
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

	

	startGameTeach = Sprite::create("teach.png");
	startGameTeach->setPosition(Vec2(visibleSize.width/2, visibleSize.height/2));
	this->addChild(startGameTeach);

	score = Label::createWithSystemFont("0", "Arial", 40);
	score->setPosition(Vec2(visibleSize.width / 2, visibleSize.height*7 / 8));
	
	this->addChild(score);
//	scoreLabel->setVisible(false);

	getScoreFlag = true;

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
	//����ˮ��
	if (bird->getBoundingBox().intersectsRect(pipe1->getBoundingBox()) || bird->getBoundingBox().intersectsRect(pipe3->getBoundingBox()) || bird->getBoundingBox().intersectsRect(pipe2->getBoundingBox()) || bird->getBoundingBox().intersectsRect(pipe4->getBoundingBox()))
	{
		return true;
	}
	//��������
	if (bird->getPositionY() - bird->getContentSize().height / 2 <= ground1->getContentSize().height)
	{
		return true;
	}
	return false;
}

void PlayScene::createMenu()
{
	//TODO ������ʷ��߷ֺ����ڵķ���

	auto result = MenuItemImage::create("result.png", "result.png");
	result->setPosition(Vec2(visibleSize.width/2,visibleSize.height/2));
	result->setName("result");

	auto s = __String::createWithFormat("%d",currentScore);
	auto mCurrentScore = Label::createWithSystemFont(s->getCString(), "Arial", 20);
	mCurrentScore->setPosition(result->getContentSize().width*27/32,result->getContentSize().height*11/18);
	result->addChild(mCurrentScore);

	int bestScore = UserDefault::getInstance()->getIntegerForKey("bestscore", 0);
	if (currentScore > bestScore)
	{
		bestScore = currentScore;
	}
	auto b = __String::createWithFormat("%d", bestScore);
	auto mBestScore = Label::createWithSystemFont(b->getCString(), "Arial", 20);
	mBestScore->setPosition(result->getContentSize().width * 27 / 32, result->getContentSize().height * 5 / 18);
	result->addChild(mBestScore);

	UserDefault::getInstance()->setIntegerForKey("bestscore", bestScore);

	auto gameover = MenuItemImage::create("gameover.png","gameover.png");
	gameover->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2 + result->getContentSize().height));

	//��ӿ�ʼ�˵�
	auto startMenuItem = MenuItemImage::create("restart.png", "restart.png", CC_CALLBACK_1(PlayScene::startGame, this));
	startMenuItem->setAnchorPoint(Vec2(0.5, 0));
	startMenuItem->setPosition(Vec2(visibleSize.width / 4, ground1->getContentSize().height));

	//��ӳɼ��˵�
	auto scoreMenuItem = MenuItemImage::create("rank.png", "rank.png", CC_CALLBACK_1(PlayScene::scoreMenu, this));
	scoreMenuItem->setAnchorPoint(Vec2(0.5, 0));
	scoreMenuItem->setPosition(Vec2(visibleSize.width * 3 / 4, ground1->getContentSize().height));
//	scoreMenuItem->setName("score");

	auto ranks = MenuItemImage::create("ranks.png", "ranks.png");
	ranks->setPosition(Vec2(visibleSize.width / 2, visibleSize.height * 9 / 20));
	ranks->setName("ranks");
	ranks->setVisible(false);

	menu = Menu::create(result,gameover,startMenuItem,scoreMenuItem,ranks,NULL);
	menu->setTag(10);
	menu->setAnchorPoint(Vec2::ZERO);
	menu->setPosition(Vec2::ZERO);
	
	
	this->addChild(menu);
	log("create menu");
}

void PlayScene::startGame(Ref * pSender)
{
	auto secene = PlayScene::createScene();
	Director::getInstance()->replaceScene(secene);
	log("restartGame");
}

void PlayScene::scoreMenu(Ref * pSender)
{
//	this->removeChildByTag(10);
	log("score");
	auto s = __String::createWithFormat("result");
	auto result = menu->getChildByName(s->getCString());
	auto ranks = menu->getChildByName("ranks");
	if (result->isVisible())
	{
		result->setVisible(false);
		ranks->setVisible(true);
		
	}
	else
	{
		result->setVisible(true);
		ranks->setVisible(false);
	}
	//TODO ������ʷ����
}


bool PlayScene::onTouchBegan(Touch * touch, Event * event)
{
	if (startGameTeach->isVisible())
	{
		startGameTeach->setVisible(false);
		this->scheduleUpdate();
	}

//	bird->setPositionY(bird->getContentSize().height / 2);
	bird->runAction(MoveBy::create(0.25, Vec2(0, bird->getContentSize().height*3)));
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
		// �������߶�
		pipe1->setPositionY(ground1->getContentSize().height / 2 * myRandom());
		pipe2->setPositionY(pipe1->getPositionY() + pipe1->getContentSize().height + visibleSize.height / 5);

		getScoreFlag = true;
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
		// �������߶�
		pipe3->setPositionY(ground1->getContentSize().height / 2 * myRandom());
		pipe4->setPositionY(pipe3->getPositionY() + pipe3->getContentSize().height + visibleSize.height / 5);

		getScoreFlag = true;
	}
	//�ﵽ���λ��
	if (bird->getPositionY() + bird->getContentSize().height / 2 > visibleSize.height)
	{
		bird->setPositionY(visibleSize.height - bird->getContentSize().height /2);
	}



//�ж��Ƿ���ײ
	if (isLoseGame())
	{
		this->setTouchEnabled(false);
		this->unscheduleAllSelectors();
		bird->stopAllActions();
//		auto dead = Director::getInstance()->getTextureCache()->addImage("bird3.png");
		bird->setTexture("bird3.png");
		bird->setAnchorPoint(Vec2(1, 0.5));
		bird->setPositionX(bird->getPositionX()+bird->getContentSize().width/2);
		auto action = Spawn::create(MoveTo::create(1, Vec2(bird->getPositionX(), ground1->getContentSize().height + bird->getContentSize().height / 2)), CallFunc::create(CC_CALLBACK_0(PlayScene::createMenu,this)),NULL);
		bird->runAction(action);
	}
	else 
	{//�½�
		bird->setPositionY(bird->getPositionY() - bird->getContentSize().height /11);
	}

	if (getScoreFlag&&(pipe1->getPositionX() <= bird->getPositionX()||pipe3->getPositionX() <= bird->getPositionX()))
	{
		score->setString(__String::createWithFormat("%d", ++currentScore)->getCString());
		getScoreFlag = false;
	}


}

void PlayScene::onExit()
{
	Layer::onExit();
	log("onExit");
	this->unscheduleAllSelectors();
	this->setTouchEnabled(false);
}
