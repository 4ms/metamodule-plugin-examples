#include "CoreModules/register_module.hh"
#include "simple_vca.hh"

extern "C" void init() {
	MetaModule::register_module<SimpleVCA, SimpleVCAInfo>("NativeExample");
}
