#include "ArgParse/Message.h"
#include "ArgParse/ArgObjContainer.h"

namespace ArgParse {
	ArgObjContainer::~ArgObjContainer() {
		for(size_t i=0;i<objects.size();++i) {
			delete objects[i];
		}
	}

	void ArgObjContainer::AddArgument(const std::string& call_name, const std::string& help_text, bool* argument, const Argument::Req_t required, bool* was_defined) {
		Argument* the_argument = new Argument(call_name, Argument::Bool, Argument::Single, help_text, (void*) argument, required, was_defined);
		AddArgument(the_argument);
	}

	void ArgObjContainer::AddArgument(const std::string& call_name, const std::string& help_text, std::vector<bool>* arguments, const Argument::Req_t required, bool* was_defined) {
		Argument* the_argument = new Argument(call_name, Argument::Bool, Argument::Multiple, help_text, (void*) arguments, required, was_defined);
		AddArgument(the_argument);
	}

	void ArgObjContainer::AddArgument(const std::string& call_name, const std::string& help_text, std::string* argument, const Argument::Req_t required, bool* was_defined) {
		Argument* the_argument = new Argument(call_name, Argument::Str, Argument::Single, help_text, (void*) argument, required, was_defined);
		AddArgument(the_argument);
	}

	void ArgObjContainer::AddArgument(const std::string& call_name, const std::string& help_text, std::vector<std::string>* arguments, const Argument::Req_t required, bool* was_defined) {
		Argument* the_argument = new Argument(call_name, Argument::Str, Argument::Multiple, help_text, (void*) arguments, required, was_defined);
		AddArgument(the_argument);
	}

	void ArgObjContainer::AddArgument(const std::string& call_name, const std::string& help_text, char* argument, const Argument::Req_t required, bool* was_defined) {
		Argument* the_argument = new Argument(call_name, Argument::Char, Argument::Single, help_text, (void*) argument, required, was_defined);
		AddArgument(the_argument);
	}

	void ArgObjContainer::AddArgument(const std::string& call_name, const std::string& help_text, std::vector<char>* arguments, const Argument::Req_t required, bool* was_defined) {
		Argument* the_argument = new Argument(call_name, Argument::Char, Argument::Multiple, help_text, (void*) arguments, required, was_defined);
		AddArgument(the_argument);
	}

	void ArgObjContainer::AddArgument(const std::string& call_name, const std::string& help_text, unsigned char* argument, const Argument::Req_t required, bool* was_defined) {
		Argument* the_argument = new Argument(call_name, Argument::UChar, Argument::Single, help_text, (void*) argument, required, was_defined);
		AddArgument(the_argument);
	}

	void ArgObjContainer::AddArgument(const std::string& call_name, const std::string& help_text, std::vector<unsigned char>* arguments, const Argument::Req_t required, bool* was_defined) {
		Argument* the_argument = new Argument(call_name, Argument::UChar, Argument::Multiple, help_text, (void*) arguments, required, was_defined);
		AddArgument(the_argument);
	}

	void ArgObjContainer::AddArgument(const std::string& call_name, const std::string& help_text, short* argument, const Argument::Req_t required, bool* was_defined) {
		Argument* the_argument = new Argument(call_name, Argument::Short, Argument::Single, help_text, (void*) argument, required, was_defined);
		AddArgument(the_argument);
	}

	void ArgObjContainer::AddArgument(const std::string& call_name, const std::string& help_text, std::vector<short>* arguments, const Argument::Req_t required, bool* was_defined) {
		Argument* the_argument = new Argument(call_name, Argument::Short, Argument::Multiple, help_text, (void*) arguments, required, was_defined);
		AddArgument(the_argument);
	}

	void ArgObjContainer::AddArgument(const std::string& call_name, const std::string& help_text, unsigned short* argument, const Argument::Req_t required, bool* was_defined) {
		Argument* the_argument = new Argument(call_name, Argument::UShort, Argument::Single, help_text, (void*) argument, required, was_defined);
		AddArgument(the_argument);
	}

	void ArgObjContainer::AddArgument(const std::string& call_name, const std::string& help_text, std::vector<unsigned short>* arguments, const Argument::Req_t required, bool* was_defined) {
		Argument* the_argument = new Argument(call_name, Argument::UShort, Argument::Multiple, help_text, (void*) arguments, required, was_defined);
		AddArgument(the_argument);
	}

	void ArgObjContainer::AddArgument(const std::string& call_name, const std::string& help_text, int* argument, const Argument::Req_t required, bool* was_defined) {
		Argument* the_argument = new Argument(call_name, Argument::Int, Argument::Single, help_text, (void*) argument, required, was_defined);
		AddArgument(the_argument);
	}

	void ArgObjContainer::AddArgument(const std::string& call_name, const std::string& help_text, std::vector<int>* arguments, const Argument::Req_t required, bool* was_defined) {
		Argument* the_argument = new Argument(call_name, Argument::Int, Argument::Multiple, help_text, (void*) arguments, required, was_defined);
		AddArgument(the_argument);
	}

	void ArgObjContainer::AddArgument(const std::string& call_name, const std::string& help_text, unsigned int* argument, const Argument::Req_t required, bool* was_defined) {
		Argument* the_argument = new Argument(call_name, Argument::UInt, Argument::Single, help_text, (void*) argument, required, was_defined);
		AddArgument(the_argument);
	}

	void ArgObjContainer::AddArgument(const std::string& call_name, const std::string& help_text, std::vector<unsigned int>* arguments, const Argument::Req_t required, bool* was_defined) {
		Argument* the_argument = new Argument(call_name, Argument::UInt, Argument::Multiple, help_text, (void*) arguments, required, was_defined);
		AddArgument(the_argument);
	}

	void ArgObjContainer::AddArgument(const std::string& call_name, const std::string& help_text, long* argument, const Argument::Req_t required, bool* was_defined) {
		Argument* the_argument = new Argument(call_name, Argument::Long, Argument::Single, help_text, (void*) argument, required, was_defined);
		AddArgument(the_argument);
	}

	void ArgObjContainer::AddArgument(const std::string& call_name, const std::string& help_text, std::vector<long>* arguments, const Argument::Req_t required, bool* was_defined) {
		Argument* the_argument = new Argument(call_name, Argument::Long, Argument::Multiple, help_text, (void*) arguments, required, was_defined);
		AddArgument(the_argument);
	}

	void ArgObjContainer::AddArgument(const std::string& call_name, const std::string& help_text, unsigned long* argument, const Argument::Req_t required, bool* was_defined) {
		Argument* the_argument = new Argument(call_name, Argument::ULong, Argument::Single, help_text, (void*) argument, required, was_defined);
		AddArgument(the_argument);
	}

	void ArgObjContainer::AddArgument(const std::string& call_name, const std::string& help_text, std::vector<unsigned long>* arguments, const Argument::Req_t required, bool* was_defined) {
		Argument* the_argument = new Argument(call_name, Argument::ULong, Argument::Multiple, help_text, (void*) arguments, required, was_defined);
		AddArgument(the_argument);
	}

	void ArgObjContainer::AddArgument(const std::string& call_name, const std::string& help_text, long long* argument, const Argument::Req_t required, bool* was_defined) {
		Argument* the_argument = new Argument(call_name, Argument::LongLong, Argument::Single, help_text, (void*) argument, required, was_defined);
		AddArgument(the_argument);
	}

	void ArgObjContainer::AddArgument(const std::string& call_name, const std::string& help_text, std::vector<long long>* arguments, const Argument::Req_t required, bool* was_defined) {
		Argument* the_argument = new Argument(call_name, Argument::LongLong, Argument::Multiple, help_text, (void*) arguments, required, was_defined);
		AddArgument(the_argument);
	}

	void ArgObjContainer::AddArgument(const std::string& call_name, const std::string& help_text, unsigned long long* argument, const Argument::Req_t required, bool* was_defined) {
		Argument* the_argument = new Argument(call_name, Argument::ULongLong, Argument::Single, help_text, (void*) argument, required, was_defined);
		AddArgument(the_argument);
	}

	void ArgObjContainer::AddArgument(const std::string& call_name, const std::string& help_text, std::vector<unsigned long long>* arguments, const Argument::Req_t required, bool* was_defined) {
		Argument* the_argument = new Argument(call_name, Argument::ULongLong, Argument::Multiple, help_text, (void*) arguments, required, was_defined);
		AddArgument(the_argument);
	}

	void ArgObjContainer::AddArgument(const std::string& call_name, const std::string& help_text, float* argument, const Argument::Req_t required, bool* was_defined) {
		Argument* the_argument = new Argument(call_name, Argument::Float, Argument::Single, help_text, (void*) argument, required, was_defined);
		AddArgument(the_argument);
	}

	void ArgObjContainer::AddArgument(const std::string& call_name, const std::string& help_text, std::vector<float>* arguments, const Argument::Req_t required, bool* was_defined) {
		Argument* the_argument = new Argument(call_name, Argument::Float, Argument::Multiple, help_text, (void*) arguments, required, was_defined);
		AddArgument(the_argument);
	}

	void ArgObjContainer::AddArgument(const std::string& call_name, const std::string& help_text, double* argument, const Argument::Req_t required, bool* was_defined) {
		Argument* the_argument = new Argument(call_name, Argument::Double, Argument::Single, help_text, (void*) argument, required, was_defined);
		AddArgument(the_argument);
	}

	void ArgObjContainer::AddArgument(const std::string& call_name, const std::string& help_text, std::vector<double>* arguments, const Argument::Req_t required, bool* was_defined) {
		Argument* the_argument = new Argument(call_name, Argument::Double, Argument::Multiple, help_text, (void*) arguments, required, was_defined);
		AddArgument(the_argument);
	}
	
	void ArgObjContainer::AddArgument(const std::string& call_name, const std::string& help_text, long double* argument, const Argument::Req_t required, bool* was_defined) {
		Argument* the_argument = new Argument(call_name, Argument::LongDouble, Argument::Single, help_text, (void*) argument, required, was_defined);
		AddArgument(the_argument);
	}

	void ArgObjContainer::AddArgument(const std::string& call_name, const std::string& help_text, std::vector<long double>* arguments, const Argument::Req_t required, bool* was_defined) {
		Argument* the_argument = new Argument(call_name, Argument::LongDouble, Argument::Multiple, help_text, (void*) arguments, required, was_defined);
		AddArgument(the_argument);
	}

	void ArgObjContainer::CheckName(const std::string& call_name, ArgObjContainer* parent) {
		if(parent == ARGPARSE_NULLPTR) {
			for(size_t i=0;i<objects.size();++i) {
				if(objects[i]->AcceptsArgument(call_name) != ArgObject::No) {
					ArgParseMessageError("The argument (%s) has already been defined!\n", call_name.c_str());
					SetMessage("The argument (%s) has already been defined!\n", call_name.c_str());
					exit(-1);
				}
			}
		} else {
			parent->CheckName(call_name, parent->parent);
		}
	}

	void ArgObjContainer::AddArgument(Argument* argument) {
		//Check that the name hasn't been defined already
		for(size_t i=0; i<argument->GetNum(); ++i) {
			CheckName(argument->GetName(i));
		}
		AddArgObject((ArgObject*) argument);
	}

	void ArgObjContainer::AddArgObject(ArgObject* object) {
		objects.push_back(object);
	}
}
