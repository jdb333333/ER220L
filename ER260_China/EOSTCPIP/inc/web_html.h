
/* ���ļ����ڴ洢��ҳ��html�ļ�
*���ڱ��ļ���c�����ļ���
*html���ı��ļ���ʹ��html����ʱ��
*ע��Է��� "  //  ���� \  ���Ա�ʾ��ascii�롣
*/

/*http�ļ�ͷ */
#define HTTP_HEAD "HTTP/1.1 200 OK\r\nContent-type: text/html\r\n\r\n"


/*��ҳ����������ʽ�洢����¼ҳ��*/
#define LOGIN "\
<html>\
<head>\
<meta http-equiv=\"Content-Type\" content=\"text/html; charset=gb2312\">\
<title>ER-260��̫������</title>\
</head>\
</body>\
<br><center><h2>�Ŵ�STM32����ƽ̨</h2>\
<br><center><b>***********�Ŵ�STM32F205-ENC28J60-��ֲLWIP***********</b>\
<form action=\"login\" method=\"post\">\
<p>  �û���:\
<input type=\"text\" name=\"UserName\">\
<p>	 ����:\
<input type=\"password\" name=\"PassWord\">\
<p><input type=\"submit\" value=\"��¼\"> \
</form>\
<br><br><br><center><a href=\"http:/\/www.eutron.com.cn/\">�Ŵ������ϣ���Ϣ�豸���޹�˾</a>\
</body> \
</html>\
" 
//form_action.asp
/*��ҳ����������ʽ�洢��LED����ҳ��*/
#define LED_CTRL_ON "\
<html>\
<head>\
<meta http-equiv=\"Content-Type\" content=\"text/html; charset=gb2312\">\
<title>ER-260��̫������</title>\
</head>\
</body>\
<br><center><h2>�Ŵ�STM32����ƽ̨</h2>\
<br><center><b>***********�Ŵ�STM32F205-ENC28J60-��ֲLWIP***********</b>\
<br><br><br><center><b>***********��������¼�ɹ�������***********</b>\
<br><br><br>LED״̬:  <input type=\"button\" id=\"b1\" style=\"background:#0000FF\" value=\"��\" > \
<form name=\"input\" action=\"/html/html_form_action.asp\" method=\"post\">\
<br>����LED1<input type=\"radio\" name=\"LED_CTRL\" value=\"ON\" checked=\"checked\">\
<br/>\
<br>�ر�LED1<input type=\"radio\" name=\"LED_CTRL\" value=\"OFF\">\
<br><br><center><input type =\"submit\" value =\"����\">\
<br><br><br><center><a href=\"http:/\/www.eutron.com.cn/\">�Ŵ������ϣ���Ϣ�豸���޹�˾</a>\
</body> \
</html>\
"

#define LED_CTRL_OFF "\
<html>\
<head>\
<meta http-equiv=\"Content-Type\" content=\"text/html; charset=gb2312\">\
<title>ER-260��̫������</title>\
</head>\
</body>\
<br><center><h2>�Ŵ�STM32����ƽ̨</h2>\
<br><center><b>***********�Ŵ�STM32F205-ENC28J60-��ֲLWIP***********</b>\
<br><br><br><center><b>***********��������¼�ɹ�������***********</b>\
<br><br><br>LED״̬:  <input type=\"button\" id=\"b1\" style=\"background:#DCDCDC\" value=\"��\" > \
<form name=\"input\" action=\"/html/html_form_action.asp\" method=\"post\">\
<br>����LED1<input type=\"radio\" name=\"LED_CTRL\" value=\"ON\" checked=\"checked\">\
<br/>\
<br>�ر�LED1<input type=\"radio\" name=\"LED_CTRL\" value=\"OFF\" checked=\"checked\">\
<br><br><center><input type =\"submit\" value =\"����\">\
<br><br><br><center><a href=\"http:/\/www.eutron.com.cn/\">�Ŵ������ϣ���Ϣ�豸���޹�˾</a>\
</body> \
</html>\
"

