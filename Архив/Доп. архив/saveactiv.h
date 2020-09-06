#ifndef SAVEACTIV_H
#define SAVEACTIV_H

#include <QMainWindow>

namespace Ui {
		class SaveActiv;
	}

class SaveActiv : public QMainWindow
	{
		Q_OBJECT

	public:
		explicit SaveActiv(QWidget *parent = nullptr);
		~SaveActiv();

	private:
		Ui::SaveActiv *ui;
	};

#endif // SAVEACTIV_H
