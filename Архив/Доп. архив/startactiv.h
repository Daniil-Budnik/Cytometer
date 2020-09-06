#ifndef STARTACTIV_H
#define STARTACTIV_H

#include <QMainWindow>
#include "qcustomplot.h"

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

		void PlayVsStep();

		void PlayTraisStep();

	private:
		Ui::StartActiv *ui;
		QCustomPlot *GraphVS;
		QCustomPlot *GraphTr;
		QVector<double> TXT(QString ls);
		QVector<double> TIMERX(int X);
		QVector<double> Traiser(QVector<double> X,QVector<double> Y, int Z);
		QVector<double> PowerOn(int X, int Y);

	};

#endif // STARTACTIV_H
