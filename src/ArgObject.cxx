#include "ArgParse/ArgObject.h"

namespace ArgParse {
	const ArgObject::Type_t ArgObject::Bool = 0;
	const ArgObject::Type_t ArgObject::Str = 1;
	const ArgObject::Type_t ArgObject::Char = 2;
	const ArgObject::Type_t ArgObject::UChar = 3;
	const ArgObject::Type_t ArgObject::Short = 4;
	const ArgObject::Type_t ArgObject::UShort = 5;
	const ArgObject::Type_t ArgObject::Int = 6;
	const ArgObject::Type_t ArgObject::UInt = 7;
	const ArgObject::Type_t ArgObject::Long = 8;
	const ArgObject::Type_t ArgObject::ULong = 9;
	const ArgObject::Type_t ArgObject::LongLong = 10;
	const ArgObject::Type_t ArgObject::ULongLong = 11;
	const ArgObject::Type_t ArgObject::Float = 12;
	const ArgObject::Type_t ArgObject::Double = 14;
	const ArgObject::Type_t ArgObject::LongDouble = 15;

	const ArgObject::Type_t ArgObject::Divider = 100;

	const ArgObject::Type_t ArgObject::Normal = 101;
	const ArgObject::Type_t ArgObject::Exclusive = 102;
	const ArgObject::Type_t ArgObject::Inclusive = 103;

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
