/*
ArgParser - C++ Argument Parser reflecting the python module ArgParse.
Copyright (C) 2014-2016  Matthew Scott Krafczyk

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

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
			static const Accept_t WithSingleArg;
			static const Accept_t WithMultipleArg;
			static const Accept_t WithoutArg;
			static const Accept_t GroupName;
			static const char* TranslateAccept(const Accept_t i);

			//Pass management
			typedef int Pass_t;
			static const Pass_t NotAccepted;
			static const Pass_t Accepted;
			static const Pass_t Error;
			static const char* TranslatePass(const Pass_t i);

			//Mode management
			typedef int Mode_t;
			static const Mode_t Single;
			static const Mode_t Multiple;
			static const Mode_t None;
			static const char* TranslateMode(const Mode_t i);

			//Required management
			typedef bool Req_t;
			static const Req_t Required;
			static const Req_t Optional;
			static const char* TranslateReq(const Req_t i);

			//Ready types
			typedef int State_t;
			static const State_t NotReady;
			static const State_t Defined;
			static const State_t NotDefined;
			static const State_t Ready;
			static const char* TranslateState(const State_t i);
	
			ArgObject(const std::string& help_text, const bool required) {
				this->help_text = help_text;
				this->required = required;
			}
			virtual ~ArgObject();
	
			virtual bool IsConfigured() const __attribute__((warn_unused_result)) {
				return true;
			}
			virtual Accept_t AcceptsArgument(const std::string& arg __attribute__((unused))) const __attribute__((warn_unused_result)) {
				return ArgObject::No;
			}
			virtual Pass_t PassArgument(const std::string& arg __attribute__((unused)), const std::string& opt __attribute__((unused)), const bool with_opt __attribute__((unused))) __attribute__((warn_unused_result)) {
				return ArgObject::NotAccepted;
			}

			virtual size_t AmountOfData() const {
				return 0;
			}
	
			virtual int State(bool quiet __attribute__((unused)) = false) const __attribute__((warn_unused_result)) {
				return ArgObject::NotReady;
			}
	
			virtual std::string GetHelpText() const {
				return "Empty ArgObject";
			}

			virtual Mode_t GetMode() const {
				return None;
			}

			bool GetRequired() const {
				return required;
			}

			const std::string& GetHelp() const {
				return help_text;
			}

		private:
			bool required;
			std::string help_text;
	};
}

#endif
