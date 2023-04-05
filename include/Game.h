#ifndef GAME_H
#define GAME_H

#include <iostream>
#include <string>
#include <algorithm>

#include "olcPixelGameEngine.h"

enum Curve {
    LINE,
    CIRCLE,
    ELLIPSE,
    ROTATED_ELLIPSE,
    QUADRATIC_BEZIER,
    QUADRATIC_RATIONAL_BEZIER,
    CUBIC_BEZIER,
    LAST
};

class Game : public olc::PixelGameEngine {
  public:
    Game() { sAppName = "Bresenham"; }

  private:
    Curve curve;
    std::vector<olc::vi2d> points;

    std::string ToString(Curve _curve) {
        switch (curve) {
        case LINE:
            return "LINE";
        case CIRCLE:
            return "CIRCLE";
        case ELLIPSE:
            return "ELLIPSE";
        case ROTATED_ELLIPSE:
            return "ROTATED_ELLIPSE";
        case QUADRATIC_BEZIER:
            return "QUADRATIC_BEZIER";
        case QUADRATIC_RATIONAL_BEZIER:
            return "QUADRATIC_RATIONAL_BEZIER";
        case CUBIC_BEZIER:
            return "CUBIC_BEZIER";
        }
        return "";
    }

  public:
    bool OnUserCreate() override;
    bool OnUserUpdate(float fElapsedTime) override;
};

#endif // !GAME_H