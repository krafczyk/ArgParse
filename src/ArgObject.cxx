#include "ArgParse/ArgObject.h"

namespace ArgParse {
	const ArgObject::Accept_t ArgObject::No = 0;
	const ArgObject::Accept_t ArgObject::WithArg = 1;
	const ArgObject::Accept_t ArgObject::WithoutArg = 2;

	ArgObject::ArgObject() {
	}
	
	ArgObject::~ArgObject() {
	}
}
