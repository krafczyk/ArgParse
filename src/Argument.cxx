/*
ArgParser - C++ Argument Parser reflecting the python module ArgParse.
Copyright (C) 2014-2016  Matthew Scott Krafczyk

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
#include <cerrno>
#include <climits>
#include <cmath>

#include "ArgParse/Argument.h"
#include "ArgParse/Message.h"

namespace ArgParse {
	Argument::Argument(const std::string& call_name, const std::string& help_text, const Req_t required, bool* was_defined) : ArgObject(help_text, required) {
		this->call_names = GetCallNames(call_name);
		if(was_defined == ARGPARSE_NULLPTR) {
			this->defined = new bool;
			this->responsible_for_defined = true;
			*(this->defined) = false;
		} else {
			this->responsible_for_defined = false;
			this->defined = was_defined;
		}
	}

	Argument::~Argument() {
		if(this->responsible_for_defined) {
			delete this->defined;
		}
	}

	std::vector<std::string> Argument::GetCallNames(const std::string& combined_names) {
		std::vector<std::string> answer;
		const size_t buffer_size = combined_names.size()+1;
		char temp_buffer[buffer_size];
		strcpy(temp_buffer, combined_names.c_str());
		char* token = strtok(temp_buffer, "/");
		do {
			if(token == NULL) {
				break;
			}
			if(DebugLevel > 0) {
				MessageStandardPrint("Found name: (%s)\n", token);
			}
			answer.push_back(std::string(token));
			token = strtok(NULL, "/");
		} while (true);
		return answer;
	}

	std::string Argument::GetName(size_t i) const {
		if(call_names.size() > i) {
			return call_names[i];
		} else {
			return "";
		}
	}

	void Argument::PrepareHelpText(std::stringstream& ss) const {
		for(size_t i=0;i<call_names.size();++i) {
			ss << GetName(i) << " ";
			if(i < call_names.size()-1) {
				ss << "/ ";
			}
		}
		ss << ": ";
	}
	
	void Argument::AppendType(std::stringstream& ss) const {
		ss << " Generic Type : ";
	}

	std::string Argument::GetHelpTextWithMessage(const std::string& message) const {
		std::stringstream ss;
		PrepareHelpText(ss);
		ss << message;
		AppendType(ss);
		ss << GetHelp();
		return ss.str();
	}

	std::string Argument::GetHelpText() const {
		return GetHelpTextWithMessage("Takes a generic argument : ");
	}

	bool Argument::DoesAnArgumentMatch(size_t& position, const std::string& arg) const {
		size_t i=0;
		for(;i<call_names.size();++i) {
			if(DebugLevel > 1) {
				MessageStandardPrint("checking if call name (%s) matches.\n", call_names[i].c_str());
			}
			if(DebugLevel > 3) {
				MessageStandardPrint("position: %lu arg: (%s)\n", position, arg.c_str());
			}
			if(arg == call_names[i]) {
				break;
			}
		}
		if (i != call_names.size()) {
			position = i;
			return true;
		} else {
			return false;
		}
	}

	ArgObject::Ready_t Argument::IsReady(bool quiet) const {
		if (IsRequired()) {
			if(!WasDefined()) {
				if (!quiet) {
					ArgParseMessageError("The argument (%s) needs to be defined.\n", GetName().c_str());
					SetMessage("The argument (%s) needs to be defined.\n", GetName().c_str());
				}
				return ArgObject::NotReady;
			} else {
				return ArgObject::Ready;
			}
		} else {
			if (WasDefined()) {
				return ArgObject::Defined;
			} else {
				return ArgObject::NotDefined;
			}
		}
	}
}
