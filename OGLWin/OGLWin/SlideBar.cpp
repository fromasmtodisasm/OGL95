#include <Windows.h>
#include <gl/GL.h>
#include "freeglut.h"
#include "SlideBar.h"
#include "GLFont.h"
#include <sstream>

SlideBar::SlideBar()
{
}

SlideBar::SlideBar(char* id, float lowNum, float highNum, float x, float y)
{
	//Instanciates the SlideBar, takes the left X and Y, low value and high value in the constructor along with an ID
	//The ID, low and high values wont be changable once instanciated. However, the left X and Y will move depending on window which will
	//be called with the SetXY function, this will be called everytime the render function is called from the host window.
	
	ID = id; 
	lowNumber = lowNum;
	highNumber = highNum;

	slideBarLeft.SetX(x);
	slideBarLeft.SetY(y);

	slideBarLX = slideBarLeft.GetX(), slideBarLY = slideBarLeft.GetY();
	slideBarRX = slideBarLeft.GetX() + 200.0f, slideBarRY = slideBarLeft.GetY();

	SliderPoint.SetX((slideBarLX));
	SliderPoint.SetY(slideBarLY);

	spX = SliderPoint.GetX();
	spY = SliderPoint.GetY();

	leftDifference = (spX - slideBarLX);
}

SlideBar::~SlideBar()
{
 
}

void SlideBar::SetAlpha(float _alpha)
{
	alpha = _alpha;
}

void SlideBar::SetXY(float x, float y)
{
	slideBarLeft.SetX(x);
	slideBarLeft.SetY(y);

	spY = y - 14;
	spX = slideBarLeft.GetX() + leftDifference;
}

float SlideBar::ReturnValue()
{
	return value;
}

void SlideBar::RenderSlideLine()
{
	slideBarLX = slideBarLeft.GetX(), slideBarLY = slideBarLeft.GetY();
	slideBarRX = slideBarLeft.GetX() + 200.0f, slideBarRY = slideBarLeft.GetY();

	glLineWidth(1);
	glBegin(GL_LINES);
		glColor4f(0.5f, 0.5f, 0.5f, alpha);
			glVertex2f(slideBarLX, slideBarLY);
			glVertex2f(slideBarRX, slideBarRY);
		glEnd();
	glBegin(GL_LINES);
	glColor4f(0.1f, 0.1f, 0.1f, alpha);
	glVertex2f(slideBarRX, slideBarRY + 1.0f);
	glVertex2f(slideBarLX - 1.0f, slideBarRY + 1.0f);

	glColor4f(1.0f, 1.0f, 1.0f, alpha);
	glVertex2f(slideBarRX, slideBarRY - 1.0f);
	glVertex2f(slideBarLX - 1.0f, slideBarRY - 1.0f);
	glEnd();

	//Makes the increment markers 
	glBegin(GL_LINES);
		glColor4f(0.1f, 0.1f, 0.1f, alpha);
			glVertex2f(slideBarLX, slideBarRY - 18.0f);
			glVertex2f(slideBarLX, slideBarRY - 21.0f);
			
			glVertex2f((slideBarLX + 50.0f), slideBarRY - 18.0f);
			glVertex2f((slideBarLX + 50.0f), slideBarRY - 21.0f);

			glVertex2f((slideBarLX + 100.0f), slideBarRY - 18.0f);
			glVertex2f((slideBarLX + 100.0f), slideBarRY - 21.0f);

			glVertex2f((slideBarLX + 150.0f), slideBarRY - 18.0f);
			glVertex2f((slideBarLX + 150.0f), slideBarRY - 21.0f);

			glVertex2f(slideBarRX, slideBarRY - 18.0f);
			glVertex2f(slideBarRX, slideBarRY - 21.0f);
	glEnd();

}

void SlideBar::RenderSlideButton()
{	
	glBegin(GL_QUADS);
		glColor4f((190 / 255.0f), (190 / 255.0f), (194 / 255.0f), alpha);
			glVertex2f(spX - 5.0f, spY + 22.0f);
			glVertex2f(spX - 5.0f, spY + 8.0f);
			glVertex2f(spX + 5.0f, spY + 8.0f);
			glVertex2f(spX + 5.0f, spY + 22.0f);
	glEnd();

	glBegin(GL_TRIANGLES);
		glColor4f((190 / 255.0f), (190 / 255.0f), (194 / 255.0f), alpha);
			glVertex2f(spX - 5.0f, spY + 8.0f);
			glVertex2f(spX, spY);
			glVertex2f(spX + 5.0f, spY + 8.0f);
	glEnd();

	glLineWidth(2.0f);
	glBegin(GL_LINES);
		glColor4f(1.0f, 1.0f, 1.0f, alpha);
			glVertex2f(spX + 5.0f, spY + 22.0f);
			glVertex2f(spX - 6.0f, spY + 22.0f);

			glVertex2f(spX - 6.0f, spY + 22.0f);
			glVertex2f(spX - 6.0f, spY + 8.0f);

			glVertex2f(spX - 6.0f, spY + 8.0f);
			glVertex2f(spX, spY);

		glColor4f(0.1f, 0.1f, 0.1f, alpha);
			glVertex2f(spX + 1.0f, spY);
			glVertex2f(spX + 6.0f, spY + 8.0f);

			glVertex2f(spX + 6.0f, spY + 8.0f);
			glVertex2f(spX + 6.0f, spY + 22.0f);
	glEnd();
}

void SlideBar::RenderValueDisplay()
{
	glEnable(GL_BLEND);
	glBegin(GL_QUADS);
		glColor4f(1.0f, 1.0f, 1.0f, alpha);
			glVertex2f(slideBarRX + 10.0f, slideBarRY);
			glVertex2f(slideBarRX + 10.0f, slideBarRY - 15.0f);
			glVertex2f(slideBarRX + 69.0f, slideBarRY - 15.0f);
			glVertex2f(slideBarRX + 69.0f, slideBarRY);
	glEnd();

	glBegin(GL_LINES);
		glColor4f(0.3f, 0.3f, 0.3f, alpha);
			glVertex2f(slideBarRX + 69.0f, slideBarRY + 1.0f);
			glVertex2f(slideBarRX + 9.0f, slideBarRY + 1.0f);

			glVertex2f(slideBarRX + 9.0f, slideBarRY + 1.0f);
			glVertex2f(slideBarRX + 9.0f, slideBarRY - 16.0f);

		glColor4f(0.8f, 0.8f, 0.8f, alpha);
			glVertex2f(slideBarRX + 9.0f, slideBarRY - 16.0f);
			glVertex2f(slideBarRX + 70.0f, slideBarRY - 16.0f);
			glVertex2f(slideBarRX + 70.0f, slideBarRY - 16.0f);
			glVertex2f(slideBarRX + 70.0f, slideBarRY + 1.0f);
	glEnd();

	float percentage;

	//This gets the ratio of where the pointer is in relation to the left and right (X) of the total bar. 
	if (slideBarLX >= 0)
	{
		percentage = ((spX - slideBarLX) / (slideBarRX - slideBarLX)) * 100;
	}
	else
	{
		percentage = ((spX + fabsf(slideBarLX)) / (slideBarRX - slideBarLX)) * 100;
	}

	//The slider happens to go above the bound by a float or two, this will be ignored as the value is set to the min/max bound by the mousemove function.
	//This will take over once the user puts the slider back in bounds.
	if (!belowLowerBound && !aboveUpperBound)
	{
		value = (highNumber - lowNumber) * (percentage / 100);
	}

	std::ostringstream converter;
	converter << value;
	converter.precision(0);
	std::string valueString(converter.str());

	GLFont *valueLabel = new GLFont();
	valueLabel->Create("franklin_gothic.glf");
	valueLabel->Begin();
		glColor4f(0.0f, 0.0f, 0.0f, alpha);
		valueLabel->RenderText(valueString.c_str(), slideBarRX + 10.0f, slideBarRY, 0, 6);
	valueLabel->End();
	delete valueLabel;

}

void SlideBar::RenderLabel()
{
	GLFont *Label = new GLFont();
	Label->Create("another_font.glf");
	Label->Begin();
	glColor4f(0.0f, 0.0f, 0.0f, alpha);
	Label->RenderText(ID, slideBarLX - 10.0f, slideBarLY + 30.0f, 0, 6.0f);
	Label->End();
	delete Label;
}

void SlideBar::Render()
{
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_BLEND);

	RenderSlideLine();
	RenderSlideButton();
	RenderLabel();
	RenderValueDisplay();
}

bool SlideBar::MouseMove(int x, int y)
{
	if (mouseDown)
	{
		if (sliderClicked)
		{
			//Standard mouse move stuff. If the "slider point" goes out of bounds, it will take over control and get the value itself. 
			if (spX <= slideBarLX)
			{
				belowLowerBound = true; 
				value = lowNumber;
				leftDifference += 1.0f; 
			}
			else if (spX >= slideBarRX)
			{
				aboveUpperBound = true; 
				value = highNumber; 
				leftDifference -= 1.0f; 
			}
			else
			{
				belowLowerBound = false;
				aboveUpperBound = false; 
				leftDifference = leftDifference + x;
			}
		}
	}
	
	oldX = x;
	oldY = y;
	return true;
}

bool SlideBar::MouseLBUp(int x, int y)
{
	mouseDown = false;
	sliderClicked = false;
	return true;
}

bool SlideBar::MouseLBDown(int x, int y)
{
	oldX = x;
	oldY = y;

	if ((float)x > spX - 6.0f && (float)x < spX + 6.0f && (float)y < spY + 22.0f && (float)y > spY + 8.0f)
	{
		mouseDown = true; 
		sliderClicked = true;

		return true;
	}
	return false;
}

bool SlideBar::MouseRBDown(int x, int y)
{
	return false;
}
