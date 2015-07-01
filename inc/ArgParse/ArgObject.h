#ifndef ARGPARSE_ArgObject_HDR
#define ARGPARSE_ArgObject_HDR

#include <string>

#include "ArgParse/Message.h"

namespace ArgParse {
	class ArgObject {
		public:
			//Accept management
			typedef int Accept_t;
			static const Accept_t No;
			static const Accept_t WithArg;
			static const Accept_t WithoutArg;
			static const Accept_t GroupName;

			//Pass management
			typedef int Pass_t;
			static const Pass_t NotAccepted;
			static const Pass_t Accepted;
			static const Pass_t Error;

			//Mode management
			typedef int Mode_t;
			static const Mode_t Single;
			static const Mode_t Multiple;
			static const Mode_t None;

			//Required management
			typedef bool Req_t;
			static const Req_t Required;
			static const Req_t Optional;
	
			ArgObject(const std::string& help_text, const Mode_t mode, const bool required) {
				this->help_text = help_text;
				this->mode = mode;
				this->required = required;
			}
			virtual ~ArgObject();
	
			virtual bool IsConfigured() __attribute__((warn_unused_result)) {
				return true;
			}
			virtual Accept_t AcceptsArgument(const std::string& arg __attribute__((unused))) __attribute__((warn_unused_result)) {
				return ArgObject::No;
			}
			virtual Pass_t PassArgument(const std::string& arg __attribute__((unused)), const std::string& opt __attribute__((unused)), const bool with_opt __attribute__((unused))) __attribute__((warn_unused_result)) {
				return ArgObject::NotAccepted;
			}

			virtual size_t AmountOfData() {
				return 0;
			}
	
			virtual bool IsReady() __attribute__((warn_unused_result)) {
				return false;
			}
	
			virtual std::string GetHelpText() {
				return "Empty ArgObject";
			}

			Mode_t GetMode() const {
				return mode;
			}

			bool GetRequired() const {
				return required;
			}

			const std::string& GetHelp() const {
				return help_text;
			}

		private:
			Mode_t mode;
			bool required;
			std::string help_text;
	};
}

#endif
