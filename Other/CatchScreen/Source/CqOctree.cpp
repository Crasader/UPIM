
/////////////////////////////////////////////////////////////////////////////
/**
* �ļ���  ��CqOctree.CPP
* �汾��  ��V1.0
* ��Ŀ���ƣ�CPH
* ��Ȩ������Copyright 2002-2003 . All Rights Reserved.
* ģ���������ִ����ɫ���ӻ��Ķ��������㣬��������ȫ�ֺ���
*     HPALETTE CreateOctreePalette (HBITMAP hImage, UINT nMaxColors, UINT nColorBits)
	  HPALETTE CreateOctreePalette (LPSTR lpDIB, UINT nMaxColors, UINT nColorBits)
*Ϊʹ�÷�������Ƕ�����DIBAPI.H��
*======================================================
* �汾�����¼:
*      v1.0  2002-11-11   
*
* 
*/

/////////////////////////////////////////////////////////////////////////////


#include "stdafx.h"
#include "..\Include\dibapi.h"

// ���ڽṹ
typedef struct _NODE 
{
    // ȷ�Ž�����ӽ��
	BOOL bIsLeaf;               
     // Ҷ������ص�����
    UINT nPixelCount; 
	// ��ɫ�ɷ�ֵ
    UINT nRedSum; 
	// ��ɫ�ɷ�ֵ       
    UINT nGreenSum;
	// ��ɫ�ɷ�ֵ
    UINT nBlueSum;              
    // �ӽڵ�ָ��
    struct _NODE* pChild[8];    
     // ָ����һ�����
    struct _NODE* pNext;       

} NODE;

// ����ԭ�Ͷ�����dibapi.h����Ϊȫ�ֺ���
//HPALETTE CreateOctreePalette (HDIB hDIB, UINT nMaxColors, UINT nColorBits)
//HPALETTE CreateOctreePalette (LPSTR lpDIB, UINT nMaxColors, UINT nColorBits)

//��������ʹ��
HPALETTE BuildOctreePalette(HANDLE hImage, UINT nMaxColors, UINT nColorBits);
void AddColor (NODE**, BYTE, BYTE, BYTE, UINT, UINT, UINT*, NODE**);
NODE* CreateNode (UINT, UINT, UINT*, NODE**);
void ReduceTree (UINT, UINT*, NODE**);
void DeleteTree (NODE**);
void GetPaletteColors (NODE*, PALETTEENTRY*, UINT*);
int GetRightShiftCount (DWORD);
int GetLeftShiftCount (DWORD);

// ������
/*
*--------------------------------------------------------------------------------
*  ��Ա������   :CreateOctreePalette
*  ��������     :����Octree����ɫ��
*  �����������	:
*  HDIB hDIB��DIB���
*  UINT nMaxColors�������ɫ��
*  UINT nColorBits����ɫλ��
*  ���ر���˵�� :���ش����ĵ�ɫ����
*  �㷨����		:
*  ����˵��     :
*--------------------------------------------------------------------------------
*/
HPALETTE CreateOctreePalette(HDIB hDIB, UINT nMaxColors, UINT nColorBits)
{
	HANDLE hImage;

	hImage = DIBToDIBSection(hDIB);
	if (! hImage)
		return NULL;
	return BuildOctreePalette(hImage, nMaxColors, nColorBits);
}

/*
*--------------------------------------------------------------------------------
*  ��Ա������   :CreateOctreePalette
*  ��������     :����Octree����ɫ��
*  �����������	:
*  LPBYTE lpDIB��DIBָ��
*  UINT nMaxColors�������ɫ��
*  UINT nColorBits����ɫλ��
*  ���ر���˵�� :���ش����ĵ�ɫ����
*  �㷨����		:
*  ����˵��     :
*--------------------------------------------------------------------------------
*/
HPALETTE CreateOctreePalette(LPBYTE lpDIB, UINT nMaxColors, UINT nColorBits)
{
	HANDLE hImage;

	hImage = DIBToDIBSection(lpDIB);
	if (! hImage)
		return NULL;
	return BuildOctreePalette(hImage, nMaxColors, nColorBits);
}

/*
*--------------------------------------------------------------------------------
*  ��Ա������   :BuildOctreePalette
*  ��������     :����Octree����ɫ��
*  �����������	:
*  HANDLE hImage:λͼ���
*  UINT nMaxColors�������ɫ��
*  UINT nColorBits����ɫλ��
*  ���ر���˵�� :���ش����ĵ�ɫ����
*  �㷨����		:
*  ����˵��     :
*--------------------------------------------------------------------------------
*/
HPALETTE BuildOctreePalette(HANDLE hImage, UINT nMaxColors, UINT nColorBits)
{
    DIBSECTION ds;
    int i, j, nPad;
    BYTE* pbBits;
    WORD* pwBits;
    DWORD* pdwBits;
    DWORD rmask, gmask, bmask;
    int rright, gright, bright;
    int rleft, gleft, bleft;
    BYTE r, g, b;
    WORD wColor;
    DWORD dwColor, dwSize;
    LOGPALETTE* plp;
    HPALETTE hPalette;
    NODE* pTree;
    UINT nLeafCount, nIndex;
    NODE* pReducibleNodes[9];
    HDC hdc;    
	BYTE* pBuffer;    
	BITMAPINFO bmi;

    // ��ʼ�� octree������
    pTree = NULL;
    nLeafCount = 0;
    if (nColorBits > 8) 
        return NULL;
    for (i=0; i<=(int) nColorBits; i++)
        pReducibleNodes[i] = NULL;

    // ɨ��DIB������octree��
    GetObject (hImage, sizeof (ds), &ds);
    nPad = ds.dsBm.bmWidthBytes - (((ds.dsBmih.biWidth *
        ds.dsBmih.biBitCount) + 7) / 8);

    switch (ds.dsBmih.biBitCount) {

    case 1: // 1-bit DIB    
	case 4: // 4-bit DIB    
	case 8: // 8-bit DIB
    
        hdc = GetDC (NULL);        
		pBuffer = new BYTE[ds.dsBmih.biWidth * 3];
        ZeroMemory (&bmi, sizeof (bmi));
        bmi.bmiHeader.biSize = sizeof (BITMAPINFOHEADER);
        bmi.bmiHeader.biWidth = ds.dsBmih.biWidth;
        bmi.bmiHeader.biHeight = ds.dsBmih.biHeight;
        bmi.bmiHeader.biPlanes = 1;        
		bmi.bmiHeader.biBitCount = 24;
        bmi.bmiHeader.biCompression = BI_RGB;
        for (i=0; i<ds.dsBmih.biHeight; i++) 
		{
            GetDIBits (hdc, (HBITMAP) hImage, i, 1, pBuffer, &bmi,
                DIB_RGB_COLORS);            
			pbBits = pBuffer;
            for (j=0; j<ds.dsBmih.biWidth; j++) 
			{                
				b = *pbBits++;
                g = *pbBits++;                
				r = *pbBits++;
                AddColor (&pTree, r, g, b, nColorBits, 0, &nLeafCount,
                          pReducibleNodes);
                while (nLeafCount > nMaxColors)
                    ReduceTree (nColorBits, &nLeafCount, pReducibleNodes);            
			}        
		}
        delete pBuffer;        
		ReleaseDC (NULL, hdc);        
		break;
		
	//  16-bit DIBs
	case 16: 
        if (ds.dsBmih.biCompression == BI_BITFIELDS) {
            rmask = ds.dsBitfields[0];
            gmask = ds.dsBitfields[1];
            bmask = ds.dsBitfields[2];
        }
        else {
            rmask = 0x7C00;
            gmask = 0x03E0;
            bmask = 0x001F;
        }

        rright = GetRightShiftCount (rmask);
        gright = GetRightShiftCount (gmask);
        bright = GetRightShiftCount (bmask);

        rleft = GetLeftShiftCount (rmask);
        gleft = GetLeftShiftCount (gmask);
        bleft = GetLeftShiftCount (bmask);

        pwBits = (WORD*) ds.dsBm.bmBits;
        for (i=0; i<ds.dsBmih.biHeight; i++) {
            for (j=0; j<ds.dsBmih.biWidth; j++) {
                wColor = *pwBits++;
                b = (BYTE) (((wColor & (WORD) bmask) >> bright) << bleft);
                g = (BYTE) (((wColor & (WORD) gmask) >> gright) << gleft);
                r = (BYTE) (((wColor & (WORD) rmask) >> rright) << rleft);
                AddColor (&pTree, r, g, b, nColorBits, 0, &nLeafCount,
                          pReducibleNodes);
                while (nLeafCount > nMaxColors)
                    ReduceTree (nColorBits, &nLeafCount, pReducibleNodes);
            }
            pwBits = (WORD*) (((BYTE*) pwBits) + nPad);
        }
        break;

    // 24-bit DIBs
    case 24: 
        pbBits = (BYTE*) ds.dsBm.bmBits;
        for (i=0; i<ds.dsBmih.biHeight; i++) {
            for (j=0; j<ds.dsBmih.biWidth; j++) {
                b = *pbBits++;
                g = *pbBits++;
                r = *pbBits++;
                AddColor (&pTree, r, g, b, nColorBits, 0, &nLeafCount,
                          pReducibleNodes);
                while (nLeafCount > nMaxColors)
                    ReduceTree (nColorBits, &nLeafCount, pReducibleNodes);
            }
            pbBits += nPad;
        }
        break;

     // 32-bit DIBs
    case 32: 
        if (ds.dsBmih.biCompression == BI_BITFIELDS) {
            rmask = ds.dsBitfields[0];
            gmask = ds.dsBitfields[1];
            bmask = ds.dsBitfields[2];
        }
        else {
            rmask = 0x00FF0000;
            gmask = 0x0000FF00;
            bmask = 0x000000FF;
        }

        rright = GetRightShiftCount (rmask);
        gright = GetRightShiftCount (gmask);
        bright = GetRightShiftCount (bmask);

        pdwBits = (DWORD*) ds.dsBm.bmBits;
        for (i=0; i<ds.dsBmih.biHeight; i++) {
            for (j=0; j<ds.dsBmih.biWidth; j++) {
                dwColor = *pdwBits++;
                b = (BYTE) ((dwColor & bmask) >> bright);
                g = (BYTE) ((dwColor & gmask) >> gright);
                r = (BYTE) ((dwColor & rmask) >> rright);
                AddColor (&pTree, r, g, b, nColorBits, 0, &nLeafCount,
                          pReducibleNodes);
                while (nLeafCount > nMaxColors)
                    ReduceTree (nColorBits, &nLeafCount, pReducibleNodes);
            }
            pdwBits = (DWORD*) (((BYTE*) pdwBits) + nPad);
        }
        break;

    // DIB ������16, 24, �� 32-bit!
    default: 
        return NULL;
    }

    if (nLeafCount > nMaxColors) { 
        DeleteTree (&pTree);
        return NULL;
    }

    // �����߼���ɫ���octree���е���ɫ
    dwSize = sizeof (LOGPALETTE) + ((nLeafCount - 1) * sizeof (PALETTEENTRY));
    if ((plp = (LOGPALETTE*) HeapAlloc (GetProcessHeap (), 0,
        dwSize)) == NULL) {
        DeleteTree (&pTree);
        return NULL;
    }

    plp->palVersion = 0x300;
    plp->palNumEntries = (WORD) nLeafCount;
    nIndex = 0;
    GetPaletteColors (pTree, plp->palPalEntry, &nIndex);
    hPalette = CreatePalette (plp);

    HeapFree (GetProcessHeap (), 0, plp);
    DeleteTree (&pTree);
    return hPalette;
}

/*
*--------------------------------------------------------------------------------
*  ��Ա������   :AddColor
*  ��������     :������ɫֵ��������
*  �����������	:
*   NODE** ppNode:����ṹָ��
*   BYTE r:��ɫλ��
*   BYTE g:��ɫλ��
*   BYTE b:��ɫλ��
*   UINT nColorBits:��ɫλ��
*   UINT nLevel: �����
*   UINT* pLeafCount:Ҷ�������
*   NODE** pReducibleNodes:����ṹָ��
*  ���ر���˵�� :
*  �㷨����		:
*  ����˵��     :
*--------------------------------------------------------------------------------
*/
void AddColor(NODE** ppNode, BYTE r, BYTE g, BYTE b, UINT nColorBits,
    UINT nLevel, UINT* pLeafCount, NODE** pReducibleNodes)
{
    int nIndex, shift;
    static BYTE mask[8] = { 0x80, 0x40, 0x20, 0x10, 0x08, 0x04, 0x02, 0x01 };

    // �������������򴴽���
    if (*ppNode == NULL)
        *ppNode = CreateNode (nLevel, nColorBits, pLeafCount,
                              pReducibleNodes);

    // ������Ҷ��������ɫ��Ϣ��ͷ
    if ((*ppNode)->bIsLeaf) {
        (*ppNode)->nPixelCount++;
        (*ppNode)->nRedSum += r;
        (*ppNode)->nGreenSum += g;
        (*ppNode)->nBlueSum += b;
    }

    // ����Ҷ���
    else {
        shift = 7 - nLevel;
        nIndex = (((r & mask[nLevel]) >> shift) << 2) |
            (((g & mask[nLevel]) >> shift) << 1) |
            ((b & mask[nLevel]) >> shift);
        AddColor (&((*ppNode)->pChild[nIndex]), r, g, b, nColorBits,
                  nLevel + 1, pLeafCount, pReducibleNodes);
    }
}


/*
*--------------------------------------------------------------------------------
*  ��Ա������   :CreateNode
*  ��������     :����������
*  �����������	:
*   UINT nLevel:���
*   UINT nColorBits:��ɫλͼ
*   UINT* pLeafCount:Ҷָ��
*   NODE** pReducibleNodes :����ṹָ��
*  ���ر���˵�� :
*  �㷨����		:
*  ����˵��     :
*--------------------------------------------------------------------------------
*/
NODE* CreateNode (UINT nLevel, UINT nColorBits, UINT* pLeafCount,
                  NODE** pReducibleNodes)
{
    NODE* pNode;

    if ((pNode = (NODE*) HeapAlloc (GetProcessHeap (), HEAP_ZERO_MEMORY,
        sizeof (NODE))) == NULL)
        return NULL;

    pNode->bIsLeaf = (nLevel == nColorBits) ? TRUE : FALSE;
    if (pNode->bIsLeaf)
        (*pLeafCount)++;
    //Ϊ�������ӵ��б���
    else { 
        pNode->pNext = pReducibleNodes[nLevel];
        pReducibleNodes[nLevel] = pNode;
    }
    return pNode;
}


/*
*--------------------------------------------------------------------------------
*  ��Ա������   :ReduceTree
*  ��������     :��ԭ���ṹ
*  �����������	:
*   UINT nColorBits:��ɫλ��
*   UINT* pLeafCount:Ҷָ��
*   NODE** pReducibleNode:����ṹָ��
*  ���ر���˵�� :
*  �㷨����		:
*  ����˵��     :
*--------------------------------------------------------------------------------
*/
void ReduceTree (UINT nColorBits, UINT* pLeafCount, NODE** pReducibleNodes)
{
    int i;
    NODE* pNode;
    UINT nRedSum, nGreenSum, nBlueSum, nChildren;

    // ��������Ҷ����Լ����ṹ
    for (i=nColorBits - 1; (i>0) && (pReducibleNodes[i] == NULL); i--);

    // �ڲ��i�м򻯽�����ӽ�㵽�б�
    pNode = pReducibleNodes[i];
    pReducibleNodes[i] = pNode->pNext;

    nRedSum = nGreenSum = nBlueSum = nChildren = 0;
    for (i=0; i<8; i++) {
        if (pNode->pChild[i] != NULL) {
            nRedSum += pNode->pChild[i]->nRedSum;
            nGreenSum += pNode->pChild[i]->nGreenSum;
            nBlueSum += pNode->pChild[i]->nBlueSum;
            pNode->nPixelCount += pNode->pChild[i]->nPixelCount;
            HeapFree (GetProcessHeap (), 0, pNode->pChild[i]);
            pNode->pChild[i] = NULL;
            nChildren++;
        }
    }

    pNode->bIsLeaf = TRUE;
    pNode->nRedSum = nRedSum;
    pNode->nGreenSum = nGreenSum;
    pNode->nBlueSum = nBlueSum;
    *pLeafCount -= (nChildren - 1);
}


/*
*--------------------------------------------------------------------------------
*  ��Ա������   :DeleteTree
*  ��������     :ɾ�����ṹ
*  �����������	:
*  NODE** ppNode������ṹָ��
*  ���ر���˵�� :
*  �㷨����		:
*  ����˵��     :
*--------------------------------------------------------------------------------
*/
void DeleteTree(NODE** ppNode)
{
    int i;

    for (i=0; i<8; i++) {
        if ((*ppNode)->pChild[i] != NULL)
            DeleteTree (&((*ppNode)->pChild[i]));
    }
    HeapFree (GetProcessHeap (), 0, *ppNode);
    *ppNode = NULL;
}

/*
*--------------------------------------------------------------------------------
*  ��Ա������   :GetPaletteColors
*  ��������     :�õ���ɫ�����ɫ
*  �����������	:
*  NODE* pTree:  ���ṹָ��
*  PALETTEENTRY* pPalEntries:��ɫ��ָ��
*  UINT* pIndex����ɫ����ָ��
*  ���ر���˵�� :
*  �㷨����		:
*  ����˵��     :
*--------------------------------------------------------------------------------
*/
void GetPaletteColors (NODE* pTree, PALETTEENTRY* pPalEntries, UINT* pIndex)
{
    int i;

    if (pTree->bIsLeaf) {
        pPalEntries[*pIndex].peRed =
            (BYTE) ((pTree->nRedSum) / (pTree->nPixelCount));
        pPalEntries[*pIndex].peGreen =
            (BYTE) ((pTree->nGreenSum) / (pTree->nPixelCount));
        pPalEntries[*pIndex].peBlue =
            (BYTE) ((pTree->nBlueSum) / (pTree->nPixelCount));
        (*pIndex)++;
    }
    else {
        for (i=0; i<8; i++) {
            if (pTree->pChild[i] != NULL)
                GetPaletteColors (pTree->pChild[i], pPalEntries, pIndex);
        }
    }
}


/*
*--------------------------------------------------------------------------------
*  ��Ա������   :GetRightShiftCount
*  ��������     :�õ�����������
*  �����������	:
*  DWORD dwVal:
*  ���ر���˵�� :
*  �㷨����		:
*  ����˵��     :
*--------------------------------------------------------------------------------
*/
int GetRightShiftCount(DWORD dwVal)
{
    int i;

    for (i=0; i<sizeof (DWORD) * 8; i++) {
        if (dwVal & 1)
            return i;
        dwVal >>= 1;
    }
    return -1;
}


/*
*--------------------------------------------------------------------------------
*  ��Ա������   :GetLeftShiftCount
*  ��������     :�õ�����������
*  �����������	:
*  DWORD dwVal:
*  ���ر���˵�� :
*  �㷨����		:
*  ����˵��     :
*--------------------------------------------------------------------------------
*/
int GetLeftShiftCount (DWORD dwVal)
{
    int nCount, i;

    nCount = 0;
    for (i=0; i<sizeof (DWORD) * 8; i++) {
        if (dwVal & 1)
            nCount++;
        dwVal >>= 1;
    }
    return (8 - nCount);
}
