//=========================================================
//=== Реализация настроек
//=========================================================

#include "settingactiv.h"
#include "ui_settingactiv.h"
#include "settingconst.h"
#include <QString>

static SettingConst ST;

SettingActiv::SettingActiv(QWidget *parent) :
QMainWindow(parent),
ui(new Ui::SettingActiv)
	{
		ui->setupUi(this);
		DataUpdate();

	}

SettingActiv::~SettingActiv()
	{
		delete ui;
	}


void SettingActiv::DataUpdate()
	{
		ui->F1->setText(QString::number(ST.V_()));
		ui->F2->setText(QString::number(ST.Speed_()));
		ui->F3->setText(QString::number(ST.RangeYMinV_()));
		ui->F4->setText(QString::number(ST.RangeYMaxV_()));
		ui->F5->setText(QString::number(ST.RangeConstTr_()));
		ui->F6->setText(QString::number(ST.RangeYConstTr_()));
	}

void SettingActiv::on_Apply_clicked()
	{
		ST.setV_(ui->F1->text().toInt());
		ST.setSpeed_(ui->F2->text().toInt());
		ST.setRangeYMinV_(ui->F3->text().toInt());
		ST.setRangeYMaxV_(ui->F4->text().toInt());
		ST.setRangeConstTr_(ui->F5->text().toInt());
		ST.setRangeYConstTr_(ui->F6->text().toInt());
		DataUpdate();
		this->deleteLater();
	}
