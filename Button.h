#pragma once

class Button
	{
	public:
		int row;
		int column;
		long color;

		Button()
			{
			this->color = 0xFFFFFF;
			}
		void SetRowColumn(int row, int column)
			{
			this->row = row;
			this->column = column;
			}

		void SetColor(long int color)
			{
			this->color = color;
			neoTrellisM4.setPixelColor(this->row * BUTTON_COLUMNS + this->column, this->color);
			}

		virtual void Press()
			{
			SetColor(0xFFFFFF);
			}

		virtual void Release()
			{
			SetColor(0);
			}
	};
