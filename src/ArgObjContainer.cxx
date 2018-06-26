#include "ArgParse/Message.h"
#include "ArgParse/ArgObjContainer.h"
#include "ArgParse/ArgGroup.h"
#include "ArgParse/ArgInclusiveGroup.h"
#include "ArgParse/ArgExclusiveGroup.h"

namespace ArgParse {
	ArgObjContainer::~ArgObjContainer() {
		for(size_t i=0; i<objects.size(); ++i) {
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
		if(parent == nullptr) {
			for(size_t i=0; i<objects.size(); ++i) {
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
