#include "parser.h"
#include "integrator.h"
#include "timer.h"

#include <iostream>
#include <iomanip>

int main(int argc, char *argv[])
{
    fst::Timer timer;
    fst::Timer total_timer;

    total_timer.start();
    timer.start();
    parser::Scene scene;
    scene.loadFromXml(argv[1]);
    //scene okumak, xml'i komple parselayıp scene'e veriyor
    std::cout << std::fixed << std::showpoint << std::setprecision(5);
    std::cout << "loadFromXml    : " << timer.getTime() << " seconds" << std::endl;

    timer.start();
    fst::Integrator integrator(scene);
    //Scene objesini oluşturutor
    std::cout << "loadFromParser : " << timer.getTime() << " seconds" << std::endl;

    timer.start();
    integrator.integrate();
    //
    std::cout << "Traversal      : " << timer.getTime() << " seconds" << std::endl;
    std::cout << std::endl << "Total          : " << total_timer.getTime() << " seconds" << std::endl;

    return 0;
}
