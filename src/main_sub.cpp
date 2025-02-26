#include <ToFDataSubscriber.hpp>

int main()
{
    std::cout << "Starting subscriber. Press any key to stop it." << std::endl;

    ToFDataSubscriber mysub;
    mysub.init();
    mysub.set_listener(mysub.reader_);

    getchar();

    return 0;
}
