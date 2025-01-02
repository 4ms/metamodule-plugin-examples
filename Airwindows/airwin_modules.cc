#include "module_creator.hh"

namespace MetaModuleAirwindows
{
std::vector<ModuleCreator> modules;
}

extern "C" void init() {
	AirwinConsolidatedBase::defaultSampleRate = 48000;

	for (unsigned reg_idx = 0; auto module : AirwinRegistry::registry) {
		MetaModuleAirwindows::modules.emplace_back(reg_idx);
		reg_idx++;
	}
}
