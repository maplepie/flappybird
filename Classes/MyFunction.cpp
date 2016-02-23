#include "MyFunction.h"
#include "PlayScene.h"

void MyFunction::playGame()
{
	auto scene = PlayScene::createScene();
	Director::getInstance()->replaceScene(scene);
}
