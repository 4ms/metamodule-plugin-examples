//***********************************************************************************************
// Geodesics: A modular collection for VCV Rack by Pierre Collard and Marc Boulé
//
// Based on code from the Fundamental plugins by Andrew Belt
//  and graphics from the Component Library by Wes Milholen
// See ./LICENSE.txt for all licenses
// See ./res/fonts/ for font licenses
//
//***********************************************************************************************

#include "plugin.hpp"

Plugin *pluginInstance;

void init(Plugin *p) {
  pluginInstance = p;

  p->addModel(modelFence);
  p->addModel(modelSwing);
  p->addModel(modelMother);
  p->addModel(modelPhrase);
  p->addModel(modelDejavu);
  p->addModel(modelGator);
  p->addModel(modelResc);
  p->addModel(modelMorph);
  p->addModel(modelMorpheus);
}
