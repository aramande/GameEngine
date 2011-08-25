#include <iostream>
#include <cxxtest/TestSuite.h>
#include "sprite.h"
#include "badarg.h"
#include "logger.h"
#include "resource.h"
#include "resourcehandler.h"
#include "fileexception.h"

using namespace engine;

class ResourceParserTest : public CxxTest::TestSuite {
public:
	void testParserIsCategory(){
		std::vector<std::string> argv;
		ResourceParser rp;
		TS_ASSERT(rp.isCategory("resource stuff 1{", "resource", argv));
		TS_ASSERT_EQUALS(argv[0], "stuff");
		TS_ASSERT_EQUALS(argv[1], "1");
		TS_ASSERT_EQUALS(argv[2], "{");
	}

	void testParserIsVariable(){
		std::string value;
		ResourceParser rp;
		TS_ASSERT(rp.isVariable("variable=5", "variable", value));
		TS_ASSERT_EQUALS(value, "5");
	}
};

class ResourceHandlerTest : public CxxTest::TestSuite {
private:
	SDL_Surface* screen;
	ResourceHandler* reshan;
public:
	ResourceHandlerTest(){
		SDL_Init( SDL_INIT_EVERYTHING ); 
		screen = SDL_SetVideoMode( 40, 20, 32, SDL_SWSURFACE );
		logger->setToCommand(false);
		logger->setLogFile("test.log");
		logger->print("Testing resourcehandler");
		//ResourceHandler::destroy();
		reshan = ResourceHandler::init();
		reshan->loadResourceFile("test.res");
	}
	~ResourceHandlerTest(){
		SDL_Quit();
		//ResourceHandler::destroy();
		reshan = NULL;
	}

	void testRemovalByName(){
		logger->print("Testing resourcehandler, removal by name");
		Resource* resource = reshan->getResource("testimage");
		TS_ASSERT(resource->getRefCount() == 1);
		reshan->release("testimage");
		TS_ASSERT(resource->getRefCount() == 0);
	}

	void testRemovalByObject(){
		Resource* resource = reshan->getResource("testimage");
		TS_ASSERT(resource->getRefCount() == 1);
		resource->release();
		TS_ASSERT(resource->getRefCount() == 0);

	}

	void testExistingImage(){
		TS_ASSERT(reshan->getResource("testimage") != NULL);
		reshan->release("testimage");
	}

	void testDuplicates(){
		Resource* res1 = reshan->getResource("testimage");
		Resource* res2 = reshan->getResource("testimage");
		TS_ASSERT_EQUALS(res1, res2);
		res1->release();
		res2->release();
	}

	void testNonExistantImage(){
		TS_ASSERT(reshan->getResource("nonexistant") == NULL);
		//reshan->release("nonexistant");
	}
};

