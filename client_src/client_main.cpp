#include <QFile>
#include <client/game/client.h>
#include "client/config_checker.h"

int main(int argc, char* args[]) {
  std::string map_name;
  QApplication app(argc, args);
  ConfigChecker checker(map_name);
  QFile file("../client_src/client.qss");
  file.open(QFile::ReadOnly);
  QString styleSheet = QLatin1String(file.readAll());
  app.setStyleSheet(styleSheet);
  checker.show();
  app.exec();
  NetworkConnection sk(std::move(checker.getConnection()));
  app.quit();
  if (map_name.empty()) return 0;
  Client client(sk);
  client.startGame(map_name);
}
