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

#ifndef ARGPARSE_ArgScalar_HDR
#define ARGPARSE_ArgScalar_HDR

#include <sstream>

#include "ArgParse/Message.h"
#include "ArgParse/Argument.h"

namespace ArgParse {
	template<class T>
	class ArgScalar : public Argument {
		public:
			ArgScalar(const std::string& call_name, const std::string& help_text, T* value, const Req_t required, bool* was_defined = ARGPARSE_NULLPTR);
			~ArgScalar() {}

			virtual int SetValue(const std::string& optarg) __attribute__((warn_unused_result));

			virtual ArgObject::Accept_t AcceptsArgument(const std::string& arg __attribute__((unused))) __attribute__((warn_unused_result));
			virtual int PassArgument(const std::string& arg, const std::string& opt, const bool with_opt) __attribute__((warn_unused_result));
			virtual size_t AmountOfData();

			virtual std::string GetHelpText();

			virtual void AppendType(std::stringstream& ss) {
				ss << "Scalar : ";
			}

			virtual ArgObject::Mode_t GetMode() const {
				return ArgObject::Single;
			}

		private:
			T* value;
	};

	template<class T>
	ArgScalar<T>::ArgScalar(const std::string& call_name, const std::string& help_text, T* value, const Req_t required, bool* was_defined) : Argument(call_name, help_text, required, was_defined) {
		this->value = value;
	}

	template<class T>
	int ArgScalar<T>::SetValue(const std::string& optarg) {
		std::stringstream ss(optarg);
		if(!(ss >> *value)) {
			ArgParseMessageError("There was an error reading values from the string stream.\n");
			return -1;
		}
		if(ss.eof()) {
			SetDefined(true);
			return 0;
		} else {
			ArgParseMessageError("String stream has some sort of error.\n");
			return -2;
		}
	}

	template<class T>
	ArgObject::Accept_t ArgScalar<T>::AcceptsArgument(const std::string& arg) {
		if(DebugLevel > 1) {
			MessageStandardPrint("Testing the argument (%s)\n", arg.c_str());
		}
		size_t pos;
		bool result = DoesAnArgumentMatch(pos, arg);
		if(!result) {
			return ArgObject::No;
		}

		return ArgObject::WithArg;
	}

	template<class T>
	int ArgScalar<T>::PassArgument(const std::string& arg, const std::string& opt, const bool with_opt) {
		size_t pos;
		bool result = DoesAnArgumentMatch(pos, arg);
		if(!result) {
			return ArgObject::NotAccepted;
		}

		if(!with_opt) {
			ArgParseMessageError("A non-boolean argument must have a value!\n");
			SetMessage("A non-boolean argument must have a value!\n");
			return ArgObject::Error;
		}

		if(SetValue(opt) < 0) {
			ArgParseMessageError("There was a problem setting the value of the option!\n");
			return ArgObject::Error;
		}
		SetDefined(true);
		return ArgObject::Accepted;
	}

	template<class T>
	size_t ArgScalar<T>::AmountOfData() {
		if(!WasDefined()) {
			return 0;
		}
		return 1;
	}

	template<class T>
	std::string ArgScalar<T>::GetHelpText() {
		return GetHelpTextWithMessage("Takes a generic type : ");
	}

	template<>
	int ArgScalar<bool>::SetValue(const std::string& optarg);

	template<>
	ArgObject::Accept_t ArgScalar<bool>::AcceptsArgument(const std::string& arg);

	template<>
	int ArgScalar<bool>::PassArgument(const std::string& arg, const std::string& opt, const bool with_opt);

	template<>
	std::string ArgScalar<bool>::GetHelpText();

	template<>
	std::string ArgScalar<std::string>::GetHelpText();

	template<>
	std::string ArgScalar<char>::GetHelpText();

	template<>
	std::string ArgScalar<unsigned char>::GetHelpText();

	template<>
	std::string ArgScalar<short>::GetHelpText();

	template<>
	std::string ArgScalar<unsigned short>::GetHelpText();

	template<>
	std::string ArgScalar<int>::GetHelpText();

	template<>
	std::string ArgScalar<unsigned int>::GetHelpText();

	template<>
	std::string ArgScalar<long>::GetHelpText();

	template<>
	std::string ArgScalar<unsigned long>::GetHelpText();

	template<>
	std::string ArgScalar<long long>::GetHelpText();

	template<>
	std::string ArgScalar<unsigned long long>::GetHelpText();

	template<>
	std::string ArgScalar<float>::GetHelpText();

	template<>
	std::string ArgScalar<double>::GetHelpText();

	template<>
	std::string ArgScalar<long double>::GetHelpText();
}

#endif
