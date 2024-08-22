//***********************************************************************************************
// Geodesics: A modular collection for VCV Rack by Pierre Collard and Marc Boulé
//
// Based on code from the Fundamental plugins by Andrew Belt
//  and graphics from the Component Library by Wes Milholen
// See ./LICENSE.txt for all licenses
// See ./res/fonts/ for font licenses
//
//***********************************************************************************************

#include "CountModula.hpp"

Plugin *pluginInstance;
int defaultTheme = 0;
int prevDefaultTheme = -1;

void init(Plugin *p) {
  pluginInstance = p;

  defaultTheme = readDefaultIntegerValue("DefaultTheme");
  prevDefaultTheme = -1;

  p->addModel(modelAnalogueShiftRegister);
  // p->addModel(modelArpeggiator);
  p->addModel(modelAttenuator);
  p->addModel(modelAttenuverter);
  p->addModel(modelBarGraph);
  p->addModel(modelBasicSequencer8);
  p->addModel(modelBinaryComparator);
  p->addModel(modelBinarySequencer);
  // p->addModel(modelBlank12HP);
  // p->addModel(modelBlank16HP);
  // p->addModel(modelBlank20HP);
  // p->addModel(modelBlank24HP);
  // p->addModel(modelBlank2HP);
  // p->addModel(modelBlank4HP);
  // p->addModel(modelBlank8HP);
  p->addModel(modelBooleanAND);
  p->addModel(modelBooleanOR);
  p->addModel(modelBooleanVCNOT);
  p->addModel(modelBooleanXOR);
  p->addModel(modelBreakout);
  p->addModel(modelBurstGenerator);
  p->addModel(modelBurstGenerator64);
  p->addModel(modelBusRoute);
  p->addModel(modelBusRoute2);
  p->addModel(modelCarousel);
  p->addModel(modelChances);
  p->addModel(modelClockDivider);
  // p->addModel(modelClockedRandomGateExpanderCV);
  // p->addModel(modelClockedRandomGateExpanderLog);
  p->addModel(modelClockedRandomGates);
  p->addModel(modelComparator);
  p->addModel(modelCVSpreader);
  p->addModel(modelEuclid);
  // p->addModel(modelEuclidExpanderCV);
  p->addModel(modelEventArranger);
  p->addModel(modelEventTimer);
  p->addModel(modelEventTimer2);
  p->addModel(modelFade);
  // p->addModel(modelFadeExpander);
  p->addModel(modelG2T);
  p->addModel(modelGatedComparator);
  p->addModel(modelGateDelay);
  p->addModel(modelGateDelayMT);
  p->addModel(modelGateModifier);
  p->addModel(modelGateSequencer16);
  p->addModel(modelGateSequencer8);
  // p->addModel(modelHyperManiacalLFO); // compilation error
  // p->addModel(modelHyperManiacalLFOExpander);
  // p->addModel(modelMegalomaniac);
  // p->addModel(modelLightStrip);
  p->addModel(modelMangler);
  p->addModel(modelManifold);
  p->addModel(modelManualCV);
  p->addModel(modelManualCV2);
  p->addModel(modelManualGate);
  p->addModel(modelMasterReset);
  p->addModel(modelMatrixCombiner);
  p->addModel(modelMatrixMixer);
  p->addModel(modelMinimusMaximus);
  p->addModel(modelMixer);
  p->addModel(modelMorphShaper);
  p->addModel(modelMult);
  p->addModel(modelMultiplexer);
  p->addModel(modelMultiStepSequencer);
  p->addModel(modelMute);
  p->addModel(modelMuteIple);
  p->addModel(modelNibbleTriggerSequencer);
  p->addModel(modelOctetTriggerSequencer);
  // p->addModel(modelOctetTriggerSequencerCVExpander);
  // p->addModel(modelOctetTriggerSequencerGateExpander);
  p->addModel(modelOffsetGenerator);
  // p->addModel(modelOscilloscope);
  // p->addModel(modelPalette); //can't find glfw symbols
  p->addModel(modelPolyChances);
  p->addModel(modelPolyG2T);
  p->addModel(modelPolyGateModifier);
  p->addModel(modelPolyLogic);
  p->addModel(modelPolyMinMax);
  p->addModel(modelPolyMute);
  // p->addModel(modelPolyrhythmicGenerator);
  p->addModel(modelPolyrhythmicGeneratorMkII);
  p->addModel(modelPolyVCPolarizer);
  p->addModel(modelPolyVCSwitch);
  // p->addModel(modelRackEarLeft);
  // p->addModel(modelRackEarRight);
  p->addModel(modelRandomAccessSwitch18);
  p->addModel(modelRandomAccessSwitch81);
  p->addModel(modelRectifier);
  p->addModel(modelSampleAndHold);
  p->addModel(modelSampleAndHold2);
  p->addModel(modelSequenceEncoder);
  p->addModel(modelSequencer16);
  p->addModel(modelSequencer64);
  p->addModel(modelSequencer8);
  //    p->addModel(modelSequencerChannel16);
  //    p->addModel(modelSequencerChannel8);
  //    p->addModel(modelSequencerExpanderCV8);
  //    p->addModel(modelSequencerExpanderLog8);
  //    p->addModel(modelSequencerExpanderOut8);
  //    p->addModel(modelSequencerExpanderRM8);
  //    p->addModel(modelSequencerExpanderTrig8);
  //    p->addModel(modelSequencerExpanderTSG);
  //    p->addModel(modelSequencerGates16);
  //    p->addModel(modelSequencerGates8);
  //    p->addModel(modelSequencerTriggers16);
  //    p->addModel(modelSequencerTriggers8);
  p->addModel(modelShepardGenerator);
  p->addModel(modelShiftRegister16);
  p->addModel(modelShiftRegister32);
  p->addModel(modelSingleDFlipFlop);
  p->addModel(modelSingleSRFlipFlop);
  p->addModel(modelSingleTFlipFlop);
  p->addModel(modelSlopeDetector);
  p->addModel(modelSRFlipFlop);
  p->addModel(modelStack);
  p->addModel(modelStartupDelay);
  p->addModel(modelStepSequencer8);
  p->addModel(modelSubHarmonicGenerator);
  p->addModel(modelSwitch16To1);
  p->addModel(modelSwitch1To16);
  p->addModel(modelSwitch1To8);
  p->addModel(modelSwitch2);
  p->addModel(modelSwitch3);
  p->addModel(modelSwitch4);
  p->addModel(modelSwitch8To1);
  p->addModel(modelTFlipFlop);
  p->addModel(modelTriggerSequencer16);
  p->addModel(modelTriggerSequencer8);
  // p->addModel(modelVCFrequencyDivider);
  p->addModel(modelVCFrequencyDividerMkII);
  p->addModel(modelVCPolarizer);
  p->addModel(modelVCPulseDivider);
  p->addModel(modelVoltageControlledSwitch);
  p->addModel(modelVoltageInverter);
  p->addModel(modelVoltageScaler);
}

void setDefaultTheme(int themeToUse, bool previous) {
  if (previous)
    prevDefaultTheme = themeToUse;
  else
    defaultTheme = themeToUse;
}

int getDefaultTheme(bool previous) {
  return previous ? prevDefaultTheme : defaultTheme;
}

// save the given global count modula settings`
void saveSettings(json_t *rootJ) {
  std::string settingsFilename = asset::user("CountModula.json");

  FILE *file = fopen(settingsFilename.c_str(), "w");

  if (file) {
    json_dumpf(rootJ, file, JSON_INDENT(2) | JSON_REAL_PRECISION(9));
    fclose(file);
  }
}

// read the global count modula settings
json_t *readSettings() {
  std::string settingsFilename = asset::user("CountModula.json");
  FILE *file = fopen(settingsFilename.c_str(), "r");

  if (!file) {
    return json_object();
  }

  json_error_t error;
  json_t *rootJ = json_loadf(file, 0, &error);

  fclose(file);
  return rootJ;
}

// read the given default integer value from the global count modula settings
// file
int readDefaultIntegerValue(std::string setting) {
  int value = 0; // default to the standard value

  // read the settings file
  json_t *rootJ = readSettings();

  // get the default value
  json_t *jsonValue = json_object_get(rootJ, setting.c_str());
  if (jsonValue)
    value = json_integer_value(jsonValue);

  // houskeeping
  json_decref(rootJ);

  return value;
}

// save the given integer value in the global count modula settings file
void saveDefaultIntegerValue(std::string setting, int value) {
  // read the settings file
  json_t *rootJ = readSettings();

  // set the default theme value
  json_object_set_new(rootJ, setting.c_str(), json_integer(value));

  // save the updated data
  saveSettings(rootJ);

  // houskeeping
  json_decref(rootJ);
}

// hack for module expanders always to the right
static math::Vec eachNearestGridPosRight(math::Vec pos,
                                         std::function<bool(math::Vec pos)> f) {
  math::Vec leftPos = (pos / RACK_GRID_SIZE).round();
  math::Vec rightPos = leftPos + math::Vec(1, 0);

  while (true) {
    if (f(rightPos * RACK_GRID_SIZE))
      return rightPos * RACK_GRID_SIZE;
    rightPos.x += 1;
  }

  assert(false);
  return math::Vec();
}

// hack for module expanders always to the left
void setModulePosNearestRight(ModuleWidget *mw, math::Vec pos) {
  eachNearestGridPosRight(pos, [&](math::Vec pos) -> bool {
    return APP->scene->rack->requestModulePos(mw, pos);
  });
}

static math::Vec eachNearestGridPosLeft(math::Vec pos,
                                        std::function<bool(math::Vec pos)> f) {
  math::Vec leftPos = (pos / RACK_GRID_SIZE).round();

  while (true) {
    if (f(leftPos * RACK_GRID_SIZE))
      return leftPos * RACK_GRID_SIZE;
    leftPos.x -= 1;
  }

  assert(false);
  return math::Vec();
}

// hack for module expanders always to the left
void setModulePosNearestLeft(ModuleWidget *mw, math::Vec pos) {
  eachNearestGridPosLeft(pos, [&](math::Vec pos) -> bool {
    return APP->scene->rack->requestModulePos(mw, pos);
  });
}
