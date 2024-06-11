#pragma once
class Sample : public MyCore
{
	MyActer objScreen; // »ï°¢Çü
	std::vector<MyActer> m_UIList;
	std::vector<MyNpc> m_npcList;
	MyHero hero;
public:
	void   Init() override;
	void   Frame() override;
	void   Render() override;
	void   Release() override;

};