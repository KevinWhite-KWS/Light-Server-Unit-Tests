#include "CppUnitTest.h"
#include <iostream>

#include "../../Light Server/src/ArduinoJson-v6.12.0.h"

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
					char json[] = "{ \"name\" : \"test prog\", \"instructions\" : { \"instruction\" : \"ins 1\", \"instruction\" : \"ins 2\" } }";
					StaticJsonDocument<1000> jsonDoc;

					// act
					DeserializationError error = deserializeJson(jsonDoc, json);

					// assert
					// const char* name = jsonDoc["name"];
					// const char* notExist = jsonDoc["notexist"];
					const char* progName = jsonDoc["name"];
					JsonObject instructions = jsonDoc["instructions"];

					// using C++98 syntax (for older compilers):
					for (JsonObject::iterator it = instructions.begin(); it != instructions.end(); ++it) {
						const char* key = it->key().c_str();
						const char* val = it->value().as<char*>();

						// Logger::WriteMessage(key + " = " + val);
						// Logger::WriteMessage(val);
						cout << key << " = " << val;

						int x = 10;
						// const char* val = it->value().as<char*>;
					}
				}
		};
	}
}