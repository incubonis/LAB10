#include <QApplication>
#include <QVBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QDir>
#include <QDateTime>
#include <QString>
#include <QWidget>

QString FillLabel();
void sleep(int s);

int main(int argc, char *argv[ ])
{
  QApplication app(argc, argv);
  QWidget *wdg = new QWidget();
  QVBoxLayout *layout = new QVBoxLayout(wdg);
  QLabel *createdFoldersHint = new QLabel("Created folders");
  QLabel *createdFoldersLabel = new QLabel("");
  QLabel *renamedFoldersHint = new QLabel("Renamed folders");
  QLabel *renamedFoldersLabel = new QLabel("");

  QPushButton *createButton = new QPushButton("createButton");
  createButton->setText("CREATE");


  QString const MAIN_PATH("./Test_folders/");

  QObject::connect(createButton, &QPushButton::clicked, [&createdFoldersLabel, &MAIN_PATH](){
    QDir dir(MAIN_PATH);
    dir.setFilter(QDir::AllDirs | QDir::NoDot | QDir::NoDotDot);
    if (!dir.exists()) {
        dir.mkpath(".");
    }
    for (int i = 1; i <= 5; i++) {
        QDir subDir(MAIN_PATH+"Test"+QString::number(i));
        if(!subDir.exists()) {
          subDir.mkpath(".");
        };
    }
    createdFoldersLabel->setText(FillLabel());
  });

  QObject::connect(renameButton, &QPushButton::clicked, [&renamedFoldersLabel, &MAIN_PATH](){
    QDir dir(MAIN_PATH);
    dir.setFilter(QDir::AllDirs | QDir::NoDot | QDir::NoDotDot);
    QString date = "";
    foreach(QString folder, dir.entryList()){
        date = QString::number(QDateTime::currentMSecsSinceEpoch());
        dir.rename(folder, folder + date);
        renamedFoldersLabel->setText(FillLabel());
        sleep(3);
    }
  });

  QObject::connect(resetButton, &QPushButton::clicked, [&createdFoldersLabel, &renamedFoldersLabel, &MAIN_PATH]() {
      QDir dir(MAIN_PATH);
      if (dir.exists()) {
          foreach(QString folder, dir.entryList()){
              QDir subDir(MAIN_PATH+folder);
              subDir.removeRecursively();
          }
          createdFoldersLabel->setText("Folders were deleted!");
          renamedFoldersLabel->setText("Folders were deleted!");
      }
  });

  QObject::connect(removeButton, &QPushButton::clicked, [&createdFoldersLabel, &renamedFoldersLabel, &MAIN_PATH]() {
      QDir dir(MAIN_PATH);
      if (dir.exists()) {
          dir.removeRecursively();
          createdFoldersLabel->setText("Folders were deleted!");
          renamedFoldersLabel->setText("Folders were deleted!");
      }
  });

  layout->addWidget(createdFoldersHint);
  layout->addWidget(createdFoldersLabel);
  layout->addWidget(renamedFoldersHint);
  layout->addWidget(renamedFoldersLabel);
  layout->addWidget(createButton);
  layout->addWidget(renameButton);
  layout->addWidget(resetButton);
  layout->addWidget(removeButton);

  wdg->setLayout(layout);
  wdg->show();
  wdg->resize(400, 400);

  return app.exec();
}

QString FillLabel(){
    QString folders="";
    QDir dir("./Test_folders");
    dir.setFilter(QDir::AllDirs | QDir::NoDot | QDir::NoDotDot);

    foreach(QString folderName, dir.entryList()){
        folders += " "+folderName;
    }
    return folders;
}

void sleep(int s){
    QTime dieTime= QTime::currentTime().addSecs(s);
    while (QTime::currentTime() < dieTime)
        QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
}
