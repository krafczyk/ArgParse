#include "ArgParse/ArgObject.h"

namespace ArgParse {
	const ArgObject::Mode_t ArgObject::Single = 0;
	const ArgObject::Mode_t ArgObject::Multiple = 1;
	const ArgObject::Mode_t ArgObject::None = -1;

	const ArgObject::Req_t ArgObject::Required = true;
	const ArgObject::Req_t ArgObject::Optional = false;

	const ArgObject::Accept_t ArgObject::No = 0;
	const ArgObject::Accept_t ArgObject::WithSingleArg = 1;
	const ArgObject::Accept_t ArgObject::WithMultipleArg = 4;
	const ArgObject::Accept_t ArgObject::WithoutArg = 2;
	const ArgObject::Accept_t ArgObject::GroupName = 3;

	const ArgObject::Pass_t ArgObject::NotAccepted = 0;
	const ArgObject::Pass_t ArgObject::Accepted = 1;
	const ArgObject::Pass_t ArgObject::Error = -1;

	const ArgObject::State_t ArgObject::NotReady = -1;
	const ArgObject::State_t ArgObject::Defined = 0;
	const ArgObject::State_t ArgObject::NotDefined = 1;
	const ArgObject::State_t ArgObject::Ready = 2;

	ArgObject::~ArgObject() {
	}

	const char* ArgObject::TranslateState(const State_t i) {
		if(i == NotReady) {
			return "NotReady";
		} else if (i == Defined) {
			return "Defined";
		} else if (i == NotDefined) {
			return "NotDefined";
		} else if (i == Ready) {
			return "Ready";
		} else {
			return "Undefined State_t";
		}
	}

	const char* ArgObject::TranslateReq(const Req_t i) {
		if(i == Required) {
			return "Required";
		} else if (i == Optional) {
			return "Optional";
		} else {
			return "Undefined Req_t";
		}
	}

	const char* ArgObject::TranslateAccept(const Accept_t i) {
		if(i == No) {
			return "No";
		} else if (i == WithSingleArg) {
			return "WithSingleArg";
		} else if (i == WithMultipleArg) {
			return "WithMultipleArg";
		} else if (i == WithoutArg) {
			return "WithoutArg";
		} else if (i == GroupName) {
			return "GroupName";
		} else {
			return "Undefined Accept_t";
		}
	}

	const char* ArgObject::TranslateMode(const Mode_t i) {
		if(i == Single) {
			return "Single";
		} else if (i == Multiple) {
			return "Multiple";
		} else if (i == None) {
			return "None";
		} else {
			return "Undefined Mode_t";
		}
	}

	const char* ArgObject::TranslatePass(const Pass_t i) {
		if(i == NotAccepted) {
			return "NotAccepted";
		} else if (i == Accepted) {
			return "Accepted";
		} else if (i == Error) {
			return "Error";
		} else {
			return "Undefined Pass_t";
		}
	}
}
