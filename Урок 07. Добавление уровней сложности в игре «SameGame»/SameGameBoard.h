#pragma once


class CSameGameBoard
{
public:
	/*  ����������� ��-��������� */
	CSameGameBoard(void);
	/*  ����������  */
	~CSameGameBoard(void);
	/*  ������� ��� ��������� ����������� ������ � ������ ���� */
	void SetupBoard(void);
	/*  �������� ���� � ����������� ������� �������� ���� */
	COLORREF GetBoardSpace(int row, int col);
	/*  ������� ��� ��������� ���������� � ���������� �������� ���� */
	int GetWidth(void) const { return m_nWidth; }
	int GetHeight(void) const { return m_nHeight; }
	int GetColumns(void) const { return m_nColumns; }
	int GetRows(void) const { return m_nRows; }
	/*  ������ � ������� ��� ���������� ������ */
	int GetNumColors(void) { return m_nColors; }
	void SetNumColors(int nColors)
	{	m_nColors = (nColors >= 3 && nColors <= 7) ? nColors : m_nColors;	}

	/*  �� ��������� ����? */
	bool IsGameOver(void) const;
	/*  ������� ���������� ���������� ������ */
	int GetRemainingCount(void) const { return m_nRemaining; }
	/*  ������� ��� �������� ���� ����������� ������ */
	int DeleteBlocks(int row, int col);
	/*  ������� ��� �������� �������� ���� � ������������ ������ */
	void DeleteBoard(void);
	
private:
	/*  ������� ��� �������� �������� ���� � ��������� ������ ��� ���� */
	void CreateBoard(void);
	/*  ������������ � ���������� ����������� (������ �� ������). ����������� ��� �������� ������ */
	enum Direction
	{
		DIRECTION_UP,
		DIRECTION_DOWN,
		DIRECTION_LEFT,
		DIRECTION_RIGHT
	};
	/*  ��������������� ����������� ������� ��� �������� ����������� ������ */
	int DeleteNeighborBlocks(int row, int col, int color,
		Direction direction);
	/*  ������� ��� ������ ����� ����� ����, ��� ���� ������� ����� */
	void CompactBoard(void);
	/*  ��������� �� ��������� ������ */
	int** m_arrBoard;
	/*  ������ ������, 0 � ���� ����, 1-7 - ����� ������ */
	static COLORREF m_arrColors[8];

	/*  ���������� � ������� �������� ���� */
	int m_nColumns;
	int m_nRows;
	int m_nHeight;
	int m_nWidth;

	/*  ���������� ���������� ������ */
	int m_nRemaining;
	/*  ���������� ������ */
	int m_nColors;

};

