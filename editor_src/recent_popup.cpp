#include "editor/recent_popup.h"
#include "editor/editor.h"

#define LAST_FILES_QUANT 4
#define MAP_FOLDER_PATH "../maps/"
#define INTRO_BACKGROUND "../resources/intro_background.jpg"

RecentPopup::RecentPopup(std::string& _path, QMainWindow* parent) : path(_path), QMainWindow(parent){
    Ui::RecentPopup recent;
    recent.setupUi(this);
    QCommandLinkButton* open_button = findChild<QCommandLinkButton*>("openButton");
    connect(open_button, &QPushButton::clicked, this, &RecentPopup::close);
    this->setStyleSheet("background-image:url(\"../resources/intro_background.png\"); ");
}

bool cmp(std::pair<const char *, QDateTime> n1, std::pair<const char *, QDateTime> n2) { return n1.second > n2.second; };

void RecentPopup::showLastModifiedFiles() {
    std::unordered_map<const char *, QDateTime> files_names;
    if (auto dir = opendir(MAP_FOLDER_PATH)) {
        while (auto f = readdir(dir)) {
            if (f->d_name[0] == '.')
                continue;
            QFile file(f->d_name);
            QFileInfo file_info;
            file_info.setFile(file);
            QDateTime created = file_info.lastModified();
            files_names[f->d_name] = created;
            qDebug(f->d_name);
        }
        closedir(dir);
    }
    std::vector<const char *> last_files_names;
    std::vector<std::pair<const char *, QDateTime>> sorted;
    for (auto& elem : files_names) sorted.emplace_back(elem);
    std::sort(sorted.begin(), sorted.end(), cmp);

    QVBoxLayout* recents_layout = findChild<QVBoxLayout*>("recentsLayout");
    QWidget* recents_widget = findChild<QWidget*>("recentsWidget");
    recents_widget->setStyleSheet("background-image:url("");background-color:#5C241F; ");

    for (int i = 0; i < LAST_FILES_QUANT; ++i) {
        qDebug(sorted[i].first);
        QPushButton* file_button = new QPushButton();
        file_button->setFlat(true);
        file_button->setText(QString(sorted[i].first));
        recents_layout->addWidget(file_button);
        file_button->setCheckable(true);
        file_button->setStyleSheet("background-image:url("");");
        connect(file_button, &QPushButton::clicked, this, &RecentPopup::changeFileToOpen);
    }
    recents_widget->show();
}

void RecentPopup::changeFileToOpen() {
    QPushButton* button_sender = qobject_cast<QPushButton*>(sender());
    QString button_text = button_sender->text();
    path = MAP_FOLDER_PATH + button_text.toStdString();

}
