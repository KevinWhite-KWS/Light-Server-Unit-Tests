#include "CppUnitTest.h"
#include "../../../../Light-Server/src/LPE/LpiExecutors/LpiExecutorFactory.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace LS {
	namespace LPE {
		namespace LpiExecutors {
			TEST_CLASS(LpiExecutorFactory_GetLpiExecutor)
			{
			public:
				TEST_METHOD(WhenInvalidOpCode_NullPtrReturned)
				{
					// arrange
					LpiExecutorFactory lpiExecutorFactory;

					// act
					LpiExecutor* lpiExecutor = lpiExecutorFactory.GetLpiExecutor(255);

					// assert
					Assert::IsNull(lpiExecutor);
				}

				TEST_METHOD(WhenOpIsClear_ClearLpiExecutorReturned)
				{
					// arrange
					LpiExecutorFactory lpiExecutorFactory;

					// act
					LpiExecutor* lpiExecutor = lpiExecutorFactory.GetLpiExecutor((uint8_t)LpiOpCode::Clear);

					// assert
					ClearNonAnimatedLpiExecutor* clearLpiExecutor = dynamic_cast<ClearNonAnimatedLpiExecutor*>(lpiExecutor);
					Assert::IsNotNull(lpiExecutor);
				}

				TEST_METHOD(WhenOpIsSolid_SolidLpiExecutorReturned)
				{
					// arrange
					LpiExecutorFactory lpiExecutorFactory;

					// act
					LpiExecutor* lpiExecutor = lpiExecutorFactory.GetLpiExecutor((uint8_t)LpiOpCode::Solid);

					// assert
					SolidNonAnimatedLpiExecutor* solidLpiExecutor = dynamic_cast<SolidNonAnimatedLpiExecutor*>(lpiExecutor);
					Assert::IsNotNull(solidLpiExecutor);
				}

				TEST_METHOD(WhenOpIsPattern_PatternLpiExecutorReturned)
				{
					// arrange
					LpiExecutorFactory lpiExecutorFactory;

					// act
					LpiExecutor* lpiExecutor = lpiExecutorFactory.GetLpiExecutor((uint8_t)LpiOpCode::Pattern);

					// assert
					PatternNonAnimatedLpiExecutor* patternLpiExecutor = dynamic_cast<PatternNonAnimatedLpiExecutor*>(lpiExecutor);
					Assert::IsNotNull(patternLpiExecutor);
				}

				TEST_METHOD(WhenOpIsSlider_SliderLpiExecutorReturned)
				{
					// arrange
					LpiExecutorFactory lpiExecutorFactory;

					// act
					LpiExecutor* lpiExecutor = lpiExecutorFactory.GetLpiExecutor((uint8_t)LpiOpCode::Slider);

					// assert
					SliderAnimatedLpiExecutor* sliderLpiExecutor = dynamic_cast<SliderAnimatedLpiExecutor*>(lpiExecutor);
					Assert::IsNotNull(sliderLpiExecutor);
				}

				TEST_METHOD(WhenOpIsFade_FadeLpiExecutorReturned)
				{
					// arrange
					LpiExecutorFactory lpiExecutorFactory;

					// act
					LpiExecutor* lpiExecutor = lpiExecutorFactory.GetLpiExecutor((uint8_t)LpiOpCode::Fade);

					// assert
					FadeAnimatedLpiExecutor* fadeLpiExecutor = dynamic_cast<FadeAnimatedLpiExecutor*>(lpiExecutor);
					Assert::IsNotNull(fadeLpiExecutor);
				}

				TEST_METHOD(WhenOpIsStochastic_StochasticLpiExecutorReturned)
				{
					// arrange
					LpiExecutorFactory lpiExecutorFactory;

					// act
					LpiExecutor* lpiExecutor = lpiExecutorFactory.GetLpiExecutor((uint8_t)LpiOpCode::Stochastic);

					// assert
					StochasticNonAnimatedLpiExecutor* stochasticLpiExecutor = dynamic_cast<StochasticNonAnimatedLpiExecutor*>(lpiExecutor);
					Assert::IsNotNull(stochasticLpiExecutor);
				}

				TEST_METHOD(WhenOpIsBlocks_BlocksLpiExecutorReturned)
				{
					// arrange
					LpiExecutorFactory lpiExecutorFactory;

					// act
					LpiExecutor* lpiExecutor = lpiExecutorFactory.GetLpiExecutor((uint8_t)LpiOpCode::Blocks);

					// assert
					BlocksNonAnimatedLpiExecutor* blocksLpiExecutor = dynamic_cast<BlocksNonAnimatedLpiExecutor*>(lpiExecutor);
					Assert::IsNotNull(blocksLpiExecutor);
				}

				TEST_METHOD(WhenOpIsRainbow_RainbowLpiExecutorReturned)
				{
					// arrange
					LpiExecutorFactory lpiExecutorFactory;

					// act
					LpiExecutor* lpiExecutor = lpiExecutorFactory.GetLpiExecutor((uint8_t)LpiOpCode::Rainbow);

					// assert
					RainbowAnimatedLpiExecutor* rainbowLpiExecutor = dynamic_cast<RainbowAnimatedLpiExecutor*>(lpiExecutor);
					Assert::IsNotNull(rainbowLpiExecutor);
				}
			};
		}
	}
}