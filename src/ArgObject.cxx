#include "ArgParse/ArgObject.h"

namespace ArgParse {
	const ArgObject::Accept_t ArgObject::No = 0;
	const ArgObject::Accept_t ArgObject::WithArg = 1;
	const ArgObject::Accept_t ArgObject::WithoutArg = 2;
	const ArgObject::Accept_t ArgObject::GroupName = 3;

	const ArgObject::Pass_t ArgObject::NotAccepted = 0;
	const ArgObject::Pass_t ArgObject::Accepted = 1;
	const ArgObject::Pass_t ArgObject::Error = -1;

	ArgObject::ArgObject() {
	}
	
	ArgObject::~ArgObject() {
	}
}
