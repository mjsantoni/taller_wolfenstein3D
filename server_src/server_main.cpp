#include "server/events/game_handler.h"
#include <unistd.h>
#include "common/network_acceptor.h"
#include "common/network_error.h"
#include "server/server.h"
#include <sys/stat.h>
#include <fstream>
#include <iostream>
#include <unistd.h>

#define STOP_CHAR "q"
#define ARG_PORT 1
#define ARG_AMOUNT 2

int main(int argc, char* argv[]) {

  struct stat sb;
  if (!(stat("../maps", &sb) == 0 && S_ISDIR(sb.st_mode))) {
    if (chdir("/usr/local/share/wolfenstein3d-server/routing") < 0) {
      std::cerr
          << "FATAL ERROR: Game files not found."
          << std::endl;
      return 1;
    }
  }

  if (argc != ARG_AMOUNT) {
    std::cerr << "[Server] Incorrect parameter amount." << std::endl;
    return 1;
  }
  const char* port = argv[ARG_PORT];

  try {
    NetworkAcceptor networkAcceptor(port);
    Server server(std::move(networkAcceptor));
    std::string buffer_stop;
    server.start();
    while (std::getline(std::cin, buffer_stop)) {
      if (buffer_stop == STOP_CHAR) break;
    }
    server.stop();
    server.join();
  } catch (const NetworkError& e) {
    std::cerr << e.what();
  } catch (const std::exception& e) {
    std::cerr << e.what() << std::endl;
  } catch (const YAML::BadFile& e) {
    std::cerr << "Game files not found. " << e.what() << std::endl;
  } catch (...) {
    std::cerr << "Unknown error." << std::endl;
  }
  return 0;
}
