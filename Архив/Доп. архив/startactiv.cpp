#include "startactiv.h"
#include "ui_startactiv.h"
#include "qcustomplot.h"
#include "saveactiv.h"
#include "settingconst.h"
#include "loadingactiv.h"

static bool StartING = false;
static bool PauseING = false;

static int TimerS;

static int RangeXBegin;
static int RangeXEnd;
static int RangeY;
static int RangeConstTr;
static int RangeYConstTr;

static QVector<double> Line_Y_1;
static QVector<double> Line_X_1;
static QVector<double> Line_Y_2;
static QVector<double> Line_X_2;

static int TimeElapsedVs = 0;
static int TimeElapsedTr = 0;

static QVector<double> xV;
static QVector<double> yV;
static QVector<double> xT;
static QVector<double> yT;

static int N;
static int TS;
static int SP;
static int PowerOpen;

static QString ls;

static QTimer* VsTimer;
static QTimer* TrTimer;

static SettingConst ST;

StartActiv::StartActiv(QWidget *parent) :
QMainWindow(parent),
ui(new Ui::StartActiv)
	{
		ui->setupUi(this);
		LoadingActiv LA;
		LA.EXIT();

		// Константы для тестирования !!!
		{
			ls = ST.ls_();
			PowerOpen = ST.PowerOpen_();
			TS = ST.TS_();
			TimerS = ST.TimerS_();
			SP = ST.SP_();
			RangeConstTr = ST.RangeConstTr_();
			RangeYConstTr = ST.RangeYConstTr_();
		}

		// Объявление графиков
		GraphVS = ui->Graph_Vs;
		GraphTr = ui->Graph_Trais;


		// Интерактив графика (только для тестов, пред релиз выключить)
		// GraphVS->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectAxes |
		// 			 QCP::iSelectLegend | QCP::iSelectPlottables);
		// GraphTr->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectAxes |
		// 			 QCP::iSelectLegend | QCP::iSelectPlottables);


		// Кастомизация графиков
		{
			QLinearGradient plotGradient;
			plotGradient.setStart(0, 0);
			plotGradient.setFinalStop(0, 350);
			plotGradient.setColorAt(0, QColor(80, 80, 80));
			plotGradient.setColorAt(1, QColor(50, 50, 50));

			QLinearGradient axisRectGradient;
			axisRectGradient.setStart(0, 0);
			axisRectGradient.setFinalStop(0, 350);
			axisRectGradient.setColorAt(0, QColor(80, 80, 80));
			axisRectGradient.setColorAt(1, QColor(30, 30, 30));

			GraphVS->xAxis->setBasePen(QPen(Qt::white, 1));
			GraphVS->yAxis->setBasePen(QPen(Qt::white, 1));
			GraphVS->xAxis->setTickPen(QPen(Qt::white, 1));
			GraphVS->yAxis->setTickPen(QPen(Qt::white, 1));
			GraphVS->xAxis->setSubTickPen(QPen(Qt::white, 1));
			GraphVS->yAxis->setSubTickPen(QPen(Qt::white, 1));
			GraphVS->xAxis->setTickLabelColor(Qt::white);
			GraphVS->yAxis->setTickLabelColor(Qt::white);
			GraphVS->xAxis->grid()->setPen(QPen(QColor(140, 140, 140), 1, Qt::DotLine));
			GraphVS->yAxis->grid()->setPen(QPen(QColor(140, 140, 140), 1, Qt::DotLine));
			GraphVS->xAxis->grid()->setSubGridPen(QPen(QColor(80, 80, 80), 1, Qt::DotLine));
			GraphVS->yAxis->grid()->setSubGridPen(QPen(QColor(80, 80, 80), 1, Qt::DotLine));
			GraphVS->xAxis->grid()->setSubGridVisible(true);
			GraphVS->yAxis->grid()->setSubGridVisible(true);
			GraphVS->xAxis->grid()->setZeroLinePen(Qt::NoPen);
			GraphVS->yAxis->grid()->setZeroLinePen(Qt::NoPen);
			GraphVS->xAxis->setUpperEnding(QCPLineEnding::esSpikeArrow);
			GraphVS->yAxis->setUpperEnding(QCPLineEnding::esSpikeArrow);
			GraphVS->setBackground(plotGradient);
			GraphVS->axisRect()->setBackground(axisRectGradient);
			GraphVS->rescaleAxes();
			GraphVS->yAxis->setRange(0, 4);

			GraphTr->xAxis->setBasePen(QPen(Qt::white, 1));
			GraphTr->yAxis->setBasePen(QPen(Qt::white, 1));
			GraphTr->xAxis->setTickPen(QPen(Qt::white, 1));
			GraphTr->yAxis->setTickPen(QPen(Qt::white, 1));
			GraphTr->xAxis->setSubTickPen(QPen(Qt::white, 1));
			GraphTr->yAxis->setSubTickPen(QPen(Qt::white, 1));
			GraphTr->xAxis->setTickLabelColor(Qt::white);
			GraphTr->yAxis->setTickLabelColor(Qt::white);
			GraphTr->xAxis->grid()->setPen(QPen(QColor(140, 140, 140), 1, Qt::DotLine));
			GraphTr->yAxis->grid()->setPen(QPen(QColor(140, 140, 140), 1, Qt::DotLine));
			GraphTr->xAxis->grid()->setSubGridPen(QPen(QColor(80, 80, 80), 1, Qt::DotLine));
			GraphTr->yAxis->grid()->setSubGridPen(QPen(QColor(80, 80, 80), 1, Qt::DotLine));
			GraphTr->xAxis->grid()->setSubGridVisible(true);
			GraphTr->yAxis->grid()->setSubGridVisible(true);
			GraphTr->xAxis->grid()->setZeroLinePen(Qt::NoPen);
			GraphTr->yAxis->grid()->setZeroLinePen(Qt::NoPen);
			GraphTr->xAxis->setUpperEnding(QCPLineEnding::esSpikeArrow);
			GraphTr->yAxis->setUpperEnding(QCPLineEnding::esSpikeArrow);
			GraphTr->setBackground(plotGradient);
			GraphTr->axisRect()->setBackground(axisRectGradient);
			GraphTr->rescaleAxes();
			GraphTr->yAxis->setRange(0, 4);

			GraphVS->xAxis->setTickLabelFont(QFont(QFont().family(), 10));
			GraphVS->yAxis->setTickLabelFont(QFont(QFont().family(), 10));
			GraphTr->xAxis->setTickLabelFont(QFont(QFont().family(), 10));
			GraphTr->yAxis->setTickLabelFont(QFont(QFont().family(), 10));

		}


		// Создание массива значений, считываемых с файла
		Line_Y_1 = TXT(ls);
		Line_X_1 = TIMERX(Line_Y_1.length());

		// Генерируем массив такта включения лазера (искуственно)

		QVector<double> PowerS = PowerOn(Line_Y_1.length(),PowerOpen);


		// График трэй
		Line_Y_2 = Traiser(PowerS,Line_Y_1,PowerOpen);
		Line_X_2 = TIMERX(Line_Y_2.length());


		// Построение графика частот
		GraphVS->addGraph();
		// GraphVS->graph(0)->addData(Line_X_1,Line_Y_1);
		GraphVS->graph(0)->setPen(QPen(Qt::green));
		GraphVS->colorCount();
		GraphVS->rescaleAxes();
		GraphVS->replot();


		// Построение графика трэйса
		GraphTr->addGraph();
		// GraphTr->graph(0)->addData(Line_X_2,Line_Y_2);
		GraphTr->graph(0)->setPen(QPen(Qt::yellow));
		GraphTr->colorCount();
		GraphTr->rescaleAxes();
		GraphTr->replot();


		// Таймер для графика частот
		VsTimer= new QTimer(this);
		connect(VsTimer,SIGNAL(timeout()),this,SLOT(PlayVsStep()));



		// Таймер для графика трэйса
		TrTimer = new QTimer(this);
		connect(TrTimer,SIGNAL(timeout()),this,SLOT(PlayTraisStep()));


	}



StartActiv::~StartActiv()
	{
		delete ui;
	}

void StartActiv::on_Menu_B_clicked()
	{
		this->deleteLater();
	}

void StartActiv::on_Start_B_clicked()
	{
		if(!StartING){
				ui->Start_B->setText("Stop");
				StartING = true;
				RangeXBegin = 0;
				RangeXEnd = RangeConstTr;
				RangeY = RangeYConstTr;
				N = 0;
				VsTimer->start(TimerS);
				TrTimer->start(TimerS);
			}
		else {
				ui->Start_B->setText("Start");
				StartING = false;
				ui->Pause_B->setText("Pause");
				PauseING = false;
				VsTimer->stop();
				TrTimer->stop();
				xV.clear();yV.clear();xT.clear();yT.clear();
				TimeElapsedVs = 0;
				TimeElapsedTr = 0;
				GraphVS->graph(0)->setData(xV, yV);
				GraphVS->rescaleAxes();
				GraphVS->replot();
				GraphTr->graph(0)->setData(xT, yT);
				GraphTr->rescaleAxes();
				GraphTr->replot();

			}
	}

void StartActiv::on_Pause_B_clicked()
	{
		if(!PauseING and StartING){
				ui->Pause_B->setText("Continue");
				PauseING = true;
			}
		else {
				ui->Pause_B->setText("Pause");
				PauseING = false;
			}
	}

void StartActiv::on_Save_B_clicked()
	{
		SaveActiv *SAVEACTIV = new SaveActiv();
		SAVEACTIV->show();
	}

void StartActiv::PlayVsStep()
	{
		if(StartING and !PauseING){
				xV.clear();yV.clear();
				for (int i = TimeElapsedVs; (Line_Y_1.length() > (TimeElapsedVs+TS))and(i < TimeElapsedVs+TS); i++) {
						yV.push_back(Line_Y_1.at(i));
						xV.push_back(i);
					}
				TimeElapsedVs+=TS;
				GraphVS->graph(0)->setData(xV, yV);
				GraphVS->rescaleAxes();
				GraphVS->replot();
			}
	}

void StartActiv::PlayTraisStep()
	{

		if(StartING and !PauseING){
				for (int i = TimeElapsedTr; (Line_Y_2.length() > (TimeElapsedTr+TS))and(i < TimeElapsedTr+TS); i++) {
						yT.push_back(Line_Y_2.at(i));
						xT.push_back(i);
						if(N > RangeXEnd){
								RangeXBegin = RangeXEnd;
								RangeXEnd += RangeConstTr;
								xT.clear();yT.clear();
							}
						N+=1;
					}
				TimeElapsedTr+=TS;
				GraphTr->graph(0)->setData(xT, yT);
				GraphTr->xAxis->setRange(RangeXBegin,RangeXEnd);
				GraphTr->yAxis->setRange(0,RangeY);
				GraphTr->replot();
			}
	}

QVector<double> StartActiv::TXT(QString LS)
	{
		QVector<double> Line_Y_1;
		QFile File(LS);
		if(!File.open(QFile::ReadOnly)){
				ui->Stat_Text->setText("ERROR");
			}else{
				ui->Stat_Text->setText("Good");
				QString str;
				QString CHAR;
				int Y;
				while(!File.atEnd()){
						Y = 0;
						str = File.readLine();
						for(int bock = 0; bock <= str.length(); bock++){
								if(str[bock]!='\t' and str[bock]!='\n' and str[bock]!=' '){
										CHAR += str[bock];
									}else{
										if(Y == SP){
												int num = 0;
												int ls = 1;
												for (int i = 0; i < CHAR.length(); i++){
														if(CHAR[i]=="-"){ls = -1;}
														if(CHAR.at(i).isDigit()){
																if(num!=0){num=num*10;}
																num += CHAR.at(i).digitValue();
															}
													}
												num = num * ls;
												Line_Y_1.push_back(num);
											}
										CHAR = "";
										Y++;
									}
							}
					}
			}
		File.close();
		return Line_Y_1;
	}

QVector<double> StartActiv::TIMERX(int X)
	{
		QVector<double> Line_X_1;
		for(int i = 0; i < X; i++){
				Line_X_1.push_back(i);
			}
		return  Line_X_1;
	}

QVector<double> StartActiv::Traiser(QVector<double> X, QVector<double> Y, int Z)
	{
		QVector<double> Line_Y_2;
		for (int i = 0; i < Y.length(); i++) {
				if(X.at(i) > 0){
						double MIN = Y.at(i);
						double MAX = Y.at(i);
						for (int g = i-(Z/2); g < i-(Z/4);g++) {
								if(Y.at(g) < MIN){MIN = Y.at(g);}
								if(Y.at(g) > MAX){MAX = Y.at(g);}
							}
						if(MIN>0){Line_Y_2.append(MAX-MIN);}else {
								if(MAX>0){Line_Y_2.append(MAX+abs(MIN));}else{
										Line_Y_2.append(abs(MIN)-abs(MAX));
									}
							}
					}else{Line_Y_2.append(0);}
			}
		return Line_Y_2;
	}

QVector<double> StartActiv::PowerOn(int X, int Y)
	{
		QVector<double> Power;
		for (int i = 0; i < X; i++) {
				if(i%Y == (Y/2)){Power.append(1);}else{Power.append(0);}
			}
		return Power;
	}
