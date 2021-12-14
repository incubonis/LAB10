#include <QApplication>
#include <QVBoxLayout>
#include <QLabel>
#include <QDateTime>
#include <QWidget>
#include <QPushButton>
#include <QString>
#include <QDir>
int main( int argc, char *argv[ ]){
  QApplication app(argc, argv); 
  QWidget *wdg = new QWidget(); 
  QVBoxLayout *layout = new QVBoxLayout(wdg); 
  QLabel *createdFoldersLabel = new QLabel(""); 
  QLabel *renamedFoldersLabel = new QLabel(""); 
 
  QPushButton *createButton = new QPushButton("createButton"); 
  createButton->setText("CREATE"); 
  QPushButton *renameButton = new QPushButton("renameButton"); 
  renameButton->setText("RENAME"); 
  QPushButton *resetButton = new QPushButton("resetButton"); 
  resetButton->setText("RESET");  
 
    QObject::connect(createButton, &QPushButton::clicked, [&createdFoldersLabel](){ 
    QDir dir("./Test_folders/");     
    if (!dir.exists()) { 
        dir.mkpath("."); 
    } 
    for (int i = 1; i <= 5; i++) { 
        QDir subDir("./Test_folders/"+"Test"+QString::number(i)); 
        if(!subDir.exists()) { 
          subDir.mkpath("."); 
        }; 
    } 
    createdFoldersLabel->setText(FillLabel()); 
  }); 
 
  QObject::connect(renameButton, &QPushButton::clicked, [&renamedFoldersLabel](){ 
    QDir dir("./Test_folders/"); 
    QString date = ""; 
    foreach(QString folder, dir.entryList()){ 
        date = QString::number(QDateTime::currentMSecsSinceEpoch()); 
        dir.rename(folder, folder + date); 
        renamedFoldersLabel->setText(FillLabel());      
    } 
  }); 
 
  QObject::connect(resetButton, &QPushButton::clicked, []() { 
      QDir dir("./Test_folders/"); 
      if (dir.exists()) { 
          foreach(QString folder, dir.entryList()){ 
              QDir subDir("./Test_folders/"+folder); 
              subDir.removeRecursively(); 
          } 
        
      } 
  }); 
 
  layout->addWidget(createdFoldersLabel); 
  layout->addWidget(renamedFoldersLabel); 
  layout->addWidget(createButton); 
  layout->addWidget(renameButton); 
  layout->addWidget(resetButton);  
  wdg->setLayout(layout); 
  wdg->show(); 
  wdg->resize(400, 400); 
 
  return app.exec();
}
