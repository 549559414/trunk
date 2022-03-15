#ifndef	_W5500PROCESS_H_
#define	_W5500PROCESS_H_



void W5500_Initialization(void);
void Load_Net_Parameters(void);
void W5500_Socket_Set(void);
void Process_Socket_Data(unsigned char s);
void W5500Pro_Initialization(void);
void TestW5500(void);
void TestW5500TX(unsigned char *ch,unsigned char len);
unsigned short Process_Socket_Data1(unsigned char *ch);



#endif

