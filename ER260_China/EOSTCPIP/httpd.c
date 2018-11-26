/******************** (C) COPYRIGHT 2012 *****************************************
 * �ļ���  ��httpd.c
 * ����    ����ҳ��������غ���
**********************************************************************************/
#include "httpd.h"
//ouhs #include "usart.h"

const static uint8_t http_html_hdr[] =  HTTP_HEAD;      //http�ļ�ͷ
const static uint8_t login[]= LOGIN;            //Ҫ��ʾ����ҳ
const static uint8_t led_ctrl_on[] =LED_CTRL_ON;
const static uint8_t led_ctrl_off[] =LED_CTRL_OFF;




/**
 * http���յ����ݺ�Ļص�����
 *
 * @author EutronSoftware (2015-01-20)
 *
 * @param arg ���õĲ���
 * @param pcb
 * @param p :�յ�������
 * @param err
 *
 * @return err_t
 */
static err_t http_recv(void *arg, struct tcp_pcb *pcb,struct pbuf *p,err_t err)
{
    char * data = NULL;
    char *UserName =NULL;
    char *PassWord =NULL;
    char *LED_CMD  =NULL;
    char *ch =NULL;

    data = p->payload;  //�ѽ��յ�������ָ�뽻��data

    if (err == ERR_OK && p != NULL)    //�ж��Ƿ�ǿ�
    {
        if (strncmp(data,"GET",3)==0)
        {

            /*��һ������������ӣ��򿪵�¼ҳ�棬δ�����¼��Ϣ*/
            tcp_write(pcb,http_html_hdr,sizeof(http_html_hdr),0);      /* ����httpЭ��ͷ����Ϣ */
            tcp_write(pcb,login,sizeof(login),0);                       /* ���͵�¼��ҳ��Ϣ */
        }

        else if (strncmp(data,"POST",4)==0)
        {
            LED_CMD = strstr(data,"LED_CTRL=");
            UserName = strstr(data,"UserName=");        //��ȡUserName=
            PassWord = strstr(UserName,"PassWord=");    //��ȡPassWord=

            if (UserName!=NULL && PassWord!=NULL)     /*�������û���������*/
            {
                ch = strchr(UserName,'&');              //��&�滻Ϊ��\0��
                *ch = '\0';

                UserName +=sizeof("UserName=")-1;       //��ȡ�û�����sizeof�ַ���������ֹ����\0��
                PassWord += sizeof("PassWord=")-1;      //��ȡ����

                if (strcmp(UserName,"EUTR")==0 && strncmp(PassWord,"123456",6)==0)   /*������û�����������ȷ*/
                {
                    USART_printf("\r\nLED1 ON\r\n");//LED1(ON);
                    //	printf("\r\n��ȡ�����û��� =%s\r\n��ȡ�������� =%s",UserName,PassWord);
                    tcp_write(pcb,http_html_hdr,sizeof(http_html_hdr),0);      /* ����httpЭ��ͷ����Ϣ */
                    tcp_write(pcb,led_ctrl_on,sizeof(led_ctrl_on),0);          /* ����led������ҳ��Ϣ */

                } else /*������û������������*/
                {
                    tcp_write(pcb,http_html_hdr,sizeof(http_html_hdr),0);      /* ����httpЭ��ͷ����Ϣ */
                    tcp_write(pcb,login,sizeof(login),0);                       /* ���͵�¼��ҳ��Ϣ */
                }
            } else if (LED_CMD !=NULL)   /*���յ�LED��������*/
            {
                if (strstr(LED_CMD,"LED_CTRL=ON"))    /*������ĸ������\��*/
                {
                    USART_printf("\r\nLED1 ON\r\n");//LED1(ON);
                    tcp_write(pcb,http_html_hdr,sizeof(http_html_hdr),0);      /* ����httpЭ��ͷ����Ϣ */
                    tcp_write(pcb,led_ctrl_on,sizeof(led_ctrl_on),0);         /* ����led������ҳ��Ϣ */
                } else if (strstr(LED_CMD,"LED_CTRL=OFF"))
                {
                    USART_printf("\r\nLED1 OFF\r\n");//LED1(OFF);
                    tcp_write(pcb,http_html_hdr,sizeof(http_html_hdr),0);      /* ����httpЭ��ͷ����Ϣ */
                    tcp_write(pcb,led_ctrl_off,sizeof(led_ctrl_off),0);        /* ����led������ҳ��Ϣ */
                }
            }
        }

        pbuf_free(p);  /* �ͷŸ�pbuf�� */
    }
    tcp_close(pcb);                                                       /* �ر�������� */
    err = ERR_OK;

    return err;
}



/*
 * ��������http_accept
 * ����  ��http web server�Ļص��������������Ӻ����
 * ����  ��tcp_arg���õĲ�����pcb��err
 * ���  ��err
 * ����  ���ڲ�����
 */
static err_t http_accept(void *arg,struct tcp_pcb *pcb,err_t err)
{
    tcp_setprio(pcb, TCP_PRIO_MIN);     /* ���ûص��������ȼ��������ڼ�������ʱ�ر���Ҫ���˺����������*/

    tcp_recv(pcb,http_recv);            /* ����TCP�ε�ʱ�Ļص����� */

    return ERR_OK;
}


/**
 * ��ʼ��web server����ʼ���������ʾ��ҳ
 *
 * @author EutronSoftware (2015-01-20)
 */
void httpd_init(void)
{
    struct tcp_pcb *pcb;

    pcb = tcp_new();                           /* ����ͨ�ŵ�TCP���ƿ�(pcb) */

    tcp_bind(pcb,IP_ADDR_ANY,HTTP_PORT);             /* �󶨱���IP��ַ�Ͷ˿ں� */

    pcb = tcp_listen(pcb);                    /* �������״̬ */

    tcp_accept(pcb,http_accept);             /* ��������������ʱ�Ļص����� */

}

