/*
ArgParser - C++ Argument Parser reflecting the python module ArgParse.
Copyright (C) 2014-2017  Matthew Scott Krafczyk

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

#include "ArgParse/ArgScalar.h"

namespace ArgParse {
	template<>
	int ArgScalar<bool>::SetValue(const std::string& optarg) {
		if (optarg != "") {
			ArgParseMessageError("Trying to set the value of a bool with a non-empty string!\n");
			return -1;
		}
		*value = true;
		SetDefined(true);
		return 0;
	}

	template<>
	ArgObject::Accept_t ArgScalar<bool>::AcceptsArgument(const std::string& arg) const {
		if(DebugLevel > 1) {
			MessageStandardPrint("Testing the argument (%s)\n", arg.c_str());
		}
		size_t pos;
		bool result = DoesAnArgumentMatch(pos, arg);
		if(!result) {
			return ArgObject::No;
		}

		return ArgObject::WithoutArg;
	}

	template<>
	int ArgScalar<bool>::PassArgument(const std::string& arg, const std::string& opt, const bool with_opt) {
		size_t pos;
		bool result = DoesAnArgumentMatch(pos, arg);
		if(!result) {
			return ArgObject::NotAccepted;
		}

		if(with_opt) {
			ArgParseMessageError("A boolean argument cannot accept a value!\n");
			SetMessage("A boolean argument cannot accept a value!\n");
			return ArgObject::Error;
		}

		if(opt.size() != 0) {
			ArgParseMessageError("You told me you didn't pass an option, but you did!\n");
			SetMessage("You told me you didn't pass an option, but you did!\n");
			return ArgObject::Error;
		}

		if(SetValue("") < 0) {
			return ArgObject::Error;
		}
		return ArgObject::Accepted;
	}

	template<>
	std::string ArgScalar<bool>::GetHelpText() const {
		return GetHelpTextWithMessage("Takes no argument : ");
	}

	template<>
	std::string ArgScalar<std::string>::GetHelpText() const {
		return GetHelpTextWithMessage("Takes a string : ");
	}

	template<>
	std::string ArgScalar<char>::GetHelpText() const {
		return GetHelpTextWithMessage("Takes a character : ");
	}

	template<>
	std::string ArgScalar<unsigned char>::GetHelpText() const {
		return GetHelpTextWithMessage("Takes an unsigned character : ");
	}

	template<>
	std::string ArgScalar<short>::GetHelpText() const {
		return GetHelpTextWithMessage("Takes a short : ");
	}

	template<>
	std::string ArgScalar<unsigned short>::GetHelpText() const {
		return GetHelpTextWithMessage("Takes an unsigned short : ");
	}

	template<>
	std::string ArgScalar<int>::GetHelpText() const {
		return GetHelpTextWithMessage("Takes an integer : ");
	}

	template<>
	std::string ArgScalar<unsigned int>::GetHelpText() const {
		return GetHelpTextWithMessage("Takes an unsigned integer : ");
	}

	template<>
	std::string ArgScalar<long>::GetHelpText() const {
		return GetHelpTextWithMessage("Takes a long : ");
	}

	template<>
	std::string ArgScalar<unsigned long>::GetHelpText() const {
		return GetHelpTextWithMessage("Takes an unsigned long : ");
	}

	template<>
	std::string ArgScalar<long long>::GetHelpText() const {
		return GetHelpTextWithMessage("Takes a long long : ");
	}

	template<>
	std::string ArgScalar<unsigned long long>::GetHelpText() const {
		return GetHelpTextWithMessage("Takes an unsigned long long : ");
	}

	template<>
	std::string ArgScalar<float>::GetHelpText() const {
		return GetHelpTextWithMessage("Takes a float : ");
	}

	template<>
	std::string ArgScalar<double>::GetHelpText() const {
		return GetHelpTextWithMessage("Takes a double : ");
	}

	template<>
	std::string ArgScalar<long double>::GetHelpText() const {
		return GetHelpTextWithMessage("Takes a long double : ");
	}
}
