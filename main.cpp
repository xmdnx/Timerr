#include <QApplication>
#include <QDateTime>
#include <QMainWindow>
#include <QLabel>
#include <QTime>
#include <QTimer>
#include <QDate>
#include <QPushButton>
#include <QComboBox>
#include <QStackedWidget>
#include <QVBoxLayout>

#include "styles.hpp"

struct Timezone {
	QString name;
	int offset;
};

const std::vector<Timezone> kTimezones = {
		{"Лондон, UTC+0", 0},
		{"Париж, UTC+1", 1},
		{"Калининград, UTC+2", 2},  
		{"Москва, UTC+3", 3},
		{"Самара, UTC+4", 4},
		{"Екатеринбург, UTC+5", 5},
		{"Омск, UTC+6", 6},
		{"Красноярск, UTC+7", 7},  
		{"Иркутск, UTC+8", 8},
		{"Якутск, UTC+9", 9},
		{"Владивосток, UTC+10", 10},
		{"Сахалин, UTC+11", 11},
		{"США, UTC-12", -12},
		{"Ниуэ, UTC-11", -11},
		{"Гонолулу, UTC-10", -10},
		{"Анкоридж, UTC-9", -9},
		{"Лос-Анжелес, UTC-8", -8},  
		{"Эдмонтон, UTC-7", -7},
		{"Чикаго, UTC-6", -6},
		{"Нью-Йорк, UTC-5", -5},
		{"Сантьяго, UTC-4", -4},
		{"Гренландия, UTC-3", -3},
		{"Южная Георгия, UTC-2", -2},
		{"Прая, UTC-1", -1}
};

enum class Screen {
	Timer,
	Second
};

void setScreen(QStackedWidget* mainWidget, Screen screen) {
	switch (screen) {
		case Screen::Timer:
			mainWidget->setCurrentIndex(0);
			break;
		case Screen::Second:
			mainWidget->setCurrentIndex(1);
			break;
	}
}

void updateTimeLabel(QLabel* timeLabel, int currentTimezoneIndex) {
	int offset = kTimezones.at(currentTimezoneIndex).offset;
	timeLabel->setText(
		QDateTime::currentDateTimeUtc()
			.addSecs(offset*3600)
			.time()
			.toString("hh:mm:ss")
	);
}

void updateDateLabel(QLabel* dateLabel) {
	dateLabel->setText(
		QDate::currentDate()
			.toString("d MMMM yyyy")
	);
}

int main(int argc, char* argv[]) {
	int currentTimezoneIndex = 3;
	QApplication app(argc, argv);
	app.setStyle("Fusion");

	bool isRunning = true;
	bool theme = true;

	QMainWindow window;
	window.setMinimumSize(400, 300);
	window.setWindowTitle("Timerr");

	QStackedWidget* mainWidget = new QStackedWidget(&window);
	window.setCentralWidget(mainWidget);

	QWidget* timerScreen = new QWidget();

	QWidget* secondScreen = new QWidget();

	mainWidget->addWidget(timerScreen);
	mainWidget->addWidget(secondScreen);
	setScreen(mainWidget, Screen::Timer);

	QTimer* timer = new QTimer(timerScreen);

	// secondScreen setup
	QVBoxLayout* secondLayout = new QVBoxLayout(secondScreen);
	QPushButton* switchScreenButton2 = new QPushButton(secondScreen);
	secondLayout->addWidget(switchScreenButton2);

	// timerScreen layout setup
	QVBoxLayout* timerLayout = new QVBoxLayout(timerScreen);

	// timeLabel setup
	QLabel* timeLabel = new QLabel(timerScreen);

	timeLabel->setFont(styleTimeLabel);
	updateTimeLabel(timeLabel, currentTimezoneIndex);

	// dateLabel setup
	QLabel* dateLabel = new QLabel(timerScreen);

	dateLabel->setFont(styleDateLabel);
	updateDateLabel(dateLabel);

	// timerControlButton setup
	QPushButton* timerControlButton = new QPushButton(timerScreen);
	timerControlButton->setText("Start/Stop");

	// changeThemeButton setup
	QPushButton* changeThemeButton = new QPushButton(timerScreen);
	changeThemeButton->setText("change theme");

	// switchScreenButton1 setup
	QPushButton* switchScreenButton1 = new QPushButton(timerScreen);
	switchScreenButton1->setText("Switch to second screen");

	// timezoneSelectionDropdown setup
	QComboBox* timezoneSelectionDropdown = new QComboBox(timerScreen);
	for (const auto& timezone : kTimezones) {
		timezoneSelectionDropdown->addItem(timezone.name);
	}
	timezoneSelectionDropdown->setCurrentIndex(currentTimezoneIndex);

	// Adding widgets to timerScreen layout
	timerLayout->addWidget(timezoneSelectionDropdown, 0, Qt::AlignLeft);
	timerLayout->addWidget(timeLabel, 0, Qt::AlignCenter);
	timerLayout->addWidget(dateLabel, 0, Qt::AlignCenter);
	timerLayout->addWidget(timerControlButton, 0, Qt::AlignCenter);
	timerLayout->addWidget(changeThemeButton, 0, Qt::AlignRight);
	timerLayout->addWidget(switchScreenButton1, 0, Qt::AlignRight);
	
	switchScreenButton2->setText("Switch to timer screen");
	
	QObject::connect(
		timezoneSelectionDropdown, 
		QOverload<int>::of(&QComboBox::currentIndexChanged), 
		[&currentTimezoneIndex](int selectedTimezoneIndex) {
			currentTimezoneIndex = selectedTimezoneIndex;
		}
	);

	QObject::connect(
		timer, 
		&QTimer::timeout, 
		[&timeLabel, &isRunning, &dateLabel, &currentTimezoneIndex]() {
			if (!isRunning) return;
			updateTimeLabel(timeLabel, currentTimezoneIndex);
			updateDateLabel(dateLabel);
		}
	);

	QObject::connect(
		timerControlButton, 
		&QPushButton::clicked, 
		[&isRunning]() {
			isRunning = !isRunning;
		}
	);

	QObject::connect(
		changeThemeButton, 
		&QPushButton::clicked, 
		[&theme, &app]() {
			theme = !theme;
			app.setStyle(theme ? "Fusion" : "Windows");
		}
	);

	QObject::connect(
		switchScreenButton1, 
		&QPushButton::clicked, 
		[&mainWidget]() {
			setScreen(mainWidget, Screen::Second);
		}
	);

	QObject::connect(
		switchScreenButton2, 
		&QPushButton::clicked, 
		[&mainWidget]() {
			setScreen(mainWidget, Screen::Timer);
		}
	);

	timer->start(500);
	window.show();
	return app.exec();
}
