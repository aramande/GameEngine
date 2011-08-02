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
#include "C:/Users/Arian/Documents/My Dropbox/DSV/Termin 3/PROG3/GameEngine/src/guitest.h"

static GuiTest suite_GuiTest;

static CxxTest::List Tests_GuiTest = { 0, 0 };
CxxTest::StaticSuiteDescription suiteDescription_GuiTest( "C:/Users/Arian/Documents/My Dropbox/DSV/Termin 3/PROG3/GameEngine/src/guitest.h", 10, "GuiTest", suite_GuiTest, Tests_GuiTest );

static class TestDescription_GuiTest_testAddComp : public CxxTest::RealTestDescription {
public:
 TestDescription_GuiTest_testAddComp() : CxxTest::RealTestDescription( Tests_GuiTest, suiteDescription_GuiTest, 18, "testAddComp" ) {}
 void runTest() { suite_GuiTest.testAddComp(); }
} testDescription_GuiTest_testAddComp;

static class TestDescription_GuiTest_testAddComp_DuplicateCollision : public CxxTest::RealTestDescription {
public:
 TestDescription_GuiTest_testAddComp_DuplicateCollision() : CxxTest::RealTestDescription( Tests_GuiTest, suiteDescription_GuiTest, 27, "testAddComp_DuplicateCollision" ) {}
 void runTest() { suite_GuiTest.testAddComp_DuplicateCollision(); }
} testDescription_GuiTest_testAddComp_DuplicateCollision;

static class TestDescription_GuiTest_testAddComp_IncrementName : public CxxTest::RealTestDescription {
public:
 TestDescription_GuiTest_testAddComp_IncrementName() : CxxTest::RealTestDescription( Tests_GuiTest, suiteDescription_GuiTest, 32, "testAddComp_IncrementName" ) {}
 void runTest() { suite_GuiTest.testAddComp_IncrementName(); }
} testDescription_GuiTest_testAddComp_IncrementName;

static class TestDescription_GuiTest_testSetComp : public CxxTest::RealTestDescription {
public:
 TestDescription_GuiTest_testSetComp() : CxxTest::RealTestDescription( Tests_GuiTest, suiteDescription_GuiTest, 37, "testSetComp" ) {}
 void runTest() { suite_GuiTest.testSetComp(); }
} testDescription_GuiTest_testSetComp;

static class TestDescription_GuiTest_testSetComp_Duplicate : public CxxTest::RealTestDescription {
public:
 TestDescription_GuiTest_testSetComp_Duplicate() : CxxTest::RealTestDescription( Tests_GuiTest, suiteDescription_GuiTest, 50, "testSetComp_Duplicate" ) {}
 void runTest() { suite_GuiTest.testSetComp_Duplicate(); }
} testDescription_GuiTest_testSetComp_Duplicate;

static class TestDescription_GuiTest_testSetComp_NameReuse : public CxxTest::RealTestDescription {
public:
 TestDescription_GuiTest_testSetComp_NameReuse() : CxxTest::RealTestDescription( Tests_GuiTest, suiteDescription_GuiTest, 55, "testSetComp_NameReuse" ) {}
 void runTest() { suite_GuiTest.testSetComp_NameReuse(); }
} testDescription_GuiTest_testSetComp_NameReuse;

static class TestDescription_GuiTest_testSetComp_RenameExisting : public CxxTest::RealTestDescription {
public:
 TestDescription_GuiTest_testSetComp_RenameExisting() : CxxTest::RealTestDescription( Tests_GuiTest, suiteDescription_GuiTest, 60, "testSetComp_RenameExisting" ) {}
 void runTest() { suite_GuiTest.testSetComp_RenameExisting(); }
} testDescription_GuiTest_testSetComp_RenameExisting;

static class TestDescription_GuiTest_testSetComp_RenameOldRemoved : public CxxTest::RealTestDescription {
public:
 TestDescription_GuiTest_testSetComp_RenameOldRemoved() : CxxTest::RealTestDescription( Tests_GuiTest, suiteDescription_GuiTest, 65, "testSetComp_RenameOldRemoved" ) {}
 void runTest() { suite_GuiTest.testSetComp_RenameOldRemoved(); }
} testDescription_GuiTest_testSetComp_RenameOldRemoved;

#include "C:/Users/Arian/Documents/My Dropbox/DSV/Termin 3/PROG3/GameEngine/src/keyeventtest.h"

static KeyEventTest suite_KeyEventTest;

static CxxTest::List Tests_KeyEventTest = { 0, 0 };
CxxTest::StaticSuiteDescription suiteDescription_KeyEventTest( "C:/Users/Arian/Documents/My Dropbox/DSV/Termin 3/PROG3/GameEngine/src/keyeventtest.h", 7, "KeyEventTest", suite_KeyEventTest, Tests_KeyEventTest );

static class TestDescription_KeyEventTest_testFunction : public CxxTest::RealTestDescription {
public:
 TestDescription_KeyEventTest_testFunction() : CxxTest::RealTestDescription( Tests_KeyEventTest, suiteDescription_KeyEventTest, 11, "testFunction" ) {}
 void runTest() { suite_KeyEventTest.testFunction(); }
} testDescription_KeyEventTest_testFunction;

#include "C:/Users/Arian/Documents/My Dropbox/DSV/Termin 3/PROG3/GameEngine/src/resourcetest.h"

static ResourceTest suite_ResourceTest;

static CxxTest::List Tests_ResourceTest = { 0, 0 };
CxxTest::StaticSuiteDescription suiteDescription_ResourceTest( "C:/Users/Arian/Documents/My Dropbox/DSV/Termin 3/PROG3/GameEngine/src/resourcetest.h", 10, "ResourceTest", suite_ResourceTest, Tests_ResourceTest );

static class TestDescription_ResourceTest_testExistingImage : public CxxTest::RealTestDescription {
public:
 TestDescription_ResourceTest_testExistingImage() : CxxTest::RealTestDescription( Tests_ResourceTest, suiteDescription_ResourceTest, 23, "testExistingImage" ) {}
 void runTest() { suite_ResourceTest.testExistingImage(); }
} testDescription_ResourceTest_testExistingImage;

static class TestDescription_ResourceTest_testDuplicates : public CxxTest::RealTestDescription {
public:
 TestDescription_ResourceTest_testDuplicates() : CxxTest::RealTestDescription( Tests_ResourceTest, suiteDescription_ResourceTest, 27, "testDuplicates" ) {}
 void runTest() { suite_ResourceTest.testDuplicates(); }
} testDescription_ResourceTest_testDuplicates;

static class TestDescription_ResourceTest_testNonExistantImage : public CxxTest::RealTestDescription {
public:
 TestDescription_ResourceTest_testNonExistantImage() : CxxTest::RealTestDescription( Tests_ResourceTest, suiteDescription_ResourceTest, 33, "testNonExistantImage" ) {}
 void runTest() { suite_ResourceTest.testNonExistantImage(); }
} testDescription_ResourceTest_testNonExistantImage;

#include "C:/Users/Arian/Documents/My Dropbox/DSV/Termin 3/PROG3/GameEngine/src/spritetest.h"

static SpriteTest suite_SpriteTest;

static CxxTest::List Tests_SpriteTest = { 0, 0 };
CxxTest::StaticSuiteDescription suiteDescription_SpriteTest( "C:/Users/Arian/Documents/My Dropbox/DSV/Termin 3/PROG3/GameEngine/src/spritetest.h", 10, "SpriteTest", suite_SpriteTest, Tests_SpriteTest );

static class TestDescription_SpriteTest_testConstructor : public CxxTest::RealTestDescription {
public:
 TestDescription_SpriteTest_testConstructor() : CxxTest::RealTestDescription( Tests_SpriteTest, suiteDescription_SpriteTest, 23, "testConstructor" ) {}
 void runTest() { suite_SpriteTest.testConstructor(); }
} testDescription_SpriteTest_testConstructor;

static class TestDescription_SpriteTest_testTranslate : public CxxTest::RealTestDescription {
public:
 TestDescription_SpriteTest_testTranslate() : CxxTest::RealTestDescription( Tests_SpriteTest, suiteDescription_SpriteTest, 31, "testTranslate" ) {}
 void runTest() { suite_SpriteTest.testTranslate(); }
} testDescription_SpriteTest_testTranslate;

static class TestDescription_SpriteTest_testMoveTo : public CxxTest::RealTestDescription {
public:
 TestDescription_SpriteTest_testMoveTo() : CxxTest::RealTestDescription( Tests_SpriteTest, suiteDescription_SpriteTest, 42, "testMoveTo" ) {}
 void runTest() { suite_SpriteTest.testMoveTo(); }
} testDescription_SpriteTest_testMoveTo;

static class TestDescription_SpriteTest_testResize : public CxxTest::RealTestDescription {
public:
 TestDescription_SpriteTest_testResize() : CxxTest::RealTestDescription( Tests_SpriteTest, suiteDescription_SpriteTest, 53, "testResize" ) {}
 void runTest() { suite_SpriteTest.testResize(); }
} testDescription_SpriteTest_testResize;

static class TestDescription_SpriteTest_testResize_Negative : public CxxTest::RealTestDescription {
public:
 TestDescription_SpriteTest_testResize_Negative() : CxxTest::RealTestDescription( Tests_SpriteTest, suiteDescription_SpriteTest, 59, "testResize_Negative" ) {}
 void runTest() { suite_SpriteTest.testResize_Negative(); }
} testDescription_SpriteTest_testResize_Negative;

#include <cxxtest/Root.cpp>
