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
			//Type management
			typedef int Type_t;
			static const Type_t Bool;
			static const Type_t Str;
			static const Type_t Char;
			static const Type_t UChar;
			static const Type_t Short;
			static const Type_t UShort;
			static const Type_t Int;
			static const Type_t UInt;
			static const Type_t Long;
			static const Type_t ULong;
			static const Type_t LongLong;
			static const Type_t ULongLong;
			static const Type_t Float;
			static const Type_t Double;
			static const Type_t LongDouble;

			//Mode management
			typedef int Mode_t;
			static const Mode_t Single;
			static const Mode_t Multiple;

			//Required management
			typedef bool Req_t;
			static const Req_t Required;
			static const Req_t Optional;

			//Parser status
			typedef int ParseStatus_t;
			static const ParseStatus_t Complete;
			static const ParseStatus_t Incomplete;
			static const ParseStatus_t OutOfRange;
			static const ParseStatus_t ParseError;

		public:
			Argument(const std::string& call_name, const std::string& help_text, bool* argument, const Req_t required = Optional, bool* was_defined = ARGPARSE_NULLPTR);
			Argument(const std::string& call_name, const std::string& help_text, std::vector<bool>* arguments, const Req_t required = Optional, bool* was_defined = ARGPARSE_NULLPTR);
			Argument(const std::string& call_name, const std::string& help_text, std::string* argument, const Req_t required = Optional, bool* was_defined = ARGPARSE_NULLPTR);
			Argument(const std::string& call_name, const std::string& help_text, std::vector<std::string>* arguments, const Req_t required = Optional, bool* was_defined = ARGPARSE_NULLPTR);
			Argument(const std::string& call_name, const std::string& help_text, char* argument, const Req_t required = Optional, bool* was_defined = ARGPARSE_NULLPTR);
			Argument(const std::string& call_name, const std::string& help_text, std::vector<char>* arguments, const Req_t required = Optional, bool* was_defined = ARGPARSE_NULLPTR);
			Argument(const std::string& call_name, const std::string& help_text, unsigned char* argument, const Req_t required = Optional, bool* was_defined = ARGPARSE_NULLPTR);
			Argument(const std::string& call_name, const std::string& help_text, std::vector<unsigned char>* arguments, const Req_t required = Optional, bool* was_defined = ARGPARSE_NULLPTR);
			Argument(const std::string& call_name, const std::string& help_text, short* argument, const Req_t required = Optional, bool* was_defined = ARGPARSE_NULLPTR);
			Argument(const std::string& call_name, const std::string& help_text, std::vector<short>* arguments, const Req_t required = Optional, bool* was_defined = ARGPARSE_NULLPTR);
			Argument(const std::string& call_name, const std::string& help_text, unsigned short* argument, const Req_t required = Optional, bool* was_defined = ARGPARSE_NULLPTR);
			Argument(const std::string& call_name, const std::string& help_text, std::vector<unsigned short>* arguments, const Req_t required = Optional, bool* was_defined = ARGPARSE_NULLPTR);
			Argument(const std::string& call_name, const std::string& help_text, int* argument, const Req_t required = Optional, bool* was_defined = ARGPARSE_NULLPTR);
			Argument(const std::string& call_name, const std::string& help_text, std::vector<int>* arguments, const Req_t required = Optional, bool* was_defined = ARGPARSE_NULLPTR);
			Argument(const std::string& call_name, const std::string& help_text, unsigned int* argument, const Req_t required = Optional, bool* was_defined = ARGPARSE_NULLPTR);
			Argument(const std::string& call_name, const std::string& help_text, std::vector<unsigned int>* arguments, const Req_t required = Optional, bool* was_defined = ARGPARSE_NULLPTR);
			Argument(const std::string& call_name, const std::string& help_text, long* argument, const Req_t required = Optional, bool* was_defined = ARGPARSE_NULLPTR);
			Argument(const std::string& call_name, const std::string& help_text, std::vector<long>* arguments, const Req_t required = Optional, bool* was_defined = ARGPARSE_NULLPTR);
			Argument(const std::string& call_name, const std::string& help_text, unsigned long* argument, const Req_t required = Optional, bool* was_defined = ARGPARSE_NULLPTR);
			Argument(const std::string& call_name, const std::string& help_text, std::vector<unsigned long>* arguments, const Req_t required = Optional, bool* was_defined = ARGPARSE_NULLPTR);
			Argument(const std::string& call_name, const std::string& help_text, long long* argument, const Req_t required = Optional, bool* was_defined = ARGPARSE_NULLPTR);
			Argument(const std::string& call_name, const std::string& help_text, std::vector<long long>* arguments, const Req_t required = Optional, bool* was_defined = ARGPARSE_NULLPTR);
			Argument(const std::string& call_name, const std::string& help_text, unsigned long long* argument, const Req_t required = Optional, bool* was_defined = ARGPARSE_NULLPTR);
			Argument(const std::string& call_name, const std::string& help_text, std::vector<unsigned long long>* arguments, const Req_t required = Optional, bool* was_defined = ARGPARSE_NULLPTR);
			Argument(const std::string& call_name, const std::string& help_text, float* argument, const Req_t required = Optional, bool* was_defined = ARGPARSE_NULLPTR);
			Argument(const std::string& call_name, const std::string& help_text, std::vector<float>* arguments, const Req_t required = Optional, bool* was_defined = ARGPARSE_NULLPTR);
			Argument(const std::string& call_name, const std::string& help_text, double* argument, const Req_t required = Optional, bool* was_defined = ARGPARSE_NULLPTR);
			Argument(const std::string& call_name, const std::string& help_text, std::vector<double>* arguments, const Req_t required = Optional, bool* was_defined = ARGPARSE_NULLPTR);
			Argument(const std::string& call_name, const std::string& help_text, long double* argument, const Req_t required = Optional, bool* was_defined = ARGPARSE_NULLPTR);
			Argument(const std::string& call_name, const std::string& help_text, std::vector<long double>* arguments, const Req_t required = Optional, bool* was_defined = ARGPARSE_NULLPTR);
			Argument(const std::string& call_name, const Type_t& Type, const Mode_t& Mode, const std::string& help_text, const Req_t required, void* arguments, bool* was_defined = ARGPARSE_NULLPTR);
			~Argument();

			//Getters/Setters
			bool IsArgument(const std::string& opt) __attribute__((warn_unused_result));
			bool NeedsArgument();
			std::string GetName(size_t i=0);
			size_t GetNum() {
				return call_names.size();
			}

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
			int SetValue(const std::string& optarg) __attribute__((warn_unused_result));

			static std::vector<std::string> GetCallNames(const std::string& combined_names);

			bool WasDefined() const {
				return *defined;
			}
			void SetDefined(bool status) {
				*defined = status;
			}
			void SetRequired(const Req_t required) {
				this->required = required;
			}
			Req_t IsRequired() const {
				return required;
			}

			//ArgObject functions
			ArgObject::Accept_t AcceptsArgument(std::string arg) __attribute__((warn_unused_result));
			int PassArgument(std::string arg, std::string opt, bool with_opt) __attribute__((warn_unused_result));
			bool IsReady() __attribute__((warn_unused_result));
			std::string GetHelpText();
			
		private:
			void InitializeArgument(const std::string& call_name, const Type_t& Type, const Mode_t& Mode, const std::string& help_text, const Req_t required, void* arguments, bool* was_defined);

			std::vector<std::string> call_names;
			Type_t type;
			Mode_t mode;
			bool required;
			bool* defined;
			bool responsible_for_defined;
			std::string help_text;
			void* value;
	};
}

#endif
