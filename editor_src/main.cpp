#include "editor/editor.h"
#include "editor/recent_popup.h"
#include "editor_routes.h"
#include <unistd.h>
#include <sys/stat.h>

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
  QFile file_main(EDITOR_MAIN_QSS);
  file_main.open(QFile::ReadOnly);
  QString style_sheet_main = QLatin1String(file_main.readAll());
  file_main.close();

    std::string path;
    RecentPopup popup(path);
    popup.showLastModifiedFiles();
    popup.show();
    app.exec();
    app.setStyleSheet(style_sheet_main);
    Editor editor(path);
    editor.show();
    app.exec();

  return 0;
}

