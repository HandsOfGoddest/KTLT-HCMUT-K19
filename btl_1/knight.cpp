#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fstream>
#include <math.h>

using namespace std;

const int ENDGAME = 0;
const int MADBEAR = 1;
const int BANDIT = 2;
const int LORDLUPIN = 3;
const int ELF = 4;
const int TROLL = 5;
const int SHAMAN = 6;
const int VAJISH = 7;
const int EXCALIBUR = 8;
const int MYTHRIL = 9;
const int EXCALIPOOR = 10;
const int MUSHMARIO = 11;
const int MUSHFIB = 12;
const int MUSHGHOST = 13;
const int MUSHKNIGHT = 14;
const int REMEDY = 15;
const int MAIDENKISS = 16;
const int PHOENIXDOWN = 17;
const int MERLIN = 18;
const int ABYSS = 19;
const int GUINEVERE = 20;
const int LIGHTWING = 21;
const int ODIN = 22;
const int DRAGONSWORD = 23;
const int BOWSER = 99;
const int EVENT_SIZE = 100;
const int MAX_CHARACTER_EACH_LINE = 250;

struct knight
{
   int HP;
   int level;
   int remedy;
   int maidenkiss;
   int phoenixdown;
};

// read data from input file to corresponding variables
// return 1 if successfully done, otherwise return 0
int readFile(const char* filename, knight& theKnight, int& nEvent, int* arrEvent)
{
	const char* file_name = filename;
	FILE* f = 0;
	char* str = new char[MAX_CHARACTER_EACH_LINE];
	int num;

	f = fopen(file_name, "r");
	if (f == NULL)	//file not found || cannot read
		return 0;

	fgets(str, MAX_CHARACTER_EACH_LINE, f);
	if (feof(f))
		return 0;

	int start = 0;
	int len = strlen(str);
	// read HP
	while (start < len && str[start] == ' ')
		start ++;
	num = 0;
	while (start < len && str[start] <= '9' && str[start] >= '0'){
		num = num * 10 + str[start] - '0';
		start++;
	}
	theKnight.HP = num;
	if (theKnight.HP < 1 || theKnight.HP > 999)
		return 0;

	// read level
	while (start < len && (str[start] > '9' || str[start] < '0'))
		start ++;
	num = 0;
	while (start < len && str[start] <= '9' && str[start] >= '0'){
		num = num * 10 + str[start] - '0';
		start++;
	}
	theKnight.level = num;
	if (theKnight.level < 1 || theKnight.level > 10)
		return 0;

	// read remedy
	while (start < len && (str[start] > '9' || str[start] < '0'))
		start ++;
	num = 0;
	while (start < len && str[start] <= '9' && str[start] >= '0'){
		num = num * 10 + str[start] - '0';
		start++;
	}
	theKnight.remedy = num;
	if (theKnight.remedy < 0 || theKnight.remedy > 99)
		return 0;

	// read maidenkiss
	while (start < len && (str[start] > '9' || str[start] < '0'))
		start ++;
	num = 0;
	while (start < len && str[start] <= '9' && str[start] >= '0'){
		num = num * 10 + str[start] - '0';
		start++;
	}
	theKnight.maidenkiss = num;
	if (theKnight.maidenkiss < 0 || theKnight.maidenkiss > 99)
		return 0;

	// read phoenixdown
	while (start < len && (str[start] > '9' || str[start] < '0'))
		start ++;
	num = 0;
	while (start < len && str[start] <= '9' && str[start] >= '0'){
		num = num * 10 + str[start] - '0';
		start++;
	}
	theKnight.phoenixdown = num;
	if (theKnight.phoenixdown < 0 || theKnight.phoenixdown > 99)
		return 0;

	// read events
	nEvent = 0;
	while (1){
		if (feof(f))
			break;
		fgets(str, MAX_CHARACTER_EACH_LINE, f);
		if (str == NULL)
			break;
		start = 0;
		len = strlen(str);
    // cout << "\'" << str << "\'" << "\t" << len << endl;
		while (start < len){
			while (start < len && (str[start] > '9' || str[start] < '0'))
				start++;
			if (start >= len)
				break;
			arrEvent[nEvent] = 0;
			while (start < len && str[start] <= '9' && str[start] >= '0'){
				arrEvent[nEvent] = arrEvent[nEvent] * 10 + str[start] - '0';
				start++;
			}
			nEvent++;
		}
    delete[] str;
	}
	fclose(f);
	return 1;
}

void display(int* nOut)
{
  if (nOut)
    cout << *nOut;
  else
    cout << "Error!";
}

int level_check(int level)
{
	if(level>10)	return(10);
	else return (level);
}
int HP_check(int HP, int maxHP)
{
	if(HP>maxHP)	return(maxHP);
	else return(HP);
}
bool Knight_status(int HP, bool &confirm_1, bool &confirm_2, bool &confirm_3)
{
	if(HP==999)	confirm_1=1;//xac dinh arthur
	else if(HP==888)//xac dinh lancelot
		 {
		 	confirm_2=1;	
		 }
		 else
		 {
		 	//xac dinh paladin
		 	confirm_3=1;
		 	if(HP!=1)
		 	{
		 		for(int i=2; i<=sqrt(HP); i++)
				{
					if(HP%i==0)
					{
						confirm_3=0;
						break;	
					}	
				}	
			}else confirm_3=0; 	
		 }
	if(confirm_1==0 && confirm_2==0 && confirm_3==0)	return 0;
	else return 1;
}
void check_dragonKnight(int HP,bool &confirm)
{
	for(int i=5; i<=HP; i++)
	{
		for(int j=4; j<=i; j++)
		{
			for(int z=3; z<=j; z++)
			{
				if((z*z+j*j==i*i) && (z+j+i==HP))
				{
					confirm=1;
					break;
				}	
			}
		}
	}
}
void lancelot_status(int level, bool &confirm_1)
{
	if(level%2!=0)
		confirm_1=1;
	else
		confirm_1=0;	
}
int Fibonacci_Number(int N)
{
	if(N==2 || N==1)	return (1);
	return(Fibonacci_Number(N-1)+Fibonacci_Number(N-2));
}
void Find_Fibonacci(int &HP, int N)
{
	if(HP>=Fibonacci_Number(N))		Find_Fibonacci(HP,N+1);
	else HP=Fibonacci_Number(N);
}
void check_eflect(int &turns_eflect, bool &Shaman_eflect, bool &Vajish_eflect, int &HP, int &level, int pre_level)
{
	if(turns_eflect>=0)
	{
		if(turns_eflect==0)
		{
			if(Shaman_eflect==1)
			{
				HP=HP * 5;
				Shaman_eflect=0;
			}				
			else if(Vajish_eflect==1)
			{
				level=pre_level;
				Vajish_eflect=0;
			}
			turns_eflect=-1;
		}else turns_eflect--;
	}
}
void check_support_turn(int &support_turns, int &ODIN)
{
	if(support_turns>=0)
	{
		if(support_turns==0)
		{
			support_turns=-1;
			ODIN=-1;
		}	
		else support_turns--;
	}
}
void minion_level(int i, int &levelO, int &b)
{
	b=(i+1)%10;
	levelO = (i+1)>6? (b> 5? b : 5) : b;
}
void check_survie(int &HP,int maxHP,int &level,int pre_level, int &phoenix, int &out, bool &vajish, int &turns_eflect)
{
	if(HP<=0)
	{
		if(phoenix==0)	out=-1;
		else 
		{
			HP=maxHP;
			phoenix--;
			if(vajish==1)
			{
				level=pre_level;
				vajish=0;
				turns_eflect=-1;
			}
		}
	}
}


int main(int argc, char** argv)
{
    if (argc < 2) return 1;
    const char* filename = argv[1];;

   struct knight theKnight;
   int nEvent; //number of events
   int* arrEvent = new int[EVENT_SIZE]; // array of events
   int* nOut;                           // final result
   int i;

	readFile(filename, theKnight, nEvent, arrEvent);
	//cout << theKnight.HP << ' ' << theKnight.level << ' ' << theKnight.remedy << ' ' << theKnight.maidenkiss << ' ' << theKnight.phoenixdown << endl;
   int k(0);//bien dem level cho quai khi gap sk20
   int maxHP=theKnight.HP;
   int levelO(0);
   float baseDamage(0);
   int b(0);
   int Out(0);
   nOut=&Out;
   int turns_eflect(-1),
	   support_turns(-1);
   int level_before_eflect(0);
   bool confirm_arthur(0),
   		confirm_lancelot(0),
   		confirm_paladin(0),
		confirm_dragonKnight(0);
   bool SHAMAN_eflect(0), VAJISH_eflect(0);
   int ODIN_support(0);
   bool confirm_excalibur(0),
   		confirm_mythril(0),
		confirm_excalipoor(0),
		confirm_guinevere_escape(0),
		confirm_lightwing_jumb(0),
		confirm_dragonsword(0);
   	int N_fibonacci(3);
   	Knight_status(theKnight.HP, confirm_arthur, confirm_lancelot, confirm_paladin); //ktra status cua Knight
    if (Knight_status(theKnight.HP, confirm_arthur, confirm_lancelot, confirm_paladin)==0)	check_dragonKnight(theKnight.HP,confirm_dragonKnight);
	for (i = 0; i < nEvent; i++)
	{
		if(confirm_lancelot==1)
		{
			lancelot_status(theKnight.level, confirm_arthur);
		}
		int theEvent = arrEvent[i];
		if(confirm_guinevere_escape==0)	minion_level(i, levelO, b);
		else							minion_level(k, levelO, b);
		//cout << theEvent << endl;
		switch (theEvent)
		{
		case MADBEAR:
			baseDamage=1;
		break;
			
		case BANDIT:
			baseDamage=1.5;
		break;
		
		case LORDLUPIN:
			baseDamage = 4.5;
		break;
		
		case ELF:
			baseDamage = 6.5;
		break;
		
		case TROLL:
			baseDamage = 8.5;
		break;
		
		case SHAMAN:
			if(turns_eflect==-1)
			{
				if (ODIN_support==1 || confirm_arthur==1 || confirm_paladin==1 || confirm_dragonsword==1)	theKnight.level+=2;
				else
				{
					if (theKnight.level>levelO && confirm_excalipoor==0)		theKnight.level+=2;
					else if(theKnight.level!=levelO)
					{
						if (theKnight.HP<5)	theKnight.HP=1;
						else
						{
							if(confirm_mythril==0)	theKnight.HP/=5;	
						}
						if(theKnight.remedy>=1)
						{
							theKnight.remedy-=1;	
							theKnight.HP*=5;
						}	
						else
						{
							turns_eflect=3;
							SHAMAN_eflect=1;
						}
					}	
				}			
			}
		break;
		
		case VAJISH:
			if(turns_eflect==-1)
			{
				if(ODIN_support==1 || confirm_arthur==1 || confirm_paladin==1 || confirm_dragonsword==1)		theKnight.level+=2;
				else
				{
					if (theKnight.level>levelO && confirm_excalipoor==0)		theKnight.level+=2;
					else if(theKnight.level<levelO || confirm_excalipoor==1)
						 {
						 	if(theKnight.maidenkiss>=1)	theKnight.maidenkiss--;
							else
							{
								level_before_eflect=theKnight.level;
								theKnight.level=1;
								turns_eflect=3;
								VAJISH_eflect=1;
							}		
						 }	
				}		
			}
		break;
						
		case EXCALIBUR:
			confirm_excalibur=1;
			confirm_excalipoor=0;
		break;
			
		case MYTHRIL:
			confirm_mythril=1;
		break;
			
		case EXCALIPOOR:
			if(theKnight.level<5 && confirm_arthur==0 && confirm_paladin==0 && confirm_dragonKnight==0 && support_turns==-1)
			{
				confirm_excalipoor=1;
				confirm_excalibur=0;
			}	
		break;
			
		case MUSHMARIO:
			theKnight.HP+=50;
		break;
		
		case MUSHFIB:
			Find_Fibonacci(theKnight.HP, N_fibonacci);
		break;
			
		case MUSHGHOST:
			if(confirm_paladin==0 && confirm_dragonsword==0 && confirm_mythril==0 && support_turns==-1)
			{
				if(theKnight.HP>=51)	theKnight.HP-=50;	
				else theKnight.HP=1;
			}
		break;
			
		case MUSHKNIGHT:
			maxHP+=50;
			if(maxHP>999)	maxHP=999;
			theKnight.HP=maxHP;
		break;
			
		case REMEDY:
			if(SHAMAN_eflect==1)
			{
				turns_eflect=-1;
				SHAMAN_eflect=0;
				theKnight.HP*=5;
			}
			else
			{
				theKnight.remedy+=1;
				if(theKnight.remedy>99)	theKnight.remedy=99;
			}
		break;
		
		case MAIDENKISS:			
			if(VAJISH_eflect==1)
			{
				turns_eflect=-1;
				VAJISH_eflect=0;
				theKnight.level=level_before_eflect;
			}
			else
			{
				theKnight.maidenkiss +=1;
				if(theKnight.maidenkiss>99)	theKnight.maidenkiss=99;	
			}
				
		break;
			
		case PHOENIXDOWN:
			theKnight.phoenixdown +=1;
			if(theKnight.phoenixdown>99)	theKnight.phoenixdown=99;
		break;
			
		case MERLIN:
			if(turns_eflect>=0)	
			{
				if(SHAMAN_eflect==1)	
				{
					turns_eflect=-1;
					SHAMAN_eflect=0;
				}
				else if(VAJISH_eflect==1)
				{
					turns_eflect=-1;
					VAJISH_eflect=0;
					theKnight.level=level_before_eflect;
				}
			}
			theKnight.level+=1;
			theKnight.HP=maxHP;
		break;
			
		case ABYSS:
			if(theKnight.level<7 && confirm_dragonsword==0 && support_turns==-1)
			{
				Out=-1;
				display(nOut);
				exit(0);
			}
		break;
			
		case GUINEVERE:
			confirm_guinevere_escape=1;
			k=i;
		break;
			
		case LIGHTWING:
			if(confirm_guinevere_escape==0)
			{
				if((nEvent-i-1)<4)
				{
					Out=theKnight.HP + theKnight.level +theKnight.maidenkiss + theKnight.phoenixdown + theKnight.remedy;
					display(nOut);
					exit(0);
				}
				else
				{
					for(int j=i+1; j<i+4; j++)
					{
						if(arrEvent[j]==0 || arrEvent[j]==20)
						{
							Out=theKnight.HP + theKnight.level +theKnight.maidenkiss + theKnight.phoenixdown + theKnight.remedy;
							display(nOut);
							exit(0);		
						}
						else if(j==(i+3))	confirm_lightwing_jumb=1;
					}
				}
				if(confirm_lightwing_jumb==1)
				{
					i+=3;
					if(support_turns>=0)
					{
						ODIN_support=-1;
						support_turns=-1;	
					}	
					check_eflect(turns_eflect, SHAMAN_eflect, VAJISH_eflect, theKnight.HP, theKnight.level, level_before_eflect);
					continue;
				}		
			}
			else if(confirm_guinevere_escape==1)
			{
				check_eflect(turns_eflect, SHAMAN_eflect, VAJISH_eflect, theKnight.HP, theKnight.level, level_before_eflect);
				Out=theKnight.HP + theKnight.level +theKnight.maidenkiss + theKnight.phoenixdown + theKnight.remedy;
				display(nOut);
				exit(0);
			}
		break;

		case ODIN:
			if(ODIN_support==0)
			{
				ODIN_support=1;
				support_turns=3;	
			}	
		break;	
			
		case DRAGONSWORD:
			if(confirm_dragonKnight==1)
			{
				confirm_dragonsword=1;
			}
		break;
			
		case BOWSER:
			if(ODIN_support==1)
			{
				theKnight.level=10;
				break;	
			}	
			if(confirm_arthur==1 || confirm_lancelot==1)	theKnight.level=10;
			else if(confirm_paladin==1)
			{
				if(theKnight.level<8)
				{
					Out=-1;
					display(nOut);
					exit(0);
				}	
				else theKnight.level=10;
			}
			else if (confirm_dragonsword==1)	theKnight.level=10;
				 else if(theKnight.level<10 || confirm_excalipoor==1)
				 	  {
				 			Out=-1;
							display(nOut);
							exit(0); 	
					  }
				 	  else theKnight.level=10;	
		break;
			
		}
		if(theEvent>=1 && theEvent<=5)
		{
			if(confirm_excalibur==1 || ODIN_support==1 || confirm_arthur==1 || confirm_paladin==1 || confirm_dragonsword==1)		theKnight.level+=1;
			else if(confirm_excalipoor==1 && confirm_mythril==0)	theKnight.HP=theKnight.HP-baseDamage*levelO*10;
				 else
				 {
					if (theKnight.level>levelO && confirm_excalipoor==0)	theKnight.level++;
					else if(theKnight.level<levelO && confirm_mythril==0)
					{
						theKnight.HP=theKnight.HP-baseDamage*levelO*10;
					}	
				 }
		}
		check_survie(theKnight.HP, maxHP,theKnight.level, level_before_eflect, theKnight.phoenixdown, Out, VAJISH_eflect, turns_eflect);//xu ly tinh huong khi HP<=0
		if(Out==-1)	break;
		check_eflect(turns_eflect, SHAMAN_eflect, VAJISH_eflect, theKnight.HP, theKnight.level, level_before_eflect);//xu ly luot bi nhiem hieu ung
		theKnight.level=level_check(theKnight.level);//ktra dk cua level
		theKnight.HP=HP_check(theKnight.HP, maxHP);// ktra dk cua HP
		if(ODIN_support==1)
		{
			check_support_turn(support_turns, ODIN_support);	
		}//xu ly luot ho tro cua ODIN
		Out=theKnight.HP + theKnight.level +theKnight.maidenkiss + theKnight.phoenixdown + theKnight.remedy;
		//bat dau qua trinh di lui 1 su kien khi confirm_guinevre_escape=1
		if(confirm_guinevere_escape==1)
		{
			if(i==0)	break;//ket thuc khi het su kien ban dau
			else
			{
				i-=2;
				k++;// tang level cho quai
			}
		}//ket thuc	
		if(theEvent==0)	break;//tinh huong khi BOWSER dau hang
	}
    display(nOut);
    return 0;
}
