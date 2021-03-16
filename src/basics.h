#ifndef headers
#define headers
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/PrimitiveType.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/VertexArray.hpp>
#include <SFML/System/Vector2.hpp>
#include <cmath>
#include <math.h>
#include <utility>
#include <vector>
#include "nanosvg.h"
#include <getopt.h>


struct Complex{
    float re, im;
    Complex(float r, float i): re(r), im(i){}
    Complex(){}
};

#endif
