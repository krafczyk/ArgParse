#include "ArgParse/ArgExclusiveGroup.h"

namespace ArgParse {
	ArgExclusiveGroup::ArgExclusiveGroup(const std::string& title, const std::string& help_text, const ArgObject::Mode_t mode, const ArgObject::Req_t required, ArgObjContainer* parent) : ArgGroup(title, help_text, mode, required, parent) {
	}
}
