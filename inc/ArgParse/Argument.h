/*
ArgParser - C++ Argument Parser reflecting the python module ArgParse.
Copyright (C) 2014-2015  Matthew Scott Krafczyk

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef ARGPARSE_Argument_HDR
#define ARGPARSE_Argument_HDR

#include <vector>
#include <string>
#include "ArgParse/config.h"
#include "ArgParse/ArgObject.h"

namespace ArgParse {
	class Argument : public ArgObject {
		public:
			//Parser status
			typedef int ParseStatus_t;
			static const ParseStatus_t Complete;
			static const ParseStatus_t Incomplete;
			static const ParseStatus_t OutOfRange;
			static const ParseStatus_t ParseError;

			template<class T>
			static size_t vector_length(void* data);

		public:
			Argument(const std::string& call_name, const Type_t& Type, const Mode_t& Mode, const std::string& help_text, void* arguments, const Req_t required, bool* was_defined = ARGPARSE_NULLPTR);
			virtual ~Argument();

			//Getters/Setters
			static ParseStatus_t ParseArgumentAsChar(char& val, const std::string& optarg) __attribute__((warn_unused_result));
			static ParseStatus_t ParseArgumentAsUChar(unsigned char& val, const std::string& optarg) __attribute__((warn_unused_result));
			static ParseStatus_t ParseArgumentAsShort(short& val, const std::string& optarg) __attribute__((warn_unused_result));
			static ParseStatus_t ParseArgumentAsUShort(unsigned short& val, const std::string& optarg) __attribute__((warn_unused_result));
			static ParseStatus_t ParseArgumentAsInt(int& val, const std::string& optarg) __attribute__((warn_unused_result));
			static ParseStatus_t ParseArgumentAsUInt(unsigned int& val, const std::string& optarg) __attribute__((warn_unused_result));
			static ParseStatus_t ParseArgumentAsLong(long& val, const std::string& optarg) __attribute__((warn_unused_result));
			static ParseStatus_t ParseArgumentAsULong(unsigned long& val, const std::string& optarg) __attribute__((warn_unused_result));
			static ParseStatus_t ParseArgumentAsLongLong(long long& val, const std::string& optarg) __attribute__((warn_unused_result));
			static ParseStatus_t ParseArgumentAsULongLong(unsigned long long& val, const std::string& optarg) __attribute__((warn_unused_result));
			static ParseStatus_t ParseArgumentAsFloat(float& val, const std::string& optarg) __attribute__((warn_unused_result));
			static ParseStatus_t ParseArgumentAsDouble(double& val, const std::string& optarg) __attribute__((warn_unused_result));
			static ParseStatus_t ParseArgumentAsLongDouble(long double& val, const std::string& optarg) __attribute__((warn_unused_result));
			virtual int SetValue(const std::string& optarg) __attribute__((warn_unused_result));

			static std::vector<std::string> GetCallNames(const std::string& combined_names);

			std::string GetName(size_t i=0);
			size_t GetNum() {
				return call_names.size();
			}

			//ArgObject functions
			bool IsConfigured() __attribute__((warn_unused_result));
			virtual ArgObject::Accept_t AcceptsArgument(std::string arg) __attribute__((warn_unused_result));
			virtual int PassArgument(std::string arg, std::string opt, bool with_opt) __attribute__((warn_unused_result));
			virtual size_t AmountOfData();
			bool IsReady() __attribute__((warn_unused_result));
			virtual std::string GetHelpText();
			
		private:
			bool DoesAnArgumentMatch(size_t& position, const std::string& arg) __attribute__((warn_unused_result));

			bool WasDefined() const {
				return *defined;
			}
			void SetDefined(bool status) {
				*defined = status;
			}
			Req_t IsRequired() const {
				return GetRequired();
			}

			std::vector<std::string> call_names;
			bool* defined;
			bool responsible_for_defined;
			void* value;
	};
}

#endif
