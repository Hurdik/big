#include "CppUnitTest.h"

#include "../../include/big_core_input.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace test
{		
	TEST_CLASS(BigCoreInput_UnitTest)
	{
	public:
		
		TEST_METHOD(EmptyConstructor)
		{
            BigCoreInput big;
            big.openFile("test.big");
            Assert::AreEqual(2ull, big.getNumberOfImages());
            Assert::AreEqual(1ull, big.getNumberOfTiles());
            Assert::AreEqual(3ull, big.getImageHeight());
            Assert::AreEqual(4ull, big.getImageWidth());
            Assert::AreEqual(1ull, big.getNumberOfPlanes());

            big.loadToMemory();
            // todo: test correcness of the data
		}

        TEST_METHOD(InputConstructor)
        {
            BigCoreInput big("test.big");
            Assert::AreEqual(2ull, big.getNumberOfImages());
            Assert::AreEqual(1ull, big.getNumberOfTiles());
            Assert::AreEqual(3ull, big.getImageHeight());
            Assert::AreEqual(4ull, big.getImageWidth());
            Assert::AreEqual(1ull, big.getNumberOfPlanes());

            big.loadToMemory();
            // todo: test correcness of the data
        }

        TEST_METHOD(BigData)
        {
            BigCoreInput big;
            big.readFile("test.big", 0);
            Assert::AreEqual(2ull, big.getNumberOfImages());
            Assert::AreEqual(1ull, big.getNumberOfTiles());
            Assert::AreEqual(3ull, big.getImageHeight());
            Assert::AreEqual(4ull, big.getImageWidth());
            Assert::AreEqual(1ull, big.getNumberOfPlanes());

            big.loadToMemory(); // must not read anything

            // todo: test correcness of the data that are read instantly from the file
        }

        // todo: test everything possible

        // todo: test performance, employ profiling, optimize if possible
    };
}
