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
	
			ArgObject();
			virtual ~ArgObject();
	
			virtual Accept_t AcceptsArgument(std::string arg) = 0;
			virtual int PassArgument(std::string arg, std::string opt, bool with_opt) = 0;
	
			virtual bool IsReady() = 0;
	
			virtual std::string GetHelpText() = 0;
	};
}

#endif
