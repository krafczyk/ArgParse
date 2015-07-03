#include "ArgParse/Message.h"
#include "ArgParse/ArgExclusiveGroup.h"

namespace ArgParse {
	ArgExclusiveGroup::ArgExclusiveGroup(const std::string& title, const std::string& help_text, const ArgObject::Mode_t mode, const ArgObject::Req_t required, ArgObjContainer* parent) : ArgGroup(title, help_text, mode, required, parent) {
	}

	bool ArgExclusiveGroup::IsConfigured() const {
		//If any of it's sub objects aren't configured, it isn't configured.
		for(size_t i = 0; i < objects.size(); ++i) {
			if(!objects[i]->IsConfigured()) {
				return false;
			}
		}
		if(GetMode() != ArgObject::None) {
			//Now check for consistency with group mode
			for(size_t i=0; i< objects.size(); ++i) {
				if (objects[i]->GetMode() != GetMode()) {
					ArgParseMessageError("An element of this container doesn't have the right mode! All elments must have matching modes.\n");
					SetMessage("An element of this container doesn't have the right mode! All elments must have matching modes.\n");
					return false;
				}
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

	std::string ArgExclusiveGroup::GetHelpText() const {
		return GetGroupHelpText("Exclusive");
	}

	bool ArgExclusiveGroup::CheckSubObjects() const {
		if(GetRequired()) {
			int num_ready = 0;
			for(size_t i=0; i<objects.size(); ++i) {
				ArgObject::Ready_t isready = objects[i]->IsReady();
				if(isready == ArgObject::Ready) {
					num_ready += 1;
				}
			}
			if (num_ready == 0) {
				ArgParseMessageError("No arguments of the required exclusive group (%s) were ready.\n", GetTitle().c_str());
				return false;
			}
			if (num_ready != 1) {
				ArgParseMessageError("Only a single argument in the exclusive group (%s) should be defined.\n", GetTitle().c_str());
				return false;
			}
		} else {
			int num_defined = 0;
			for(size_t i=0; i<objects.size(); ++i) {
				ArgObject::Ready_t isready = objects[i]->IsReady();
				if((isready == ArgObject::Defined)||(isready == ArgObject::Ready)) {
					num_defined += 1;
					ArgParseMessageError("All sub arguments of the group (%s) must either be defined or not defined.\n", GetTitle().c_str());
				}
			}
			if(num_defined > 1) {
				ArgParseMessageError("Only a single argument in the exclusive group (%s) should be defined.\n", GetTitle().c_str());
				return false;
			}
		}
		return true;
	}
}
