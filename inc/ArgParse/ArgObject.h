#ifndef ARGPARSE_ArgObject_HDR
#define ARGPARSE_ArgObject_HDR

#include <string>

namespace ArgParse {
	class ArgObject {
		public:
			//Type management
			typedef int Type_t;
			//Argument types
			static const Type_t Bool;
			static const Type_t Str;
			static const Type_t Char;
			static const Type_t UChar;
			static const Type_t Short;
			static const Type_t UShort;
			static const Type_t Int;
			static const Type_t UInt;
			static const Type_t Long;
			static const Type_t ULong;
			static const Type_t LongLong;
			static const Type_t ULongLong;
			static const Type_t Float;
			static const Type_t Double;
			static const Type_t LongDouble;

			static const Type_t Divider;

			//Group types
			static const Type_t Group;
			static const Type_t Normal;
			static const Type_t Exclusive;
			static const Type_t Inclusive;

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
	
			ArgObject(const std::string& help_text, const Mode_t mode, const bool required, const Type_t type) {
				this->help_text = help_text;
				this->mode = mode;
				this->required = required;
				this->type = type;
			}
			virtual ~ArgObject();
	
			virtual bool IsConfigured() __attribute__((warn_unused_result)) {
				return true;
			}
			virtual Accept_t AcceptsArgument(std::string arg) __attribute__((warn_unused_result)) = 0;
			virtual Pass_t PassArgument(std::string arg, std::string opt, bool with_opt) __attribute__((warn_unused_result)) = 0;

			virtual size_t AmountOfData() {
				return 0;
			}
	
			virtual bool IsReady() __attribute__((warn_unused_result)) = 0;
	
			virtual std::string GetHelpText() = 0;

			Type_t GetType() const {
				return type;
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
			Type_t type;
			Mode_t mode;
			bool required;
			std::string help_text;
	};
}

#endif
