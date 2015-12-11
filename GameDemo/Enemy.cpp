#include "stdafx.h"
#include "Enemy.h"


CEnemy::CEnemy()
{
	m_ptPos.x = 50;
	m_ptPos.y = 100;
}


CEnemy::~CEnemy()
{
}

CImageList CEnemy::m_Images;

BOOL Draw(CDC* pDC, BOOL bPause);

static BOOL LoadImage();

BOOL CEnemy::Draw(CDC* pDC, BOOL bPause)
{

	return m_Images.Draw(pDC, 0, m_ptPos, ILD_NORMAL);
}

