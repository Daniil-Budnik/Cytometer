#include "saveactiv.h"
#include "ui_saveactiv.h"

SaveActiv::SaveActiv(QWidget *parent) :
QMainWindow(parent),
ui(new Ui::SaveActiv)
	{
		ui->setupUi(this);
	}

SaveActiv::~SaveActiv()
	{
		delete ui;
	}
