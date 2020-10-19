// #include "pch.h"
#include "CppUnitTest.h"
// #include "../Light Server/src/ValueDomainTypes.h"
#include "../../Light-Server/src/StringProcessor.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace LS
{
	TEST_CLASS(StringProcesor_ExtractColourFromHexEncoded)
	{
	public:
		// *** ExtractColourFromHexEncoded Tests ***
		// Negative test cases
		TEST_METHOD(NullString)
		{
			// arrange
			StringProcessor* p = new StringProcessor();
			bool isValid;

			// act
			Colour c = p->ExtractColourFromHexEncoded(nullptr, isValid);

			// assert
			Assert::IsFalse(isValid);
		}

		TEST_METHOD(EmptyString)
		{
			// arrange
			StringProcessor* p = new StringProcessor();
			bool isValid;

			// act
			Colour c = p->ExtractColourFromHexEncoded("", isValid);

			// assert
			Assert::IsFalse(isValid);
		}

		TEST_METHOD(ThreeChars)
		{
			// arrange
			StringProcessor* p = new StringProcessor();
			bool isValid;

			// act
			Colour c = p->ExtractColourFromHexEncoded("FFF", isValid);

			// assert
			Assert::IsFalse(isValid);
		}

		TEST_METHOD(FiveChars)
		{
			// arrange
			StringProcessor* p = new StringProcessor();
			bool isValid;

			// act
			Colour c = p->ExtractColourFromHexEncoded("FFFFF", isValid);

			// assert
			Assert::IsFalse(isValid);
		}

		TEST_METHOD(InvalidRed)
		{
			// arrange
			StringProcessor* p = new StringProcessor();
			bool isValid;

			// act
			Colour c = p->ExtractColourFromHexEncoded("G0FFFF", isValid);

			// assert
			Assert::IsFalse(isValid);
		}

		TEST_METHOD(InvalidGreen)
		{
			// arrange
			StringProcessor* p = new StringProcessor();
			bool isValid;

			// act
			Colour c = p->ExtractColourFromHexEncoded("FFG0FF", isValid);

			// assert
			Assert::IsFalse(isValid);
		}

		TEST_METHOD(InvalidBlue)
		{
			// arrange
			StringProcessor* p = new StringProcessor();
			bool isValid;

			// act
			Colour c = p->ExtractColourFromHexEncoded("FFFFG0", isValid);

			// assert
			Assert::IsFalse(isValid);
		}

		TEST_METHOD(Lowercase)
		{
			// arrange
			StringProcessor* p = new StringProcessor();
			bool isValid;

			// act
			Colour c = p->ExtractColourFromHexEncoded("ffffff", isValid);

			// assert
			Assert::IsFalse(isValid);
		}

		TEST_METHOD(InvalidSymbol)
		{
			// arrange
			StringProcessor* p = new StringProcessor();
			bool isValid;

			// act
			Colour c = p->ExtractColourFromHexEncoded("FF--FF", isValid);

			// assert
			Assert::IsFalse(isValid);
		}


		// Positive test cases
		TEST_METHOD(ValidColour1)
		{
			// arrange
			StringProcessor* p = new StringProcessor();
			bool isValid;

			// act
			Colour c = p->ExtractColourFromHexEncoded("000000", isValid);

			// assert
			Assert::IsTrue(isValid);
			Assert::AreEqual<uint8_t>(0, c.red);
			Assert::AreEqual<uint8_t>(0, c.green);
			Assert::AreEqual<uint8_t>(0, c.blue);
		}

		TEST_METHOD(ValidColour2)
		{
			// arrange
			StringProcessor* p = new StringProcessor();
			bool isValid;

			// act
			Colour c = p->ExtractColourFromHexEncoded("FFFFFF", isValid);

			// assert
			Assert::IsTrue(isValid);
			Assert::AreEqual<uint8_t>(255, c.red);
			Assert::AreEqual<uint8_t>(255, c.green);
			Assert::AreEqual<uint8_t>(255, c.blue);
		}

		TEST_METHOD(ValidColour3)
		{
			// arrange
			StringProcessor* p = new StringProcessor();
			bool isValid;

			// act
			Colour c = p->ExtractColourFromHexEncoded("A0B0C0", isValid);

			// assert
			Assert::IsTrue(isValid);
			Assert::AreEqual<uint8_t>(160, c.red);
			Assert::AreEqual<uint8_t>(176, c.green);
			Assert::AreEqual<uint8_t>(192, c.blue);
		}

		TEST_METHOD(ValidColour4)
		{
			// arrange
			StringProcessor* p = new StringProcessor();
			bool isValid;

			// act
			Colour c = p->ExtractColourFromHexEncoded("D0E0F0", isValid);

			// assert
			Assert::IsTrue(isValid);
			Assert::AreEqual<uint8_t>(208, c.red);
			Assert::AreEqual<uint8_t>(224, c.green);
			Assert::AreEqual<uint8_t>(240, c.blue);
		}

		TEST_METHOD(ValidColour5)
		{
			// arrange
			StringProcessor* p = new StringProcessor();
			bool isValid;

			// act
			Colour c = p->ExtractColourFromHexEncoded("123456", isValid);

			// assert
			Assert::IsTrue(isValid);
			Assert::AreEqual<uint8_t>(18, c.red);
			Assert::AreEqual<uint8_t>(52, c.green);
			Assert::AreEqual<uint8_t>(86, c.blue);
		}

		TEST_METHOD(ValidColour6)
		{
			// arrange
			StringProcessor* p = new StringProcessor();
			bool isValid;

			// act
			Colour c = p->ExtractColourFromHexEncoded("789000", isValid);

			// assert
			Assert::IsTrue(isValid);
			Assert::AreEqual<uint8_t>(120, c.red);
			Assert::AreEqual<uint8_t>(144, c.green);
			Assert::AreEqual<uint8_t>(0, c.blue);
		}
	};


	TEST_CLASS(StringProcesor_ExtractNumberFromHexEncoded)
	{
	public:

		// *** ExtractNumberFromHexEncoded Tests ***
		// Negative test cases
		TEST_METHOD(NullString)
		{
			// arrange
			StringProcessor* p = new StringProcessor();
			bool isValid;

			// act
			uint8_t n = p->ExtractNumberFromHexEncoded(nullptr, 0, 255, isValid);

			// assert
			Assert::IsFalse(isValid);
		}

		TEST_METHOD(EmptyString)
		{
			// arrange
			StringProcessor* p = new StringProcessor();
			bool isValid;

			// act
			uint8_t n = p->ExtractNumberFromHexEncoded("", 0, 255, isValid);

			// assert
			Assert::IsFalse(isValid);
		}

		TEST_METHOD(SingleDigitOnly)
		{
			// arrange
			StringProcessor* p = new StringProcessor();
			bool isValid;

			// act
			uint8_t n = p->ExtractNumberFromHexEncoded("F", 0, 255, isValid);

			// assert
			Assert::IsFalse(isValid);
		}

		TEST_METHOD(InvalidHex1)
		{
			// arrange
			StringProcessor* p = new StringProcessor();
			bool isValid;

			// act
			uint8_t n = p->ExtractNumberFromHexEncoded("GG", 0, 255, isValid);

			// assert
			Assert::IsFalse(isValid);
		}

		TEST_METHOD(InvalidHex2)
		{
			// arrange
			StringProcessor* p = new StringProcessor();
			bool isValid;

			// act
			uint8_t n = p->ExtractNumberFromHexEncoded("0G", 0, 255, isValid);

			// assert
			Assert::IsFalse(isValid);
		}

		TEST_METHOD(InvalidHex3)
		{
			// arrange
			StringProcessor* p = new StringProcessor();
			bool isValid;

			// act
			uint8_t n = p->ExtractNumberFromHexEncoded("-F", 0, 255, isValid);

			// assert
			Assert::IsFalse(isValid);
		}

		TEST_METHOD(InvalidHex4)
		{
			// arrange
			StringProcessor* p = new StringProcessor();
			bool isValid;

			// act
			uint8_t n = p->ExtractNumberFromHexEncoded("ab", 0, 255, isValid);

			// assert
			Assert::IsFalse(isValid);
		}

		TEST_METHOD(MinGreaterThanMax)
		{
			// arrange
			StringProcessor* p = new StringProcessor();
			bool isValid;

			// act
			uint8_t n = p->ExtractNumberFromHexEncoded("C7", 201, 200, isValid);

			// assert
			Assert::IsFalse(isValid);
		}

		TEST_METHOD(ValueGreaterThanMax)
		{
			// arrange
			StringProcessor* p = new StringProcessor();
			bool isValid;

			// act
			uint8_t n = p->ExtractNumberFromHexEncoded("C9", 0, 200, isValid);

			// assert
			Assert::IsFalse(isValid);
		}

		TEST_METHOD(ValueLessThanMin)
		{
			// arrange
			StringProcessor* p = new StringProcessor();
			bool isValid;

			// act
			uint8_t n = p->ExtractNumberFromHexEncoded("00", 1, 200, isValid);

			// assert
			Assert::IsFalse(isValid);
		}

		
		// Positive test cases
		TEST_METHOD(ValueEqualMin)
		{
			// arrange
			StringProcessor* p = new StringProcessor();
			bool isValid;

			// act
			uint8_t n = p->ExtractNumberFromHexEncoded("00", 0, 255, isValid);

			// assert
			Assert::IsTrue(isValid);
			Assert::AreEqual<int>(0, n);
		}

		TEST_METHOD(ValueEqualMax)
		{
			// arrange
			StringProcessor* p = new StringProcessor();
			bool isValid;

			// act
			uint8_t n = p->ExtractNumberFromHexEncoded("FF", 0, 255, isValid);

			// assert
			Assert::IsTrue(isValid);
			Assert::AreEqual<int>(255, n);
		}

		TEST_METHOD(ValueGreaterThanMin)
		{
			// arrange
			StringProcessor* p = new StringProcessor();
			bool isValid;

			// act
			uint8_t n = p->ExtractNumberFromHexEncoded("01", 0, 255, isValid);

			// assert
			Assert::IsTrue(isValid);
			Assert::AreEqual<int>(1, n);
		}

		TEST_METHOD(ValueLessThanMax)
		{
			// arrange
			StringProcessor* p = new StringProcessor();
			bool isValid;

			// act
			uint8_t n = p->ExtractNumberFromHexEncoded("FE", 0, 255, isValid);

			// assert
			Assert::IsTrue(isValid);
			Assert::AreEqual<int>(254, n);
		}

		TEST_METHOD(ValidValue1)
		{
			// arrange
			StringProcessor* p = new StringProcessor();
			bool isValid;

			// act
			uint8_t n = p->ExtractNumberFromHexEncoded("A0", 0, 255, isValid);

			// assert
			Assert::IsTrue(isValid);
			Assert::AreEqual<int>(160, n);
		}

		TEST_METHOD(ValidValue2)
		{
			// arrange
			StringProcessor* p = new StringProcessor();
			bool isValid;

			// act
			uint8_t n = p->ExtractNumberFromHexEncoded("B1", 0, 255, isValid);

			// assert
			Assert::IsTrue(isValid);
			Assert::AreEqual<int>(177, n);
		}

		TEST_METHOD(ValidValue3)
		{
			// arrange
			StringProcessor* p = new StringProcessor();
			bool isValid;

			// act
			uint8_t n = p->ExtractNumberFromHexEncoded("C2", 0, 255, isValid);

			// assert
			Assert::IsTrue(isValid);
			Assert::AreEqual<int>(194, n);
		}

		TEST_METHOD(ValidValue4)
		{
			// arrange
			StringProcessor* p = new StringProcessor();
			bool isValid;

			// act
			uint8_t n = p->ExtractNumberFromHexEncoded("D3", 0, 255, isValid);

			// assert
			Assert::IsTrue(isValid);
			Assert::AreEqual<int>(211, n);
		}

		TEST_METHOD(ValidValue5)
		{
			// arrange
			StringProcessor* p = new StringProcessor();
			bool isValid;

			// act
			uint8_t n = p->ExtractNumberFromHexEncoded("E4", 0, 255, isValid);

			// assert
			Assert::IsTrue(isValid);
			Assert::AreEqual<int>(228, n);
		}

		TEST_METHOD(ValidValue6)
		{
			// arrange
			StringProcessor* p = new StringProcessor();
			bool isValid;

			// act
			uint8_t n = p->ExtractNumberFromHexEncoded("F5", 0, 255, isValid);

			// assert
			Assert::IsTrue(isValid);
			Assert::AreEqual<int>(245, n);
		}

		TEST_METHOD(ValidValue7)
		{
			// arrange
			StringProcessor* p = new StringProcessor();
			bool isValid;

			// act
			uint8_t n = p->ExtractNumberFromHexEncoded("67", 0, 255, isValid);

			// assert
			Assert::IsTrue(isValid);
			Assert::AreEqual<int>(103, n);
		}

		TEST_METHOD(ValidValue8)
		{
			// arrange
			StringProcessor* p = new StringProcessor();
			bool isValid;

			// act
			uint8_t n = p->ExtractNumberFromHexEncoded("89", 0, 255, isValid);

			// assert
			Assert::IsTrue(isValid);
			Assert::AreEqual<int>(137, n);
		}
	};



	TEST_CLASS(StringProcesor_ExtractRIFromHexEncoded)
	{
	public:
		// Negative tests
		TEST_METHOD(IsNull)
		{
			// arrange
			StringProcessor* p = new StringProcessor();
			bool isValid;

			// act
			RI r = p->ExtractRIFromHexEncoded(nullptr, isValid);

			// assert
			Assert::IsFalse(isValid);
		}

		TEST_METHOD(EmptyString)
		{
			// arrange
			StringProcessor* p = new StringProcessor();
			bool isValid;

			// act
			RI r = p->ExtractRIFromHexEncoded("", isValid);

			// assert
			Assert::IsFalse(isValid);
		}

		TEST_METHOD(InvalidColour)
		{
			// arrange
			StringProcessor* p = new StringProcessor();
			bool isValid;

			// act
			RI r = p->ExtractRIFromHexEncoded("FFGGFF01", isValid);

			// assert
			Assert::IsFalse(isValid);
		}

		TEST_METHOD(MissingOneCharacter)
		{
			// arrange
			StringProcessor* p = new StringProcessor();
			bool isValid;

			// act
			RI r = p->ExtractRIFromHexEncoded("FFFFF01", isValid);

			// assert
			Assert::IsFalse(isValid);
		}

		TEST_METHOD(MissingThreeCharacters)
		{
			// arrange
			StringProcessor* p = new StringProcessor();
			bool isValid;

			// act
			RI r = p->ExtractRIFromHexEncoded("FFF01", isValid);

			// assert
			Assert::IsFalse(isValid);
		}

		TEST_METHOD(MissingNumber)
		{
			// arrange
			StringProcessor* p = new StringProcessor();
			bool isValid;

			// act
			RI r = p->ExtractRIFromHexEncoded("FFFFFF", isValid);

			// assert
			Assert::IsFalse(isValid);
		}

		TEST_METHOD(NumberIsZero)
		{
			// arrange
			StringProcessor* p = new StringProcessor();
			bool isValid;

			// act
			RI r = p->ExtractRIFromHexEncoded("FFFFFF00", isValid);

			// assert
			Assert::IsFalse(isValid);
		}


		// Positive tests
		TEST_METHOD(OneLEDAffected)
		{
			// arrange
			StringProcessor* p = new StringProcessor();
			bool isValid;

			// act
			RI r = p->ExtractRIFromHexEncoded("FFFFFF01", isValid);

			// assert
			Assert::IsTrue(isValid);
			Assert::AreEqual<uint8_t>(r.number, 1);
			Assert::AreEqual<uint8_t>(r.colour.red, 255);
			Assert::AreEqual<uint8_t>(r.colour.green, 255);
			Assert::AreEqual<uint8_t>(r.colour.blue, 255);
		}


		TEST_METHOD(TwoHundredFiftyFiveLEDsAffected)
		{
			// arrange
			StringProcessor* p = new StringProcessor();
			bool isValid;

			// act
			RI r = p->ExtractRIFromHexEncoded("FFFFFFFF", isValid);

			// assert
			Assert::IsTrue(isValid);
			Assert::AreEqual<uint8_t>(r.number, 255);
			Assert::AreEqual<uint8_t>(r.colour.red, 255);
			Assert::AreEqual<uint8_t>(r.colour.green, 255);
			Assert::AreEqual<uint8_t>(r.colour.blue, 255);
		}

		TEST_METHOD(RedColourFiveLEDs)
		{
			// arrange
			StringProcessor* p = new StringProcessor();
			bool isValid;

			// act
			RI r = p->ExtractRIFromHexEncoded("FF000005", isValid);

			// assert
			Assert::IsTrue(isValid);
			Assert::AreEqual<uint8_t>(r.number, 5);
			Assert::AreEqual<uint8_t>(r.colour.red, 255);
			Assert::AreEqual<uint8_t>(r.colour.green, 0);
			Assert::AreEqual<uint8_t>(r.colour.blue, 0);
		}

		TEST_METHOD(GreenColourTenLEDs)
		{
			// arrange
			StringProcessor* p = new StringProcessor();
			bool isValid;

			// act
			RI r = p->ExtractRIFromHexEncoded("00FF0010", isValid);

			// assert
			Assert::IsTrue(isValid);
			Assert::AreEqual<uint8_t>(r.number, 16);
			Assert::AreEqual<uint8_t>(r.colour.red, 0);
			Assert::AreEqual<uint8_t>(r.colour.green, 255);
			Assert::AreEqual<uint8_t>(r.colour.blue, 0);
		}

		TEST_METHOD(BlueColourFiftyLEDs)
		{
			// arrange
			StringProcessor* p = new StringProcessor();
			bool isValid;

			// act
			RI r = p->ExtractRIFromHexEncoded("0000FF32", isValid);

			// assert
			Assert::IsTrue(isValid);
			Assert::AreEqual<uint8_t>(r.number, 50);
			Assert::AreEqual<uint8_t>(r.colour.red, 0);
			Assert::AreEqual<uint8_t>(r.colour.green, 0);
			Assert::AreEqual<uint8_t>(r.colour.blue, 255);
		}
	};

	TEST_CLASS(StringProcesor_ExtractLPIFromHexEncoded)
	{
	public:
		// Negative test cases
		TEST_METHOD(NullString)
		{
			// arrange
			StringProcessor* p = new StringProcessor();
			bool isValid;

			// act
			LPIInstruction lpi = p->ExtractLPIFromHexEncoded(nullptr, isValid);

			// assert
			Assert::IsFalse(isValid);
		}

		TEST_METHOD(InvalidOpCode_InvalidSymbol)
		{
			// arrange
			StringProcessor* p = new StringProcessor();
			bool isValid;

			// act
			LPIInstruction lpi = p->ExtractLPIFromHexEncoded("-0010000", isValid);

			// assert
			Assert::IsFalse(isValid);
		}

		TEST_METHOD(InvalidOpCode_InvalidHexValue1)
		{
			// arrange
			StringProcessor* p = new StringProcessor();
			bool isValid;

			// act
			LPIInstruction lpi = p->ExtractLPIFromHexEncoded("HF010000", isValid);

			// assert
			Assert::IsFalse(isValid);
		}

		TEST_METHOD(InvalidOpCode_InvalidHexValue2)
		{
			// arrange
			StringProcessor* p = new StringProcessor();
			bool isValid;

			// act
			LPIInstruction lpi = p->ExtractLPIFromHexEncoded("FH010000", isValid);

			// assert
			Assert::IsFalse(isValid);
		}

		TEST_METHOD(InvalidOpCode_MissingOpCode)
		{
			// arrange
			StringProcessor* p = new StringProcessor();
			bool isValid;

			// act
			LPIInstruction lpi = p->ExtractLPIFromHexEncoded("010000", isValid);

			// assert
			Assert::IsFalse(isValid);
		}




		TEST_METHOD(InvalidDuration_InvalidSymbol)
		{
			// arrange
			StringProcessor* p = new StringProcessor();
			bool isValid;

			// act
			LPIInstruction lpi = p->ExtractLPIFromHexEncoded("00-10000", isValid);

			// assert
			Assert::IsFalse(isValid);
		}

		TEST_METHOD(InvalidDuration_InvalidHexValue1)
		{
			// arrange
			StringProcessor* p = new StringProcessor();
			bool isValid;

			// act
			LPIInstruction lpi = p->ExtractLPIFromHexEncoded("FFH10000", isValid);

			// assert
			Assert::IsFalse(isValid);
		}

		TEST_METHOD(InvalidDuration_InvalidHexValue2)
		{
			// arrange
			StringProcessor* p = new StringProcessor();
			bool isValid;

			// act
			LPIInstruction lpi = p->ExtractLPIFromHexEncoded("FF0H0000", isValid);

			// assert
			Assert::IsFalse(isValid);
		}

		TEST_METHOD(InvalidDuration_MissingDuration)
		{
			// arrange
			StringProcessor* p = new StringProcessor();
			bool isValid;

			// act
			LPIInstruction lpi = p->ExtractLPIFromHexEncoded("FF0000", isValid);

			// assert
			Assert::IsFalse(isValid);
		}

		TEST_METHOD(InvalidDuration_ZeroValue)
		{
			// arrange
			StringProcessor* p = new StringProcessor();
			bool isValid;

			// act
			LPIInstruction lpi = p->ExtractLPIFromHexEncoded("FF000000", isValid);

			// assert
			Assert::IsFalse(isValid);
		}


		TEST_METHOD(InvalidReserved1_Not00_1)
		{
			// arrange
			StringProcessor* p = new StringProcessor();
			bool isValid;

			// act
			LPIInstruction lpi = p->ExtractLPIFromHexEncoded("FF010200", isValid);

			// assert
			Assert::IsFalse(isValid);
		}

		TEST_METHOD(InvalidReserved1_Not00_2)
		{
			// arrange
			StringProcessor* p = new StringProcessor();
			bool isValid;

			// act
			LPIInstruction lpi = p->ExtractLPIFromHexEncoded("FF01F-00", isValid);

			// assert
			Assert::IsFalse(isValid);
		}

		TEST_METHOD(InvalidReserved1_Missing)
		{
			// arrange
			StringProcessor* p = new StringProcessor();
			bool isValid;

			// act
			LPIInstruction lpi = p->ExtractLPIFromHexEncoded("FF0100", isValid);

			// assert
			Assert::IsFalse(isValid);
		}

		TEST_METHOD(InvalidReserved2_Not00_1)
		{
			// arrange
			StringProcessor* p = new StringProcessor();
			bool isValid;

			// act
			LPIInstruction lpi = p->ExtractLPIFromHexEncoded("FF010002", isValid);

			// assert
			Assert::IsFalse(isValid);
		}

		TEST_METHOD(InvalidReserved2_Not00_2)
		{
			// arrange
			StringProcessor* p = new StringProcessor();
			bool isValid;

			// act
			LPIInstruction lpi = p->ExtractLPIFromHexEncoded("FF0100F-", isValid);

			// assert
			Assert::IsFalse(isValid);
		}



		/** Postive cases **/
		TEST_METHOD(ValidOpCode_Lowerboundary)
		{
			// arrange
			StringProcessor* p = new StringProcessor();
			bool isValid;

			// act
			LPIInstruction lpi = p->ExtractLPIFromHexEncoded("00010000", isValid);

			// assert
			Assert::IsTrue(isValid);
		}

		TEST_METHOD(ValidOpCode_Upperboundary)
		{
			// arrange
			StringProcessor* p = new StringProcessor();
			bool isValid;

			// act
			LPIInstruction lpi = p->ExtractLPIFromHexEncoded("FF010000", isValid);

			// assert
			Assert::IsTrue(isValid);
		}

		TEST_METHOD(ValidDuration_Lowerboundary)
		{
			// arrange
			StringProcessor* p = new StringProcessor();
			bool isValid;

			// act
			LPIInstruction lpi = p->ExtractLPIFromHexEncoded("00010000", isValid);

			// assert
			Assert::IsTrue(isValid);
		}

		TEST_METHOD(ValidDuration_Upperboundary)
		{
			// arrange
			StringProcessor* p = new StringProcessor();
			bool isValid;

			// act
			LPIInstruction lpi = p->ExtractLPIFromHexEncoded("00FF0000", isValid);

			// assert
			Assert::IsTrue(isValid);
		}

		TEST_METHOD(Valid_ReturnOpCodeIsExpectedValue)
		{
			// arrange
			StringProcessor* p = new StringProcessor();
			bool isValid;

			// act
			LPIInstruction lpi = p->ExtractLPIFromHexEncoded("01FF0000", isValid);

			// assert
			Assert::AreEqual<uint8_t>(1, lpi.opcode);
		}

		TEST_METHOD(Valid_ReturnDurationIsExpectedValue)
		{
			// arrange
			StringProcessor* p = new StringProcessor();
			bool isValid;

			// act
			LPIInstruction lpi = p->ExtractLPIFromHexEncoded("01FF0000", isValid);

			// assert
			Assert::AreEqual<uint8_t>(255, lpi.duration);
		}
	};

	TEST_CLASS(StringProcesor_ExtractBoolFromHexEncoded)
	{
	public:
		// Negative test cases
		TEST_METHOD(NotValid_NullString)
		{
			// arrange
			StringProcessor* p = new StringProcessor();
			bool isValid;

			// act
			bool extractedBool = p->ExtractBoolFromHexEncoded(nullptr, isValid);

			// assert
			Assert::IsFalse(isValid);
		}

		TEST_METHOD(NotValid_EmptyString)
		{
			// arrange
			StringProcessor* p = new StringProcessor();
			bool isValid;

			// act
			bool extractedBool = p->ExtractBoolFromHexEncoded("", isValid);

			// assert
			Assert::IsFalse(isValid);
		}

		TEST_METHOD(NotValid_NegativeSymbol)
		{
			// arrange
			StringProcessor* p = new StringProcessor();
			bool isValid;

			// act
			bool extractedBool = p->ExtractBoolFromHexEncoded("-", isValid);

			// assert
			Assert::IsFalse(isValid);
		}

		TEST_METHOD(NotValid_ValueOf2)
		{
			// arrange
			StringProcessor* p = new StringProcessor();
			bool isValid;

			// act
			bool extractedBool = p->ExtractBoolFromHexEncoded("2", isValid);

			// assert
			Assert::IsFalse(isValid);
		}

		TEST_METHOD(NotValid_ValueOfA)
		{
			// arrange
			StringProcessor* p = new StringProcessor();
			bool isValid;

			// act
			bool extractedBool = p->ExtractBoolFromHexEncoded("A", isValid);

			// assert
			Assert::IsFalse(isValid);
		}

		TEST_METHOD(Valid_Value0)
		{
			// arrange
			StringProcessor* p = new StringProcessor();
			bool isValid;

			// act
			bool extractedBool = p->ExtractBoolFromHexEncoded("0", isValid);

			// assert
			Assert::IsTrue(isValid);
		}

		TEST_METHOD(Valid_Value1)
		{
			// arrange
			StringProcessor* p = new StringProcessor();
			bool isValid;

			// act
			bool extractedBool = p->ExtractBoolFromHexEncoded("1", isValid);

			// assert
			Assert::IsTrue(isValid);
		}

		TEST_METHOD(Valid_ReturnValueIsFalse)
		{
			// arrange
			StringProcessor* p = new StringProcessor();
			bool isValid;

			// act
			bool extractedBool = p->ExtractBoolFromHexEncoded("0", isValid);

			// assert
			Assert::IsFalse(extractedBool);
		}

		TEST_METHOD(Valid_ReturnValueIsTrue)
		{
			// arrange
			StringProcessor* p = new StringProcessor();
			bool isValid;

			// act
			bool extractedBool = p->ExtractBoolFromHexEncoded("1", isValid);

			// assert
			Assert::IsTrue(extractedBool);
		}
	};

	TEST_CLASS(StringProcesor_ConvertNumberToHexEncoded)
	{
	public:
		// Negative test cases
		TEST_METHOD(NotValid_NullString)
		{
			// arrange
			StringProcessor* p = new StringProcessor();
			char putBuffer[3] = "**";

			// act
			p->ConvertNumberToHexEncoded(nullptr, 90);

			// assert
			int putBufferCompare = strcmp("**", putBuffer);
			Assert::AreEqual<int>(0, putBufferCompare);
		}

		// Positive test cases
		TEST_METHOD(Valid_00Expected)
		{
			// arrange
			StringProcessor* p = new StringProcessor();
			char putBuffer[3] = "**";

			// act
			p->ConvertNumberToHexEncoded(putBuffer, 0);

			// assert
			int putBufferCompare = strcmp("00", putBuffer);
			Assert::AreEqual<int>(0, putBufferCompare);
		}

		TEST_METHOD(Valid_32Expected)
		{
			// arrange
			StringProcessor* p = new StringProcessor();
			char putBuffer[3] = "**";

			// act
			p->ConvertNumberToHexEncoded(putBuffer, 50);

			// assert
			int putBufferCompare = strcmp("32", putBuffer);
			Assert::AreEqual<int>(0, putBufferCompare);
		}
		TEST_METHOD(Valid_64Expected)
		{
			// arrange
			StringProcessor* p = new StringProcessor();
			char putBuffer[3] = "**";

			// act
			p->ConvertNumberToHexEncoded(putBuffer, 100);

			// assert
			int putBufferCompare = strcmp("64", putBuffer);
			Assert::AreEqual<int>(0, putBufferCompare);
		}

		TEST_METHOD(Valid_C8Expected)
		{
			// arrange
			StringProcessor* p = new StringProcessor();
			char putBuffer[3] = "**";

			// act
			p->ConvertNumberToHexEncoded(putBuffer, 200);

			// assert
			int putBufferCompare = strcmp("C8", putBuffer);
			Assert::AreEqual<int>(0, putBufferCompare);
		}

		TEST_METHOD(Valid_FFExpected)
		{
			// arrange
			StringProcessor* p = new StringProcessor();
			char putBuffer[3] = "**";

			// act
			p->ConvertNumberToHexEncoded(putBuffer, 255);

			// assert
			int putBufferCompare = strcmp("FF", putBuffer);
			Assert::AreEqual<int>(0, putBufferCompare);
		}
	};
}