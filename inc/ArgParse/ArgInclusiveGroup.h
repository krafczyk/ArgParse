#ifndef ARGPARSE_ArgInclusiveGroup_HDR
#define ARGPARSE_ArgInclusiveGroup_HDR

#include "ArgParse/ArgGroup.h"

namespace ArgParse {
	class ArgInclusiveGroup : public ArgGroup {
		public:
			ArgInclusiveGroup(const std::string& title, const std::string& help_text, const ArgObject::Mode_t mode = ArgObject::None, const ArgObject::Req_t required = ArgObject::Optional, ArgObjContainer* parent = ARGPARSE_NULLPTR);

			virtual bool IsConfigured() __attribute__((warn_unused_result));
			virtual size_t AmountOfData();
			virtual ArgObject::Accept_t AcceptsArgument(std::string arg) __attribute__((warn_unused_result));
			virtual bool IsReady() __attribute__((warn_unused_result));
	
			virtual std::string GetHelpText();
	};
}

#endif
