#pragma once
#include <string>

#if !(defined(__EXCEPTIONS) || defined(__cpp_exceptions) || defined(_CPPUNWIND) || defined(CMRC_NO_EXCEPTIONS))
#define CMRC_NO_EXCEPTIONS 1
#endif

// clang-format off
namespace cmrc { namespace detail { struct dummy; } }

#define CMRC_DECLARE(libid) \
    namespace cmrc { namespace detail { \
    struct dummy; \
    static_assert(std::is_same<dummy, ::cmrc::detail::dummy>::value, "CMRC_DECLARE() must only appear at the global namespace"); \
    } } \
    namespace cmrc { namespace libid { \
	} } static_assert(true, "")

// clang-format on

namespace cmrc
{

struct fs {
	bool is_file(std::string) {
		return false;
	}

	std::string open(std::string) {
		return "";
	}
};

namespace awdoc_resources
{
fs get_filesystem() {
	return fs{};
}
} // namespace awdoc_resources
} // namespace cmrc
