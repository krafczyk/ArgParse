#ifndef ARGPARSE_ArgVector_HDR
#define ARGPARSE_ArgVector_HDR

#include <sstream>

#include "ArgParse/Message.h"
#include "ArgParse/Argument.h"

namespace ArgParse {
	template<class T>
	class ArgVector : public Argument {
		public:
			ArgVector(const std::string& call_name, const std::string& help_text, std::vector<T>* value, const Req_t required, bool* was_defined = nullptr);
			~ArgVector() {}

			virtual int SetValue(const std::string& optarg) __attribute__((warn_unused_result));

			virtual ArgObject::Accept_t AcceptsArgument(const std::string& arg __attribute__((unused))) const __attribute__((warn_unused_result));
			virtual int PassArgument(const std::string& arg, const std::string& opt, const bool with_opt) __attribute__((warn_unused_result));
			virtual size_t AmountOfData() const;

			virtual std::string GetHelpText() const;

			virtual void AppendType(std::stringstream& ss) const {
				ss << "Vector : ";
			}

			virtual ArgObject::Mode_t GetMode() const {
				return ArgObject::Multiple;
			}

		private:
			std::vector<T>* value;
	};

	template<class T>
	ArgVector<T>::ArgVector(const std::string& call_name, const std::string& help_text, std::vector<T>* value, const Req_t required, bool* was_defined) : Argument(call_name, help_text, required, was_defined) {
		this->value = value;
	}

	template<class T>
	int ArgVector<T>::SetValue(const std::string& optarg) {
		std::stringstream ss(optarg);
		T temp_val;
		if(!(ss >> temp_val)) {
			ArgParseMessageError("There was an error reading values from the string stream.\n");
			return -1;
		}
		if(ss.eof()) {
			SetDefined(true);
			this->value->push_back(temp_val);
			return 0;
		} else {
			ArgParseMessageError("String stream has some sort of error.\n");
			return -2;
		}
	}

	template<class T>
	ArgObject::Accept_t ArgVector<T>::AcceptsArgument(const std::string& arg) const {
		if(DebugLevel > 1) {
			MessageStandardPrint("Testing the argument (%s)\n", arg.c_str());
		}
		size_t pos;
		bool result = DoesAnArgumentMatch(pos, arg);
		if(!result) {
			return ArgObject::No;
		}

		return ArgObject::WithMultipleArg;
	}

	template<class T>
	int ArgVector<T>::PassArgument(const std::string& arg, const std::string& opt, const bool with_opt) {
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
			ArgParseMessageError("There was a problem setting the value of the option! Arg(%s) Opt(%s)\n", arg.c_str(), opt.c_str());
			return ArgObject::Error;
		}
		return ArgObject::Accepted;
	}

	template<class T>
	size_t ArgVector<T>::AmountOfData() const {
		if(!WasDefined()) {
			return 0;
		}
		return this->value->size();
	}

	template<class T>
	std::string ArgVector<T>::GetHelpText() const {
		return GetHelpTextWithMessage("Takes a generic type : ");
	}

	template<>
	int ArgVector<bool>::SetValue(const std::string& optarg);

	template<>
	ArgObject::Accept_t ArgVector<bool>::AcceptsArgument(const std::string& arg) const;

	template<>
	int ArgVector<bool>::PassArgument(const std::string& arg, const std::string& opt, const bool with_opt);

	template<>
	std::string ArgVector<bool>::GetHelpText() const;

	template<>
	std::string ArgVector<std::string>::GetHelpText() const;

	template<>
	std::string ArgVector<char>::GetHelpText() const;

	template<>
	std::string ArgVector<unsigned char>::GetHelpText() const;

	template<>
	std::string ArgVector<short>::GetHelpText() const;

	template<>
	std::string ArgVector<unsigned short>::GetHelpText() const;

	template<>
	std::string ArgVector<int>::GetHelpText() const;

	template<>
	std::string ArgVector<unsigned int>::GetHelpText() const;

	template<>
	std::string ArgVector<long>::GetHelpText() const;

	template<>
	std::string ArgVector<unsigned long>::GetHelpText() const;

	template<>
	std::string ArgVector<long long>::GetHelpText() const;

	template<>
	std::string ArgVector<unsigned long long>::GetHelpText() const;

	template<>
	std::string ArgVector<float>::GetHelpText() const;

	template<>
	std::string ArgVector<double>::GetHelpText() const;

	template<>
	std::string ArgVector<long double>::GetHelpText() const;
}

#endif
