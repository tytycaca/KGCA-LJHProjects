#include "MyCharacter.h"

Point MyCharacter::getPos()
{
	return m_Point;
}

void MyCharacter::setPos(float p_x_pos, float p_y_pos, float p_z_pos)
{
	m_Point.m_x_pos = p_x_pos;
	m_Point.m_y_pos = p_y_pos;
	m_Point.m_z_pos = p_z_pos;
}

Stat MyCharacter::getStat()
{
	return m_Stat;
}

void MyCharacter::setStat(std::wstring p_name, Gender p_gender, Tribe p_tribe, int p_age, float p_hp, float p_mp, float p_exp)
{
	m_Stat.m_name   = p_name;
	m_Stat.m_gender = p_gender;
	m_Stat.m_tribe  = p_tribe;
	m_Stat.m_age    = p_age;
	m_Stat.m_hp     = p_hp;
	m_Stat.m_mp     = p_mp;
	m_Stat.m_exp    = p_exp;
}

// ���� ������ ������ (MyCharacter Ŭ������ ������ ���� ���������) - ����
std::wostream& operator << (std::wostream& wos, const MyCharacter& mc)
{
	wos << mc.m_Stat << std::endl << mc.m_Point << std::endl;

	return wos;
}

// ���� ������ ������ (MyCharacter Ŭ������ �����ͷ� ���������) - ����
std::wostream& operator << (std::wostream& wos, const MyCharacter* mc)
{
	wos << mc->m_Stat << std::endl << mc->m_Point << std::endl;

	return wos;
}

MyCharacter::MyCharacter() :
	m_Point(0, 0, 0),
	m_Stat(L"FOO", Gender::MALE, Tribe::HUMAN, 0, 0.0f, 0.0f, 0.0f)
{
	std::wcout << L"ĳ���� ��ü�� �����Ͽ����ϴ�." << std::endl << std::endl;
}