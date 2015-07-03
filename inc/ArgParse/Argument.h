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
			bool IsReady() const __attribute__((warn_unused_result));
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
