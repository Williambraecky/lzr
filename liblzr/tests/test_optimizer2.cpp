
#include "../src/optimizer2.hpp"

#include <liblzr.hpp>
#include <gtest/gtest.h>
#include <algorithm>

namespace lzr
{

void print_frame(Frame& frame)
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

TEST(Optimizer2, PointByOffset)
{
    Frame line;
    line.add(Point(0.0, -1.0));
    line.add(Point(0.0, 0.0));
    line.add(Point(0.0, 1.0));

    Path path(line, 0, 2);

    EXPECT_EQ(path.point_by_offset(0), 0);
    EXPECT_EQ(path.point_by_offset(1), 1);
    EXPECT_EQ(path.point_by_offset(2), 2);

    // should loop across the front and the back
    EXPECT_EQ(path.point_by_offset(3), 0);
    EXPECT_EQ(path.point_by_offset(-1), 2);
}

TEST(Optimizer2, SinglePoint)
{
    Frame single_point;
    single_point.add(Point(0.0, 0.0));

    Path path(single_point, 0, 0);
    EXPECT_EQ(path.size, 1);
    EXPECT_EQ(path.first_p, 0);
    EXPECT_EQ(path.last_p, 0);
    EXPECT_EQ(path.cycle, false);

    EXPECT_EQ(path.num_traversals(), 1);

    PathTraversal trav = path.traversal(single_point, 0);
    EXPECT_EQ(trav.first.p, 0);
    EXPECT_EQ(trav.last.p, 0);

    // The forward path
    {
        Frame dest;
        path.traverse(single_point, 0, dest);
        EXPECT_EQ(single_point, dest);
    }
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
    EXPECT_EQ(path.size, 5);
    EXPECT_EQ(path.first_p, 0);
    EXPECT_EQ(path.last_p, 4);
    EXPECT_EQ(path.cycle, false);

    EXPECT_EQ(path.num_traversals(), 2);

    // The forward path
    {
        PathTraversal trav = path.traversal(line, 0);
        EXPECT_EQ(trav.first.p, 0);
        EXPECT_EQ(trav.last.p, 4);

        Frame dest;
        path.traverse(line, 0, dest);
        EXPECT_EQ(line, dest);
    }

    // The backwards path
    {
        PathTraversal trav = path.traversal(line, 1);
        EXPECT_EQ(trav.first.p, 4);
        EXPECT_EQ(trav.last.p, 0);

        Frame dest;
        path.traverse(line, 1, dest);
        std::reverse(dest.begin(), dest.end());
        EXPECT_EQ(line, dest);
    }
}

TEST(Optimizer2, Cycle)
{
    Frame triangle;
    triangle.add(Point(-1.0, -1.0));
    triangle.add(Point(0.0, 1.0));
    triangle.add(Point(1.0, -1.0));
    triangle.add(Point(-1.0, -1.0));

    Path path(triangle, 0, 3);
    EXPECT_EQ(path.size, 4);
    EXPECT_EQ(path.first_p, 0);
    EXPECT_EQ(path.last_p, 3);
    EXPECT_EQ(path.cycle, true);

    EXPECT_EQ(path.num_traversals(), 6);  // 3 corners, 2 directions

    {
        // first point, forward direction
        PathTraversal trav = path.traversal(triangle, 0);
        EXPECT_EQ(trav.first.p, 0);
        EXPECT_EQ(trav.last.p, 3);
    }
}
}  // namespace lzr