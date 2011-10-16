#ifndef UTIL_H_INCLUDED
#define UTIL_H_INCLUDED

#include <string>

#define OGLFT_NO_SOLID 1
#define OGLFT_NO_QT 1
#include <oglft/OGLFT.h>

namespace BreakAll {

// ========================== //

std::string intToStr(int x);
float measureTextWidth(OGLFT::Face* face, std::string text);
float measureTextHeight(OGLFT::Face* face, std::string text);

// ========================== //

}; // namespace BreakAll

#endif  /* UTIL_H_INCLUDED */

