#include "loadingactiv.h"
#include "ui_loadingactiv.h"
#include "startactiv.h"

static int TIMER = 0;

LoadingActiv::LoadingActiv(QWidget *parent) :
QMainWindow(parent),
ui(new Ui::LoadingActiv)
	{
		ui->setupUi(this);
		TIMER = 0;
		QTimer* TT = new QTimer(this);
		connect(TT,SIGNAL(timeout()),this,SLOT(TTT()));
		TT->start();
	}

LoadingActiv::~LoadingActiv()
	{
		delete ui;
	}

void LoadingActiv::EXIT()
	{
		this->deleteLater();
	}

void LoadingActiv::TTT()
	{
		TIMER++;
		if(TIMER == 4000){
				StartActiv *STAR = new StartActiv();
				STAR->show();
				this->deleteLater();

			}
	}
