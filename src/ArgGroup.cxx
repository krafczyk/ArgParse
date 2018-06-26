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
		for(size_t i=0; i<objects.size(); ++i) {
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

	ArgObject::State_t ArgGroup::State(bool quiet __attribute__((unused))) const {
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
		if(DebugLevel > 5) {
			ArgParseMessageDebug("There are %lu objects in this group.\n", this->objects.size());
		}
		for(size_t i=0; i< this->objects.size(); ++i) {
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
			State_t ready = objects[i]->State();
			if(ready == ArgObject::NotReady) {
				ArgParseMessageError("A sub argument(%i) of the group (%s) wasn't ready. (%s)\n", i, GetTitle().c_str(), ArgObject::TranslateState(ready));
				SetMessage("A sub argument(%i) of the group (%s) wasn't ready. (%s)\n", i, GetTitle().c_str(), ArgObject::TranslateState(ready));
				return false;
			}
		}
		return true;
	}

	bool ArgGroup::CheckDataConsistency() const {
		return true;
	}
}
