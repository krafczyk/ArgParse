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

#include "ArgParse/Message.h"
#include "ArgParse/ArgObjContainer.h"
#include "ArgParse/ArgGroup.h"
#include "ArgParse/ArgInclusiveGroup.h"
#include "ArgParse/ArgExclusiveGroup.h"

namespace ArgParse {
	ArgObjContainer::~ArgObjContainer() {
		for(size_t i=0;i<objects.size();++i) {
			delete objects[i];
		}
	}

	ArgGroup* ArgObjContainer::AddArgGroup(const std::string& title, const std::string& help_text, const ArgObject::Mode_t mode, const ArgObject::Req_t required) {
		ArgGroup* the_group = new ArgGroup(title, help_text, mode, required, this);
		AddArgGroupObject(the_group);
		return the_group;
	}

	ArgGroup* ArgObjContainer::AddInclusiveArgGroup(const std::string& title, const std::string& help_text, const ArgObject::Mode_t mode, const ArgObject::Req_t required) {
		ArgGroup* the_group = (ArgGroup*) new ArgInclusiveGroup(title, help_text, mode, required, this);
		AddArgGroupObject(the_group);
		return the_group;
	}

	ArgGroup* ArgObjContainer::AddExclusiveArgGroup(const std::string& title, const std::string& help_text, const ArgObject::Mode_t mode, const ArgObject::Req_t required) {
		ArgGroup* the_group = (ArgGroup*) new ArgExclusiveGroup(title, help_text, mode, required, this);
		AddArgGroupObject(the_group);
		return the_group;
	}

	void ArgObjContainer::CheckName(const std::string& call_name, ArgObjContainer* parent) {
		if(parent == ARGPARSE_NULLPTR) {
			for(size_t i=0;i<objects.size();++i) {
				ArgObject::Accept_t accept = objects[i]->AcceptsArgument(call_name);
				if(accept != ArgObject::No) {
					if(accept == ArgObject::GroupName) {
						ArgParseMessageError("The argument (%s) conflicts with a group name!\n", call_name.c_str());
						SetMessage("The argument (%s) conflicts with a group name!\n", call_name.c_str());
					} else {
						ArgParseMessageError("The argument (%s) has already been defined!\n", call_name.c_str());
						SetMessage("The argument (%s) has already been defined!\n", call_name.c_str());
					}
					exit(-1);
				}
			}
		} else {
			parent->CheckName(call_name, parent->parent);
		}
	}

	void ArgObjContainer::AddArgument(Argument* argument) {
		//Check that the name hasn't been defined already
		for(size_t i=0; i<argument->GetNum(); ++i) {
			CheckName(argument->GetName(i), parent);
		}
		AddArgObject((ArgObject*) argument);
	}

	void ArgObjContainer::AddArgGroupObject(ArgGroup* arggroup) {
		//Check that the name hasn't been defined already
		CheckName(arggroup->GetTitle(), parent);
		AddArgObject((ArgObject*) arggroup);
	}

	void ArgObjContainer::AddArgObject(ArgObject* object) {
		objects.push_back(object);
	}
}
