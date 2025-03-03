﻿
// SameGameView.cpp: реализация класса CSameGameView
//

#include "stdafx.h"
// SHARED_HANDLERS можно определить в обработчиках фильтров просмотра реализации проекта ATL, эскизов
// и поиска; позволяет совместно использовать код документа в данным проекте.
#ifndef SHARED_HANDLERS
#include "SameGame.h"
#endif

#include "SameGameDoc.h"
#include "SameGameView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CSameGameView

IMPLEMENT_DYNCREATE(CSameGameView, CView)

BEGIN_MESSAGE_MAP(CSameGameView, CView)
	ON_WM_LBUTTONDOWN()
END_MESSAGE_MAP()

// Создание или уничтожение CSameGameView

CSameGameView::CSameGameView() noexcept
{
	// TODO: добавьте код создания

}

CSameGameView::~CSameGameView()
{
}

BOOL CSameGameView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: изменить класс Window или стили посредством изменения
	//  CREATESTRUCT cs


	return CView::PreCreateWindow(cs);
}


// Рисование CSameGameView

void CSameGameView::OnDraw(CDC* pDC) // MFC will comment out the argument name by default; uncomment it
{
	//  Вначале создаем указатель на Document
	CSameGameDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	//  Сохраняем текущее состояние контекста устройства
	int nDCSave = pDC->SaveDC();
	//  Получаем размеры клиентской области
	CRect rcClient;
	GetClientRect(&rcClient);
	COLORREF clr = pDoc->GetBoardSpace(-1, -1);
	//	Сначала отрисовываем фон
	pDC->FillSolidRect(&rcClient, clr);
	//  Создаем кисть для рисования
	CBrush br;
	br.CreateStockObject(HOLLOW_BRUSH);
	CBrush* pbrOld = pDC->SelectObject(&br);
	//	Рисуем блоки
	for (int row = 0; row < pDoc->GetRows(); row++)
	{
		for (int col = 0; col < pDoc->GetColumns(); col++)
		{
			clr = pDoc->GetBoardSpace(row, col);
			//  Вычисляем размер и позицию игрового пространства
			CRect rcBlock;
			rcBlock.top = row * pDoc->GetHeight();
			rcBlock.left = col * pDoc->GetWidth();
			rcBlock.right = rcBlock.left + pDoc->GetWidth();
			rcBlock.bottom = rcBlock.top + pDoc->GetHeight();
			//  Заполняем блок соответствующим цветом
			pDC->FillSolidRect(&rcBlock, clr);
			//  Рисуем контур
			pDC->Rectangle(&rcBlock);
		}
	}
	//  Восстанавливаем контекст устройства
	pDC->RestoreDC(nDCSave);
	br.DeleteObject();
}

// Диагностика CSameGameView

#ifdef _DEBUG
void CSameGameView::AssertValid() const
{
	CView::AssertValid();
}

void CSameGameView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CSameGameDoc* CSameGameView::GetDocument() const // встроена неотлаженная версия
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CSameGameDoc)));
	return (CSameGameDoc*)m_pDocument;
}
#endif //_DEBUG


// Обработчики сообщений CSameGameView


void CSameGameView::OnLButtonDown(UINT nFlags, CPoint point)
{
	//  Вначале создаем указатель на Document
	CSameGameDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	//  Получаем индекс строки и столбца элемента, по которому был клик мышкой
	int row = point.y / pDoc->GetHeight();
	int col = point.x / pDoc->GetWidth();
	//  Удаляем блоки из Document
	int count = pDoc->DeleteBlocks(row, col);
	//  Проверяем, было ли удаление блоков
	if (count > 0)
	{
		//  Перерисовываем View
		Invalidate();
		UpdateWindow();
		//  Проверяем, закончилась ли игра
		if (pDoc->IsGameOver())
		{
			//  Получаем количество оставшихся блоков
			int remaining = pDoc->GetRemainingCount();
			CString message;
			message.Format(_T("Нет доступных ходов\nКоличество оставшихся блоков: %d"),
				remaining);
			//  Отображаем пользователю результат игры
			MessageBox(message, _T("Игра Закончена"), MB_OK | MB_ICONINFORMATION);
		}
	}
	// TODO: добавьте свой код обработчика сообщений или вызов стандартного

	CView::OnLButtonDown(nFlags, point);
}


void CSameGameView::OnInitialUpdate()
{
	
	
	CView::OnInitialUpdate();

	//  Resize the window
	ResizeWindow();

	// TODO: добавьте специализированный код или вызов базового класса
}

void CSameGameView::ResizeWindow()
{
	//  Вначале создаем указатель на Document
	CSameGameDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	//  Получаем размеры клиентской области
	CRect rcClient, rcWindow;
	GetClientRect(&rcClient);
	GetParentFrame()->GetWindowRect(&rcWindow);
	//  Вычисляем разницу
	int nWidthDiff = rcWindow.Width() - rcClient.Width();
	int nHeightDiff = rcWindow.Height() - rcClient.Height();
	//  Изменяем размеры окна на основе полученных данных
	rcWindow.right = rcWindow.left +
		pDoc->GetWidth() * pDoc->GetColumns() + nWidthDiff;
	rcWindow.bottom = rcWindow.top +
		pDoc->GetHeight() * pDoc->GetRows() + nHeightDiff;
	//  Функция MoveWindow изменяет размеры окна
	GetParentFrame()->MoveWindow(&rcWindow);
}
