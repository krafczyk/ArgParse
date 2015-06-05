#include "ArgParse/ArgObjContainer.h"

namespace ArgParse {
	ArgObjContainer::~ArgObjContainer() {
		for(size_t i=0;i<objects.size();++i) {
			delete objects[i];
		}
	}

	void ArgObjContainer::AddArgument(const std::string& call_name, const std::string& help_text, bool* argument, const Argument::Req_t required, bool* was_defined) {
		Argument* the_argument = new Argument(call_name, help_text, argument, required, was_defined);
		AddArgObject((ArgObject*) the_argument);
	}

	void ArgObjContainer::AddArgument(const std::string& call_name, const std::string& help_text, std::vector<bool>* arguments, const Argument::Req_t required, bool* was_defined) {
		Argument* the_argument = new Argument(call_name, help_text, arguments, required, was_defined);
		AddArgObject((ArgObject*) the_argument);
	}

	void ArgObjContainer::AddArgument(const std::string& call_name, const std::string& help_text, std::string* argument, const Argument::Req_t required, bool* was_defined) {
		Argument* the_argument = new Argument(call_name, help_text, argument, required, was_defined);
		AddArgObject((ArgObject*) the_argument);
	}

	void ArgObjContainer::AddArgument(const std::string& call_name, const std::string& help_text, std::vector<std::string>* arguments, const Argument::Req_t required, bool* was_defined) {
		Argument* the_argument = new Argument(call_name, help_text, arguments, required, was_defined);
		AddArgObject((ArgObject*) the_argument);
	}

	void ArgObjContainer::AddArgument(const std::string& call_name, const std::string& help_text, char* argument, const Argument::Req_t required, bool* was_defined) {
		Argument* the_argument = new Argument(call_name, help_text, argument, required, was_defined);
		AddArgObject((ArgObject*) the_argument);
	}

	void ArgObjContainer::AddArgument(const std::string& call_name, const std::string& help_text, std::vector<char>* arguments, const Argument::Req_t required, bool* was_defined) {
		Argument* the_argument = new Argument(call_name, help_text, arguments, required, was_defined);
		AddArgObject((ArgObject*) the_argument);
	}

	void ArgObjContainer::AddArgument(const std::string& call_name, const std::string& help_text, unsigned char* argument, const Argument::Req_t required, bool* was_defined) {
		Argument* the_argument = new Argument(call_name, help_text, argument, required, was_defined);
		AddArgObject((ArgObject*) the_argument);
	}

	void ArgObjContainer::AddArgument(const std::string& call_name, const std::string& help_text, std::vector<unsigned char>* arguments, const Argument::Req_t required, bool* was_defined) {
		Argument* the_argument = new Argument(call_name, help_text, arguments, required, was_defined);
		AddArgObject((ArgObject*) the_argument);
	}

	void ArgObjContainer::AddArgument(const std::string& call_name, const std::string& help_text, short* argument, const Argument::Req_t required, bool* was_defined) {
		Argument* the_argument = new Argument(call_name, help_text, argument, required, was_defined);
		AddArgObject((ArgObject*) the_argument);
	}

	void ArgObjContainer::AddArgument(const std::string& call_name, const std::string& help_text, std::vector<short>* arguments, const Argument::Req_t required, bool* was_defined) {
		Argument* the_argument = new Argument(call_name, help_text, arguments, required, was_defined);
		AddArgObject((ArgObject*) the_argument);
	}

	void ArgObjContainer::AddArgument(const std::string& call_name, const std::string& help_text, unsigned short* argument, const Argument::Req_t required, bool* was_defined) {
		Argument* the_argument = new Argument(call_name, help_text, argument, required, was_defined);
		AddArgObject((ArgObject*) the_argument);
	}

	void ArgObjContainer::AddArgument(const std::string& call_name, const std::string& help_text, std::vector<unsigned short>* arguments, const Argument::Req_t required, bool* was_defined) {
		Argument* the_argument = new Argument(call_name, help_text, arguments, required, was_defined);
		AddArgObject((ArgObject*) the_argument);
	}

	void ArgObjContainer::AddArgument(const std::string& call_name, const std::string& help_text, int* argument, const Argument::Req_t required, bool* was_defined) {
		Argument* the_argument = new Argument(call_name, help_text, argument, required, was_defined);
		AddArgObject((ArgObject*) the_argument);
	}

	void ArgObjContainer::AddArgument(const std::string& call_name, const std::string& help_text, std::vector<int>* arguments, const Argument::Req_t required, bool* was_defined) {
		Argument* the_argument = new Argument(call_name, help_text, arguments, required, was_defined);
		AddArgObject((ArgObject*) the_argument);
	}

	void ArgObjContainer::AddArgument(const std::string& call_name, const std::string& help_text, unsigned int* argument, const Argument::Req_t required, bool* was_defined) {
		Argument* the_argument = new Argument(call_name, help_text, argument, required, was_defined);
		AddArgObject((ArgObject*) the_argument);
	}

	void ArgObjContainer::AddArgument(const std::string& call_name, const std::string& help_text, std::vector<unsigned int>* arguments, const Argument::Req_t required, bool* was_defined) {
		Argument* the_argument = new Argument(call_name, help_text, arguments, required, was_defined);
		AddArgObject((ArgObject*) the_argument);
	}

	void ArgObjContainer::AddArgument(const std::string& call_name, const std::string& help_text, long* argument, const Argument::Req_t required, bool* was_defined) {
		Argument* the_argument = new Argument(call_name, help_text, argument, required, was_defined);
		AddArgObject((ArgObject*) the_argument);
	}

	void ArgObjContainer::AddArgument(const std::string& call_name, const std::string& help_text, std::vector<long>* arguments, const Argument::Req_t required, bool* was_defined) {
		Argument* the_argument = new Argument(call_name, help_text, arguments, required, was_defined);
		AddArgObject((ArgObject*) the_argument);
	}

	void ArgObjContainer::AddArgument(const std::string& call_name, const std::string& help_text, unsigned long* argument, const Argument::Req_t required, bool* was_defined) {
		Argument* the_argument = new Argument(call_name, help_text, argument, required, was_defined);
		AddArgObject((ArgObject*) the_argument);
	}

	void ArgObjContainer::AddArgument(const std::string& call_name, const std::string& help_text, std::vector<unsigned long>* arguments, const Argument::Req_t required, bool* was_defined) {
		Argument* the_argument = new Argument(call_name, help_text, arguments, required, was_defined);
		AddArgObject((ArgObject*) the_argument);
	}

	void ArgObjContainer::AddArgument(const std::string& call_name, const std::string& help_text, long long* argument, const Argument::Req_t required, bool* was_defined) {
		Argument* the_argument = new Argument(call_name, help_text, argument, required, was_defined);
		AddArgObject((ArgObject*) the_argument);
	}

	void ArgObjContainer::AddArgument(const std::string& call_name, const std::string& help_text, std::vector<long long>* arguments, const Argument::Req_t required, bool* was_defined) {
		Argument* the_argument = new Argument(call_name, help_text, arguments, required, was_defined);
		AddArgObject((ArgObject*) the_argument);
	}

	void ArgObjContainer::AddArgument(const std::string& call_name, const std::string& help_text, unsigned long long* argument, const Argument::Req_t required, bool* was_defined) {
		Argument* the_argument = new Argument(call_name, help_text, argument, required, was_defined);
		AddArgObject((ArgObject*) the_argument);
	}

	void ArgObjContainer::AddArgument(const std::string& call_name, const std::string& help_text, std::vector<unsigned long long>* arguments, const Argument::Req_t required, bool* was_defined) {
		Argument* the_argument = new Argument(call_name, help_text, arguments, required, was_defined);
		AddArgObject((ArgObject*) the_argument);
	}

	void ArgObjContainer::AddArgument(const std::string& call_name, const std::string& help_text, float* argument, const Argument::Req_t required, bool* was_defined) {
		Argument* the_argument = new Argument(call_name, help_text, argument, required, was_defined);
		AddArgObject((ArgObject*) the_argument);
	}

	void ArgObjContainer::AddArgument(const std::string& call_name, const std::string& help_text, std::vector<float>* arguments, const Argument::Req_t required, bool* was_defined) {
		Argument* the_argument = new Argument(call_name, help_text, arguments, required, was_defined);
		AddArgObject((ArgObject*) the_argument);
	}

	void ArgObjContainer::AddArgument(const std::string& call_name, const std::string& help_text, double* argument, const Argument::Req_t required, bool* was_defined) {
		Argument* the_argument = new Argument(call_name, help_text, argument, required, was_defined);
		AddArgObject((ArgObject*) the_argument);
	}

	void ArgObjContainer::AddArgument(const std::string& call_name, const std::string& help_text, std::vector<double>* arguments, const Argument::Req_t required, bool* was_defined) {
		Argument* the_argument = new Argument(call_name, help_text, arguments, required, was_defined);
		AddArgObject((ArgObject*) the_argument);
	}
	
	void ArgObjContainer::AddArgument(const std::string& call_name, const std::string& help_text, long double* argument, const Argument::Req_t required, bool* was_defined) {
		Argument* the_argument = new Argument(call_name, help_text, argument, required, was_defined);
		AddArgObject((ArgObject*) the_argument);
	}

	void ArgObjContainer::AddArgument(const std::string& call_name, const std::string& help_text, std::vector<long double>* arguments, const Argument::Req_t required, bool* was_defined) {
		Argument* the_argument = new Argument(call_name, help_text, arguments, required, was_defined);
		AddArgObject((ArgObject*) the_argument);
	}

	void ArgObjContainer::AddArgObject(ArgObject* object) {
		objects.push_back(object);
	}
}
