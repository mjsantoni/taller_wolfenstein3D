#include <sys/stat.h>
#include <fstream>
#include <iostream>
#include <unistd.h>
#include <QFile>
#include <client/game/client.h>
#include "client/config_checker.h"
#include "client_routes.h"

int main(int argc, char* args[]) {
  struct stat sb;
  if (!(stat("../maps", &sb) == 0 && S_ISDIR(sb.st_mode))) {
    if (chdir("/usr/local/share/wolfenstein3d-client/routing") < 0) {
      std::cerr
          << "FATAL ERROR: Game files not found."
          << std::endl;
      return -1;
    }
  }
  try {
    std::string map_name;
    QApplication app(argc, args);
    ConfigChecker checker(map_name);
    QFile file(QSS_PATH);
    file.open(QFile::ReadOnly);
    QString styleSheet = QLatin1String(file.readAll());
    app.setStyleSheet(styleSheet);
    checker.show();
    app.exec();
    NetworkConnection sk(std::move(checker.getConnection()));
    app.quit();
    if (map_name.empty()) return 0;
    std::string config_file = CONFIG_PATH;
    Client client(sk, config_file);
    client.startGame(map_name);
  }
  catch (SdlException& e) {
    std::cerr << "SDL Error: " << e.what() << std::endl;
  }
  catch (YAML::ParserException& e) {
    std::cerr << "Error parsing YAML file: " << e.what() << std::endl;
  }
  catch (NetworkError& e) {
    std::cerr << "Connection error. " << e.what() << std::endl;
  }
  catch (std::exception& e) {
    std::cerr << "Unexpected error: " << e.what() << std::endl;
  }
  catch (...) {
    std::cerr << "Unknown error." << std::endl;
  }
  return 0;
}
