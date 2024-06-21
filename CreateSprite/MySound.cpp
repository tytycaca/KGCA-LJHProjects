#include "MySound.h"

bool MySound::Load(std::wstring filename)
{
	// 1���� ���� ���� ������ 1���� ä���� ���������.
	m_fVolume = 0.5f;
	FMOD_RESULT hr = m_pFmodSystem->createSound(to_wm(filename).c_str(), FMOD_DEFAULT, 0, &m_pSound);
	if (hr == FMOD_OK)
	{
		return true;
	}

	return false;
}

FMOD::Channel* MySound::Play(bool bLoop)
{
	// ä��: ����Ǵ� ���� ��� ����Ѵ�.
	FMOD::Channel* pChannel = nullptr;
	FMOD_RESULT hr = m_pFmodSystem->playSound(m_pSound, nullptr, false, &pChannel);

	m_pChannel = pChannel;
	if (hr == FMOD_OK)
	{
		m_pChannel->setVolume(m_fVolume);
		m_pSound->getLength(&m_sizeMS, FMOD_TIMEUNIT_MS);
		_stprintf_s(m_msSound,
			L"��ü�ð�[%02d:%02d:%02d]",
			m_sizeMS / 1000 / 60,
			m_sizeMS / 1000 % 60,
			m_sizeMS / 100 / 60);

		if (bLoop)
		{
			m_pChannel->setMode(FMOD_LOOP_NORMAL); // ���ѹݺ�
		}
		else
		{
			m_pChannel->setMode(FMOD_LOOP_OFF);
		}
	}

	return pChannel;
}

void MySound::PlayEffect()
{
	// ä��: ����Ǵ� ���� ��� ����Ѵ�.
	FMOD::Channel* pChannel = nullptr;
	FMOD_RESULT hr = m_pFmodSystem->playSound(m_pSound, nullptr, false, &pChannel);
	if (hr == FMOD_OK)
	{
	}
}

// �ߴ�
void MySound::Stop()
{
	if (m_pChannel != nullptr)
	{
		m_pChannel->stop();
	}
}

// �Ͻ�����
void MySound::Paused()
{
	if (m_pChannel == nullptr) return;

	// ���� �Ͻ����� ���� �ľ�
	bool bPlay = false;
	m_pChannel->isPlaying(&bPlay);
	if (bPlay == true)
	{
		bool paused;
		m_pChannel->getPaused(&paused);
		m_pChannel->setPaused(!paused);
	}
}

void MySound::VolumeUp(float fVolume)
{
	if (m_pChannel == nullptr) return;
	float fCurrentVolume;
	m_pChannel->getVolume(&fCurrentVolume);
	m_fVolume = fCurrentVolume + fVolume;
	m_fVolume = max(0.0f, m_fVolume);
	m_fVolume = min(1.0f, m_fVolume);
	m_pChannel->setVolume(m_fVolume);
}

void MySound::VolumeDown(float fVolume)
{
	if (m_pChannel == nullptr) return;
	float fCurrentVolume;
	m_pChannel->getVolume(&fCurrentVolume);
	m_fVolume = fCurrentVolume - fVolume;
	m_fVolume = max(0.0f, m_fVolume);
	m_fVolume = min(1.0f, m_fVolume);
	m_pChannel->setVolume(m_fVolume);
}

void MySound::Init()
{
}

void MySound::Frame()
{
	if (m_pChannel == nullptr) return;
	unsigned int ms;
	m_pChannel->getPosition(&ms, FMOD_TIMEUNIT_MS);
	_stprintf_s(m_msSound,
		L"����ð�[%02d:%02d:%02d]\n",
		ms / 1000 / 60,
		ms / 1000 % 60,
		ms / 10 / 60);
}

void MySound::Render()
{
}

void MySound::Release()
{
	if (m_pSound)
	{
		Stop();
		m_pSound->release();
	}
	m_pSound = nullptr;
}
