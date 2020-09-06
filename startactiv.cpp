 //====================================================
//=== Реализация функционала программы
//====================================================

#include "startactiv.h"
#include "ui_startactiv.h"

#include "remoteselector.h" // Вкладка для подключении сервера
#include "chatclient.h"     // Библиотека клиента BT
#include "chatserver.h"		// Библиотека сервера BT

#include "qcustomplot.h"  // Подключение библиотеки QCustomPlot

#include "saveactiv.h"    // Вкладка для сохранений (НЕ РАБОТАЕТ)
#include "settingconst.h" // Тут храняться настройки

StartActiv::StartActiv(QWidget *parent) :
QMainWindow(parent), ui(new Ui::StartActiv)
	{
		ui->setupUi(this);
        DirS_PC = "C:\\Users\\Saigen\\Desktop\\DD.bin";
        //DirS_PC = "D:\\Bin_Zip\\Data_2Byte_05.07.19.bin";
        //DirS_AD = "assets:/Datas/DataR.bin";

		// Привязка графиков к глобальным переменным
		GraphVS = ui->Graph_Vs;
		GraphTr = ui->Graph_Trais;
		CustumPlotD(); // Настройка дизайна графиков
		InterPlotD(true); // Интерактив графика (только при паузе), такиз как смещение графика, zoom и.т.д.

		DIR = DirS_PC;
		//DIR = DirS_AD;

		// Цвета графиков
		GraphCreatorD(GraphVS,"green");
		GraphCreatorD(GraphTr,"yellow");

        TrigerTrais = ST.TrigerTrais_();

		// Таймер для графика частот
        TIMERSET= new QTimer(this); // QTimer *

        // Запуск потока, в котором происходит отрисовка и обработка в реальном времени
        connect(TIMERSET,SIGNAL(timeout()),this,SLOT(TIMERSETGRAPH()));

	}

StartActiv::~StartActiv()
	{
		FileS.close(); // Закрытие файла. при выходе
		delete ui;
	}

void StartActiv::on_Menu_B_clicked() // Закрытие окна, при нажтии на меню
	{
		this->deleteLater();
	}

void StartActiv::on_Start_B_clicked() // Действия в момент нажатия на старт/стоп
	{
		if(!StartING){
				// Логика кнопок
				FileS.setFileName(DIR);
				ui->Start_B->setText("Stop");
				StartING = true;
				ui->TRAIS_IN->clear();
				TTtimer = 0;
				RangeXBeginV = 0; RangeXBeginT = 0; // Для будущего движения графиков
				RangeXEndV = ST.V_(); RangeXEndT = ST.RangeConstTr_();
				FileS.open(QIODevice::ReadOnly); // Открытие, для чтения как бинарник
				MIN = 999999; MAX = -999999;
				TIMERSET->start(Speed); // Запуск таймера. с определённой скоростью
			}
		else {
				// Сброс логики кнопок
				ui->Start_B->setText("Start");
				StartING = false;
				ui->Pause_B->setText("Pause");
				PauseING = false;

				TIMERSET->stop(); // Остановка таймера
				FileS.close(); // Закрытие файла
				xV.clear();yV.clear();xT.clear();yT.clear(); // Сброс графика

				// Обновление графиков
                GraphVS->graph(0)->setData(xV, yV);
                GraphVS->rescaleAxes();
                GraphVS->replot();

				GraphTr->graph(0)->setData(xT, yT);
				GraphTr->rescaleAxes();
				GraphTr->replot();

			}
	}

void StartActiv::on_Pause_B_clicked() // Пауза
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

void StartActiv::on_Connect_B_clicked() // Кнопка подклчения к серверу
	{
		//QDialog QTBT_Server = QTBT_Server.
	}

void StartActiv::on_Save_B_clicked() // Открытие вкладки сохранения, при нажатии на кнопку
	{
		SaveActiv *SAVEACTIV = new SaveActiv();
		SAVEACTIV->show();
	}

void StartActiv::TIMERSETGRAPH() // ГЛАВНЫЙ МЕТОД !!! Реализация постройки графика, а так же его обработки
	{
		if(StartING and !PauseING){

                // Чтение и расшифровка данных
				g = 0;
                while ((g<ST.V_())){                                // Сколько чисел поместится за один импульс
                        ByteS = FileS.read(sizeof (short int));     // Чтение из файла двух байт
                        for (int i = 0; i < ByteS.length(); i ++) { ByteC[i] = ByteS[i]; }
						YV = *reinterpret_cast<short int *>(ByteC);
                        yV.append(YV-1);    // Значение сигнала по оси Y
                        xV.append(g);       // Значение сигнала по оси X
						g++;
					}



                // Построение графика частот (Trace строится также)
                // На данный момент уже есть более свежая версия библиотеки,
                // которая имеет более эфективные методы, для работы в Real Time

                GraphVS->graph(0)->setData(xV, yV); // Два массива значений по X и по Y
                GraphVS->xAxis->setRange(RangeXBeginV,RangeXEndV);  // Авторазмер по X
                GraphVS->yAxis->setRange(RangeYMinV,RangeYMaxV);    // Авторазмер по Y
                GraphVS->replot();                                  // Перерисовывает


				if(!yV.isEmpty()){

						// Действие, когда график трэйса построен до самого края
						if(yT.length()/3>ST.RangeConstTr_()){

								// Чистка графика трэйса
								xT.clear();yT.clear();

								// Мув графика трэйса
								RangeXBeginT = RangeXEndT;
								RangeXEndT += ST.RangeConstTr_();
							}

						TR = Traiser(yV); // Получаем значение трэйса

                        // Вариант добавления в массив значений так, чтобы рисовал столбчетый график.
                        // В будущих версиях библиотеки QCustomPlot должны сделать их по умолчанию.
						{
							yT.append(0);
							yT.append(TR);
							yT.append(0);

							xT.append(yT.length()/3-0.0001+RangeXBeginT);
							xT.append(yT.length()/3+RangeXBeginT);
							xT.append(yT.length()/3+0.0001+RangeXBeginT);
						}

						// Вывод абсолютного максимума и минимума, а так же их координаты на циферблат
						if(TR>MAX){MAX = TR; ui->NUM_1->display(MAX);ui->NUM_3->display(yT.length()/3+RangeXBeginT);}

						// После построения графика трэйса, очистка графика частот
						xV.clear();yV.clear();

						// Обновление графика трэйса
						GraphTr->graph(0)->setData(xT, yT);
						GraphTr->xAxis->setRange(RangeXBeginT,RangeXEndT);
						GraphTr->yAxis->setRange(0,RangeYT);
						GraphTr->replot();
					}

                TrigerTrace();
			}
	}

void StartActiv::CustumPlotD() // Дизайнер графиков (тут без комментариев, шаблоны брал из источников)
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

void StartActiv::InterPlotD(bool X) // Интерактив графиков
	{
		if(X){
				GraphVS->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectAxes |
				QCP::iSelectLegend | QCP::iSelectPlottables);
				GraphTr->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectAxes |
				QCP::iSelectLegend | QCP::iSelectPlottables);
			}
	}

void StartActiv::GraphCreatorD(QCustomPlot *X, QString Y) // Цвета графиков
	{
		X->addGraph();
		if(Y == "yellow"){X->graph(0)->setPen(QPen(Qt::yellow));}
		if(Y == "green"){X->graph(0)->setPen(QPen(Qt::green));}
		X->colorCount();
		X->rescaleAxes();
        X->replot();
}

void StartActiv::TrigerTrace() // Тригер Трэйс
{
    if(TrigerTrais<TR){
            TTtimer++;
            TTs = " | ";
            TTnum =		QString::number(TTtimer);
            TTpoint =	QString::number(yT.length()/3+RangeXBeginT);
            TTtrais =	QString::number(TR);
            ui->TRAIS_IN->addItem(TTnum + TTs + TTpoint + TTs + TTtrais);
        }
}

QVector<double> StartActiv::TIMERX(int X) // Бональный криейтор массива от 0 до n
	{
		QVector<double> Line_X_1;
		for(int i = 0; i < X; i++){
				Line_X_1.push_back(i);
			}
		return  Line_X_1;
	}

// Метод обработки трейса
// Нахождение разницы между максимумом и минимумом
double StartActiv::Traiser(QVector<double> Y)
	{
		double N;
		double MAX = Y.at(0);
		double MIN = Y.at(0);
		for (int i = 0;Y.length()>i;i++) {
				if(MAX<Y.at(i)){MAX = Y.at(i);}
				if(MIN>Y.at(i)){MIN = Y.at(i);}
			}
		N = MAX-MIN;
		return N;
	}



