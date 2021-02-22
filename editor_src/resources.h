#ifndef TP_WOLFENSTEIN_RESOURCES_H
#define TP_WOLFENSTEIN_RESOURCES_H

#include <unordered_map>
#include <QPixmap>
#include <QAction>

class Resources {
  std::unordered_map<std::string, QPixmap*> pixmaps;
  std::unordered_map<std::string, QIcon*> icons;
  std::unordered_map<std::string, QAction*> actions;
 public:
  Resources();
  QPixmap* getPixmap(std::string resource_name);
  QIcon* getIcon(std::string resource_name);
  QAction* getAction(std::string resource_name);
};

#endif //TP_WOLFENSTEIN_RESOURCES_H
