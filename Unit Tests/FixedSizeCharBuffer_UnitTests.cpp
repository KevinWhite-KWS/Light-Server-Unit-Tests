#include "CppUnitTest.h"
#include "../../Light Server/src/FixedSizeCharBuffer.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace LS
{
	TEST_CLASS(FixedSizeCharBuffer_Constructor)
	{
	public:
		TEST_METHOD(BufferHasBeenZerod)
		{
			// arrange
			FixedSizeCharBuffer fixedSizeCharBuffer = FixedSizeCharBuffer(10);

			// act

			// assert
			char* buf = fixedSizeCharBuffer.GetBuffer();
			for (int i = 0; i < 10; i++) Assert::AreEqual<int>(0, *(buf + i));
		}
	};

	TEST_CLASS(FixedSizeCharBuffer_ClearBuffer)
	{
	public:
		TEST_METHOD(BufferHasBeenZerod)
		{
			// arrange
			FixedSizeCharBuffer fixedSizeCharBuffer = FixedSizeCharBuffer(10);
			char* buf = fixedSizeCharBuffer.GetBuffer();
			for (int i = 0; i < 10; i++)* (buf + i) = 1;

			// act
			fixedSizeCharBuffer.ClearBuffer();

			// assert
			for (int i = 0; i < 10; i++) Assert::AreEqual<int>(0, *(buf + i));
		}
	};

	TEST_CLASS(FixedSizeCharBuffer_LoadFromBuffer)
	{
	public:
		TEST_METHOD(BufferHasBeenCopied)
		{
			// arrange
			FixedSizeCharBuffer fixedSizeCharBuffer = FixedSizeCharBuffer(100);
			const char sourceBuffer[] = "Hello World";

			// act
			fixedSizeCharBuffer.LoadFromBuffer(sourceBuffer);

			// assert
			char* internalBuffer = fixedSizeCharBuffer.GetBuffer();
			Assert::IsTrue(strcmp(sourceBuffer, internalBuffer) == 0);
		}

		TEST_METHOD(BufferPartiallyCopied_TooSmall)
		{
			// arrange
			FixedSizeCharBuffer fixedSizeCharBuffer = FixedSizeCharBuffer(6);
			const char sourceBuffer[] = "Hello World";
			const char expectedResult[] = "Hello";

			// act
			fixedSizeCharBuffer.LoadFromBuffer(sourceBuffer);

			// assert
			char* internalBuffer = fixedSizeCharBuffer.GetBuffer();
			Assert::IsTrue(strcmp(expectedResult, internalBuffer) == 0);
		}


		TEST_METHOD(NothingCopied_NullSource)
		{
			// arrange
			FixedSizeCharBuffer fixedSizeCharBuffer = FixedSizeCharBuffer(5);
			fixedSizeCharBuffer.ClearBuffer();
			char* buffer = fixedSizeCharBuffer.GetBuffer();
			for (int i = 0; i < 4; i++)* (buffer + i) = '1';
			*(buffer + 4) = '\0';
			const char expectedResult[] = "1111";

			// act
			fixedSizeCharBuffer.LoadFromBuffer(nullptr);

			// assert
			char* internalBuffer = fixedSizeCharBuffer.GetBuffer();
			Assert::IsTrue(strcmp(expectedResult, internalBuffer) == 0);
		}
	};
}