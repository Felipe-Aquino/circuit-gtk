#ifndef __CIRCLE_H_
#define __CIRCLE_H_

	#include <cmath>
	#include "Shape.h"

	using namespace std;

namespace Shapes {
	class Circle : public Shape {
	protected:
	float _r;

	public:
		Circle();
		Circle(float, float, float);
		Circle(Circle&);

		virtual void incCenter(float, float);

		float getRadius();
		void setRadius(float);

		void print();
		virtual void draw(const Cairo::RefPtr<Cairo::Context>& cr);
		bool isInside(float x, float y);
		void drawCircunference(const Cairo::RefPtr<Cairo::Context>& cr);
		virtual ~Circle();
	};
}
#endif