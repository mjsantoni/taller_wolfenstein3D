#ifndef WOLFENSTEIN3D_EDITOR_RECENT_POPUP_H
#define WOLFENSTEIN3D_EDITOR_RECENT_POPUP_H

#include <QMainWindow>
#include <QActionGroup>
#include <QLabel>
#include <QGridLayout>
#include <QPushButton>
#include <vector>
#include <QDropEvent>
#include <QDateTime>
#include <QMimeData>
#include <iostream>
#include <fstream>
#include <unordered_map>
#include <QDebug>
#include <QFileDialog>
#include <algorithm>
#include <dirent.h>
#include "ui_recents.h"

class RecentPopup : public QMainWindow {
  std::string& path;
 public:
  explicit RecentPopup(std::string& _path, QMainWindow* parent = 0);
  void showLastModifiedFiles();
  void changeFileToOpen();
  void resetButtons();
  void mousePressEvent(QMouseEvent* event);
};

#endif //WOLFENSTEIN3D_EDITOR_RECENT_POPUP_H
