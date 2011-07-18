#include <iostream>
#include <cxxtest/TestSuite.h>
#include "keyevent.h"

using namespace engine;

class KeyEventTest : public CxxTest::TestSuite 
{
 private:
 public:
	 void testFunction(){
		 TS_ASSERT_EQUALS(1, 1);
	 }
};