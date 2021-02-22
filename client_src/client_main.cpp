#include <sys/stat.h>
#include <fstream>
#include <iostream>
#include <QFile>
#include <client/game/client.h>
#include "client/config_checker.h"
#include "client_routes.h"

int main(int argc, char* args[]) {

  struct stat sb;
  if (!(stat("../resources", &sb) == 0 && S_ISDIR(sb.st_mode))) {
    if (chdir("/usr/local/share/wolfenstein3d-client/routing") < 0) {
      std::cerr
          << "FATAL ERROR: Game files not found."
          << std::endl;
      return -1;
    }
  }

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
