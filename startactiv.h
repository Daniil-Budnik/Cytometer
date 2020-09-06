#ifndef STARTACTIV_H
#define STARTACTIV_H

#include <QMainWindow>
#include "qcustomplot.h"
#include "string.h"
#include "settingconst.h"

using namespace std;

namespace Ui {
		class StartActiv;
	}

class StartActiv : public QMainWindow
	{
		Q_OBJECT
	public:
		explicit StartActiv(QWidget *parent = nullptr);
		~StartActiv();

	private slots:

		void on_Menu_B_clicked();

		void on_Start_B_clicked();

		void on_Pause_B_clicked();

		void on_Save_B_clicked();

		void TIMERSETGRAPH();

		void on_Connect_B_clicked();

	private:
		Ui::StartActiv *ui;

		QString DirS_PC;
		QString DirS_AD;

		QCustomPlot *GraphVS; // Сокращение графа частот
		QCustomPlot *GraphTr; // Сокращение графа трэйса

		QVector<double> TIMERX(int X); // Бональный криейтор массива от 0 до n
		double Traiser(QVector<double> Y); // Нахождение трэйса

		QFile FileS; // Переменна, где храниться путь к файлу

		SettingConst ST; // Вызов класса, хронящий в себе настройки

		// Проверка нажатых кнопок
		bool StartING = false;
		bool PauseING = false;

		// Таймер работы конструктора графиков, а так же обработки
		QTimer* TIMERSET;

		// Массивы, для постройки графиков
		QVector<double> Line_Y_1;
		QVector<double> Line_X_1;
		QVector<double> Line_Y_2;
		QVector<double> Line_X_2;

		// Массивы, где хранятся данные
		QVector<double> xV;
		QVector<double> yV;
		QVector<double> xT;
		QVector<double> yT;

		//static QString ls = ST.ls_(); // Старый метод обработки

		// Крайние точки видисти на графике по оси X /// (V (сигнал) - первый график T (трэйс) - второй)
		int RangeXBeginV;
		int RangeXEndV;
		int RangeXBeginT;
		int RangeXEndT;

		// Максимальная верхняя точка видимости на втором графике
		int RangeYT = ST.RangeYConstTr_();

		int RangeYMinV = ST.RangeYMinV_();
		int RangeYMaxV = ST.RangeYMaxV_();

		int V = ST.V_(); // Частота графика
		int Speed = ST.Speed_(); // Скорость обновления

		double MIN; // Константа минимума
		double MAX; // Константа максимума

		// Обработка данных
		int g;
		QByteArray ByteS;
        char *ByteC = new char[sizeof (short int)];
		float YV;
		double TR;
		QString DIR;

		// Тригер Трэйс
		int TTtimer; // Счётчик для Тригер Трэйса
		int TrigerTrais;
		QString TTs;
		QString TTnum;
		QString TTpoint;
		QString TTtrais;

		void CustumPlotD();
		void InterPlotD(bool X);
		void GraphCreatorD(QCustomPlot *X, QString Y);
        void TrigerTrace();

	};

#endif // STARTACTIV_H
