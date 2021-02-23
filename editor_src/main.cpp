#include <QApplication>
#include "editor/editor.h"
#include "editor/recent_popup.h"
#include <QDebug>
#include <QStyle>
#include <QStyleFactory>
#include <sys/stat.h>
#include <fstream>
#include <iostream>
#include <unistd.h>
#include "editor_routes.h"

int main(int argc, char* args[]) {
    struct stat sb;
    if (!(stat("../maps", &sb) == 0 && S_ISDIR(sb.st_mode))) {
        if (chdir("/usr/local/share/wolfenstein3d-editor/routing") < 0) {
            std::cerr
                    << "FATAL ERROR: Game files not found."
                    << std::endl;
            return -1;
        }
    }

  QApplication app(argc, args);
  QFile file(EDITOR_QSS);
  file.open(QFile::ReadOnly);
  QString styleSheet = QLatin1String(file.readAll());

  app.setStyleSheet(styleSheet);
  std::string path;
  RecentPopup popup(path);
  popup.showLastModifiedFiles();
    popup.show();
    app.exec();
    Editor editor(path);
    editor.show();
    app.exec();

  return 0;
}

