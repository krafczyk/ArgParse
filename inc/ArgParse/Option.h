/*
ArgParser - C++ Argument Parser reflecting the python module ArgParse.
Copyright (C) 2014  Matthew Scott Krafczyk

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

#ifndef ARGPARSE_Option_HDR
#define ARGPARSE_Option_HDR

#include <vector>
#include <string>
#include "ArgParse/config.h"

namespace ArgParse {
	class Option {
		public:
			//Type management
			typedef int Type_t;
			static const Type_t Bool;
			static const Type_t Str;
			static const Type_t Short;
			static const Type_t UShort;
			static const Type_t Int;
			static const Type_t UInt;
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
			Option(const std::string& call_name, const std::string& help_text, bool* option, const Req_t required = Optional, bool* was_defined = ARGPARSE_NULLPTR);
			Option(const std::string& call_name, const std::string& help_text, std::vector<bool>* options, const Req_t required = Optional, bool* was_defined = ARGPARSE_NULLPTR);
			Option(const std::string& call_name, const std::string& help_text, std::string* option, const Req_t required = Optional, bool* was_defined = ARGPARSE_NULLPTR);
			Option(const std::string& call_name, const std::string& help_text, std::vector<std::string>* options, const Req_t required = Optional, bool* was_defined = ARGPARSE_NULLPTR);
			Option(const std::string& call_name, const std::string& help_text, short* option, const Req_t required = Optional, bool* was_defined = ARGPARSE_NULLPTR);
			Option(const std::string& call_name, const std::string& help_text, std::vector<short>* options, const Req_t required = Optional, bool* was_defined = ARGPARSE_NULLPTR);
			Option(const std::string& call_name, const std::string& help_text, unsigned short* option, const Req_t required = Optional, bool* was_defined = ARGPARSE_NULLPTR);
			Option(const std::string& call_name, const std::string& help_text, std::vector<unsigned short>* options, const Req_t required = Optional, bool* was_defined = ARGPARSE_NULLPTR);
			Option(const std::string& call_name, const std::string& help_text, int* option, const Req_t required = Optional, bool* was_defined = ARGPARSE_NULLPTR);
			Option(const std::string& call_name, const std::string& help_text, std::vector<int>* options, const Req_t required = Optional, bool* was_defined = ARGPARSE_NULLPTR);
			Option(const std::string& call_name, const std::string& help_text, unsigned int* option, const Req_t required = Optional, bool* was_defined = ARGPARSE_NULLPTR);
			Option(const std::string& call_name, const std::string& help_text, std::vector<unsigned int>* options, const Req_t required = Optional, bool* was_defined = ARGPARSE_NULLPTR);
			Option(const std::string& call_name, const std::string& help_text, float* option, const Req_t required = Optional, bool* was_defined = ARGPARSE_NULLPTR);
			Option(const std::string& call_name, const std::string& help_text, std::vector<float>* options, const Req_t required = Optional, bool* was_defined = ARGPARSE_NULLPTR);
			Option(const std::string& call_name, const std::string& help_text, double* option, const Req_t required = Optional, bool* was_defined = ARGPARSE_NULLPTR);
			Option(const std::string& call_name, const std::string& help_text, std::vector<double>* options, const Req_t required = Optional, bool* was_defined = ARGPARSE_NULLPTR);
			Option(const std::string& call_name, const std::string& help_text, long double* option, const Req_t required = Optional, bool* was_defined = ARGPARSE_NULLPTR);
			Option(const std::string& call_name, const std::string& help_text, std::vector<long double>* options, const Req_t required = Optional, bool* was_defined = ARGPARSE_NULLPTR);
			Option(const std::string& call_name, const Type_t& Type, const Mode_t& Mode, const std::string& help_text, const Req_t required, void* options, bool* was_defined = ARGPARSE_NULLPTR);

			//Getters/Setters
			std::string GetHelpText();

			bool IsOption(const char* opt) __attribute__((warn_unused_result));
			bool NeedsArgument();
			std::string GetName(size_t i=0);
			size_t GetNum() {
				return call_names.size();
			}

			static ParseStatus_t ParseArgumentAsShort(short& val, const char* optarg) __attribute__((warn_unused_result));
			static ParseStatus_t ParseArgumentAsUShort(unsigned short& val, const char* optarg) __attribute__((warn_unused_result));
			static ParseStatus_t ParseArgumentAsInt(int& val, const char* optarg) __attribute__((warn_unused_result));
			static ParseStatus_t ParseArgumentAsUInt(unsigned int& val, const char* optarg) __attribute__((warn_unused_result));
			static ParseStatus_t ParseArgumentAsFloat(float& val, const char* optarg) __attribute__((warn_unused_result));
			static ParseStatus_t ParseArgumentAsDouble(double& val, const char* optarg) __attribute__((warn_unused_result));
			static ParseStatus_t ParseArgumentAsLongDouble(long double& val, const char* optarg) __attribute__((warn_unused_result));
			int SetValue(const char* optarg) __attribute__((warn_unused_result));

			static std::vector<std::string> GetCallNames(const std::string& combined_names);

			bool WasDefined() const {
				if(defined != ARGPARSE_NULLPTR) {
					return *defined;
				} else {
					return false;
				}
			}
			void SetDefined(bool status) {
				if(defined != ARGPARSE_NULLPTR) {
					*defined = status;
				}
			}
			void SetRequired(const Req_t required) {
				this->required = required;
			}
			Req_t IsRequired() const {
				return required;
			}
			
		private:
			void InitializeOption(const std::string& call_name, const Type_t& Type, const Mode_t& Mode, const std::string& help_text, const Req_t required, void* options, bool* was_defined);

			std::vector<std::string> call_names;
			Type_t type;
			Mode_t mode;
			bool required;
			bool* defined;
			std::string help_text;
			void* value;
	};
}

#endif
