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
		if(GetMode() != ArgObject::None) {
			//Now check for consistency with group mode
			for(size_t i=0; i< objects.size(); ++i) {
				Mode_t the_mode = objects[i]->GetMode();
				if (the_mode != GetMode()) {
					ArgParseMessageError("A sub argument(%i) of this container(%s) doesn't have the right mode! All elments must have matching modes. object(%s) versus container(%s)\n", i, this->GetTitle().c_str(), TranslateMode(the_mode), TranslateMode(GetMode()));
					SetMessage("A sub argument(%i) of this container(%s) doesn't have the right mode! All elments must have matching modes. object(%s) versus container(%s)\n", i, this->GetTitle().c_str(), TranslateMode(the_mode), TranslateMode(GetMode()));
					return false;
				}
			}
		}
		//Now check for consistency with requirement
		for(size_t i=0; i< objects.size(); ++i) {
			if(objects[i]->GetRequired() != GetRequired()) {
				ArgParseMessageError("A sub argument(%i) of this container(%s) doesn't have the same requirement criteria! object(%s) versus container(%s)\n", i, this->GetTitle().c_str(), TranslateReq(objects[i]->GetRequired()), TranslateReq(GetRequired()));
				SetMessage("A sub argument(%i) of this container(%s) doesn't have the same requirement criteria! object(%s) versus container(%s)\n", i, this->GetTitle().c_str(), TranslateReq(objects[i]->GetRequired()), TranslateReq(GetRequired()));
				return false;
			}
		}
		return true;
	}

	size_t ArgInclusiveGroup::AmountOfData() const {
		return objects[0]->AmountOfData();
	}

	std::string ArgInclusiveGroup::GetHelpText() const {
		return GetGroupHelpText("Inclusive");
	}

	bool ArgInclusiveGroup::CheckSubObjects() const {
		if(GetRequired()) {
			for(size_t i=0; i<objects.size(); ++i) {
				ArgObject::State_t obj_state = objects[i]->State(true);
				if(obj_state != ArgObject::Ready) {
					ArgParseMessageError("A sub argument(%i) of the group (%s) wasn't ready. (%s)\n", i, GetTitle().c_str(), TranslateState(obj_state));
					SetMessage("A sub argument(%i) of the group (%s) wasn't ready. (%s)\n", i, GetTitle().c_str(), TranslateState(obj_state));
					return false;
				}
			}
		} else {
			ArgObject::State_t obj_state = objects[0]->State(true);
			bool defined = false;
			if((obj_state == ArgObject::Defined)||(obj_state == ArgObject::Ready)) {
				defined = true;
			}
			for(size_t i=1; i<objects.size(); ++i) {
				obj_state = objects[i]->State(true);
				if (defined) {
					if((obj_state == ArgObject::NotDefined)||(obj_state == ArgObject::NotReady)) {
						ArgParseMessageError("All sub arguments of the group (%s) must either be defined or not defined. (%s)\n", GetTitle().c_str(), TranslateState(obj_state));
						SetMessage("All sub arguments of the group (%s) must either be defined or not defined. (%s)\n", GetTitle().c_str(), TranslateState(obj_state));
						return false;
					}
				} else {
					if((obj_state == ArgObject::Defined)||(obj_state == ArgObject::Ready)) {
						ArgParseMessageError("All sub arguments of the group (%s) must either be defined or not defined. (%s)\n", GetTitle().c_str(), TranslateState(obj_state));
						SetMessage("All sub arguments of the group (%s) must either be defined or not defined. (%s)\n", GetTitle().c_str(), TranslateState(obj_state));
						return false;
					}
				}
			}
		}
		return true;
	}

	bool ArgInclusiveGroup::CheckDataConsistency() const {
		if((GetMode() == ArgObject::Multiple)||(GetMode() == ArgObject::Single)) {
			//Check that everybody has the same amount of data.
			size_t the_size = objects[0]->AmountOfData();
			for(size_t i=1; i<objects.size(); ++i) {
				if(objects[i]->AmountOfData() != the_size) {
					ArgParseMessageError("You need to pass the same number of arguments for each argument in an inclusive group.\n");
					SetMessage("You need to pass the same number of arguments for each argument in an inclusive group.\n");
					return false;
				}
			}
		}
		return true;
	}
}
