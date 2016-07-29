
/*
    Right now, this is mostly just glue that puts an
    etherdream on a ZMQ subscriber socket.
*/

#include <liblzr.h>
#include <zmq.h>
#include <libconfig.h++>

#include "dac.h"

using namespace lzr;
using namespace libconfig;

static void* zmq_ctx;
static void* zmq_sub;
static Frame frame;
static DACList dacs;
static Config cfg;

bool read_config(char* filename)
{
    try
    {
        cfg.readFile(filename);
    }
    catch(const FileIOException& fioex)
    {
        perror("Error reading config file");
        return false;
    }
    catch(const ParseException& pex)
    {
        std::cerr << "Parse error at " << pex.getFile() << ":" << pex.getLine()
                  << " - " << pex.getError() << std::endl;
        return false;
    }

    return true;
}

//main laser client
int main(int argc, char** argv)
{
    init_dacs();
    zmq_ctx = zmq_ctx_new();
    std::vector<DAC*> dacs;

    if(argc == 1)
    {
        //list all dacs
        for(auto name : list_dacs())
            std::cout << name << std::endl;
    }
    else if(argc == 2)
    {
        //load config file
        if(!read_config(argv[1]))
            return EXIT_FAILURE;

        for(const Setting& scanner : cfg.getRoot())
        {
            std::cout << scanner.getName() << std::endl;
            //zmq_sub = frame_sub_new(zmq_ctx, LZRD_GRAPHICS_ENDPOINT);
            DAC* dac = dac_connect(scanner.getName());
            dacs.push_back(dac);
        }
    }

    return(0);

    //enter the main loop
    //-------------------
    // while(1)
    // {
        // recv_frame(zmq_sub, frame);
        // dac->send(frame);
    // }
    //-------------------

    for(DAC* dac : dacs)
        delete dac;

    //zmq_close(zmq_sub);
    zmq_ctx_term(zmq_ctx);

    return 0;
}

