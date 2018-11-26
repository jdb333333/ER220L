/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef	__SYSTICK_H
#define	__SYSTICK_H

/* Includes ------------------------------------------------------------------*/

#define uSECOND 60      //uSECOND = SystemCoreClock / 2000000;

/* Exported functions ------------------------------------------------------- */
#define PRNPAUSEMAX  30000           //��ӡ������ʱ,��ͣ30��
extern  volatile unsigned long msTimer_Delay0,msTimer_Delay1,msTimer_Delay2;
extern  volatile unsigned long RTCTimer;
extern unsigned short Prn_Delay;          //��ӡ����ͣʱ��

#define GetSystemTimer()  RTCTimer
extern void SetTimerDelay(int timerID,unsigned long msDelay);
extern unsigned long GetTimerDelay(int timerID);

#define SetTimerDelay0(msDelay)   msTimer_Delay0=msDelay
#define SetTimerDelay1(msDelay)   msTimer_Delay1=msDelay
#define SetTimerDelay2(msDelay)   msTimer_Delay2=msDelay

#define GetTimerDelay0()   msTimer_Delay0
#define GetTimerDelay1()   msTimer_Delay1   //Delay For checkError
#define GetTimerDelay2()   msTimer_Delay2

#endif /* __SYSTICK_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
