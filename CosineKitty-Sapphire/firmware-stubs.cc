struct NSVGimage;

extern "C" {

NSVGimage *nsvgParseFromFile(const char *filename, const char *, unsigned dpi) {
  return nullptr;
}

void nsvgDelete(NSVGimage *handle) {}

int access(const char *filename, int flag) { return -1; }

struct stat;
int stat(const char *filename, stat *buf) { return -1; }
}

namespace rack::system {
double getTime() { return 0; }
} // namespace rack::system
