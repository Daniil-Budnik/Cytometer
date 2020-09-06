#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "startactiv.h"
#include "settingactiv.h"
#include "loadingactiv.h"

MainWindow::MainWindow(QWidget *parent) :
QMainWindow(parent),
ui(new Ui::MainWindow)
	{
		ui->setupUi(this);
		QPalette pal = ui->Fon->palette();
		pal.setColor(QPalette::Base, pal.color(QPalette::Window));
		ui->Fon->setPalette(pal);
	}

MainWindow::~MainWindow()
	{
		delete ui;
	}

void MainWindow::on_B1_Start_clicked()
	{
		LoadingActiv *LOADACT = new LoadingActiv();
		LOADACT->show();
	}

void MainWindow::on_B2_Setting_clicked()
	{
		SettingActiv *SETTINGACTIV = new SettingActiv;
		SETTINGACTIV->show();
	}
