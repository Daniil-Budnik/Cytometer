#ifndef SETTINGCONST_H
#include <QString>
#define SETTINGCONST_H


class SettingConst
{
	public:
		SettingConst();

		QString ls_() const;
		void setLs_(const QString & ls);

		int V_() const;
		void setV_(int PowerOpen);

		int TS_() const;
		void setTS_(int TS);

		int Speed_() const;
		void setSpeed_(int TimerS);

		int SP_() const;
		void setSP_(int SP);

		int RangeConstTr_() const;
		void setRangeConstTr_(int RangeConstTr);

		int RangeYConstTr_() const;
		void setRangeYConstTr_(int RangeYConstTr);

		int RangeYMinV_() const;
		void setRangeYMinV_(int RangeYMinV);

		int RangeYMaxV_() const;
		void setRangeYMaxV_(int RangeYMaxV);

		int TrigerTrais_() const;
		void TrigerTrais_(int TrigerTrais);
	};

#endif // SETTINGCONST_H
