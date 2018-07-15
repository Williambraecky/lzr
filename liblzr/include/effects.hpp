#pragma once

#include <liblzr.hpp>
#include <node_graph.hpp>

namespace lzr
{

/******************************************************************************/
/*  Numeric Nodes                                                             */
/******************************************************************************/

struct Constant : public Node
{
    Constant(float value = 0)
      : output_value(this)
    {
        output_value(value);
    }

    Output<float> output_value;

    void operator()()
    {
        // noop
    }
};

struct LinearMap : public Node
{
    LinearMap()
      : output_value(this)
    {
    }

    Input<float> input_value;
    Input<float> from_a;
    Input<float> from_b;
    Input<float> to_a;
    Input<float> to_b;

    Output<float> output_value;

    void operator()()
    {
        output_value((input_value() - from_a()) * (to_b() - to_a()) / (from_b() - from_a()) + to_a());
    }
};

/******************************************************************************/
/*  Frame Effects                                                             */
/******************************************************************************/

struct FrameEffect : public Node
{
    FrameEffect()
      : output_frame(this)
    {
    }

    // inputs
    Input<float> frame_number;

    // outputs
    Output<Frame> output_frame;

    void operator()()
    {
        output_frame(frames_[frame_number()]);
    }

private:
    FrameList frames_;
};

struct TranslateEffect : public Node
{
    TranslateEffect()
      : output_frame(this)
    {
    }

    // inputs
    Input<float> x;
    Input<float> y;
    Input<Frame> input_frame;

    // outputs
    Output<Frame> output_frame;

    void operator()()
    {
        // TODO: find a way to prevent this copy (maybe we operate on Frame references?)
        output_frame(input_frame());
        translate(output_frame(), x(), y());
    }
};

}  // end namespace lzr