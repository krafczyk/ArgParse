#ifndef ARGPARSE_ArgObject_HDR
#define ARGPARSE_ArgObject_HDR

#include <string>

class ArgObject {
	public:
		typedef int Accept_t;
		static const Accept_t No = 0;
		static const Accept_t WithArg = 1;
		static const Accept_t WithoutArg = 2;

		ArgObject();
		virtual ~ArgObject();

		virtual Accept_t AcceptsArgument(std::string arg) = 0;
		virtual int PassArgument(std::string arg, std::string opt, bool with_opt) = 0;

		virtual bool IsReady() = 0;

		virtual std::string GetHelpText() = 0;
};

#endif
