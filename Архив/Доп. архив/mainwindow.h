#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
		class MainWindow;
	}

class MainWindow : public QMainWindow
	{
		Q_OBJECT

	public:
		explicit MainWindow(QWidget *parent = nullptr);
		~MainWindow();

	private slots:
		void on_B1_Start_clicked();

		void on_B2_Setting_clicked();

	private:
		Ui::MainWindow *ui;
	};

#endif // MAINWINDOW_H
