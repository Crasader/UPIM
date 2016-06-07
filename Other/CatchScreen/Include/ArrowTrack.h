#pragma once
#include "track.h"
class CArrowTrack :
	public CTrack
{
public:
	CArrowTrack(HDC hDC, COLORREF crTrackColor) ;
	~CArrowTrack(void);
protected:
	// ���ݹ켣������ļ���
	virtual BOOL CreatePos();

	// ������
	virtual void Draw(const CPoint& ptStart, const CPoint& ptEnd) const;

};

