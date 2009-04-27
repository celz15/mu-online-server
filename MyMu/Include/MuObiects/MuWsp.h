#ifndef MUWSP_H_
#define MUWSP_H_
class MuWsp
{
	public: 		//wszystko publiczne to tylko tolsy
	int X;
	int Y;
	MuWsp(int x,int y):X(x),Y(y){};
	~MuWsp(){};
	bool inXDest(int dx,int dy,int zak)
	{
		int squZak=zak*zak;
		int dtX=(X-dx)(X-dx);
		int dtY=(Y-dy)(Y-dy);
		dtLen=dtX+dtY;
		return (squZak<=dtLen);
	};
	
	
	
};
#endif /*MUWSP_H_*/
