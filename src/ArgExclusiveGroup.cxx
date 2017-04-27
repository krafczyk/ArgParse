/*
ArgParser - C++ Argument Parser reflecting the python module ArgParse.
Copyright (C) 2014-2017  Matthew Scott Krafczyk

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
					ArgParseMessageError("A sub argument(%i) of this container(%s) doesn't have the right mode! All elments must have matching modes. object(%s) versus container(%s)\n", i, this->GetTitle().c_str(), TranslateMode(objects[i]->GetMode()), TranslateMode(GetMode()));
					SetMessage("A sub argument(%i) of this container(%s) doesn't have the right mode! All elments must have matching modes. object(%s) versus container(%s)\n", i, this->GetTitle().c_str(), TranslateMode(objects[i]->GetMode()), TranslateMode(GetMode()));
					return false;
				}
			}
		}
		//Now check for consistency with requirement
		for(size_t i=0; i< objects.size(); ++i) {
			if(objects[i]->GetRequired() != GetRequired()) {
				ArgParseMessageError("A sub argument(%i) of this container(%s) doesn't have the same requirement criteria! object(%i) versus container(%i)\n", i, this->GetTitle().c_str(), TranslateReq(objects[i]->GetRequired()), TranslateReq(GetRequired()));
				SetMessage("A sub argument(%i) of this container(%s) doesn't have the same requirement criteria! object(%i) versus container(%i)\n", i, this->GetTitle().c_str(), TranslateReq(objects[i]->GetRequired()), TranslateReq(GetRequired()));
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
				ArgObject::State_t obj_state = objects[i]->State(true);
				if(obj_state == ArgObject::Ready) {
					num_ready += 1;
				}
			}
			if (num_ready == 0) {
				ArgParseMessageError("No arguments of the required exclusive group (%s) were ready.\n", GetTitle().c_str());
				SetMessage("No arguments of the required exclusive group (%s) were ready.\n", GetTitle().c_str());
				return false;
			}
			if (num_ready != 1) {
				ArgParseMessageError("Only a single argument in the exclusive group (%s) should be defined.\n", GetTitle().c_str());
				SetMessage("Only a single argument in the exclusive group (%s) should be defined.\n", GetTitle().c_str());
				return false;
			}
		} else {
			int num_defined = 0;
			for(size_t i=0; i<objects.size(); ++i) {
				ArgObject::State_t obj_state = objects[i]->State(true);
				if((obj_state == ArgObject::Defined)||(obj_state == ArgObject::Ready)) {
					num_defined += 1;
				}
			}
			if(num_defined > 1) {
				ArgParseMessageError("Only a single argument in the exclusive group (%s) should be defined.\n", GetTitle().c_str());
				SetMessage("Only a single argument in the exclusive group (%s) should be defined.\n", GetTitle().c_str());
				return false;
			}
		}
		return true;
	}
}
