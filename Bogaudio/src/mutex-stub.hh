#pragma once

#ifndef METAMODULE_BUILTIN

namespace std
{

struct mutex {
	void lock() {
	}
	void unlock() {
	}
};

} // namespace std

#endif
