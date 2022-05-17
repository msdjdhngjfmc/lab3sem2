#include "pch.h"
#include "CppUnitTest.h"
#include <fstream>
#include "..\lab3\lab3.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;


namespace lab3test
{
    TEST_CLASS(lab3test)
    {
    public:

        TEST_METHOD(FindCity)
        {
            createListCity();

            std::ifstream file("city.txt");
            std::string str;
            std::string delimiter = ";";
            size_t pos = 0;
            std::string token;
            while (getline(file, str)) {
                string arrStr[2];
                int i = 0;
                int arrInt[2];
                while (((pos = str.find(delimiter)) != std::string::npos) && i != 2) {
                    arrStr[i] = str.substr(0, pos);
                    i++;
                    str.erase(0, pos + delimiter.length());
                }
                i = 0;

                if (index == 1)
                    Citys = Init(arrStr[0], index++);
                if (!FindItem(Citys, arrStr[0]))
                    AddItem(Citys, arrStr[0], index++);
                if (!FindItem(Citys, arrStr[1]))
                    AddItem(Citys, arrStr[1], index++);

            }

            Assert::IsTrue(FindItem(Citys, "Москва"));

        }
        TEST_METHOD(PriceCheck)
        {

            Assert::AreEqual(step(1, 4, 1), 660);
        }
        TEST_METHOD(FindNA)
        {
            std::ifstream file("city.txt");
            std::string str;
            std::string delimiter = ";";
            size_t pos = 0;
            std::string token;
            while (getline(file, str)) {
                string arrStr[2];
                int i = 0;
                int arrInt[2];
                while (((pos = str.find(delimiter)) != std::string::npos) && i != 2) {
                    arrStr[i] = str.substr(0, pos);
                    i++;
                    str.erase(0, pos + delimiter.length());
                }
                i = 0;

                if (index == 1)
                    Citys = Init(arrStr[0], index++);
                if (!FindItem(Citys, arrStr[0]))
                    AddItem(Citys, arrStr[0], index++);
                if (!FindItem(Citys, arrStr[1]))
                    AddItem(Citys, arrStr[1], index++);

            }
            Assert::IsFalse(FindItem(Citys, "Казань"));
        }
    };
}