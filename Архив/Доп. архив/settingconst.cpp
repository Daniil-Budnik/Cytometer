#include "settingconst.h"

//static QString _ls= "/home/white-pirate/Документы/QtProject/Graph_Life_Studio_ADB/asset/Data.txt";
static QString _ls=  "assets:/Datas/Data.txt"; // Data , Data2 , Data3
static int _PowerOpen = 100; // Шаг включения вируального лазера
static int _TS = 100; // Строк за один такт
static int _TimerS = 5; // Скорость такта в миллисекундах
static int _SP = 0 ; // Номер графика указывать тут (Эту настройку НЕ ТРОГАТЬ ПОКА ЧТО!!!)
static int _RangeConstTr = 50000; // Выресовывание точек, до очистки графа
static int _RangeYConstTr = 4000; // Максимальная высота, видимая в графе трэйс


static QString TESTER ;



SettingConst::SettingConst()
{

}

QString SettingConst::TESTER_() const
{
	return  ::TESTER;
}

void SettingConst::setTESTER_(QString TES)
{

	::TESTER = TES;
}

int SettingConst::RangeYConstTr_() const
{
	return :: _RangeYConstTr;
}

void SettingConst::setRangeYConstTr_(int RangeYConstTr)
{
	::_RangeYConstTr = RangeYConstTr;
}

int SettingConst::RangeConstTr_() const
{
	return ::_RangeConstTr;
}

void SettingConst::setRangeConstTr_(int RangeConstTr)
{
	::_RangeConstTr = RangeConstTr;
}

int SettingConst::SP_() const
{
	return ::_SP;
}

void SettingConst::setSP_(int SP)
{
	::_SP = SP;
}

int SettingConst::TimerS_() const
{
	return ::_TimerS;
}

void SettingConst::setTimerS_(int TimerS)
{
	::_TimerS = TimerS;
}

int SettingConst::TS_() const
{
	return ::_TS;
}

void SettingConst::setTS_(int TS)
{
	::_TS = TS;
}

int SettingConst::PowerOpen_() const
{
	return ::_PowerOpen;
}

void SettingConst::setPowerOpen_(int PowerOpen)
{
	::_PowerOpen = PowerOpen;
}

QString SettingConst::ls_() const
{
	return ::_ls;
}

void SettingConst::setLs_(const QString & ls)
{
	::_ls = ls;
}
