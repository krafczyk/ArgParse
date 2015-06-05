#include "ArgParse/Message.h"
#include "ArgParse/ArgObjContainer.h"

namespace ArgParse {
	ArgObjContainer::~ArgObjContainer() {
		for(size_t i=0;i<objects.size();++i) {
			delete objects[i];
		}
	}

	void ArgObjContainer::AddArgument(const std::string& call_name, const std::string& help_text, bool* argument, const ArgObject::Req_t required, bool* was_defined) {
		Argument* the_argument = new Argument(call_name, ArgObject::Bool, ArgObject::Single, help_text, (void*) argument, required, was_defined);
		AddArgument(the_argument);
	}

	void ArgObjContainer::AddArgument(const std::string& call_name, const std::string& help_text, std::vector<bool>* arguments, const ArgObject::Req_t required, bool* was_defined) {
		Argument* the_argument = new Argument(call_name, ArgObject::Bool, ArgObject::Multiple, help_text, (void*) arguments, required, was_defined);
		AddArgument(the_argument);
	}

	void ArgObjContainer::AddArgument(const std::string& call_name, const std::string& help_text, std::string* argument, const ArgObject::Req_t required, bool* was_defined) {
		Argument* the_argument = new Argument(call_name, ArgObject::Str, ArgObject::Single, help_text, (void*) argument, required, was_defined);
		AddArgument(the_argument);
	}

	void ArgObjContainer::AddArgument(const std::string& call_name, const std::string& help_text, std::vector<std::string>* arguments, const ArgObject::Req_t required, bool* was_defined) {
		Argument* the_argument = new Argument(call_name, ArgObject::Str, ArgObject::Multiple, help_text, (void*) arguments, required, was_defined);
		AddArgument(the_argument);
	}

	void ArgObjContainer::AddArgument(const std::string& call_name, const std::string& help_text, char* argument, const ArgObject::Req_t required, bool* was_defined) {
		Argument* the_argument = new Argument(call_name, ArgObject::Char, ArgObject::Single, help_text, (void*) argument, required, was_defined);
		AddArgument(the_argument);
	}

	void ArgObjContainer::AddArgument(const std::string& call_name, const std::string& help_text, std::vector<char>* arguments, const ArgObject::Req_t required, bool* was_defined) {
		Argument* the_argument = new Argument(call_name, ArgObject::Char, ArgObject::Multiple, help_text, (void*) arguments, required, was_defined);
		AddArgument(the_argument);
	}

	void ArgObjContainer::AddArgument(const std::string& call_name, const std::string& help_text, unsigned char* argument, const ArgObject::Req_t required, bool* was_defined) {
		Argument* the_argument = new Argument(call_name, ArgObject::UChar, ArgObject::Single, help_text, (void*) argument, required, was_defined);
		AddArgument(the_argument);
	}

	void ArgObjContainer::AddArgument(const std::string& call_name, const std::string& help_text, std::vector<unsigned char>* arguments, const ArgObject::Req_t required, bool* was_defined) {
		Argument* the_argument = new Argument(call_name, ArgObject::UChar, ArgObject::Multiple, help_text, (void*) arguments, required, was_defined);
		AddArgument(the_argument);
	}

	void ArgObjContainer::AddArgument(const std::string& call_name, const std::string& help_text, short* argument, const ArgObject::Req_t required, bool* was_defined) {
		Argument* the_argument = new Argument(call_name, ArgObject::Short, ArgObject::Single, help_text, (void*) argument, required, was_defined);
		AddArgument(the_argument);
	}

	void ArgObjContainer::AddArgument(const std::string& call_name, const std::string& help_text, std::vector<short>* arguments, const ArgObject::Req_t required, bool* was_defined) {
		Argument* the_argument = new Argument(call_name, ArgObject::Short, ArgObject::Multiple, help_text, (void*) arguments, required, was_defined);
		AddArgument(the_argument);
	}

	void ArgObjContainer::AddArgument(const std::string& call_name, const std::string& help_text, unsigned short* argument, const ArgObject::Req_t required, bool* was_defined) {
		Argument* the_argument = new Argument(call_name, ArgObject::UShort, ArgObject::Single, help_text, (void*) argument, required, was_defined);
		AddArgument(the_argument);
	}

	void ArgObjContainer::AddArgument(const std::string& call_name, const std::string& help_text, std::vector<unsigned short>* arguments, const ArgObject::Req_t required, bool* was_defined) {
		Argument* the_argument = new Argument(call_name, ArgObject::UShort, ArgObject::Multiple, help_text, (void*) arguments, required, was_defined);
		AddArgument(the_argument);
	}

	void ArgObjContainer::AddArgument(const std::string& call_name, const std::string& help_text, int* argument, const ArgObject::Req_t required, bool* was_defined) {
		Argument* the_argument = new Argument(call_name, ArgObject::Int, ArgObject::Single, help_text, (void*) argument, required, was_defined);
		AddArgument(the_argument);
	}

	void ArgObjContainer::AddArgument(const std::string& call_name, const std::string& help_text, std::vector<int>* arguments, const ArgObject::Req_t required, bool* was_defined) {
		Argument* the_argument = new Argument(call_name, ArgObject::Int, ArgObject::Multiple, help_text, (void*) arguments, required, was_defined);
		AddArgument(the_argument);
	}

	void ArgObjContainer::AddArgument(const std::string& call_name, const std::string& help_text, unsigned int* argument, const ArgObject::Req_t required, bool* was_defined) {
		Argument* the_argument = new Argument(call_name, ArgObject::UInt, ArgObject::Single, help_text, (void*) argument, required, was_defined);
		AddArgument(the_argument);
	}

	void ArgObjContainer::AddArgument(const std::string& call_name, const std::string& help_text, std::vector<unsigned int>* arguments, const ArgObject::Req_t required, bool* was_defined) {
		Argument* the_argument = new Argument(call_name, ArgObject::UInt, ArgObject::Multiple, help_text, (void*) arguments, required, was_defined);
		AddArgument(the_argument);
	}

	void ArgObjContainer::AddArgument(const std::string& call_name, const std::string& help_text, long* argument, const ArgObject::Req_t required, bool* was_defined) {
		Argument* the_argument = new Argument(call_name, ArgObject::Long, ArgObject::Single, help_text, (void*) argument, required, was_defined);
		AddArgument(the_argument);
	}

	void ArgObjContainer::AddArgument(const std::string& call_name, const std::string& help_text, std::vector<long>* arguments, const ArgObject::Req_t required, bool* was_defined) {
		Argument* the_argument = new Argument(call_name, ArgObject::Long, ArgObject::Multiple, help_text, (void*) arguments, required, was_defined);
		AddArgument(the_argument);
	}

	void ArgObjContainer::AddArgument(const std::string& call_name, const std::string& help_text, unsigned long* argument, const ArgObject::Req_t required, bool* was_defined) {
		Argument* the_argument = new Argument(call_name, ArgObject::ULong, ArgObject::Single, help_text, (void*) argument, required, was_defined);
		AddArgument(the_argument);
	}

	void ArgObjContainer::AddArgument(const std::string& call_name, const std::string& help_text, std::vector<unsigned long>* arguments, const ArgObject::Req_t required, bool* was_defined) {
		Argument* the_argument = new Argument(call_name, ArgObject::ULong, ArgObject::Multiple, help_text, (void*) arguments, required, was_defined);
		AddArgument(the_argument);
	}

	void ArgObjContainer::AddArgument(const std::string& call_name, const std::string& help_text, long long* argument, const ArgObject::Req_t required, bool* was_defined) {
		Argument* the_argument = new Argument(call_name, ArgObject::LongLong, ArgObject::Single, help_text, (void*) argument, required, was_defined);
		AddArgument(the_argument);
	}

	void ArgObjContainer::AddArgument(const std::string& call_name, const std::string& help_text, std::vector<long long>* arguments, const ArgObject::Req_t required, bool* was_defined) {
		Argument* the_argument = new Argument(call_name, ArgObject::LongLong, ArgObject::Multiple, help_text, (void*) arguments, required, was_defined);
		AddArgument(the_argument);
	}

	void ArgObjContainer::AddArgument(const std::string& call_name, const std::string& help_text, unsigned long long* argument, const ArgObject::Req_t required, bool* was_defined) {
		Argument* the_argument = new Argument(call_name, ArgObject::ULongLong, ArgObject::Single, help_text, (void*) argument, required, was_defined);
		AddArgument(the_argument);
	}

	void ArgObjContainer::AddArgument(const std::string& call_name, const std::string& help_text, std::vector<unsigned long long>* arguments, const ArgObject::Req_t required, bool* was_defined) {
		Argument* the_argument = new Argument(call_name, ArgObject::ULongLong, ArgObject::Multiple, help_text, (void*) arguments, required, was_defined);
		AddArgument(the_argument);
	}

	void ArgObjContainer::AddArgument(const std::string& call_name, const std::string& help_text, float* argument, const ArgObject::Req_t required, bool* was_defined) {
		Argument* the_argument = new Argument(call_name, ArgObject::Float, ArgObject::Single, help_text, (void*) argument, required, was_defined);
		AddArgument(the_argument);
	}

	void ArgObjContainer::AddArgument(const std::string& call_name, const std::string& help_text, std::vector<float>* arguments, const ArgObject::Req_t required, bool* was_defined) {
		Argument* the_argument = new Argument(call_name, ArgObject::Float, ArgObject::Multiple, help_text, (void*) arguments, required, was_defined);
		AddArgument(the_argument);
	}

	void ArgObjContainer::AddArgument(const std::string& call_name, const std::string& help_text, double* argument, const ArgObject::Req_t required, bool* was_defined) {
		Argument* the_argument = new Argument(call_name, ArgObject::Double, ArgObject::Single, help_text, (void*) argument, required, was_defined);
		AddArgument(the_argument);
	}

	void ArgObjContainer::AddArgument(const std::string& call_name, const std::string& help_text, std::vector<double>* arguments, const ArgObject::Req_t required, bool* was_defined) {
		Argument* the_argument = new Argument(call_name, ArgObject::Double, ArgObject::Multiple, help_text, (void*) arguments, required, was_defined);
		AddArgument(the_argument);
	}
	
	void ArgObjContainer::AddArgument(const std::string& call_name, const std::string& help_text, long double* argument, const ArgObject::Req_t required, bool* was_defined) {
		Argument* the_argument = new Argument(call_name, ArgObject::LongDouble, ArgObject::Single, help_text, (void*) argument, required, was_defined);
		AddArgument(the_argument);
	}

	void ArgObjContainer::AddArgument(const std::string& call_name, const std::string& help_text, std::vector<long double>* arguments, const ArgObject::Req_t required, bool* was_defined) {
		Argument* the_argument = new Argument(call_name, ArgObject::LongDouble, ArgObject::Multiple, help_text, (void*) arguments, required, was_defined);
		AddArgument(the_argument);
	}

	void ArgObjContainer::CheckName(const std::string& call_name, ArgObjContainer* parent) {
		if(parent == ARGPARSE_NULLPTR) {
			for(size_t i=0;i<objects.size();++i) {
				ArgObject::Accept_t accept = objects[i]->AcceptsArgument(call_name);
				if(accept != ArgObject::No) {
					if(accept == ArgObject::GroupName) {
						ArgParseMessageError("The argument (%s) conflicts with a group name!\n", call_name.c_str());
						SetMessage("The argument (%s) conflicts with a group name!\n", call_name.c_str());
					} else {
						ArgParseMessageError("The argument (%s) has already been defined!\n", call_name.c_str());
						SetMessage("The argument (%s) has already been defined!\n", call_name.c_str());
					}
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
			CheckName(argument->GetName(i), parent);
		}
		AddArgObject((ArgObject*) argument);
	}

	void ArgObjContainer::AddArgObject(ArgObject* object) {
		objects.push_back(object);
	}
}
