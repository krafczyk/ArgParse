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

#ifndef ARGPARSE_ArgObjContainer_HDR
#define ARGPARSE_ArgObjContainer_HDR

#include "ArgParse/config.h"
#include "ArgParse/ArgObject.h"
#include "ArgParse/Argument.h"
#include "ArgParse/ArgScalar.h"
#include "ArgParse/ArgVector.h"


namespace ArgParse {
	//Need to forward declare this..
	class ArgGroup;

	class ArgObjContainer {
		public:
			ArgObjContainer(ArgObjContainer* parent = ARGPARSE_NULLPTR) {
				this->parent = parent;
			}
			virtual ~ArgObjContainer();

			template<class T>
			void AddArgument(const std::string& call_name, const std::string& help_text, T* argument, const ArgObject::Req_t required = ArgObject::Optional, bool* was_defined = ARGPARSE_NULLPTR) {
				Argument* the_argument = (Argument*) new ArgScalar<T>(call_name, ArgObject::Single, help_text, argument, required, was_defined);
				AddArgument(the_argument);
			}
			
			template<class T>
			void AddArgument(const std::string& call_name, const std::string& help_text, std::vector<T>* argument, const ArgObject::Req_t required = ArgObject::Optional, bool* was_defined = ARGPARSE_NULLPTR) {
				Argument* the_argument = (Argument*) new ArgVector<T>(call_name, ArgObject::Multiple, help_text, argument, required, was_defined);
				AddArgument(the_argument);
			}

			ArgGroup& AddArgGroup(const std::string& title, const std::string& help_text, const ArgObject::Mode_t mode = ArgObject::None, const ArgObject::Req_t required = ArgObject::Optional);
			ArgGroup& AddInclusiveArgGroup(const std::string& title, const std::string& help_text, const ArgObject::Mode_t mode = ArgObject::None, const ArgObject::Req_t required = ArgObject::Optional);
			ArgGroup& AddExclusiveArgGroup(const std::string& title, const std::string& help_text, const ArgObject::Mode_t mode = ArgObject::None, const ArgObject::Req_t required = ArgObject::Optional);

		private:
			void CheckName(const std::string& call_name, ArgObjContainer* parent);
			void AddArgument(Argument* argument);
			void AddArgGroupObject(ArgGroup* arggroup);
			void AddArgObject(ArgObject* object);

		protected:
			ArgObjContainer* parent;
			std::vector<ArgObject*> objects;
	};
}

#endif
