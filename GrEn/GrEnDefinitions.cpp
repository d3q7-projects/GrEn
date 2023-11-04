#include "GrEnDefinitions.h"
#define SRGB_MAX 255

GrEn::hexColor GrEn::rgbaToHex(GrEn::rgba color)
{
    GrEn::hexColor hex = static_cast<unsigned int>(color.a * SRGB_MAX);
    hex = hex << 8;
    hex += static_cast<unsigned int>(color.r * SRGB_MAX);
    hex = hex << 8;
    hex += static_cast<unsigned int>(color.g * SRGB_MAX);
    hex = hex << 8;
    hex += static_cast<unsigned int>(color.b * SRGB_MAX);
    
    return hex;
}
