/******************************************************************************

                  ��Ȩ���� (C), 2001-2011, �������Ժͨ�����õ缼���ֹ�˾

 ******************************************************************************
  �� �� ��   : fmprint.h
  �� �� ��   : ����
  ��    ��   : liming
  ��������   : 2013��4��26�� ������
  ����޸�   :
  ��������   : ���ն����Զ���ʽ��ʽ(��ͬ��ǰ��ɫ������ɫ���»��ߵ�)����ı�
  �����б�   : fm_print(char* str, unsigned int ulFormat)
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

  
  �޸���ʷ   :
  1.��    ��   : 2013��4��26�� ������
    ��    ��   : liming
    �޸�����   : �����ļ�

******************************************************************************/

// ���ܴ���
#define FM_ALL_NORMAL    0x00000   // �����������Ե�ȱʡ����
#define FM_BOLD          0x10000   // ���� 
#define FM_HALF_BRIGHT   0x20000   // ����һ������ 
#define FM_UNDERLINE     0x40000
#define FM_FLASH         0x80000   // ��˸
#define FM_RES_WHITE     0x100000  // ������ʾ
#define FM_IN_VISIBLE    0x200000  // ���ɼ�

// ǰ��ɫ
#define FR_NORMAL  0x00 
#define FR_BLACK   0x01  
#define FR_RED     0x02
#define FR_GREEN   0x03
#define FR_YELLOW  0x04
#define FR_BLUE    0x05
#define FR_MAGENTA 0x06         // Magenta �Ϻ�ɫ
#define FR_CYAN    0x07         // ����ɫ
#define FR_WHITE   0x08  
#define FR_SET_UNDERLINE 0x09   // Ĭ��ǰ��ɫ���»���
#define FR_RMV_UNDERLINE 0x0A

// ����ɫ
#define BK_NORMAL  0x0000
#define BK_BLACK   0x0100
#define BK_RED     0x0200
#define BK_GREEN   0x0300
#define BK_YELLOW  0x0400
#define BK_BLUE    0x0500
#define BK_MAGENTA 0x0600  // Magenta �Ϻ�ɫ
#define BK_CYAN    0x0700  // ����ɫ
#define BK_WHITE   0x0800 
#define BK_DEFAULT 0x0900  // Ĭ�ϱ���ɫ

void fmt_print(char* str,...);
void fm_print(char* str, unsigned int ulFormat);

#define FMT_ALL_NORMAL         "0"  // �����������Ե�ȱʡ����
#define FMT_BOLD               "1"  // ���� 
#define FMT_HALF_BRIGHT        "2"  // ����һ������ 
#define FMT_UNDERLINE          "4"
#define FMT_FLASH              "5"  // ��˸
#define FMT_RES_WHITE          "7"  // ������ʾ
#define FMT_IN_VISIBLE         "8"  // ���ɼ�

// ǰ��ɫ
#define FR_COLOR_BLACK         "30"  
#define FR_COLOR_RED           "31"
#define FR_COLOR_GREEN         "32"
#define FR_COLOR_YELLOW        "33"
#define FR_COLOR_BLUE          "34"
#define FR_COLOR_MAGENTA       "35"         // Magenta �Ϻ�ɫ
#define FR_COLOR_CYAN          "36"         // ����ɫ
#define FR_COLOR_WHITE         "37"  
#define FR_COLOR_SET_UNDERLINE "38"   // Ĭ��ǰ��ɫ���»���
#define FR_COLOR_RMV_UNDERLINE "39"

// ����ɫ
#define BK_COLOR_BLACK         "40"
#define BK_COLOR_RED           "41"
#define BK_COLOR_GREEN         "42"
#define BK_COLOR_YELLOW        "43"
#define BK_COLOR_BLUE          "44"
#define BK_COLOR_MAGENTA       "45"   // Magenta �Ϻ�ɫ
#define BK_COLOR_CYAN          "46"   // ����ɫ
#define BK_COLOR_WHITE         "47" 
#define BK_COLOR_DEFAULT       "49"   // Ĭ�ϱ���ɫ

#define FM_PRINT_BNG           "\033["
#define FM_PRINT_MID           "m"
#define FM_PRINT_END           "\033[0m"

/*
|---------------|---------------|---------------|---------------|
     ǰ��ɫ           ����ɫ        ������ʽ        ������
|---------------|---------------|---------------|---------------|
*/

typedef enum
{  
    E_BK_NORMAL = 0,  
    E_BK_BLACK,    // 1
    E_BK_RED,      //2// 2 
    E_BK_GREEN,    // 3
    E_BK_YELLOW,   // 4
    E_BK_BLUE,     // 5
    E_BK_MAGENTA,  // 6 
    E_BK_CYAN,     // 7 
    E_BK_WHITE,    // 8
    E_BK_DEFAULT,  // 9

}eBackColor;

typedef enum
{
    EFMT_ALL_NORMAL,   // 0  �����������Ե�ȱʡ����
    EFMT_BOLD,         // 1  ���� 
    EFMT_HALF_BRIGHT,  // 2  ����һ������ 
    EFMT_UNDERLINE,    // 4  �»���
    EFMT_FLASH,        // 5  ��˸
    EFMT_RES_WHITE,    // 7  ������ʾ
    EFMT_IN_VISIBLE,   // 8  ���ɼ�
    
}eEffect;

