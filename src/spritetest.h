#include <iostream>
#include <cxxtest/TestSuite.h>
#include "sprite.h"
#include "badarg.h"
#include "logger.h"
#include "resource.h"
#include "fileexception.h"

using namespace engine;

class SpriteTest : public CxxTest::TestSuite 
{
private:
	SDL_Surface* screen;
	ResourceHandler* reshan;
public:
	SpriteTest(){
		logger->print("Testing sprite");
		SDL_Init( SDL_INIT_EVERYTHING ); 
		screen = SDL_SetVideoMode( 40, 20, 32, SDL_SWSURFACE );
		//ResourceHandler::destroy();
		reshan = ResourceHandler::init();
		reshan->loadResourceFile("test.res");
	}
	~SpriteTest(){
		//ResourceHandler::destroy();
		SDL_Quit();
		reshan = NULL;
	}

	void testConstructor(){
		logger->print("Testing resourcehandler, constructor");
		Sprite* test = new Sprite(reshan->getImage("testimage"));
		TS_ASSERT_EQUALS(test->getX(), 0);
		TS_ASSERT_EQUALS(test->getY(), 0);
		TS_ASSERT_EQUALS(test->getWidth(), 100);
		TS_ASSERT_EQUALS(test->getHeight(), 120);
		delete test;
	}

	void testTranslate(){
		Sprite* test = new Sprite(reshan->getImage("testimage"));
		test->translate(13, 21);
		TS_ASSERT_EQUALS(test->getX(), 13);
		TS_ASSERT_EQUALS(test->getY(), 21);

		test->translate(-21, 5);
		TS_ASSERT_EQUALS(test->getX(), -8);
		TS_ASSERT_EQUALS(test->getY(), 26);
		delete test;
	}

	void testMoveTo(){
		Sprite* test = new Sprite(reshan->getImage("testimage"));
		test->moveTo(13, 21);
		TS_ASSERT_EQUALS(test->getX(), 13);
		TS_ASSERT_EQUALS(test->getY(), 21);

		test->moveTo(-21, 5);
		TS_ASSERT_EQUALS(test->getX(), -21);
		TS_ASSERT_EQUALS(test->getY(), 5);
		delete test;
	}

	void testResize(){
		Sprite* test = new Sprite(reshan->getImage("testimage"));
		test->resize(130, 110);
		TS_ASSERT_EQUALS(test->getWidth(), 130);
		TS_ASSERT_EQUALS(test->getHeight(), 110);
		delete test;
	}
	void testResize_Negative(){
		Sprite* test = new Sprite(reshan->getImage("testimage"));
		TS_ASSERT_THROWS(test->resize(-20, 50), bad_arg);
		delete test;
	}
};

