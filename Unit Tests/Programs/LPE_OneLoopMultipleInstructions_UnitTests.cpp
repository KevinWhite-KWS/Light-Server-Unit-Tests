#include "CppUnitTest.h"
#include "..\..\..\Light-Server\src\LPE.h"
#include "..\..\mocks\Mock_LPE.h"
#include "..\..\Helpers\LPE_UnitTestHelper.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace LS
{
	namespace LightProgramExecutor_OneLookMultipleInstructions {
		TEST_CLASS(GetNextRI) {
			protected:
				const char* ldlProgram = "{\"name\":\"Demoskiptolastinsinfirstloop\",\"instructions\":{\"repeat\":{\"times\":2,\"instructions\":{\"instruction\":\"010A0000FF0000\",\"instruction\":\"010A000000FF00\",\"instruction\":\"010A00000000FF\"}}}}";

			public:
				TEST_METHOD(GetFrame1_SolidRedExpected)
				{
					// arrange
					LPE_UnitTestHelper lpeUnitTestHelper = LPE_UnitTestHelper();
					LPE* lpe = lpeUnitTestHelper.InstantiateLPEWithProgram(ldlProgram);

					// act
					bool result;
					for (int i = 0; i < 1; i++) result = lpe->GetNextRI(lpeUnitTestHelper.riBuffer);

					// assert
					int areEqual = strcmp("FF000001R", lpeUnitTestHelper.riBuffer->GetBuffer());
					lpeUnitTestHelper.CleanUp();
					Assert::AreEqual<bool>(true, result);
					Assert::AreEqual<int>(0, areEqual);
				}

				TEST_METHOD(GetFrame2_SolidGreenExpected)
				{
					// arrange
					LPE_UnitTestHelper lpeUnitTestHelper = LPE_UnitTestHelper();
					LPE* lpe = lpeUnitTestHelper.InstantiateLPEWithProgram(ldlProgram);

					// act
					bool result;
					for (int i = 0; i < 11; i++) result = lpe->GetNextRI(lpeUnitTestHelper.riBuffer);

					// assert
					int areEqual = strcmp("00FF0001R", lpeUnitTestHelper.riBuffer->GetBuffer());
					lpeUnitTestHelper.CleanUp();
					Assert::AreEqual<bool>(true, result);
					Assert::AreEqual<int>(0, areEqual);
				}

				TEST_METHOD(GetFrame3_SolidBlueExpected)
				{
					// arrange
					LPE_UnitTestHelper lpeUnitTestHelper = LPE_UnitTestHelper();
					LPE* lpe = lpeUnitTestHelper.InstantiateLPEWithProgram(ldlProgram);

					// act
					bool result;
					for (int i = 0; i < 21; i++) result = lpe->GetNextRI(lpeUnitTestHelper.riBuffer);

					// assert
					int areEqual = strcmp("0000FF01R", lpeUnitTestHelper.riBuffer->GetBuffer());
					lpeUnitTestHelper.CleanUp();
					Assert::AreEqual<bool>(true, result);
					Assert::AreEqual<int>(0, areEqual);
				}

				TEST_METHOD(GetFrame4_SolidRedExpected)
				{
					// arrange
					LPE_UnitTestHelper lpeUnitTestHelper = LPE_UnitTestHelper();
					LPE* lpe = lpeUnitTestHelper.InstantiateLPEWithProgram(ldlProgram);

					// act
					bool result;
					for (int i = 0; i < 31; i++) result = lpe->GetNextRI(lpeUnitTestHelper.riBuffer);

					// assert
					int areEqual = strcmp("FF000001R", lpeUnitTestHelper.riBuffer->GetBuffer());
					lpeUnitTestHelper.CleanUp();
					Assert::AreEqual<bool>(true, result);
					Assert::AreEqual<int>(0, areEqual);
				}

				TEST_METHOD(GetFrame5_SolidGreenExpected)
				{
					// arrange
					LPE_UnitTestHelper lpeUnitTestHelper = LPE_UnitTestHelper();
					LPE* lpe = lpeUnitTestHelper.InstantiateLPEWithProgram(ldlProgram);

					// act
					bool result;
					for (int i = 0; i < 41; i++) result = lpe->GetNextRI(lpeUnitTestHelper.riBuffer);

					// assert
					int areEqual = strcmp("00FF0001R", lpeUnitTestHelper.riBuffer->GetBuffer());
					lpeUnitTestHelper.CleanUp();
					Assert::AreEqual<bool>(true, result);
					Assert::AreEqual<int>(0, areEqual);
				}

				TEST_METHOD(GetFrame6_SolidBlueExpected)
				{
					// arrange
					LPE_UnitTestHelper lpeUnitTestHelper = LPE_UnitTestHelper();
					LPE* lpe = lpeUnitTestHelper.InstantiateLPEWithProgram(ldlProgram);

					// act
					bool result;
					for (int i = 0; i < 51; i++) result = lpe->GetNextRI(lpeUnitTestHelper.riBuffer);

					// assert
					int areEqual = strcmp("0000FF01R", lpeUnitTestHelper.riBuffer->GetBuffer());
					lpeUnitTestHelper.CleanUp();
					Assert::AreEqual<bool>(true, result);
					Assert::AreEqual<int>(0, areEqual);
				}
		};
	}
}