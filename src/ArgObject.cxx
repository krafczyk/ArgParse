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

	ArgObject::~ArgObject() {
	}
}
