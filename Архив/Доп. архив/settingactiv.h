#ifndef SETTINGACTIV_H
#define SETTINGACTIV_H

#include <QMainWindow>

namespace Ui {
		class SettingActiv;
	}

class SettingActiv : public QMainWindow
	{
		Q_OBJECT

	public:
		explicit SettingActiv(QWidget *parent = nullptr);
		~SettingActiv();

	private slots:
		void on_Apply_clicked();

	private:
		Ui::SettingActiv *ui;
		void DataUpdate();
	};

#endif // SETTINGACTIV_H
