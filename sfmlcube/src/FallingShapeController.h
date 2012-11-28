/*
 * FallingShapeController.h
 *
 *  Created on: Nov 27, 2012
 *      Author: imizus
 */

#ifndef FALLINGSHAPECONTROLLER_H_
#define FALLINGSHAPECONTROLLER_H_

#include "movingcubes/Shape.h"
#include "movingcubes/ShapeKinematics.h"
#include "movingcubes/ShapeDynamics.h"

#include "WallsController.h"
#include "FallenController.h"

using namespace sfmlcubes::movingcubes;

namespace sfmlcubes
{

	enum FallingShapeControllerState
	{
		fscsFlying,
		fscsLanded
	};

	class FallingShapeController : public ShapeContainer
	{
		static float ROTATION_LONGITUDE;
		static float FALLING_DOWN_LONGITUDE;
		static float FALLING_DOWN_FAST_LONGITUDE;
		static float HORIZONTAL_MOVING_LONGITUDE;

	private:
		Shape falling;

		WallsController& wallsController;
		FallenController& fallenController;

		ShapeKinematics fallingKinematics;
		ShapeDynamics fallingDynamics;

		bool fastFalling, movingRight, movingLeft, fallDownPending, rotatingCW;
		FallingShapeControllerState state;
	protected:
		void updateObstacles();

		bool createTBlock(const sf::Color& gen, const Shape& fallen);
		bool createJBlock(const sf::Color& gen, const Shape& fallen);
		bool createLBlock(const sf::Color& gen, const Shape& fallen);
		bool createIBlock(const sf::Color& gen, const Shape& fallen);
		bool createOBlock(const sf::Color& gen, const Shape& fallen);
		bool createSBlock(const sf::Color& gen, const Shape& fallen);
		bool createZBlock(const sf::Color& gen, const Shape& fallen);

	public:
		FallingShapeController(WallsController& wallsController, FallenController& fallenController);

		const Shape& getShape() const { return falling; }
		void setShape(const Shape& shape) { falling = shape; }

		void processTimeStep(float dt);
		void fallDown();
		void turnOnFastFalling();
		void turnOnRight();
		void turnOnLeft();
		void turnOnRotateCW();
		void turnOffFastFalling();
		void turnOffRight();
		void turnOffLeft();
		void turnOffRotateCW();

		FallingShapeControllerState getState() const { return state; }

		void clearShape();
		bool createNewShape();

		virtual ~FallingShapeController();
	};

}
#endif
