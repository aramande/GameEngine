#include <iostream>
#include <cxxtest/TestSuite.h>
#include "component.h"
#include "button.h"
#include "gui.h"
#include "badarg.h"

using namespace engine;

class GuiTest : public CxxTest::TestSuite 
{
 private:
  Component* comp;
  Component* comp1;
  Gui* test;
 public:

  void testAddComp(){
	  comp = new Button(1, 1, 1, 1);
	  comp1 = new Button(1, 1, 1, 1);
	  test = new Gui();

	  test->addComp(comp);
	  TS_ASSERT_EQUALS(comp->getName(), "comp0");
  }

  void testAddComp_DuplicateCollision(){
	  test->addComp(comp);
	  TS_ASSERT_EQUALS(comp->getName(), "comp0");
  }

  void testAddComp_IncrementName(){
	  test->addComp(comp1);
	  TS_ASSERT_EQUALS(comp1->getName(), "comp1");
  }

  void testSetComp(){
	  delete comp;
	  delete comp1;
	  delete test;
	  comp = new Button(1, 1, 1, 1);
	  comp1 = new Button(1, 1, 1, 1);
	  test = new Gui();

	  // User chosen name
	  test->setComp("GLaDOS", comp);
	  TS_ASSERT_EQUALS(comp->getName(), "GLaDOS");
  }

  void testSetComp_Duplicate(){
	  test->setComp("GLaDOS", comp);
	  TS_ASSERT_EQUALS(comp->getName(), "GLaDOS");
  }

  void testSetComp_NameReuse(){
	  // No reuse of name
	  TS_ASSERT_THROWS(test->setComp("GLaDOS", comp1), bad_arg);
  }

  void testSetComp_RenameExisting(){
	  test->setComp("Turret", comp);
	  TS_ASSERT_EQUALS(comp->getName(), "Turret");
  }
  
  void testSetComp_RenameOldRemoved(){
	  test->setComp("Turret", comp);
	  TS_ASSERT_THROWS(test->getComp("GLaDOS"), bad_arg);
  }
};