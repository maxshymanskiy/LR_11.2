#include "pch.h"
#include "CppUnitTest.h"
#include <fstream>
#include <string>
#include "../LR_11.2.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTestForLineProcessing
{
    TEST_CLASS(UnitTestForLineProcessing)
    {
    public:

        TEST_METHOD(TestProcessLine_RemoveLeadingZeros)
        {
            char inputLine[] = "00123 text 0456.";
            std::ofstream outputFile("testOutput.txt");
            processLine(inputLine, outputFile);
            outputFile.close();

            std::ifstream resultFile("testOutput.txt");
            std::string resultLine;
            std::getline(resultFile, resultLine);
            resultFile.close();

            Assert::AreEqual(std::string("123 text 456."), resultLine, L"������ ������� ���������� ����.");
            remove("testOutput.txt");
        }

        TEST_METHOD(TestProcessLine_TrimFractionalPart)
        {
            char inputLine[] = "0.12345 more text";
            std::ofstream outputFile("testOutput.txt");
            processLine(inputLine, outputFile);
            outputFile.close();

            std::ifstream resultFile("testOutput.txt");
            std::string resultLine;
            std::getline(resultFile, resultLine);
            resultFile.close();

            Assert::AreEqual(std::string("0.12 more text"), resultLine, L"������ ���������� ������� �������.");
            remove("testOutput.txt");
        }

        TEST_METHOD(TestProcessLine_MixedCases)
        {
            char inputLine[] = "00123 text 0456. 0.12345 numbers";
            std::ofstream outputFile("testOutput.txt");
            processLine(inputLine, outputFile);
            outputFile.close();

            std::ifstream resultFile("testOutput.txt");
            std::string resultLine;
            std::getline(resultFile, resultLine);
            resultFile.close();

            Assert::AreEqual(std::string("123 text 456. 0.12 numbers"), resultLine, L"������ ������� ������� �������.");
            remove("testOutput.txt");
        }
    };
}
