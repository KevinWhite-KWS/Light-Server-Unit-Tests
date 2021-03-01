//#include "CppUnitTest.h"
//#include "..\..\..\Light-Server\src\LPE.h"
//#include "..\..\mocks\Mock_LPE.h"
//#include "..\..\Helpers\LPE_UnitTestHelper.h"
//
//using namespace Microsoft::VisualStudio::CppUnitTestFramework;
//
//namespace LS {
//	namespace LightProgramExecutor_ClearBeforeLoop_FunctionalTest {
//		TEST_CLASS(GetNextRI) {
//			protected:
//			public:
//				static char* ldlProgram;
//				static LPE_UnitTestHelper lpeUnitTestHelper;
//				static LPE* lpe;
//
//				TEST_CLASS_INITIALIZE(Con);
//				TEST_CLASS_CLEANUP(Clean);
//
//				TEST_METHOD(a_GetFrame1_ClearExpected);
//				TEST_METHOD(b_GetFrame2_RedSolidExpected);
//				TEST_METHOD(c_GetFrame12_GreenSolidExpected);
//				TEST_METHOD(d_GetFrame22_BlueSolidExpected);
//				TEST_METHOD(e_GetFrame32_RedSolidExpected);
//				TEST_METHOD(f_GetFrame42_GreenSolidExpected);
//				TEST_METHOD(f_GetFrame52_BlueSolidExpected);
//				TEST_METHOD(g_GetFrame1_ClearExpected);
//				TEST_METHOD(h_GetFrame2_RedSolidExpected);
//				TEST_METHOD(i_GetFrame12_GreenSolidExpected);
//				TEST_METHOD(j_GetFrame22_BlueSolidExpected);
//				TEST_METHOD(k_GetFrame32_RedSolidExpected);
//				TEST_METHOD(l_GetFrame42_GreenSolidExpected);
//				TEST_METHOD(m_GetFrame52_BlueSolidExpected);
//		};
//
//		char* GetNextRI::ldlProgram{ "{\"name\":\"Demoloopcrashwheninstructionbeforeloop\",\"instructions\":{\"instruction\":\"00010000\",\"repeat\":{\"times\":2,\"instructions\":{\"instruction\":\"010A0000FF0000\",\"instruction\":\"010A000000FF00\",\"instruction\":\"010A00000000FF\"}}}}" };
//		LPE_UnitTestHelper GetNextRI::lpeUnitTestHelper{ LPE_UnitTestHelper() };
//		LPE* GetNextRI::lpe { lpeUnitTestHelper.InstantiateLPEWithProgram(ldlProgram) };
//	}
//}