#include "CppUnitTest.h"
#include <iostream>

#include "../../Light-Server/src/ArduinoJson-v6.12.0.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace std;

namespace LS
{
	namespace Testing {
		TEST_CLASS(Testing) {
			public:
				TEST_METHOD(JSON_BasicTest1)
				{
					// arrange
					// char json[] = "{ \"name\" : \"kevin\" }";
					char json[] = "{ \"name\" : \"my program\", \"instructions\" : { \"instruction\":\"0101000000FF00\",  \"instruction\":\"01010000FF0000\"} }";
					StaticJsonDocument<1000> jsonDoc;

					// act
					DeserializationError error = deserializeJson(jsonDoc, json);

					JsonObject ins = jsonDoc["instructions"];
					// JsonVariant el = ins.
					// const char * val = el.as<const char*>();

					//// assert
					//// const char* name = jsonDoc["name"];
					//// const char* notExist = jsonDoc["notexist"];
					//const char* progName = jsonDoc["name"];
					//JsonObject instructions = jsonDoc["instructions"];

					//// using C++98 syntax (for older compilers):
					//for (JsonObject::iterator it = instructions.begin(); it != instructions.end(); ++it) {
					//	const char* key = it->key().c_str();
					//	const char* val = it->value().as<char*>();

					//	// Logger::WriteMessage(key + " = " + val);
					//	// Logger::WriteMessage(val);
					//	cout << key << " = " << val;

					//	int x = 10;
					//	// const char* val = it->value().as<char*>;
					//}
				}
		};
	}
}