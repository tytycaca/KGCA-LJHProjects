#pragma once
#include "stdInclude.h"

enum class Gender
{
	MALE,
	FEMALE
};

enum class Tribe
{
	HUMAN,
	ELF,
	DWARF
};

struct Point
{
	float m_x_pos;
	float m_y_pos;
	float m_z_pos;

	// 삽입 연산자 재정의 (Point 구조체를 출력했을때)
	friend std::wostream& operator << (std::wostream& wos, const Point& p)
	{
		using std::endl;

		wos << L"현재 캐릭터의 위치" << endl
			<< L"X 좌표값: " << p.m_x_pos << endl
			<< L"Y 좌표값: " << p.m_y_pos << endl
			<< L"Z 좌표값: " << p.m_z_pos << endl;

		return wos;
	}

	Point(float p_x_pos, float p_y_pos, float p_z_pos) :
		m_x_pos(p_x_pos),
		m_y_pos(p_y_pos),
		m_z_pos(p_z_pos)
	{

	}
};

struct Stat
{
	std::wstring m_name;
	Gender m_gender;
	Tribe m_tribe;
	int m_age;
	float m_hp;
	float m_mp;
	float m_exp;

	// 삽입 연산자 재정의 (Stat 구조체를 출력했을때)
	friend std::wostream& operator << (std::wostream& wos, const Stat& s)
	{
		using std::endl;

		wos << L"스탯을 표시합니다." << endl;
		wos << s.m_name << std::endl;

		if (s.m_gender == Gender::MALE)
			wos << L"성별: " << L"남" << endl;
		else
			wos << L"성별: " << L"여" << endl;

		if (s.m_tribe == Tribe::HUMAN)
			wos << L"종족: " << L"인간"   << endl;
		else if (s.m_tribe == Tribe::ELF)
			wos << L"종족: " << L"엘프"   << endl;
		else
			wos << L"종족: " << L"드워프" << endl;

		wos << L"나이: "   << s.m_age << endl
			<< L"체력: "   << s.m_hp  << endl
			<< L"마나: "   << s.m_mp  << endl
			<< L"경험치: " << s.m_exp << endl;

		return wos;
	}

	Stat(std::wstring p_name, Gender p_gender, Tribe p_tribe, int p_age, float p_hp, float p_mp, float p_exp) :
		m_name(p_name),
		m_gender(p_gender),
		m_tribe(p_tribe),
		m_age(p_age),
		m_hp(p_hp),
		m_mp(p_mp),
		m_exp(p_exp)
	{

	}
};

class MyCharacter
{
private:
	Point m_Point;
	Stat  m_Stat;

public:
	virtual Point getPos();
	virtual void setPos(float, float, float);
	virtual Stat getStat();
	virtual void setStat(std::wstring, Gender, Tribe, int, float, float, float);
	// 삽입 연산자 재정의 (MyCharacter 클래스를 값으로 참조 출력했을때) - 선언
	friend std::wostream& operator << (std::wostream& wos, const MyCharacter& mc);
	// 삽입 연산자 재정의 (MyCharacter 클래스를 포인터로 출력했을때) - 선언
	friend std::wostream& operator << (std::wostream& wos, const MyCharacter* mc);
	
public:
	MyCharacter();

};

