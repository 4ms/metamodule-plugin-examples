#include "Valley.hpp"

// The pluginInstance-wide instance of the Plugin class
Plugin *pluginInstance;

void init(rack::Plugin *p) {
  pluginInstance = p;

  p->addModel(modelInterzone);
  p->addModel(modelAmalgam);
  p->addModel(modelFeline);

  // These are internal plugins to the MetaModule:
  // p->addModel(modelTopograph);
  // p->addModel(modelUGraph);
  // p->addModel(modelPlateau);

  // These don't work yet
  // p->addModel(modelDexter);
  // p->addModel(modelTerrorform);
}
