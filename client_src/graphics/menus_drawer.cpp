//
// Created by andy on 31/1/21.
//

#include <zconf.h>
#include "client/graphics/menus_drawer.h"
#include "client_routes.h"

MenusDrawer::MenusDrawer(SdlWindow& _window) : window(_window) {
  window_width = window.getWidth();
  window_height = window.getHeight();
  match_mode_new_game_area = Area(window_width / 8, window_height / 8,
                                  window_width / 6, window_height / 8);
  match_mode_join_game_area = Area(6 * window_width / 8, window_height / 8,
                                   window_width / 6, window_height / 8);
  level_selection_easy =
      Area(window_width / 2 - window_width / 4, 4 * window_height / 10,
           window_width / 2, window_height / 10);
  level_selection_medium =
      Area(window_width / 2 - window_width / 4, 6 * window_height / 10,
           window_width / 2, window_height / 10);
  level_selection_hard =
      Area(window_width / 2 - window_width / 4, 8 * window_height / 10,
           window_width / 2, window_height / 10);
}

void MenusDrawer::displayIntro() {
  SdlTexture intro_tex(window, CLIENT_MENUS_ROUTE + std::string("intro.jpg"));
  displayFullImage(intro_tex);
  std::string message_text = "PRESS ANY KEY TO CONTINUE";
  Area screen_area(3 * window_width / 8, 5 * window_height / 6, window_width / 2,
                   window_height / 10);
  Area msg_area;
  MessageParameters msg_parms(message_text, "POLOBM__.TTF", 35);
  renderMessage(message_text, msg_area, screen_area, msg_parms);
  window.render();
}

void MenusDrawer::displayFullImage(SdlTexture& texture) {
  Area dest_area(0, 0, window_width, window_height);
  texture.render(dest_area);
}

void MenusDrawer::renderMessage(const std::string& message_text,
                                Area& msg_area,
                                Area& screen_area,
                                MessageParameters message_parameters) {
  SdlMessage message(message_parameters);
  message.renderMessage(window, msg_area, screen_area);
}

void MenusDrawer::renderMessage(const std::string& message_text,
                                Area& msg_area,
                                Area& screen_area) {
  MessageParameters message_parameters(message_text);
  SdlMessage message(message_parameters);
  message.renderMessage(window, msg_area, screen_area);
}

std::vector<Area> MenusDrawer::getKeyAreas() {
  return std::vector<Area>{match_mode_new_game_area,
                           match_mode_join_game_area,
                           level_selection_easy,
                           level_selection_medium,
                           level_selection_hard
  };
}

void MenusDrawer::displayLoadingScreen(bool waiting_for_input) {
  SdlTexture menu_tex(window, CLIENT_MENUS_ROUTE
      + std::string("loading_screen.png"));
  displayFullImage(menu_tex);
  Area screen_area(5 * window_width / 8, 3 * window_height / 4, 5 * window_width / 16,
                   window_height / 6);
  std::string message_text = "Press 'P' when ready";
  if (!waiting_for_input) {
    screen_area = Area(5 * window_width / 8, 3 * window_height / 4, window_width / 4,
                       window_height / 6);
    message_text = "Loading...";
  }
  Area msg_area;
  MessageParameters msg_parms(message_text, "Snowstorm Kraft.ttf", 35);
  renderMessage(message_text, msg_area, screen_area, msg_parms);
  window.render();
}

void MenusDrawer::displayRespawningScreen() {
  Area screen_area(0, 0, window_width, window_height);
  window.drawRectangle(screen_area, 255, 0, 0, 0);
  std::string message_text = "DEAD! RESPAWNING";
  screen_area = Area(window_width / 4, window_height / 4, window_width / 2,
                     window_height / 4);
  Area msg_area;
  SDL_Color color_black{0, 0, 0};
  MessageParameters message_parameters(color_black, message_text,
                                       "Action_Force.ttf", 50);
  renderMessage(message_text, msg_area, screen_area, message_parameters);
  window.render();
}

void MenusDrawer::displayDeadScreen() {
  Area screen_area(0, 0, window_width, window_height);
  window.drawRectangle(screen_area, 0, 0, 0, 0);
  std::string message_text = "DEAD! NO COMING BACK THIS TIME";
  screen_area = Area(window_width / 8, window_height / 4, 3 * window_width / 4,
                     window_height / 4);
  Area msg_area;
  MessageParameters message_parameters(message_text,
                                       "Action_Force.ttf", 40);
  renderMessage(message_text, msg_area, screen_area, message_parameters);
  window.render();
}

void MenusDrawer::displayNetworkConnectingErrorScreen() {
  Area screen_area(0, 0, window_width, window_height);
  window.drawRectangle(screen_area, 0, 0, 0, 0);
  std::string message_text = "ERROR WHILE CONNECTING TO THE SERVER: EXITING";
  screen_area = Area(window_width / 4, window_height / 3, window_width/2,
                     window_height / 6);
  Area msg_area;
  SDL_Color gray_color{224, 224, 224};
  MessageParameters message_parameters(gray_color, message_text,
                                       "BabelSans.ttf", 30);
  renderMessage(message_text, msg_area, screen_area, message_parameters);
  window.render();
}

void MenusDrawer::displayStatistics(std::vector<std::vector<int>> statistics) {
  std::vector<int> top_killers = statistics[0];
  std::vector<int> top_shooters = statistics[1];
  std::vector<int> top_scorers = statistics[2];
  std::vector<int> top_killers_stats = statistics[3];
  std::vector<int> top_shooters_stats = statistics[4];
  std::vector<int> top_scorers_stats = statistics[5];
  Area screen_area(0, 0, window_width, window_height);
  window.drawRectangle(screen_area, 0, 0, 0, 0);
  if (top_killers.empty() && top_scorers.empty() && top_shooters.empty()) {
    displayEmptyStatisticsScreen();
    window.render();
    return;
  }
  displayStatisticsHeaders();
  displayTopKillers(top_killers, top_killers_stats);
  displayTopShooters(top_shooters, top_shooters_stats);
  displayTopScorers(top_scorers, top_scorers_stats);
  window.render();
}

void MenusDrawer::displayEmptyStatisticsScreen() {
  std::string message_text = "NO STATS TO SHOW";
  Area screen_area = Area(window_width / 4, window_height / 4, window_width / 2,
                          window_height / 4);
  Area msg_area;
  MessageParameters message_parameters(message_text,
                                       "Action_Force.ttf", 50);
  renderMessage(message_text, msg_area, screen_area, message_parameters);
}

void MenusDrawer::displayStatisticsHeaders() {
  std::string top_killer_header = "TOP KILLERS";
  std::string top_shooter_header = "TOP SHOOTERS";
  std::string top_scorer_header = "TOP SCORERS";
  Area header_area_1;
  Area header_area_2;
  Area header_area_3;
  Area screen_area_1 = Area(window_width / 10, 0, window_width / 5,
                            window_height / 12);
  Area screen_area_2 = Area(4*window_width/10, 0, window_width / 5,
                            window_height / 12);
  Area screen_area_3 = Area(7 * window_width / 10, 0,
                            window_width / 5, window_height / 12);
  renderMessage(top_killer_header, header_area_1, screen_area_1);
  renderMessage(top_shooter_header, header_area_2, screen_area_2);
  renderMessage(top_scorer_header, header_area_3, screen_area_3);
}

void MenusDrawer::displayVictoryScreen() {
  SdlTexture menu_tex(window, CLIENT_MENUS_ROUTE +
      std::string("victory_screen.jpg"));
  displayFullImage(menu_tex);
  Area screen_area(3 * window_width / 8, 3 * window_height / 4, window_width / 4,
                   window_height / 6);
  std::string message_text = "VICTORY";
  MessageParameters msg_parms(message_text, "vikingsquadboldital.ttf", 75);
  Area msg_area;
  renderMessage(message_text, msg_area, screen_area, msg_parms);
  window.render();
}

void MenusDrawer::displayTopKillers(std::vector<int> top_killers,
                                    std::vector<int> top_killers_stats) {
  for (int i = 0; i < top_killers.size(); ++i) {
    std::string msg_text = "Player " + std::to_string(top_killers[i]) +
        ": " + std::to_string(top_killers_stats[i]);
    Area msg_area;
    Area screen_area = Area(window_width / 10, (2 + 2 * i) * window_height / 12,
                            window_width / 5, window_height / 12);
    renderMessage(msg_text, msg_area, screen_area);
  }
}

void MenusDrawer::displayTopShooters(std::vector<int> top_shooters,
                                     std::vector<int> top_shooters_stats) {
  for (int i = 0; i < top_shooters.size(); ++i) {
    std::string msg_text = "Player " + std::to_string(top_shooters[i]) +
        ": " + std::to_string(top_shooters_stats[i]);
    Area msg_area;
    Area screen_area = Area(4* window_width/10, (2 + 2 * i) * window_height/ 12,
                            window_width / 5, window_height / 12);
    renderMessage(msg_text, msg_area, screen_area);
  }
}

void MenusDrawer::displayTopScorers(std::vector<int> top_scorers,
                                    std::vector<int> top_scorers_stats) {
  for (int i = 0; i < top_scorers.size(); ++i) {
    std::string msg_text = "Player " + std::to_string(top_scorers[i]) +
        ": " + std::to_string(top_scorers_stats[i]);
    Area msg_area;
    Area screen_area = Area(7 * window_width/10, (2 + 2 * i) * window_height/12,
                            window_width / 5, window_height / 12);
    renderMessage(msg_text, msg_area, screen_area);
  }
}

void MenusDrawer::displayDefeatScreen() {
  SdlTexture menu_tex(window, CLIENT_MENUS_ROUTE +
      std::string("defeat_screen.jpg"));
  displayFullImage(menu_tex);
  Area screen_area(3 * window_width / 8, 3 * window_height / 4, window_width / 4,
                   window_height / 6);
  window.render();
}

void MenusDrawer::displayTimeOverScreen() {
  Area screen_area(0, 0, window_width, window_height);
  window.drawRectangle(screen_area, 255, 255, 255, 0);
  std::string message_text = "TIME OVER! IT'S A TIE!";
  screen_area = Area(window_width / 4, window_height / 4, window_width / 2,
                     window_height / 4);
  Area msg_area;
  SDL_Color color_black{0, 0, 0};
  MessageParameters message_parameters(color_black, message_text,
                                       "Action_Force.ttf", 50);
  renderMessage(message_text, msg_area, screen_area, message_parameters);
  window.render();
}
