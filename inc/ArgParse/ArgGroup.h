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

			virtual bool IsConfigured() __attribute__((warn_unused_result));
			virtual size_t AmountOfData();
			virtual ArgObject::Accept_t AcceptsArgument(std::string arg) __attribute__((warn_unused_result));
			virtual ArgObject::Pass_t PassArgument(std::string arg, std::string opt, bool with_opt) __attribute__((warn_unused_result));
	
			virtual bool IsReady() __attribute__((warn_unused_result));
	
			virtual std::string GetHelpText();

			std::string GetGroupHelpText(const std::string& name);

			const std::string& GetTitle() {
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
