
void init_simple_gain();

namespace rack::plugin {
struct Plugin;
}

__attribute__((__visibility__("default"))) void init(rack::plugin::Plugin *p) {
  // __attribute__((__visibility__("default"))) void init() {
  init_simple_gain();
}
