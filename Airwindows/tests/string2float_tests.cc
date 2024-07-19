#include "doctest.h"
#include <cmath>
#include <cstdlib>
#include <iostream>
#include <string>

bool string2float(const char *txt, float &f);

bool Xstring2float(const char *txt, float &f) {
  try {
    float v = std::stof(txt);
    f = v;
    return true;
  } catch (const std::exception &e) {
    return false;
  }
}

TEST_CASE("Compare throwing and non-throwing string2float") {

  auto check = [](const char *txt, bool expect_match) {
    // std::cout << "\"" << txt << "\""
    //           << "\n";
    float f = 999;
    auto ok = string2float(txt, f);
    float Xf = 999;
    auto Xok = Xstring2float(txt, Xf);

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
    //   std::cout << "  FAIL " << "\n";

    // if (Xok)
    //   std::cout << "  " << Xf << "\n";
    // else
    //   std::cout << "  FAIL " << "\n";

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

  // Summary:
  // Small numbers within about 1e-45 < abs(x) < 1e-38 work with the
  // non-throwing version but fail on the throwing version.
  //
  // Small numbers abs(x) < 1e-45 return 0 with the
  // non-throwing version but fail on the throwing version.
  //
  // Large numbers return +/- inf on the non-throwing version and fail on the
  // throwing version ... but "inf" does not fail on either version
}
