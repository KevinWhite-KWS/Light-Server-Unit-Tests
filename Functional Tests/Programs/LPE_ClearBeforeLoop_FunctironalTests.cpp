#include "LPE_ClearBeforeLoop_FunctionalTests.h"

namespace LS {
	namespace LightProgramExecutor_ClearBeforeLoop_FunctionalTest {
		void GetNextRI::Con() {
		}

		void GetNextRI::Clean() {
			lpeUnitTestHelper.CleanUp();
		}

		void GetNextRI::a_GetFrame1_ClearExpected() {
			// arrange
			
			// act
			bool result;
			for (int i = 0; i < 1; i++) result = lpe->GetNextRI(lpeUnitTestHelper.riBuffer);
			
			// assert
			int areEqual = strcmp("00000001R", lpeUnitTestHelper.riBuffer->GetBuffer());
			// lpeUnitTestHelper.CleanUp();
			Assert::AreEqual<bool>(true, result);
			Assert::AreEqual<int>(0, areEqual);
		}

		void GetNextRI::b_GetFrame2_RedSolidExpected()
		{
			// arrange
		
			// act
			bool result;
				// advance to frame 2 (solid red)
			for (int i = 0; i < 1; i++) result = lpe->GetNextRI(lpeUnitTestHelper.riBuffer);
		
			// assert
			int areEqual = strcmp("FF000001R", lpeUnitTestHelper.riBuffer->GetBuffer());
			Assert::AreEqual<bool>(true, result);
			Assert::AreEqual<int>(0, areEqual);
		}

		void GetNextRI::c_GetFrame12_GreenSolidExpected()
		{
			// arrange

			// act
			bool result;
			// advance to frame 12 (solid red)
			for (int i = 0; i < 10; i++) result = lpe->GetNextRI(lpeUnitTestHelper.riBuffer);

			// assert
			int areEqual = strcmp("00FF0001R", lpeUnitTestHelper.riBuffer->GetBuffer());
			Assert::AreEqual<bool>(true, result);
			Assert::AreEqual<int>(0, areEqual);
		}

		void GetNextRI::d_GetFrame22_BlueSolidExpected()
		{
			// arrange

			// act
			bool result;
			// advance to frame 12 (solid red)
			for (int i = 0; i < 10; i++) result = lpe->GetNextRI(lpeUnitTestHelper.riBuffer);

			// assert
			int areEqual = strcmp("0000FF01R", lpeUnitTestHelper.riBuffer->GetBuffer());
			Assert::AreEqual<bool>(true, result);
			Assert::AreEqual<int>(0, areEqual);
		}

		void GetNextRI::e_GetFrame32_RedSolidExpected()
		{
			// arrange

			// act
			bool result;
			// advance to frame 12 (solid red)
			for (int i = 0; i < 10; i++) result = lpe->GetNextRI(lpeUnitTestHelper.riBuffer);

			// assert
			int areEqual = strcmp("FF000001R", lpeUnitTestHelper.riBuffer->GetBuffer());
			Assert::AreEqual<bool>(true, result);
			Assert::AreEqual<int>(0, areEqual);
		}

		void GetNextRI::f_GetFrame42_GreenSolidExpected()
		{
			// arrange

			// act
			bool result;
			// advance to frame 12 (solid red)
			for (int i = 0; i < 10; i++) result = lpe->GetNextRI(lpeUnitTestHelper.riBuffer);

			// assert
			int areEqual = strcmp("00FF0001R", lpeUnitTestHelper.riBuffer->GetBuffer());
			Assert::AreEqual<bool>(true, result);
			Assert::AreEqual<int>(0, areEqual);
		}

		void GetNextRI::f_GetFrame52_BlueSolidExpected()
		{
			// arrange

			// act
			bool result;
			// advance to frame 12 (solid red)
			for (int i = 0; i < 10; i++) result = lpe->GetNextRI(lpeUnitTestHelper.riBuffer);

			// assert
			int areEqual = strcmp("0000FF01R", lpeUnitTestHelper.riBuffer->GetBuffer());
			Assert::AreEqual<bool>(true, result);
			Assert::AreEqual<int>(0, areEqual);
		}

		void GetNextRI::g_GetFrame1_ClearExpected() {
			// arrange
			FixedSizeCharBuffer* lpBuffer = lpeUnitTestHelper.lpBuffer;
			lpBuffer->LoadFromBuffer(ldlProgram);
			LPValidateResult validateResult = LPValidateResult();
			lpe->ValidateLP(lpeUnitTestHelper.lpBuffer, &validateResult);

			// act
			bool result;
			for (int i = 0; i < 1; i++) result = lpe->GetNextRI(lpeUnitTestHelper.riBuffer);

			// assert
			int areEqual = strcmp("00000001R", lpeUnitTestHelper.riBuffer->GetBuffer());
			Assert::AreEqual<bool>(true, result);
			Assert::AreEqual<int>(0, areEqual);
		}

		void GetNextRI::h_GetFrame2_RedSolidExpected()
		{
			// arrange

			// act
			bool result;
			// advance to frame 2 (solid red)
			for (int i = 0; i < 1; i++) result = lpe->GetNextRI(lpeUnitTestHelper.riBuffer);

			// assert
			int areEqual = strcmp("FF000001R", lpeUnitTestHelper.riBuffer->GetBuffer());
			Assert::AreEqual<bool>(true, result);
			Assert::AreEqual<int>(0, areEqual);
		}

		void GetNextRI::i_GetFrame12_GreenSolidExpected()
		{
			// arrange

			// act
			bool result;
			// advance to frame 12 (solid red)
			for (int i = 0; i < 10; i++) result = lpe->GetNextRI(lpeUnitTestHelper.riBuffer);

			// assert
			int areEqual = strcmp("00FF0001R", lpeUnitTestHelper.riBuffer->GetBuffer());
			Assert::AreEqual<bool>(true, result);
			Assert::AreEqual<int>(0, areEqual);
		}

		void GetNextRI::j_GetFrame22_BlueSolidExpected()
		{
			// arrange

			// act
			bool result;
			// advance to frame 12 (solid red)
			for (int i = 0; i < 10; i++) result = lpe->GetNextRI(lpeUnitTestHelper.riBuffer);

			// assert
			int areEqual = strcmp("0000FF01R", lpeUnitTestHelper.riBuffer->GetBuffer());
			Assert::AreEqual<bool>(true, result);
			Assert::AreEqual<int>(0, areEqual);
		}

		void GetNextRI::k_GetFrame32_RedSolidExpected()
		{
			// arrange

			// act
			bool result;
			// advance to frame 12 (solid red)
			for (int i = 0; i < 10; i++) result = lpe->GetNextRI(lpeUnitTestHelper.riBuffer);

			// assert
			int areEqual = strcmp("FF000001R", lpeUnitTestHelper.riBuffer->GetBuffer());
			Assert::AreEqual<bool>(true, result);
			Assert::AreEqual<int>(0, areEqual);
		}

		void GetNextRI::l_GetFrame42_GreenSolidExpected()
		{
			// arrange

			// act
			bool result;
			// advance to frame 12 (solid red)
			for (int i = 0; i < 10; i++) result = lpe->GetNextRI(lpeUnitTestHelper.riBuffer);

			// assert
			int areEqual = strcmp("00FF0001R", lpeUnitTestHelper.riBuffer->GetBuffer());
			Assert::AreEqual<bool>(true, result);
			Assert::AreEqual<int>(0, areEqual);
		}

		void GetNextRI::m_GetFrame52_BlueSolidExpected()
		{
			// arrange

			// act
			bool result;
			// advance to frame 12 (solid red)
			for (int i = 0; i < 10; i++) result = lpe->GetNextRI(lpeUnitTestHelper.riBuffer);

			// assert
			int areEqual = strcmp("0000FF01R", lpeUnitTestHelper.riBuffer->GetBuffer());
			Assert::AreEqual<bool>(true, result);
			Assert::AreEqual<int>(0, areEqual);
		}
	}
}


//#include "CppUnitTest.h"
//#include "..\..\..\Light-Server\src\LPE.h"
//#include "..\..\mocks\Mock_LPE.h"
//#include "..\..\Helpers\LPE_UnitTestHelper.h"
//
//using namespace Microsoft::VisualStudio::CppUnitTestFramework;
//
//namespace LS
//{
//	/*
//	These tests attempt to verify that a clear instruction (or any instruction)
//	before a finite loop executes the instruction in the sequence as expected.
//	These new tests are in response to a detected bug whereby a clear instruction
//	before a finite loop causes a crash if it is executed three times.  As we are
//	retaining a reference to the LPE, this is more like a functional test.
//	*/
//	namespace LightProgramExecutor_ClearBeforeLoop_FunctionalTest {
//		TEST_CLASS(GetNextRI) {
//
//
//
//		protected:
//
//
//
//		public:
//			static const char* ldlProgram;
//			static LPE_UnitTestHelper lpeUnitTestHelper;
//			//static LPE* lpe;
//
//			TEST_CLASS_INITIALIZE(Con)
//			{
//				// test class initialization  code
//				ldlProgram = "{\"name\":\"Demoloopcrashwheninstructionbeforeloop\",\"instructions\":{\"instruction\":\"00010000\",\"repeat\":{\"times\":2,\"instructions\":{\"instruction\":\"010A0000FF0000\",\"instruction\":\"010A000000FF00\",\"instruction\":\"010A00000000FF\"}}}}";
//				//lpeUnitTestHelper = LPE_UnitTestHelper();
//				//lpe = lpeUnitTestHelper.InstantiateLPEWithProgram(ldlProgram);
//			}
//
//			TEST_CLASS_CLEANUP(Clean)
//			{
//				// test class cleanup  code
//				lpeUnitTestHelper.CleanUp();
//			}
//
//			/*
//			TEST_METHOD(GetFrame1_ClearExpected)
//			{
//				// arrange
//
//				// act
//				bool result;
//				for (int i = 0; i < 1; i++) result = lpe->GetNextRI(lpeUnitTestHelper.riBuffer);
//
//				// assert
//				int areEqual = strcmp("00000001R", lpeUnitTestHelper.riBuffer->GetBuffer());
//				// lpeUnitTestHelper.CleanUp();
//				Assert::AreEqual<bool>(true, result);
//				Assert::AreEqual<int>(0, areEqual);
//			}
//
//			TEST_METHOD(GetFrame2_RedSolidExpected)
//			{
//				// arrange
//
//				// act
//				bool result;
//					// advance to frame 2 (solid red)
//				for (int i = 0; i < 1; i++) result = lpe->GetNextRI(lpeUnitTestHelper.riBuffer);
//
//				// assert
//				int areEqual = strcmp("FF000001R", lpeUnitTestHelper.riBuffer->GetBuffer());
//				lpeUnitTestHelper.CleanUp();
//				Assert::AreEqual<bool>(true, result);
//				Assert::AreEqual<int>(0, areEqual);
//			}
//			*/
//		};
//	}
//}