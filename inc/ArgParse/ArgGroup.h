#ifndef ARGPARSE_ArgGroup_HDR
#define ARGPARSE_ArgGroup_HDR

#include "ArgParse/ArgObject.h"
#include "ArgParse/ArgObjContainer.h"

namespace ArgParse {
	class ArgGroup : public ArgObject, public ArgObjContainer {
		public:
			ArgGroup(const std::string& title, const std::string& help_text, const ArgObject::Type_t type = ArgObject::Normal, const ArgObject::Mode_t mode = ArgObject::None, const ArgObject::Req_t required = ArgObject::Optional) : ArgObject(help_text, mode, required, type) {
				this->title = title;
			}
			~ArgGroup() {
			}

			bool IsConfigured() __attribute__((warn_unused_result));
			size_t AmountOfData();
			ArgObject::Accept_t AcceptsArgument(std::string arg) __attribute__((warn_unused_result));
			ArgObject::Pass_t PassArgument(std::string arg, std::string opt, bool with_opt) __attribute__((warn_unused_result));
	
			bool IsReady() __attribute__((warn_unused_result));
	
			std::string GetHelpText();

		private:
			std::string title;
	};
}

#endif
