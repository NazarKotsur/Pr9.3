#include "pch.h"
#include "CppUnitTest.h"
#include "../Pr9.3/Pr9.3.cpp"


using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest1
{
    TEST_CLASS(UnitTest1)
    {
    public:

        TEST_METHOD(TestSortByName)
        {
            Tovar tovary[] = {
                {"Товар3", 30.0, 3, 10.0},
                {"Товар1", 10.0, 1, 5.0},
                {"Товар2", 20.0, 2, 8.0}
            };

            SortByName(tovary, 3);

            Assert::AreEqual(std::string("Товар1"), tovary[0].nazva);
            Assert::AreEqual(std::string("Товар2"), tovary[1].nazva);
            Assert::AreEqual(std::string("Товар3"), tovary[2].nazva);
        }

    };
}