//====================================================
//=== Реализация главного окна
//====================================================

#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "startactiv.h"
#include "settingactiv.h"

MainWindow::MainWindow(QWidget *parent) :
QMainWindow(parent),
ui(new Ui::MainWindow)
	{
		ui->setupUi(this);\
		QString VER = "Ver.0.0.15/demo";
		ui->Ver_Text->setText(VER);
		// Тут дописать дизайн дизайн !!!
	}

MainWindow::~MainWindow()
	{
		delete ui;
	}

void MainWindow::on_B1_Start_clicked() // Действие, при нажатии на Старт
	{
		StartActiv *STARTACT = new StartActiv();
		STARTACT->show();
	}

void MainWindow::on_B2_Setting_clicked() // Действие, при нажатии на Настройки
	{
		SettingActiv *SETTINGACTIV = new SettingActiv;
		SETTINGACTIV->show();
	}
