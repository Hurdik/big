#include "CppUnitTest.h"

#include "../../include/big_core_output.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace test
{
    TEST_CLASS(BigCoreOutput_UnitTest)
    {
    public:

        TEST_METHOD(EmptyConstructor)
        {
            BigCoreOutput big;

            Assert::AreEqual(0ull, big.getNumberOfImages());
            Assert::AreEqual(1ull, big.getNumberOfTiles());
            Assert::AreEqual(0ull, big.getImageHeight());
            Assert::AreEqual(0ull, big.getImageWidth());
            Assert::AreEqual(1ull, big.getNumberOfPlanes());
        }

        // todo: test all constructors meaningly

        TEST_METHOD(OutputAndReserveConstructor4)
        {
            std::vector<uint64_t> dataOrder = { 1, 3, 4, 5, 2 };
            std::vector<uint8_t> dataType = { 8 };
            BigCoreOutput big("test.big", dataOrder, dataType, 2, 3, 4);

            Assert::AreEqual(2ull, big.getNumberOfImages());
            Assert::AreEqual(1ull, big.getNumberOfTiles());
            Assert::AreEqual(3ull, big.getImageHeight());
            Assert::AreEqual(4ull, big.getImageWidth());
            Assert::AreEqual(1ull, big.getNumberOfPlanes());
        }

        // todo
        // Copy data to big using iterators and consequently write everything to file
        //TEST_METHOD(OutputIteratorsTest1)
        //{
        //    // todo: prepare some data
        //    std::vector<std::vector<int>> images;

        //    // prepare big object
        //    std::vector<uint64_t> dataOrder = { 1, 3, 4, 5, 2 };
        //    std::vector<uint8_t> dataType = { 8 };
        //    BigCoreOutput big(dataOrder, dataType, 2, 3, 4);

        //    // copy data to big
        //    auto big_it = big.begin();
        //    for (auto it = images.cbegin(); it != images.cend(); ++it, ++big_it) {
        //        *big_it = *it;
        //    }

        //    // write to file
        //    big.writeFile("test.big");
        //}

        // Write data to file using iterators
        TEST_METHOD(OutputIteratorsTest2)
        {
            // todo: prepare some data
            std::vector<std::vector<int>> images;

            // prepare big object
            std::vector<uint64_t> dataOrder = { 1, 3, 4, 5, 2 };
            std::vector<uint8_t> dataType = { 8 };
            BigCoreOutput big("test.big", dataOrder, dataType, 2, 3, 4);

            // copy data to big
            int imageNum = 0;
            for (auto it = images.cbegin(); it != images.cend(); ++it, ++imageNum) {
                big.addTile(*it, imageNum);
            }
        }

        // todo: test everything possible

        // todo: test performance, employ profiling, optimize if possible
    };
}
