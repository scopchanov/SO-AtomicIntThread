#include "MainWindow.h"
#include "Counter.h"
#include <QThread>
#include <QVBoxLayout>
#include <QPushButton>
#include <QLineEdit>

MainWindow::MainWindow(QWidget *parent) :
	QMainWindow(parent),
	m_counter(new Counter())
{
	auto *widget = new QWidget(this);
	auto *layoutMain = new QVBoxLayout(widget);
	auto *editCurrent = new QLineEdit(this);
	auto *editSnapshot = new QLineEdit(this);
	auto *button = new QPushButton(tr("Show"), this);
	auto *mThread = new QThread(this);

	m_counter->moveToThread(mThread);
	mThread->start();

	m_counter->countFrom(15, 250);

	editCurrent->setReadOnly(true);
	editSnapshot->setReadOnly(true);

	layoutMain->addWidget(editCurrent);
	layoutMain->addWidget(editSnapshot);
	layoutMain->addWidget(button);

	setCentralWidget(widget);

	connect(button, &QPushButton::clicked, [this, editSnapshot, editCurrent](){
		int value = 0;

		editSnapshot->setText(QString::number(m_counter->setValue(value)));
		editCurrent->setText(QString::number(value));
	});

	connect(m_counter, &Counter::changed, [this, editCurrent](int value){
		editCurrent->setText(QString::number(value));
	});
}

MainWindow::~MainWindow()
{
	m_counter->thread()->quit();
	m_counter->thread()->wait(1000);
	delete m_counter;
}
