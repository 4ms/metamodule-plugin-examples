
#include "BaconPlugs.hpp"

Plugin *pluginInstance;

void init(Plugin *p) {
  pluginInstance = p;

  p->addModel(modelGlissinator);
  p->addModel(modelHarMoNee);
  p->addModel(modelQuantEyes);
  p->addModel(modelLuckyHold);
  p->addModel(modelSampleDelay);
  p->addModel(modelPolyGnome);
}
