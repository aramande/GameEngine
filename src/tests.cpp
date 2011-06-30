/* Generated file, do not edit */

#ifndef CXXTEST_RUNNING
#define CXXTEST_RUNNING
#endif

#define _CXXTEST_HAVE_STD
#define _CXXTEST_HAVE_EH
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
CxxTest::StaticSuiteDescription suiteDescription_SpriteTest( "spritetest.h", 9, "SpriteTest", suite_SpriteTest, Tests_SpriteTest );

static class TestDescription_SpriteTest_testConstructor : public CxxTest::RealTestDescription {
public:
 TestDescription_SpriteTest_testConstructor() : CxxTest::RealTestDescription( Tests_SpriteTest, suiteDescription_SpriteTest, 22, "testConstructor" ) {}
 void runTest() { suite_SpriteTest.testConstructor(); }
} testDescription_SpriteTest_testConstructor;

static class TestDescription_SpriteTest_testNonExistantFile : public CxxTest::RealTestDescription {
public:
 TestDescription_SpriteTest_testNonExistantFile() : CxxTest::RealTestDescription( Tests_SpriteTest, suiteDescription_SpriteTest, 30, "testNonExistantFile" ) {}
 void runTest() { suite_SpriteTest.testNonExistantFile(); }
} testDescription_SpriteTest_testNonExistantFile;

static class TestDescription_SpriteTest_testTranslate : public CxxTest::RealTestDescription {
public:
 TestDescription_SpriteTest_testTranslate() : CxxTest::RealTestDescription( Tests_SpriteTest, suiteDescription_SpriteTest, 34, "testTranslate" ) {}
 void runTest() { suite_SpriteTest.testTranslate(); }
} testDescription_SpriteTest_testTranslate;

static class TestDescription_SpriteTest_testMoveTo : public CxxTest::RealTestDescription {
public:
 TestDescription_SpriteTest_testMoveTo() : CxxTest::RealTestDescription( Tests_SpriteTest, suiteDescription_SpriteTest, 45, "testMoveTo" ) {}
 void runTest() { suite_SpriteTest.testMoveTo(); }
} testDescription_SpriteTest_testMoveTo;

static class TestDescription_SpriteTest_testResize : public CxxTest::RealTestDescription {
public:
 TestDescription_SpriteTest_testResize() : CxxTest::RealTestDescription( Tests_SpriteTest, suiteDescription_SpriteTest, 56, "testResize" ) {}
 void runTest() { suite_SpriteTest.testResize(); }
} testDescription_SpriteTest_testResize;

static class TestDescription_SpriteTest_testResizeNegative : public CxxTest::RealTestDescription {
public:
 TestDescription_SpriteTest_testResizeNegative() : CxxTest::RealTestDescription( Tests_SpriteTest, suiteDescription_SpriteTest, 62, "testResizeNegative" ) {}
 void runTest() { suite_SpriteTest.testResizeNegative(); }
} testDescription_SpriteTest_testResizeNegative;

#include <cxxtest/Root.cpp>
