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

#include <sstream>

#include "ArgParse/Message.h"
#include "ArgParse/ArgGroup.h"

namespace ArgParse {
	bool ArgGroup::IsConfigured() const {
		//If any of it's sub objects aren't configured, it isn't configured.
		for(size_t i = 0; i < objects.size(); ++i) {
			if(!objects[i]->IsConfigured()) {
				return false;
			}
		}
		return true;
	}

	size_t ArgGroup::AmountOfData() const {
		for(size_t i=0;i<objects.size();++i) {
			size_t amount = objects[i]->AmountOfData();
			if(amount != 0) {
				return amount;
			}
		}
		return 0;
	}

	ArgObject::Accept_t ArgGroup::AcceptsArgument(const std::string& arg) const {
		if (DebugLevel > 5) {
			ArgParseMessageDebug("Checking if we accept an argument\n");
		}
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

	ArgObject::Pass_t ArgGroup::PassArgument(const std::string& arg, const std::string& opt, const bool with_opt) {
		for(size_t i=0; i < this->objects.size(); ++i) {
			ArgObject::Pass_t passed = this->objects[i]->PassArgument(arg, opt, with_opt);
			if(passed != ArgObject::NotAccepted) {
				return passed;
			}
		}
		return ArgObject::NotAccepted;
	}

	ArgObject::Ready_t ArgGroup::IsReady(bool quiet __attribute__((unused))) const {
		//Check that everybody is ready.
		if(!CheckSubObjects()) {
			return ArgObject::NotReady;
		}
		//Check that the data is consistent
		if(!CheckDataConsistency()) {
			return ArgObject::NotReady;
		}
		return ArgObject::Ready;
	}

	std::string ArgGroup::GetGroupHelpText(const std::string& name) const {
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

	std::string ArgGroup::GetHelpText() const {
		return GetGroupHelpText("");
	}

	bool ArgGroup::CheckSubObjects() const {
		for(size_t i=0; i<objects.size(); ++i) {
			Ready_t ready = objects[i]->IsReady();
			if(ready == ArgObject::NotReady) {
				ArgParseMessageError("A sub argument(%i) of the group (%s) wasn't ready. (%s)\n", i, GetTitle().c_str(), ArgObject::TranslateReady(ready));
				SetMessage("A sub argument(%i) of the group (%s) wasn't ready. (%s)\n", i, GetTitle().c_str(), ArgObject::TranslateReady(ready));
				return false;
			}
		}
		return true;
	}

	bool ArgGroup::CheckDataConsistency() const {
		return true;
	}
}
