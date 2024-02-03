#include "include/network/listener.hpp"
#include <iostream>
int main(int argc, char *argv[]) {
  if (argc != 4) {
    std::cerr << "Usage: http-server-async <address> <port> <threads>\n"
              << "Example:\n"
              << "    http-server-async 0.0.0.0 8080 . 1\n";
    return EXIT_FAILURE;
  }
  auto const address = net::ip::make_address(argv[1]);
  auto const port = static_cast<unsigned short>(std::atoi(argv[2]));
  auto const threads = std::max<int>(1, std::atoi(argv[3]));
  auto app = std::make_shared<Application>();
  net::io_context ioc{threads};
  std::make_shared<listener>(ioc, tcp::endpoint{address, port}, app)->run();
  std::vector<std::thread> v;
  v.reserve(threads - 1);
  for (auto i = threads - 1; i > 0; --i)
    v.emplace_back([&ioc] { ioc.run(); });
  ioc.run();
  return EXIT_SUCCESS;
}
