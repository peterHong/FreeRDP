/*
   FreeRDP: A Remote Desktop Protocol client.
   GDI Shape Functions

   Copyright 2010-2011 Marc-Andre Moreau <marcandre.moreau@gmail.com>

   Licensed under the Apache License, Version 2.0 (the "License");
   you may not use this file except in compliance with the License.
   You may obtain a copy of the License at

       http://www.apache.org/licenses/LICENSE-2.0

   Unless required by applicable law or agreed to in writing, software
   distributed under the License is distributed on an "AS IS" BASIS,
   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
   See the License for the specific language governing permissions and
   limitations under the License.
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include <freerdp/freerdp.h>
#include "gdi.h"

#include "gdi_32bpp.h"
#include "gdi_16bpp.h"
#include "gdi_8bpp.h"

#include "gdi_shape.h"

pFillRect FillRect_[5];

static void Ellipse_Bresenham(HDC hdc, int x1, int y1, int x2, int y2)
{
	int a, b, c;
	int e, e2;
	int dx, dy;

	HBITMAP bmp;
	uint8 pixel8;
	uint16 pixel16;
	uint32 pixel32;
	int bpp = hdc->bitsPerPixel;

	a = (x1 < x2) ? x2 - x1 : x1 - x2;
	b = (y1 < y2) ? y2 - y1 : y1 - y2;
	c = b & 1;

	dx = 4 * (1 - a) * b * b;
	dy = 4 * (c + 1) * a * a;

	if (x2 > x1)
	{
		x2 = x1;
		x2 += a;
	}

	if (y2 > y1)
		y2 = y1;

	y1 += (b + 1) / 2;
	y2 = y1 - c;

	a *= 8 * a;
	c = 8 * b * b;

	pixel8 = pixel16 = pixel32 = 0;
	bmp = (HBITMAP) hdc->selectedObject;

	do
	{
		if (bpp == 32)
		{
			SetPixel_32bpp(bmp, x2, y1, pixel32);
			SetPixel_32bpp(bmp, x1, y1, pixel32);
			SetPixel_32bpp(bmp, x1, y2, pixel32);
			SetPixel_32bpp(bmp, x2, y2, pixel32);
		}
		else if (bpp == 16)
		{
			SetPixel_16bpp(bmp, x2, y1, pixel16);
			SetPixel_16bpp(bmp, x1, y1, pixel16);
			SetPixel_16bpp(bmp, x1, y2, pixel16);
			SetPixel_16bpp(bmp, x2, y2, pixel16);
		}
		else if (bpp == 8)
		{
			SetPixel_8bpp(bmp, x2, y1, pixel8);
			SetPixel_8bpp(bmp, x1, y1, pixel8);
			SetPixel_8bpp(bmp, x1, y2, pixel8);
			SetPixel_8bpp(bmp, x2, y2, pixel8);
		}

		e2 = 2 * e;

		if (e2 >= dx)
		{
			x1++;
			x2--;
			e += dx += c;
		}

		if (e2 >= dy)
		{
			y1++;
			y2--;
			e += dy += a;
		}
	}
	while (x1 <= x2);

	while (y1 - y2 < b)
	{
		if (bpp == 32)
		{
			SetPixel_32bpp(bmp, x1 - 1, ++y1, pixel32);
			SetPixel_32bpp(bmp, x1 - 1, --y2, pixel32);
		}
		else if (bpp == 16)
		{
			SetPixel_16bpp(bmp, x1 - 1, ++y1, pixel16);
			SetPixel_16bpp(bmp, x1 - 1, --y2, pixel16);
		}
		else if (bpp == 8)
		{
			SetPixel_8bpp(bmp, x1 - 1, ++y1, pixel8);
			SetPixel_8bpp(bmp, x1 - 1, --y2, pixel8);
		}
	}
}

/**
 * Draw an ellipse
 * @param hdc device context
 * @param nLeftRect x1
 * @param nTopRect y1
 * @param nRightRect x2
 * @param nBottomRect y2
 * @return
 */
int Ellipse(HDC hdc, int nLeftRect, int nTopRect, int nRightRect, int nBottomRect)
{
	Ellipse_Bresenham(hdc, nLeftRect, nTopRect, nRightRect, nBottomRect);
	return 1;
}

/**
 * Fill a rectangle with the given brush.\n
 * @msdn{dd162719}
 * @param hdc device context
 * @param rect rectangle
 * @param hbr brush
 * @return 1 if successful, 0 otherwise
 */

int FillRect(HDC hdc, HRECT rect, HBRUSH hbr)
{
	return FillRect_[IBPP(hdc->bitsPerPixel)](hdc, rect, hbr);
}

/**
 *
 * @param hdc device context
 * @param lpPoints array of points
 * @param nCount number of points
 * @return
 */
int Polygon(HDC hdc, POINT *lpPoints, int nCount)
{
	return 1;
}

/**
 * Draw a series of closed polygons
 * @param hdc device context
 * @param lpPoints array of series of points
 * @param lpPolyCounts array of number of points in each series
 * @param nCount count of number of points in lpPolyCounts
 * @return
 */
int PolyPolygon(HDC hdc, POINT *lpPoints, int *lpPolyCounts, int nCount)
{
	return 1;
}

/**
 * Draw a rectangle
 * @param hdc device context
 * @param nLeftRect x1
 * @param nTopRect y1
 * @param nRightRect x2
 * @param nBottomRect y2
 * @return
 */
int Rectangle(HDC hdc, int nLeftRect, int nTopRect, int nRightRect, int nBottomRect)
{
	return 1;
}

void ShapeInit()
{
	/* FillRect */
	FillRect_[1] = FillRect_8bpp;
	FillRect_[2] = FillRect_16bpp;
	FillRect_[4] = FillRect_32bpp;
}