#ifndef ARGPARSE_Argument_HDR
#define ARGPARSE_Argument_HDR

#include <vector>
#include <string>
#include "ArgParse/config.h"
#include "ArgParse/ArgObject.h"

namespace ArgParse {
	class Argument : public ArgObject {
		public:
			Argument(const std::string& call_name, const std::string& help_text, const Req_t required, bool* was_defined = ARGPARSE_NULLPTR);
			virtual ~Argument();

			static std::vector<std::string> GetCallNames(const std::string& combined_names);

			std::string GetName(size_t i=0) const;
			size_t GetNum() {
				return call_names.size();
			}

			//ArgObject functions
			ArgObject::State_t State(bool quiet = false) const __attribute__((warn_unused_result));
			virtual std::string GetHelpText() const;
			void PrepareHelpText(std::stringstream& ss) const;
			virtual void AppendType(std::stringstream& ss) const;
			std::string GetHelpTextWithMessage(const std::string& message) const;

		protected:
			bool DoesAnArgumentMatch(size_t& position, const std::string& arg) const __attribute__((warn_unused_result));
			bool WasDefined() const {
				return *defined;
			}
			void SetDefined(bool status) {
				*defined = status;
			}

		private:
			Req_t IsRequired() const {
				return GetRequired();
			}

			std::vector<std::string> call_names;
			bool* defined;
			bool responsible_for_defined;
	};
}

#endif
