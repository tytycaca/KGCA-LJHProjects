#include "MyScene.h"

void MyScene::InitInstance(MyWriterFont mf)
{
	m_WriterFont = std::make_shared<MyWriterFont>(mf);
}