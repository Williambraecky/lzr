
#include "dac.h"
#include "etherdream.h"
#include <unistd.h>


static inline bool starts_with(const std::string& str,
                               const std::string& substr)
{
    return str.compare(0, substr.length(), substr) == 0;
}

static inline void append_dacs(DACList& master, DACList other)
{
    master.insert(master.end(), other.begin(), other.end());
}

void init_dacs()
{
    etherdream_lib_start();
}

DACList list_dacs_inst()
{
    DACList dacs;
    append_dacs(dacs, EtherDream::list_dacs());
    return dacs;
}

DACList list_dacs()
{
    DACList dacs;

    while(dacs.size() == 0)
    {
        sleep(1); //wait for the etherdream lib to see pings from the dacs
        dacs = list_dacs_inst();
    }

    return dacs;
}

DAC* dac_connect(std::string name)
{
    DAC* dac = NULL;

    //instantiate the right connection class
    if(starts_with(name, PREFIX_ETHERDREAM))
    {
        dac = new EtherDream(name);
    }

    //check that we did something worth returning
    if(dac)
    {
        if(dac->success())
            return dac; //success!
        else
            delete dac; //failed: abort
    }

    return NULL;
}



DAC::DAC(std::string name) : _name(name)
{

}

DAC::~DAC()
{

}

std::string DAC::name()
{
    return _name;
}

bool DAC::success()
{
    return _success == 0;
}
