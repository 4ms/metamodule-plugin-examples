#include "plugin.hpp"
#include <thread>

Plugin *pluginInstance;

void init(Plugin *p) {
  pluginInstance = p;

  // Add modules here
  p->addModel(modelChowTape); // takes up to 95% load!
  p->addModel(modelChowPhaserFeedback);
  p->addModel(modelChowPhaserMod);
  // p->addModel(modelChowFDN); //  uses too much iostreams
  // p->addModel(modelChowRNN); // loads but crashes on run
  p->addModel(modelChowModal);
  p->addModel(modelChowDer);
  p->addModel(modelWarp);
  p->addModel(modelWerner);
  // p->addModel(modelCredit);
  p->addModel(modelChowPulse);
  p->addModel(modelChowTapeCompression);
  p->addModel(modelChowTapeChew);
  p->addModel(modelChowTapeDegrade);
  p->addModel(modelChowTapeLoss);
  // p->addModel(modelChowChorus); // loads but crashes on run

  // Any other plugin initialization may go here.
  // As an alternative, consider lazy-loading assets and lookup tables when your
  // module is created to reduce startup times of Rack.
}

void createScrews(ModuleWidget &mw) {
  mw.addChild(createWidget<ScrewBlack>(Vec(0, 0)));
  mw.addChild(createWidget<ScrewBlack>(Vec(mw.box.size.x - 15, 0)));
  mw.addChild(
      createWidget<ScrewBlack>(Vec(0, RACK_GRID_HEIGHT - RACK_GRID_WIDTH)));
  mw.addChild(createWidget<ScrewBlack>(
      Vec(mw.box.size.x - 15, RACK_GRID_HEIGHT - RACK_GRID_WIDTH)));
}

void addPubToMenu(Menu *menu, const std::string &pub) {
  // struct PublicationItem : MenuItem {
  //     std::string pub = "";

  // void onAction(const event::Action& e) override {
  // std::thread t(system::openBrowser, pub);
  // t.detach();
  // }
  // };

  // menu->addChild(construct<PublicationItem>(&MenuItem::text, "Publication",
  // &PublicationItem::pub, pub));
}
