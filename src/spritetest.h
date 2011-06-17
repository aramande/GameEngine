#include <cxxtest/TestSuite.h>
#include "sprite.h"

class SpriteTest : public CxxTest::TestSuite 
{
 public:
  void testFunction( void )
  {
	  TS_ASSERT_EQUALS( 1, 1 )
  }

  void testFunction2( void )
  {
	  TS_ASSERT_EQUALS( 1, 2 )
  }
};

