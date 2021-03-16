#include <math.h>
#include "circle.h"

/*
 * Input - position of a center of a circle in complex number format, frequency
 * and phase
 */
Circle::Circle(Complex num, float frequency, float rotation) : freq(frequency){
    radius = sqrt(num.re*num.re + num.im*num.im);
    phase = std::atan2(num.im, num.re) + rotation;
    circle.setRadius(radius);
    circle.setFillColor(sf::Color(255,255,255,0));
    circle.setOutlineThickness(0.7);
    tip_circle.setRadius(2);
    if(rotation)
        circle.setOutlineColor(sf::Color(255,255,255,50));
    else
        circle.setOutlineColor(sf::Color(179,212,242,50));
}

// Computes rotation of a circle according to a given time
Complex Circle::update(float time, Complex position){
    center.re = position.re;
    center.im = position.im;
    tip.re = center.re + radius*cos(time*freq + phase);
    tip.im = center.im + radius*sin(time*freq + phase);
    return tip;
};

// Render circles with frequency greater than 0
void Circle::draw(sf::RenderWindow* w){
    if(!freq) return;
    circle.setPosition(center.re - radius, center.im - radius);
    w->draw(circle);
}

// Draw line of a circle and its tip
void Circle::draw_tip(sf::RenderWindow *w){
    if(!freq) return;
    tip_circle.setPosition(tip.re-1, tip.im-1);
    w->draw(tip_circle);
    sf::Vertex line[] = { sf::Vertex(sf::Vector2f(center.re, center.im)),
                          sf::Vertex(sf::Vector2f(tip.re, tip.im)) };
    w->draw(line, 2, sf::Lines);
}
