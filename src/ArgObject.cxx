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

#include "ArgParse/ArgObject.h"

namespace ArgParse {
	const ArgObject::Mode_t ArgObject::Single = 0;
	const ArgObject::Mode_t ArgObject::Multiple = 1;
	const ArgObject::Mode_t ArgObject::None = -1;

	const ArgObject::Req_t ArgObject::Required = true;
	const ArgObject::Req_t ArgObject::Optional = false;

	const ArgObject::Accept_t ArgObject::No = 0;
	const ArgObject::Accept_t ArgObject::WithArg = 1;
	const ArgObject::Accept_t ArgObject::WithoutArg = 2;
	const ArgObject::Accept_t ArgObject::GroupName = 3;

	const ArgObject::Pass_t ArgObject::NotAccepted = 0;
	const ArgObject::Pass_t ArgObject::Accepted = 1;
	const ArgObject::Pass_t ArgObject::Error = -1;

	const ArgObject::Ready_t ArgObject::NotReady = -1;
	const ArgObject::Ready_t ArgObject::Defined = 0;
	const ArgObject::Ready_t ArgObject::NotDefined = 1;
	const ArgObject::Ready_t ArgObject::Ready = 2;

	ArgObject::~ArgObject() {
	}
}
