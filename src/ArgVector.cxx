#include "ArgParse/ArgVector.h"

namespace ArgParse {
	template<>
	int ArgVector<bool>::SetValue(const std::string& optarg) {
		if (optarg != "") {
			ArgParseMessageError("Trying to set the value of a bool with a non-empty string!\n");
			return -1;
		}
		value->push_back(true);
		SetDefined(true);
		return 0;
	}

	template<>
	ArgObject::Accept_t ArgVector<bool>::AcceptsArgument(const std::string& arg) {
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
	int ArgVector<bool>::PassArgument(const std::string& arg, const std::string& opt, const bool with_opt) {
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
	std::string ArgVector<bool>::GetHelpText() {
		return GetHelpTextWithMessage("Takes no argument : ");
	}

	template<>
	std::string ArgVector<std::string>::GetHelpText() {
		return GetHelpTextWithMessage("Takes a string : ");
	}

	template<>
	std::string ArgVector<char>::GetHelpText() {
		return GetHelpTextWithMessage("Takes a character : ");
	}

	template<>
	std::string ArgVector<unsigned char>::GetHelpText() {
		return GetHelpTextWithMessage("Takes an unsigned character : ");
	}

	template<>
	std::string ArgVector<short>::GetHelpText() {
		return GetHelpTextWithMessage("Takes a short : ");
	}

	template<>
	std::string ArgVector<unsigned short>::GetHelpText() {
		return GetHelpTextWithMessage("Takes an unsigned short : ");
	}

	template<>
	std::string ArgVector<int>::GetHelpText() {
		return GetHelpTextWithMessage("Takes an integer : ");
	}

	template<>
	std::string ArgVector<unsigned int>::GetHelpText() {
		return GetHelpTextWithMessage("Takes an unsigned integer : ");
	}

	template<>
	std::string ArgVector<long>::GetHelpText() {
		return GetHelpTextWithMessage("Takes a long : ");
	}

	template<>
	std::string ArgVector<unsigned long>::GetHelpText() {
		return GetHelpTextWithMessage("Takes an unsigned long : ");
	}

	template<>
	std::string ArgVector<long long>::GetHelpText() {
		return GetHelpTextWithMessage("Takes a long long : ");
	}

	template<>
	std::string ArgVector<unsigned long long>::GetHelpText() {
		return GetHelpTextWithMessage("Takes an unsigned long long : ");
	}

	template<>
	std::string ArgVector<float>::GetHelpText() {
		return GetHelpTextWithMessage("Takes a float : ");
	}

	template<>
	std::string ArgVector<double>::GetHelpText() {
		return GetHelpTextWithMessage("Takes a double : ");
	}

	template<>
	std::string ArgVector<long double>::GetHelpText() {
		return GetHelpTextWithMessage("Takes a long double : ");
	}
}
