#ifndef ARGPARSE_ArgGroup_HDR
#define ARGPARSE_ArgGroup_HDR

#include "ArgParse/ArgObject.h"
#include "ArgParse/ArgObjContainer.h"

namespace ArgParse {
	class ArgGroup : public ArgObject , public ArgObjContainer {
		public:
			ArgGroup(const std::string& title, const std::string& help_text, const ArgObject::Mode_t mode = ArgObject::None, const ArgObject::Req_t required = ArgObject::Optional, ArgObjContainer* parent = ARGPARSE_NULLPTR) : ArgObject(help_text, mode, required, ArgObject::Group) , ArgObjContainer(parent) {
				this->title = title;
			}
			~ArgGroup() {
			}

			virtual bool IsConfigured() __attribute__((warn_unused_result));
			virtual size_t AmountOfData();
			virtual ArgObject::Accept_t AcceptsArgument(std::string arg) __attribute__((warn_unused_result));
			virtual ArgObject::Pass_t PassArgument(std::string arg, std::string opt, bool with_opt) __attribute__((warn_unused_result));
	
			virtual bool IsReady() __attribute__((warn_unused_result));
	
			virtual std::string GetHelpText();

			const std::string& GetTitle() {
				return this->title;
			}

		private:
			std::string title;
	};
}

#endif
