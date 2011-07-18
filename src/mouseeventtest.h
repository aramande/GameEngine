#include <iostream>
#include <cxxtest/TestSuite.h>
#include "event.h"

using namespace engine;

class EventTest : public CxxTest::TestSuite 
{
 private:
 public:
	 void testFunction(){
		 TS_ASSERT_EQUALS(1, 1);
	 }
};