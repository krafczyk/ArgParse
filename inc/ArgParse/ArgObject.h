/*
ArgParser - C++ Argument Parser reflecting the python module ArgParse.
Copyright (C) 2014-2015  Matthew Scott Krafczyk

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

			//Ready types
			typedef int Ready_t;
			static const Ready_t NotReady;
			static const Ready_t Defined;
			static const Ready_t NotDefined;
			static const Ready_t Ready;
	
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
	
			virtual int IsReady(bool quiet __attribute__((unused)) = false) const __attribute__((warn_unused_result)) {
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
