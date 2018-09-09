#include "CppUnitTest.h"

#include "../../include/big_core_input.h"
#include "../../include/big_core_output.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace test
{
    TEST_CLASS(BigCore_UnitTest)
    {
    public:

        TEST_METHOD(ReorganizeData)
        {
            std::vector<uint64_t> newDataOrder = { 1, 2, 3, 4, 5 };

            BigCoreInput bigIn("test.big");
            BigCoreOutput bigOut("test2.big", newDataOrder, bigIn.getDataType(), bigIn.getNumberOfImages(), bigIn.getImageHeight(), bigIn.getImageWidth(), bigIn.getNumberOfPlanes(), bigIn.getNumberOfTiles());

            // todo: using iterators if even possible
            //auto oit = bigOut.begin();
            //for (auto iit = bigIn.cbegin(); iit != bigIn.cend(); ++iit, ++oit) {
            //    *oit = *iit;
            //}

            // using addTile / getTile
            for (uint64_t imageNum = 0; imageNum < bigIn.getNumberOfImages(); ++imageNum) {
                for (uint64_t tileNum = 0; tileNum < bigIn.getNumberOfTiles(); ++tileNum) {
                    std::vector<int> data;
                    bigIn.getTile(data, imageNum, tileNum);
                    bigOut.addTile(data, imageNum, tileNum);
                }
            }

            bigOut.closeFile();

            BigCoreInput bigIn2("test2.big");
            Assert::AreEqual(2ull, bigIn2.getNumberOfImages());
            Assert::AreEqual(1ull, bigIn2.getNumberOfTiles());
            Assert::AreEqual(3ull, bigIn2.getImageHeight());
            Assert::AreEqual(4ull, bigIn2.getImageWidth());
            Assert::AreEqual(1ull, bigIn2.getNumberOfPlanes());

            bigIn2.loadToMemory();
            // todo: test correcness of the data
        }

        // todo: test everything possible
    };
}
