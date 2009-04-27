#ifndef _DBITEMS_H_
#define _DBITEMS_H_
#include "MuObiects/MuItemInstance.h"
#include "DB/BDBase.h"
class DBMuInwentory
{
	BDBase * BD;
	int charID;
	public:
	
//	MuItemInstance * getItemFromSlot(int x)
//	{
//		 
//       string lan;
//       lan="select * from inwentory where u_login='"+login+"'";
//       mysql_query(BD->GetDB(), lan.c_str());
//       MYSQL_RES *wynik = mysql_use_result(BD->GetDB());
//       if (wynik!=NULL)
//       		{
//		       MYSQL_ROW wiersz = mysql_fetch_row(wynik);
//		       tmp->id=atoi(wiersz[0]);
//		       tmp->user=wiersz[1];
//		       tmp->pass=wiersz[2];
//		       tmp->HCHar=atoi(wiersz[4]);
//		       tmp->HCHar;
//		       //cout << "w bd Chara=" << tmp->HCHar <<"\n";
//		       switch (atoi(wiersz[3]))
//      			{
//           		    case 0:tmp->flag=OK;     break;
//	                case 1:tmp->flag=Loged;  break;
//                    case 2:tmp->flag=Blocked;break;
//		        }
//		       mysql_free_result(wynik);//zwalniamy wynik bo nikt po nas nie posprzata :(
//       		}else cout <<"Blad: Nie istnieje taki user w bazie!!!\n";
//       
//}
//		return NULL;
//	};
//	
};


#endif
