#include "CppUnitTest.h"
#include "../../../../Light-Server/src/LPE/StateBuilder/LpJsonStateBuilder.h"
#include "LpJsonState_TestHelper.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace LS {
	namespace LPE {
		namespace StateBuilder {
			TEST_CLASS(LpJsonStateBuilder_BuildState)
			{
			public:
				TEST_METHOD(WhenLpBufferNull_FalseReturned)
				{
					// arrange
					LEDConfig ledConfig;
					ledConfig.numberOfLEDs = 8;
					StringProcessor stringProcessor;
					LpiExecutorFactory lpiExecutorFactory;
					JsonInstructionBuilderFactory factory(&lpiExecutorFactory, &stringProcessor, &ledConfig);
					LpJsonStateBuilder stateBuilder(&factory);
					LpJsonState state;
					FixedSizeCharBuffer lp(1000);

					// act
					bool stateBuilt = stateBuilder.BuildState(nullptr, &state);

					// assert
					Assert::IsFalse(stateBuilt);
				}

				TEST_METHOD(WhenStateNull_FalseReturned)
				{
					// arrange
					LEDConfig ledConfig;
					ledConfig.numberOfLEDs = 8;
					StringProcessor stringProcessor;
					LpiExecutorFactory lpiExecutorFactory;
					JsonInstructionBuilderFactory factory(&lpiExecutorFactory, &stringProcessor, &ledConfig);
					LpJsonStateBuilder stateBuilder(&factory);
					LpJsonState state;
					FixedSizeCharBuffer lp(1000);

					// act
					bool stateBuilt = stateBuilder.BuildState(&lp, nullptr);

					// assert
					Assert::IsFalse(stateBuilt);
				}

				TEST_METHOD(WhenValidParams_TrueReturned)
				{
					// arrange
					LEDConfig ledConfig;
					ledConfig.numberOfLEDs = 8;
					StringProcessor stringProcessor;
					LpiExecutorFactory lpiExecutorFactory;
					JsonInstructionBuilderFactory factory(&lpiExecutorFactory, &stringProcessor, &ledConfig);
					LpJsonStateBuilder stateBuilder(&factory);
					LpJsonState state;
					FixedSizeCharBuffer lp(1000);

					// act
					bool stateBuilt = stateBuilder.BuildState(&lp, &state);

					// assert
					Assert::IsTrue(stateBuilt);
				}

				TEST_METHOD(WhenOneInstruction_TreeBuiltAndValid)
				{
					// arrange
					LEDConfig ledConfig;
					ledConfig.numberOfLEDs = 8;
					StringProcessor stringProcessor;
					LpiExecutorFactory lpiExecutorFactory;
					JsonInstructionBuilderFactory factory(&lpiExecutorFactory, &stringProcessor, &ledConfig);
					LpJsonStateBuilder stateBuilder(&factory);
					LpJsonState_TestHelper state;
					FixedSizeCharBuffer lp(1000);
lp.LoadFromBuffer(
"{\
	\"name\" : \"testing\",\
	\"instructions\" : [\
		\"01010000FF0000\"\
	]\
}"
);

					// act
					stateBuilder.BuildState(&lp, &state);

					// assert
					char* verificationStatements[1] = {
						"In01010000FF0000"
					};
					char* failedVerificationStatement = state.VerifyState(verificationStatements, 1);
					Assert::IsNull(failedVerificationStatement);
				}

				TEST_METHOD(WhenTwoInstructions_TreeBuiltAndValid)
				{
					// arrange
					LEDConfig ledConfig;
					ledConfig.numberOfLEDs = 8;
					StringProcessor stringProcessor;
					LpiExecutorFactory lpiExecutorFactory;
					JsonInstructionBuilderFactory factory(&lpiExecutorFactory, &stringProcessor, &ledConfig);
					LpJsonStateBuilder stateBuilder(&factory);
					LpJsonState_TestHelper state;
					FixedSizeCharBuffer lp(1000);
					lp.LoadFromBuffer(
"{\
	\"name\" : \"testing\",\
	\"instructions\" : [\
		\"01010000FF0000\",\
		\"0101000000FF00\"\
	]\
}");

					// act
					stateBuilder.BuildState(&lp, &state);

					// assert
					char* verificationStatements[2] = {
						"IN01010000FF0000",
						"In0101000000FF00"
					};
					char* failedVerificationStatement = state.VerifyState(verificationStatements, 2);
					Assert::IsNull(failedVerificationStatement);
				}

				TEST_METHOD(WhenOneLpInsInRepeat_TreeBuiltAndValid)
				{
					// arrange
					LEDConfig ledConfig;
					ledConfig.numberOfLEDs = 8;
					StringProcessor stringProcessor;
					LpiExecutorFactory lpiExecutorFactory;
					JsonInstructionBuilderFactory factory(&lpiExecutorFactory, &stringProcessor, &ledConfig);
					LpJsonStateBuilder stateBuilder(&factory);
					LpJsonState_TestHelper state;
					FixedSizeCharBuffer lp(1000);
					lp.LoadFromBuffer(
"{\
	\"name\" : \"testing\",\
	\"instructions\" : [\
		{\
			\"repeat\" : {\
				\"times\" : 50,\
				\"instructions\" : [\
					\"01010000FFFFFF\"\
				]\
			}\
		}\
	]\
}");

					// act
					stateBuilder.BuildState(&lp, &state);

					// assert
					const int numVerificationStatements = 3;
					char* verificationStatements[numVerificationStatements] = {
						"RC50",				
						"IP01010000FFFFFF",	
						"Rn50"				
					};
					char* failedVerificationStatement = state.VerifyState(verificationStatements, numVerificationStatements);
					Assert::IsNull(failedVerificationStatement);
				}

				TEST_METHOD(WhenRepeatTwoInsRepeatOneIns_TreeBuiltAndValid)
				{
					// arrange
					LEDConfig ledConfig;
					ledConfig.numberOfLEDs = 8;
					StringProcessor stringProcessor;
					LpiExecutorFactory lpiExecutorFactory;
					JsonInstructionBuilderFactory factory(&lpiExecutorFactory, &stringProcessor, &ledConfig);
					LpJsonStateBuilder stateBuilder(&factory);
					LpJsonState_TestHelper state;
					FixedSizeCharBuffer lp(1000);
					lp.LoadFromBuffer(
"{\
	\"name\" : \"testing\",\
	\"instructions\" : [\
		{\
			\"repeat\" : {\
				\"times\" : 50,\
				\"instructions\" : [\
					\"01010000FFFFFF\",\
					\"01010000FFFF00\",\
					{\
						\"repeat\": {\
							\"times\":100,\
							\"instructions\": [\
								\"01010000FF0000\"\
							]\
						}\
					}\
				]\
			}\
		}\
	]\
}");

					// act
					stateBuilder.BuildState(&lp, &state);

					// assert
					const int numVerificationStatements = 7;
					char* verificationStatements[numVerificationStatements] = {
						"RC50",
						"IN01010000FFFFFF",
						"IN01010000FFFF00",
						"RC100",
						"IP01010000FF0000",
						"RP100",
						"Rn50",
					};
					char* failedVerificationStatement = state.VerifyState(verificationStatements, numVerificationStatements);
					Assert::IsNull(failedVerificationStatement);
				}

				TEST_METHOD(WhenRepeatTwoInsThenAnotherRepeatTwoIns_TreeBuiltAndValid)
				{
					// arrange
					LEDConfig ledConfig;
					ledConfig.numberOfLEDs = 8;
					StringProcessor stringProcessor;
					LpiExecutorFactory lpiExecutorFactory;
					JsonInstructionBuilderFactory factory(&lpiExecutorFactory, &stringProcessor, &ledConfig);
					LpJsonStateBuilder stateBuilder(&factory);
					LpJsonState_TestHelper state;
					FixedSizeCharBuffer lp(1000);
					lp.LoadFromBuffer(
"{\
	\"name\" : \"testing\",\
	\"instructions\" : [\
		{\
			\"repeat\" : {\
				\"times\" : 50,\
				\"instructions\" : [\
					\"01010000FFFFFF\",\
					\"01010000FFFF00\"\
				]\
			}\
		},\
		{\
			\"repeat\" : {\
				\"times\" : 100,\
				\"instructions\" : [\
					\"01010000FF0000\",\
					\"01010000000000\"\
				]\
			}\
		}\
	]\
}");

					// act
					stateBuilder.BuildState(&lp, &state);

					// assert
					const int numVerificationStatements = 8;
					char* verificationStatements[numVerificationStatements] = {
						"RC50",
						"IN01010000FFFFFF",
						"IP01010000FFFF00",
						"RN50",
						"RC100",
						"IN01010000FF0000",
						"IP01010000000000",
						"Rn100",
					};
					char* failedVerificationStatement = state.VerifyState(verificationStatements, numVerificationStatements);
					Assert::AreEqual<char*>(nullptr, failedVerificationStatement);
				}

				TEST_METHOD(WhenRepeatTwoInsThenInsThenRepeatTwoIns_TreeBuiltAndValid)
				{
					// arrange
					LEDConfig ledConfig;
					ledConfig.numberOfLEDs = 8;
					StringProcessor stringProcessor;
					LpiExecutorFactory lpiExecutorFactory;
					JsonInstructionBuilderFactory factory(&lpiExecutorFactory, &stringProcessor, &ledConfig);
					LpJsonStateBuilder stateBuilder(&factory);
					LpJsonState_TestHelper state;
					FixedSizeCharBuffer lp(1000);
					lp.LoadFromBuffer(
"{\
	\"name\" : \"testing\",\
	\"instructions\" : [\
		{\
			\"repeat\" : {\
				\"times\" : 50,\
				\"instructions\" : [\
					\"01010000FFFFFF\",\
					\"01010000FFFF00\"\
				]\
			}\
		},\
		\"01010000AAAAAA\",\
		{\
			\"repeat\" : {\
				\"times\" : 100,\
				\"instructions\" : [\
					\"01010000FF0000\",\
					\"01010000000000\"\
				]\
			}\
		}\
	]\
}");

					// act
					stateBuilder.BuildState(&lp, &state);

					// assert
					const int numVerificationStatements = 9;
					char* verificationStatements[numVerificationStatements] = {
						"RC50",
						"IN01010000FFFFFF",
						"IP01010000FFFF00",
						"RN50",
						"IN01010000AAAAAA",
						"RC100",
						"IN01010000FF0000",
						"IP01010000000000",
						"Rn100",
					};
					char* failedVerificationStatement = state.VerifyState(verificationStatements, numVerificationStatements);
					Assert::AreEqual<char*>(nullptr, failedVerificationStatement);
				}

				/*
					repeat
						ins
					ins
					repeat
						ins
						repeat
							repeat
								ins
				*/
				TEST_METHOD(WhenComplexProgramWithManyRepeats_TreeBuiltAndValid)
				{
					// arrange
					LEDConfig ledConfig;
					ledConfig.numberOfLEDs = 8;
					StringProcessor stringProcessor;
					LpiExecutorFactory lpiExecutorFactory;
					JsonInstructionBuilderFactory factory(&lpiExecutorFactory, &stringProcessor, &ledConfig);
					LpJsonStateBuilder stateBuilder(&factory);
					LpJsonState_TestHelper state;
					FixedSizeCharBuffer lp(1000);
					lp.LoadFromBuffer(
"{\
	\"name\" : \"testing\",\
	\"instructions\" : [\
		{\
			\"repeat\" : {\
				\"times\" : 50,\
				\"instructions\" : [\
					\"01010000FFFFFF\"\
				]\
			}\
		},\
		\"01010000FF0000\",\
		{\
			\"repeat\" : {\
				\"times\" : 100,\
				\"instructions\" : [\
					\"01010000000000\",\
					{\
						\"repeat\" : {\
							\"times\" : 150,\
							\"instructions\" : [\
								{\
									\"repeat\" : {\
										\"times\" : 200,\
										\"instructions\" : [\
											\"010100000000FF\"\
										]\
									}\
								}\
							]\
						}\
					}\
				]\
			}\
		}\
	]\
}");

					// act
					stateBuilder.BuildState(&lp, &state);

					// assert
					const int numVerificationStatements = 12;
					char* verificationStatements[numVerificationStatements] = {
						"RC50",
						"IP01010000FFFFFF",
						"RN50",
						"IN01010000FF0000",
						"RC100",
						"IN01010000000000",
						"RC150",
						"RC200",
						"IP010100000000FF",
						"RP200",
						"RP150",
						"Rn100",
					};
					char* failedVerificationStatement = state.VerifyState(verificationStatements, numVerificationStatements);
					Assert::AreEqual<char*>(nullptr, failedVerificationStatement);
				}

				/*
					repeat
						ins
						ins
					ins
					repeat
						ins
						ins
					ins
					repeat
						ins
						ins
				*/
				TEST_METHOD(WhenComplexProgramWithSubsequentRepeats_TreeBuiltAndValid)
				{
					// arrange
					LEDConfig ledConfig;
					ledConfig.numberOfLEDs = 8;
					StringProcessor stringProcessor;
					LpiExecutorFactory lpiExecutorFactory;
					JsonInstructionBuilderFactory factory(&lpiExecutorFactory, &stringProcessor, &ledConfig);
					LpJsonStateBuilder stateBuilder(&factory);
					LpJsonState_TestHelper state;
					FixedSizeCharBuffer lp(1000);
					lp.LoadFromBuffer(
"{\
	\"name\" : \"testing\",\
	\"instructions\" : [\
		{\
			\"repeat\" : {\
				\"times\" : 50,\
				\"instructions\" : [\
					\"01010000FFFFFF\",\
					\"01010000FFFF00\"\
				]\
			}\
		},\
		\"01010000FF0000\",\
		{\
			\"repeat\" : {\
				\"times\" : 100,\
				\"instructions\" : [\
					\"01010000AAAAAA\",\
					\"01010000AAAA00\"\
				]\
			}\
		},\
		\"01010000BB0000\",\
		{\
			\"repeat\" : {\
				\"times\" : 150,\
				\"instructions\" : [\
					\"01010000BBBBBB\",\
					\"01010000BBBB00\"\
				]\
			}\
		}\
	]\
}");

					// act
					stateBuilder.BuildState(&lp, &state);

					// assert
					const int numVerificationStatements = 14;
					char* verificationStatements[numVerificationStatements] = {
						"RC50",
						"IN01010000FFFFFF",
						"IP01010000FFFF00",
						"RN50",
						"IN01010000FF0000",
						"RC100",
						"IN01010000AAAAAA",
						"IP01010000AAAA00",
						"RN100",
						"IN01010000BB0000",
						"RC150",
						"IN01010000BBBBBB",
						"IP01010000BBBB00",
						"Rn150",
					};
					char* failedVerificationStatement = state.VerifyState(verificationStatements, numVerificationStatements);
					Assert::AreEqual<char*>(nullptr, failedVerificationStatement);
				}

				TEST_METHOD(WhenOneFadeInstruction_TreeBuiltAndValid)
				{
					// arrange
					LEDConfig ledConfig;
					ledConfig.numberOfLEDs = 8;
					StringProcessor stringProcessor;
					LpiExecutorFactory lpiExecutorFactory;
					JsonInstructionBuilderFactory factory(&lpiExecutorFactory, &stringProcessor, &ledConfig);
					LpJsonStateBuilder stateBuilder(&factory);
					LpJsonState_TestHelper state;
					FixedSizeCharBuffer lp(1000);
					lp.LoadFromBuffer(
"{\
	\"name\" : \"testing\",\
	\"instructions\" : [\
		\"040100000A1FFFFFF000000\"\
	]\
}"
);

					// act
					stateBuilder.BuildState(&lp, &state);

					// assert
					char* verificationStatements[1] = {
						"In040100000A1FFFFFF000000"
					};
					char* failedVerificationStatement = state.VerifyState(verificationStatements, 1);
					Assert::IsNull(failedVerificationStatement);
				}
			};
		}
	}
}