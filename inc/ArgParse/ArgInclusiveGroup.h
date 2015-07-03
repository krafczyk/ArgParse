#ifndef ARGPARSE_ArgInclusiveGroup_HDR
#define ARGPARSE_ArgInclusiveGroup_HDR

#include "ArgParse/ArgGroup.h"

namespace ArgParse {
	class ArgInclusiveGroup : public ArgGroup {
		public:
			ArgInclusiveGroup(const std::string& title, const std::string& help_text, const ArgObject::Mode_t mode = ArgObject::None, const ArgObject::Req_t required = ArgObject::Optional, ArgObjContainer* parent = ARGPARSE_NULLPTR);

			virtual bool IsConfigured() const __attribute__((warn_unused_result));
			virtual size_t AmountOfData() const;
	
			virtual std::string GetHelpText() const;

			virtual bool CheckSubObjects() const __attribute__((warn_unused_result));

			virtual bool CheckDataConsistency() const __attribute__((warn_unused_result));
	};
}

#endif
