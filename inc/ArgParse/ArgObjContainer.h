#ifndef ARGPARSE_ArgObjContainer_HDR
#define ARGPARSE_ArgObjContainer_HDR

#include "ArgParse/config.h"
#include "ArgParse/ArgObject.h"
#include "ArgParse/Argument.h"


namespace ArgParse {
	//Need to forward declare this..
	class ArgGroup;

	class ArgObjContainer {
		public:
			ArgObjContainer(ArgObjContainer* parent = ARGPARSE_NULLPTR) {
				this->parent = parent;
			}
			virtual ~ArgObjContainer();

			void AddArgument(const std::string& call_name, const std::string& help_text, bool* argument, const ArgObject::Req_t required = ArgObject::Optional, bool* was_defined = ARGPARSE_NULLPTR);
			void AddArgument(const std::string& call_name, const std::string& help_text, std::vector<bool>* arguments, const ArgObject::Req_t required = ArgObject::Optional, bool* was_defined = ARGPARSE_NULLPTR);
			void AddArgument(const std::string& call_name, const std::string& help_text, std::string* argument, const ArgObject::Req_t required = ArgObject::Optional, bool* was_defined = ARGPARSE_NULLPTR);
			void AddArgument(const std::string& call_name, const std::string& help_text, std::vector<std::string>* arguments, const ArgObject::Req_t requred = ArgObject::Optional, bool* was_defined = ARGPARSE_NULLPTR);
			void AddArgument(const std::string& call_name, const std::string& help_text, char* argument, const ArgObject::Req_t required = ArgObject::Optional, bool* was_defined = ARGPARSE_NULLPTR);
			void AddArgument(const std::string& call_name, const std::string& help_text, std::vector<char>* arguments, const ArgObject::Req_t required = ArgObject::Optional, bool* was_defined = ARGPARSE_NULLPTR);
			void AddArgument(const std::string& call_name, const std::string& help_text, unsigned char* argument, const ArgObject::Req_t required = ArgObject::Optional, bool* was_defined = ARGPARSE_NULLPTR);
			void AddArgument(const std::string& call_name, const std::string& help_text, std::vector<unsigned char>* arguments, const ArgObject::Req_t required = ArgObject::Optional, bool* was_defined = ARGPARSE_NULLPTR);
			void AddArgument(const std::string& call_name, const std::string& help_text, short* argument, const ArgObject::Req_t required = ArgObject::Optional, bool* was_defined = ARGPARSE_NULLPTR);
			void AddArgument(const std::string& call_name, const std::string& help_text, std::vector<short>* arguments, const ArgObject::Req_t required = ArgObject::Optional, bool* was_defined = ARGPARSE_NULLPTR);
			void AddArgument(const std::string& call_name, const std::string& help_text, unsigned short* argument, const ArgObject::Req_t required = ArgObject::Optional, bool* was_defined = ARGPARSE_NULLPTR);
			void AddArgument(const std::string& call_name, const std::string& help_text, std::vector<unsigned short>* arguments, const ArgObject::Req_t required = ArgObject::Optional, bool* was_defined = ARGPARSE_NULLPTR);
			void AddArgument(const std::string& call_name, const std::string& help_text, int* argument, const ArgObject::Req_t required = ArgObject::Optional, bool* was_defined = ARGPARSE_NULLPTR);
			void AddArgument(const std::string& call_name, const std::string& help_text, std::vector<int>* arguments, const ArgObject::Req_t required = ArgObject::Optional, bool* was_defined = ARGPARSE_NULLPTR);
			void AddArgument(const std::string& call_name, const std::string& help_text, unsigned int* argument, const ArgObject::Req_t required = ArgObject::Optional, bool* was_defined = ARGPARSE_NULLPTR);
			void AddArgument(const std::string& call_name, const std::string& help_text, std::vector<unsigned int>* arguments, const ArgObject::Req_t required = ArgObject::Optional, bool* was_defined = ARGPARSE_NULLPTR);
			void AddArgument(const std::string& call_name, const std::string& help_text, long* argument, const ArgObject::Req_t required = ArgObject::Optional, bool* was_defined = ARGPARSE_NULLPTR);
			void AddArgument(const std::string& call_name, const std::string& help_text, std::vector<long>* arguments, const ArgObject::Req_t required = ArgObject::Optional, bool* was_defined = ARGPARSE_NULLPTR);
			void AddArgument(const std::string& call_name, const std::string& help_text, unsigned long* argument, const ArgObject::Req_t required = ArgObject::Optional, bool* was_defined = ARGPARSE_NULLPTR);
			void AddArgument(const std::string& call_name, const std::string& help_text, std::vector<unsigned long>* arguments, const ArgObject::Req_t required = ArgObject::Optional, bool* was_defined = ARGPARSE_NULLPTR);
			void AddArgument(const std::string& call_name, const std::string& help_text, long long* argument, const ArgObject::Req_t required = ArgObject::Optional, bool* was_defined = ARGPARSE_NULLPTR);
			void AddArgument(const std::string& call_name, const std::string& help_text, std::vector<long long>* arguments, const ArgObject::Req_t required = ArgObject::Optional, bool* was_defined = ARGPARSE_NULLPTR);
			void AddArgument(const std::string& call_name, const std::string& help_text, unsigned long long* argument, const ArgObject::Req_t required = ArgObject::Optional, bool* was_defined = ARGPARSE_NULLPTR);
			void AddArgument(const std::string& call_name, const std::string& help_text, std::vector<unsigned long long>* arguments, const ArgObject::Req_t required = ArgObject::Optional, bool* was_defined = ARGPARSE_NULLPTR);
			void AddArgument(const std::string& call_name, const std::string& help_text, float* argument, const ArgObject::Req_t required = ArgObject::Optional, bool* was_defined = ARGPARSE_NULLPTR);
			void AddArgument(const std::string& call_name, const std::string& help_text, std::vector<float>* arguments, const ArgObject::Req_t required = ArgObject::Optional, bool* was_defined = ARGPARSE_NULLPTR);
			void AddArgument(const std::string& call_name, const std::string& help_text, double* argument, const ArgObject::Req_t required = ArgObject::Optional, bool* was_defined = ARGPARSE_NULLPTR);
			void AddArgument(const std::string& call_name, const std::string& help_text, std::vector<double>* arguments, const ArgObject::Req_t required = ArgObject::Optional, bool* was_defined = ARGPARSE_NULLPTR);
			void AddArgument(const std::string& call_name, const std::string& help_text, long double* argument, const ArgObject::Req_t required = ArgObject::Optional, bool* was_defined = ARGPARSE_NULLPTR);
			void AddArgument(const std::string& call_name, const std::string& help_text, std::vector<long double>* arguments, const ArgObject::Req_t required = ArgObject::Optional, bool* was_defined = ARGPARSE_NULLPTR);

			ArgGroup& AddArgGroup(const std::string& title, const std::string& help_text, const ArgObject::Mode_t mode = ArgObject::None, const ArgObject::Req_t required = ArgObject::Optional, const ArgObject::Type_t type = ArgObject::Normal);

		private:
			void CheckName(const std::string& call_name, ArgObjContainer* parent);
			void AddArgument(Argument* argument);
			void AddArgGroupObject(ArgGroup* arggroup);
			void AddArgObject(ArgObject* object);

		protected:
			ArgObjContainer* parent;
			std::vector<ArgObject*> objects;
	};
}

#endif
