#include <iostream>
#include <sys/uio.h>
#include <limits.h>
#include <chrono>
#include <unistd.h>
#include <cstdio>

int main()
{
    std::cout << "IOV_MAX: " << IOV_MAX << std::endl;

    char buff[1024];
    char *p1 = &buff[0];   
    char *p2 = &buff[32]; 
    char *p3 = &buff[64]; 
    char *p4 = &buff[128]; 
    char *p5 = &buff[256]; 
    char *p6 = &buff[512];

    auto STDOUT = fileno(stdout);

    auto t1 = std::chrono::high_resolution_clock::now();
    write(STDOUT, p1, 32);
    write(STDOUT, p2, 32);
    write(STDOUT, p3, 64);
    write(STDOUT, p4, 128);
    write(STDOUT, p5, 256);
    write(STDOUT, p6, 512);
    auto t2 = std::chrono::high_resolution_clock::now();
    auto total1 = std::chrono::duration_cast<std::chrono::nanoseconds>(t2 - t1).count();

    struct iovec iov[6];
    iov[0].iov_base = p1;
    iov[0].iov_len = 32;
    iov[1].iov_base = p2;
    iov[1].iov_len = 32;
    iov[2].iov_base = p3;
    iov[2].iov_len = 64;
    iov[3].iov_base = p4;
    iov[3].iov_len = 128;
    iov[4].iov_base = p5;
    iov[4].iov_len = 256;
    iov[5].iov_base = p6;
    iov[5].iov_len = 512;

    auto t3 = std::chrono::high_resolution_clock::now();
    writev(STDOUT, iov, 6);
    auto t4 = std::chrono::high_resolution_clock::now();
    auto total2 = std::chrono::duration_cast<std::chrono::nanoseconds>(t4 - t3).count();

    std::cout << std::endl;
    std::cout << (total1 / 1000000.0) << " nsecs vs "
              << (total2 / 1000000.0) << " nsecs" << std::endl;

    return 0;
}
