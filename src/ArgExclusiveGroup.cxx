#include "ArgParse/Message.h"
#include "ArgParse/ArgExclusiveGroup.h"

namespace ArgParse {
	ArgExclusiveGroup::ArgExclusiveGroup(const std::string& title, const std::string& help_text, const ArgObject::Mode_t mode, const ArgObject::Req_t required, ArgObjContainer* parent) : ArgGroup(title, help_text, mode, required, parent) {
	}

	bool ArgExclusiveGroup::IsConfigured() {
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
		//Now check for consistency with group mode
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
		return true;
	}

	bool ArgExclusiveGroup::IsReady() {
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
		return true;
	}
	
	std::string ArgExclusiveGroup::GetHelpText() {
		return GetGroupHelpText("Exclusive");
	}
}
