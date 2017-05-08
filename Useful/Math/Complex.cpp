#include "Complex.h"

namespace Math {
	Complex::Complex(float r, float i, Format format){
		this->r = r;
		this->i = i;
		this->format = format;
	}
	
	Complex::Complex(const Complex &n){
		format = n.format;
		r = n.r;
		i = n.i;
	}
	
	void Complex::toPolar(){
		if(format == RECT){
			float m = sqrt(r*r + i*i);
			float t;
			if(r != 0)
				t = atan(i/r);
			else
				t = sgn(r)*(pi/2);
			r = m;
			i = t;
			format = POLAR;
		}
	}
	
	void Complex::toRect(){
		if(format == POLAR){
			float a = r*cos(i); 
			float b = r*sin(i);
			r = a;	
			i = b;	
			format = RECT;
		}
	} 
	
	Complex& Complex::operator=(const Complex &n){
		if(this == &n)
			return *this;
		format = n.format;
		r = n.r;
		i = n.i;
		return *this;
	}
	
	const Complex Complex::operator+(const Complex &n0){
		float r1,i1;
		Complex n = n0;
		
		if(format == POLAR){
			this->toRect();
			if(n.format == RECT){
				r1 = r + n.r;
				i1 = i + n.i;
			}
			else if(n.format == POLAR){
				n.toRect();
				r1 = r + n.r;
				i1 = i + n.i;
				n.toPolar();
			}
			this->toPolar();
		}
		else if(format == RECT){
			if(n.format == RECT){
				r1 = r + n.r;
				i1 = i + n.i;
			}
			else if(n.format == POLAR){
				n.toRect();
				r1 = r + n.r;
				i1 = i + n.i;
				n.toPolar();
			}
		}
		
		return Complex(r1,i1);
	}
	
	const Complex Complex::operator+(float n0){
		float r1,i1;
		Complex n(n0, 0.0);
		
		if(format == POLAR){
			this->toRect();
			r1 = r + n.r;
			i1 = i + n.i;
			this->toPolar();
		}
		else if(format == RECT){
			r1 = r + n.r;
			i1 = i + n.i;
		}
		
		return Complex(r1,i1);
	}

	const Complex Complex::operator+=(const Complex &n0){
		*this = *this + n0;
		return *this;
	}

	const Complex Complex::operator+=(float n0){
		*this = *this + n0;
		return *this + n0;
	}

	const Complex Complex::operator-(const Complex &n0){
		float r1,i1;
		Complex n = n0;
		
		if(format == POLAR){
			this->toRect();
			if(n.format == RECT){
				r1 = r - n.r;
				i1 = i - n.i;
			}
			else if(n.format == POLAR){
				n.toRect();
				r1 = r - n.r;
				i1 = i - n.i;
				n.toPolar();
			}
			this->toPolar();
		}
		else if(format == RECT){
			if(n.format == RECT){
				r1 = r - n.r;
				i1 = i - n.i;
			}
			else if(n.format == POLAR){
				n.toRect();
				r1 = r - n.r;
				i1 = i - n.i;
				n.toPolar();
			}
		}
		
		return Complex(r1,i1);
	}
	
	const Complex Complex::operator-(float n0){
		float r1,i1;
		Complex n(n0, 0.0);
		
		if(format == POLAR){
			this->toRect();
			r1 = r - n.r;
			i1 = i - n.i;
			this->toPolar();
		}
		else if(format == RECT){
			r1 = r - n.r;
			i1 = i - n.i;
		}
		
		return Complex(r1,i1);
	}

	const Complex Complex::operator-=(const Complex &n0){
		*this = *this - n0;
		return *this;
	}

	const Complex Complex::operator-=(float n0){
		*this = *this - n0;
		return *this;
	}

	const Complex Complex::operator*(const Complex &n0){
		float r1,i1;
		Complex n = n0;
		
		if(format == POLAR){
			if(n.format == RECT){
				n.toPolar();
				r1 = r*n.r;
				i1 = i + n.i;
				n.toRect();
			}
			else if(n.format == POLAR){
				r1 = r*n.r;
				i1 = i + n.i;
			}
		}
		else if(format == RECT){
			this->toPolar();
			if(n.format == RECT){
				n.toPolar();
				r1 = r*n.r;
				i1 = i + n.i;
				n.toRect();
			}
			else if(n.format == POLAR){
				r1 = r*n.r;
				i1 = i + n.i;
			}
			this->toRect();
		}
		
		return Complex(r1,i1,POLAR);
	}
	
	const Complex Complex::operator*(float n0){
		float r1,i1;
		Complex n(n0, 0.0);
		
		if(format == POLAR){
			n.toPolar();
			r1 = r*n.r;
			i1 = i + n.i;
			n.toRect();
		}
		else if(format == RECT){
			this->toPolar();
			n.toPolar();
			r1 = r*n.r;
			i1 = i + n.i;
			n.toRect();
			this->toRect();
		}
		
		return Complex(r1,i1,POLAR);
	}

	const Complex Complex::operator*=(const Complex &n0){
		*this = *this * n0;
		return *this;
	}

	const Complex Complex::operator*=(float n0){
		*this = *this * n0;
		return *this;
	}

	const Complex Complex::operator/(const Complex &n0){
		float r1,i1;
		Complex n = n0;
		
		if(format == POLAR){
			if(n.format == RECT){
				n.toPolar();
				r1 = r/n.r;
				i1 = i - n.i;
				n.toRect();
			}
			else if(n.format == POLAR){
				r1 = r/n.r;
				i1 = i - n.i;
			}
		}
		else if(format == RECT){
			this->toPolar();
			if(n.format == RECT){
				n.toPolar();
				r1 = r/n.r;
				i1 = i - n.i;
				n.toRect();
			}
			else if(n.format == POLAR){
				r1 = r/n.r;
				i1 = i - n.i;
			}
			this->toRect();
		}
		
		return Complex(r1,i1,POLAR);
	}

	const Complex Complex::operator/(float &n0){
		float r1,i1;
		Complex n(n0, 0.0);
		
		if(format == POLAR){
			n.toPolar();
			r1 = r/n.r;
			i1 = i - n.i;
			n.toRect();
		}
		else if(format == RECT){
			this->toPolar();
			n.toPolar();
			r1 = r/n.r;
			i1 = i - n.i;
			n.toRect();
			this->toRect();
		}
		
		return Complex(r1,i1,POLAR);
	}

	const Complex Complex::operator/=(const Complex &n0){
		*this = *this / n0;
		return *this;
	}

	const Complex Complex::operator/=(float n0){
		*this = *this / n0;
		return *this;
	}

	const Complex Complex::operator^(float n0){
		return toThePower(n0);
	}
    
	const Complex Complex::operator^(Complex n0){
		return toThePower(n0);
	}

	bool Complex::operator==(const Complex &n0) const{
		Complex n = n0;
		
		if(this == &n0)
			return true;

		if(format == POLAR){
			if(n.format == RECT){
				n.toPolar();
				return (r == n.r && i == n.i);
			}
			else if(n.format == POLAR)
				return (r == n.r && i == n.i);
		}
		else if(format == RECT){
			if(n.format == RECT)
				return (r == n.r && i == n.i);
			else if(n.format == POLAR){
				n.toRect();
				return (r == n.r && i == n.i);
			}
		}
	}

	bool Complex::operator!=(const Complex &n) const{
		return !(*this == n);
	}

	Complex Complex::toThePower(float n){
		if(format == POLAR){
			Complex num(pow(r,n),n*i,POLAR);
			return num;
		}
		else{
			this->toPolar();
			Complex num(pow(r,n),n*i,POLAR);
			this->toRect();
			return num;
		}
	}

	Complex Complex::toThePower(Complex n){	
		if(format == POLAR){
			this->toRect();
			float M = pow(i*i + r*r, 0.5*n.r)*pow(e, -n.i*atan(i/r));
			Complex num(M*cos(0.5*n.i*log(i*i + r*r) + n.r*atan(i/r)),
		                M*sin(0.5*n.i*log(i*i + r*r) + n.r*atan(i/r)));
			this->toPolar();
			return num;
		}
		else{
			float M = pow(i*i + r*r, 0.5*n.r)*pow(e, -n.i*atan(i/r));
			Complex num(M*cos(0.5*n.i*log(i*i + r*r) + n.r*atan(i/r)),
		                M*sin(0.5*n.i*log(i*i + r*r) + n.r*atan(i/r)));
			return num;
		}
	}

	void Complex::print(){
		string signal = sgn(i) == -1 ? "-" : "+";
		if(format == RECT)
			cout <<" " << r << " " << signal << " i*(" << fabs(i) <<")\n";
		else if(format == POLAR)
			cout <<" " << r << "*exp("<< signal << "i*(" << fabs(i) <<"))\n";
	}
	
	Complex::~Complex(){
	}

	int sgn(float n){
		if(n<0)
			return -1;
		if(n>=0)
			return 1;
	}
}