#include <SFML/Graphics/RenderWindow.hpp>
#include "circle.h"
#include "machine.h"

/*
 * Constructor of DFT machine.
 * It runs DFT on data samples and produces parameters for circles
 */
Machine::Machine(const std::vector<Complex>& points, sf::RenderWindow* w, bool fancy) 
    :fancy(fancy), center(300, 300){
    window = w;
    N = points.size();
    time_increment = 2*pi/N;
    fader = std::max(1, 2*N/255);
    coefficients_x = dft(points, true);
    coefficients_y = dft(points, false);
    make_circles();
    compute_path_length();
}

/* Discrete fourier transform calculator
 * Input - samples of picture in complex number format
 *       - boolean telling whether real or imaginary part is computed
 * Output - vector of complex numbers representing coefficients for circles
 */
std::vector<Complex> Machine::dft(const std::vector<Complex> &v, bool real){
    std::vector<Complex> coeffs;
    for(int n = 0; n < N; n++){
        float re = 0, im = 0; 
        for(int k = 0; k < N; k++){
            float v_k = (real)? v[k].re : v[k].im;
            float arg = 2*pi*k*n/N;
            re += v_k * cos(arg);
            im -= v_k * sin(arg);
        }
        re /= N;
        im /= N;
        coeffs.push_back({re, im});
    }
    return coeffs;
}

bool comparator(const Circle &a, const Circle &b){
    return a.radius > b.radius;
}

// Create circles from coefficients and sort them by radius
void Machine::make_circles(){
    for(int i = 0; i < N; i++){
        circles.emplace_back(Circle(coefficients_x[i], i, 0));
        circles.emplace_back(Circle(coefficients_y[i], i, pi/2));
    }
    sort(circles.begin(), circles.end(), comparator);
}

// Draw circles
void Machine::draw_machine(){
    // Only first N are drawn
    for(int i = 0; i < N; i++)
        circles[i].draw(window);
    for(int i = 0; i < N; i++)
        circles[i].draw_tip(window);
}

// Update positions of circles
void Machine::update_circles(){
    Complex position = center;
    for(int i = 0; i < 2*N; i++)
        position = circles[i].update(time, position);
    path.push_back({sf::Vector2f(circles[2*N-1].tip.re, circles[2*N-1].tip.im), sf::Color(255,142,122,255)});
    // Fade
    if(fancy) fancy_fade();
    else slow_fade();
    if(time > 2*pi)
        time = 0;
    // Cleanup transparent vertices
    if(path.size() > 4*N){
        std::vector<sf::Vertex> t;
        for(int i = 2*N; i < path.size(); i++)
            t.push_back(path[i]);
        path = t;
    }
    time += time_increment;
}

// "Chasing tail" fade style
void Machine::slow_fade(){
    if(counter % fader == 0)
        for(auto && v : path)
            if(v.color.a > 0)
                v.color.a -= 1;
    counter++;
}

// Fancy fade
void Machine::fancy_fade(){
    for(auto && v : path)
        v.color.a -= 1;
}

// Compute path length to filter short trajectories
void Machine::compute_path_length(){
    Complex position = center;
    float t = 0;
    while(t < 2*pi){
        for(int i = 0; i < 2*N; i++)
            position = circles[i].update(time, position);
        path_length++;
        t += time_increment;
    }
}

// Getter for path length
float Machine::get_length(){
    return path_length;
}
