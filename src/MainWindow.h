#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

class Counter;

class MainWindow : public QMainWindow
{
	Q_OBJECT
public:
	explicit MainWindow(QWidget *parent = nullptr);
	~MainWindow();

private:
	Counter *m_counter;
};

#endif // MAINWINDOW_H
