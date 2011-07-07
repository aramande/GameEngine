#include <iostream>
#include <cxxtest/TestSuite.h>
#include "sprite.h"
#include "badarg.h"
#include "resource.h"
#include "fileexception.h"

using namespace engine;

class SpriteTest : public CxxTest::TestSuite 
{
 private:
  SDL_Surface* screen;
 public:
  SpriteTest(){
	  SDL_Init( SDL_INIT_EVERYTHING ); 
	  screen = SDL_SetVideoMode( 40, 20, 32, SDL_SWSURFACE ); 
  }
  virtual ~SpriteTest(){
	  SDL_Quit();
  }

  void testConstructor(){
	  Sprite* test = new Sprite(Resource::loadImage("testimage.png"));
	  TS_ASSERT_EQUALS(test->getX(), 0);
	  TS_ASSERT_EQUALS(test->getY(), 0);
	  TS_ASSERT_EQUALS(test->getWidth(), 100);
	  TS_ASSERT_EQUALS(test->getHeight(), 120);
  }

  void testTranslate(){
	  Sprite* test = new Sprite(Resource::loadImage("testimage.png"));
	  test->translate(13, 21);
	  TS_ASSERT_EQUALS(test->getX(), 13);
	  TS_ASSERT_EQUALS(test->getY(), 21);

	  test->translate(-21, 5);
	  TS_ASSERT_EQUALS(test->getX(), -8);
	  TS_ASSERT_EQUALS(test->getY(), 26);
  }

  void testMoveTo(){
	  Sprite* test = new Sprite(Resource::loadImage("testimage.png"));
	  test->moveTo(13, 21);
	  TS_ASSERT_EQUALS(test->getX(), 13);
	  TS_ASSERT_EQUALS(test->getY(), 21);

	  test->moveTo(-21, 5);
	  TS_ASSERT_EQUALS(test->getX(), -21);
	  TS_ASSERT_EQUALS(test->getY(), 5);
  }

  void testResize(){
	  Sprite* test = new Sprite(Resource::loadImage("testimage.png"));
	  test->resize(130, 110);
	  TS_ASSERT_EQUALS(test->getWidth(), 130);
	  TS_ASSERT_EQUALS(test->getHeight(), 110);
  }
  void testResize_Negative(){
	  Sprite* test = new Sprite(Resource::loadImage("testimage.png"));
	  TS_ASSERT_THROWS(test->resize(-20, 50), bad_arg);
  }
};

