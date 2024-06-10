#pragma once
class Sample : public TCore
{
	TActer objScreen; // »ï°¢Çü
	std::vector<TActer> m_UIList;
	std::vector<TNpc> m_npcList;
	THero hero;
public:
	void   Init() override;
	void   Frame() override;
	void   Render() override;
	void   Release() override;

};