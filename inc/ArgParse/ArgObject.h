#ifndef ARGPARSE_ArgObject_HDR
#define ARGPARSE_ArgObject_HDR

#include <string>

namespace ArgParse {
	class ArgObject {
		public:
			typedef int Accept_t;
			static const Accept_t No;
			static const Accept_t WithArg;
			static const Accept_t WithoutArg;

			typedef int Pass_t;
			static const Pass_t NotAccepted;
			static const Pass_t Accepted;
			static const Pass_t Error;
	
			ArgObject();
			virtual ~ArgObject();
	
			virtual Accept_t AcceptsArgument(std::string arg) __attribute__((warn_unused_result)) = 0;
			virtual Pass_t PassArgument(std::string arg, std::string opt, bool with_opt) __attribute__((warn_unused_result)) = 0;
	
			virtual bool IsReady() __attribute__((warn_unused_result)) = 0;
	
			virtual std::string GetHelpText() = 0;
	};
}

#endif
