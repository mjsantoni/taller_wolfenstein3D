#include "editor/recent_popup.h"
#include "editor/editor.h"

#define LAST_FILES_QUANT 4
#define MAP_FOLDER_PATH "../maps/"
#define INTRO_BACKGROUND "../resources/intro_background.png"

RecentPopup::RecentPopup(std::string& _path, QMainWindow* parent) : path(_path), QMainWindow(parent){
    Ui::RecentPopup recent;
    recent.setupUi(this);
    QCommandLinkButton* open_button = findChild<QCommandLinkButton*>("openButton");
    connect(open_button, &QPushButton::clicked, this, &RecentPopup::close);
    this->setStyleSheet("background-image:url(\"../resources/intro_background.png\"); ");
    open_button->setStyleSheet("background-image:url();color:white;font-size:18px");
}

bool cmp(std::pair<const char *, QDateTime> n1, std::pair<const char *, QDateTime> n2) {
    return n1.second < n2.second;
}

void RecentPopup::showLastModifiedFiles() {
    std::vector<std::pair<const char *, QDateTime>> files_names;
    if (auto dir = opendir(MAP_FOLDER_PATH)) {
        while (auto f = readdir(dir)) {
            if (f->d_name[0] == '.')
                continue;
            QFile file(f->d_name);
            QFileInfo file_info;
            file_info.setFile(file);
            QDateTime modified = file_info.lastModified();
            files_names.emplace_back(f->d_name, modified);
        }
        closedir(dir);
    }
    std::sort(files_names.begin(), files_names.end(), cmp);

    QVBoxLayout* recents_layout = findChild<QVBoxLayout*>("recentsLayout");
    QWidget* recents_widget = findChild<QWidget*>("recentsWidget");
    recents_widget->setStyleSheet("background-image:url("");background-color:#48494B;color:white");

    for (int i = 0; i < LAST_FILES_QUANT; ++i) {
        QPushButton* file_button = new QPushButton();
        file_button->setFlat(true);
        file_button->setText(QString(files_names[i].first));
        recents_layout->addWidget(file_button);
        file_button->setCheckable(true);
        file_button->setStyleSheet("background-image:url(""); color:#B9BBB6;");
        connect(file_button, &QPushButton::clicked, this, &RecentPopup::changeFileToOpen);
    }
    recents_widget->show();
}

void RecentPopup::changeFileToOpen() {
    QPushButton* button_sender = qobject_cast<QPushButton*>(sender());
    resetButtons();
    button_sender->setChecked(true);
    QString button_text = button_sender->text();
    path = MAP_FOLDER_PATH + button_text.toStdString();
}

void RecentPopup::resetButtons() {
    QWidget* recents_widget = findChild<QWidget*>("recentsWidget");
    QList<QPushButton*> layout_buttons = recents_widget->findChildren<QPushButton*>();
    for(auto it = layout_buttons.begin(); it != layout_buttons.end(); ++it) {
        (*it)->setChecked(false);
    }
    path = "";
}

void RecentPopup::mousePressEvent(QMouseEvent* event) {
    if (event->button() == Qt::LeftButton) {
        resetButtons();
    }
}