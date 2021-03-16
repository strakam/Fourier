#ifndef circle_h
#define circle_h
#include "basics.h"
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <cmath>
#include <math.h>

class Circle{
public:
    float radius, freq, phase;
    Complex center, tip;
    sf::CircleShape circle, tip_circle;
    Circle(Complex num, float frequency, float rotation);
    Circle(){}

    Complex update(float time, Complex position);
    void draw(sf::RenderWindow* w);
    void draw_tip(sf::RenderWindow* w);
};

#endif
