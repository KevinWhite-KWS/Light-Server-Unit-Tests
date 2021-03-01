#include "CppUnitTest.h"

#include "../../../Light-Server/src/Orchastrator/Timer.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace LS {
	namespace Orchastrator {
		namespace Ti {
			class TestTimer : public Timer {
			protected:
				uint32_t GetCurrent() {
					return currentTime;
				}

			public:
				TestTimer(uint8_t interval, uint32_t initialCurrentTime = 0) 
					: Timer{ interval } {
					currentTime = initialCurrentTime;
					nextTime = GetCurrent() + this->interval;
				}

				uint32_t currentTime = 0;
			};


			TEST_CLASS(IsTime) {
			public:
				TEST_METHOD(WhenInterval50Start0_TrueReturned)
				{
					// arrange
					TestTimer timer = TestTimer(50);

					// act
					bool isTime = timer.IsTime();

					// assert
					Assert::IsTrue(isTime);
				}

				TEST_METHOD(WhenInterval50Start1000_FalseReturned)
				{
					// arrange
					TestTimer timer = TestTimer(50, 1000);

					// act
					bool isTime = timer.IsTime();

					// assert
					Assert::IsFalse(isTime);
				}

				TEST_METHOD(WhenInterval50Start1000AdvanceTo1025_FalseReturned)
				{
					// arrange
					TestTimer timer = TestTimer(50, 1000);
					timer.currentTime = 1025;

					// act
					bool isTime = timer.IsTime();

					// assert
					Assert::IsFalse(isTime);
				}

				TEST_METHOD(WhenInterval50Start1000AdvanceTo1050_TrueReturned)
				{
					// arrange
					TestTimer timer = TestTimer(50, 1000);
					timer.currentTime = 1050;

					// act
					bool isTime = timer.IsTime();

					// assert
					Assert::IsTrue(isTime);
				}

				// overshoot next time of 1050 by 20 ms, should still return a postive value
				TEST_METHOD(WhenInterval50Start1000AdvanceTo1070_TrueReturned)
				{
					// arrange
					TestTimer timer = TestTimer(50, 1000);
					timer.currentTime = 1070;

					// act
					bool isTime = timer.IsTime();

					// assert
					Assert::IsTrue(isTime);
				}

				TEST_METHOD(WhenInterval50Start1000AdvanceTo1070ThenAdvanceTo1100_FalseReturned)
				{
					// arrange
					TestTimer timer = TestTimer(50, 1000);
					timer.currentTime = 1070;

					// act
					bool isTime = timer.IsTime();
					timer.currentTime = 1100;
					isTime = timer.IsTime();

					// assert
					Assert::IsFalse(isTime);
				}

				TEST_METHOD(WhenInterval50Start1000AdvanceTo1070ThenAdvanceTo1119_FalseReturned)
				{
					// arrange
					TestTimer timer = TestTimer(50, 1000);
					timer.currentTime = 1070;

					// act
					bool isTime = timer.IsTime();
					timer.currentTime = 1119;
					isTime = timer.IsTime();

					// assert
					Assert::IsFalse(isTime);
				}

				TEST_METHOD(WhenInterval50Start1000AdvanceTo1070ThenAdvanceTo1120_FalseReturned)
				{
					// arrange
					TestTimer timer = TestTimer(50, 1000);
					timer.currentTime = 1070;

					// act
					bool isTime = timer.IsTime();
					timer.currentTime = 1120;
					isTime = timer.IsTime();

					// assert
					Assert::IsTrue(isTime);
				}

				TEST_METHOD(WhenInterval50Start1000IsTimeThreeTimes_TrueReturned)
				{
					// arrange
					TestTimer timer = TestTimer(50, 1000);
					timer.currentTime = 1000;

					// act
					bool isTime = timer.IsTime();
					timer.currentTime = 1050;
					isTime = timer.IsTime();
					timer.currentTime = 1100;
					isTime = timer.IsTime();

					// assert
					Assert::IsTrue(isTime);
				}
			};
		}
	}
}