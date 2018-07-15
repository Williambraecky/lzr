
#include <liblzr.hpp>
#include <effects.hpp>

#include <iostream>

using namespace lzr;

int main(int argc, char* argv[])
{
    (void) argc;
    (void) argv;

    Constant x(1);
    Constant from_a(0);
    Constant from_b(2);
    Constant to_a(0);
    Constant to_b(100);
    LinearMap map;
    map.input_value = x.output_value.make_accessor();
    map.from_a = from_a.output_value.make_accessor();
    map.from_b = from_b.output_value.make_accessor();
    map.to_a = to_a.output_value.make_accessor();
    map.to_b = to_b.output_value.make_accessor();

    Input<float> result = map.output_value.make_accessor();
    
    // this call for data should execute the entire graph
    std::cout << result() << std::endl;

    // FrameEffect frames;
    // frames.frame_number = frame_number.output_value.make_accessor();

    return 0;
}
