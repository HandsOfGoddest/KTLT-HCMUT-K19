/*****Version 1.1***********/
#include <stdio.h>
#include <iostream.h>
#include <fstream.h>
#include <math.h>

//read data from input file to corresponding variables
//return 1 if successfully done, otherwise return 0
int readFile(int& baseHP1,int& baseHP2,int& wp1,int& wp2,int& ground)
{
	char* file_name = "input.txt";
	ifstream in;
	in.open(file_name);
	in >> baseHP1;
	in >> wp1;
	in >> baseHP2;
	in >> wp2;
	in >> ground;
	in.close();
	if (baseHP1 < 99 || baseHP1 > 999)
		return 0;
	if (wp1 < 0 || wp1 > 3)
		return 0;
	if (baseHP2 < 1 || baseHP2 > 888)
		return 0;
	if (wp2 < 0 || wp2 > 3)
		return 0;
	if (ground < 1 || ground > 999)
		return 0;
	in.close();
	return 1;

}
void display(float fOut)
//display value of fOut in format of 0.XX
// no exception handled
{
	if (fOut == 1){
		cout << fOut;
	}
	else{
		char s[10];
		sprintf(s,"%.2f",fOut);
		cout << s;
	}
}


int main(void)
{
	int baseHP1,baseHP2,wp1,wp2,ground;
	float fOut = 0.0;
	readFile(baseHP1,baseHP2,wp1,wp2,ground);
	//write your code here
	float realHP1(0), realHP2(0);
	if(baseHP1==999)	fOut=1;
	else if(baseHP2==888 && baseHP1!=999)	fOut=0;
		  else
		  {
				int flag_1(0), flag_2(0);
				for(int i=2; i<sqrt(baseHP1); i++)
				{
					if(baseHP1%i==0)	flag_1++;	
				}	  
				if(baseHP2!=1)
				{
					for(int j=2; j<sqrt(baseHP2); j++)
					{	
						if(baseHP2%j==0)	flag_2++;	
					}		
				}	else flag_2=1;
				if(flag_1==0 && flag_2==0)
				{
					if(baseHP1>baseHP2)	fOut=0.99;
					else if(baseHP1<baseHP2)	fOut=0.01;
						 else fOut=0.5;
				}	
				else if (flag_1!=0 && flag_2==0)	fOut=0.01;
					 else if (flag_1==0 && flag_2!=0)	fOut=0.99;
					 	  else 
						   {	
						   		realHP1=baseHP1;
								realHP2=baseHP2;
								if(wp1==0)
								{
									realHP1=baseHP1/10;
									cout<<realHP1;
								}
								if (baseHP1==ground)	realHP1=realHP1*1.1;
								if(wp1==3 && wp2!=2)
								{
									realHP1*=2;
									cout<<realHP1<<endl;
								}
								if(wp2==0)
								{
									realHP2=baseHP2/10;
								}
								if(baseHP2==ground)		realHP2=realHP2*1.1;
								if(realHP1>999)		realHP1=999;
								if(realHP2>999)		realHP2=999;
								if((wp1==2 && realHP1<realHP2) || (wp2==2 && realHP2<realHP1))	fOut=0.5;
								else 	fOut=(realHP1-realHP2+999)/2000;
								cout<<realHP1<<":"<<realHP2<<endl;		 	  			
						   }
		  } 
	display(fOut);
	return 0;
}