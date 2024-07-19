#include "doctest.h"
#include <cmath>
#include <iostream>
#include <string>

bool _string2float(const char *txt, float &f) {
  char *pEnd = nullptr;
  float v = std::strtof(txt, &pEnd);
  if (pEnd == txt) {
    return false;
  } else if (v != INFINITY && v != -INFINITY &&
             (v == HUGE_VALF || v == -HUGE_VALF)) {
    return false;
  } else {
    f = v;
    return true;
  }
}

bool string2dBNorm(const char *txt, float &f) {
  auto s = std::string(txt);
  if (s.find("-inf") != std::string::npos) {
    f = 0;
    return true;
  }

  if (auto ok = _string2float(txt, f)) {
    f = std::pow(10, f / 20);
    return true;
  }
  return false;
}

bool Xstring2dBNorm(const char *txt, float &f) {
  auto s = std::string(txt);
  if (s.find("-inf") != std::string::npos) {
    f = 0;
    return true;
  }

  try {
    float v = std::stof(txt);
    f = std::pow(10, v / 20);
    return true;
  } catch (const std::exception &e) {

    return false;
  }
  return false;
}

TEST_CASE("Compare throwing and non-throwing versions of string2dBNorm") {

  auto check = [](const char *txt, bool expect_match) {
    // std::cout << "\"" << txt << "\"" << "\n";

    float f = 999;
    auto ok = string2dBNorm(txt, f);
    float Xf = 999;
    auto Xok = Xstring2dBNorm(txt, Xf);

    if (expect_match) {
      CHECK(ok == Xok);

      // NANs are always non-equal, so check if they are both NAN
      if (!std::isnan(f) && !std::isnan(Xf))
        CHECK(f == Xf);
      else
        CHECK(std::isnan(f) == std::isnan(Xf));

    } else {
      CHECK_FALSE(ok == Xok);
      CHECK_FALSE(f == Xf);
    }

    // if (ok)
    //   std::cout << "  " << f << "\n";
    // else
    //   std::cout << "  FAIL "
    //             << "\n";

    // if (Xok)
    //   std::cout << "  " << Xf << "\n";
    // else
    //   std::cout << "  FAIL "
    //             << "\n";

    // std::cout << "\n";
  };

  check("3.14", true);
  check("asdfasdff", true);
  check("9.111 33.222", true);
  check("inf", true);
  check("+inf", true);
  check("-inf", true);
  check("NaN", true);
  check("+0", true);
  check("-0.0", true);

  // 0 vs FAIL
  check("0.0000000000000000000000000000000000000000000001", false);

  // 1.4e-45 vs FAIL
  check("0.000000000000000000000000000000000000000000001", false);

  //+1e-38 vs FAIL
  check("0.00000000000000000000000000000000000001", false);

  // 1e-37
  check("0.0000000000000000000000000000000000001", true);

  //-0 vs FAIL
  check("-0.0000000000000000000000000000000000000000000001", false);

  //-1.4e-45 vs FAIL
  check("-0.000000000000000000000000000000000000000000001", false);

  //-1e-38 vs FAIL
  check("-0.00000000000000000000000000000000000001", false);

  // -1e-37
  check("-0.0000000000000000000000000000000000001", true);

  // inf vs FAIL
  check("1000000000000000000000000000000000000001", false);

  // 1e+38
  check("100000000000000000000000000000000000001", true);

  //-inf vs FAIL
  check("-1000000000000000000000000000000000000001", false);

  // -1e+38
  check("-100000000000000000000000000000000000001", true);
}
