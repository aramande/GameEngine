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

};