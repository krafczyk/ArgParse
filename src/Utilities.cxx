#include <cstring>

#include "ArgParse/Utilities.h"

namespace ArgParse {
	const char* basename(const char* filename) {
		const char* p = strrchr(filename, '/');
		return p ? p + 1 : filename;
	}
}
