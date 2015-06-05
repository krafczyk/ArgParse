#ifndef ARGPARSE_ArgObject_HDR
#define ARGPARSE_ArgObject_HDR

#include <string>

class ArgObject {
	public:
		ArgObject();
		virtual ~ArgObject();

		virtual int AcceptsArgument(std::string arg) = 0;
		virtual int PassArgument(std::string arg, std::string opt, bool with_opt) = 0;

		virtual bool IsReady() = 0;
};

#endif
