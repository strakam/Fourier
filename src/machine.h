#ifndef machine_h
#define machine_h
#include "basics.h"
#include "circle.h"
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Vertex.hpp>

class Machine{
    sf::RenderWindow* window;
    
    // Coefficients for circles
    std::vector<Complex> coefficients_x, coefficients_y;
    std::vector<Circle> circles;
    int N, fader, counter = 0, path_length;
    float pi = 3.14159265358979323846264338327, time = 0, time_increment;
    bool fancy = false;
    // Center of drawing
    Complex center;

    std::vector<Complex> dft(const std::vector<Complex> &v, bool real);
    void make_circles();
public:
    std::vector<sf::Vertex> path;
    std::vector<Complex> pic;
    Machine(const std::vector<Complex> &v, sf::RenderWindow* w, bool fancy);
    void draw_machine();    
    void update_circles();
    void set_drawing_properties();
    void slow_fade();
    void fancy_fade();
    void compute_path_length();
    float get_length();
};

bool comparator(const Circle &a, const Circle &b);

#endif
