#include "MyFunction.h"
#include "PlayScene.h"

void MyFunction::playGame()
{
	auto scene = PlayScene::createScene();
	Director::getInstance()->replaceScene(scene);
}

float MyFunction::myRandom()
{
	struct timeval nowTimeval;
	gettimeofday(&nowTimeval, NULL);
	long second = nowTimeval.tv_sec;
	long microsecond = nowTimeval.tv_usec;
	//	log("%d,%d", second, microsecond);
	unsigned int seed = second * 1000 + microsecond / 1000 + rand();
	srand(seed);

	return CCRANDOM_0_1() * 2 - 1;
}