#include <iostream>
#include <cxxtest/TestSuite.h>
#include "sprite.h"
#include "badarg.h"
#include "resource.h"
#include "fileexception.h"

using namespace engine;

class ResourceTest : public CxxTest::TestSuite 
{
 private:
  SDL_Surface* screen;
 public:
  ResourceTest(){
	  SDL_Init( SDL_INIT_EVERYTHING ); 
	  screen = SDL_SetVideoMode( 40, 20, 32, SDL_SWSURFACE ); 
  }
  virtual ~ResourceTest(){
	  SDL_Quit();
  }

  void testExistingImage(){
	  TS_ASSERT(Resource::loadImage("testimage.png") != NULL);
  }

  void testDuplicates(){
	  Image* img1 = Resource::loadImage("testimage.png");
	  Image* img2 = Resource::loadImage("testimage.png");
	  TS_ASSERT_EQUALS(img1, img2);
  }

  void testNonExistantImage(){
	  TS_ASSERT_THROWS(Resource::loadImage("nonexistantimage.png"), file_exception);
  }

  
};

