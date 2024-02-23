#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <string.h>
#include <QColor>

namespace Constants {
inline constexpr int windowWidth{600};
inline constexpr int windowHeight{450};
inline const std::string supportedExtensions {"mp4 mkv mov mkv avi"};
inline const std::string supportedExtensionsExt{"mp4 (*.mp4);; mkv (*.mkv);; mov (*.mov);; mkv (*.mkv);; avi (*.avi)"};
inline const QColor focusedColor{"#E9F1F9"};
inline const int sliderMaxValue{99};
}

#endif
