/* Generated file, do not edit */

#ifndef CXXTEST_RUNNING
#define CXXTEST_RUNNING
#endif

#define _CXXTEST_HAVE_STD
#include <cxxtest/TestListener.h>
#include <cxxtest/TestTracker.h>
#include <cxxtest/TestRunner.h>
#include <cxxtest/RealDescriptions.h>
#include <cxxtest/ErrorPrinter.h>

int main() {
 return CxxTest::ErrorPrinter().run();
}
#include "spritetest.h"

static SpriteTest suite_SpriteTest;

static CxxTest::List Tests_SpriteTest = { 0, 0 };
CxxTest::StaticSuiteDescription suiteDescription_SpriteTest( "spritetest.h", 4, "SpriteTest", suite_SpriteTest, Tests_SpriteTest );

static class TestDescription_SpriteTest_testFunction : public CxxTest::RealTestDescription {
public:
 TestDescription_SpriteTest_testFunction() : CxxTest::RealTestDescription( Tests_SpriteTest, suiteDescription_SpriteTest, 7, "testFunction" ) {}
 void runTest() { suite_SpriteTest.testFunction(); }
} testDescription_SpriteTest_testFunction;

static class TestDescription_SpriteTest_testFunction2 : public CxxTest::RealTestDescription {
public:
 TestDescription_SpriteTest_testFunction2() : CxxTest::RealTestDescription( Tests_SpriteTest, suiteDescription_SpriteTest, 12, "testFunction2" ) {}
 void runTest() { suite_SpriteTest.testFunction2(); }
} testDescription_SpriteTest_testFunction2;

#include <cxxtest/Root.cpp>
