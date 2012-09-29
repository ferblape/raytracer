#ifndef _RGB_
#define _RGB_

class RGB{

	public :
		float r;
		float g;
		float b;

		RGB();
		RGB(float r, float g,float b);	

		RGB operator *(RGB rgb);	
		RGB operator *(float f);	
		RGB operator +(RGB rgb);	
		void set(float nr,float ng, float nb);
		void escribir();
};

#endif 
