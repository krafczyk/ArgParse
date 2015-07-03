#include "ArgParse/Message.h"
#include "ArgParse/ArgInclusiveGroup.h"

namespace ArgParse {
	ArgInclusiveGroup::ArgInclusiveGroup(const std::string& title, const std::string& help_text, const ArgObject::Mode_t mode, const ArgObject::Req_t required, ArgObjContainer* parent) : ArgGroup(title, help_text, mode, required, parent) {
	}

	bool ArgInclusiveGroup::IsConfigured() const {
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

	size_t ArgInclusiveGroup::AmountOfData() const {
		return objects[0]->AmountOfData();
	}

	bool ArgInclusiveGroup::IsReady() const {
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
		return true;
	}
	
	std::string ArgInclusiveGroup::GetHelpText() const {
		return GetGroupHelpText("Inclusive");
	}
}
