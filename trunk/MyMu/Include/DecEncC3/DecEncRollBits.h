#ifndef DECENCROLBITS_H_
#define DECENCROLBITS_H_

void ShiftBuffer(unsigned char*Buff,int Len,int ShiftLen)
{
	if(ShiftLen)
	{
		if(ShiftLen>0)
		{
			if(Len-1>0)
				for (int i=Len-1;i>0;i--)
					Buff[i]=(Buff[i-1]<<(8-ShiftLen))|(Buff[i]>>(ShiftLen));
			Buff[0] = Buff[0]>>ShiftLen;
            return;
		}
		ShiftLen=-ShiftLen;
		if(Len-1>0)
			for(int i=0;i<Len-1;i++)
				Buff[i] =(Buff[i+1]>>(8-ShiftLen))|(Buff[i]<<ShiftLen);
		Buff[Len-1] = Buff[Len-1]<<ShiftLen;
	}
}

#endif /*DECENCROLBITS_H_*/
