#include <QApplication>
#include <QMainWindow>
#include <QLabel>
#include <QTime>
#include <QTimer>
#include <QDate>
#include <QPushButton>
#include <QComboBox>
#include <QStackedWidget>

int main(int argc, char* argv[]) {
  int howmuchtime = 3;
  QApplication app(argc, argv);
  app.setStyle("Fusion");
  QMainWindow win;
  QStackedWidget* sw = new QStackedWidget(&win);
  win.setCentralWidget(sw);
  win.resize(1024, 900);
  win.setWindowTitle("Timerr");
  win.setStyleSheet("QMainWindow {background-color: #1e1e2e}");

  QWidget* gt = new QWidget();
  QWidget* second = new QWidget();
  sw->addWidget(gt);
  sw->addWidget(second);
  sw->setCurrentWidget(gt);

  QLabel* lab = new QLabel(gt);
  QLabel* dat = new QLabel(gt);
  QTimer* timer = new QTimer(gt);
  QPushButton* b = new QPushButton(gt);
  QPushButton* ch = new QPushButton(gt);
  QPushButton* cha = new QPushButton(gt);
  QPushButton* cha1 = new QPushButton(second);
  QComboBox* cb = new QComboBox(gt);
  bool isRunning = 1, theme = 1, c = 0;

  lab->resize(450, 120);
  lab->move((win.width() - 450)/2, (win.height() - 120)/2 - 200);
  lab->setStyleSheet("QLabel {font-family: 'Times new Roman'; font-size: 96px; color: #1e1e2e; background-color: #f5f5f5; border: 1px solid #3498db; border-radius: 10px; padding: 20px 20px;}");
  lab->setText(QDateTime::currentDateTimeUtc().addSecs((howmuchtime - 7)*3600).time().toString("hh:mm:ss"));
  
  b->setText("stop/continue");
  b->resize(100, 50);
  b->move((1024 - 100)/2, (900 - 50)/2 - 25);
  b->setStyleSheet("QPushButton{background-color: #4361ee; border-radius: 10px;} QPushButton:hover {background-color: #3a56e4;} QPushButton:pressed {background-color: #2d46b9;}");
  
  ch->setText("change theme");
  ch->resize(100, 25);
  ch->move(win.width() - 100, 0);
  
  dat->setText(QDate::currentDate().toString("d MMMM yyyy"));
  dat->resize(200, 100);
  dat->move((win.width() - 200)/2, (win.height() - 100)/2 - 120);
  dat->setStyleSheet("QLabel {font-family: 'Times new Roman'; font-size: 32px; color: #ffffff}");
  
  cha->move(win.width() - 75, win.height() - 25);
  cha->setText("switch");
  cha->resize(75, 25);
  
  cb->addItem("Лондон, UTC+0");
  cb->addItem("Париж, UTC+1");
  cb->addItem("Калининград, UTC+2");  
  cb->addItem("Москва, UTC+3");
  cb->addItem("Самара, UTC+4");
  cb->addItem("Екатеринбург, UTC+5");
  cb->addItem("Омск, UTC+6");
  cb->addItem("Красноярск, UTC+7");  
  cb->addItem("Иркутск, UTC+8");
  cb->addItem("Якутск, UTC+9");
  cb->addItem("Владивосток, UTC+10");
  cb->addItem("Сахалин, UTC+11");
  cb->addItem("США, UTC-12");
  cb->addItem("Ниуэ, UTC-11");
  cb->addItem("Гонолулу, UTC-10");
  cb->addItem("Анкоридж, UTC-9");
  cb->addItem("Лос-Анжелес, UTC-8");  
  cb->addItem("Эдмонтон, UTC-7");
  cb->addItem("Чикаго, UTC-6");
  cb->addItem("Нью-Йорк, UTC-5");
  cb->addItem("Сантьяго, UTC-4");
  cb->addItem("Гренландия, UTC-3");
  cb->addItem("Южная Георгия, UTC-2");
  cb->addItem("Прая, UTC-1");
  cb->resize(200, 30);
  cb->setStyleSheet("QComboBox{background-color: #99abff; color: #1c2920}");
  
  cha1->move(win.width() - 75, win.height() - 25);
  cha1->setText("switch");
  cha1->resize(75, 25);
  
  QObject::connect(cb, QOverload<int>::of(&QComboBox::currentIndexChanged), [&howmuchtime](int in) {
    howmuchtime = in;
  });
  QObject::connect(timer, &QTimer::timeout, [&lab, &isRunning, &win, &dat, &ch, &b, &howmuchtime, &cha]() {
    if (isRunning) lab->setText(QDateTime::currentDateTimeUtc().addSecs((howmuchtime - 7)*3600).time().toString("hh:mm:ss"));
        lab->move((win.width() - 450)/2, (win.height() - 120)/2 - 200);
        dat->move((win.width() - 200)/2, (win.height() - 100)/2 - 120);
        ch->move(win.width() - 100, 0);
        b->move((win.width() - 100)/2, (win.height() - 50)/2 - 25);
        cha->move(win.width() - 75, win.height() - 25);
  });
  QObject::connect(b, &QPushButton::clicked, [&isRunning]() {
    isRunning = !isRunning;
  });
  QObject::connect(ch, &QPushButton::clicked, [&lab, &win, &theme, &b, &dat](){
    if (theme) {
      lab->setStyleSheet("QLabel {font-family: 'Times new Roman';"
          "font-size: 96px;"
          "color: #ffffff;"
          "background-color: #212529;"
          "border: 1px solid #3498db;"
          "border-radius: 10px;"
          "padding: 20px 20px;}");
      win.setStyleSheet("QMainWindow {background-color: #f8f9fa}");
      b->setStyleSheet("QPushButton{background-color: #4361ee;"
          "border-radius: 10px;}" 
          "QPushButton:hover {background-color: #3a56e4;}"
          "QPushButton:pressed {background-color: #2d46b9;}");
      dat->setStyleSheet("QLabel {font-family: 'Times new Roman';"
          "font-size: 32px;"
          "color: #000000}");
      theme = 0;
    } else {
      b->setStyleSheet("QPushButton{background-color: #4361ee;"
          "border-radius: 10px;}" 
          "QPushButton:hover {background-color: #3a56e4;}"
          "QPushButton:pressed {background-color: #2d46b9;}");
      lab->setStyleSheet("QLabel {font-family: 'Times new Roman';"
          "font-size: 96px; color: #1e1e2e;" 
          "background-color: #f5f5f5;"
          "border: 1px solid #3498db;"
          "border-radius: 10px;" 
          "padding: 20px 20px;}");
      win.setStyleSheet("QMainWindow {background-color: #1e1e2e}");
      dat->setStyleSheet("QLabel {font-family: 'Times new Roman';"
          "font-size: 32px;"
          "color: #ffffff}");
      theme = 1;
    }
  });
  QObject::connect(cha, &QPushButton::clicked, [&sw, &c]() {
    c = !c;
    sw->setCurrentIndex(c);
  });
  QObject::connect(cha1, &QPushButton::clicked, [&sw, &c]() {
    c = !c;
    sw->setCurrentIndex(c);
  });
  
  timer->start(1000);
  win.show();
  return app.exec();
}
