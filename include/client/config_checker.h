#ifndef TP_WOLFENSTEIN_CONFIG_CHECKER_H
#define TP_WOLFENSTEIN_CONFIG_CHECKER_H

#include <iostream>
#include <dirent.h>
#include <QMainWindow>
#include <QApplication>
#include <QSpinBox>
#include <QComboBox>
#include <common/map_parser.h>
#include <common/network_connection.h>
#include <common/network_error.h>


/*Class that extends a window from QT making an intro/configuration of the game*/
class ConfigChecker : public QMainWindow {

  std::string& map_data;
  NetworkConnection sk;
  bool backed_join = false;
  bool backed_create = false;
 public:

  explicit ConfigChecker(std::string& _map_data, QMainWindow* parent = 0);

  void connectEvents();

  void lookForServer();

  void createNewGame();

  void joinGame();

  std::string getLineContent(const char* lineName);

  std::string getSpinContent(const char* spinName);

  void hideWidget(const char* widgetName);

  void showWidget(const char* widgetName);

  void showParameters();

  void showIdSelection();

  std::string getComboContent(const char* combo_name);

  QStringList readAllMaps();

  void updateMinSpin();

  void showError(const char* string);

  void backToMenu(bool backed_from_connect);

  NetworkConnection getConnection();

 public slots:

  void updateBotsSpin();

  void updateMaxPlayerMap();

  void updateMaximums();

  void updateSpin(const char* to_update, const char* updater);
};

#endif //TP_WOLFENSTEIN_CONNECTION_CHECKER_H
