#ifndef ARGPARSE_ArgGroup_HDR
#define ARGPARSE_ArgGroup_HDR

#include "ArgParse/ArgObject.h"
#include "ArgParse/ArgObjContainer.h"

namespace ArgParse {
	class ArgGroup : public ArgObject , public ArgObjContainer {
		public:
			ArgGroup(const std::string& title, const std::string& help_text, const ArgObject::Mode_t mode = ArgObject::None, const ArgObject::Req_t required = ArgObject::Optional, ArgObjContainer* parent = ARGPARSE_NULLPTR) : ArgObject(help_text, required) , ArgObjContainer(parent) {
				this->mode = mode;
				this->title = title;
			}
			~ArgGroup() {
			}

			virtual bool IsConfigured() const __attribute__((warn_unused_result));
			virtual size_t AmountOfData() const;
			virtual ArgObject::Accept_t AcceptsArgument(const std::string& arg) const __attribute__((warn_unused_result));
			virtual ArgObject::Pass_t PassArgument(const std::string& arg, const std::string& opt, const bool with_opt) __attribute__((warn_unused_result));

			virtual ArgObject::State_t State(bool quiet = false) const __attribute__((warn_unused_result));

			virtual std::string GetHelpText() const;

			virtual bool CheckSubObjects() const __attribute__((warn_unused_result));

			virtual bool CheckDataConsistency() const __attribute__((warn_unused_result));

			std::string GetGroupHelpText(const std::string& name) const;

			const std::string& GetTitle() const {
				return this->title;
			}

			virtual ArgObject::Mode_t GetMode() const {
				return this->mode;
			}

		private:
			ArgObject::Mode_t mode;
			std::string title;
	};
}

#endif
