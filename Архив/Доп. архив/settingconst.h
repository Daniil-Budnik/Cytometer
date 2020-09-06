#ifndef SETTINGCONST_H
#include <QString>
#define SETTINGCONST_H


class SettingConst
{
	public:
		SettingConst();
		QString  _ls ;
		int _PowerOpen;
		int _TS;
		int _TimerS;
		int _SP;
		int _RangeConstTr;
		int _RangeYConstTr;

		QString TESTER;
		QString TESTER_() const;
		void setTESTER_(QString TES);

		QString ls_() const;
		void setLs_(const QString & ls);
		int PowerOpen_() const;
		void setPowerOpen_(int PowerOpen);
		int TS_() const;
		void setTS_(int TS);
		int TimerS_() const;
		void setTimerS_(int TimerS);
		int SP_() const;
		void setSP_(int SP);
		int RangeConstTr_() const;
		void setRangeConstTr_(int RangeConstTr);
		int RangeYConstTr_() const;
		void setRangeYConstTr_(int RangeYConstTr);
};

#endif // SETTINGCONST_H
