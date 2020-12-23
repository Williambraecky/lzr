
#include <stdio.h>
#include <lzr.h>


#define POINT_INIT(_x, _y, _r, _g, _b, _i) { .x=_x, .y=_y, .r=_r, .g=_g, .b=_b, .i=_i }


static void print_frame(lzr_frame* frame)
{
    for(size_t i = 0; i < frame->n_points; i++)
    {
        lzr_point p = frame->points[i];
        printf("%zu: (%f, %f)\n", i, p.x, p.y);
    }
}

int main()
{
    lzr_frame frame;

    //                        x,     y,     r, g, b, i
    lzr_point p0 = POINT_INIT(-1.0,  -1.0,  1, 1, 1, 1); frame.points[0] = p0;
    frame.n_points = 1;

    lzr_point offset = POINT_INIT(2.0, 2.0, 0, 0, 0, 0);
    int r = lzr_frame_dup_linear(&frame, offset, 5, false);

    print_frame(&frame);
    printf("frame transformation returned: %d\n", r);
    return 0;
}

