#include "stdafx.h"
#include "Me.h"


CMe::CMe()
{
	m_nHorMotion = 0;
	m_nVerMotion = 0;
	m_ptPos.x = 300;
	m_ptPos.y = 500;
}

CImageList CMe::m_Images;

CMe::~CMe()
{
}

BOOL CMe::Draw(CDC* pDC, BOOL bPause)
{
	m_ptPos.x += m_nHorMotion * 5;
	return m_Images.Draw(pDC, 0, m_ptPos, ILD_NORMAL);
}

BOOL CMe::LoadImage()
{
	return CGameObject::LoadImage(m_Images, IDB_ME, RGB(0, 0, 0), PLANE_WIDTH, PLANE_WIDTH, 1);
}
