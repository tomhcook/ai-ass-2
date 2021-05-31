#include "bots.h"
void cbotSimple::ChooseNextGridPosition() {

	
		if (PositionX() > gTarget.PositionX()) {
			SetNext((PositionX() - 1), (PositionY()), gLevel);
		}
		else if (PositionX() < gTarget.PositionX()) SetNext((PositionX() + 1), (PositionY()), gLevel);

	
		if (PositionY() > gTarget.PositionY()) {
			SetNext((PositionX()), (PositionY()-1), gLevel);
		}
		else if (PositionY() < gTarget.PositionY()) SetNext((PositionX()), (PositionY()+1), gLevel);

}