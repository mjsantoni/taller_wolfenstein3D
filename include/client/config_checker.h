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

  ~ConfigChecker();

  /* Connects the buttons with their actions */
  void connectEvents();

  void lookForServer();

  /* Sends the configuration of the game to
   * the server, if an error occurs a error message displays */
  void createNewGame();

  void joinGame();

  /* Returns a valid NetworkConnection for the client to use */
  NetworkConnection getConnection();

  std::string getLineContent(const char* lineName);

  std::string getSpinContent(const char* spinName);

  void hideWidget(const char* widgetName);

  void showWidget(const char* widgetName);

  void showParameters();

  /* Shows the games that are available to join */
  void showIdSelection();

  std::string getComboContent(const char* combo_name);

  QStringList readAllMaps();

  void updateMinSpin();

  /* Displays an error message with the string passed by parameter */
  void showError(const char* string);

  void backToMenu(bool backed_from_connect);

 public slots:

  void updateBotsSpin();

  void updateMaxPlayerMap();

  void updateMaximums();

  void updateSpin(const char* to_update, const char* updater);
};

#endif //TP_WOLFENSTEIN_CONNECTION_CHECKER_H
