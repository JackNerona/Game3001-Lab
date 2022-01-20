#pragma once
#ifndef __STARSHIP__
#define __STARSHIP__

#include "DisplayObject.h"

class StarShip final : public DisplayObject {
public:
	StarShip();
	~StarShip();

	// Inherited via GameObject
	virtual void draw() override;
	virtual void update() override;
	virtual void clean() override;

private:

};


#endif /* defined (__STARSHIP__) */