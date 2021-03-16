#include "machine.h"
#include <iostream>
#include <stdexcept>
#include <string>

using namespace sf;

#define NANOSVG_IMPLEMENTATION
#include "nanosvg.h"

std::vector<std::vector<Complex>> parse_file(const char* filename){
    NSVGimage* image;
    NSVGshape* shape;
    NSVGpath* path;

    std::vector<std::vector<Complex>> points;
    image = nsvgParseFromFile(filename, "px", 96.f);
    if(image == nullptr)
        throw std::runtime_error("Wrong filename");
    for (shape = image->shapes; shape != NULL; shape = shape->next){
		for (path = shape->paths; path != NULL; path = path->next){
            points.push_back(std::vector<Complex>());
            int size = points.size();
            for(int i = 0; i < path->npts; i++)
                points[size-1].push_back({path->pts[2*i], path->pts[2*i+1]});
        }
    }
    return points;
}

int main(int argc, char *argv[]) {
    sf::RenderWindow window(sf::VideoMode(1920, 1080), "Fourier Drawing");
    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;
    char opt;
    bool fancy = false;
    int filter = 200;
    while((opt = getopt(argc, argv, "f")) != -1){
        switch (opt) {
            case 'f':
                fancy = true;
                break;
        }
    }
    try {
        std::vector<Machine> machines;
        auto points = parse_file(argv[optind]);
        for(auto && v : points)
            machines.emplace_back(Machine(v, &window, fancy));
        while (window.isOpen()){
            sf::Event event;
            while (window.pollEvent(event))
                if (event.type == sf::Event::Closed)
                    window.close();
            window.clear();
            for(int i = 0; i < machines.size(); i++){
                machines[i].update_circles();
                if(machines[i].get_length() > 500)
                    machines[i].draw_machine();
                window.draw(&machines[i].path[0], machines[i].path.size(), sf::LineStrip);
            }
            window.display();
        }
    } catch (std::exception &e) {
        std:: cout << "Invalid filename" << std::endl;
    }
    return 0;
}
