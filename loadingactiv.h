#ifndef LOADINGACTIV_H
#define LOADINGACTIV_H

#include <QMainWindow>

namespace Ui {
		class LoadingActiv;
	}

class LoadingActiv : public QMainWindow
	{
		Q_OBJECT

	public:
		explicit LoadingActiv(QWidget *parent = nullptr);
		~LoadingActiv();
		void EXIT();

	private:
		Ui::LoadingActiv *ui;
	private slots:
		void TTT();
	};

#endif // LOADINGACTIV_H
