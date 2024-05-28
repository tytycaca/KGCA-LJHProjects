#pragma once
#include <iostream>
#include <string>

using namespace std;

enum class Position
{
	Staff,
	Assistant,
	General,
	Director,
	Excutive
};

enum class SalaryType
{
	Hourly,
	Monthly,
	Yearly,
};

class Employee
{
private:
	string		m_Name;
	Position	m_Position;
	SalaryType	m_SalaryType;
	int			m_WorkTime	= 0;
	int			m_Year		= 0;
	int			m_Grade		= 0;

public:
	string		GetName()		{ return m_Name; }
	Position	GetPosition()	{ return m_Position; }
	SalaryType	GetSalaryType() { return m_SalaryType; }
	int			GetWorkTime()	{ return m_WorkTime; }
	int			GetYear()		{ return m_Year; }
	int			GetGrade()		{ return m_Grade; }

	void		SetName(string name)				 { m_Name = name; }
	void		SetPosition(Position position)		 { m_Position = position; }
	void		SetSalaryType(SalaryType salaryType) { m_SalaryType = salaryType; }
	void		SetWorkTime(int time)				 { m_WorkTime = time; }
	void		SetYear(int year)					 { m_Year = year; }
	void		SetGrade(int grade)					 { m_Grade = grade; }
};

