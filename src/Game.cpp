#include "Game.h"
#include "bresenham.h"

bool Game::OnUserCreate() {
    curve = LINE;

    return true;
}

bool Game::OnUserUpdate(float fElapsedTime) {
    if (GetKey(olc::ESCAPE).bPressed) {
        return false;
    }
    Clear(olc::BLACK);

    if (GetKey(olc::LEFT).bPressed) {
        if (curve == LINE) {
            curve = LAST;
        }
        curve = (Curve)((int)curve - 1);
    }
    if (GetKey(olc::RIGHT).bPressed) {
        curve = (Curve)((int)curve + 1);
        if (curve == LAST) {
            curve = LINE;
        }
    }

    olc::vi2d mousePos = GetMousePos();
    switch (curve) {
    case LINE:
        if (points.size() > 2) {
            points.erase(points.begin(), points.end() - 1);
        } else if (points.size() == 2) {
            plotLine(this, points[0].x, points[0].y, points[1].x, points[1].y,
                     olc::WHITE);
        } else if (points.size() == 1) {
            plotLine(this, points[0].x, points[0].y, mousePos.x, mousePos.y,
                     olc::WHITE);
        }
        break;
    case CIRCLE:
        if (points.size() > 2) {
            points.erase(points.begin(), points.end() - 1);
        } else if (points.size() == 2) {
            float dist =
                sqrt((points[0].x - points[1].x) * (points[0].x - points[1].x) +
                     (points[0].y - points[1].y) * (points[0].y - points[1].y));
            plotCircle(this, points[0].x, points[0].y, round(dist), olc::WHITE);
        } else if (points.size() == 1) {
            float dist =
                sqrt((points[0].x - mousePos.x) * (points[0].x - mousePos.x) +
                     (points[0].y - mousePos.y) * (points[0].y - mousePos.y));
            plotCircle(this, points[0].x, points[0].y, round(dist), olc::WHITE);
        }
        break;
    case ELLIPSE:
        if (points.size() > 2) {
            points.erase(points.begin(), points.end() - 1);
        } else if (points.size() == 2) {
            plotEllipseRect(this, points[0].x, points[0].y, points[1].x,
                            points[1].y, olc::WHITE);
        } else if (points.size() == 1) {
            plotEllipseRect(this, points[0].x, points[0].y, mousePos.x,
                            mousePos.y, olc::WHITE);
        }
        break;
    case ROTATED_ELLIPSE:
        if (points.size() > 3) {
            points.erase(points.begin(), points.end() - 1);
        } else if (points.size() == 3) {
            float midX = (points[0].x + points[1].x) / 2;
            float midY = (points[0].y + points[1].y) / 2;
            float angle = atan2(points[2].y - midY, points[2].x - midX);
            plotRotatedEllipse(
                this, midX, midY, abs(points[0].x - points[1].x) >> 1,
                abs(points[0].y - points[1].y) >> 1, angle, olc::WHITE);
        } else if (points.size() == 2) {
            float midX = (points[0].x + points[1].x) / 2;
            float midY = (points[0].y + points[1].y) / 2;
            float angle = atan2(mousePos.y - midY, mousePos.x - midX);
            plotRotatedEllipse(
                this, midX, midY, abs(points[0].x - points[1].x) >> 1,
                abs(points[0].y - points[1].y) >> 1, angle, olc::WHITE);
        } else if (points.size() == 1) {
            plotEllipseRect(this, points[0].x, points[0].y, mousePos.x,
                            mousePos.y, olc::WHITE);
        }
        break;
    case QUADRATIC_BEZIER:
        if (points.size() > 3) {
            points.erase(points.begin(), points.end() - 1);
        } else if (points.size() == 3) {
            plotQuadBezier(this, points[0].x, points[0].y, points[1].x,
                           points[1].y, points[2].x, points[2].y, olc::WHITE);
        } else if (points.size() > 0) {
            std::vector<olc::vi2d> p = std::vector<olc::vi2d>(3, mousePos);
            for (int i = 0; i < points.size(); i++) {
                p[i] = points[i];
            }
            plotQuadBezier(this, points[0].x, points[0].y, p[1].x, p[1].y,
                           p[2].x, p[2].y, olc::WHITE);
        }
        break;
    case QUADRATIC_RATIONAL_BEZIER:
        if (points.size() > 4) {
            points.erase(points.begin(), points.end() - 1);
        } else if (points.size() == 4) {
            float w = abs(1 + (points[3].x - points[2].x) / 100);
            plotQuadRationalBezier(this, points[0].x, points[0].y, points[1].x,
                                   points[1].y, points[2].x, points[2].y, w,
                                   olc::WHITE);
        } else if (points.size() > 0) {
            std::vector<olc::vi2d> p = std::vector<olc::vi2d>(3, mousePos);
            float w;
            for (int i = 0; i < points.size(); i++) {
                w = abs(1 + (p[i].x - points[i - 1].x) / 100);
                p[i] = points[i];
            }
            plotQuadRationalBezier(this, points[0].x, points[0].y, p[1].x,
                                   p[1].y, p[2].x, p[2].y, w, olc::WHITE);
        }
        break;
    case CUBIC_BEZIER:
        if (points.size() > 4) {
            points.erase(points.begin(), points.end() - 1);
        } else if (points.size() == 4) {
            plotCubicBezier(this, points[0].x, points[0].y, points[1].x,
                            points[1].y, points[2].x, points[2].y, points[3].x,
                            points[3].y, olc::WHITE);
        } else if (points.size() > 0) {
            std::vector<olc::vi2d> p = std::vector<olc::vi2d>(4, mousePos);
            for (int i = 0; i < points.size(); i++) {
                p[i] = points[i];
            }
            plotCubicBezier(this, points[0].x, points[0].y, p[1].x, p[1].y,
                            p[2].x, p[2].y, p[3].x, p[3].y, olc::WHITE);
        }
        break;
    }

    if (GetMouse(0).bPressed) {
        points.push_back(GetMousePos());
    }
    if (GetKey(olc::BACK).bPressed) {
        points.clear();
    }

    for (olc::vi2d point : points) {
        Draw(point, olc::RED);
    }
    DrawString({ 0, 0 }, ToString(curve), olc::WHITE);

    return true;
}
