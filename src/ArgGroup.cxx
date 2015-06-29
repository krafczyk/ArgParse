#include <sstream>

#include "ArgParse/Message.h"
#include "ArgParse/ArgGroup.h"

namespace ArgParse {
	bool ArgGroup::IsConfigured() {
		//if(GetType() <= ArgObject::Divider) {
		//	ArgParseMessageError("An Argument type is being passed to a group!\n");
		//	SetMessage("An Argument type is beign passed to a group!\n");
		//	return false;
		//}
		//If any of it's sub objects aren't configured, it isn't configured.
		for(size_t i = 0; i < objects.size(); ++i) {
			if(!objects[i]->IsConfigured()) {
				return false;
			}
		}
		return true;
	}

	size_t ArgGroup::AmountOfData() {
		for(size_t i=0;i<objects.size();++i) {
			size_t amount = objects[i]->AmountOfData();
			if(amount != 0) {
				return amount;
			}
		}
		return 0;
	}

	ArgObject::Accept_t ArgGroup::AcceptsArgument(std::string arg) {
		if (arg == GetTitle()) {
			return ArgObject::GroupName;
		}
		for(size_t i=0; i<this->objects.size(); ++i) {
			ArgObject::Accept_t accept = this->objects[i]->AcceptsArgument(arg);
			if (accept != ArgObject::No) {
				return accept;
			}
		}
		return ArgObject::No;
	}

	ArgObject::Pass_t ArgGroup::PassArgument(std::string arg, std::string opt, bool with_opt) {
		for(size_t i=0; i < this->objects.size(); ++i) {
			ArgObject::Pass_t passed = this->objects[i]->PassArgument(arg, opt, with_opt);
			if(passed != ArgObject::NotAccepted) {
				return passed;
			}
		}
		return ArgObject::NotAccepted;
	}

	bool ArgGroup::IsReady() {
		//Check for normal group
		//Check that everybody is ready.
		for(size_t i=0; i<objects.size(); ++i) {
			if(!objects[i]->IsReady()) {
				ArgParseMessageError("A sub argument of the group (%s) wasn't ready.\n", GetTitle().c_str());
				return false;
			}
		}
		return true;
	}

	std::string ArgGroup::GetGroupHelpText(const std::string& name) {
		std::stringstream ss;
		ss << "--- Begin ";
		if(name.size() != 0) {
			ss << name;
		}
		ss << "Group " << title << " ---" << std::endl;
		ss << GetHelp() << std::endl;
		for(size_t i=0;i< this->objects.size(); ++i) {
			ss << this->objects[i]->GetHelpText() << std::endl;
		}
		ss << "--- End ";
		if(name.size() != 0) {
			ss << name;
		}
		ss << "Group " << title << " ---" << std::endl;
		return ss.str();

	}

	std::string ArgGroup::GetHelpText() {
		return GetGroupHelpText("");
	}
}
