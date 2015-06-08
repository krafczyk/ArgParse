#ifndef ARGPARSE_ArgExclusiveGroup_HDR
#define ARGPARSE_ArgExclusiveGroup_HDR

#include "ArgParse/ArgGroup.h"

namespace ArgParse {
	class ArgExclusiveGroup : public ArgGroup {
		public:
			ArgExclusiveGroup(const std::string& title, const std::string& help_text, const ArgObject::Mode_t mode = ArgObject::None, const ArgObject::Req_t required = ArgObject::Optional, ArgObjContainer* parent = ARGPARSE_NULLPTR);
	};
}

#endif
