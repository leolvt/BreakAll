#include <sstream>

#include "Util.h"

namespace BreakAll {

// ========================== //

std::string intToStr(int x)
{
    std::stringstream ss;
    ss << x;
    return ss.str();
}

// ========================== //

float measureTextWidth(OGLFT::Face* face, std::string text)
{
    OGLFT::BBox bb = face->measure(text.c_str());
    return bb.x_max_ - bb.x_min_;
}

// ========================== //

float measureTextHeight(OGLFT::Face* face, std::string text)
{
    OGLFT::BBox bb = face->measure(text.c_str());
    return bb.y_max_ - bb.y_min_;
}

// ========================== //

}; //namespace BreakAll
