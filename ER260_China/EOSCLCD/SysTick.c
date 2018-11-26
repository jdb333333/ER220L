
/* Includes ------------------------------------------------------------------*/
#include "SysTick.h"

/* Private variables ---------------------------------------------------------*/
/**************************************************************
 * �����ӳټ�����
 *
 * @author EutronSoftware (2014-12-17)
 *
 * @param timerID:��ʱ��ʱ�����(0,1,2)
 * @param msDelay:�Ժ����ĵ�λ���ӳ�ʱ��
 ***************************************************************/
void SetTimerDelay(int timerID,unsigned long msDelay)
{
    if (timerID==0)
        msTimer_Delay0 =msDelay;
    else if (timerID==1)
        msTimer_Delay1 =msDelay;
    else if (timerID==2)
        msTimer_Delay2 =msDelay;
}
/**
 * ��ȡ�ӳټ�ʱ����ֵ
 *
 * @author EutronSoftware (2014-12-17)
 *
 * @param timerID:��ʱ��ʱ�����(0,1,2)
 *
 * @return int�ӳټ�ʱ����ֵ
 */
unsigned long GetTimerDelay(int timerID)
{
    if (timerID==0)
        return msTimer_Delay0;
    else if (timerID==1)
        return msTimer_Delay1;
    else if (timerID==2)
        return msTimer_Delay2;
}


