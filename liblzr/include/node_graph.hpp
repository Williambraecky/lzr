#pragma once

#include <memory>

namespace lzr
{

// fwd-decl
template <typename T>
class Output;

class Node
{
public:
    /**
     * The required execute function for a node. This function will automatically be called
     * whenever another node requests one of our outputs. This function should also be
     * resiliant to multiple calls with the same inputs.
     */
    virtual void operator()()=0;
};

/**
 * Generic value accessor that can be created as a token from any node. Serves
 * as the linkage between nodes, and is trivially assignable. Hold these as members
 * of your Node subclass, and assign them with the values returned by 
 */
template <typename T>
class Input
{
public:
    Input()
      : output_(nullptr)
    {
    }

    Input(Output<T>* output)
      : output_(output)
    {
    }

    const T& operator()()
    {
        return output_->execute();
    }

private:
    Output<T>* output_;
};

/**
 * Output class. Should be held as a member of a Node, where "value" is used as it's output
 * data. The make_accessor() function can be called to connect this output to any number of
 * Inputs.
 */
template <typename T>
class Output
{
public:
    /**
     * Constructor takes an argument to the Node that has this output. This allows
     * the loaned-out Inputs to request this node to execute, and update it's outputs.
     */
    Output(Node* node)
      : node_(node)
    {
    }

    // setter and getter
    void operator()(const T& value)
    {
        value_ = value;
    }

    T& operator()()
    {
        return value_;
    }

    /**
     * Call this function to construct a pre-configured ValueAccessor object that
     * knows how to execute the descendant tree.
     */
    Input<T> make_accessor()
    {
        return Input<T>(this);
    }

private:

    // allow ValueAccessors to execute us.
    friend class Input<T>;
    const T& execute()
    {
        // call the node's execute function, to update "value".
        (*node_)();
        return value_;
    }

    // The actual value stored and used by the Node. The node may edit this value
    // only during it's execute function (operator()).
    T value_;

    // The Node of which we are a member
    Node* node_;
};

}  // end namespace lzr