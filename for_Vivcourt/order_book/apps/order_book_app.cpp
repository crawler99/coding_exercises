#include "order_book_manager.hpp"
#include <iostream>
#include <fstream>
#include <cstring>

int main (int argc, char *argv[])
{
    if (argc != 3)
    {
        std::cout << "Usage: " << argv[0] << " depth binary_marketdata_file" << std::endl;
        return EXIT_FAILURE;
    }

    vivcourt::OrderBookManager ob_manager;
    if (::strcmp(argv[1], "full") != 0)
    {
        ob_manager.SetReportDepth(std::stoi(argv[1]));
    }

    std::ifstream md_file(argv[2], std::ios::binary);
    std::vector<char> buffer(std::istreambuf_iterator<char>(md_file), {});
    size_t idx = 0;
    while (idx < buffer.size() - sizeof(vivcourt::messages::Header))
    {
        auto *header = reinterpret_cast<vivcourt::messages::Header*>(&buffer[idx]);
        idx += sizeof(vivcourt::messages::Header);
        std::optional<vivcourt::DepthUpdate> depth_update;
        switch (buffer[idx])
        {
            case 'A':
            {
                depth_update = ob_manager.ProcessOrderAdded(*header, *reinterpret_cast<vivcourt::messages::OrderAdded*>(&buffer[idx]));
                break;
            }
            case 'U':
            {
                depth_update = ob_manager.ProcessOrderUpdated(*header, *reinterpret_cast<vivcourt::messages::OrderUpdated*>(&buffer[idx]));
                break;
            }
            case 'D':
            {
                depth_update = ob_manager.ProcessOrderDeleted(*header, *reinterpret_cast<vivcourt::messages::OrderDeleted*>(&buffer[idx]));
                break;
            }
            case 'E':
            {
                depth_update = ob_manager.ProcessOrderExecuted(*header, *reinterpret_cast<vivcourt::messages::OrderExecuted*>(&buffer[idx]));
                break;
            }
            default:
            ;
        }

        if (depth_update)
        {
            std::cout << *depth_update << std::endl;
        }
        idx += header->_msg_size.Value();
    }

    return EXIT_SUCCESS;
}

