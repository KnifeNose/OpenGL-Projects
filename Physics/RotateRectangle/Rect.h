#ifndef RECT_H
#define RECT_H
class Rect
{
public:
	void drawRect(float x, float y, float witdth, float height, float speed);

	void startPos(float x, float y);

	void rotateRect(float speed);

	float posX = 0;
	float posY = 0;
	


};





#endif
