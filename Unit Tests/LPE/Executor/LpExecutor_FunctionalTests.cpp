#include "CppUnitTest.h"
#include "../../../../Light-Server/src/LPE/StateBuilder/LpJsonStateBuilder.h"
#include "../../../../Light-Server/src/LPE/StateBuilder/JsonInstructionBuilderFactory.h"

#include "../../../../Light-Server/src/LPE/StateBuilder/LpJsonState.h";
#include "../../../../Light-Server/src/StringProcessor.h"
#include "../../../../Light-Server/src/LPE/Executor/LpExecutor.h"

#include "LpExecutor_Tester.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace LS {
	namespace LPE {
		namespace Executor {
			/*!
				@brief		Tests that Light Programs are executed as expected.
							NOTE: these are functional tests as we are not stubbing
							critical dependencies.
				@author		Kevin White
				@date		31 Dec 2020
			*/
			TEST_CLASS(LpExecutor_Execute)
			{
			public:
				TEST_METHOD(WhenOneLPI_OutputAsExpected)
				{
					// arrange
					const int numberOfExpectedOutputs = 2;
					char* expectedOutputs[numberOfExpectedOutputs] = {
						"1  :00000001R",
						"2  :"
					};
					LpExecutor_Tester executorTester(expectedOutputs, numberOfExpectedOutputs);
					char* lp =
"{\
	\"name\" : \"testing\",\
	\"instructions\" : [\
		\"00010000\"\
	]\
}";


					// act
					char* failingExpectedOutput = executorTester.TestExecutor(lp);

					// assert
					if (failingExpectedOutput == nullptr) Assert::IsTrue(1 == 1);
					else Assert::AreEqual<char*>(failingExpectedOutput, executorTester.renderingBuffer.GetBuffer());
				}

				TEST_METHOD(WhenOneLPIFourDuration_OutputAsExpected)
				{
					// arrange
					const int numberOfExpectedOutputs = 4;
					char* expectedOutputs[numberOfExpectedOutputs] = {
						// "1  :00000001R"
						"1  :00000001R",
						"2  :",
						"3  :",
						"4  :"
					};
					LpExecutor_Tester executorTester(expectedOutputs, numberOfExpectedOutputs);
					char* lp =
"{\
	\"name\" : \"testing\",\
	\"instructions\" : [\
		\"00040000\"\
	]\
}";


					// act
					char* failingExpectedOutput = executorTester.TestExecutor(lp);

					// assert
					if (failingExpectedOutput == nullptr) Assert::IsTrue(1 == 1);
					else Assert::AreEqual<char*>(failingExpectedOutput, executorTester.renderingBuffer.GetBuffer());
				}

				TEST_METHOD(WhenOTwoLPIs_OutputAsExpected)
				{
					// arrange
					const int numberOfExpectedOutputs = 3;
					char* expectedOutputs[numberOfExpectedOutputs] = {
						// "1  :00000001R"
						"1  :00000001R",
						"2  :FFFFFF01R",
						"3  :"
					};
					LpExecutor_Tester executorTester(expectedOutputs, numberOfExpectedOutputs);
					char* lp =
"{\
	\"name\" : \"testing\",\
	\"instructions\" : [\
		\"00010000\",\
		\"01010000FFFFFF\"\
	]\
}";


					// act
					char* failingExpectedOutput = executorTester.TestExecutor(lp);

					// assert
					if (failingExpectedOutput == nullptr) Assert::IsTrue(1 == 1);
					else Assert::AreEqual<char*>(failingExpectedOutput, executorTester.renderingBuffer.GetBuffer());
				}

				TEST_METHOD(WhenOTwoLPIsFourDuration_OutputAsExpected)
				{
					// arrange
					const int numberOfExpectedOutputs = 6;
					char* expectedOutputs[numberOfExpectedOutputs] = {
						// "1  :00000001R"
						"1  :00000001R",
						"2  :",
						"3  :",
						"4  :",
						"5  :FFFFFF01R",
						"6  :"
					};
					LpExecutor_Tester executorTester(expectedOutputs, numberOfExpectedOutputs);
					char* lp =
"{\
	\"name\" : \"testing\",\
	\"instructions\" : [\
		\"00040000\",\
		\"01010000FFFFFF\"\
	]\
}";


					// act
					char* failingExpectedOutput = executorTester.TestExecutor(lp);

					// assert
					if (failingExpectedOutput == nullptr) Assert::IsTrue(1 == 1);
					else Assert::AreEqual<char*>(failingExpectedOutput, executorTester.renderingBuffer.GetBuffer());
				}

				TEST_METHOD(WhenRepeatIns2Iterations_OutputAsExpected)
				{
					// arrange
					const int numberOfExpectedOutputs = 4;
					char* expectedOutputs[numberOfExpectedOutputs] = {
						"1  :00000001R",
						"2  :00000001R",
						"3  :",
						"4  :"
					};
					LpExecutor_Tester executorTester(expectedOutputs, numberOfExpectedOutputs);
					char* lp =
"{\
	\"name\" : \"testing\",\
	\"instructions\" : [\
		{\
			\"repeat\" : {\
				\"times\" : 2,\
				\"instructions\" : [\
					\"00010000\"\
				]\
			}\
		}\
	]\
}";


					// act
					char* failingExpectedOutput = executorTester.TestExecutor(lp);

					// assert
					if (failingExpectedOutput == nullptr) Assert::IsTrue(1 == 1);
					else Assert::AreEqual<char*>(failingExpectedOutput, executorTester.renderingBuffer.GetBuffer());
				}

				TEST_METHOD(WhenRepeatIns2ThenRepeatIns2_OutputAsExpected)
				{
					// arrange
					const int numberOfExpectedOutputs = 13;
					char* expectedOutputs[numberOfExpectedOutputs] = {
						"1  :00000001R",
						"2  :FFFFFF01R",
						"3  :AAAAAA01R",
						"4  :BBBBBB01R",
						"5  :AAAAAA01R",
						"6  :BBBBBB01R",
						"7  :00000001R",
						"8  :FFFFFF01R",
						"9  :AAAAAA01R",
						"10 :BBBBBB01R",
						"11 :AAAAAA01R",
						"12 :BBBBBB01R",
						"13 :"
					};
					LpExecutor_Tester executorTester(expectedOutputs, numberOfExpectedOutputs);
					char* lp =
"{\
	\"name\" : \"testing\",\
	\"instructions\" : [\
		{\
			\"repeat\" : {\
				\"times\" : 2,\
				\"instructions\" : [\
					\"00010000\",\
					\"01010000FFFFFF\",\
					{\
						\"repeat\" : {\
							\"times\" : 2,\
							\"instructions\" : [\
								\"01010000AAAAAA\",\
								\"01010000BBBBBB\"\
							]\
						}\
					}\
				]\
			}\
		}\
	]\
}";


					// act
					char* failingExpectedOutput = executorTester.TestExecutor(lp);

					// assert
					if (failingExpectedOutput == nullptr) Assert::IsTrue(1 == 1);
					else Assert::AreEqual<char*>(failingExpectedOutput, executorTester.renderingBuffer.GetBuffer());
				}

				TEST_METHOD(WhenInfiniteLoop2Ins_OutputAsExpected)
				{
					// arrange
					const int numberOfExpectedOutputs = 10;
					char* expectedOutputs[numberOfExpectedOutputs] = {
						"1  :00000001R",
						"2  :FFFFFF01R",
						"3  :00000001R",
						"4  :FFFFFF01R",
						"5  :00000001R",
						"6  :FFFFFF01R",
						"7  :00000001R",
						"8  :FFFFFF01R",
						"9  :00000001R",
						"10 :FFFFFF01R"
					};
					LpExecutor_Tester executorTester(expectedOutputs, numberOfExpectedOutputs);
					char* lp =
"{\
	\"name\" : \"testing\",\
	\"instructions\" : [\
		{\
			\"repeat\" : {\
				\"times\" : 0,\
				\"instructions\" : [\
					\"00010000\",\
					\"01010000FFFFFF\"\
				]\
			}\
		}\
	]\
}";


					// act
					char* failingExpectedOutput = executorTester.TestExecutor(lp);

					// assert
					if (failingExpectedOutput == nullptr) Assert::IsTrue(1 == 1);
					else Assert::AreEqual<char*>(failingExpectedOutput, executorTester.renderingBuffer.GetBuffer());
				}

				TEST_METHOD(WhenLoopThenInfiniteLoop_OutputAsExpected)
				{
					// arrange
					const int numberOfExpectedOutputs = 6;
					char* expectedOutputs[numberOfExpectedOutputs] = {
						"1  :00000001R",
						"2  :FFFFFF01R",
						"3  :BBBBBB01R",
						"4  :BBBBBB01R",
						"5  :BBBBBB01R",
						"6  :BBBBBB01R",
					};
					LpExecutor_Tester executorTester(expectedOutputs, numberOfExpectedOutputs);
					char* lp =
"{\
	\"name\" : \"testing\",\
	\"instructions\" : [\
		{\
			\"repeat\" : {\
				\"times\" : 2,\
				\"instructions\" : [\
					\"00010000\",\
					\"01010000FFFFFF\",\
					{\
						\"repeat\" : {\
							\"times\" : 0,\
							\"instructions\" : [\
								\"01010000BBBBBB\"\
							]\
						}\
					}\
				]\
			}\
		}\
	]\
}";


					// act
					char* failingExpectedOutput = executorTester.TestExecutor(lp);

					// assert
					if (failingExpectedOutput == nullptr) Assert::IsTrue(1 == 1);
					else Assert::AreEqual<char*>(failingExpectedOutput, executorTester.renderingBuffer.GetBuffer());
				}

				TEST_METHOD(WhenRepeatThenFollowedByRepeat_OutputAsExpected)
				{
					// arrange
					const int numberOfExpectedOutputs = 18;
					char* expectedOutputs[numberOfExpectedOutputs] = {
						"1  :00000001R",
						"2  :FFFFFF01R",
						"3  :00000001R",
						"4  :FFFFFF01R",
						"5  :AAAAAA01R",
						"6  :BBBBBB01R",
						"7  :AAAAAA01R",
						"8  :BBBBBB01R",
						"9  :AAAAAA01R",
						"10 :BBBBBB01R",
						"11 :AAAAAA01R",
						"12 :BBBBBB01R",
						"13 :AAAAAA01R",
						"14 :BBBBBB01R",
						"15 :",
						"16 :",
						"17 :",
						"18 :"
					};
					LpExecutor_Tester executorTester(expectedOutputs, numberOfExpectedOutputs);
					char* lp =
"{\
	\"name\" : \"testing\",\
	\"instructions\" : [\
		{\
			\"repeat\" : {\
				\"times\" : 2,\
				\"instructions\" : [\
					\"00010000\",\
					\"01010000FFFFFF\"\
				]\
			}\
		},\
		{\
			\"repeat\" : {\
				\"times\" : 5,\
				\"instructions\" : [\
					\"01010000AAAAAA\",\
					\"01010000BBBBBB\"\
				]\
			}\
		}\
	]\
}";


					// act
					char* failingExpectedOutput = executorTester.TestExecutor(lp);

					// assert
					if (failingExpectedOutput == nullptr) Assert::IsTrue(1 == 1);
					else Assert::AreEqual<char*>(failingExpectedOutput, executorTester.renderingBuffer.GetBuffer());
				}

				TEST_METHOD(WhenRepeatFollowedByThreeIns_OutputAsExpected)
				{
					// arrange
					const int numberOfExpectedOutputs = 8;
					char* expectedOutputs[numberOfExpectedOutputs] = {
						"1  :00000001R",
						"2  :FFFFFF01R",
						"3  :00000001R",
						"4  :FFFFFF01R",
						"5  :AAAAAA01R",
						"6  :BBBBBB01R",
						"7  :CCCCCC01R",
						"8  :"
					};
					LpExecutor_Tester executorTester(expectedOutputs, numberOfExpectedOutputs);
					char* lp =
"{\
	\"name\" : \"testing\",\
	\"instructions\" : [\
		{\
			\"repeat\" : {\
				\"times\" : 2,\
				\"instructions\" : [\
					\"00010000\",\
					\"01010000FFFFFF\"\
				]\
			}\
		},\
		\"01010000AAAAAA\",\
		\"01010000BBBBBB\",\
		\"01010000CCCCCC\"\
	]\
}";


					// act
					char* failingExpectedOutput = executorTester.TestExecutor(lp);

					// assert
					if (failingExpectedOutput == nullptr) Assert::IsTrue(1 == 1);
					else Assert::AreEqual<char*>(failingExpectedOutput, executorTester.renderingBuffer.GetBuffer());
				}

				TEST_METHOD(WhenRepeatFollowedByThreeInsFollowedByRepeat_OutputAsExpected)
				{
					// arrange
					const int numberOfExpectedOutputs = 12;
					char* expectedOutputs[numberOfExpectedOutputs] = {
						"1  :00000001R",
						"2  :FFFFFF01R",
						"3  :00000001R",
						"4  :FFFFFF01R",
						"5  :AAAAAA01R",
						"6  :BBBBBB01R",
						"7  :CCCCCC01R",
						"8  :00000001R",
						"9  :FFFFFF01R",
						"10 :00000001R",
						"11 :FFFFFF01R",
						"12 :"
					};
					LpExecutor_Tester executorTester(expectedOutputs, numberOfExpectedOutputs);
					char* lp =
"{\
	\"name\" : \"testing\",\
	\"instructions\" : [\
		{\
			\"repeat\" : {\
				\"times\" : 2,\
				\"instructions\" : [\
					\"00010000\",\
					\"01010000FFFFFF\"\
				]\
			}\
		},\
		\"01010000AAAAAA\",\
		\"01010000BBBBBB\",\
		\"01010000CCCCCC\",\
		{\
			\"repeat\" : {\
				\"times\" : 2,\
				\"instructions\" : [\
					\"00010000\",\
					\"01010000FFFFFF\"\
				]\
			}\
		}\
	]\
}";


					// act
					char* failingExpectedOutput = executorTester.TestExecutor(lp);

					// assert
					if (failingExpectedOutput == nullptr) Assert::IsTrue(1 == 1);
					else Assert::AreEqual<char*>(failingExpectedOutput, executorTester.renderingBuffer.GetBuffer());
				}

				TEST_METHOD(WhenRepeatThreeLevelsDeep_OutputAsExpected)
				{
					// arrange
					const int numberOfExpectedOutputs = 17;
					char* expectedOutputs[numberOfExpectedOutputs] = {
						"1  :00000001R",
						"2  :FFFFFF01R",
						"3  :00000001R",
						"4  :FFFFFF01R",
						"5  :00000001R",
						"6  :FFFFFF01R",
						"7  :00000001R",
						"8  :FFFFFF01R",
						"9  :00000001R",
						"10 :FFFFFF01R",
						"11 :00000001R",
						"12 :FFFFFF01R",
						"13 :00000001R",
						"14 :FFFFFF01R",
						"15 :00000001R",
						"16 :FFFFFF01R",
						"17 :"
					};
					LpExecutor_Tester executorTester(expectedOutputs, numberOfExpectedOutputs);
					char* lp =
"{\
	\"name\" : \"testing\",\
	\"instructions\" : [\
		{\
			\"repeat\" : {\
				\"times\" : 2,\
				\"instructions\" : [\
				{\
					\"repeat\" : {\
						\"times\" : 2,\
						\"instructions\" : [\
						{\
							\"repeat\" : {\
								\"times\" : 2,\
								\"instructions\" : [\
									\"00010000\",\
									\"01010000FFFFFF\"\
								]\
							}\
						}\
						]\
					}\
				]\
			}\
		}\
	]\
}";


					// act
					char* failingExpectedOutput = executorTester.TestExecutor(lp);

					// assert
					if (failingExpectedOutput == nullptr) Assert::IsTrue(1 == 1);
					else Assert::AreEqual<char*>(failingExpectedOutput, executorTester.renderingBuffer.GetBuffer());
				}

				TEST_METHOD(WhenInsThenRepeat_OutputAsExpected)
				{
					// arrange
					const int numberOfExpectedOutputs = 8;
					char* expectedOutputs[numberOfExpectedOutputs] = {
						"1  :AAAAAA01R",
						"2  :BBBBBB01R",
						"3  :CCCCCC01R",
						"4  :00000001R",
						"5  :FFFFFF01R",
						"6  :00000001R",
						"7  :FFFFFF01R",
						"8  :"
					};
					LpExecutor_Tester executorTester(expectedOutputs, numberOfExpectedOutputs);
					char* lp =
"{\
	\"name\" : \"testing\",\
	\"instructions\" : [\
		\"01010000AAAAAA\",\
		\"01010000BBBBBB\",\
		\"01010000CCCCCC\",\
		{\
			\"repeat\" : {\
				\"times\" : 2,\
				\"instructions\" : [\
					\"00010000\",\
					\"01010000FFFFFF\"\
				]\
			}\
		}\
	]\
}";


					// act
					char* failingExpectedOutput = executorTester.TestExecutor(lp);

					// assert
					if (failingExpectedOutput == nullptr) Assert::IsTrue(1 == 1);
					else Assert::AreEqual<char*>(failingExpectedOutput, executorTester.renderingBuffer.GetBuffer());
				}

				TEST_METHOD(WhenComplexProgram_OutputAsExpected)
				{
					// arrange
					const int numberOfExpectedOutputs = 15;
					char* expectedOutputs[numberOfExpectedOutputs] = {
						"1  :AAAAAA01R",
						"2  :BBBBBB01R",
						"3  :CCCCCC01R",
						"4  :00000001R",
						"5  :FFFFFF01R",
						"6  :AAAAAA01R",
						"7  :AAAAAA01R",
						"8  :00000001R",
						"9  :FFFFFF01R",
						"10 :AAAAAA01R",
						"11 :AAAAAA01R",
						"12 :DDDDDD01R",
						"13 :EEEEEE01R",
						"14 :EEEEEE01R",
						"15 :"
					};
					LpExecutor_Tester executorTester(expectedOutputs, numberOfExpectedOutputs);
					char* lp =
"{\
	\"name\" : \"testing\",\
	\"instructions\" : [\
		\"01010000AAAAAA\",\
		\"01010000BBBBBB\",\
		\"01010000CCCCCC\",\
		{\
			\"repeat\" : {\
				\"times\" : 2,\
				\"instructions\" : [\
					\"00010000\",\
					\"01010000FFFFFF\",\
					{\
						\"repeat\" : {\
							\"times\" : 2,\
							\"instructions\" : [\
								\"01010000AAAAAA\"\
							]\
						}\
					}\
				]\
			}\
		},\
		\"01010000DDDDDD\",\
		{\
			\"repeat\" : {\
				\"times\" : 2,\
				\"instructions\" : [\
					\"01010000EEEEEE\"\
				]\
			}\
		}\
	]\
}";


					// act
					char* failingExpectedOutput = executorTester.TestExecutor(lp);

					// assert
					if (failingExpectedOutput == nullptr) Assert::IsTrue(1 == 1);
					else Assert::AreEqual<char*>(failingExpectedOutput, executorTester.renderingBuffer.GetBuffer());
				}

				TEST_METHOD(WhenSliderProgram_OutputAsExpected)
				{
					// arrange
					const int numberOfExpectedOutputs = 8;
					char* expectedOutputs[numberOfExpectedOutputs] = {
						"1  :FF00000200FF0006",
						"2  :00FF0001FF00000200FF0005",
						"3  :00FF0002FF00000200FF0004",
						"4  :00FF0003FF00000200FF0003",
						"5  :00FF0004FF00000200FF0002",
						"6  :00FF0005FF00000200FF0001",
						"7  :00FF0006FF000002",
						"8  :",
					};
					LpExecutor_Tester executorTester(expectedOutputs, numberOfExpectedOutputs);
					char* lp =
"{\
	\"name\" : \"testing\",\
	\"instructions\" : [\
		\"030100000200000FF000000FF00\"\
	]\
}";


					// act
					char* failingExpectedOutput = executorTester.TestExecutor(lp);

					// assert
					if (failingExpectedOutput == nullptr) Assert::IsTrue(1 == 1);
					else Assert::AreEqual<char*>(failingExpectedOutput, executorTester.renderingBuffer.GetBuffer());
				}

				TEST_METHOD(WhenSliderStartFarProgram_OutputAsExpected)
				{
					// arrange
					const int numberOfExpectedOutputs = 8;
					char* expectedOutputs[numberOfExpectedOutputs] = {
						"1  :00FF0006FF000002",
						"2  :00FF0005FF00000200FF0001",
						"3  :00FF0004FF00000200FF0002",
						"4  :00FF0003FF00000200FF0003",
						"5  :00FF0002FF00000200FF0004",
						"6  :00FF0001FF00000200FF0005",
						"7  :FF00000200FF0006",
						"8  :"
					};
					LpExecutor_Tester executorTester(expectedOutputs, numberOfExpectedOutputs);
					char* lp =
"{\
	\"name\" : \"testing\",\
	\"instructions\" : [\
		\"030100000210000FF000000FF00\"\
	]\
}";


					// act
					char* failingExpectedOutput = executorTester.TestExecutor(lp);

					// assert
					if (failingExpectedOutput == nullptr) Assert::IsTrue(1 == 1);
					else Assert::AreEqual<char*>(failingExpectedOutput, executorTester.renderingBuffer.GetBuffer());
				}

				TEST_METHOD(WhenSliderDuration2Program_OutputAsExpected)
				{
					// arrange
					const int numberOfExpectedOutputs = 15;
					char* expectedOutputs[numberOfExpectedOutputs] = {
						"1  :FF00000200FF0006",
						"2  :",
						"3  :00FF0001FF00000200FF0005",
						"4  :",
						"5  :00FF0002FF00000200FF0004",
						"6  :",
						"7  :00FF0003FF00000200FF0003",
						"8  :",
						"9  :00FF0004FF00000200FF0002",
						"10 :",
						"11 :00FF0005FF00000200FF0001",
						"12 :",
						"13 :00FF0006FF000002",
						"14 :",
						"15 :",
					};
					LpExecutor_Tester executorTester(expectedOutputs, numberOfExpectedOutputs);
					char* lp =
"{\
	\"name\" : \"testing\",\
	\"instructions\" : [\
		\"030200000200000FF000000FF00\"\
	]\
}";


					// act
					char* failingExpectedOutput = executorTester.TestExecutor(lp);

					// assert
					if (failingExpectedOutput == nullptr) Assert::IsTrue(1 == 1);
					else Assert::AreEqual<char*>(failingExpectedOutput, executorTester.renderingBuffer.GetBuffer());
				}

				TEST_METHOD(WhenFadeOutProgram_OutputAsExpected)
				{
					// arrange
					const int numberOfExpectedOutputs = 5;
					char* expectedOutputs[numberOfExpectedOutputs] = {
						"1  :FFFFFF01R",
						"2  :F5F5F501R",
						"3  :EBEBEB01R",
						"4  :E1E1E101R",
						"5  :D7D7D701R"
					};
					LpExecutor_Tester executorTester(expectedOutputs, numberOfExpectedOutputs);
					char* lp =
"{\
	\"name\" : \"testing\",\
	\"instructions\" : [\
		\"040100000A1FFFFFF000000\"\
	]\
}";


					// act
					char* failingExpectedOutput = executorTester.TestExecutor(lp);

					// assert
					if (failingExpectedOutput == nullptr) Assert::IsTrue(1 == 1);
					else Assert::AreEqual<char*>(failingExpectedOutput, executorTester.renderingBuffer.GetBuffer());
				}

				TEST_METHOD(WhenFadeInProgramDuration3_OutputAsExpected)
				{
					// arrange
					const int numberOfExpectedOutputs = 15;
					char* expectedOutputs[numberOfExpectedOutputs] = {
						"1  :00000001R",
						"2  :",
						"3  :",
						"4  :0A0A0A01R",
						"5  :",
						"6  :",
						"7  :14141401R",
						"8  :",
						"9  :",
						"10 :1E1E1E01R",
						"11 :",
						"12 :",
						"13 :28282801R",
						"14 :",
						"15 :"
					};
					LpExecutor_Tester executorTester(expectedOutputs, numberOfExpectedOutputs);
					char* lp =
"{\
	\"name\" : \"testing\",\
	\"instructions\" : [\
		\"040300000A0000000FFFFFF\"\
	]\
}";


					// act
					char* failingExpectedOutput = executorTester.TestExecutor(lp);

					// assert
					if (failingExpectedOutput == nullptr) Assert::IsTrue(1 == 1);
					else Assert::AreEqual<char*>(failingExpectedOutput, executorTester.renderingBuffer.GetBuffer());
				}

				TEST_METHOD(WhenFadeInsInLoopsWithDurations_OutputAsExpected)
				{
					// arrange
					const int numberOfExpectedOutputs = 24;
					char* expectedOutputs[numberOfExpectedOutputs] = {
						"1  :00000001R",
						"2  :",
						"3  :64646401R",
						"4  :",
						"5  :C8C8C801R",
						"6  :",
						"7  :FFFFFF01R",
						"8  :",
						"9  :FFFFFF01R",
						"10 :",
						"11 :",
						"12 :",
						"13 :9B9B9B01R",
						"14 :",
						"15 :",
						"16 :",
						"17 :37373701R",
						"18 :",
						"19 :",
						"20 :",
						"21 :00000001R",
						"22 :",
						"23 :",
						"24 :"
					};
					LpExecutor_Tester executorTester(expectedOutputs, numberOfExpectedOutputs);
					char* lp =
"{\
	\"name\" : \"testing\",\
	\"instructions\" : [\
		\"04020000640000000FFFFFF\",\
		\"04040000641FFFFFF000000\"\
	]\
}";


					// act
					char* failingExpectedOutput = executorTester.TestExecutor(lp);

					// assert
					if (failingExpectedOutput == nullptr) Assert::IsTrue(1 == 1);
					else Assert::AreEqual<char*>(failingExpectedOutput, executorTester.renderingBuffer.GetBuffer());
				}

				TEST_METHOD(WhenFadeInsThenSolid_OutputAsExpected)
				{
					// arrange
					const int numberOfExpectedOutputs = 15;
					char* expectedOutputs[numberOfExpectedOutputs] = {
						"1  :00000001R",
						"2  :",
						"3  :64646401R",
						"4  :",
						"5  :C8C8C801R",
						"6  :",
						"7  :FFFFFF01R",
						"8  :",
						"9  :00FF0001R",
						"10 :AAAAAA01R",
						"11 :",
						"12 :",
						"13 :",
						"14 :",
						"15 :"
					};
					LpExecutor_Tester executorTester(expectedOutputs, numberOfExpectedOutputs);
					char* lp =
"{\
	\"name\" : \"testing\",\
	\"instructions\" : [\
		\"04020000640000000FFFFFF\",\
		\"0101000000FF00\",\
		\"01010000AAAAAA\"\
	]\
}";


					// act
					char* failingExpectedOutput = executorTester.TestExecutor(lp);

					// assert
					if (failingExpectedOutput == nullptr) Assert::IsTrue(1 == 1);
					else Assert::AreEqual<char*>(failingExpectedOutput, executorTester.renderingBuffer.GetBuffer());
				}
			};
		}
	}
}