#ifndef SCREEN_H
#define SCREEN_H

class Screen
{
public:
	virtual void draw() const = 0;
};

class HomeScreen : public Screen
{
private:
public:
	void draw() const override;
};

#endif