#include "ArgParse/Message.h"
#include "ArgParse/ArgInclusiveGroup.h"

namespace ArgParse {
	ArgInclusiveGroup::ArgInclusiveGroup(const std::string& title, const std::string& help_text, const ArgObject::Mode_t mode, const ArgObject::Req_t required, ArgObjContainer* parent) : ArgGroup(title, help_text, mode, required, parent) {
	}

	bool ArgInclusiveGroup::IsConfigured() {
		if(GetType() <= ArgObject::Divider) {
			ArgParseMessageError("An Argument type is being passed to a group!\n");
			SetMessage("An Argument type is beign passed to a group!\n");
			return false;
		}
		//If any of it's sub objects aren't configured, it isn't configured.
		for(size_t i = 0; i < objects.size(); ++i) {
			if(!objects[i]->IsConfigured()) {
				return false;
			}
		}
		//Now check for consistency with group mode
		if(GetMode() != None) {
			for(size_t i=0; i< objects.size(); ++i) {
				if (objects[i]->GetMode() != GetMode()) {
					ArgParseMessageError("An element of this container doesn't have the right mode! All elments must have matching modes.\n");
					SetMessage("An element of this container doesn't have the right mode! All elments must have matching modes.\n");
					return false;
				}
			}
			//Now check for consistency with requirement
			for(size_t i=0; i< objects.size(); ++i) {
				if(objects[i]->GetRequired() != GetRequired()) {
					ArgParseMessageError("An element of this container doesn't have the same requirement criteria!\n");
					SetMessage("An element of this container doesn't have the same requirement criteria!\n");
					return false;
				}
			}
		}
		return true;
	}

	size_t ArgInclusiveGroup::AmountOfData() {
		if(GetType() == ArgObject::Inclusive) {
			return objects[0]->AmountOfData();
		} else {
			for(size_t i=0;i<objects.size();++i) {
				size_t amount = objects[i]->AmountOfData();
				if(amount != 0) {
					return amount;
				}
			}
		}
		return 0;
	}

	ArgObject::Accept_t ArgInclusiveGroup::AcceptsArgument(std::string arg) {
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

	bool ArgInclusiveGroup::IsReady() {
		if(GetType() == ArgObject::Normal) {
			//Check for normal group
			//Check that everybody is ready.
			for(size_t i=0; i<objects.size(); ++i) {
				if(!objects[i]->IsReady()) {
					ArgParseMessageError("A sub argument of the group (%s) wasn't ready.\n", GetTitle().c_str());
					return false;
				}
			}
		} else if(GetType() == ArgObject::Inclusive) {
			//Check for inclusive groups
			if((GetMode() == ArgObject::Multiple)||(GetMode() == ArgObject::Single)) {
				//Check that everybody has the same amount of data.
				size_t the_size = objects[0]->AmountOfData();
				for(size_t i=1;i<objects.size();++i) {
					if(objects[i]->AmountOfData() != the_size) {
						ArgParseMessageError("You need to pass the same number of arguments for each argument in an inclusive group.\n");
						SetMessage("You need to pass the same number of arguments for each argument in an inclusive group.\n");
						return false;
					}
				}
			}
		} else if (GetType() == ArgObject::Exclusive) {
			//Check for exclusive group
			bool found_non_zero = false;
			for(size_t i=0;i<objects.size(); ++i) {
				if (objects[i]->AmountOfData() > 0) {
					if(found_non_zero) {
						ArgParseMessageError("Only a single argument in an exclusive group may be defined!\n");
						SetMessage("Only a single argument in an exclusive group may be defined!\n");
						return false;
					} else {
						found_non_zero = true;
					}
				}
			}
		}
		return true;
	}
	
	std::string ArgInclusiveGroup::GetHelpText() {
		return GetGroupHelpText("Inclusive");
	}
}
