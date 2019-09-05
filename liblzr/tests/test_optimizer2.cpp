
#include "../src/optimizer2.hpp"

#include <liblzr.hpp>
#include <gtest/gtest.h>
#include <algorithm>

using namespace lzr;


static void print_frame(Frame& frame)
{
    printf("--------------\n");
    for(Point& p : frame)
    {
        printf("(%f, %f, r=%d, g=%d, b=%d, i=%d)\n", p.x, p.y, p.r, p.g, p.b, p.i);
    }
}

static void test_junk()
{
    Frame frame;

    //construct a row of vertical lines

    Frame line;
    //the base line
    line.add(Point(-1.0, 1.0, 255, 255, 255, 255));
    line.add(Point(1.0,  1.0, 255, 255, 255, 255));

    for(int i = 0; i < 5; i++)
    {
        frame.add_with_blank_jump(line);
        translate(line, 0.0, -0.5);
    }

    Optimizer opt(Point(-1.0, 1.0, 255, 255, 255, 255));
    opt.run(frame);

    print_frame(frame);
}

TEST(Optimizer2, LinearPath)
{
    Frame line;
    line.add(Point(0.0, -1.0));
    line.add(Point(0.0, -0.5));
    line.add(Point(0.0, 0.0));
    line.add(Point(0.0, 0.5));
    line.add(Point(0.0, 1.0));

    Path path(line, 0, 4);
    assert(path.size == 5);
    assert(path.first_p == 0);
    assert(path.last_p == 4);
    assert(path.cycle == false);

    assert(path.num_traversals() == 2);

    PathTraversal trav_a = path.traversal(line, 0);
    assert(trav_a.first.p == 0);
    assert(trav_a.last.p == 4);

    PathTraversal trav_b = path.traversal(line, 1);
    assert(trav_b.first.p == 4);
    assert(trav_b.last.p == 0);

    // The forward path
    {
        Frame dest;
        path.traverse(line, 0, dest);
        assert(line == dest);
    }

    // The backwards path
    {
        Frame dest;
        path.traverse(line, 1, dest);
        std::reverse(dest.begin(), dest.end());
        assert(line == dest);
    }
}
