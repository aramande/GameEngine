/* Generated file, do not edit */

#ifndef CXXTEST_RUNNING
#define CXXTEST_RUNNING
#endif

#define _CXXTEST_LONGLONG long long
#include <cxxtest/TestListener.h>
#include <cxxtest/TestTracker.h>
#include <cxxtest/TestRunner.h>
#include <cxxtest/RealDescriptions.h>
#include <cxxtest/TestMain.h>

bool suite_SpriteTest_init = false;
#include "spritetest.h"

static SpriteTest suite_SpriteTest;

static CxxTest::List Tests_SpriteTest = { 0, 0 };
CxxTest::StaticSuiteDescription suiteDescription_SpriteTest( "spritetest.h", 4, "SpriteTest", suite_SpriteTest, Tests_SpriteTest );

static class TestDescription_suite_SpriteTest_testFunction : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_SpriteTest_testFunction() : CxxTest::RealTestDescription( Tests_SpriteTest, suiteDescription_SpriteTest, 7, "testFunction" ) {}
 void runTest() { suite_SpriteTest.testFunction(); }
} testDescription_suite_SpriteTest_testFunction;

#include <cxxtest/Root.cpp>
const char* CxxTest::RealWorldDescription::_worldName = "cxxtest";
