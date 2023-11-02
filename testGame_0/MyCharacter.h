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

	// ���� ������ ������ (Point ����ü�� ���������)
	friend std::wostream& operator << (std::wostream& wos, const Point& p)
	{
		using std::endl;

		wos << L"���� ĳ������ ��ġ" << endl
			<< L"X ��ǥ��: " << p.m_x_pos << endl
			<< L"Y ��ǥ��: " << p.m_y_pos << endl
			<< L"Z ��ǥ��: " << p.m_z_pos << endl;

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

	// ���� ������ ������ (Stat ����ü�� ���������)
	friend std::wostream& operator << (std::wostream& wos, const Stat& s)
	{
		using std::endl;

		wos << L"������ ǥ���մϴ�." << endl;
		wos << s.m_name << std::endl;

		if (s.m_gender == Gender::MALE)
			wos << L"����: " << L"��" << endl;
		else
			wos << L"����: " << L"��" << endl;

		if (s.m_tribe == Tribe::HUMAN)
			wos << L"����: " << L"�ΰ�"   << endl;
		else if (s.m_tribe == Tribe::ELF)
			wos << L"����: " << L"����"   << endl;
		else
			wos << L"����: " << L"�����" << endl;

		wos << L"����: "   << s.m_age << endl
			<< L"ü��: "   << s.m_hp  << endl
			<< L"����: "   << s.m_mp  << endl
			<< L"����ġ: " << s.m_exp << endl;

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
	// ���� ������ ������ (MyCharacter Ŭ������ ������ ���� ���������) - ����
	friend std::wostream& operator << (std::wostream& wos, const MyCharacter& mc);
	// ���� ������ ������ (MyCharacter Ŭ������ �����ͷ� ���������) - ����
	friend std::wostream& operator << (std::wostream& wos, const MyCharacter* mc);
	
public:
	MyCharacter();

};

