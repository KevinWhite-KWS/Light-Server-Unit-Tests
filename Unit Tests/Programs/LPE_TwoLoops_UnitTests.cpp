#include "CppUnitTest.h"
#include "..\..\..\Light-Server\src\LPE.h"
#include "..\..\mocks\Mock_LPE.h"
#include "..\..\Helpers\LPE_UnitTestHelper.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace LS
{
	namespace LightProgramExecutor_TwoLoops {
		TEST_CLASS(GetNextRI) {
			protected:
				const char* ldlProgram = "{\"name\" : \"Demo loop then loop issue\",\"instructions\": {\"repeat\": {\"times\" : 2,\"instructions\": {\"instruction\" : \"01010000FF0000\"}},\"repeat\": {\"times\" : 2,\"instructions\": {\"instruction\" : \"0101000000FF00\"}}}}";

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

				TEST_METHOD(GetFrame2_SolidRedExpected)
				{
					// arrange
					LPE_UnitTestHelper lpeUnitTestHelper = LPE_UnitTestHelper();
					LPE* lpe = lpeUnitTestHelper.InstantiateLPEWithProgram(ldlProgram);

					// act
					bool result;
					for (int i = 0; i < 2; i++) result = lpe->GetNextRI(lpeUnitTestHelper.riBuffer);

					// assert
					int areEqual = strcmp("FF000001R", lpeUnitTestHelper.riBuffer->GetBuffer());
					lpeUnitTestHelper.CleanUp();
					Assert::AreEqual<bool>(true, result);
					Assert::AreEqual<int>(0, areEqual);
				}

				TEST_METHOD(GetFrame3_SolidGreenExpected)
				{
					// arrange
					LPE_UnitTestHelper lpeUnitTestHelper = LPE_UnitTestHelper();
					LPE* lpe = lpeUnitTestHelper.InstantiateLPEWithProgram(ldlProgram);

					// act
					bool result;
					for (int i = 0; i < 3; i++) result = lpe->GetNextRI(lpeUnitTestHelper.riBuffer);

					// assert
					int areEqual = strcmp("00FF0001R", lpeUnitTestHelper.riBuffer->GetBuffer());
					lpeUnitTestHelper.CleanUp();
					Assert::AreEqual<bool>(true, result);
					Assert::AreEqual<int>(0, areEqual);
				}

				TEST_METHOD(GetFrame4_SolidGreenExpected)
				{
					// arrange
					LPE_UnitTestHelper lpeUnitTestHelper = LPE_UnitTestHelper();
					LPE* lpe = lpeUnitTestHelper.InstantiateLPEWithProgram(ldlProgram);

					// act
					bool result;
					for (int i = 0; i < 4; i++) result = lpe->GetNextRI(lpeUnitTestHelper.riBuffer);

					// assert
					int areEqual = strcmp("00FF0001R", lpeUnitTestHelper.riBuffer->GetBuffer());
					lpeUnitTestHelper.CleanUp();
					Assert::AreEqual<bool>(true, result);
					Assert::AreEqual<int>(0, areEqual);
				}
		};
	}
}