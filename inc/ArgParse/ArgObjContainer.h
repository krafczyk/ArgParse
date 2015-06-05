#ifndef ARGPARSE_ArgObjContainer_HDR
#define ARGPARSE_ArgObjContainer_HDR

#include "ArgParse/Argument.h"
#include "ArgParse/ArgObject.h"

namespace ArgParse {
	class ArgObjContainer {
		public:
			ArgObjContainer() {
			}
			virtual ~ArgObjContainer();

			void AddArgument(const std::string& call_name, const std::string& help_text, bool* argument, const Argument::Req_t required = Argument::Optional, bool* was_defined = ARGPARSE_NULLPTR);
			void AddArgument(const std::string& call_name, const std::string& help_text, std::vector<bool>* arguments, const Argument::Req_t required = Argument::Optional, bool* was_defined = ARGPARSE_NULLPTR);
			void AddArgument(const std::string& call_name, const std::string& help_text, std::string* argument, const Argument::Req_t required = Argument::Optional, bool* was_defined = ARGPARSE_NULLPTR);
			void AddArgument(const std::string& call_name, const std::string& help_text, std::vector<std::string>* arguments, const Argument::Req_t requred = Argument::Optional, bool* was_defined = ARGPARSE_NULLPTR);
			void AddArgument(const std::string& call_name, const std::string& help_text, char* argument, const Argument::Req_t required = Argument::Optional, bool* was_defined = ARGPARSE_NULLPTR);
			void AddArgument(const std::string& call_name, const std::string& help_text, std::vector<char>* arguments, const Argument::Req_t required = Argument::Optional, bool* was_defined = ARGPARSE_NULLPTR);
			void AddArgument(const std::string& call_name, const std::string& help_text, unsigned char* argument, const Argument::Req_t required = Argument::Optional, bool* was_defined = ARGPARSE_NULLPTR);
			void AddArgument(const std::string& call_name, const std::string& help_text, std::vector<unsigned char>* arguments, const Argument::Req_t required = Argument::Optional, bool* was_defined = ARGPARSE_NULLPTR);
			void AddArgument(const std::string& call_name, const std::string& help_text, short* argument, const Argument::Req_t required = Argument::Optional, bool* was_defined = ARGPARSE_NULLPTR);
			void AddArgument(const std::string& call_name, const std::string& help_text, std::vector<short>* arguments, const Argument::Req_t required = Argument::Optional, bool* was_defined = ARGPARSE_NULLPTR);
			void AddArgument(const std::string& call_name, const std::string& help_text, unsigned short* argument, const Argument::Req_t required = Argument::Optional, bool* was_defined = ARGPARSE_NULLPTR);
			void AddArgument(const std::string& call_name, const std::string& help_text, std::vector<unsigned short>* arguments, const Argument::Req_t required = Argument::Optional, bool* was_defined = ARGPARSE_NULLPTR);
			void AddArgument(const std::string& call_name, const std::string& help_text, int* argument, const Argument::Req_t required = Argument::Optional, bool* was_defined = ARGPARSE_NULLPTR);
			void AddArgument(const std::string& call_name, const std::string& help_text, std::vector<int>* arguments, const Argument::Req_t required = Argument::Optional, bool* was_defined = ARGPARSE_NULLPTR);
			void AddArgument(const std::string& call_name, const std::string& help_text, unsigned int* argument, const Argument::Req_t required = Argument::Optional, bool* was_defined = ARGPARSE_NULLPTR);
			void AddArgument(const std::string& call_name, const std::string& help_text, std::vector<unsigned int>* arguments, const Argument::Req_t required = Argument::Optional, bool* was_defined = ARGPARSE_NULLPTR);
			void AddArgument(const std::string& call_name, const std::string& help_text, long* argument, const Argument::Req_t required = Argument::Optional, bool* was_defined = ARGPARSE_NULLPTR);
			void AddArgument(const std::string& call_name, const std::string& help_text, std::vector<long>* arguments, const Argument::Req_t required = Argument::Optional, bool* was_defined = ARGPARSE_NULLPTR);
			void AddArgument(const std::string& call_name, const std::string& help_text, unsigned long* argument, const Argument::Req_t required = Argument::Optional, bool* was_defined = ARGPARSE_NULLPTR);
			void AddArgument(const std::string& call_name, const std::string& help_text, std::vector<unsigned long>* arguments, const Argument::Req_t required = Argument::Optional, bool* was_defined = ARGPARSE_NULLPTR);
			void AddArgument(const std::string& call_name, const std::string& help_text, long long* argument, const Argument::Req_t required = Argument::Optional, bool* was_defined = ARGPARSE_NULLPTR);
			void AddArgument(const std::string& call_name, const std::string& help_text, std::vector<long long>* arguments, const Argument::Req_t required = Argument::Optional, bool* was_defined = ARGPARSE_NULLPTR);
			void AddArgument(const std::string& call_name, const std::string& help_text, unsigned long long* argument, const Argument::Req_t required = Argument::Optional, bool* was_defined = ARGPARSE_NULLPTR);
			void AddArgument(const std::string& call_name, const std::string& help_text, std::vector<unsigned long long>* arguments, const Argument::Req_t required = Argument::Optional, bool* was_defined = ARGPARSE_NULLPTR);
			void AddArgument(const std::string& call_name, const std::string& help_text, float* argument, const Argument::Req_t required = Argument::Optional, bool* was_defined = ARGPARSE_NULLPTR);
			void AddArgument(const std::string& call_name, const std::string& help_text, std::vector<float>* arguments, const Argument::Req_t required = Argument::Optional, bool* was_defined = ARGPARSE_NULLPTR);
			void AddArgument(const std::string& call_name, const std::string& help_text, double* argument, const Argument::Req_t required = Argument::Optional, bool* was_defined = ARGPARSE_NULLPTR);
			void AddArgument(const std::string& call_name, const std::string& help_text, std::vector<double>* arguments, const Argument::Req_t required = Argument::Optional, bool* was_defined = ARGPARSE_NULLPTR);
			void AddArgument(const std::string& call_name, const std::string& help_text, long double* argument, const Argument::Req_t required = Argument::Optional, bool* was_defined = ARGPARSE_NULLPTR);
			void AddArgument(const std::string& call_name, const std::string& help_text, std::vector<long double>* arguments, const Argument::Req_t required = Argument::Optional, bool* was_defined = ARGPARSE_NULLPTR);

		private:
			void CheckName(const std::string& call_name);
			void AddArgument(Argument* argument);
			void AddArgObject(ArgObject* object);

		protected:
			std::vector<ArgObject*> objects;
	};
}

#endif
