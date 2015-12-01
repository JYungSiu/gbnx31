#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include "fmprint.h"

/*****************************************************************************
 �� �� ��  : fmt_print
 ��������  : ��ʽ�����
 �������  : char* str
             int fmt
             ...
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��4��26�� ������
    ��    ��   : liming
    �޸�����   : �����ɺ���

*****************************************************************************/
void fmt_print(char* str,...)
{
    if(!str)
    {
        return;
    }

    char outbuf[1024] = {0};
    char *pStr;
    int len = 0;

    va_list arg_ptr;

    len += sprintf(outbuf, "%s", FM_PRINT_BNG);
    va_start(arg_ptr, str);
    do
    {
        pStr = va_arg(arg_ptr, char*);
        if(pStr != NULL)
        len += sprintf(outbuf+len,"%s;", pStr);

    }while(pStr != NULL);

    va_end(arg_ptr);
    sprintf(outbuf+len-1, "%s%s%s", FM_PRINT_MID, str, FM_PRINT_END);
    printf(outbuf);
}

/*****************************************************************************
 �� �� ��  : fm_print
 ��������  : | | �ķ����������ʽ
 �������  : char* str
             unsigned int ulFormat
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��4��26�� ������
    ��    ��   : liming
    �޸�����   : �����ɺ���


ʹ�ð�����ǰ��ɫ | ����ɫ | ���ֹ��������

    ��:fm_print("text", ǰ��ɫ[|����ɫ|��ʽ��])

    // ǰ��ɫ
    FR_NORMAL          Ĭ��ɫ
    FR_BLACK           ��ɫ
    FR_RED             ��ɫ
    FR_GREEN           ��ɫ
    FR_YELLOW          ��ɫ
    FR_BLUE            ��ɫ
    FR_MAGENTA         �Ϻ�ɫ
    FR_CYAN            ����ɫ
    FR_WHITE           ��ɫ
    FR_SET_UNDERLINE   Ĭ��ǰ��ɫ���»���
    FR_RMV_UNDERLINE 

    // ����ɫ
    BK_NORMAL          Ĭ��ɫ
    BK_BLACK           ��ɫ
    BK_RED             ��ɫ
    BK_GREEN           ��ɫ
    BK_YELLOW          ��ɫ
    BK_BLUE            ��ɫ
    BK_MAGENTA         �Ϻ�ɫ
    BK_CYAN            ����ɫ
    BK_WHITE           ��ɫ
    BK_DEFAULT         Ĭ�ϱ���ɫ
    
    // ��ʽ��
    FM_ALL_NORMAL      �����������Ե�ȱʡ����
    FM_BOLD            ����
    FM_HALF_BRIGHT     ����һ������
    FM_UNDERLINE       �»���
    FM_FLASH           ��˸
    FM_RES_WHITE       ������ʾ
    FM_IN_VISIBLE      ���ɼ�

*****************************************************************************/
void fm_print(char* str, unsigned int ulFormat)
{
    unsigned char ucFrontColor = 0;
    unsigned char ucBackColr   = 0;
    unsigned char ucEffect     = 0;
    unsigned char ucCtrl       = 0;
    unsigned int  ulFormatTmp  = 0;
    int           len          = 0;
    
    ucFrontColor = ulFormat         & 0xFF;
    ucBackColr   = (ulFormat >> 8)  & 0xFF;
    ucEffect     = (ulFormat >> 16) & 0xFF;
    ucCtrl       = (ulFormat >> 24) & 0xFF;
    ucCtrl       = ucCtrl;
    char strFmt[64] = {0};

    switch(ucFrontColor)
    {
        case FR_NORMAL:
            break;

        case FR_BLACK:
            len = sprintf(strFmt, "%s", FR_COLOR_BLACK);
            break;
            
        case FR_RED:
            len = sprintf(strFmt, "%s", FR_COLOR_RED);
            break;
            
        case FR_GREEN:
            len =  sprintf(strFmt, "%s", FR_COLOR_GREEN);
            break;
            
        case FR_YELLOW:
            len = sprintf(strFmt, "%s", FR_COLOR_YELLOW);
            break;
            
        case FR_BLUE:
            len = sprintf(strFmt, "%s", FR_COLOR_BLUE);
            break;
            
        case FR_MAGENTA:
            len = sprintf(strFmt, "%s", FR_COLOR_MAGENTA);
            break;
            
        case FR_CYAN:
            len = sprintf(strFmt, "%s", FR_COLOR_CYAN);
            break;
            
       case FR_WHITE:
            len = sprintf(strFmt, "%s", FR_COLOR_WHITE);
            break;
            
        case FR_SET_UNDERLINE:
            len = sprintf(strFmt, "%s", FR_COLOR_SET_UNDERLINE);
            break;
            
        case FR_RMV_UNDERLINE:
            len = sprintf(strFmt, "%s", FR_COLOR_RMV_UNDERLINE);
            break;

        default:
            break;
    }

    if(ucBackColr != 0)
    {
        len += sprintf(strFmt+len,"%s",";");
    }

    switch(ucBackColr)
    {
        case E_BK_BLACK:
            len += sprintf(strFmt+len, "%s", BK_COLOR_BLACK);
            break;
            
        case E_BK_RED:
            len += sprintf(strFmt+len, "%s", BK_COLOR_RED);
            break;
            
        case E_BK_GREEN:
            len += sprintf(strFmt+len, "%s", BK_COLOR_GREEN);
            break;
            
        case E_BK_YELLOW:
            len += sprintf(strFmt+len, "%s", BK_COLOR_YELLOW);
            break;
            
        case E_BK_BLUE:
            len += sprintf(strFmt+len, "%s", BK_COLOR_BLUE);
            break;
            
        case E_BK_MAGENTA:
           len += sprintf(strFmt+len, "%s", BK_COLOR_MAGENTA);
            break;
            
        case E_BK_CYAN:
            len += sprintf(strFmt+len, "%s", BK_COLOR_CYAN);
            break;
            
       case E_BK_WHITE:
            len += sprintf(strFmt+len, "%s", BK_COLOR_WHITE);
            break;
            
        default:
            break;

    }

    if(ucEffect != 0)
    {
        len += sprintf(strFmt+len, "%s", ";");
    }

    ulFormatTmp = ulFormat & 0xFFFF0000;
    if(ulFormatTmp & FM_BOLD)
    {
         len += sprintf(strFmt+len, "%s", FMT_BOLD);
         ulFormatTmp &= ~FM_BOLD;

         if(ulFormatTmp != 0)
         {
            len += sprintf(strFmt+len, "%s", ";");
         }
    }

    if(ulFormatTmp & FM_HALF_BRIGHT)
    {
         len += sprintf(strFmt+len, "%s", FMT_HALF_BRIGHT);
         ulFormatTmp &= ~FM_HALF_BRIGHT;
         if(ulFormatTmp != 0)
         {
            len += sprintf(strFmt+len, "%s", ";");
         }
    }

    if(ulFormatTmp & FM_UNDERLINE)
    {
         len += sprintf(strFmt+len, "%s", FMT_UNDERLINE);
         ulFormatTmp &= ~FM_UNDERLINE;
         if(ulFormatTmp != 0)
         {
            len += sprintf(strFmt+len, "%s", ";");
         }
    }

    if(ulFormatTmp & FM_FLASH)
    {
         len += sprintf(strFmt+len, "%s", FMT_FLASH);
         ulFormatTmp &= ~FM_FLASH;
         if(ulFormatTmp != 0)
         {
            len += sprintf(strFmt+len, "%s", ";");
         }
    }

    if(ulFormatTmp & FM_RES_WHITE)
    {
         len += sprintf(strFmt+len, "%s", FMT_RES_WHITE);
         ulFormatTmp &= ~FM_RES_WHITE;
         if(ulFormatTmp != 0)
         {
            len += sprintf(strFmt+len, "%s", ";");
         }
    }

    if(ulFormatTmp & FM_IN_VISIBLE)
    {
         len += sprintf(strFmt+len, "%s", FMT_IN_VISIBLE);
         ulFormatTmp &= ~FM_IN_VISIBLE;
         if(ulFormatTmp != 0)
         {
            len += sprintf(strFmt+len, "%s", ";");
         }
    }

    //CTRL
    printf("%s%s%s%s%s", FM_PRINT_BNG, strFmt, FM_PRINT_MID, str, FM_PRINT_END);
    //sprintf(strOut, "%s%s%s%s%s", FM_PRINT_BNG,strFmt,FM_PRINT_MID,str,FM_PRINT_END);
    //printf(strOut);
}

