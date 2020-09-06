//=========================================================
//=== Классс, который хранит в себе настройки по умолчанию
//=========================================================

#include "settingconst.h"

// --------------------------- Данные, для реализации старого метода обработки...  ------
//static QString _ls= "/home/white-pirate/Документы/QtProject/Graph_Life_Studio_ADB/asset/DataR.txt";
//static QString _ls=  "assets:/Datas/Data.txt"; // Data , Data2 , Data3
//static int _SP = 0 ; // Номер графика указывать тут (Эту настройку НЕ Т� ОГАТЬ ПОКА ЧТО!!!)
// --------------------------- --------------------------- ---------------------------

static int _V= 4048; // Частота (16384)
static int _Speed = 1; // Скорость в миллисекундах

static int _RangeYMinV = -4000; // Минимальная значение видимой высоты графика частот
static int _RangeYMaxV = 10000;  // Максимальное значение видимой высоты графика частот

static int _RangeConstTr = 500; // Выресовывание точек, до очистки графа
static int _RangeYConstTr = 34000; // Максимальная высота, видимая в графе трэйс

static int _TrigerTrais = 10000;


// Тут реализованны методы получения и изминения значения настройки
// Name_ получение // setName_ изминение

SettingConst::SettingConst()
	{

	}

int SettingConst::RangeYMaxV_() const
	{
		return ::_RangeYMaxV;
	}

void SettingConst::setRangeYMaxV_(int RangeYMaxV)
	{
		::_RangeYMaxV = RangeYMaxV;
	}

int SettingConst::TrigerTrais_() const
	{
		return :: _TrigerTrais;
	}

void SettingConst::TrigerTrais_(int TrigerTrais)
	{
		:: _TrigerTrais = TrigerTrais;
	}

int SettingConst::RangeYMinV_() const
	{
		return ::_RangeYMinV;
	}

void SettingConst::setRangeYMinV_(int RangeYMinV)
	{
		::_RangeYMinV = RangeYMinV;
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

//int SettingConst::SP_() const
//	{
//		return ::_SP;
//	}

//void SettingConst::setSP_(int SP)
//	{
//		::_SP = SP;
//	}

int SettingConst::Speed_() const
	{
		return ::_Speed;
	}

void SettingConst::setSpeed_(int TimerS)
	{
		::_Speed = TimerS;
	}



int SettingConst::V_() const
	{
		return ::_V;
	}

void SettingConst::setV_(int PowerOpen)
	{
		::_V = PowerOpen;
	}

//QString SettingConst::ls_() const
//	{
//		return ::_ls;
//	}

//void SettingConst::setLs_(const QString & ls)
//	{
//		::_ls = ls;
//	}
