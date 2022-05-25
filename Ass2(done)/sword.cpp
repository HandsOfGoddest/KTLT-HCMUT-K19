#ifndef _definition_h_
#include "defs.h"
#define _definition_h_
#endif

enum event_index{MADBEAR=1, MOONBRINGER, ELF, SAXON, TROLL,TORNBERY, QUEEN, NINA, VSR, ANTIDOTE, OdiN, MERLIN, OW, HADES, SH, LD,
				 P_SHIELD=95, L_SPEAR, G_HAIR, EXCALIBUR, ULTIMECIA};

void Calling_Phoenix(knight &theKnight,int MaxHP, bool &TORN_poison){
	callPhoenix(theKnight, MaxHP);
	if(TORN_poison==1)	TORN_poison=0;
}

void increase_level_MaxHP(int &level, int &MaxHP){
	if(level<10)	MaxHP=(MaxHP<=899)?(MaxHP+100):999;
	level=(level<10)?(level+1):10;
}

bool check_Arthur(int &HP, bool &Arthur){
	if(HP==999)
	{
		Arthur=1;
		return 1;
	}return 0;
}

bool check_Lancelot(int &HP, bool &Lancelot){
	if(HP==888)
	{
		Lancelot=1;
		return 1;
	}return 0;
}

bool check_Guinerve(int &HP, bool &Guinerve){
	if(HP==777)
	{
		Guinerve=1;
		return 1;
	}return 0;
}

bool check_Paladin(int &HP, bool &Paladin){
	if(HP!=1)
	{
		Paladin=1;
		for(int i=2; i<HP; i++)
		{
			if(HP%i==0)
			{
				Paladin=0;
				return 0;
			}
		}return 1;
	}return 0;
}

bool check_DragonKnight(int &HP, bool &Dragon_Knight){
	for(int i=1; i<=HP; i++)
	{
		for(int j=i;j<=(HP-i); j++)
		{
			if((i*i + j*j == (HP-i-j)*(HP-i-j)))
			{
				Dragon_Knight=1;
				return 1;
			}
		}
	} return 0;
}

void check_Knight_status(knight &theKnight, bool &Arthur, bool &Lancelot, bool &Guinerve, bool &Paladin, bool &Dragon_Knight)
{
	bool flag=check_Arthur(theKnight.HP, Arthur);
	if(flag!=1)
	{
		flag=check_Lancelot(theKnight.HP, Lancelot);
		if(flag!=1)
		{
			flag=check_Guinerve(theKnight.HP, Guinerve);
			if(flag!=1){
				flag=check_Paladin(theKnight.HP, Paladin);
				if(flag!=1)	check_DragonKnight(theKnight.HP, Dragon_Knight);
			}			
		}
	}	
}

int level0(int i){
	int b=(i+1)%10;
	return (i+1)>6?(b>5?b:5):b;
}

void check_gil(int &gil){
	if(gil>999)	gil=999;
}

void monster_1_to_5(knight &theKnight,int MaxHP, float baseDamage, int levelO, bool &TORN_poison, int ODIN, bool Arthur, bool Lancelot, bool Guinerve, bool Paladin, bool mythril,bool LH, int &nWin,int &nLose, castle arrCastle[], int i, int j){
	int damage=levelO*baseDamage*10;
	if(Arthur==1 || Lancelot==1 || Paladin==1 || LH==1 || ODIN==1){
		theKnight.gil+=baseDamage*100;
		check_gil(theKnight.gil);
		nWin+=1;
	}	
	else{
		if(theKnight.level >=levelO){
			theKnight.gil+=baseDamage*100;
			check_gil(theKnight.gil);
			nWin+=1;
		}	
		else{
			if(Guinerve!=1 || arrCastle[i].arrEvent[j]!=2){
				if(mythril!=1)	theKnight.HP-=damage;
			}	
			nLose+=1;
		}
	}
	if(TORN_poison==1)	theKnight.HP-=damage;
	if(theKnight.HP<=0)	Calling_Phoenix(theKnight, MaxHP, TORN_poison);
}//function for events from 1 to 5
//functions for TORN event
void vs_TORN(knight &theKnight,int &MaxHP,int levelO, int ODIN, bool Arthur, bool Lancelot, bool Paladin, bool DragonKnight, bool LH, bool &TORN_poison, int &poison_turns, int &nWin, int &nLose){
	if(TORN_poison==0){
		if(Arthur==1 || Lancelot==1 || LH==1 || ODIN==1){
			increase_level_MaxHP(theKnight.level, MaxHP);
			nWin+=1;
		}	
		else{
			if(theKnight.level>=levelO){
				increase_level_MaxHP(theKnight.level, MaxHP);
				nWin+=1;
			}	
			else{
				if(Paladin!=1 && DragonKnight!=1){
					if(theKnight.antidote>=1)	theKnight.antidote-=1;
					else{
						TORN_poison=1;
						poison_turns=5;	
					}	
				} 
				nLose+=1;
			}
		}
	}
}

void erase_poison(bool &TORN_poison, int &poison_turns){
	TORN_poison=0;
	poison_turns=-1;
}
//end
void vs_Queen(knight &theKnight,int levelO, int ODIN, bool Arthur, bool Lancelot, bool Guinerve, bool LH, bool Hakama, int &nWin, int &nLose){
	if(Arthur==1 || Lancelot==1 || LH==1 || ODIN==1){
		theKnight.gil=(theKnight.gil<=499)?(theKnight.gil*2):999;
		nWin+=1;
	}
	else{
		if(theKnight.level>=levelO){
			theKnight.gil=(theKnight.gil<=499)?(theKnight.gil*2):999;
			nWin+=1;
		}
		else{
			if(Hakama!=1)	theKnight.gil/=2;
			nLose+=1;
		}
	}
}//function for Queen event
//functions for Nina event
float sum(int A)
{
	int sum(0);
	for(int i=1; i<=A; i++)
	{
		if(A%i==0)	sum+=i;
	}
	return (sum);
}

bool Fr_Num(int HP, int gil)
{
	if(HP >0 && gil >0){
		float av_HP=sum(HP)/HP;
		float av_gil=sum(gil)/gil;
		if (av_HP==av_gil)	return 1;	
	}
	return 0;
}

void convert_gil_HP(int &gil, int &HP, int MaxHP)
{
	while(1)
	{
		if(HP==MaxHP || gil==0)	break;
		else{
			HP+=1;
			gil-=1;
		}
	}
}

void trade_NiNa(knight &theKnight, bool Paladin, bool Guinerve, bool &LH, int &borrow_turns,bool Hakama, bool &TORN_poison, int &poison_turns, int MaxHP ){
	bool Fr_Number=Fr_Num(theKnight.HP, theKnight.gil);
	if(Guinerve==1 || Paladin==1 || Hakama==1){
		if(Fr_Number==1){
			LH=1;
			borrow_turns=5;
		}	
		if(Guinerve==1)	theKnight.gil=(theKnight.gil<=949)?(theKnight.gil+50):999;
		if(Paladin==1)	borrow_turns=-2;
		if(TORN_poison==1)	erase_poison(TORN_poison, poison_turns);
		theKnight.HP=MaxHP;
	}
	else{
		if(Fr_Number==1){
			theKnight.HP=MaxHP;
			LH=1;
			borrow_turns=5;
			if(TORN_poison==1)	erase_poison(TORN_poison, poison_turns);
		}
		else{
			if(theKnight.gil>=50){
				if(TORN_poison==1){
					erase_poison(TORN_poison, poison_turns);
					theKnight.gil-=50;
				}
				if(theKnight.gil>=1 && theKnight.HP<MaxHP)	convert_gil_HP(theKnight.gil,theKnight.HP, MaxHP);
			}
		}
	}
}
//end

void Vsr(int &HP, int MaxHP, bool &TORN_poison, int poison_turns, int &nPetal, bool &Hakama){
	HP=MaxHP;
	if(TORN_poison==1)	erase_poison(TORN_poison, poison_turns);
	if(Hakama==1)	nPetal=99;
	else nPetal=(nPetal<=94)?(nPetal+5):99;
}//function for Vuon Sau Rieng event

void Antidote(int &Antidote, bool &TORN_poison, int &poison_turns)
{
	if(TORN_poison==1 && poison_turns!=0){
		erase_poison(TORN_poison, poison_turns);
	}
	else Antidote=(Antidote<99)?(Antidote+1):99;
}//function for Antidote event

void Odin(int &ODIN, int &ODIN_turns){
	if(ODIN==0){
		ODIN=1;
		ODIN_turns=5;	
	}
}//function for ODIN event

void Merlin(int &HP, int &MaxHP, int &level, bool &TORN_poison, int &poison_turns){
	if(TORN_poison==1)	erase_poison(TORN_poison, poison_turns);
	increase_level_MaxHP(level, MaxHP);
	HP=MaxHP;
}//function for Merlin event

void Ow(knight &theKnight, bool Ex, bool DragonKnight, bool LH, bool mythril, int &MaxHP, bool &Omega,bool &TORN_poison, int &nWin, int &nLose){
	if(Omega==0){
		if((theKnight.level==10 && Ex==1) || (DragonKnight==1 && LH==1)){
			while(1){
				increase_level_MaxHP(theKnight.level, MaxHP);
				if(theKnight.level==10)	break;
			}
			Omega=1;
			nWin+=1;
		}
		else{
			if(mythril!=1)	Calling_Phoenix(theKnight, MaxHP, TORN_poison);
			nLose+=1;
		}
	}
}//functon for Omega Weapon event
//functions for Hades event
bool EL(bool has_Ex,bool has_hair, bool has_spear, bool Arthur, bool Guinerve, bool Lancelot ){
	if(has_hair==1){
		if(has_spear==1 && has_Ex==0)	return 1;
		else{
			if(Arthur==1 || Lancelot==1)	return 1;
			else return 0;
		}
	}
	if(has_spear==1 && Guinerve==1)	return 1;
	return 0;
}

void Hades(knight &theKnight, int levelO, bool &mythril, int MaxHP, int &ODIN, bool has_hair, bool has_spear, bool has_Ex,bool has_LH, bool DragonKnight, bool EL,bool &TORN_poison, int &nWin, int &nLose){
	if(ODIN==1 && DragonKnight!=1)	ODIN=-1;
	if(theKnight.level>=levelO || EL==1 || has_LH==1){
		mythril=1;
		nWin+=1;
	}
	else{
		if(mythril==0)	Calling_Phoenix(theKnight,MaxHP, TORN_poison);
		nLose+=1;
	}
}
//end
//functions for locked door event
void transfer_castle(int &i, int &j, int &level, int &MaxHP, int nCastle, castle arrCastle[]){
	increase_level_MaxHP(level, MaxHP);
	i=(i==(nCastle-1))?-1:i;
	j=arrCastle[i].nEvent;
}

void Locked_door(int &i, int &j, int &level, int &MaxHP, int nCastle, castle arrCastle[], bool Lancelot, bool DragonKnight){
	if(level<=(j+1)%10 && Lancelot!=1 && DragonKnight!=1)	transfer_castle(i, j, level, MaxHP, nCastle, arrCastle);
}
//end
void Ulti(knight &theKnight, bool Guinerve, bool has_Ex, bool has_LH, bool has_mythril,bool TORN_poison, int &bFlag, int &nWin, int &nLose){
	if(has_Ex==1 || has_LH==1){
		nWin+=1;
		bFlag=1;
	}	
	else{
		if(Guinerve!=1){
			if(has_mythril!=1){
				if(theKnight.HP<3)	theKnight.HP=1;
				else theKnight.HP/=3;	
			}
				
		}
		nLose+=1;
	}
	if(TORN_poison==1){
		if(theKnight.HP<3)	theKnight.HP=1;
		else theKnight.HP/=3;
	}
}//function for Ultimecia event
//functions for decrease buff and debuff
void decrease_turns_1(bool &status, int &status_turns){
	if(status_turns>=0){
		if(status_turns==0){
			status=0;
		}
		status_turns-=1;
	}
}

void decrease_turns_2(int &status, int &status_turns){
	if(status_turns>=0){
		if(status_turns==0){
			status=0;
		}
		status_turns-=1;
	}
}

void decrease_buff_debuff(bool &TORN_poison, int &poison_turns, int &ODIN, int &ODIN_turns, bool &LH, int &borrow_turns){
	if(TORN_poison==1)	decrease_turns_1(TORN_poison, poison_turns);
	if(ODIN==1)	decrease_turns_2(ODIN, ODIN_turns);
	if(borrow_turns>=0)	decrease_turns_1(LH, borrow_turns);
}
//end
//functions for mode 1
void Set_min_hash(int *&arr, int &min){
	for(int i=0; i<3; i++){
		arr[i]=hash(95+i);
	}
	min=arr[0];
	for(int i=1; i<3; i++){
		if(min>arr[i])	min=arr[i];
	}
	for(int i=0; i<3; i++){
		for(int j=i; j<3; j++){
			int temp(0);
			if(arr[i]>arr[j]){
				temp=arr[i];
				arr[i]=arr[j];
				arr[j]=temp;
			}
		}
	}
}

void Set_next_min_hash(int *arr, int &min){
	static int index=1;
	min=arr[index];
	index++;
}
//end

report*  walkthrough (knight& theKnight, castle arrCastle[], int nCastle, int mode, int nPetal)
{
  report* pReturn;
  int bFlag;
  //fighting for the existence of mankind here
  bFlag=-1;
  int nWin(0), nLose(0);
  int MaxHP=theKnight.HP;
  float baseDamage(0);
  int	levelO(0);
  bool TORN_poison(0);
  int poison_turns(-1);
  int ODIN(0), ODIN_turns(-1);
  bool Omega(0);
  bool Arthur(0), Lancelot(0), Guinerve(0), Paladin(0), DragonKnight(0);
  check_Knight_status(theKnight, Arthur, Lancelot, Guinerve, Paladin, DragonKnight);
  bool get_spear=(Lancelot==1 || Arthur==1)?1:0,
	   get_shield=(Paladin==1 || Arthur==1)?1:0,
	   get_hair=(Guinerve==1 || Arthur==1)?1:0,
	   get_Ex(0),
	   get_LH(0), mythril(0), get_Hakama(0);
  int borrow_turns(-1);
  int min(0);
  int* arr=(mode==1)?(new int [3]):NULL;
  if(mode==1)
  {
  	Set_min_hash(arr, min);
  	if(hash(95)==min && get_shield==1)	Set_next_min_hash(arr,min);
  	else{
  		if(hash(96)==min && get_spear==1)	Set_next_min_hash(arr,min);
		else if(hash(97)==min && get_hair==1) Set_next_min_hash(arr,min);	
	}
  }	
  for (int i=0; i<nCastle; i++)
  {
  	if(arrCastle[i].nEvent==0){
  		increase_level_MaxHP(theKnight.level, MaxHP);
  		continue;
	}
  		
  	else for(int j=0; j<arrCastle[i].nEvent; j++)
    {
    	bool Eternal_Love=EL(get_Ex, get_hair, get_spear, Arthur, Guinerve, Lancelot);
    	levelO=level0(j);
    	switch (arrCastle[i].arrEvent[j])
    	{
    		case MADBEAR:
    			baseDamage=1;
    			monster_1_to_5(theKnight, MaxHP, baseDamage, levelO, TORN_poison, ODIN, Arthur, Lancelot, Guinerve, Paladin, mythril, get_LH, nWin, nLose, arrCastle, i, j);
    		break;
    		case MOONBRINGER:
    			baseDamage=1.5;
    			monster_1_to_5(theKnight, MaxHP, baseDamage, levelO, TORN_poison, ODIN, Arthur, Lancelot, Guinerve, Paladin, mythril, get_LH, nWin, nLose, arrCastle, i, j);
    		break;
    		case ELF:
    			baseDamage=4.5;
    			monster_1_to_5(theKnight, MaxHP, baseDamage, levelO, TORN_poison, ODIN, Arthur, Lancelot, Guinerve, Paladin, mythril, get_LH, nWin, nLose, arrCastle, i, j);
    		break;
    		case SAXON:
    			baseDamage=6.5;
    			monster_1_to_5(theKnight, MaxHP, baseDamage, levelO, TORN_poison, ODIN, Arthur, Lancelot, Guinerve, Paladin, mythril, get_LH, nWin, nLose, arrCastle, i, j);
    		break;
    		case TROLL:
    			baseDamage=8.5;
    			monster_1_to_5(theKnight, MaxHP, baseDamage, levelO, TORN_poison, ODIN, Arthur, Lancelot, Guinerve, Paladin, mythril, get_LH, nWin, nLose, arrCastle, i, j);
    		break;
    		case TORNBERY:
    			vs_TORN(theKnight, MaxHP, levelO, ODIN, Arthur, Lancelot, Paladin, DragonKnight, get_LH, TORN_poison, poison_turns, nWin, nLose);
			break;
			case QUEEN:
				vs_Queen(theKnight, levelO, ODIN, Arthur, Lancelot, Guinerve, get_LH, get_Hakama, nWin, nLose);
			break;
			case NINA:
				trade_NiNa(theKnight, Paladin, Guinerve, get_LH, borrow_turns, get_Hakama, TORN_poison, poison_turns, MaxHP);
			break;	
			case VSR:
				Vsr(theKnight.HP, MaxHP, TORN_poison, poison_turns, nPetal,get_Hakama);
			break;
			case ANTIDOTE:
				Antidote(theKnight.antidote, TORN_poison, poison_turns);
			break;
			case OdiN:	
				Odin(ODIN, ODIN_turns);
			break;
			case MERLIN:
				Merlin(theKnight.HP, MaxHP, theKnight.level, TORN_poison, poison_turns);
			break;
			case OW:
				Ow(theKnight, get_Ex, DragonKnight, get_LH, mythril, MaxHP, Omega,TORN_poison, nWin, nLose);
			break;			
			case HADES:
				Hades(theKnight, levelO, mythril, MaxHP, ODIN, get_hair, get_spear, get_Ex,get_LH, DragonKnight, Eternal_Love,TORN_poison, nWin, nLose);
			break;										
			case SH:
				get_Hakama=1;
			break; 
			case LD:
				Locked_door(i, j, theKnight.level, MaxHP, nCastle, arrCastle, Lancelot, DragonKnight);
			break;	
			case P_SHIELD:
				if(mode==1){
					if(hash(P_SHIELD)==min){
						get_shield=1;
						Set_next_min_hash(arr, min);
					}
				}else	get_shield=1;
			break;			
			case L_SPEAR:
				if(mode==1){
					if(hash(L_SPEAR)==min){
						get_spear=1;
						Set_next_min_hash(arr, min);
					}
				}else	get_spear=1;
			break;
			case G_HAIR:
				if(mode==1){
					if(hash(G_HAIR)==min){
						get_hair=1;
						Set_next_min_hash(arr, min);
					}
				}else	get_hair=1;
			break;
			case EXCALIBUR:
				get_Ex=(get_shield==1 && get_spear==1 && get_hair==1)?1:0;
			break;
			case ULTIMECIA:
				Ulti(theKnight, Guinerve, get_Ex, get_LH, mythril, TORN_poison, bFlag, nWin, nLose);
			break;																																								
		}
		decrease_buff_debuff(TORN_poison, poison_turns, ODIN, ODIN_turns, get_LH, borrow_turns);
		if(nPetal==0 && Arthur!=1)	bFlag=0;
		nPetal=(nPetal>0 || Arthur!=1)?(nPetal-1):0;
		if(bFlag==1 || bFlag==0)	break;
		if(j==(arrCastle[i].nEvent-1))	transfer_castle(i, j, theKnight.level, MaxHP, nCastle, arrCastle);
	}
	if(bFlag==1 || bFlag==0)	break;
  }
  delete []arr;
  // success or failure?	
  pReturn = (bFlag)? new report : NULL;
  if(pReturn!=NULL){
  	pReturn->nPetal=nPetal;
  	pReturn->nWin=nWin;
  	pReturn->nLose=nLose;
  	return pReturn;	
  }
}
