#include "order_book_manager.hpp"
#include <iostream>
#include <fstream>
#include <cstring>

int main (int argc, char *argv[])
{
    if (argc != 3)
    {
        std::cout << "Usage: " << argv[0] << " full|<depth> binary_marketdata_file" << std::endl;
        return EXIT_FAILURE;
    }

    vivcourt::OrderBookManager ob_manager;
    if (::strcmp(argv[1], "full") != 0)
    {
        int report_depth{0};
        try
        {
            report_depth = std::stoi(argv[1]);
            if (report_depth < 0 || report_depth > std::numeric_limits<uint8_t>::max())
            {
                std::cerr << "Invalid program argument: depth=" << report_depth << ", where the desired range is full or [0, "
                          << static_cast<int>(std::numeric_limits<uint8_t>::max()) << "]" << std::endl;
                return EXIT_FAILURE;
            }
        }
        catch (...)
        {
            std::cerr << "Non-integer program argument 'depth'" << std::endl;
            return EXIT_FAILURE;
        }
        ob_manager.SetReportDepth(report_depth);
    }

    std::ifstream md_file(argv[2], std::ios::binary);
    std::vector<char> buffer(std::istreambuf_iterator<char>(md_file), {});
    size_t idx = 0;
    while (idx < buffer.size() - sizeof(vivcourt::messages::Header))
    {
        auto *header = reinterpret_cast<vivcourt::messages::Header*>(&buffer[idx]);
        idx += sizeof(vivcourt::messages::Header);
        if (idx + header->_msg_size.Value() >= buffer.size())
        {
            break; // Imcomplete message.
        }

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

