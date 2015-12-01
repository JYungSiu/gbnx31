/******************************************************************************

                  ��Ȩ���� (C), 2005-2015, ���ҵ���ͨ�����õ缼���ֹ�˾

 ******************************************************************************
  �� �� ��   : gbnx_31_api.h
  �� �� ��   : ����
  ��    ��   : liming
  ��������   : 2013��10��17��
  ����޸�   :
  ��������   : GB/T XXXX.31 2013 ��վ��ɼ��ն�ͨ��Э�����api(C����)
               ���ļ��������ҵ����������ϵͳ�����淶(����) ��3-1����
               ��(��)վ�����ͨ����Ϣ�����뽻���ն�ͨ��Э��
               ��صĶ��弰Э������Ļ����ӿ�

  ��д˵��   : ��վ              master       -> m
               �����ն�(������)  concentrator -> c
               �ɼ��ն�(�ն�)    terminal     -> t

               �û�������(Ĭ���ֽڶ���)
               ��֡������(��1 �ֽڶ���)

  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2013��10��17��
    ��    ��   : liming(vliming@126.com)
    �޸�����   : �����ļ�

******************************************************************************/
#ifndef _GBNX_31_API_H_
#define _GBNX_31_API_H_


/*******************************************************
 *  �����ļ� �����
 *  �ô�API֮ǰ�����ú�
 *
{*///
#ifndef _TYPE_DEF_LM_
#define _TYPE_DEF_LM_
#ifndef __RTL_H__
#define __RTL_H__
typedef char                BOOL;
#endif
#define TRUE                (1)
#define FALSE               (0)
typedef unsigned char       UCHAR;
typedef char                CHAR;
typedef unsigned short      USHORT;
typedef short               SHORT;
typedef unsigned long       ULONG;
typedef long                LONG;

#ifndef _TYPE_DEF_
#define _TYPE_DEF_
typedef char                INT8;       //c
typedef short               INT16;      //s
typedef int                 INT32;      //l
typedef unsigned char       UINT8;      //uc
typedef unsigned short      UINT16;     //us
typedef unsigned int        UINT32;     //ul

#ifdef MACHINE_64_BITS
typedef long                INT64;
typedef unsigned long       UINT64;
#else
typedef long long           INT64;
typedef unsigned long long  UINT64;
#endif

typedef char*               STRING;     //str
typedef char                ISBOOL;     //b
typedef unsigned int        IPADDR;     //ip
typedef double              DOUBLE;
typedef void*               FRWK_HANDLE;
#endif
#endif
///*}

/*******************************************************
 *  �����ļ� �����
 *  �ô�API֮ǰ�����ú�
 *
{*///

#define MC_CFG_SPT_MST         (1)         // �Ƿ�֧����վ   �����ļ� ��֧�ֽ����Ϊ 0
#define MC_CFG_SPT_CON         (1)         // �Ƿ�֧�ּ����� �����ļ� ��֧�ֽ����Ϊ 0
#define MC_CFG_MEDIUM_NET      (1)         // ͨ�Ž���,���������ĵ���󳤶� �������̫��1 ������0
#define MC_CFG_ENCRYPT         (0)         // �Ƿ���Ҫ����
#define MC_CFG_EC              (1)         // ��������Ĭ���������Ec 
#define MC_CFG_TP              (1)         // ��������Ĭ���������Tp
#define MC_CFG_PW              (1)         // ��������Ĭ���������Pw
#define MC_CFG_IP_VER          (1)         // IP��ַ�İ汾 1-IPV4 0-IPV6         
///*}

/*******************************************************
 *  Э����غ궨��
 *
{*///

#define MC_PROTO_VERSION       (0x21)       // ��Э��汾

#define METER_ADDR_LEN         (12)         // ����ַ����
/****************************************
 *  ��ַ��
 *  �ն˵�ַA2ѡַ��ΧΪ1��65535��
 *  A2=0000HΪ��Ч��ַ��A2=FFFFH��A3��D0λΪ"1"ʱ��ʾϵͳ�㲥��ַ��
 *
 *
 *
{*///

#define MC_TML_ADDR_MIN        (1)         // �ն˻�������ַ���ֵ
#define MC_TML_ADDR_MAX        (65535)     // ��վ��ַ���ֵ
#define MC_TML_ADDR_BRD        (0xFFFF)    // ��վ��ַ���ֵ

#define MC_MST_ADDR_MIN        (0)         // ��վ��ַ���ֵ
#define MC_MST_ADDR_MAX        (127)       // ��վ��ַ���ֵ

///*}

/****************************************
 *  Ӧ�������� ���ݵ�Ԫ��ʶ
 *  ����һ��ȷ����DaDt�ṹ,���֧�� 8��Pn ͬʱ����Ӧ�����±� 8��Fn
 *  ������Ҫ 8*8�����ݵ�Ԫ
 *
 *
 *
{*///
#define MC_PN_INDEX_MAX        (8)          // �������ݵ�Ԫ����֯
#define MC_FN_INDEX_MAX        (8)          // �������ݵ�Ԫ����֯
///*}

/****************************************
 *  ��⡢��װ��ز����ֽڳ�
 *
 *
 *
{*///
#define MC_PW_LEN              (16)         // ��Ϣ��֤����
#define MC_PN_MAX              (2040)       // ���ݵ�Ԫ��ʶ DA Pn ���ֵ
#define MC_PN_MIN              (0)          // ���ݵ�Ԫ��ʶ Da Pn ��Сֵ
#define MC_PN_NONE             (0xFFFF)     // ���ݵ�Ԫ��ʶ Da Pn ��Чֵ �����ù��ĵ�ֵ
 
#define MC_FN_MAX              (248)        // ���ݵ�Ԫ��ʶ Dt Fn ���ֵ
#define MC_FN_MIN              (1)          // ���ݵ�Ԫ��ʶ Dt Fn ��Сֵ
#define MC_FN_NONE             (0xFF)       // ���ݵ�Ԫ��ʶ Dt Fn ��Чֵ �����ù��ĵ�ֵ

#define MC_UNIT_DATA_MAX       (128)        // �������ݵ�Ԫ�ֳ�

#define MC_FRM_MAX_WRLESS      (255)        // ����ר�����������ŵ�,����L1������255
#define MC_FRM_MAX_NET         (16384)      // �������紫��,����L1������16383
#define MC_SEQ2CS_MAX          (2048)       // ÿ��֡����SEQ��CS֮�������ֽ������ֵ
#define MC_CA_LEN              (10)          // ���������ַ�����ֳ�
#define MC_VAC_LEN             (2)          // �䳤֡��Э���ʶ��Ӧ�ÿ�����AC�ֽڳ���
#define MC_CANS_LEN            (8)          // ������C ��ַ��A AFN SEQ�ֽ��ܳ�
#define MC_UN_USER_LEN         (8)          // �����з��������ܳ���  0x68 0x68 L L CS 0x16
#define MC_DADT_LEN            (4)          // ���ݱ�ʶ�ֳ� DaDt
#define MC_AFN_LEN             (1)          // AFN �ֳ�
#define MC_DADT_ERR_LEN        (MC_DADT_LEN + 1)  // DaDt �� ERR���ֳ�

// ֡������ֳ�
#if MC_CFG_MEDIUM_NET
#define MC_FRM_LEN_MAX         MC_FRM_MAX_NET
#else
#define MC_FRM_LEN_MAX         MC_FRM_MAX_WRLESS
#endif

#define MC_CS_LEN              (1)                          // У���CS�ֳ�
#define MC_FIXED_USR_LEN       (MC_A_LEN + MC_C_LEN + 1)    // �̶�֡�û��������ֳ� (������C + ��ַ��A + ��·�û�����D)
#define MC_FIXED_LEN           (MC_FIXED_USR_LEN + 3)       // �̶�֡�ֳ�           (�û������� + ��ʼ�ַ�+ CS)
#define MC_STCHAR_FIXED        (0x10)                       // �̶�֡��ʼ�ַ�
#define MC_STCHAR_ALTER        (0x68)                       // �ɱ�֡��ʼ�ַ�
#define MC_FRM_END_CHAR        (0x16)                       // ������
#define MC_ALTER_USR_OTHER_LEN (MC_A_LEN + MC_C_LEN)        // �ɱ�֡�û��������ֳ�(����·�û�����)
#define MC_ALTER_BUT_USER_LEN  (8)                          // �ɱ�֡����(�û�������֮��ĳ���)
#define MC_ALTER_OTHER_LEN     (MC_ALTER_USR_OTHER_LEN + 8) // �ɱ�֡������·�û������ⲿ���ֳ�

#define MC_A2CS_BYTE_MAX       (MC_FRM_LEN_MAX - MC_ALTER_OTHER_LEN)  // ÿ��֡����A��CS֮�������ֽ������ֵ
#define MC_USER_MAX            (2*MC_A2CS_BYTE_MAX)                   // �û���ȱ䳤�ṹ smcPack smcBasePack ��󳤶�

// ֡����С�ֳ�
#define MC_FRM_LEN_MIN         (MC_FIXED_LEN)               // ��������¼��֡����С

// IP��ַ����
#if MC_CFG_IP_VER
#define MC_IP_LEN              (4)                          // ��ӦIPv4 ��ַ����
#else 
#define MC_IP_LEN              (16)                         // ��ӦIpv6 ��ַ����
#endif
///*}

/*******************************************************
 *  �����붨�� eMcErr
 *
{*///
typedef enum
{
    MC_OK,             // �޴���                    0
    MC_ERR_NULL,       // ָ��Ϊ��                  1
    MC_ERR_OUTRNG,     // ����Խ��                  2
    MC_ERR_NONE,       // ������,û���ҵ�           3
    MC_ERR_IO,         // IO����                    4
    MC_ERR_RES,        // ��Դ����                  5
    MC_ERR_INIT,       // û�г�ʼ��                6
    MC_ERR_PARA,       // ��������                  7
    MC_ERR_FN,         // ָ��Afn �в�֧�ֵ� Fn     8
    MC_ERR_PN,         // ָ��Afn �в�֧�ֵ� Pn     9
    MC_ERR_ADDR,       // ��Ч��ַ                  10
    MC_ERR_CTRL,       // ���������                11
    MC_ERR_0x10,       // SEQ�����                 12
    MC_ERR_A2CS,       // A2CS �������             13
    MC_ERR_AFN,        // AFN ����                  14
    MC_ERR_UNCOMP,     // ��������Э���            15
    MC_ERR_0x68,       // ����ı�����ʼ            16
    MC_ERR_PROTO,      // �����Э���ʶ            17
    MC_ERR_CS,         // ����ļ���              18
    MC_ERR_0x16,       // ����Ľ�β��              19
    MC_ERR_LOGIC,      // ����Ĵ����߼�            20
    MC_ERR_PACK,       // ����һ����Ч�İ�          21
    MC_ERR_PFC,        // ���кŲ���Ӧ              22
    MC_ERR_TIMEOUT,    // ���ĳ�ʱ                  23
    MC_ERR_PRM,        // ����վ��ʶ��              24
    MC_ERR_TEAM,       // Fn��Pn����ͬһ����        25
    MC_ERR_ENCRYPT,    // ���ܴ���                  26
    MC_ERR_DECRYPT,    // ���ܴ���                  27
    MC_ERR_L1L2,       // ֡�е�L1��L2�����        28
    MC_ERR_FCODE,      // ���������                29
    MC_ERR_DIR,        // ���ĵķ������            30

}eMcErr;
///*}

/*******************************************************
 *  Ӧ�ò㹦���� AFN
 *
{*///
typedef enum
{
    MC_AFN_00_CONF  = 0x00,     // ȷ�Ϸ���                
    MC_AFN_01_RSET  = 0x01,     // ��λ                     (���б���, ���б���Ϊȷ��/���ϱ���)
    MC_AFN_02_LINK  = 0x02,     // ��·����                 ��AFN��������Э��,�������Ϊ��ʵ�ַ���,��ע��
    MC_AFN_04_SETP  = 0x04,     // ���ò���                 (���б���, ���б���Ϊȷ��/���ϱ���)
    MC_AFN_05_CTRL  = 0x05,     // ��������                 (���б���, ���б���Ϊȷ��/���ϱ���)
    MC_AFN_06_AUTH  = 0x06,     // �����֤����ԿЭ��       (�����б���)
    MC_AFN_08_CASC  = 0x08,     // ���󱻼����ն������ϱ�
    MC_AFN_10_GETP  = 0x0A,     // ��ѯ����                 (�����б���, ����Ӧ������)
    MC_AFN_12_ASKT  = 0x0C,     // ���󣨶�ʱ�ϱ����������� (�����б���, ����Ӧ������)
    MC_AFN_13_ASKR  = 0x0D,     // ����ʵʱ����             (�����б���, ����Ӧ������)
    MC_AFN_14_ASKE  = 0x0E,     // ���������ϱ����¼���¼ (�����б���, ����Ӧ������)
    MC_AFN_15_FILE  = 0x0F,     // �ļ�����                 
    MC_AFN_16_DATA  = 0x10,     // ����ת��
    MC_AFN_NULL     = 0xFF      // �����ڵ�AFN

}eMcAFN;
 ///*}

/*******************************************************
 *  �����붨��
 *  �������� MCMD_AFN_(xx)_F(xx)_NAME
 *  xx ��ʾ����
 *  F  ��ʾ��Ϣ���ʶ
 *  ����Э�����, ÿ���ڵ����8��Fn�������һ�����ݱ�ʶ
 *  ����: �ն˻���������վ
 *  ����: ��վ���ն˻�����
 *
{*///
typedef enum
{
    MCMD_AFN_F_UNKOWN,                                // δ֪����

    /**********************************
    * ����: ȷ��/����
    * AFN : 00H
    *  PN : p0
    * ����: ��
    * ����: ��
    {*///
    MCMD_AFN_0_F1_ALL_OK_DENY         = 0x0001,       // ȫ��ȷ��/���ϣ����յ������е�ȫ�����ݵ�Ԫ��ʶ����ȷ��/����
    MCMD_AFN_0_F2_ONE_BY_ONE          = 0x0002,       // �����ݵ�Ԫ��ʶȷ�Ϻͷ��ϣ����յ������е�ȫ�����ݵ�Ԫ��ʶ�������ȷ��/����
    ///*}

    /**********************************
     * ����: ��λ����
     * AFN : 01
     *  PN : p0 /����ն˺�
     * ����: AFN 00H ȷ��/����
     * ����: ��
    {*///
    MCMD_AFN_1_F1_HARD_INIT           = 0x0101,       // Ӳ����ʼ��
    MCMD_AFN_1_F2_DATA_INIT           = 0x0102,       // ��������ʼ��
    MCMD_AFN_1_F3_FACTORY_RESET       = 0x0103,       // ������ȫ����������ʼ�������ָ����������ã�
    MCMD_AFN_1_F4_PARA_INIT           = 0x0104,       // ����������ϵͳ��վͨ���йصģ���ȫ����������ʼ��
    MCMD_AFN_1_F5_DATA_CLEAR          = 0x0105,       // ָ����������
    ///*}


    /**********************************
     * ��·�ӿڼ��
     * AFN : ��
     *  PN : ��
     * ����: ��(F1 ~ F3)
     * ����: ��(F4)
     * ˵��: ��������֡Ϊ�̶�֡,�����֡��ʽΪ�ɱ�֡
    {*///
    MCMD_AFN_2_F1_LOG_IN              = 0x0201,       // ������·����¼ϵͳ
    MCMD_AFN_2_F2_LOG_OUT             = 0x0202,       // �����·���˳�ϵͳ
    MCMD_AFN_2_F3_HEART_BEAT          = 0x0203,       // ������·����������
    MCMD_AFN_2_F4_LINK_OK             = 0x0204,       // ȷ��(��¼/�˳�/����)
    ///*}

    /**********************************
     * ����: ���ò���
     * AFN : 04
     *  PN : ���鶨��
     * ����: ��
     * ����: ��
    {*///
    // ��1   pn:p0
    MCMD_AFN_4_F1_CON_UP_CFG          = 0x0401,       // ��Ϣ�����뽻���ն�����ͨ�ſ�ͨ�Ų���
    MCMD_AFN_4_F2_MST_PARA            = 0x0402,       // ��(��)վ����
    MCMD_AFN_4_F3_CON_AUTH_PARA       = 0x0403,       // ��Ϣ�����뽻���ն�����ͨ����Ϣ��֤����
    MCMD_AFN_4_F4_TEAM_ADDR           = 0x0404,       // ��Ϣ�����뽻���ն����ַ
    MCMD_AFN_4_F5_CON_IP_PORT         = 0x0405,       // ��Ϣ�����뽻���ն�IP��ַ�Ͷ˿�
    MCMD_AFN_4_F6_CON_CASC            = 0x0406,       // ��Ϣ�����뽻���ն˼���ͨ�Ų���
    MCMD_AFN_4_F7_CON_DOWN_CFG        = 0x0407,       // ��Ϣ�����뽻���ն�������̫���˿�ͨ�Ų���

    // ��2   pn:p0/����ն˺�
    MCMD_AFN_4_F9_CON_EVENT_CFG       = 0x0409,       // �¼���¼����
    MCMD_AFN_4_F10_CON_STATE_INPUT    = 0x040A,       // �豸״̬���������

    // ��3   pn:����ն˺�
    MCMD_AFN_4_F17_TML_UP_CFG         = 0x0411,       // ����ն�����ͨ�Ų�������

    // ��4   pn:�����������
    MCMD_AFN_4_F25_ELEC_MP_CFG        = 0x0419,       // �������������ò���
    MCMD_AFN_4_F26_ELEC_MP_BASE       = 0x041A,       // �����������������
    MCMD_AFN_4_F27_ELEC_LMIT_POWER    = 0x041B,       // �����������������ֵ����
    MCMD_AFN_4_F28_ELEC_LMIT_FACTR    = 0x041C,       // ���������㹦������Խ��ֵ����
    MCMD_AFN_4_F29_ELEC_FIX_HARM      = 0x041D,       // ����������г��������Խ�޶�ֵ
    MCMD_AFN_4_F30_ELEC_FLASH         = 0x041E,       // ��������������Խ�޲���

    // ��5   pn:�ǵ����������
    MCMD_AFN_4_F33_NELC_MP_CFG        = 0x0421,       // �ǵ������������ò���
    MCMD_AFN_4_F34_NELC_MP_PARA       = 0x0422,       // �ǵ������������ݲ���
    MCMD_AFN_4_F35_NELC_MP_LMIT       = 0x0423,       // �ǵ���������Խ�����ݲ���

    // ��7  pn:�����
    MCMD_AFN_4_F49_FREZ_TASK_PARA     = 0x0431,       // ���������������
    ///*}

    /**********************************
     * ����: ��������
     * AFN : 05
     *  PN : ���鶨��
     * ����: AFN 00H ȷ��/����
     * ����: ��
    {*///
    // ��1  pn:p0
    MCMD_AFN_5_F1_CHECK_TIME          = 0x0501,       // Уʱ����
    MCMD_AFN_5_F2_FREZ_TEMP           = 0x0502,       // ��ʱ��������
    MCMD_AFN_5_F3_AUTO_SAY_ON         = 0x0503,       // ������Ϣ�����뽻���ն������ϱ�
    MCMD_AFN_5_F4_AUTO_SAY_OFF        = 0x0504,       // ��ֹ��Ϣ�����뽻���ն������ϱ�
    MCMD_AFN_5_F5_CON_LINK_ON         = 0x0505,       // ������Ϣ�����뽻���ն�������(��)վ
    MCMD_AFN_5_F6_CON_LINK_OFF        = 0x0506,       // ������Ϣ�����뽻���ն˶Ͽ�����

    // ��2  pn:p0/����ն˺�
    MCMD_AFN_5_F9_REMOTE_OFF          = 0x0509,       // ң����բ
    MCMD_AFN_5_F10_REMOTE_ON          = 0x050A,       // �����բ

    // ��3  pn:p0/����ն˺�
    MCMD_AFN_5_F17_NX_MODEL_ACT       = 0x0511,       // ��Чģ����Ч
    MCMD_AFN_5_F18_NX_MODEL_CLR       = 0x0512,       // ��Чģ�����
    MCMD_AFN_5_F19_RQ_RESPN_ACT       = 0x0513,       // ������Ӧ��Ϣ��Ч
    MCMD_AFN_5_F20_RQ_RESPN_CLT       = 0x0514,       // ������Ӧ��Ϣ���

    // ��4  pn:�����
    MCMD_AFN_5_F25_REPT_FREZ_ON       = 0x0519,       // ������ʱ�ϱ�������������
    MCMD_AFN_5_F26_REPT_FREZ_OFF      = 0x051A,       // ��ֹ��ʱ�ϱ�������������
    MCMD_AFN_5_F27_TASK_FREZ_ON       = 0x051B,       // ����������������
    MCMD_AFN_5_F28_TASK_FREZ_OFF      = 0x051C,       // ������������ֹͣ
    ///*}

    /**********************************
     * ����: �����֤����ԿЭ��
     * AFN : 06
     *  PN : p0
     * ����: ��
     * ����: ��
    {*///
    MCMD_AFN_6_F1_ID_AUTH_Q           = 0x0601,       // �����֤����
    MCMD_AFN_6_F2_ID_AUTH_A           = 0x0602,       // �����֤��Ӧ
    MCMD_AFN_6_F3_RAND_Q              = 0x0603,       // ȡ���������
    MCMD_AFN_6_F4_RAND_A              = 0x0604,       // ȡ�������Ӧ
    ///*}

    /**********************************
     * ����: ���󱻼����ն������ϱ�
     * AFN : 08
     *  PN : p0
     * ����: �������ϱ�����ʱ,
     *       �������ϱ�����ʱ, Ӧ����ϱ��� CMD_AFN_0_F2_ALL_DENY
     * ����: ��
    {*///
    MCMD_AFN_8_F1_CALL_AUTO_REPT      = 0x0801,       // ���󱻼����ն������ϱ�
    ///*}

    /**********************************
     * ����: ��ѯ����
     * AFN : 0A
     *  PN : ���鶨��
     * ����: ��
     * ����: ��
    {*///
    // ��1   pn:p0
    MCMD_AFN_A_F1_CON_UP_CFG          = 0x0A01,       // ��ѯ��Ϣ�����뽻���ն�����ͨ�ſ�ͨ�Ų���
    MCMD_AFN_A_F2_MST_PARA            = 0x0A02,       // ��ѯ��(��)վ����
    MCMD_AFN_A_F3_CON_AUTH_PARA       = 0x0A03,       // ��ѯ��Ϣ�����뽻���ն�����ͨ����Ϣ��֤����
    MCMD_AFN_A_F4_TEAM_ADDR           = 0x0A04,       // ��ѯ��Ϣ�����뽻���ն����ַ
    MCMD_AFN_A_F5_CON_IP_PORT         = 0x0A05,       // ��ѯ��Ϣ�����뽻���ն�IP��ַ�Ͷ˿�
    MCMD_AFN_A_F6_CON_CASC            = 0x0A06,       // ��ѯ��Ϣ�����뽻���ն˼���ͨ�Ų���
    MCMD_AFN_A_F7_CON_DOWN_CFG        = 0x0A07,       // ��Ϣ�����뽻���ն�������̫���˿�ͨ�Ų���

    // ��2   pn:p0/����ն˺�
    MCMD_AFN_A_F9_CON_EVENT_CFG       = 0x0A09,       // ��ѯ�¼���¼����
    MCMD_AFN_A_F10_CON_STATE_INPUT    = 0x0A0A,       // ��ѯ�豸״̬���������
    MCMD_AFN_A_F11_CON_LOGIC_ADDR     = 0x0A0B,       // �豸�߼���ַ
    MCMD_AFN_A_F12_CON_VERSION        = 0x0A0C,       // ��ѯ�豸�汾��Ϣ
    MCMD_AFN_A_F13_ELEC_MP_INFO       = 0x0A0D,       // �����õ�����������Ϣ
    MCMD_AFN_A_F14_NELC_MP_INFO       = 0x0A0E,       // �����÷ǵ�����������Ϣ
    MCMD_AFN_A_F15_SUPT_EVENT         = 0x0A0F,       // �豸֧�ֵ��¼���¼

    // ��3   pn:����ն˺�
    MCMD_AFN_A_F17_TML_UP_CFG         = 0x0A11,       // ��ѯ����ն˵�����ͨ�Ų���

    // ��4   pn:�����������
    MCMD_AFN_A_F25_ELEC_MP_CFG        = 0x0A19,       // ��ѯ�������������ò���
    MCMD_AFN_A_F26_ELEC_MP_BASE       = 0x0A1A,       // ��ѯ�����������������


    #if 0 // ԭ�����
    MCMD_AFN_A_F27_ELEC_LMIT_POWER    = 0x0A1C,       // ��ѯ�����������������ֵ����
    MCMD_AFN_A_F28_ELEC_LMIT_FACTR    = 0x0A1D,       // ��ѯ���������㹦�����طֶ���ֵ����
    //MCMD_AFN_A_F29_ELEC_FIX_HARM      = 0x0A1E,       // ��ѯ����������г��������Խ�޶�ֵ
    //MCMD_AFN_A_F30_ELEC_FLASH         = 0x0A1F,       // ��ѯ��������������Խ�޲���
    #else // ���Ժ�ڲ���
    
    MCMD_AFN_A_F27_ELEC_LMIT_POWER    = 0x0A1B,       // ��ѯ�����������������ֵ����
    MCMD_AFN_A_F28_ELEC_LMIT_FACTR    = 0x0A1C,       // ��ѯ���������㹦�����طֶ���ֵ����
    MCMD_AFN_A_F29_ELEC_FIX_HARM      = 0x0A1D,       // ��ѯ����������г��������Խ�޶�ֵ
    MCMD_AFN_A_F30_ELEC_FLASH         = 0x0A1E,       // ��ѯ��������������Խ�޲���
    #endif

    // ��5   pn:�ǵ����������
    MCMD_AFN_A_F33_NELC_MP_CFG        = 0x0A21,       // ��ѯ�ǵ������������ò���
    MCMD_AFN_A_F34_NELC_MP_PARA       = 0x0A22,       // ��ѯ�ǵ������������ݲ���
    MCMD_AFN_A_F35_NELC_MP_LMIT       = 0x0A23,       // ��ѯ�ǵ���������Խ�����ݲ���

    // ��7  pn:�����
    MCMD_AFN_A_F49_FREZ_TASK_PARA     = 0x0A31,       // ��ѯ���������������

    // ��8  pn:p0
    MCMD_AFN_A_F57_TML_CFG_INFO       = 0x0A39,       // ��ѯ�����ü���ն���Ϣ
    ///*}

    /**********************************
     * ����: ����(��ʱ�ϱ�)��������
     * AFN : 12
     *  PN : ���鶨��
     * ����: ��
     * ����: ��
    {*///
    // ��1   pn:p0
    MCMD_AFN_C_F1_FREZ_TEMP           = 0x0C01,       // ������ʱ��������Ķ�������

    // ��2   pn:�����
    MCMD_AFN_C_F9_FREZ_AUTO           = 0x0C09,       // ���󣨶�ʱ�ϱ���������������
    ///*}

    /**********************************
     * ����: ����ʵʱ����
     * AFN : 13
     *  PN : ���鶨��
     * ����: ��
     * ����: ��
    {*///
    // ��1   pn: p0/����ն˺�
    MCMD_AFN_D_F1_CLOCK              = 0x0D01,       // ����ʱ��
    MCMD_AFN_D_F2_PARA_STATE         = 0x0D02,       // ����״̬��־
    MCMD_AFN_D_F3_EVENT_1            = 0x0D03,       // ��Ҫ�¼���������ǰֵ
    MCMD_AFN_D_F4_EVENT_2            = 0x0D04,       // һ���¼���������ǰֵ
    MCMD_AFN_D_F5_EVENT_STATE        = 0x0D05,       // �¼�״̬��־
    MCMD_AFN_D_F6_POWR_TIMES         = 0x0D06,       // �ϵ����

    // ��2   pn:p0/����ն˺�
    MCMD_AFN_D_F9_STATE              = 0x0D09,       // ״̬������λ��־
    MCMD_AFN_D_F10_SWITCH            = 0x0D0A,       // ���������·���ؽ���״̬������λ��־

    // ��4   pn:p0/�����������
    MCMD_AFN_D_F25_POWR_HAVE_T       = 0x0D19,       // ���й�����
    MCMD_AFN_D_F26_POWR_NONE_T       = 0x0D1A,       // ���޹�����
    MCMD_AFN_D_F27_FACTR_T           = 0x0D1B,       // �ܹ�������
    MCMD_AFN_D_F28_FACTR_A           = 0x0D1C,       // A�๦������
    MCMD_AFN_D_F29_FACTR_B           = 0x0D1D,       // B�๦������
    MCMD_AFN_D_F30_FACTR_C           = 0x0D1E,       // C�๦������

    // ��5   pn:p0/�����������
    MCMD_AFN_D_F33_DEMAND            = 0x0D21,       // ����
    MCMD_AFN_D_F34_DEMAND_MAX        = 0x0D22,       // ���������
    MCMD_AFN_D_F35_DEMAND_TIME       = 0x0D23,       // �������������ʱ��

    // ��6   pn:�����������
    MCMD_AFN_D_F41_POWR_HAVE_A       = 0x0D29,       // A���й�����
    MCMD_AFN_D_F42_POWR_HAVE_B       = 0x0D2A,       // B���й�����
    MCMD_AFN_D_F43_POWR_HAVE_C       = 0x0D2B,       // C���й�����
    MCMD_AFN_D_F44_POWR_NONE_A       = 0x0D2C,       // A���޹�����
    MCMD_AFN_D_F45_POWR_NONE_B       = 0x0D2D,       // B���޹�����
    MCMD_AFN_D_F46_POWR_NONE_C       = 0x0D2E,       // C���޹�����

    // ��7   pn:�����������
    MCMD_AFN_D_F49_POWR_HAVE_FRTH    = 0x0D31,       // �������й��ܵ���ʾ��
    MCMD_AFN_D_F50_POWR_HAVE_BACK    = 0x0D32,       // �������й��ܵ���ʾ��
    MCMD_AFN_D_F51_POWR_NONE_FRTH    = 0x0D33,       // �������޹��ܵ���ʾ��
    MCMD_AFN_D_F52_POWR_NONE_BACK    = 0x0D34,       // �������޹��ܵ���ʾ��

    // ��8 pn:�����������
    MCMD_AFN_D_F57_VOLT_A            = 0x0D39,       // A���ѹ
    MCMD_AFN_D_F58_VOLT_B            = 0x0D3A,       // B���ѹ
    MCMD_AFN_D_F59_VOLT_C            = 0x0D3B,       // C���ѹ
    MCMD_AFN_D_F60_VANGL_A           = 0x0D3C,       // A���ѹ��λ��
    MCMD_AFN_D_F61_VANGL_B           = 0x0D3D,       // B���ѹ��λ��
    MCMD_AFN_D_F62_VANGL_C           = 0x0D3E,       // C���ѹ��λ��
    MCMD_AFN_D_F63_VOLT_UBL          = 0x0D3F,       // ��ѹ��ƽ���
    MCMD_AFN_D_F64_CIRCLE_V          = 0x0D40,       // �ܲ�

    // ��9 pn:�����������
    MCMD_AFN_D_F65_ELEC_A            = 0x0D41,       // A�����
    MCMD_AFN_D_F66_ELEC_B            = 0x0D42,       // B�����
    MCMD_AFN_D_F67_ELEC_C            = 0x0D43,       // C�����
    MCMD_AFN_D_F68_ELEC_M            = 0x0D44,       // �����ߵ���
    MCMD_AFN_D_F69_EANGL_A           = 0x0D45,       // A�������λ��
    MCMD_AFN_D_F70_EANGL_B           = 0x0D46,       // B�������λ��
    MCMD_AFN_D_F71_EANGL_C           = 0x0D47,       // C�������λ��
    MCMD_AFN_D_F72_ELEC_UBL          = 0x0D48,       // ������ƽ���

    // ��10 pn:�����������
    MCMD_AFN_D_F73_VDMAX_A           = 0x0D49,       // ��A���ѹ����ֵ
    MCMD_AFN_D_F74_VDMAX_A_TIME      = 0x0D4A,       // ��A���ѹ����ֵ����ʱ��
    MCMD_AFN_D_F75_VDMAX_B           = 0x0D4B,       // ��A���ѹ����ֵ
    MCMD_AFN_D_F76_VDMAX_B_TIME      = 0x0D4C,       // ��A���ѹ����ֵ����ʱ��
    MCMD_AFN_D_F77_VDMAX_C           = 0x0D4D,       // ��A���ѹ����ֵ
    MCMD_AFN_D_F78_VDMAX_C_TIME      = 0x0D4E,       // ��A���ѹ����ֵ����ʱ��

    // ��11 pn:�����������
    MCMD_AFN_D_F81_IDMAX_A           = 0x0D51,       // ��A���������ֵ
    MCMD_AFN_D_F82_IDMAX_A_TIME      = 0x0D52,       // ��A���������ֵ����ʱ��
    MCMD_AFN_D_F83_IDMAX_B           = 0x0D53,       // ��B���������ֵ
    MCMD_AFN_D_F84_IDMAX_B_TIME      = 0x0D54,       // ��B���������ֵ����ʱ��
    MCMD_AFN_D_F85_IDMAX_C           = 0x0D55,       // ��C���������ֵ
    MCMD_AFN_D_F86_IDMAX_C_TIME      = 0x0D56,       // ��C���������ֵ����ʱ��

    // ��12 pn:�����������
    MCMD_AFN_D_F89_TFW_HAVE          = 0x0D59,       // �ܻ����й�����  (Total Fundamental Wave)
    MCMD_AFN_D_F90_TFW_NONE          = 0x0D5A,       // �ܻ����޹�����
    MCMD_AFN_D_F91_THW_HAVE          = 0x0D5B,       // ��г���й�����  (Total Harmonic Wave)
    MCMD_AFN_D_F92_THW_NONE          = 0x0D5C,       // �ܻ����޹�����

    // ��13 pn:�����������
    MCMD_AFN_D_F97_VDPP_TIME_A       = 0x0D61,       // A���ѹԽ���������ۼ�ʱ��
    MCMD_AFN_D_F98_VDPP_TIME_B       = 0x0D62,       // B���ѹԽ���������ۼ�ʱ��
    MCMD_AFN_D_F99_VDPP_TIME_C       = 0x0D63,       // C���ѹԽ���������ۼ�ʱ��
    MCMD_AFN_D_F100_VDNN_TIME_A      = 0x0D64,       // A���ѹԽ���������ۼ�ʱ��
    MCMD_AFN_D_F101_VDNN_TIME_B      = 0x0D65,       // B���ѹԽ���������ۼ�ʱ��
    MCMD_AFN_D_F102_VDNN_TIME_C      = 0x0D66,       // C���ѹԽ���������ۼ�ʱ��

    // ��14 pn:�����������
    MCMD_AFN_D_F105_VMPP_TIME_A      = 0x0D69,       // A���ѹԽ���������ۼ�ʱ��
    MCMD_AFN_D_F106_VMPP_TIME_B      = 0x0D6A,       // B���ѹԽ���������ۼ�ʱ��
    MCMD_AFN_D_F107_VMPP_TIME_C      = 0x0D6B,       // C���ѹԽ���������ۼ�ʱ��
    MCMD_AFN_D_F108_VMNN_TIME_A      = 0x0D6C,       // A���ѹԽ���������ۼ�ʱ��
    MCMD_AFN_D_F109_VMNN_TIME_B      = 0x0D6D,       // B���ѹԽ���������ۼ�ʱ��
    MCMD_AFN_D_F110_VMNN_TIME_C      = 0x0D6E,       // C���ѹԽ���������ۼ�ʱ��

    // ��15 pn:����������� (aberrance)
    MCMD_AFN_D_F113_VABR_TOTL_A      = 0x0D71,       // A���ѹ�ܻ�����
    MCMD_AFN_D_F114_VABR_TOTL_B      = 0x0D72,       // B���ѹ�ܻ�����
    MCMD_AFN_D_F115_VABR_TOTL_C      = 0x0D73,       // C���ѹ�ܻ�����
    MCMD_AFN_D_F116_EABR_TOTL_A      = 0x0D74,       // A������ܻ�����
    MCMD_AFN_D_F117_EABR_TOTL_B      = 0x0D75,       // B������ܻ�����
    MCMD_AFN_D_F118_EABR_TOTL_C      = 0x0D76,       // C������ܻ�����

    // ��16 pn:�����������
    MCMD_AFN_D_F121_VABR_ODD_A       = 0x0D79,       // A���ѹ��λ�����
    MCMD_AFN_D_F122_VABR_EVN_A       = 0x0D7A,       // A���ѹż�λ�����
    MCMD_AFN_D_F123_VABR_ODD_B       = 0x0D7B,       // B���ѹ��λ�����
    MCMD_AFN_D_F124_VABR_EVN_B       = 0x0D7C,       // B���ѹż�λ�����
    MCMD_AFN_D_F125_VABR_ODD_C       = 0x0D7D,       // C���ѹ��λ�����
    MCMD_AFN_D_F126_VABR_EVN_C       = 0x0D7E,       // C���ѹż�λ�����

    // ��17 pn:�����������
    MCMD_AFN_D_F128_EABR_OOD_A       = 0x0D80,       // A�������λ�����
    MCMD_AFN_D_F129_EABR_EVN_A       = 0x0D81,       // A�����ż�λ�����
    MCMD_AFN_D_F130_EABR_OOD_B       = 0x0D82,       // B�������λ�����
    MCMD_AFN_D_F131_EABR_EVN_B       = 0x0D83,       // B�����ż�λ�����
    MCMD_AFN_D_F132_EABR_OOD_C       = 0x0D84,       // C�������λ�����
    MCMD_AFN_D_F133_EABR_EVN_C       = 0x0D85,       // C�����ż�λ�����

    // ��18 pn:�����������
    MCMD_AFN_D_F137_FLS_SHRT_A       = 0x0D89,       // A���ʱ����
    MCMD_AFN_D_F138_FLS_SHRT_B       = 0x0D8A,       // B���ʱ����
    MCMD_AFN_D_F139_FLS_SHRT_C       = 0x0D8B,       // C���ʱ����
    MCMD_AFN_D_F140_FLS_LONG_A       = 0x0D8C,       // A�೤ʱ����
    MCMD_AFN_D_F141_FLS_LONG_B       = 0x0D8D,       // B�೤ʱ����
    MCMD_AFN_D_F142_FLS_LONG_C       = 0x0D8E,       // C�೤ʱ����

    // ��19 pn:�����������
    MCMD_AFN_D_F145_HARM_VOLT_A      = 0x0D91,       // A��N��г����ѹ
    MCMD_AFN_D_F146_HARM_VOLT_B      = 0x0D92,       // B��N��г����ѹ
    MCMD_AFN_D_F147_HARM_VOLT_C      = 0x0D93,       // C��N��г����ѹ
    MCMD_AFN_D_F148_HARM_ELEC_A      = 0x0D94,       // A��N��г������
    MCMD_AFN_D_F149_HARM_ELEC_B      = 0x0D95,       // B��N��г������
    MCMD_AFN_D_F150_HARM_ELEC_C      = 0x0D96,       // C��N��г������

    // ��20 pn:�����������
    MCMD_AFN_D_F153_HARM_VINC_A      = 0x0D99,       // A��N��г����ѹ������
    MCMD_AFN_D_F154_HARM_VINC_B      = 0x0D9A,       // B��N��г����ѹ������
    MCMD_AFN_D_F155_HARM_VINC_C      = 0x0D9B,       // C��N��г����ѹ������
    MCMD_AFN_D_F156_HARM_EINC_A      = 0x0D9C,       // A��N��г������������
    MCMD_AFN_D_F157_HARM_EINC_B      = 0x0D9D,       // B��N��г������������
    MCMD_AFN_D_F158_HARM_EINC_C      = 0x0D9E,       // C��N��г������������

    // ��30 pn:�ǵ����������
    MCMD_AFN_D_F233_NELC_VALUE       = 0x0DE9,       // �ǵ�����
    ///*}

    /**********************************
     * ����: ���������ϱ����¼���¼
     * AFN : 0E
     *  PN : p0
     * ����: ��
     * ����: ��
    {*///
    MCMD_AFN_E_F1_EVENT_1             = 0x0E01,       // ������Ҫ�¼�
    MCMD_AFN_E_F2_EVENT_2             = 0x0E02,       // ����һ���¼�
    MCMD_AFN_E_F3_EVENT_3             = 0x0E03,       // ����ָ���¼�
    ///*}

    /**********************************
     * ����: �ļ�����
     * AFN : 0F
     *  PN : p0
     * ����: ��
     * ����: ��
    {*///
    // ��1   pn:p0/����ն˺�
    MCMD_AFN_F_F1_SOFT_DOWN           = 0x0F01,        // �������
    MCMD_AFN_F_F2_SOFT_LEFT           = 0x0F02,        // �������δ�յ����ݶ�

    // ��2   pn:p0/����ն˺�
    MCMD_AFN_F_F9_NXMD_DOWN           = 0x0F09,        // �������
    MCMD_AFN_F_F10_NXMD_LEFT          = 0x0F0A,        // �������δ�յ����ݶ�

    // ��3   pn:p0/����ն˺�
    MCMD_AFN_F_F17_REQS_DOWN          = 0x0F11,        // �������
    MCMD_AFN_F_F18_REQS_LEFT          = 0x0F12,        // �������δ�յ����ݶ�
    ///*}

    /**********************************
     * ����: ����ת��
     * AFN : 10H
     *  PN : p0
     * ����: ��
     * ����: ��
    {*///
    // ��1 Pn:P0
    MCMD_AFN_10_F1_TRANSMIT           = 0x1001,       // ͸��ת��
    ///*}

    /* ����֮�������չ������ */
    MCMD_AFN_FN_MAX
}eMcmd;
///*}

/*******************************************************
 *  �¼����Ͷ��� eMcErc
 *
{*///
typedef enum
{
    MC_ERC_UNKOWN,            // ERC0: δ֪�¼���¼����
    MC_ERC_1_RESET,           // ERC1: ��λ�¼�
    MC_ERC_2_DATA_CLEAR,      // ERC2: ָ�����������¼�
    MC_ERC_3_SOFT_CHANGE,     // ERC3: ����汾����¼�
    MC_ERC_4_PARA_CHANGE,     // ERC4: ��������¼�
    MC_ERC_5_CHECK_TIME,      // ERC5: Уʱ�¼�
    MC_ERC_6_STATE_CHANGE,    // ERC6: ״̬����λ�¼�
    MC_ERC_7_REMOTE_SWITCH,   // ERC7: ң����բ�¼�
    MC_ERC_8_POWER_ON_OFF,    // ERC8: ͣ/�ϵ��¼�
    MC_ERC_9_FACTOR_OVER,     // ERC9: �ܹ�������Խ���¼�
    MC_ERC_10_VOLT_EXCP,      // ERC10: ��ѹƫ��Խ���¼�
    MC_ERC_11_VOLT_CIRCLE,    // ERC11: ��ѹ��·�쳣�¼�
    MC_ERC_12_ELEC_CRICLE,    // ERC12: ������·�쳣�¼�
    MC_ERC_13_VOLT_OVER,      // ERC13: ��ѹԽ���¼�
    MC_ERC_14_ELEC_OVER,      // ERC14: ����Խ���¼�
    MC_ERC_15_UNBL_OVER_V,    // ERC15: ��ѹ��ƽ���Խ���¼�
    MC_ERC_16_UNBL_OVER_I,    // ERC16: ������ƽ���Խ���¼�
    MC_ERC_17_HUNBL_OVER_V,   // ERC17: г����ѹ������Խ���¼�
    MC_ERC_18_HUNBL_OVER_I,   // ERC18: г������������Խ���¼�
    MC_ERC_19_FLASH_OVER,     // ERC19: ����Խ���¼�
    MC_ERC_20_NELC_OVER,      // ERC20: �ǵ�����Խ���¼�
    MC_ERC_NUM_MAX            // �¼��������ֵ

}eMcEventRecord, eMcErc; // �¼����Ͷ���

/*******************************************************
 *  ֡�����û��� ���ݽṹת���������Ͷ���
 *
{*///
typedef enum
{
    MC_TRANS_UNKOWN,    // δ֪����
    MC_TRANS_U2F,       // �û������ݽṹ��֡���ݽṹ
    MC_TRANS_F2U,       // ֡�����ݽṹ���û������ݽṹ

}eMcTrans;              // �û�����֡�����ݽṹת������

// ת��֡�����û������ݽṹ�ĺ���ָ������
// pusLen Ϊ��װ��֡��������ֽڳ�
typedef eMcErr (*pMcFunc)(eMcTrans eTrans, void* pUser, void* pFrame, UINT16* pusLen);
///*}

/************************************************************
 *  �ڲ��ӿ�
 *
{*///

/*******************************************************************
 *  ��¼A ���ݸ�ʽ�Ķ�����ת������
 *
{*///

/*********************************************
 *  ���ݸ�ʽ01 ���ڱ�A.1
 *  ��ʽ:
 *  �ֳ�: 6
 *  +-------+------+------+------+------+------+------+------+------+
 *  |              |                       �ֽڸ�ʽ                 |
 *  + �� �� +------+------+------+------+------+------+------+------+
 *  |       |  D7  |  D6  |  D5  |  D4  |  D3  |  D2  |  D1  |  D0  |
 *  +-------+------+------+------+------+------+------+------+------+
 *  |   ��  |         BCD��ʮλ         |         BCD���λ         |
 *  +-------+------+------+------+------+------+------+------+------+
 *  |   ��  |         BCD��ʮλ         |         BCD���λ         |
 *  +-------+------+------+------+------+------+------+------+------+
 *  |   ʱ  |         BCD��ʮλ         |         BCD���λ         |
 *  +-------+------+------+------+------+------+------+------+------+
 *  |   ��  |         BCD��ʮλ         |         BCD���λ         |
 *  +-------+------+------+------+------+------+------+------+------+
 *  |����-��| ����BCD��λ        |��BCD |        ��BCD���λ        |
 *  |       |                    |��ʮλ|                           |
 *  +-------+------+------+------+------+------+------+------+------+
 *  |   ��  |         BCD��ʮλ         |         BCD���λ         |
 *  +-------+------+------+------+------+------+------+------+------+
 *  ���ڶ������£�D5 ~ D7�����ʾ 0 ~ 7��0����Ч��1-7���α�ʾ����һ��������
{*///
// �û���
typedef struct
{
    UINT8 ucYY;    // ��
    UINT8 ucMM;    // ��
    UINT8 ucWW;    // ����
    UINT8 ucDD;    // ��
    UINT8 ucHH;    // Сʱ
    UINT8 ucmm;    // ����
    UINT8 ucss;    // ��

}sMcUerClock, sMcFmt01, sMcYWMDhms;

// ��֡��
#pragma pack(1)
typedef struct
{
    UINT8  bcd_ss_0:4;  //��
    UINT8  bcd_ss_1:4;
    UINT8  bcd_mm_0:4;  // ��
    UINT8  bcd_mm_1:4;
    UINT8  bcd_HH_0:4;  // ʱ
    UINT8  bcd_HH_1:4;
    UINT8  bcd_DD_0:4;  // ��
    UINT8  bcd_DD_1:4;
    UINT8  bcd_MM_0:4;  // ��
    UINT8  bcd_MM_1:1;
    UINT8  bcd_WW_0:3;  // ����
    UINT8  bcd_YY_0:4;  // ��
    UINT8  bcd_YY_1:4;

}sMcUerClock_f, sMcFmt01_f, sMcYWMDhms_f;
#pragma pack()

// ת������
eMcErr emc_trans_YWMDhms(eMcTrans eTrans, sMcYWMDhms* psUser, sMcYWMDhms_f* psFrame);
///*}

/*********************************************
 *  ���ݸ�ʽ2 ���ڱ�A.2
 *  ��λ: ������ʱ��
 *  �ֳ�: 5
 *  ��ʽ:
 *  +------+------+------+------+------+------+------+------+------+
 *  |      |                       �ֽڸ�ʽ                        |
 *  + ���� +------+------+------+------+------+------+------+------+
 *  |      |  D7  |  D6  |  D5  |  D4  |  D3  |  D2  |  D1  |  D0  |
 *  +------+------+------+------+------+------+------+------+------+
 *  |  ��  |         BCD��ʮλ         |         BCD���λ         |
 *  +------+------+------+------+------+------+------+------+------+
 *  |  ʱ  |         BCD��ʮλ         |         BCD���λ         |
 *  +------+------+------+------+------+------+------+------+------+
 *  |  ��  |         BCD��ʮλ         |         BCD���λ         |
 *  +------+------+------+------+------+------+------+------+------+
 *  |  ��  |         BCD��ʮλ         |         BCD���λ         |
 *  +------+------+------+------+------+------+------+------+------+
 *  |  ��  |         BCD��ʮλ         |         BCD���λ         |
 *  +------+------+------+------+------+------+------+------+------+
 *
{*///
// �û���
typedef struct
{
    UINT8  ucYY;        // ��
    UINT8  ucMM;        // ��
    UINT8  ucDD;        // ��
    UINT8  ucHH;        // ʱ
    UINT8  ucmm;        // ��

}sMcFmt02, sMcYYMMDDhhmm, sMcYMDhm;

// ��֡��
#pragma pack(1)
typedef struct
{
    UINT8  bcd_mm_0:4;  // ��
    UINT8  bcd_mm_1:4;
    UINT8  bcd_hh_0:4;  // ʱ
    UINT8  bcd_hh_1:4;
    UINT8  bcd_DD_0:4;  // ��
    UINT8  bcd_DD_1:4;
    UINT8  bcd_MM_0:4;  // ��
    UINT8  bcd_MM_1:4;
    UINT8  bcd_YY_0:4;  // ��
    UINT8  bcd_YY_1:4;

}sMcFmt02_f,sMcYYMMDDhhmm_f, sMcYMDhm_f;
#pragma pack()

// ת������
eMcErr emc_trans_YYMMDDhhmm(eMcTrans eTrans, sMcYMDhm* psUser, sMcYMDhm_f* psFrame);
///*}

/*********************************************
 *  ���ݸ�ʽ3 ���ڱ�A.3
 *  ��λ: ����ʱ��
 *  �ֳ�: 4
 *  ��ʽ:
 *  +------+------+------+------+------+------+------+------+------+
 *  |      |                       �ֽڸ�ʽ                        |
 *  + ���� +------+------+------+------+------+------+------+------+
 *  |      |  D7  |  D6  |  D5  |  D4  |  D3  |  D2  |  D1  |  D0  |
 *  +------+------+------+------+------+------+------+------+------+
 *  |  ��  |         BCD��ʮλ         |         BCD���λ         |
 *  +------+------+------+------+------+------+------+------+------+
 *  |  ��  |         BCD��ʮλ         |         BCD���λ         |
 *  +------+------+------+------+------+------+------+------+------+
 *  |  ʱ  |         BCD��ʮλ         |         BCD���λ         |
 *  +------+------+------+------+------+------+------+------+------+
 *  |  ��  |         BCD��ʮλ         |         BCD���λ         |
 *  +------+------+------+------+------+------+------+------+------+
 *
{*///
// �û���
typedef struct
{
    UINT8  ucDD;        // ��
    UINT8  ucHH;        // ʱ
    UINT8  ucmm;        // ��
    UINT8  ucss;        // ��
}sMcFmt03, sMcDDHHmmss;

// ֡��
typedef struct
{
    UINT8  bcd_ss_0:4;  // ��
    UINT8  bcd_ss_1:4;
    UINT8  bcd_mm_0:4;  // ��
    UINT8  bcd_mm_1:4;
    UINT8  bcd_HH_0:4;  // ʱ
    UINT8  bcd_HH_1:4;
    UINT8  bcd_DD_0:4;  // ��
    UINT8  bcd_DD_1:4;

}sMcFmt03_f, sMcDDHHmmss_f;

// ת������
eMcErr emc_trans_DDHHmmss(eMcTrans eTrans, sMcDDHHmmss* psDDHHmmss_u, sMcDDHHmmss_f* psDDHHmmss_f);
///*}

/*********************************************
 *  ���ݸ�ʽ4 ���ڱ�A.4
 *  ��ʽ: (+)XXXXXX.XXXX
 *  �ֳ�: 5
 *  ��ʽ:
 *  +-------+------+------+------+------+------+------+------+------+
 *  |       |                       �ֽڸ�ʽ                        |
 *  + ����  +------+------+------+------+------+------+------+------+
 *  |       |  D7  |  D6  |  D5  |  D4  |  D3  |  D2  |  D1  |  D0  |
 *  +-------+------+------+------+------+------+------+------+------+
 *  | BYTE1 |        BCD��ǧ��λ        |        BCD�����λ        |
 *  +-------+------+------+------+------+------+------+------+------+
 *  | BYTE2 |        BCD��ʮ��λ        |        BCD��ٷ�λ        |
 *  +-------+------+------+------+------+------+------+------+------+
 *  | BYTE3 |         BCD��ʮλ         |         BCD���λ         |
 *  +-------+------+------+------+------+------+------+------+------+
 *  | BYTE4 |         BCD��ǧλ         |         BCD���λ         |
 *  +-------+------+------+------+------+------+------+------+------+
 *  | BYTE5 |        BCD��ʮ��λ        |          BCD����λ        |
 *  +-------+------+------+------+------+------+------+------+------+
{*///
// �û���
// double dXXXXXX.XXXX

// ֡��
typedef struct
{
    UINT8 BCD_0_4:4;  // BCD �ٷ�λ
    UINT8 BCD_0_3:4;  // BCD ʮ��λ
    UINT8 BCD_0_2:4;  // BCD �ٷ�λ
    UINT8 BCD_0_1:4;  // BCD ʮ��λ
    UINT8 BCD_0  :4;  // BCD ��λ
    UINT8 BCD_1  :4;  // BCD ʮλ
    UINT8 BCD_2  :4;  // BCD ��λ
    UINT8 BCD_3  :4;  // BCD ǧλ
    UINT8 BCD_4  :4;  // BCD ��λ
    UINT8 BCD_5  :4;  // BCD ʮ��λ

}sMcFmt04, sMcFmt04_f,sMcFmt_XXXXXX_XXXX;

// ת������
eMcErr emc_trans_XXXXXX_XXXX(eMcTrans eTrans, double* psUser, sMcFmt_XXXXXX_XXXX* psFrame);
///*}

/*********************************************
 *  ���ݸ�ʽ5 ���ڱ�A.5
 *  ��ʽ: (+)XXXXXX.XX
 *  �ֳ�: 4
 *  +-------+------+------+------+------+------+------+------+------+
 *  |       |                       �ֽڸ�ʽ                        |
 *  + ����  +------+------+------+------+------+------+------+------+
 *  |       |  D7  |  D6  |  D5  |  D4  |  D3  |  D2  |  D1  |  D0  |
 *  +-------+------+------+------+------+------+------+------+------+
 *  | BYTE1 |        BCD��ʮ��λ        |        BCD��ٷ�λ        |
 *  +-------+------+------+------+------+------+------+------+------+
 *  | BYTE2 |         BCD��ʮλ         |         BCD���λ         |
 *  +-------+------+------+------+------+------+------+------+------+
 *  | BYTE3 |         BCD��ǧλ         |         BCD���λ         |
 *  +-------+------+------+------+------+------+------+------+------+
 *  | BYTE4 |        BCD��ʮ��λ        |         BCD����λ         |
 *  +-------+------+------+------+------+------+------+------+------+
{*///
// �û���
// double dXXXXXX.XX

// ֡��
typedef struct
{
    UINT8 BCD_0_2:4;  // BCD �ٷ�λ
    UINT8 BCD_0_1:4;  // BCD ʮ��λ
    UINT8 BCD_0  :4;  // BCD ��λ
    UINT8 BCD_1  :4;  // BCD ʮλ
    UINT8 BCD_2  :4;  // BCD ��λ
    UINT8 BCD_3  :4;  // BCD ǧλ
    UINT8 BCD_4  :4;  // BCD ��λ
    UINT8 BCD_5  :4;  // BCD ʮ��λ

}sMcFmt05, sMcFmt05_f, sMcFmt_XXXXXX_XX;

// ת������
eMcErr emc_trans_XXXXXX_XX(eMcTrans eTrans, double* psUser, sMcFmt_XXXXXX_XX* psFrame);
///*}

/*********************************************
 *  ���ݸ�ʽ6 ���ڱ�A.6
 *  ��ʽ: (+/-)XX.XXXX
 *  �ֳ�: 3
 *  +-------+------+------+------+------+------+------+------+------+
 *  |       |                       �ֽڸ�ʽ                        |
 *  + ����  +------+------+------+------+------+------+------+------+
 *  |       |  D7  |  D6  |  D5  |  D4  |  D3  |  D2  |  D1  |  D0  |
 *  +-------+------+------+------+------+------+------+------+------+
 *  | BYTE1 |        BCD��ǧ��λ        |        BCD�����λ        |
 *  +-------+------+------+------+------+------+------+------+------+
 *  | BYTE2 |        BCD��ʮ��λ        |        BCD��ٷ�λ        |
 *  +-------+------+------+------+------+------+------+------+------+
 *  | BYTE3 |  S   |     BCD��ʮλ      |         BCD���λ         |
 *  +-------+------+------+------+------+------+------+------+------+
{*///
// �û���
// float fXX.XXXX

// ֡��
typedef struct
{
    UINT8 BCD_0_4:4;  // BCD ���λ
    UINT8 BCD_0_3:4;  // BCD ǧ��λ
    UINT8 BCD_0_2:4;  // BCD �ٷ�λ
    UINT8 BCD_0_1:4;  // BCD ʮ��λ
    UINT8 BCD_0  :4;  // BCD ��λ
    UINT8 BCD_1  :3;  // BCD ʮλ
    UINT8 S      :1;  // ����λ
}sMcFmt06_f, sMcFmt_sXX_XXXX;

// 10 exp�η� exp < 10
int  nmc_pow(UINT8 exp);

// ת������
eMcErr emc_trans_sXX_XXXX(eMcTrans eTrans, float* psUser, sMcFmt06_f* psFrame);
///*}

/*********************************************
 *  ���ݸ�ʽ07 ���ڱ�A.7
 *  ��ʽ: (+/-)XXX.X
 *  �ֳ�: 2
 *  +-------+------+------+------+------+------+------+------+------+
 *  |       |                       �ֽڸ�ʽ                        |
 *  + �� �� +------+------+------+------+------+------+------+------+
 *  |       |  D7  |  D6  |  D5  |  D4  |  D3  |  D2  |  D1  |  D0  |
 *  +-------+------+------+------+------+------+------+------+------+
 *  | BYTE1 |        BCD�����λ        |        BCD��ʮ��λ        |
 *  +-------+------+------+------+------+------+------+------+------+
 *  | BYTE2 |  S   |     BCD���λ      |         BCD��ʮλ         |
 *  +-------+------+------+------+------+------+------+------+------+
{*///
// �û���
// float fsXXX.X

// ֡��
typedef struct
{
    UINT8 BCD_0_1:4;  // BCD ʮ��λ
    UINT8 BCD_0  :4; // BCD ��λ
    UINT8 BCD_1  :4; // BCD ʮλ
    UINT8 BCD_2  :3; // BCD ��λ
    UINT8 S      :1; // BCD ����λ
}sMcFmt07, sMcFmt07_f, sMcFmt_sXXX_X;

// ת������
eMcErr emc_trans_sXXX_X(eMcTrans eTrans, float* psUser, sMcFmt07_f* psFrame);
///*}

/*********************************************
 *  ���ݸ�ʽ08 ���ڱ�A.8
 *  ��ʽ: (+)XXX.X
 *  �ֳ�: 2
 *  +-------+------+------+------+------+------+------+------+------+
 *  |       |                       �ֽڸ�ʽ                        |
 *  + �� �� +------+------+------+------+------+------+------+------+
 *  |       |  D7  |  D6  |  D5  |  D4  |  D3  |  D2  |  D1  |  D0  |
 *  +-------+------+------+------+------+------+------+------+------+
 *  | BYTE1 |        BCD�����λ        |        BCD��ʮ��λ        |
 *  +-------+------+------+------+------+------+------+------+------+
 *  | BYTE2 |         BCD���λ         |         BCD��ʮλ         |
 *  +-------+------+------+------+------+------+------+------+------+
{*///
// �û���
// float fXXX.X

// ֡��
typedef struct
{
    UINT8 BCD_0_1:4;  // BCD ʮ��λ
    UINT8 BCD_0  :4;  // BCD ��λ
    UINT8 BCD_1  :4;  // BCD ʮλ
    UINT8 BCD_2  :4;  // BCD ��λ
}sMcFmt08, sMcFmt08_f, sMcFmt_XXX_X;

// ת������
eMcErr emc_trans_XXX_X(eMcTrans eTrans, float* psUser, sMcFmt_XXX_X* psFrame);
///*}

/*********************************************
 *  ���ݸ�ʽ09 ���ڱ�A.9
 *  ��ʽ: (+/-)XXX.XXX
 *  �ֳ�: 3
 *  +-------+------+------+------+------+------+------+------+------+
 *  |       |                       �ֽڸ�ʽ                        |
 *  + ����  +------+------+------+------+------+------+------+------+
 *  |       |  D7  |  D6  |  D5  |  D4  |  D3  |  D2  |  D1  |  D0  |
 *  +-------+------+------+------+------+------+------+------+------+
 *  | BYTE1 |        BCD��ٷ�λ        |        BCD��ǧ��λ        |
 *  +-------+------+------+------+------+------+------+------+------+
 *  | BYTE2 |         BCD���λ         |        BCD��ʮ��λ        |
 *  +-------+------+------+------+------+------+------+------+------+
 *  | BYTE3 |  S   |     BCD���λ      |         BCD��ʮλ         |
 *  +-------+------+------+------+------+------+------+------+------+
 *
{*///
// �û���
// float sXXX.XXX    (+/-)XXX.XXX

// ֡��
typedef struct
{
    UINT8 BCD_0_3:4;  // BCD ǧ��λ
    UINT8 BCD_0_2:4;  // BCD �ٷ�λ
    UINT8 BCD_0_1:4;  // BCD ʮ��λ
    UINT8 BCD_0  :4;  // BCD ��λ
    UINT8 BCD_1  :4;  // BCD ʮλ
    UINT8 BCD_2  :3;  // BCD ��λ
    UINT8 S      :1;  // ����λ

}sMcFmt09,sMcFmt09_f,sMcFmt_sXXX_XXX;

// ת������
eMcErr emc_trans_sXXX_XXX(eMcTrans eTrans, float* psUser, sMcFmt_sXXX_XXX* psFrame);
///*}

/*********************************************
 *  ���ݸ�ʽ10 ���ڱ�A.10 ��ʽ�б�
 *  ��ʽ: (+)XX.XX
 *  �ֳ�: 2
 *  +-------+------+------+------+------+------+------+------+------+
 *  |       |                       �ֽڸ�ʽ                        |
 *  + �� �� +------+------+------+------+------+------+------+------+
 *  |       |  D7  |  D6  |  D5  |  D4  |  D3  |  D2  |  D1  |  D0  |
 *  +-------+------+------+------+------+------+------+------+------+
 *  | BYTE1 |        BCD��ʮ��λ        |        BCD��ٷ�λ        |
 *  +-------+------+------+------+------+------+------+------+------+
 *  | BYTE2 |         BCD��ʮλ         |         BCD���λ         |
 *  +-------+------+------+------+------+------+------+------+------+
{*///
// �û���
// float fXX.XX

// ֡��
typedef struct
{
    UINT8 BCD_0_2:4;  // BCD �ٷ�λ
    UINT8 BCD_0_1:4;  // BCD ʮ��λ
    UINT8 BCD_0  :4;  // BCD ��λ
    UINT8 BCD_1  :4;  // BCD ʮλ
}sMcFmt10_f, sMcFmt_XX_XX;

// ת������
eMcErr emc_trans_XX_XX(eMcTrans eTrans, float* psUser, sMcFmt10_f* psFrame);
///*}

/*********************************************
 *  ���ݸ�ʽ11 ���ڱ�A.11
 *  ��ʽ: (+/-)XXXXXXX
 *  �ֳ�: 4
 *  +-------+------+------+------+------+------+------+------+------+
 *  |       |                       �ֽڸ�ʽ                        |
 *  + �� �� +------+------+------+------+------+------+------+------+
 *  |       |  D7  |  D6  |  D5  |  D4  |  D3  |  D2  |  D1  |  D0  |
 *  +-------+------+------+------+------+------+------+------+------+
 *  | BYTE1 |         BCD��ʮλ         |         BCD���λ         |
 *  +-------+------+------+------+------+------+------+------+------+
 *  | BYTE2 |         BCD��ǧλ         |         BCD���λ         |
 *  +-------+------+------+------+------+------+------+------+------+
 *  | BYTE3 |        BCD��ʮ��λ        |         BCD����λ         |
 *  +-------+------+------+------+------+------+------+------+------+
 *  | BYTE4 |  G3  |  G2  |  G1  |  S   |         BCD�����λ       |
 *  +-------+------+------+------+------+------+------+------+------+
 *  
 *  +-------+-------+-------+----------+
 *  |   G3  |  G2   |  G1   |   ����   |
 *  +-------+-------+-------+----------+
 *  |   0   |   0   |   0   |   10(4)  |
 *  +-------+-------+-------+----------+
 *  |   0   |   0   |   1   |   10(3)  |
 *  +-------+-------+-------+----------+
 *  |   0   |   1   |   0   |   10(2)  |
 *  +-------+-------+-------+----------+
 *  |   0   |   1   |   1   |   10(1)  |
 *  +-------+-------+-------+----------+
 *  |   1   |   0   |   0   |   10(0)  |
 *  +-------+-------+-------+----------+
 *  |   1   |   0   |   1   |   10(-1) |
 *  +-------+-------+-------+----------+
 *  |   1   |   1   |   0   |   10(-2) |
 *  +-------+-------+-------+----------+
 *  |   1   |   1   |   1   |   10(-3) |
 *  +-------+-------+-------+----------+
 *
 *  S ����λ:S = 0 ���� S = 1 ��ʾ����
 *
{*///
// �û���
//double dValue
#define MC_SX7_MIN     (-99999990000.0)
#define MC_SX7_MAX     (99999990000.0)

typedef enum
{
    MC_PREC_UNKOWN,
    MC_PREC_P4,  // ��Χ 0, (+/-)10000~99999990000
    MC_PREC_P3,  // ��Χ 0, (+/-)1000~9999999000
    MC_PREC_P2,  // ��Χ 0, (+/-)100~999999900
    MC_PREC_P1,  // ��Χ 0, (+/-)10~99999990
    MC_PREC_P0,  // ��Χ 0, (+/-)1~9999999
    MC_PREC_N1,  // ��Χ 0, (+/-)0.1~999999.9
    MC_PREC_N2,  // ��Χ 0, (+/-)0.01~99999.99
    MC_PREC_N3,  // ��Χ 0, (+/-)0.001~9999.999

}eMcPrecise;            // ����

typedef struct
{
    eMcPrecise  ePrec;
    double      dValue;   
}sMcFmt11, sMcDouble; 

// ֡��
#pragma pack(1)
typedef struct
{
    UINT8 BCD_0  :4; // BCD ��λ
    UINT8 BCD_1  :4; // BCD ʮλ
    UINT8 BCD_2  :4; // BCD ��λ
    UINT8 BCD_3  :4; // BCD ǧλ
    UINT8 BCD_4  :4; // BCD ��λ
    UINT8 BCD_5  :4; // BCD ʮ��λ
    UINT8 BCD_6  :4; // BCD ����λ
    UINT8 SG123  :4;
    /*
    UINT8 S      :1; // ����λ 0 Ϊ�� 1Ϊ��
    UINT8 G1     :1; // 
    UINT8 G2     :1; // 
    UINT8 G3     :1; // 
    */
}sMcFmt11_f, sMcFmt_sX7_f;
#pragma pack()

// ת������
eMcErr emc_trans_sX7(eMcTrans eTrans, void* psUser, void* psFrame);
///*}
///*}

/******************************************************************************
 *  ��������:float���͵�
 *  ����˵��:
 *  �������ڻ�����ָ����ʽ��ʾ���ֽ�Ϊ��������β����ָ������ָ���Ĳ��֡�
 *  �����ǵ����Ȼ���˫�����ڴ洢�ж���Ϊ�������֣�
 1.����λ(Sign) : 0��������1����Ϊ��
 2.ָ��λ��Exponent��:���ڴ洢��ѧ�������е�ָ�����ݣ����Ҳ�����λ�洢
 3.β�����֣�Mantissa����β������
{*///
typedef union
{
    float v;
    struct
    {
        unsigned mantissa1 : 23;
        unsigned exponent  : 8;
        unsigned sign      : 1;
    }s;

}uMcFloatFmt;

int    nmc_get_float_sign(float fVal);              // ȡ��һ��flaot�ķ���λ  sign = -1 / +1
void   vmc_set_float_sign(float *pfVal, int sign);  // ����һ���������ķ���λ sign = -1 / +1
///*}

/******************************************************************************
 * ��������: double ���͵ĺϳ����ϳ�
 * ����˵��:
 * �������ڻ�����ָ����ʽ��ʾ���ֽ�Ϊ��������β����ָ������ָ���Ĳ��֡�
 * �����ǵ����Ȼ���˫�����ڴ洢�ж���Ϊ�������֣�
 *   1.����λ(Sign) : 0��������1����Ϊ��
 *   2.ָ��λ��Exponent��:���ڴ洢��ѧ�������е�ָ�����ݣ����Ҳ�����λ�洢
 *   3.β�����֣�Mantissa����β������
 *
{*///
typedef union
{
    double v;
    struct
    {
        unsigned mantissa2 : 32;
        unsigned mantissa1 : 20;
        unsigned exponent  : 11;
        unsigned sign      :  1;
    } s;

}uMcDoubleFmt;

int    nmc_get_double_sign(double dVal);              // ȡ��һ��double�ķ���λ sign = -1 / +1
void   vmc_set_double_sign(double *pdVal, int sign);  // ����һ���������ķ���λ sign = -1 / +1
///*}
///*}

/*********************************************
 *  BCD ת������
 *
 *
{*///
UINT8 ucmc_get_bcd_0(UINT8 ucData);        // ��ø�����BCD��λ
UINT8 ucmc_get_bcd_1(UINT8 ucData);        // ��ø�����BCD��λ
///*}

/***************************************************************************
 * BCD �� �ַ�����ת������
 * len ����Ϊż��
 *
{*///
eMcErr emc_str_to_bcd(const UINT8* pstr, UINT8* pbcd, INT32 len);
eMcErr emc_bcd_to_str(const UINT8* pbcd, UINT8* pstr, INT32 len);
///*}

/*******************************************************
 *  ��������Ϣ���ݱ�ӳ�亯��
 *
{*///
typedef enum
{
    MC_ROLE_UNKOWN,    // δ֪���
    MC_ROLE_MASTER,    // ��վ
    MC_ROLE_CONTOR,    // ������ �� �ն�
    
}eMcRole;              // Э��Ӧ��ģ������
 
typedef enum
{
    MC_DIR_UNKOWN,     // δ֪���ķ���
    MC_DIR_M2S,        // ��վ��������  ����
    MC_DIR_S2M,        // ����������վ  ����

}eMcDir;               // ���ĵķ��ͷ���

typedef enum
{
    MC_PN_UNKOWN,      // δ֪PN����
    MC_PN_P0,          // P0 ������PN ����������
    MC_PN_MP,          // �������(measured point)
    MC_PN_TK,          // �����  (task number)
    MC_PN_TM,          // �ն˺�

}eMcPn;                // Pn����

typedef struct
{
    eMcmd    eCmd;     // �������ʶ
    eMcDir   eDir;     // �ñ��Ĵ��ڵķ�������
    eMcPn    ePn;      // Pn����
    pMcFunc  pFunc;    // �������Ӧ���û����������װ�����ݽṹת������
    char*    pName;    // ��Э����Ϣ�����ĺ���

}sMcmdInfor;
///*}

// ͨ���������ͺͱ��ķ����ø������Ӧ�������Ϣ
eMcErr eMcGetCmdInfor(eMcmd eCmd, eMcDir eDir, sMcmdInfor* psInfor);
///*}

/************************************************************
 *  ��ַ��A�ṹ
 *
{*///
// �û���ṹ
#define MC_REGN_LEN   (6)      // ����������A1 ���� (�û���)
#define MC_A1_LEN     (3)      // ����������A1 ���� (��֡��)
#define MC_A_LEN      (8)      // ��ַ�� ֡�೤��

typedef struct
{
    UINT8  acRegionCode[MC_REGN_LEN];   // ����������A1 �籱�� 110000, ���������밴GB 2260-2007�Ĺ涨ִ��
    UINT32 ulConAddress;                // ��Ϣ�����뽻���ն˵�ַA2 A2 ��Χ(1~4294967295)
    BOOL   bTeam;                       // Ϊtrue ��ʾulConAddress Ϊ���ַ, Ϊfalse ��ʾulConAddress��һ��ַ
    UINT8  ucMstAddress;                // ��վ��ַ�����ַ��־A3, ��Χ(0~127)

}sMcA, sMcAddress;

// ��֡��ṹ
#pragma pack(1)
typedef struct
{
    UINT8  acRegionCode[MC_A1_LEN];     // ����������A1           (BCD)  ���ֽ���ǰ  ���ֽ��ں�
    UINT32 ulConAddress;                // ��Ϣ�����뽻���ն˵�ַA2 A2 ��Χ(1~4294967295)
    //UINT8  ucTeam:1;                  // Ϊ1��ʾ usTAddress Ϊ���ַ,A2 == 0xFFFF���㲥��ַ, Ϊ 0 ��ʾ����ַ
    UINT8  ucMstAddress;                // ��վ��ַ�����ַ��־A3 (BIN)  ��ò�Ҫ��λ��

}sMcA_f, sMcAddress_f; // ֡��ַ��ʽ����
#pragma pack()

// ת������
eMcErr emc_trans_address(eMcTrans eTrans, sMcAddress *psAddr_u, sMcAddress_f *psAddr_f);
///*}

/************************************************************
 *  ������C �ṹ��ת������
 *
 *  ��֡��Ϊ2�ֽ�
 *  +------+------+------+------+------+------+------+------+------+------+------+------+------+------+------+------+
 *  | D15  | D14  | D13  | D12  | D11  | D10  |  D9  |  D8  |  D7  |  D6  |  D5  |  D4  |  D3  |  D2  |  D1  |  D0  |
 *  +------+------+------+------+------+------+------+------+------+------+------+------+------+------+------+------+
 *  | DIR  | PRM  | ���� |            ����֡���PSEQ        |      ����֡���PSEQ       |          ֡������         |
 *  +------+------+------+------+------+------+------+------+------+------+------+------+------+------+------+------+
 *
 *
 * DIR ���䷽��λ   DIR = 0 ��ʾ��֡����������(��)վ����Ϣ�����뽻���ն˷��������б���
 *                  DIR = 1 ��ʾ��֡����������Ϣ�����뽻���ն�����(��)վ���������б���
 *
 * PRM ������־λ   PRM = 0 ��ʾ��֡�������ԴӶ�����Ӧ��վ���Ӷ�վ����Ӧվ��������վ���䱨��
 *                  PRM = 1 ��ʾ��֡������������վ������վ��Ӷ�վ���䱨��
 *
 *  ����֡���PSEQ
 *      (1)����֡���PSEQ�ñ����ʾ0~31����������Ͷ�Ӧ����֡���Լ���ֹ��Ϣ����Ķ�ʧ���ظ���
 *      (2)ÿһ������վ�ʹӶ�վ֮�����1�������ļ����������ڼ�¼��ǰPSEQ������վ��ͬһ
 *         �Ӷ�վ�����µĴ������ʱ��PSEQ+1������ʱδ�յ��Ӷ�վ�ı��ģ�
 *         ����ճ��ֲ��������վ���ı�PSEQ���ظ�ԭ���Ĵ������
 *
 *  ��Ӧ֡���RSEQ
 *      (1)��Ӧ֡���RSEQ��PRM=0ʱ�����Ӷ�֡����Ч���ñ����ʾ0~15�����ڶ���Ӷ�֡��Ӧһ������֡�Ĵ���
 *      (2)ÿһ������վ�ʹӶ�վ֮�����1�������ļ����������ڼ�¼��ǰRSEQ����ֻ��һ֡�Ӷ�֡��Ӧ����֡�ģ�RSEQ=0��
 *         ������n��n��16��֡��Ӧ�ģ�RSEQ��n-1��ݼ�������ÿ����һ֡��1��ֱ�����һ֡RSEQ=0
 *         �Ӷ�վ�����µĴ������ʱ��PSEQ+1������ʱδ�յ��Ӷ�վ�ı�
 *
 *  ֡�����룬�̶�֡�Ϳɱ�֡��֡�����붨�岻ͬ
 *
{*///

typedef enum
{
    MC_PRM_UNKWON,                 // δ֪����
    MC_PRM_A2P,                    // ��֡����������վ
    MC_PRM_P2A,                    // ��֡�����ڴӶ�վ

}eMcPRM;                           // ��������PRM�ֶ�����

// ���ĳ����ĳ����õ�PRM����
eMcPRM emc_get_prm(eMcDir eDir, eMcAFN eAfn, BOOL bAuto);

typedef enum
{
    // �̶�֡
    // PRM 0
    MC_FCD_LINK_OK      = 0,       // ȷ��

    // PRM 1
    MC_FCD_LOG_IN       = 1,       // ������·����¼ϵͳ
    MC_FCD_LOG_OUT      = 2,       // �����·���˳�ϵͳ
    MC_FCD_HEART_BEAT   = 3,       // ������·����������


    // �ɱ�֡
    // PRM 0
    MC_FCD_OK           = 0,       // ��·�û�ȷ��
    MC_FCD_ANSWER       = 1,       // ���û�������Ӧ����

    // PRM 1
    MC_FCD_NOTI         = 0,       // ���� �M�޻ش�
    MC_FCD_CONF         = 1,       // ���� �Mȷ��
    MC_FCD_ASK          = 2,       // ���� �M��Ӧ

    MC_FCD_MAX,

}eMcFcode;       // ����������

#define MC_C_LEN       (2)         // ������C��֡���ֳ�

#define MC_PSEQ_MIN    (0)         // PSEQ ��Сֵ
#define MC_PSEQ_MAX    (31)        // PSEQ ���ֵ

#define MC_RSEQ_MIN    (0)         // PSEQ ��Сֵ
#define MC_RSEQ_MAX    (15)        // PSEQ ���ֵ

// �û���
typedef struct
{
    eMcDir     eDir;               // ������
    eMcPRM     ePRM;               // ��־�ñ�������������վ ���ǴӶ�վ
    UINT8      ucPSEQ;             // ����֡��� PSEQ
    UINT8      ucRSEQ;             // ��Ӧ֡��� RSEQ
    eMcFcode   eFcode;             // ֡������

}sMctrl;

// ֡��
// UINT16 usMcCtrl;
// ת������
eMcErr emc_trans_ctrl(eMcTrans eTrans, sMctrl* puCtrl, UINT16* pfCtrl);

// ��� eMcFcode ֡���Ӧ�Ĺ�����
eMcErr emc_get_fcode(eMcmd eCmd, eMcDir eDir, eMcPRM ePRM, eMcFcode * peFcode);


// ��װ����
eMcErr emc_get_ctrl(eMcAFN eAFN, eMcDir eDir, eMcPRM ePRM, sMctrl *psCtrl);
///*}

/************************************************************
 *  Ӧ�ÿ�����AC �ṹ��ת������
 *
 *  ��֡��Ϊ1�ֽ�
 *  +------+------+------+------+------+------+------+------+
 *  |  D7  |  D6  |  D5  |  D4  |  D3  |  D2  |  D1  |  D0  |
 *  +------+------+------+------+------+------+------+------+
 *  |  Tpv |  ACD |  --  |          Ӧ�ù����� AFN          |
 *  +------+------+------+------+------+------+------+------+
 *
 *
 * Tpv ʱ���ǩ��Чλ Tpv
 *     TpV=0����ʾ�ڸ�����Ϣ����[��]ʱ���ǩ Tp
 *     TpV=1����ʾ�ڸ�����Ϣ����[��]ʱ���ǩ Tp
 *
 * ACD ��ʾ����λ
 *     ACD=1����ʾ����Ҫ�¼����ݵȴ����ʣ��Ҹ�����Ϣ������ EC
 *     ACD=0����ʾ����Ҫ�¼����ݵȴ�����
 *
 * AFN Ӧ�ù�����
 *     0   ȷ�ϨM����
 *     1   ��λ
 *     4   ���ò���
 *     5   ��������
 *     6   �����֤����ԿЭ��
 *     8   ���󱻼�����Ϣ�����뽻���ն������ϱ�
 *     10  ��ѯ����
 *     12  ���󣨶�ʱ�ϱ�����������
 *     13  ����ʵʱ����
 *     14  ���������ϱ����¼���¼
 *     15  �ļ�����
 *     16  ����ת��
 *
{*///
// �û���ṹ
typedef struct
{
    BOOL    bTp;    // �Ƿ���Tp
    BOOL    bEc;    // �Ƿ���Ec
    eMcAFN  eAfn;   // Ӧ�ù�����

}sMcAc;             // Ӧ�ÿ�����AC

// ��װ��ṹ
// ucAc;

// ת������
eMcErr emc_trans_ac(eMcTrans eTrans, sMcAc* puAc, UINT8* pfAc);
///*}

/************************************************************
 *  ���ݱ�ʶ��Ԫ
 *  ÿ�����ݱ�ʶ��Ԫ����Ϣ�������ʽ��֯��
 *  ÿ�����ݱ�ʶ��Ԫ�������(8)��Fn ��������(8)��Pn
 *
 * -----
 * DADT ֡��ṹ
 * ��Ϣ�� | DA | DA1 | D7 D6 D5 D4 D3 D2 D1 D0
 *        |    | DA2 | D7 D6 D5 D4 D3 D2 D1 D0
 * ��Ϣ�� | DT | DT1 | D7 D6 D5 D4 D3 D2 D1 D0
 *        |    | DT2 | D7 D6 D5 D4 D3 D2 D1 D0
 *
 * ---
 * ��Ϣ��DA����Ϣ��ԪDA1����Ϣ����DA2�����ֽڹ���
 * DA1 ��λ��ʾĳһ��Ϣ�����1��8����Ϣ��
 * DA2 ���ö����Ʊ��뷽ʽ��ʾ��Ϣ����
 * DA1��DA2��ͬ������Ϣ���ʶpn��n = 1��2040��
 * ��Ϣ���ʶpn��Ӧ�ڲ�ͬ��Ϣ���ʶFn���������¸��ֺ���
 * ������š��ܼ���š������ִΡ�ֱ��ģ�����˿ںš������
 *
 * ��Ϣ����DA2 | ��Ϣ��ԪDA1
 *       D7~D0 | D7    D6    D5    D4    D3    D2    D1    D0
 *           1 | p8    p7    p6    P5    p4    p3    p2    p1
 *           2 | p16   p15   p14   p13   p12   p11   p10   p9
 *           3 | p24   p23   p22   p21   p20   p19   p18   p17
 *          .. | ...   ...   ...   ...   ...   ...   ...   ...
 *          255| P2040 P2039 P2038 P2037 P2036 P2035 P2034 P2033
 *
 * ---
 * ��Ϣ��DT����Ϣ��ԪDT1����Ϣ����DT2�����ֽڹ���
 * DT1 ��λ��ʾĳһ��Ϣ�����1��8����Ϣ����
 * DT2 ���ö����Ʊ��뷽ʽ��ʾ��Ϣ����
 * DT1 DT2 ��ͬ������Ϣ���ʶFn��n = 1��248��
 *
 * ��Ϣ����DT2 | ��Ϣ��ԪD T1
 *       D7~D0 | D7   D6   D5   D4   D3   D2   D1   D0
 *           0 | F8   F7   F6   F5   F4   F3   F2   F1
 *           1 | F16  F15  F14  F13  F12  F11  F10  F9
 *           2 | F24  F23  F22  F21  F20  F19  F18  F17
 *          .. | ...  ...  ...  ...  ...  ...  ...  ...
 *          30 | F248 F247 F246 F245 F244 F243 F242 F241
 *
{*///

// �û���ṹ
typedef struct
{

    UINT16  usPn[MC_PN_INDEX_MAX];      // Pn (0 ~ 2040)
                                        // MC_PN_MAX  ���ֵ
                                        // MC_PN_MIN  ��Сֵ
                                        // MC_PN_NONE ��Чֵ

    UINT8   ucFn[MC_FN_INDEX_MAX];      // Fn (1 ~ 248)
                                        // MC_FN_MAX  ���ֵ
                                        // MC_FN_MIN  ��Сֵ
                                        // MC_FN_NONE ��Чֵ
}sMcPnFn;

// ֡��ṹ
typedef struct
{
    UINT8       ucDA1;         // ��Ϣ��Ԫ
    UINT8       ucDA2;         // ��Ϣ����
    UINT8       ucDT1;         // ��Ϣ��Ԫ
    UINT8       ucDT2;         // ��Ϣ����
}sMcDaDt;

// ת������
eMcErr emc_pnfn_to_dadt(sMcPnFn* psPnFn, sMcDaDt* psDaDt);
eMcErr emc_dadt_to_pnfn(sMcDaDt* psDaDt, sMcPnFn* psPnFn);

typedef struct
{
    eMcmd  eCmd;
    UINT16 usPn;
}sMcmdPn;

// �ڲ�����
// ��������Ӧ��AFN
eMcAFN eMcGetCmdAfn(eMcmd eCmd);

// ��������Ӧ��Fn
UINT8  ucMcGetCmdFn(eMcmd eCmd);

// �ж���8��Pn�Ƿ���ͬһ����Ϣ����,ͬʱȡ����������Ϣ����
BOOL bmc_same_team_pn(UINT16 *pUsPn8, UINT8* pucDa2);

// �ж�һ��Pn�Ƿ�Ϊ0
BOOL bmc_is_p0(UINT16 *pUsPn8);

// ���pn��Ӧ����Ϣ����
UINT8 ucmc_get_pn_team(UINT16 usPn);

// ���һ��pn��Ӧ����Ϣ����
UINT8 ucmc_get_pn8_team(UINT16 *pusPn);

// �ж�ĳһ��pn�Ƿ���һ��8��pn��
BOOL bmc_in_pn8(UINT16 usPn, UINT16 *pusPn8);

// �ж���8��Fn�Ƿ���ͬһ����Ϣ����,ͬʱȡ����������Ϣ����
BOOL bmc_same_team_fn(UINT8  *pUcFn8, UINT8* pucDt2);

// ���Fn��Ӧ����Ϣ����
UINT8 ucmc_get_fn_team(UINT8 ucFn);

// ���Fn��Ӧ����Ϣ����ĳ���bit
UINT8 ucmc_get_fn_bit(UINT8 ucFn);

// ���һ��Fn��Ӧ����Ϣ����
UINT8 ucmc_get_fn8_team(UINT8 *pucFn);

// �ж�ĳһ��fn�Ƿ���һ��8��fn��
BOOL bmc_in_fn8(UINT8 ucFn, UINT8 *pucFn8);

// ת������
eMcErr emc_add_cmdpn(sMcmdPn* psCmdPn,sMcmdPn sNewCmdPn, UINT8 *pucNumCmdPn);
eMcErr emc_pnfn_to_cmdpn(eMcAFN eAfn, sMcPnFn* psPnFn, UINT8 ucNumPnFn,   sMcmdPn* psCmdPn, UINT8 *pucNumCmdPn);
eMcErr emc_cmdpn_to_pnfn(eMcAFN eAfn, sMcPnFn* psPnFn, UINT8 *pucNumPnFn, sMcmdPn* psCmdPn, UINT8  ucNumCmdPn);
eMcErr emc_dadt_to_cmdpn(eMcAFN eAfn, sMcDaDt* psDaDt, UINT8 ucNumDaDt,   sMcmdPn* psCmdPn, UINT8 *pucNumCmdPn);
eMcErr emc_cmdpn_to_dadt(eMcAFN eAfn, sMcDaDt* psDaDt, UINT8 *pucNumDaDt, sMcmdPn* psCmdPn, UINT8  ucNumCmdPn);
///*}


/************************************************************
 *  Tp ʱ���ǩ��ʽ
 *
{*///
// �û���
typedef struct
{
    sMcFmt03 sTime;                 // ����֡����ʱ��
    UINT8    ucPermitDelayMinutes;  // �����ʹ�����ʱʱ��(����);
}sMcTp;

// ��֡��
#pragma pack(1)
typedef struct
{
    sMcFmt03_f sTime;                 // ����֡����ʱ��
    UINT8      ucPermitDelayMinutes;  // �����ʹ�����ʱʱ��(����);
}sMcTp_f;
#pragma pack()

// ת������
eMcErr emc_trans_tp(eMcTrans eTrans, sMcTp* pUser, sMcTp_f* pFrame);

// ��õ�ǰ�û���Tp
eMcErr emc_get_tp(sMcTp *psuTp);   

// �Ե�ǰʱ��Ϊ��׼�ж�һ��tp�Ƿ�ʱ
BOOL  bmc_tp_timeout(sMcTp *psTP);
///*}

/*******************************************
 *  ���������
 *  Э������Ӧ����ÿ��ʵ�ʵ�������Ϊ��,��֡����Ҫ�����������������0xEE
{*///
BOOL   bmc_is_0xEE(UINT8* pData, UINT16 usLen);    // �ж�֡��ĳ�������Ƿ�����Ч��
void   vmc_set_0xEE(UINT8* pData, UINT16 usLen);   // ��֡��ĳ����������Ϊ��Ч

BOOL   bmc_is_none(UINT8* pData, UINT16 usLen);    // ������ȱ��
void   vmc_set_none(UINT8* pData, UINT16 usLen);   // ������������Ϊȱ��
///*}

/************************************************************
 *  ������Ϣ�� AUX ����
 *
{*///

BOOL   bmc_have_pw(eMcAFN eAFN, eMcDir eDir);      // ���౨�����Ƿ�Ӧ����pw�ֶ�
BOOL   bmc_have_ec(eMcAFN eAFN, eMcDir eDir);      // ���౨�����Ƿ�Ӧ����EC�ֶ�
BOOL   bmc_have_tp(eMcAFN eAFN, eMcDir eDir);      // ���౨�����Ƿ�Ӧ����tp�ֶ�

// �û���
typedef struct
{
    UINT16 usEC1;              // ��Ҫ�¼������� EC1
    UINT16 usEC2;              // һ���¼������� EC2
}sMcEc, sMcEc_f;

// �¼��������ú���
void vmc_set_ec(sMcEc *psEc);

// ��ñ����и������֡������ֽ�����
UINT16 usmc_get_aux_len(eMcAFN eAFN, eMcDir eDir, BOOL bEc, BOOL bTp); 
///*}
///*}

/*******************************************************
 *  ��������ܺ���
 *  �ؼ����ݵļ���
 *  �����㷨:����Ӧ�ò���Ҫ���ܵĹؼ�����,���öԳ��㷨�������ݼӽ���
 *  ���ܲ���:Ӧ�ò㹦���롢���ݵ�Ԫ��ʶ�����ݵ�Ԫ����
 *  ���ܳ���:ͨ����������öԳ���Կ�㷨���������ݼ��ܳ�����,�û����ݳ��Ȼ���Ӧ�ı�
 *           �ն����յ����öԳ���Կ�㷨���ܵ�������Ϣ��,�����ݽ��н���
 *           ���ܳɹ�����ԭʼ��������Ϣ��������Ϣ�����ݳ���
 *  ��������:��Ҫ���ܵı�������
 *           (1)��λ��������б���
 *           (2)���ò�����������б���
 *           (3)������������б���
 *
 *  �ҵ�����: AFN�Ƿ�Ӧ�ü���   ���ĳ���ܽ��޷������ĸ����ͼ���
 *
{*///
#if MC_CFG_ENCRYPT
// ���ܺ�������
typedef eMcErr (*peMcEncryptFunc)(UINT8* pInData, int nInLen, UINT8* pOutData, int *pOutLen);  

// ���ܺ�������
typedef eMcErr (*peMcDecryptFunc)(UINT8* pInData, int nInLen, UINT8* pOutData, int *pOutLen);  
#endif
///*} 

/*******************************************************
 *  ���������
 *  
 *  �û���:Ĭ���ֽڶ���, ���ϲ����ʱʹ��
 *  ��֡��:1�ֽڶ���,���ڷ�װ֡�ͽ���֡
 *  ��������:ʵ�ֶԸ�Fn�û���ͷ�֡�����ݽṹ��ת������  
 *  
 *
{*///

/*******************************************
 * ��������: ȫ��ȷ��/���ϣ����յ������е�ȫ�����ݵ�Ԫ��ʶ����ȷ��/����
 * ��ӦAFN : MC_AFN_00_CONF
 * ��ӦCMD : MCMD_AFN_0_F1_ALL_OK_DENY
 * PN ���� : P0
{*///

// �û��ṹ
typedef enum
{
    MC_RES_OK          = 0,    // ȷ��
    MC_RES_NONE        = 1,    // ����������ݡ������õĲ�������Ҫִ�еĹ���
    MC_RES_NOT_READY   = 2,    // ���������δ����������ִ��δ����
    MC_RES_REMOVE      = 3,    // ����������Ѿ����Ƴ����洰��
    MC_RES_DATA_OTRNG  = 4,    // ��������ݳ���֧�ֵ���Ϣ�㷶Χ
    MC_RES_PARA_OTRNG  = 5,    // ���õĲ�������֧�ֵ���Ϣ�㷶Χ
    MC_RES_NOT_SAME    = 6,    // ���õĽ���˿ںż�������ʵ�ʲ���
    MC_RES_NOT_SUPT    = 7,    // ָ���ӿڲ�֧��ת��
    MC_RES_DENY        = 255   // ����
    
}eMcResCode, sMcAfn00F1;                   // ȷ��/������Ϣ�붨�� 

// eMcResCode    eResCode;

// ��֡�ṹ
//UINT8  ucResCode;

// ת������
eMcErr emc_trans_afn00f1(eMcTrans eTrans, void* pUser, void* pFrame, UINT16* pusLen);
///*} 

/*******************************************
 * ���ȷ�������
 * ��ӦAFN : MC_AFN_00_CONF
 * ��ӦCMD : MCMD_AFN_0_F2_ONE_BY_ONE
 * PN ���� : P0
{*///
// �û�������
typedef struct
{
    eMcmd       eCmd;         // ȷ�϶�Ӧ�Ĺ�����
    UINT16      usPn;         // Pn  0 ~ 2040
    eMcResCode  eResCode;     // ����
}sMcmdErr;                    // ȷ������� �û������ݽṹ

typedef struct
{
    eMcAFN        eAFN;       // ��Ҫȷ�ϵ�AFN
    UINT8        ucNum;       // ��Ҫȷ�� �� ���ϵ� Fn����
    sMcmdErr   sOne[1];       // ucNum ��sMtUFnPnErr  
}sMcOnebyOne;                 // ȷ������� (�û������ݽṹ)

// ֡������
#pragma pack(1) 
typedef struct
{
    sMcPnFn     sPnFn;
    eMcResCode  eResCode;
}sMcFnPnErr;                   // ȷ������� �û������ݽṹ

typedef struct
{
    sMcDaDt     sDaDt;         // ���ݵ�Ԫ��ʶ
    UINT8       ucErr;         // ���� ��ʶ   (0 ��ȷ 1 ����)
}sMcOne_f;                     // ȷ�������  ֡�����ݽṹ   

typedef struct
{
    UINT8       ucAFN;
    sMcOne_f    sOne[1];
}sMcOneByOne_f;
#pragma pack()

// ת������
eMcErr emcTrans_OneByOne(eMcTrans eTrans,void* psUser, void* psFrame, UINT16* pusfLen);
///*} 

/*******************************************
 * ��������: ָ����������(��ʵʱ���ݵ�Ԫ��ʶ��Ч)
 * ��ӦAFN : MC_AFN_01_RSET
 * ��ӦCMD : MCMD_AFN_1_F5_DATA_CLEAR
 * PN ���� : P0
{*///

// �û���
typedef struct
{
    UINT8   ucNum;      // ��������������
    sMcmdPn sCmdPn[1];  // ucNum ��������pn�����

}sMcDataClear, sMcAfn01f5, sMcRtDataClear;

// ��װ��
#pragma pack(1)
typedef struct
{
    UINT8    ucNum;    // ���ݵ�Ԫ��ʶ����
    sMcDaDt  sDaDt[1]; // ncNum�����ݵ�Ԫ��ʶ

}sMcDataClear_f, sMcAfn01f5_f;
#pragma pack()

// ת������
eMcErr emc_trans_afn01f5(eMcTrans eTrans, void* pUser, void* pFrame, UINT16* pusLen);
///*} 

/*******************************************
 * ��������: ��Ϣ�����뽻���ն�����ͨ�ſ�ͨ�Ų���
 * ��ӦAFN : MC_AFN_04_SETP
 * ��ӦCMD : MCMD_AFN_4_F1_CON_UP_CFG
 * PN ���� : P0
{*///
// �û���
typedef struct
{
    UINT8  ucPermitDelayM;    // ��Ϣ�����뽻���ն���Ϊ����վ��������ʱʱ�� (��λ:���� 0~255)
    UINT8  ucReSendTimes;     // �ط����� (0~3)   0 ��ʾ�������ط�
    UINT8  ucHeartBeat;       // ��������
    UINT16 usWaitTimeoutS;    // ��Ϣ�����뽻���ն���Ϊ����վ�ȴ�Ӧ��ĳ�ʱʱ�� (���� 0~4095)
    BOOL   bPermitRt;         // ʵʱ���� �Ƿ�������Ϣ�����뽻���ն���Ҫ��(��)վȷ��
    BOOL   bPermitTk;         // �������� �Ƿ�������Ϣ�����뽻���ն���Ҫ��(��)վȷ��
    BOOL   bPermitEv;         // �¼����� �Ƿ�������Ϣ�����뽻���ն���Ҫ��(��)վȷ��

}sMcUpCfg, sMcAfn04f1;

// ��װ��
#pragma pack(1)
typedef struct
{
    UINT8  ucPermitDelayM;    // ��Ϣ�����뽻���ն���Ϊ����վ��������ʱʱ��
    UINT8  ucSWTS1;           // ��Ϣ�����뽻���ն���Ϊ����վ�ȴ�Ӧ��ĳ�ʱʱ����ط�����
    UINT8  ucSWTS2;           // �ն˵ȴ��Ӷ�վ��Ӧ�ĳ�ʱʱ����ط����� wait ts
    UINT8  bs8Con;            // ��Ϣ�����뽻���ն���Ϊ����վ��ȷ��Ӧ��Ĵ�������־ 
    UINT8  ucHeartBeat;       // ��������

}sMcUpCfg_f, sMcAfn04f1_f;
#pragma pack()

// ת������
eMcErr emc_trans_afn04f1(eMcTrans eTrans, void* pUser, void* pFrame, UINT16* pusLen);
///*} 

/*******************************************
 * ��������: ��(��)վ����
 * ��ӦAFN : MC_AFN_04_SETP
 * ��ӦCMD : MCMD_AFN_4_F2_MST_PARA
 * PN ���� : P0
{*///
typedef enum
{
    MC_IP_UNKOWN,
    MC_IP_V4,
    MC_IP_V6,
}eMcIp;

// IP��ַ ��������
typedef struct
{
    eMcIp eVersion;
    UINT8 ip[MC_IP_LEN];
}sMcIp, sMcMask;

// ��֡��
#pragma pack(1)
typedef struct
{
    UINT8  ucVersion;
    UINT8 ip[MC_IP_LEN];

}sMcIp_f, sMcMask_f;
#pragma pack()

// ת������
eMcErr emc_trans_ip(eMcTrans eTrans, void* pUser, void* pFrame, UINT16* pusLen);

// �û���
typedef struct
{
    UINT8          ucID;   // ��վ1�ı��
    BOOL         bValid;   // ������Ч��
    UINT8       ucNoNum;   // ������������վ����վ���õ����ݵ�Ԫ��ʶ���� (0~8)  ���Ӧ�����������
    sMcmdPn   sCmdPn[8];   // ������������վ����վ���õ����ݵ�Ԫ��ʶ ucNoNum
    sMcIp       sMainIP;   // ���õ�ַ
    UINT16   usMainPort;   // ���ö˿�
    sMcIp       sBackIP;   // ���õ�ַ
    UINT16   usBackPort;   // ���ö˿� 
    UINT8  ucascAPN[16];   // APN
    UINT8       usr[32];   // �û���
    UINT8       pwd[32];   // ����
}sMcMstParaOne;

typedef struct
{
    UINT8              ucN;  // �������õ���(��)վ��n ȡֵ��Χ 0��255 ���У�0 ��ʾɾ�����е���(��)վ����)
    sMcMstParaOne  sOne[1];  // ucN����Ϣ
}sMcMstPara, sMcAfn04f2;

// ��װ��
#pragma pack(1)
typedef struct
{
    UINT8             ucID;  // ��վ1�ı��
    UINT8         bs8Valid;  // ��(��)վ��Ч�Ա�־����ʾ��Ӧ����(��)վ�Ĳ�����Ч�ԣ����С�D0��=1����Ч����D0��=0��ɾ��������������
    sMcDaDt          sDaDt;  // ������������վ����վ���õ����ݵ�Ԫ��ʶ
    sMcIp_f        sMainIP;   // ���õ�ַ
    UINT16      usMainPort;   // ���ö˿�
    sMcIp_f        sBackIP;   // ���õ�ַ
    UINT16      usBackPort;   // ���ö˿� 
    UINT8     ucascAPN[16];   // APN
    UINT8          usr[32];   // �û���
    UINT8          pwd[32];   // ���� 
}sMcMstParaOne_f;

typedef struct
{
    UINT8               ucN;  // �������õ���(��)վ��n ȡֵ��Χ 0��255 ���У�0 ��ʾɾ�����е���(��)վ����)
    sMcMstParaOne_f sOne[1];  
}sMcMstPara_f, sMcAfn04f2_f;
#pragma pack()

// ת������
eMcErr emc_trans_afn04f2(eMcTrans eTrans, void* pUser, void* pFrame, UINT16* pusLen);
///*} 

/*******************************************
 * ��������: ��Ϣ�����뽻���ն�����ͨ����Ϣ��֤����
 * ��ӦAFN : MC_AFN_04_SETP
 * ��ӦCMD : MCMD_AFN_4_F3_CON_AUTH_PARA
 * PN ���� : P0
{*///
// �û���
typedef struct
{
    UINT8     ucTypeID;   // ���ڱ�ʾ��ϵͳԼ���ĸ�����Ϣ��֤������ȡֵ��Χ0��255�����У�0��ʾ����֤��255��ʾר��Ӳ����֤������1��254���ڱ�ʾ���������֤����
    UINT16    usAuthPara; // ��Ϣ��֤��������

}sMcAuthPara, sMcAfn04f3;

// ��֡��
#pragma pack(1)
typedef struct
{
    UINT8     ucTypeID;   // ���ڱ�ʾ��ϵͳԼ���ĸ�����Ϣ��֤������ȡֵ��Χ0��255�����У�0��ʾ����֤��255��ʾר��Ӳ����֤������1��254���ڱ�ʾ���������֤����
    UINT16    usAuthPara; // ��Ϣ��֤��������

}sMcAuthPara_f, sMcAfn04f3_f;
#pragma pack()

// ת������
eMcErr emc_trans_afn04f3(eMcTrans eTrans, void* pUser, void* pFrame, UINT16* pusLen);
///*} 

/*******************************************
 * ��������: ��Ϣ�����뽻���ն����ַ
 * ��ӦAFN : MC_AFN_04_SETP
 * ��ӦCMD : MCMD_AFN_4_F4_TEAM_ADDR
 * PN ���� : P0
{*///

#define MC_TEAD_ADD_NUM (8)
// �û���
typedef struct
{
    UINT32 ulAddr[MC_TEAD_ADD_NUM];
    
}sMcTeamAddr, sMcAfn04f4;

// ��֡��
typedef sMcTeamAddr sMcTeamAddr_f, sMcAfn04f4_f;

// ת������
eMcErr emc_trans_afn04f4(eMcTrans eTrans, void* pUser, void* pFrame, UINT16* pusLen);
///*} 

/*******************************************
 * ��������: ��Ϣ�����뽻���ն�IP��ַ�Ͷ˿�
 * ��ӦAFN : MC_AFN_04_SETP
 * ��ӦCMD : MCMD_AFN_4_F5_CON_IP_PORT
 * PN ���� : P0
{*///
// �û���
typedef enum
{
    MC_DELG_UNKOWN,  // δ֪���� 
    MC_DELG_NULL,    // ��ʹ�ô���
    MC_DELG_HTTP,    // ʹ��http connect����
    MC_DELG_SOCK4,   // ʹ��sock4����
    MC_DELG_SOCK5,   // ʹ��sock5����
   
}eMcDelegate;

// ������������ӷ�ʽ
typedef enum
{
    MC_DELK_UNKOWN, // δ֪��ʽ
    MC_DELK_ANYONE, // ����Ҫ��֤
    MC_DELK_USRPWD, // ��Ҫ�û���������
}eMcDelgLink;

typedef struct
{
    UINT16          usPort;       // ��Ϣ�����뽻���ն������˿� 
    sMcIp           sConIp;       // ��Ϣ�����뽻���ն�IP��ַ
    sMcMask          sMask;       // ���������ַ
    sMcIp          sGateIp;       // ���ص�ַ
    eMcDelegate  eDelegate;       // ��������
    sMcIp          sDelgIp;       // ��������ַIP��ַ
    UINT16      usDelgPort;       // �������˿�
    eMcDelgLink  eDelgLink;       // ������������ӷ�ʽ
    BOOL          bDlegUsr;       // �Ƿ���Ҫ����������û���
    UINT8     ucDlegUsrLen;       // ����������û������� (1~20)
    UINT8    ucDlegUsr[20];       // ����������û���   
    BOOL          bDlegPwd;       // �Ƿ���Ҫ
    UINT8     ucDlegPwdLen;       // ������������볤��   (1~20)
    UINT8    ucDlegPwd[20];       // �������������
     
}sMcIpPort, sMcAfn04f5;

// ��֡��
#pragma pack(1)
typedef struct
{
    UINT16          usPort;       // ��Ϣ�����뽻���ն������˿� 
    sMcIp_f         sConIp;       // ��Ϣ�����뽻���ն�IP��ַ
    sMcMask_f        sMask;       // ���������ַ
    sMcIp_f        sGateIp;       // ���ص�ַ
    UINT8       ucDelegate;       // ��������
    sMcIp_f        sDelgIp;       // ��������ַIP��ַ
    UINT16      usDelgPort;       // �������˿�
    UINT8       ucDelgLink;       // ������������ӷ�ʽ
    UINT8         ucUsrLen;       // ����������û�������m (0~20) 0��ʾ����Ҫ�û�����֤
    /* ����Ϊ�䳤
    UINT8     ucDlegUsr[m];       // ����������û���
    UINT8     ucDlegPwdLen;       // ������������볤�� n  (0~20) 0��ʾ����Ҫ������֤
    UINT8     ucDlegPwd[n];       // �������������
    */ 
    
}sMcIpPort_f, sMcAfn04f5_f;
#pragma pack()

// ת������
eMcErr emc_trans_afn04f5(eMcTrans eTrans, void* pUser, void* pFrame, UINT16* pusLen);
///*} 

/*******************************************
 * ��������: ��Ϣ�����뽻���ն˼���ͨ�Ų���
 * ��ӦAFN : MC_AFN_04_SETP
 * ��ӦCMD : MCMD_AFN_4_F6_CON_CASC  ��MCMD_AFN_A_F6_CON_CASC
 * PN ���� : P0
{*///
typedef enum
{
    MC_BAUD_UNKOWN,
    MC_BAUD_DEFAULT,        // �������û�ʹ��Ĭ��
    MC_BAUD_1200,            
    MC_BAUD_2400,
    MC_BAUD_4800,
    MC_BAUD_9600,
    MC_BAUD_19200,
    MC_BAUD_38400,         
    MC_BAUD_76800,   
}eMcSerBaud;                // ���ڲ�����

typedef enum
{
    MC_SBIT_5,
    MC_SBIT_6,
    MC_SBIT_7,
    MC_SBIT_8,

}eMcSerBit;

typedef struct
{
    eMcSerBaud      eBaud;  // ������
    BOOL           bStop1;  // 1ֹͣλ(true) 2ֹͣλ(false)
    BOOL           bCheck;  // ��У��(true) ��У��(false) 
    BOOL             bOdd;  // ��У��(true) żУ��(true)
    eMcSerBit        eBit;  // 5~8λ��
}sMcAcsParaSer;             // ����˿����в������ݸ�ʽ-����

// �ṹsMcAcsParaSer ת������
eMcErr emc_trans_serial(eMcTrans eTrans, void* pUser, void* pFrame, UINT16* pusLen);

typedef enum
{
    MC_CASC_UNKOWN,   // δ֪������ʽ
    MC_CASC_NULL,     // �����ü�������
    MC_CASC_RS485,    // RS485����
    MC_CASC_ETH       // ��̫������
}eMcTypeCasc;         // ������ʽ

typedef struct
{
     UINT8  acRegionCode[MC_REGN_LEN];   // ������/����������Ϣ�����뽻���ն�����������
     UINT32 ulConAddr;                   // ������/����������Ϣ�����뽻���ն˵�ַ
     sMcIp  sIp;                         // ������/����������Ϣ�����뽻���ն�ͨ�ŵ�ַ
     UINT16 usPort;                      // ������/����������Ϣ�����뽻���ն˶˿ڵ�ַ
}sMcascAddr;          // ������ַ

// �û���
typedef struct
{
    eMcTypeCasc    eType;    // ��Ϣ�����뽻���ն˼������뷽ʽ
    sMcAcsParaSer  sSer;     // ��Ϣ�����뽻���ն˼���ͨ�ſ�����
    UINT8          ucWaitP;  // ���յȴ����ĳ�ʱʱ��(��λ 100ms)
    UINT8          ucWaitC;  // ���յȴ��ֽڳ�ʱʱ��(��λ 10ms)
    UINT8          ucReTry;  // ������������վ������ʧ���ط�����
    UINT8          ucPeriod; // ����Ѳ������(��λ: ����)
    UINT8          ucN;      // ����/��������־�������Ӧ�ı�����/��������Ϣ�����뽻���ն˸���n
    sMcascAddr     sOne[1];  // ucN 
}sMcasc, sMcAfn04f6;

#pragma pack(1)
typedef struct
{
     UINT8     acRegionCode[MC_A1_LEN];     // ������/����������Ϣ�����뽻���ն�����������
     UINT32    ulConAddr;                   // ������/����������Ϣ�����뽻���ն˵�ַ
     sMcIp_f   sIp;                         // ������/����������Ϣ�����뽻���ն�ͨ�ŵ�ַ
     UINT16    usPort;                       // ������/����������Ϣ�����뽻���ն˶˿ڵ�ַ
}sMcascAddr_f;          // ������ַ

// ��֡��
typedef struct
{
    UINT8          eType;    // ��Ϣ�����뽻���ն˼������뷽ʽ
    UINT8          sSer;     // ��Ϣ�����뽻���ն˼���ͨ�ſ�����
    UINT8          ucWaitP;  // ���յȴ����ĳ�ʱʱ��(��λ 100ms)
    UINT8          ucWaitC;  // ���յȴ��ֽڳ�ʱʱ��(��λ 10ms)
    UINT8          ucReTry;  // ������������վ������ʧ���ط�����
    UINT8          ucPeriod; // ����Ѳ������(��λ: ����)
    UINT8          ucN;      // ����/��������־�������Ӧ�ı�����/��������Ϣ�����뽻���ն˸���n
    sMcascAddr_f   sOne[1];  // ucN 
}sMcasc_f, sMcAfn04f6_f;
#pragma pack()

// ת������
eMcErr emc_trans_afn04f6(eMcTrans eTrans, void* pUser, void* pFrame, UINT16* pusLen);
///*} 

/*******************************************
 * ��������: ��Ϣ�����뽻���ն�������̫���˿�ͨ�Ų���
 * ��ӦAFN : MC_AFN_04_SETP
 * ��ӦCMD : MCMD_AFN_4_F7_CON_DOWN_CFG
 * PN ���� : P0
{*///

// �û���
#define MC_APN_LEN  (16)
typedef struct
{
    UINT8       ucPort;              // ��Ϣ�����뽻���ն˵�����ͨ�Ŷ˿ں�
    sMcIp       sMainIp;             // ����IP��ַ
    UINT16      usMainPort;          // ���ö˿ڵ�ַ
    sMcIp       sBackIp;             // ����IP��ַ
    UINT16      usBackPort;          // ���ö˿ڵ�ַ
    UINT8       ucAPN[MC_APN_LEN];   // APN
    UINT8       ucUsr[32];           // �û���
    UINT8       ucPwd[32];           // ����
    
}sMcDownCfg, sMcAfn04f7;

// ��֡��
#pragma pack(1)
typedef struct
{
    UINT8       ucPort;              // ��Ϣ�����뽻���ն˵�����ͨ�Ŷ˿ں�
    sMcIp_f     sMainIp;             // ����IP��ַ
    UINT16      usMainPort;          // ���ö˿ڵ�ַ
    sMcIp_f     sBackIp;             // ����IP��ַ
    UINT16      usBackPort;          // ���ö˿ڵ�ַ
    UINT8       ucAPN[MC_APN_LEN];   // APN
    UINT8       ucUsr[32];           // �û���
    UINT8       ucPwd[32];           // ����
}sMcDownCfg_f, sMcAfn04f7_f;
#pragma pack()

// ת������
eMcErr emc_trans_afn04f7(eMcTrans eTrans, void* pUser, void* pFrame, UINT16* pusLen);
///*} 

/*******************************************
 * ��������: �¼���¼����
 * ��ӦAFN : MC_AFN_04_SETP
 * ��ӦCMD : MCMD_AFN_4_F9_CON_EVENT_CFG
 * PN ���� : P0
{*///

// �û���
typedef struct
{   
    UINT8      ucNeed;    // ��Ҫ��¼���¼���¼�����͸���   
    eMcErc  aNeed[64];    // ucErcNeed����Ҫ��¼���¼���¼��������
    UINT8      ucImpt;    // ����Ϊ��Ҫ�¼��ĸ���
    eMcErc  aImpt[64];    // ucErcImpt���¼�����Ϊ��Ҫ���¼�(��ô����ľ���һ���¼�)
                          // �¼���Ҫ�Եȼ���־λ��D0��D63 ��˳���λ��ʾ�¼����� ERC1��ERC64 ��������¼���
                          //     �á�1������λ����Ӧ�ĸ澯�¼�Ϊ��Ҫ�¼������¼���������ͨ���߱������ϱ�������
                          // Ӧ�����ϱ��¼���¼���粻�߱������ϱ�������ͨ�� ACD λ�ϱ���
                          //     �á�0������λ����Ӧ�ĸ澯�¼�Ϊһ���¼������¼�������ֻ��Ҫ�����¼���¼��
    UINT16   usImpRecNum; // ��Ҫ�¼���¼������ָ��Ҫ��¼����Ҫ�¼�������Ĭ��ֵΪ 255
    UINT16   usNmlRecNum; // һ���¼���¼������ָ��Ҫ��¼��һ���¼�������Ĭ��ֵΪ 255
}sMcEventCfg, sMcAfn04f9;

// ��֡��
#pragma pack(1)
typedef struct
{
    UINT8     aNeed[8];   // �¼���¼��Ч��־λ
    UINT8     aImpt[8];   // �¼���Ҫ�Եȼ���־λ
    UINT16  usImpRecNum;  // ��Ҫ�¼���¼������ָ��Ҫ��¼����Ҫ�¼�������Ĭ��ֵΪ 255
    UINT16  usNmlRecNum;  // һ���¼���¼������ָ��Ҫ��¼��һ���¼�������Ĭ��ֵΪ 255
   
}sMcEventCfg_f, sMcAfn04f9_f;
#pragma pack()

// ת������
eMcErr emc_trans_afn04f9(eMcTrans eTrans, void* pUser, void* pFrame, UINT16* pusLen);
///*} 

/*******************************************
 * ��������: �豸״̬���������
 * ��ӦAFN : MC_AFN_04_SETP
 * ��ӦCMD : MCMD_AFN_4_F10_CON_STATE_INPUT MCMD_AFN_A_F10_CON_STATE_INPUT
 * PN ���� : P0
{*///
// �û���
typedef struct
{
    BOOL bIn[8];       // ״̬�������־λ����Ӧ 1��8 ·״̬������true����.      �� false δ����
    BOOL bOn[8];       // ״̬�����Ա�־λ����Ӧ 1��8 ·״̬���� ��true�������㡣�� false ���մ���

}sMcStateInput, sMcAfn04f10;

// ��֡��
#pragma pack(1)
typedef struct
{
    UINT8 bIn;
    UINT8 bOn;

}sMcStateInput_f, sMcAfn04f10_f;
#pragma pack()

// ת������
eMcErr emc_trans_afn04f10(eMcTrans eTrans, void* pUser, void* pFrame, UINT16* pusLen);
///*} 

/*******************************************
 * ��������: ����ն�����ͨ�Ų�������
 * ��ӦAFN : MC_AFN_04_SETP
 * ��ӦCMD : MCMD_AFN_4_F17_TML_UP_CFG  MCMD_AFN_A_F17_TML_UP_CFG
 * PN ���� : P0
{*///

#define MC_TML_UP_PROTO   (1) // �ն�����ͨ��Э������
// �û���
typedef enum
{
   MC_TUPP_UNKOWN,              // δ֪����
   MC_TUPP_DEL,                 // ɾ���ü���ն˺ŵ����ò���
   MC_TUPP_SER,                 // ����
   MC_TUPP_ETH,                 // ��̫��

}eMcUpPara;                     // ����ն�����ͨ�Ŷ˿�����

typedef struct
{
    UINT8       ucDownPort;     // ��Ϣ�����뽻���ն˵�����ͨ�Ŷ˿ں�
    UINT16    usListenPort;     // ����ն������Ŷ˿ں� 
    eMcUpPara      eUpPara;     // ����ն�����ͨ�Ŷ˿�����
    sMcA           sUpAddr;     // ����ն�����ͨ�ŵ�ַ
    UINT8        ucUpProto;     // ����ն�����ͨ��Э������ MC_TML_UP_PROTO
    sMcIp            sUpIp;     // ����ն�����IP��ַ
    sMcMask        sUpMask;     // ����ն����������ַ
    sMcIp          sGateIp;     // ���ص�ַ
    eMcDelegate  eDelegate;     // ��������
    sMcIp          sDelgIp;     // ��������ַIP��ַ
    UINT16      usDelgPort;     // �������˿�
    eMcDelgLink  eDelgLink;     // ������������ӷ�ʽ
    BOOL          bDlegUsr;     // �Ƿ���Ҫ����������û���
    UINT8     ucDlegUsrLen;     // ����������û������� (1~20)
    UINT8    ucDlegUsr[20];     // ����������û���   
    BOOL          bDlegPwd;     // �Ƿ���Ҫ
    UINT8     ucDlegPwdLen;     // ������������볤��   (1~20)
    UINT8    ucDlegPwd[20];     // �������������
    UINT8   ucPermitDelayM;     // ����ն���Ϊ����վ��������ʱʱ�� (��λ:���� 0~255)
    UINT8    ucReSendTimes;     // �ط����� (0~3)   0 ��ʾ�������ط�
    UINT8      ucHeartBeat;     // ��������
    UINT16  usWaitTimeoutS;     // ����ն���Ϊ����վ�ȴ�Ӧ��ĳ�ʱʱ�� (���� 0~4095)
    BOOL         bPermitRt;     // ʵʱ���� �Ƿ��������ն���Ҫ������ȷ��
    BOOL         bPermitTk;     // �������� �Ƿ��������ն���Ҫ������ȷ��
    BOOL         bPermitEv;     // �¼����� �Ƿ��������ն���Ҫ������ȷ��

}sMcTmlUpCfg, sMcAfn04f17;

// ��֡��
#pragma pack(1)
typedef struct
{
    UINT8       ucDownPort;     // ��Ϣ�����뽻���ն˵�����ͨ�Ŷ˿ں�(0~255)
    UINT16    usListenPort;     // ����ն������Ŷ˿ں� 
    UINT8         ucUpPara;     // ����ն�����ͨ�Ŷ˿����� 
    sMcA_f         sUpAddr;     // ����ն�����ͨ�ŵ�ַ 
    UINT8        ucUpProto;     // ����ն�����ͨ��Э������
                                // ��ֵ��Χ 1��255�����У�1��GB/TXXX.3-2-2013��
                                // 2~100�����ã�101��255 Ϊ�Զ���Э�顣
    sMcIp_f          sUpIp;     // ����ն�����IP��ַ
    sMcMask_f      sUpMask;     // ����ն����������ַ
    sMcIp_f        sGateIp;     // ���ص�ַ
    UINT8       ucDelegate;     // ��������
    sMcIp_f        sDelgIp;     // ��������ַIP��ַ
    UINT16      usDelgPort;     // �������˿�
    UINT8       ucDelgLink;     // ������������ӷ�ʽ
    UINT8         ucUsrLen;     // ����������û�������m (0~20) 0��ʾ����Ҫ�û�����֤
    /* ����Ϊ�䳤
    UINT8     ucDlegUsr[m];     // ����������û���
    UINT8     ucDlegPwdLen;     // ������������볤�� n  (0~20) 0��ʾ����Ҫ������֤
    UINT8     ucDlegPwd[n];     // �������������

    // �ͽṹ sMcUpCfg_f ��ͬ
    UINT8  ucPermitDelayM;      // ��Ϣ�����뽻���ն���Ϊ����վ��������ʱʱ�� 
    UINT8  ucSWTS1;             // ��Ϣ�����뽻���ն���Ϊ����վ�ȴ�Ӧ��ĳ�ʱʱ����ط�����
    UINT8  ucSWTS2;             // �ն˵ȴ��Ӷ�վ��Ӧ�ĳ�ʱʱ����ط����� wait ts
    UINT8  bs8Con;              // ��Ϣ�����뽻���ն���Ϊ����վ��ȷ��Ӧ��Ĵ�������־ 
    UINT8  ucHeartBeat;         // ��������                     
    */ 
}sMcTmlUpCfg_f, sMcAfn04f17_f;
#pragma pack()

// ת������
eMcErr emc_trans_afn04f17(eMcTrans eTrans, void* pUser, void* pFrame, UINT16* pusLen);
///*} 

/*******************************************
 * ��������: �������������ò���
 * ��ӦAFN : MC_AFN_04_SETP
 * ��ӦCMD : MCMD_AFN_4_F25_ELEC_MP_CFG
 * PN ���� : �����������
{*///
// �û���
typedef enum
{
   MC_ACS_PROT_UNKOWN,      // δ֪ͨ��Э������
   //MC_ACS_PROT_GBNX31,    // GB/TXXXX.3.1-2013
   MC_ACS_PROT_GBNX_32,     // GB/TXXXX.3.1-2013
   MC_ACS_PROT_DLT645_97,   // DL/T645-1997
   MC_ACS_PROT_DLT645_07,   // DL/T645-2007
   MC_ACS_PROT_MODBUS,      // Modbus
   MC_ACS_PROT_USER = 128,  // (128~255)��ʾ�Զ���

}eMcAcsProto;               // �����豸ͨ������

typedef enum
{
    MC_ACS_PORT_UNKOWN,     // δ֪�ӿ�����
    MC_ACS_PORT_DC,         // ֱ��ģ����
    MC_ACS_PORT_AC,         // ����ģ����
    MC_ACS_PORT_SER,        // ����(RS485/RS232)
    MC_ACS_PORT_ETH,        // ��̫��
    MC_ACS_PORT_ZIGB,       // zigbee
    MC_ACS_PORT_USER = 128, // 128~255 �û��Զ��� 
    
}eMcAcsPort;                // ����˿�����

typedef struct
{
    UINT16          usPort; // �����豸�����˿ں�
    sMcIp          sAccess; // �����豸IP��ַ
    /* ���Ժ�ڲ��� 
    sMcMask          sMask; // ���������ַ
    sMcIp            sGate; // ���ص�ַ
    */
}sMcAcsParaEth;             // ����˿����в������ݸ�ʽ-��̫��

typedef struct
{
    UINT16             usID;     // ������Ϣ�����뽻���ն�/����ն˺�
                                 // ��0 ��ʾ���������������Ϣ�����뽻���ն�
                                 // ��0 ��ʾ���������������Ч����ն�
    UINT8            ucPort;     // 1 ~ 255
    UINT8        ucAddr[16];     // �����豸ͨ�ŵ�ַ
    eMcAcsProto   eAcsProto;     // �����豸ͨ��Э������
    UINT8          ucPwd[6];     // ͨ������
    
    eMcAcsPort     eAcsPort;     // �����ն����� ���� uPortPara������
    union
    {
                                 // eAcsPort == MC_ACS_PORT_DC   ֱ��ģ�����޲�������
                                 // eAcsPort == MC_ACS_PORT_AC   ����ģ�����޲�������
        sMcAcsParaSer  sSer;     // eAcsPort == MC_ACS_PORT_SER  �������в���
        sMcAcsParaEth  sEth;     // eAcsPort == MC_ACS_PORT_ETH  ��̫�����в���
        UINT32   ulAddrZigb;     // eAcsPort == MC_ACS_PORT_ZIGB Zigbee��ַ 
        
    }uPortPara;                  // ����˿����в�������

    UINT16        usAcsPort;     // �����豸�����˿ں�

    sMcIp           sAccess;     // �����豸IP��ַ

    /* ���Ժ�ڲ��� 
    sMcMask           sMask;     // ���������ַ
    sMcIp           sGateIp;     // ���ص�ַ
    */

}sMcElecMpCfg, sMcAfn04f25;

// ��֡��
#pragma pack(1)

typedef struct
{
    UINT16            usPort;    // �����豸�����˿ں�
    sMcIp_f          sAccess;    // �����豸IP��ַ

    /*
    sMcMask_f          sMask;    // ���������ַ
    sMcIp_f            sGate;    // ���ص�ַ
    */
}sMcAcsParaEth_f;                // ����˿����в������ݸ�ʽ-��̫��

typedef struct
{
    UINT16             usID;     // ������Ϣ�����뽻���ն�/����ն˺�
                                 // ��0 ��ʾ���������������Ϣ�����뽻���ն�
                                 // ��0 ��ʾ���������������Ч����ն�
    UINT8            ucPort;     // 1 ~ 255
    UINT8      ucAddrBcd[8];     // �����豸ͨ�ŵ�ַ(BCD)
    UINT8         eAcsProto;     // �����豸ͨ��Э������
    UINT8          ucPwd[6];     // ͨ������
    UINT8          eAcsPort;     // �����ն�����
    UINT8      ucAcsParaLen;     // ��Ӧ�����в����Ľṹ����

    /* �䳤�����в����ṹ
                                 // MC_ACS_PORT_DC ֱ��ģ�����޲�������
                                 // MC_ACS_PORT_AC ����ģ�����޲�������
    UINT8            sSer;       // MC_ACS_PORT_SER  �������в���
    sMcAcsParaEth_f  sEth;       // MC_ACS_PORT_ETH  ��̫�����в���
    UINT32   ulAddrZigb;         // MC_ACS_PORT_ZIGB Zigbee��ַ 

    */

    /* ���½��ϱ߱䳤�ṹ֮��
    UINT16        usAcsPort;     // �����豸�����˿ں�
    sMcMask_f         sMask;     // ���������ַ
    sMcIp_f          sGateIp;    // ���ص�ַ
    */
}sMcElecMpCfg_f, sMcAfn04f25_f;
#pragma pack()

// ת������
eMcErr emc_trans_afn04f25(eMcTrans eTrans, void* pUser, void* pFrame, UINT16* pusLen);
///*} 

/*******************************************
 * ��������: �����������������
 * ��ӦAFN : MC_AFN_04_SETP
 * ��ӦCMD : MCMD_AFN_4_F26_ELEC_MP_BASE
 * PN ���� : �����������
{*///

#define MC_DNUM_INTGR_MIN   (4)  // ����λ����Сֵ
#define MC_DNUM_INTGR_MAX   (7)  // ����λ�����ֵ

#define MC_DNUM_DECIM_MIN   (1)  // С��λ����Сֵ
#define MC_DNUM_DECIM_MAX   (4)  // С��λ�����ֵ

typedef struct
{
    UINT8       ucInteger; // �й�����ʾֵ������λ����(4~7)
    UINT8       ucDecimal; // �й�����ʾֵ��С��λ����(1~4)
}sMcDigitNum;    

typedef enum
{   
    MC_LINK_UNKOWN, // δ֪
    MC_LINK_P3_L3,  // ��������
    MC_LINK_P3_L4,  // ��������
    MC_LINK_P1,     // �����
    
}eMcLink;

typedef enum
{
    MC_PHASE_UNKOWN, // δ֪
    MC_PHASE_A,      // A ��
    MC_PHASE_B,      // B ��
    MC_PHASE_C,      // C ��
    
}eMcPhase;

typedef struct
{
    eMcLink    eLink;
    eMcPhase   ePhase;
    
}sMcLinkWay; // ��Դ���߷�ʽ

// �û���
typedef struct
{
    sMcDigitNum      sDigit; // �й�����ʾֵ����λ��С��λ����
    UINT16         usTimesU; // ��ѹ����������
    UINT16         usTimesI; // ��������������
    float                fU; // ���ѹ   (+)XXX.X  (V)
    float                fI; // �����(+/-)XXX.XXX (A)
    sMcLinkWay     sLinkWay; // ��Դ���߷�ʽ
}sMcElecMpBase, sMcAfn04f26;

// ��֡��
#pragma pack(1)
typedef struct
{   
    UINT8            sDigit; // �й�����ʾֵ����λ��С��λ����
    UINT16         usTimesU; // ��ѹ����������
    UINT16         usTimesI; // ��������������
    sMcFmt_XXX_X         fU; // ���ѹ   (+)XXX.X   (V)
    sMcFmt_sXXX_XXX      fI; // ����� (+/-)XXX.XXX (A)
    UINT8          sLinkWay; // ��Դ���߷�ʽ
    
}sMcElecMpBase_f, sMcAfn04f26_f;
#pragma pack()

// ת������
eMcErr emc_trans_afn04f26(eMcTrans eTrans, void* pUser, void* pFrame, UINT16* pusLen);
///*} 

/*******************************************
 * ��������: �����������������ֵ����
 * ��ӦAFN : MC_AFN_04_SETP
 * ��ӦCMD : MCMD_AFN_4_F27_ELEC_LMIT_POWER
 * PN ���� : �����������
{*///
typedef struct
{
    float          fUpUp;        // ��ѹ������(��ѹ����) (+)XXX.X
    UINT8         ucTime;        // ����ʱ��
    float        fFactor;        // Խ�޻ָ�ϵ��         (+)XX.XX 
}sMcOverV;                       // ��ѹ�б����

typedef struct
{
    float      fDownDown;        // ��ѹ������(��ѹ����) (+)XXX.X
    UINT8         ucTime;        // ����ʱ��
    float        fFactor;        // Խ�޻ָ�ϵ��         (+)XX.XX   
}sMcLossV;                       // Ƿѹ�б���� 

typedef struct
{
    float          fUpUp;        // ����������() (+/-)XXX.XXX
    UINT8         ucTime;        // ����ʱ��
    float        fFactor;        // Խ�޻ָ�ϵ��         (+)XX.XX   
}sMcOverI;                       // �����б����

typedef struct
{
    float            fUp;        // ��������(���������) (+/-)XXX.XXX
    UINT8         ucTime;        // ����ʱ��
    float        fFactor;        // Խ�޻ָ�ϵ��         (+)XX.XX   
}sMcSuperI;                      // ��������б����

typedef struct
{
    float            fUp;        // 0��������� (+/-)XXX.XXX
    UINT8         ucTime;        // ����ʱ��
    float        fFactor;        // Խ�޻ָ�ϵ��         (+)XX.XX   
}sMcZeroI;                       // ������������б����

typedef struct
{
    float         fLimit;        // �����ѹ��ƽ�����ֵ (+/-)XX.XXXX
    UINT8         ucTime;        // ����ʱ��
    float        fFactor;        // Խ�޻ָ�ϵ��         (+)XX.XX   
}sMcUnblnV;                      // �����ѹ��ƽ�ⳬ���б����

typedef struct
{
    float         fLimit;        // ���������ƽ�����ֵ (+/-)XX.XXXX
    UINT8         ucTime;        // ����ʱ��
    float        fFactor;        // Խ�޻ָ�ϵ��         (+)XX.XX   
}sMcUnblnI;                      // ���������ƽ�ⳬ���б����

// �û���
typedef struct
{
    float             fDropV;    // ��ѹ�����б����  (+)XXX.X
    UINT8        ucTimeLossV;    // ��ѹʧѹʱ���б���� minutes
    sMcOverV          sOverV;    // ��ѹ�б����
    sMcLossV          sLossV;    // Ƿѹ�б����
    sMcOverI          sOverI;    // �����б����
    sMcSuperI        sSuperI;    // ��������б����
    sMcZeroI          sZeroI;    // ������������б����
    sMcUnblnV          sUblV;    // �����ѹ��ƽ�ⳬ���б����
    sMcUnblnI          sUblI;    // ���������ƽ�ⳬ���б����
}sMcElecLimitPower, sMcAfn04f27;

// ��֡��
#pragma pack(1)

typedef struct
{
    sMcFmt08_f     fUpUp;        // ��ѹ������(��ѹ����) (+)XXX.X
    UINT8         ucTime;        // ����ʱ��
    sMcFmt10_f   fFactor;        // Խ�޻ָ�ϵ��         (+)XX.XX 
}sMcOverV_f;                     // ��ѹ�б����

typedef struct
{
    sMcFmt08_f fDownDown;        // ��ѹ������(��ѹ����) (+)XXX.X
    UINT8         ucTime;        // ����ʱ��
    sMcFmt10_f   fFactor;        // Խ�޻ָ�ϵ��         (+)XX.XX   
}sMcLossV_f;                     // Ƿѹ�б���� 

typedef struct
{
    sMcFmt09_f     fUpUp;        // ����������() (+/-)XXX.XXX
    UINT8         ucTime;        // ����ʱ��
    sMcFmt10_f   fFactor;        // Խ�޻ָ�ϵ��         (+)XX.XX   
}sMcOverI_f;                     // �����б����

typedef struct
{
    sMcFmt09_f       fUp;        // ������(���������) (+/-)XXX.XXX
    UINT8         ucTime;        // ����ʱ��
    sMcFmt10_f   fFactor;        // Խ�޻ָ�ϵ��         (+)XX.XX   
}sMcSuperI_f;                    // ��������б����

typedef struct
{
    sMcFmt09_f       fUp;        // 0��������� (+/-)XXX.XXX
    UINT8         ucTime;        // ����ʱ��
    sMcFmt10_f   fFactor;        // Խ�޻ָ�ϵ��         (+)XX.XX   
}sMcZeroI_f;                     // ������������б����

typedef struct
{
    sMcFmt06_f    fLimit;        // �����ѹ��ƽ�����ֵ (+/-)XX.XXXX
    UINT8         ucTime;        // ����ʱ��
    sMcFmt10_f   fFactor;        // Խ�޻ָ�ϵ��         (+)XX.XX   
}sMcUnblnV_f;                    // �����ѹ��ƽ�ⳬ���б����

typedef struct
{
    sMcFmt06_f    fLimit;        // ���������ƽ�����ֵ (+/-)XX.XXXX
    UINT8         ucTime;        // ����ʱ��
    sMcFmt10_f   fFactor;        // Խ�޻ָ�ϵ��         (+)XX.XX   
}sMcUnblnI_f;                    // ���������ƽ�ⳬ���б����

typedef struct
{
    sMcFmt08_f        fDropV;    // ��ѹ�����б����  
    UINT8        ucTimeLossV;    // ��ѹʧѹʱ���б���� minutes
    sMcOverV_f        sOverV;    // ��ѹ�б����
    sMcLossV_f        sLossV;    // Ƿѹ�б����
    sMcOverI_f        sOverI;    // �����б����
    sMcSuperI_f      sSuperI;    // ��������б����
    sMcZeroI_f        sZeroI;    // ������������б����
    sMcUnblnV_f        sUblV;    // �����ѹ��ƽ�ⳬ���б����
    sMcUnblnI_f        sUblI;    // ���������ƽ�ⳬ���б����
}sMcElecLimitPower_f, sMcAfn04f27_f;
#pragma pack()

// ת������
eMcErr emc_trans_afn04f27(eMcTrans eTrans, void* pUser, void* pFrame, UINT16* pusLen);
///*} 

/*******************************************
 * ��������: ���������㹦������Խ��ֵ����
 * ��ӦAFN : MC_AFN_04_SETP
 * ��ӦCMD : MCMD_AFN_4_F28_ELEC_LMIT_FACTR
 * PN ���� : �����������
{*///
// �û���
typedef struct
{
    float  fPara1;            // �ܹ��������ֶβ��� 1   (+)XX.XX
    float  fPara2;            // �ܹ��������ֶβ��� 2   (+)XX.XX
    float  fWarning;          // �ܹ�������Խ�޸澯��ֵ (+)XX.XX
}sMcFactorLimit, sMcAfn04F28; // ���������㹦������Խ��ֵ�������ݵ�Ԫ��ʽ  

// ��֡��
#pragma pack(1)
typedef struct
{
    sMcFmt10_f  fPara1;      // �ܹ��������ֶβ��� 1
    sMcFmt10_f  fPara2;      // �ܹ��������ֶβ��� 2
    sMcFmt10_f  fWarning;    // �ܹ�������Խ�޸澯��ֵ
}sMcFactorLimit_f, sMcAfn04F28_f; // ���������㹦������Խ��ֵ�������ݵ�Ԫ��ʽ  
#pragma pack()

// ת������
eMcErr emc_trans_afn04f28(eMcTrans eTrans, void* pUser, void* pFrame, UINT16* pusLen);
///*} 

/*******************************************
 * ��������: ����������г��������Խ�޶�ֵ
 * ��ӦAFN : MC_AFN_04_SETP
 * ��ӦCMD : MCMD_AFN_4_F29_ELEC_FIX_HARM
 * PN ���� : �����������
{*///
// aberration ����
typedef struct
{
   float fTotal;              // �ܻ�����Խ�޶�ֵ    (+)XX.XX
   float   fOdd;              // ��λ�����Խ�޶�ֵ  (+)XX.XX
   float  fEven;              // ż�λ����ʳ��޶�ֵ  (+)XX.XX
}sMcAberLimit; 

// �û���
typedef struct
{
    sMcAberLimit      sVa;    // A���ѹ������Խ�޶�ֵ
    sMcAberLimit      sVb;    // B���ѹ������Խ�޶�ֵ
    sMcAberLimit      sVc;    // C���ѹ������Խ�޶�ֵ
    sMcAberLimit      sIa;    // A�����������Խ�޶�ֵ
    sMcAberLimit      sIb;    // B�����������Խ�޶�ֵ
    sMcAberLimit      sIc;    // C�����������Խ�޶�ֵ
     
}sMcElecFixHarm, sMcAfn04F29; // ���������㹦������Խ��ֵ�������ݵ�Ԫ��ʽ  

// ��֡��
#pragma pack(1)
typedef struct
{
   sMcFmt10_f fTotal;             // �ܻ�����Խ�޶�ֵ
   sMcFmt10_f   fOdd;             // ��λ�����Խ�޶�ֵ
   sMcFmt10_f  fEven;             // ż�λ����ʳ��޶�ֵ
}sMcAberLimit_f;

typedef struct
{
    sMcAberLimit_f      sVa;    // A���ѹ������Խ�޶�ֵ
    sMcAberLimit_f      sVb;    // B���ѹ������Խ�޶�ֵ
    sMcAberLimit_f      sVc;    // C���ѹ������Խ�޶�ֵ
    sMcAberLimit_f      sIa;    // A�����������Խ�޶�ֵ
    sMcAberLimit_f      sIb;    // B�����������Խ�޶�ֵ
    sMcAberLimit_f      sIc;    // C�����������Խ�޶�ֵ
    
}sMcElecFixHarm_f, sMcAfn04F29_f; // ���������㹦������Խ��ֵ�������ݵ�Ԫ��ʽ  
#pragma pack()

// ת������
eMcErr emc_trans_afn04f29(eMcTrans eTrans, void* pUser, void* pFrame, UINT16* pusLen);
///*} 

/*******************************************
 * ��������: ��������������Խ�޲���
 * ��ӦAFN : MC_AFN_04_SETP
 * ��ӦCMD : MCMD_AFN_4_F30_ELEC_FLASH
 * PN ���� : �����������
{*///
// �û���
typedef struct
{
    float    fLong;      // ��ʱ����Խ��ֵ  (+)XX.XX
    float   fShort;      // ��ʱ����Խ��ֵ  (+)XX.XX
}sMcElecFlash, sMcAfn04f30;

// ��֡��
#pragma pack(1)
typedef struct
{
    sMcFmt10_f    fLong;      // ��ʱ����Խ��ֵ
    sMcFmt10_f   fShort;      // ��ʱ����Խ��ֵ
}sMcElecFlash_f, sMcAfn04f30_f;
#pragma pack()

// ת������
eMcErr emc_trans_afn04f30(eMcTrans eTrans, void* pUser, void* pFrame, UINT16* pusLen);
///*} 

/*******************************************
 * ��������: �ǵ������������ò���
 * ��ӦAFN : MC_AFN_04_SETP
 * ��ӦCMD : MCMD_AFN_4_F33_NELC_MP_CFG
 * PN ���� : �����������
{*///
///*} 

// �û���
typedef sMcElecMpCfg sMcNelecMpCfg;
typedef sMcAfn04f25  sMcAfn04f33;

// ��֡��
typedef sMcElecMpCfg_f sMcNElecMpCfg_f;
typedef sMcAfn04f25_f  sMcAfn04f33_f; 

// ת������
eMcErr emc_trans_afn04f33(eMcTrans eTrans, void* pUser, void* pFrame, UINT16* pusLen);
///*} 

/*******************************************
 * ��������: �ǵ������������ݲ���
 * ��ӦAFN : MC_AFN_04_SETP
 * ��ӦCMD : MCMD_AFN_4_F34_NELC_MP_PARA
 * PN ���� : �����������
{*///
// �û���
typedef enum
{
   MC_NELC_UNKOWN,
   MC_NELC_TEMP,       // �¶�
   MC_NELC_FLOW,       // ����
   MC_NELC_FV,         // ����
   MC_NELC_PRESS,      // ѹ��
   MC_NELC_HUMI,       // ʪ��
   MC_NELC_LIGHT,      // �ն�
   MC_NELC_RV,         // ת��
   MC_NELC_420MA,      // 4~20MA

}eMcNElcType;

typedef struct
{
    eMcNElcType eType;           // �ǵ���������
    sMcDouble     sUp;           // ��������
    sMcDouble   sDown;           // ��������
}sMcNelcMpPara, sMcAfn04f34;

// ��֡��
#pragma pack(1)
typedef struct
{
    UINT8       eType;            // �ǵ���������
    sMcFmt11_f    sUp;            // ��������
    sMcFmt11_f  sDown;            // ��������
}sMcNelcMpCfg_f, sMcAfn04f34_f;
#pragma pack()

// ת������
eMcErr emc_trans_afn04f34(eMcTrans eTrans, void* pUser, void* pFrame, UINT16* pusLen);
///*} 

/*******************************************
 * ��������: �ǵ���������Խ�����ݲ���
 * ��ӦAFN : MC_AFN_04_SETP
 * ��ӦCMD : MCMD_AFN_4_F35_NELC_MP_LMIT
 * PN ���� : �����������
{*///
// �û���
typedef struct
{
    eMcNElcType eType;           // �ǵ���������
    sMcDouble    sUp;             // Խ���޶�ֵ
    sMcDouble    sDown;           // Խ���޶�ֵ

}sMcNelcMpLimit, sMcAfn0435;

// ��֡��
#pragma pack(1)
typedef struct
{
    UINT8       eType;            // �ǵ���������
    sMcFmt11_f    sUp;            // Խ���޶�ֵ
    sMcFmt11_f  sDown;            // Խ���޶�ֵ
}sMcNelcMpLimit_f, sMcAfn0435_f;
#pragma pack()

// ת������
eMcErr emc_trans_afn04f35(eMcTrans eTrans, void* pUser, void* pFrame, UINT16* pusLen);
///*} 

/*******************************************
 * ��������: ���������������
 * ��ӦAFN : MC_AFN_04_SETP
 * ��ӦCMD : MCMD_AFN_4_F49_FREZ_TASK_PARA
 * PN ���� : �����������
{*///
// �û���
typedef enum
{
    MC_PUNT_UNKOWN,  // δ֪�����ڵ�λ
    MC_PUNT_MONTH,   // ��
    MC_PUNT_DAY,     // ��
    MC_PUNT_HOUR,    // ʱ
    MC_PUNT_MIN,     // ����
    MC_PUNT_SEC,     // ��
    MC_PUNT_MS,      // ����
}eMcPeriodUnit;      // �������ڵ�λ

typedef struct
{
    UINT16         usPeriod;         // �������� Ϊ��ʱ�����ʱ������Ϊ0��ʾɾ�����������
    eMcPeriodUnit     eUnit;         // �������ڵ�λ
    UINT8           ucTimes;         // ��������������ʾ�Զ�������Ϊ������足��Ĵ�����Ϊ0��ʾ���޴����� 
}sMcFrezPeriod;

typedef struct
{
    sMcYWMDhms      sTimeFrez;         // �����׼ʱ�䣺���ʱ������ 
    sMcYWMDhms      sTimeRprt;         // �ϱ���׼ʱ�䣺���ʱ������
    sMcFrezPeriod      sFreez;         // ��������
    UINT8         ucPeriodRpt;         // ��ʱ�ϱ�����    ��Ϊ��ʱ�ϱ����ݵ�ʱ������0Ϊ����������������趨ʱ�ϱ���
    eMcPeriodUnit    eUnitRpt;         // ��ʱ�ϱ����ڵ�λ����ֵ��Χ1~4�����ηֱ��ʾ�֡�ʱ���ա��£���������
    UINT8           uCmdPnNum;         // ��Ҫ��������ݵ�Ԫ��ʶ ����
    sMcmdPn         sCmdPn[1];         // ��Ҫ��������ݵ�Ԫ��ʶ ����
    
}sMcFrezTaskPara, sMcAfn04f49;

// ��֡��
#pragma pack(1)
typedef struct
{
    UINT16         usPeriod;         // �������� Ϊ��ʱ�����ʱ������Ϊ0��ʾɾ�����������
    UINT8             eUnit;         // �������ڵ�λ
    UINT8           ucTimes;         // ��������������ʾ�Զ�������Ϊ������足��Ĵ�����Ϊ0��ʾ���޴����� 
}sMcFrezPeriod_f;

typedef struct
{
    sMcFmt01_f        sTimeFrez;     // �����׼ʱ�䣺���ʱ������ 
    sMcFrezPeriod_f      sFreez;     // �������� 
    UINT8             ucDaDtNum;     // ���ݵ�Ԫ��ʶ����

    // ����Ϊ�䳤
    /*
    sMcDaDt        sDaDt[1];         // ucDaDtNum �����ݵ�Ԫ��ʶ
    sMcFmt01_f        sTimeRprt;     // �����׼ʱ�䣺���ʱ������ 
    UINT8             eUnit;         // ��ʱ�ϱ�����
    UINT8           ucTimes;         // ��ʱ�ϱ����ڵ�λ 
    */
}sMcFrezTaskPara_f, sMcAfn04f49_f;
#pragma pack()

// ת������
eMcErr emc_trans_afn04f49(eMcTrans eTrans, void* pUser, void* pFrame, UINT16* pusLen);
///*} 

/*******************************************
 * ��������: Уʱ����
 * ��ӦAFN : MC_AFN_04_SETP
 * ��ӦCMD : MCMD_AFN_5_F1_CHECK_TIME
 * PN ���� : �����������
{*///

// �û���
// sMcYWMDhms
// ��֡��
// sMcYWMDhms_f

// ת������
eMcErr emc_trans_afn05f1(eMcTrans eTrans, void* pUser, void* pFrame, UINT16* pusLen);
///*} 

/*******************************************
 * ��������: ��ʱ��������
 * ��ӦAFN : MC_AFN_05_CTRL
 * ��ӦCMD : MCMD_AFN_5_F2_FREZ_TEMP
 * PN ���� : �����������
{*///
// �û���
typedef struct
{
    UINT8         ucNum;    // ���ݵ�Ԫ��ʶ����
    sMcmdPn   sCmdPn[1];    // ucNum �����ݵ�Ԫ��ʶ
}sMcFrezTemp, sMcAfn05f2;

// ��֡��
typedef struct
{
    UINT8         ucNum;     // ���ݵ�Ԫ��ʶ���� DaDt
    sMcDaDt    sDaDt[1];  // ucNum ��DaDt
}sMcFrezTemp_f, sMcAfn05f2_f;

// ת������
eMcErr emc_trans_afn05f2(eMcTrans eTrans, void* pUser, void* pFrame, UINT16* pusLen);
///*} 

/*******************************************
 * ��������: ң����բ
 * ��ӦAFN : MC_AFN_05_CTRL
 * ��ӦCMD : MCMD_AFN_5_F9_REMOTE_OFF
 * PN ���� : �����������
{*///
// �û���
typedef struct
{
    BOOL         bOff[8];    // ��1-8��������Ƿ���բ
    sMcYMDhm sTimeStart;    // ��բ��ʼʱ�� 
    sMcYMDhm   sTimeEnd;    // ��բ����ʱ�� 
}sMcRemoteOff, sMcAfn05f9;

// ��֡��
#pragma pack(1)
typedef struct
{
    UINT8         bOff;      // ÿһbit��ʾ��1-8��������Ƿ����
    sMcYMDhm_f sTimeStart;  // ��բ��ʼʱ�� 
    sMcYMDhm_f   sTimeEnd;  // ��բ����ʱ��   

}sMcRemoteOff_f, sMcAfn05f9_f;
#pragma pack()

// ת������
eMcErr emc_trans_afn05f9(eMcTrans eTrans, void* pUser, void* pFrame, UINT16* pusLen);
///*} 

/*******************************************
 * ��������: �����բ
 * ��ӦAFN : MC_AFN_05_CTRL
 * ��ӦCMD : MCMD_AFN_5_F10_REMOTE_ON
 * PN ���� : �����������
{*///
// �û���
typedef struct
{
    BOOL         bOn[8];    // ��1-8��������Ƿ���բ
}sMcRemoteOn, sMcAfn05f10;

// ��֡��
#pragma pack(1)
typedef struct
{
    UINT8         bOn;      // ÿһbit��ʾ��1-8��������Ƿ����
 
}sMcRemoteOn_f, sMcAfn05f10_f;
#pragma pack()

// ת������
eMcErr emc_trans_afn05f10(eMcTrans eTrans, void* pUser, void* pFrame, UINT16* pusLen);
///*} 

/*******************************************
 * ��������: ��Чģ����Ч
 * ��ӦAFN : MC_AFN_05_CTRL
 * ��ӦCMD : MCMD_AFN_5_F17_NX_MODEL_ACT
 * PN ���� : p0/����ն˺�
{*///
// �û���
typedef struct
{
    UINT8        ucID;       // ��N����Чģʽ���
    sMcYWMDhms  sTime;       // ��ʼʱ��:������ʱ����
}sMcNxModelOne;

typedef struct
{
    UINT8              ucN;  // ��Чģ�͸���
    sMcNxModelOne  sOne[1];  // ��n����Чģ�� һ��N����Чģ��

}sMcNxModelAct, sMcAfn05f17;

// ��֡��
#pragma pack(1)
typedef struct
{
    UINT8         ucID;       // ��N����Чģʽ���
    sMcYWMDhms_f  sTime;      // ��ʼʱ��:������ʱ����
}sMcNxModelOne_f;

typedef struct
{
    UINT8              ucN;  // ��Чģ�͸���
    sMcNxModelOne_f   sOne[1];  // ��n����Чģ�� һ��N����Чģ��
}sMcNxModelAct_f, sMcAfn05f17_f;
#pragma pack()

// ת������
eMcErr emc_trans_afn05f17(eMcTrans eTrans, void* pUser, void* pFrame, UINT16* pusLen);
///*} 

/*******************************************
 * ��������: ��Чģ�����
 * ��ӦAFN : MC_AFN_05_CTRL
 * ��ӦCMD : MCMD_AFN_5_F18_NX_MODEL_CLR
 * PN ���� : p0/����ն˺�
{*///
// �û���
typedef struct
{
    UINT8            ucN;  // ��Чģ�͸���
    UINT8        ucID[1];  // ��n����Чģ�ͱ��
}sMcNxModelClr, sMcAfn05f18;

// ��֡��
#pragma pack(1)
typedef struct
{
    UINT8            ucN;  // ��Чģ�͸���
    UINT8        ucID[1];  // ��n����Чģ�ͱ��
}sMcNxModelClr_f, sMcAfn05f18_f;
#pragma pack()

// ת������
eMcErr emc_trans_afn05f18(eMcTrans eTrans, void* pUser, void* pFrame, UINT16* pusLen);
///*} 

/*******************************************
 * ��������: ������Ӧ��Ϣ��Ч
 * ��ӦAFN : MC_AFN_05_CTRL
 * ��ӦCMD : MCMD_AFN_5_F19_RQ_RESPN_ACT
 * PN ���� : p0/����ն˺�
{*///
// �û���
typedef struct
{
    UINT8            ucN;  // ������Ӧ��Ϣ����n
    UINT8        ucID[1];  // ��n��������Ӧ��Ϣ���
}sMcRqRespnAct, sMcAfn05f19;

// ��֡��
#pragma pack(1)
typedef struct
{
    UINT8            ucN;  // ������Ӧ��Ϣ����n
    UINT8        ucID[1];  // ��n��������Ӧ��Ϣ���
}sMcRqRespnAct_f, sMcAfn05f19_f;
#pragma pack()

// ת������
eMcErr emc_trans_afn05f19(eMcTrans eTrans, void* pUser, void* pFrame, UINT16* pusLen);
///*} 

/*******************************************
 * ��������: ������Ӧ��Ϣ���
 * ��ӦAFN : MC_AFN_05_CTRL
 * ��ӦCMD : MCMD_AFN_5_F20_RQ_RESPN_CLT
 * PN ���� : p0/����ն˺�
{*///
// �û���
typedef struct
{
    UINT8            ucN;  // ������Ӧ��Ϣ����n
    UINT8        ucID[1];  // ��n��������Ӧ��Ϣ���
}sMcRqRespnClr, sMcAfn05f20;

// ��֡��
#pragma pack(1)
typedef struct
{
    UINT8            ucN;  // ������Ӧ��Ϣ����n
    UINT8        ucID[1];  // ��n��������Ӧ��Ϣ���
}sMcRqRespnClr_f, sMcAfn05f20_f;
#pragma pack()

// ת������
eMcErr emc_trans_afn05f20(eMcTrans eTrans, void* pUser, void* pFrame, UINT16* pusLen);
///*} 

/*******************************************
 * ��������: ��ѯ��(��)վ����  (�������)
 * ��ӦAFN : MC_AFN_10_GETP
 * ��ӦCMD : MCMD_AFN_A_F2_MST_PARA
 * PN ���� : p0/����ն˺�
{*///
// �û���
typedef struct
{
    UINT8            ucN;  // ���β�ѯ����(��)վ��n
    UINT8        ucID[1];  // ��n����(��)���
}sMcMstParaQ, sMcAfn11f2q;

// ��֡��
#pragma pack(1)
typedef struct
{
    UINT8            ucN;  // ���β�ѯ����(��)վ��n
    UINT8        ucID[1];  // ��n����(��)���
}sMcMstParaQ_f, sMcAfn11f2q_f;
#pragma pack()

// ת������
eMcErr emc_trans_afn10f2_m2s(eMcTrans eTrans, void* pUser, void* pFrame, UINT16* pusLen);
///*} 

/*******************************************
 * ��������: ��ѯ��(��)վ����  (����Ӧ��)
 * ��ӦAFN : MC_AFN_10_GETP
 * ��ӦCMD : MCMD_AFN_A_F2_MST_PARA
 * PN ���� : p0/����ն˺�
{*///
// �û���
typedef sMcMstPara sMcMstParaA, sMcAfn11f2a;

// ��֡��
#pragma pack(1)
typedef sMcMstPara_f sMcMstParaA_f, sMcAfn11f2a_f;
#pragma pack()

// ת������
eMcErr emc_trans_afn10f2_s2m(eMcTrans eTrans, void* pUser, void* pFrame, UINT16* pusLen);
///*} 

/*******************************************
 * ��������: ��Ϣ�����뽻���ն�������̫���˿�ͨ�Ų��� (ѯ��)
 * ��ӦAFN : MC_AFN_10_GETP
 * ��ӦCMD : MCMD_AFN_A_F7_CON_DOWN_CFG
 * PN ���� : p0/����ն˺�
{*///
// �û���
typedef struct
{
    UINT16            usN;     // ���β�ѯ��n
    UINT16        usPort[1];  // ��n���˿ں�
}sMcDownCfgQ, sMcAfn10f7q;

// ��֡��
#pragma pack(1)
typedef struct
{
    UINT16            usN;     // ���β�ѯ��n
    UINT16        usPort[1];  // ��n���˿ں�
}sMcDownCfgQ_f, sMcAfn10f7q_f;
#pragma pack()

// ת������
eMcErr emc_trans_afn10f7_m2s(eMcTrans eTrans, void* pUser, void* pFrame, UINT16* pusLen);
///*} 

/*******************************************
 * ��������: ��Ϣ�����뽻���ն�������̫���˿�ͨ�Ų��� (Ӧ��)
 * ��ӦAFN : MC_AFN_10_GETP
 * ��ӦCMD : MCMD_AFN_A_F7_CON_DOWN_CFG
 * PN ���� : p0/����ն˺�
{*///
// �û���
typedef struct
{
    UINT8            ucN;     // ���β�ѯ��n
    sMcDownCfg      sOne[1];  // ��n������
}sMcDownCfgA, sMcAfn10f7a;

// ��֡��
#pragma pack(1)
typedef struct
{
    UINT8            ucN;     // ���β�ѯ��n
    sMcDownCfg_f  sOne[1];    // ��n������
}sMcDownCfgA_f, sMcAfn10f7a_f;
#pragma pack()

// ת������
eMcErr emc_trans_afn10f7_s2m(eMcTrans eTrans, void* pUser, void* pFrame, UINT16* pusLen);
///*} 

/*******************************************
 * ��������: �豸�߼���ַ(ѯ��û�в��� Ӧ�𱾽ṹ)
 * ��ӦAFN : MC_AFN_10_GETP
 * ��ӦCMD : MCMD_AFN_A_F11_CON_LOGIC_ADDR
 * PN ���� : p0/����ն˺�
{*///
// �û���
typedef sMcA sMcLogicAddr, sMcAfn10f11;

// ��֡��
#pragma pack(1)
typedef sMcA_f sMcLogicAddr_f, sMcAfn10f11_f;
#pragma pack()

// ת������
eMcErr emc_trans_afn10f11(eMcTrans eTrans, void* pUser, void* pFrame, UINT16* pusLen);
///*} 

/*******************************************
 * ��������: ��ѯ�豸�汾��Ϣ(ѯ��û�в��� Ӧ��Ϊ���ṹ)
 * ��ӦAFN : MC_AFN_10_GETP
 * ��ӦCMD : MCMD_AFN_A_F12_CON_VERSION
 * PN ���� : p0/����ն˺�
{*///
// �û���
typedef struct
{
    UINT8             ucID;       // ģ����
    UINT8    strVersion[4];       // ģ��汾��
    sMcYMDhm         sTime;       // ģ�������������: ��ʱ������
}sMcVerModel;

typedef struct
{
    UINT8    strFactory[4];       // ���̴���
    UINT8      ucDevId[12];       // �豸ID  12λ����
    UINT8       strCap[11];       // ����������Ϣ��
    UINT8       strSoft[4];       // ����汾
    UINT8       strHard[4];       // Ӳ���汾
    sMcYMDhm         sTime;       // �����������: ��ʱ������
    UINT8              ucN;       // ģ����n
    sMcVerModel    sOne[1];       // ��n��ģ�����ϸ����
    
}sMcVersion, sMcAfn10f12;

// ��֡��
#pragma pack(1)
typedef struct
{
    UINT8             ucID;       // ģ����
    UINT8    strVersion[4];       // ģ��汾��
    sMcYMDhm_f       sTime;       // ģ�������������: ��ʱ������
}sMcVerModel_f;

typedef struct
{
    UINT8    strFactory[4];       // ���̴���
    UINT8       ucDevId[6];       // �豸ID  12λ����  ����ΪBCD
    UINT8       strCap[11];       // ����������Ϣ��
    UINT8       strSoft[4];       // ����汾
    UINT8       strHard[4];       // Ӳ���汾
    sMcYMDhm_f       sTime;       // �����������: ��ʱ������
    UINT8              ucN;       // ģ����n
    sMcVerModel_f  sOne[1];       // ��n��ģ�����ϸ����
    
}sMcVersion_f, sMcAfn10f12_f;
#pragma pack()

// ת������
eMcErr emc_trans_afn10f12(eMcTrans eTrans, void* pUser, void* pFrame, UINT16* pusLen);
///*} 

/*******************************************
 * ��������: �����õ�����������Ϣ(ѯ��û�в��� Ӧ�𱾽ṹ)
 * ��ӦAFN : MC_AFN_10_GETP
 * ��ӦCMD : MCMD_AFN_A_F13_ELEC_MP_INFO
 * PN ���� : p0/����ն˺�
{*///
// �û���
typedef struct
{
    UINT8    ucSprt;          // ֧�ֵĲ�������Ϣ��������n (1 < n < 255)
    UINT16    usNum;          // �Ѿ����õ�Pn����
    UINT16  usPn[1];          // ���õľ���pn
}sMcElecMpInfo, sMcAfn10f13;

// ��֡��
#pragma pack(1)
typedef struct
{
    UINT8   ucSprt;           // ֧�ֵĲ�������Ϣ��������n (1 < n < 255)
    UINT8   ucSDa2;           // ��֡�ϱ�����ʼ��Ϣ����DA2 (1 < m < 255)
    UINT8   ucK;              // ��֡�ϱ��ĸ���
    UINT8   ucDa1[1];         // ��i ����Ϣ����DA2����Ӧ��DA1��i=m~m+k-1�� 
}sMcElecMpInfo_f, sMcAfn10f13_f;
#pragma pack()

// ת������
eMcErr emc_trans_afn10f13(eMcTrans eTrans, void* pUser, void* pFrame, UINT16* pusLen);
///*} 

/*******************************************
 * ��������: �����÷ǵ�����������Ϣ(ѯ��û�в��� Ӧ�𱾽ṹ)
 * ��ӦAFN : MC_AFN_10_GETP
 * ��ӦCMD : MCMD_AFN_A_F14_NELC_MP_INFO
 * PN ���� : p0/����ն˺�
{*///
// �û���
typedef struct
{
    UINT8    ucSprt;          // ֧�ֵĲ�������Ϣ��������n (1 < n < 255)
    UINT16    usNum;          // �Ѿ����õ�Pn����
    UINT16  usPn[1];          // ���õľ���pn
}sMcNelcMpInfo, sMcAfn10f14;

// ��֡��
#pragma pack(1)
typedef struct
{
    UINT8   ucSprt;           // ֧�ֵĲ�������Ϣ��������n (1 < n < 255)
    UINT8   ucSDa2;           // ��֡�ϱ�����ʼ��Ϣ����DA2 (1 < m < 255)
    UINT8   ucK;              // ��֡�ϱ��ĸ���
    UINT8   ucDa1[1];         // ��i ����Ϣ����DA2����Ӧ��DA1��i=m~m+k-1�� 
}sMcNelcMpInfo_f, sMcAfn10f14_f;
#pragma pack()

// ת������
eMcErr emc_trans_afn10f14(eMcTrans eTrans, void* pUser, void* pFrame, UINT16* pusLen);
///*} 

/*******************************************
 * ��������: �豸֧�ֵ��¼���¼(ѯ��û�в��� Ӧ�𱾽ṹ)
 * ��ӦAFN : MC_AFN_10_GETP
 * ��ӦCMD : MCMD_AFN_A_F15_SUPT_EVENT
 * PN ���� : p0/����ն˺�
{*///
// �û���
typedef struct
{
   BOOL  bSuprt[MC_ERC_NUM_MAX];    // �Ը��¼��Ƿ�֧��
   
}sMcSuptEvent, sMcAfn10f15;

// ��֡��
#pragma pack(1)
typedef struct
{
   UINT8   ucEvent[8];              // D0~D63��˳���Ӧ��ʾ�¼�����ERC1~ERC64��������¼�
   
}sMcSuptEvent_f, sMcAfn10f15_f;
#pragma pack()

// ת������
eMcErr emc_trans_afn10f15(eMcTrans eTrans, void* pUser, void* pFrame, UINT16* pusLen);
///*} 

/*******************************************
 * ��������: ��ѯ�����ü���ն���Ϣ(ѯ��û�в��� Ӧ�𱾽ṹ)
 * ��ӦAFN : MC_AFN_10_GETP
 * ��ӦCMD : MCMD_AFN_A_F57_TML_CFG_INFO
 * PN ���� : p0/����ն˺�
{*///
// �û���
typedef struct
{
    UINT8    ucSprt;          // ֧�ֵĲ�������Ϣ��������n (1 < n < 255)
    UINT16    usNum;          // �Ѿ����õ�Pn����
    UINT16  usPn[1];          // ���õľ���pn
}sMcTmlCfgInfo, sMcAfn10f57;

// ��֡��
#pragma pack(1)
typedef struct
{
    UINT8   ucSprt;           // ֧�ֵĲ�������Ϣ��������n (1 < n < 255)
    UINT8   ucSDa2;           // ��֡�ϱ�����ʼ��Ϣ����DA2 (1 < m < 255)
    UINT8   ucK;              // ��֡�ϱ��ĸ���
    UINT8   ucDa1[1];         // ��i ����Ϣ����DA2����Ӧ��DA1��i=m~m+k-1�� 
}sMcTmlCfgInfo_f, sMcAfn10f57_f;
#pragma pack()

// ת������
eMcErr emc_trans_afn10f57(eMcTrans eTrans, void* pUser, void* pFrame, UINT16* pusLen);
///*} 

/*******************************************
 * ��������: ����ʱ��(Ӧ���ʽ)
 * ��ӦAFN : MC_AFN_13_ASKR
 * ��ӦCMD : MCMD_AFN_D_F1_CLOCK
 * PN ���� : p0/����ն˺�
{*///
// �û���
typedef sMcUerClock sMcClock, sMcAfn13f1;

// ��֡��
#pragma pack(1)
typedef sMcUerClock_f sMcClock_f, sMcAfn13f1_f;
#pragma pack()

// ת������
eMcErr emc_trans_afn13f1(eMcTrans eTrans, void* pUser, void* pFrame, UINT16* pusLen);
///*} 

/*******************************************
 * ��������: ����״̬��־(Ӧ���ʽ)
 * ��ӦAFN : MC_AFN_13_ASKR
 * ��ӦCMD : MCMD_AFN_D_F2_PARA_STATE
 * PN ���� : p0/����ն˺�
{*///

// Ŀǰ�������õĲ�������Ϊ20(MCMD_AFN_4_F1_CON_UP_CFG  �� MCMD_AFN_4_F49_FREZ_TASK_PARA)
#define MC_SET_NUM_MAX  (20)     

// �û���
typedef struct
{
    UINT8    ucNum;  // �Ѿ����õĸ���
    eMcmd  eCmd[1];  // �Ѿ����õĲ�������
}sMcParaState, sMcAfn13f2;

// ��֡��
#pragma pack(1)
typedef struct
{
    UINT8  ucSet[31];
}sMcParaState_f, sMcAfn13f2_f;
#pragma pack()

// ת������
eMcErr emc_trans_afn13f2(eMcTrans eTrans, void* pUser, void* pFrame, UINT16* pusLen);
///*} 

/*******************************************
 * ��������: ��Ҫ�¼���������ǰֵ(Ӧ���ʽ)
 * ��ӦAFN : MC_AFN_13_ASKR
 * ��ӦCMD : MCMD_AFN_D_F3_EVENT_1
 * PN ���� : p0/����ն˺�
{*///

// �û���
// UINT16 usEc1

// ��֡��
// UINT16 usEc1_f

// ת������
eMcErr emc_trans_afn13f3(eMcTrans eTrans, void* pUser, void* pFrame, UINT16* pusLen);
///*} 

/*******************************************
 * ��������: һ���¼���������ǰֵ(Ӧ���ʽ)
 * ��ӦAFN : MC_AFN_13_ASKR
 * ��ӦCMD : MCMD_AFN_D_F4_EVENT_2
 * PN ���� : p0/����ն˺�
{*///

// �û���
// UINT16 usEc2

// ��֡��
// UINT16 ucEc2_f

// ת������
eMcErr emc_trans_afn13f4(eMcTrans eTrans, void* pUser, void* pFrame, UINT16* pusLen);
///*} 

/*******************************************
 * ��������: �¼�״̬��־(Ӧ���ʽ)
 * ��ӦAFN : MC_AFN_13_ASKR
 * ��ӦCMD : MCMD_AFN_D_F5_EVENT_STATE
 * PN ���� : p0/����ն˺�
{*///

// �û���
typedef struct
{
    BOOL bHave[MC_ERC_NUM_MAX];      // ��:���¼� ��: ���¼� 
}sMcEventState, sMcAfn13f5;

// ��֡��
#pragma pack(1)
typedef struct
{
    UINT8   ucHave[8];               // ÿ��bit�����Ƿ��ж�Ӧ���¼�����
}sMcEventState_f, sMcAfn13f5_f;
#pragma pack()

// ת������
eMcErr emc_trans_afn13f5(eMcTrans eTrans, void* pUser, void* pFrame, UINT16* pusLen);
///*} 

/*******************************************
 * ��������: �ϵ����(Ӧ���ʽ)
 * ��ӦAFN : MC_AFN_13_ASKR
 * ��ӦCMD : MCMD_AFN_D_F6_POWR_TIMES
 * PN ���� : p0/����ն˺�
{*///

#define MC_POWR_TIMES_MAX (999999)
// �û���
typedef struct
{
    UINT32 ulTimes;    //  (0-999999)
}sMcPowerTimes, sMcAfn13f6;

// ��֡��
#pragma pack(1)
typedef struct
{
    UINT8   ucBcd[3];       // BCD��ʽ
}sMcPowerTimes_f, sMcAfn13f6_f;
#pragma pack()

// ת������
eMcErr emc_trans_afn13f6(eMcTrans eTrans, void* pUser, void* pFrame, UINT16* pusLen);
///*} 

/*******************************************
 * ��������: ״̬������λ��־(Ӧ���ʽ)
 * ��ӦAFN : MC_AFN_13_ASKR
 * ��ӦCMD : MCMD_AFN_D_F9_STATE
 * PN ���� : p0/����ն˺�
{*///

// �û���
typedef struct
{
    BOOL bSt[8];   // ��ʾ1-8·״̬����״̬ST ��:��, ��:��          
    BOOL bCd[8];   // ��ʾ1-8·״̬���ı仯CD 
                   // ��:��ǰ��ң�Ŵ��ͺ�������һ��״̬�仯
                   // ��:��ǰ��ң�Ŵ��ͺ�û��״̬�仯
}sMcState, sMcAfn13f9;

// ��֡��
#pragma pack(1)
typedef struct
{
    UINT8  ucSt8;
    UINT8  ucCd8;
}sMcState_f, sMcAfn13f9_f;
#pragma pack()

// ת������
eMcErr emc_trans_afn13f9(eMcTrans eTrans, void* pUser, void* pFrame, UINT16* pusLen);
///*} 

/*******************************************
 * ��������: ���������·���ؽ���״̬������λ��־(Ӧ���ʽ)
 * ��ӦAFN : MC_AFN_13_ASKR
 * ��ӦCMD : MCMD_AFN_D_F10_SWITCH
 * PN ���� : p0/����ն˺�
{*///

// �û���
typedef struct
{
    BOOL bSt[4];   // ��ʾ1-4·����������������մ�����뿪����բ��·״̬����״̬ST     
                   // ��:���� ��:δ����
    BOOL bCd[4];   // ��ʾ1-4·����������������մ�����뿪����բ��·״̬���ı仯CD 
                   // ��:��ǰ��ң�Ŵ��ͺ�������һ��״̬�仯
                   // ��:��ǰ��ң�Ŵ��ͺ�û��״̬�仯
}sMcSwitch, sMcAfn13f10;

// ��֡��
#pragma pack(1)
typedef struct
{
    UINT8  ucSt8;
    UINT8  ucCd8;
}sMcSwitch_f, sMcAfn13f10_f;
#pragma pack()

// ת������
eMcErr emc_trans_afn13f10(eMcTrans eTrans, void* pUser, void* pFrame, UINT16* pusLen);
///*} 

/*******************************************
 * ��������: ���й�����(Ӧ���ʽ)
 * ��ӦAFN : MC_AFN_13_ASKR
 * ��ӦCMD : MCMD_AFN_D_F25_POWR_HAVE_T
 * PN ���� : p0/����ն˺�
{*///
// �û���
typedef struct
{
    float fXX_XXXX;              //  ���й�����(Kw) (+)XX.XXXX
}sMcPowerHaveT, sMcAfn13f25;

// ��֡��
#pragma pack(1)
typedef struct
{
    sMcFmt06_f fXX_XXXX;       
}sMcPowerHaveT_f, sMcAfn13f25_f;
#pragma pack()

// ת������
eMcErr emc_trans_afn13f25(eMcTrans eTrans, void* pUser, void* pFrame, UINT16* pusLen);
///*} 

/*******************************************
 * ��������: ���޹�����(Ӧ���ʽ)
 * ��ӦAFN : MC_AFN_13_ASKR
 * ��ӦCMD : MCMD_AFN_D_F26_POWR_NONE_T
 * PN ���� : p0/����ն˺�
{*///

// �û���
typedef struct
{
    float fXX_XXXX;             //  ���޹�����(Kw) (+)XX.XXXX
}sMcPowerNoneT, sMcAfn13f26;

// ��֡��
#pragma pack(1)
typedef struct
{
    sMcFmt06_f fXX_XXXX;       
}sMcPowerNoneT_f, sMcAfn13f26_f;
#pragma pack()

// ת������
eMcErr emc_trans_afn13f26(eMcTrans eTrans, void* pUser, void* pFrame, UINT16* pusLen);
///*} 

/*******************************************
 * ��������: �ܹ�������(Ӧ���ʽ)
 * ��ӦAFN : MC_AFN_13_ASKR
 * ��ӦCMD : MCMD_AFN_D_F27_FACTR_T
 * PN ���� : p0/����ն˺�
{*///

// �û���
typedef struct
{
    float fXX_XX;             //  �ܹ������� (+)XX.XX
}sMcFactorT, sMcAfn13f27;

// ��֡��
#pragma pack(1)
typedef struct
{
    sMcFmt10_f fXX_XX;       
}sMcFactorT_f, sMcAfn13f27_f;
#pragma pack()

// ת������
eMcErr emc_trans_afn13f27(eMcTrans eTrans, void* pUser, void* pFrame, UINT16* pusLen);
///*} 

/*******************************************
 * ��������: A�๦������(Ӧ���ʽ)
 * ��ӦAFN : MC_AFN_13_ASKR
 * ��ӦCMD : MCMD_AFN_D_F28_FACTR_A
 * PN ���� : p0/����ն˺�
{*///

// �û���
typedef struct
{
    float fXX_XX;             //  A�๦������ (+)XX.XX
}sMcFactorA, sMcAfn13f28;

// ��֡��
#pragma pack(1)
typedef struct
{
    sMcFmt10_f fXX_XX;       
}sMcFactorA_f, sMcAfn13f28_f;
#pragma pack()

// ת������
eMcErr emc_trans_afn13f28(eMcTrans eTrans, void* pUser, void* pFrame, UINT16* pusLen);
///*} 

/*******************************************
 * ��������: B�๦������(Ӧ���ʽ)
 * ��ӦAFN : MC_AFN_13_ASKR
 * ��ӦCMD : MCMD_AFN_D_F29_FACTR_B
 * PN ���� : p0/����ն˺�
{*///

// �û���
typedef struct
{
    float fXX_XX;             //  B�๦������ (+)XX.XX
}sMcFactorB, sMcAfn13f29;

// ��֡��
#pragma pack(1)
typedef struct
{
    sMcFmt10_f fXX_XX;       
}sMcFactorB_f, sMcAfn13f29_f;
#pragma pack()

// ת������
eMcErr emc_trans_afn13f29(eMcTrans eTrans, void* pUser, void* pFrame, UINT16* pusLen);
///*} 

/*******************************************
 * ��������: C�๦������(Ӧ���ʽ)
 * ��ӦAFN : MC_AFN_13_ASKR
 * ��ӦCMD : MCMD_AFN_D_F30_FACTR_C
 * PN ���� : p0/����ն˺�
{*///
// �û���
typedef struct
{
    float fXX_XX;             //  C�๦������ (+)XX.XX
}sMcFactorC, sMcAfn13f30;

// ��֡��
#pragma pack(1)
typedef struct
{
    sMcFmt10_f fXX_XX;       
}sMcFactorC_f, sMcAfn13f30_f;
#pragma pack()

// ת������
eMcErr emc_trans_afn13f30(eMcTrans eTrans, void* pUser, void* pFrame, UINT16* pusLen);
///*} 

/*******************************************
 * ��������: ����(Ӧ���ʽ)
 * ��ӦAFN : MC_AFN_13_ASKR
 * ��ӦCMD : MCMD_AFN_D_F33_DEMAND
 * PN ���� : p0/����ն˺�
{*///
// �û���
typedef struct
{
    float fXX_XXXX;             //  ���� (+/-)XX.XXXX
}sMcDemand, sMcAfn13f33;

// ��֡��
#pragma pack(1)
typedef struct
{
    sMcFmt06_f fXX_XXXX;       
}sMcDemand_f, sMcAfn13f33_f;
#pragma pack()

// ת������
eMcErr emc_trans_afn13f33(eMcTrans eTrans, void* pUser, void* pFrame, UINT16* pusLen);
///*} 

/*******************************************
 * ��������: ���������(Ӧ���ʽ)
 * ��ӦAFN : MC_AFN_13_ASKR
 * ��ӦCMD : MCMD_AFN_D_F34_DEMAND_MAX
 * PN ���� : p0/����ն˺�
{*///
// �û���
typedef struct
{
    float fXX_XXXX;             //  ��������� (+/-)XX.XXXX
}sMcDemandMax, sMcAfn13f34;

// ��֡��
#pragma pack(1)
typedef struct
{
    sMcFmt06_f fXX_XXXX;       
}sMcDemandMax_f, sMcAfn13f34_f;
#pragma pack()

// ת������
eMcErr emc_trans_afn13f34(eMcTrans eTrans, void* pUser, void* pFrame, UINT16* pusLen);
///*} 

/*******************************************
 * ��������: �������������ʱ��(Ӧ���ʽ)
 * ��ӦAFN : MC_AFN_13_ASKR
 * ��ӦCMD : MCMD_AFN_D_F35_DEMAND_TIME
 * PN ���� : p0/����ն˺�
{*///
// �û���
typedef struct
{
    sMcYMDhm sTime;             //  �������������ʱ�� ������ʱ��
}sMcDemandTime, sMcAfn13f35;

// ��֡��
#pragma pack(1)
typedef struct
{
    sMcFmt02_f sTime;       
}sMcDemandTime_f, sMcAfn13f35_f;
#pragma pack()

// ת������
eMcErr emc_trans_afn13f35(eMcTrans eTrans, void* pUser, void* pFrame, UINT16* pusLen);
///*} 

/*******************************************
 * ��������: A���й�����(Ӧ���ʽ)
 * ��ӦAFN : MC_AFN_13_ASKR
 * ��ӦCMD : MCMD_AFN_D_F41_POWR_HAVE_A
 * PN ���� : p0/����ն˺�
{*///
// �û���
typedef struct
{
    float fXX_XX;             //  A���й����� (+)XX.XX
}sMcPowerHaveA, sMcAfn13f41;

// ��֡��
#pragma pack(1)
typedef struct
{
    sMcFmt10_f fXX_XX;       
}sMcPowerHaveA_f, sMcAfn13f41_f;
#pragma pack()

// ת������
eMcErr emc_trans_afn13f41(eMcTrans eTrans, void* pUser, void* pFrame, UINT16* pusLen);
///*} 

/*******************************************
 * ��������: B���й�����(Ӧ���ʽ)
 * ��ӦAFN : MC_AFN_13_ASKR
 * ��ӦCMD : MCMD_AFN_D_F42_POWR_HAVE_B
 * PN ���� : p0/����ն˺�
{*///
// �û���
typedef sMcPowerHaveA sMcPowerHaveB;

// ��֡��
// typdef sMcPowerHaveA_f sMcPowerHaveB_f;

// ת������
eMcErr emc_trans_afn13f42(eMcTrans eTrans, void* pUser, void* pFrame, UINT16* pusLen);
///*} 

/*******************************************
 * ��������: C���й�����(Ӧ���ʽ)
 * ��ӦAFN : MC_AFN_13_ASKR
 * ��ӦCMD : MCMD_AFN_D_F43_POWR_HAVE_C
 * PN ���� : p0/����ն˺�
{*///
// �û���
typedef sMcPowerHaveA sMcPowerHaveC;

// ��֡��
// typdef sMcPowerHaveA_f sMcPowerHaveC_f;

// ת������
eMcErr emc_trans_afn13f43(eMcTrans eTrans, void* pUser, void* pFrame, UINT16* pusLen);
///*} 

/*******************************************
 * ��������: A���޹�����(Ӧ���ʽ)
 * ��ӦAFN : MC_AFN_13_ASKR
 * ��ӦCMD : MCMD_AFN_D_F44_POWR_NONE_A
 * PN ���� : p0/����ն˺�
{*///
// �û���
typedef sMcPowerHaveA sMcPowerNoneA;

// ��֡��
// typdef sMcPowerHaveA_f sMcPowerNoneA_f;

// ת������
eMcErr emc_trans_afn13f44(eMcTrans eTrans, void* pUser, void* pFrame, UINT16* pusLen);
///*} 

/*******************************************
 * ��������: B���޹�����(Ӧ���ʽ)
 * ��ӦAFN : MC_AFN_13_ASKR
 * ��ӦCMD : MCMD_AFN_D_F45_POWR_NONE_B
 * PN ���� : p0/����ն˺�
{*///
// �û���
typedef sMcPowerHaveA sMcPowerNoneB;

// ��֡��
// typdef sMcPowerHaveA_f sMcPowerNoneB_f;

// ת������
eMcErr emc_trans_afn13f45(eMcTrans eTrans, void* pUser, void* pFrame, UINT16* pusLen);
///*} 

/*******************************************
 * ��������: C���޹�����(Ӧ���ʽ)
 * ��ӦAFN : MC_AFN_13_ASKR
 * ��ӦCMD : MCMD_AFN_D_F46_POWR_NONE_C
 * PN ���� : p0/����ն˺�
{*///
// �û���
typedef sMcPowerHaveA sMcPowerNoneC;

// ��֡��
// typdef sMcPowerHaveA_f sMcPowerNoneC_f;

// ת������
eMcErr emc_trans_afn13f46(eMcTrans eTrans, void* pUser, void* pFrame, UINT16* pusLen);
///*} 

/*******************************************
 * ��������: �������й��ܵ���ʾ��(Ӧ���ʽ)
 * ��ӦAFN : MC_AFN_13_ASKR
 * ��ӦCMD : MCMD_AFN_D_F49_POWR_HAVE_FRTH
 * PN ���� : p0/����ն˺�
{*///
// �û���
typedef struct
{
    double dXXXXXX_XXXX;           // ����ʾ��    (+)XXXXXX.XXXX    
}sMcPowerHaveFrth, sMcAfn13f49;

// ��֡��
#pragma pack(1)
typedef struct
{
    sMcFmt04_f dXXXXXX_XXXX;
}sMcPowerHaveFrth_f, sMcAfn13f49_f;
#pragma pack()

// ת������
eMcErr emc_trans_afn13f49(eMcTrans eTrans, void* pUser, void* pFrame, UINT16* pusLen);
///*} 

/*******************************************
 * ��������: �������й��ܵ���ʾ��(Ӧ���ʽ)
 * ��ӦAFN : MC_AFN_13_ASKR
 * ��ӦCMD : MCMD_AFN_D_F50_POWR_HAVE_BACK
 * PN ���� : p0/����ն˺�
{*///
// �û���
typedef sMcPowerHaveFrth sMcPowerHaveBack;

// ��֡��
// typdef sMcPowerHaveFrth_f sMcPowerHaveBack_f;

// ת������
eMcErr emc_trans_afn13f50(eMcTrans eTrans, void* pUser, void* pFrame, UINT16* pusLen);
///*} 

/*******************************************
 * ��������: �������޹��ܵ���ʾ��(Ӧ���ʽ)
 * ��ӦAFN : MC_AFN_13_ASKR
 * ��ӦCMD : MCMD_AFN_D_F51_POWR_NONE_FRTH
 * PN ���� : p0/����ն˺�
{*///
// �û���
typedef struct
{
    double dXXXXXX_XX;           // ����ʾ��    (+)XXXXXX.XX    
}sMcPowerNoneFrth, sMcAfn13f51;

// ��֡��
#pragma pack(1)
typedef struct
{
    sMcFmt05_f dXXXXXX_XX;
}sMcPowerNoneFrth_f, sMcAfn13f51_f;
#pragma pack()

// ת������
eMcErr emc_trans_afn13f51(eMcTrans eTrans, void* pUser, void* pFrame, UINT16* pusLen);
///*} 

/*******************************************
 * ��������: �������й��ܵ���ʾ��(Ӧ���ʽ)
 * ��ӦAFN : MC_AFN_13_ASKR
 * ��ӦCMD : MCMD_AFN_D_F52_POWR_NONE_BACK
 * PN ���� : p0/����ն˺�
{*///
// �û���
typedef sMcPowerNoneFrth sMcPowerNoneBack;

// ��֡��
// typdef sMcPowerNoneFrth_f sMcPowerNoneBack_f;

// ת������
eMcErr emc_trans_afn13f52(eMcTrans eTrans, void* pUser, void* pFrame, UINT16* pusLen);
///*} 

/*******************************************
 * ��������: A���ѹ(Ӧ���ʽ)
 * ��ӦAFN : MC_AFN_13_ASKR
 * ��ӦCMD : MCMD_AFN_D_F57_VOLT_A
 * PN ���� : p0/����ն˺�
{*///
// �û���
typedef struct
{
    float fXXX_X;           // ��ѹʾ�� (V)   (+)XXX.X    
}sMcVoltA, sMcAfn13f57;

// ��֡��
#pragma pack(1)
typedef struct
{
    sMcFmt08_f fXXX_X;
}sMcVoltA_f, sMcAfn13f57_f;
#pragma pack()

// ת������
eMcErr emc_trans_afn13f57(eMcTrans eTrans, void* pUser, void* pFrame, UINT16* pusLen);
///*} 

/*******************************************
 * ��������:  B���ѹ(Ӧ���ʽ)
 * ��ӦAFN : MC_AFN_13_ASKR
 * ��ӦCMD : MCMD_AFN_D_F58_VOLT_B
 * PN ���� : p0/����ն˺�
{*///
// �û���
typedef sMcVoltA sMcVoltB;

// ��֡��
//typedef sMcVoltA_f sMcVoltB_f;

// ת������
eMcErr emc_trans_afn13f58(eMcTrans eTrans, void* pUser, void* pFrame, UINT16* pusLen);
///*} 

/*******************************************
 * ��������: C���ѹ(Ӧ���ʽ)
 * ��ӦAFN : MC_AFN_13_ASKR
 * ��ӦCMD : MCMD_AFN_D_F59_VOLT_C
 * PN ���� : p0/����ն˺�
{*///
// �û���
typedef sMcVoltA sMcVoltC;

// ��֡��
//typedef sMcVoltA_f sMcVoltC_f;

// ת������
eMcErr emc_trans_afn13f59(eMcTrans eTrans, void* pUser, void* pFrame, UINT16* pusLen);
///*} 

/*******************************************
 * ��������: A���ѹ��λ��(Ӧ���ʽ)
 * ��ӦAFN : MC_AFN_13_ASKR
 * ��ӦCMD : MCMD_AFN_D_F60_VANGL_A
 * PN ���� : p0/����ն˺�
{*///
// �û���
typedef struct
{
    float fsXXX_X;           // ��ѹʾ�� (��)   (+/-)XXX.X    
}sMcVAngleA, sMcAfn13f60;

// ��֡��
#pragma pack(1)
typedef struct
{
    sMcFmt07_f fsXXX_X;
}sMcVAngleA_f, sMcAfn13f60_f;
#pragma pack()

// ת������
eMcErr emc_trans_afn13f60(eMcTrans eTrans, void* pUser, void* pFrame, UINT16* pusLen);
///*} 

/*******************************************
 * ��������:  B���ѹ��λ��(Ӧ���ʽ)
 * ��ӦAFN : MC_AFN_13_ASKR
 * ��ӦCMD : MCMD_AFN_D_F61_VANGL_B
 * PN ���� : p0/����ն˺�
{*///
// �û���
typedef sMcVAngleA sMcVAngleB;

// ��֡��
// typedef sMcVAngleA_f sMcVAngleB_f;

// ת������
eMcErr emc_trans_afn13f61(eMcTrans eTrans, void* pUser, void* pFrame, UINT16* pusLen);
///*} 

/*******************************************
 * ��������: C���ѹ��λ��(Ӧ���ʽ)
 * ��ӦAFN : MC_AFN_13_ASKR
 * ��ӦCMD : MCMD_AFN_D_F62_VANGL_C
 * PN ���� : p0/����ն˺�
{*///
// �û���
typedef sMcVAngleA sMcVAngleC;

// ��֡��
// typedef sMcVAngleA_f sMcVAngleC_f;

// ת������
eMcErr emc_trans_afn13f62(eMcTrans eTrans, void* pUser, void* pFrame, UINT16* pusLen);
///*} 

/*******************************************
 * ��������: ��ѹ��ƽ���(Ӧ���ʽ)
 * ��ӦAFN : MC_AFN_13_ASKR
 * ��ӦCMD : MCMD_AFN_D_F63_VOLT_UBL
 * PN ���� : p0/����ն˺�
{*///
// �û���
typedef sMcFactorT sMcVoltUbl;

// ��֡��
// typedef sMcFactorT_f sMcVoltUbl_f;

// ת������
eMcErr emc_trans_afn13f63(eMcTrans eTrans, void* pUser, void* pFrame, UINT16* pusLen);
///*} 

/*******************************************
 * ��������: �ܲ�(Ӧ���ʽ)
 * ��ӦAFN : MC_AFN_13_ASKR
 * ��ӦCMD : MCMD_AFN_D_F64_CIRCLE_V
 * PN ���� : p0/����ն˺�
{*///
// �û���
typedef sMcAfn13f25 sMcVCircle;

// ��֡��

// ת������
eMcErr emc_trans_afn13f64(eMcTrans eTrans, void* pUser, void* pFrame, UINT16* pusLen);
///*} 

/*******************************************
 * ��������: A�����(Ӧ���ʽ)
 * ��ӦAFN : MC_AFN_13_ASKR
 * ��ӦCMD : MCMD_AFN_D_F65_ELEC_A
 * PN ���� : p0/����ն˺�
{*///
// �û���
typedef struct
{
    float fsXXX_XXX;        //  (A) (+/-)XXX.XXX  
}sMcElecA, sMcAfn13f65;

// ��֡��
#pragma pack(1)
typedef struct
{
    sMcFmt09_f fsXXX_XXX;
}sMcElecA_f, sMcAfn13f65_f;
#pragma pack()

// ת������
eMcErr emc_trans_afn13f65(eMcTrans eTrans, void* pUser, void* pFrame, UINT16* pusLen);
///*} 

/*******************************************
 * ��������: B�����(Ӧ���ʽ)
 * ��ӦAFN : MC_AFN_13_ASKR
 * ��ӦCMD : MCMD_AFN_D_F66_ELEC_B
 * PN ���� : p0/����ն˺�
{*///
// �û���
typedef sMcElecA sMcElecB;

// ��֡��
// ת������
eMcErr emc_trans_afn13f66(eMcTrans eTrans, void* pUser, void* pFrame, UINT16* pusLen);
///*} 

/*******************************************
 * ��������: C�����(Ӧ���ʽ)
 * ��ӦAFN : MC_AFN_13_ASKR
 * ��ӦCMD : MCMD_AFN_D_F67_ELEC_C
 * PN ���� : p0/����ն˺�
{*///
// �û���
typedef sMcElecA sMcElecC;

// ��֡��
// ת������
eMcErr emc_trans_afn13f67(eMcTrans eTrans, void* pUser, void* pFrame, UINT16* pusLen);
///*} 

/*******************************************
 * ��������: �����ߵ���(Ӧ���ʽ)
 * ��ӦAFN : MC_AFN_13_ASKR
 * ��ӦCMD : MCMD_AFN_D_F68_ELEC_M
 * PN ���� : p0/����ն˺�
{*///
// �û���
typedef sMcElecA sMcElecM;

// ��֡��
// ת������
eMcErr emc_trans_afn13f68(eMcTrans eTrans, void* pUser, void* pFrame, UINT16* pusLen);
///*} 

/*******************************************
 * ��������: A�������λ��(Ӧ���ʽ)
 * ��ӦAFN : MC_AFN_13_ASKR
 * ��ӦCMD : MCMD_AFN_D_F69_EANGL_A
 * PN ���� : p0/����ն˺�
{*///
// �û���
typedef sMcAfn13f60 sMcEAngleA;

// ��֡��
// ת������
eMcErr emc_trans_afn13f69(eMcTrans eTrans, void* pUser, void* pFrame, UINT16* pusLen);
///*} 

/*******************************************
 * ��������: B�������λ��(Ӧ���ʽ)
 * ��ӦAFN : MC_AFN_13_ASKR
 * ��ӦCMD : MCMD_AFN_D_F70_EANGL_B
 * PN ���� : p0/����ն˺�
{*///
// �û���
typedef sMcAfn13f60 sMcEAngleB;

// ��֡��
// ת������
eMcErr emc_trans_afn13f70(eMcTrans eTrans, void* pUser, void* pFrame, UINT16* pusLen);
///*} 

/*******************************************
 * ��������: C�������λ��(Ӧ���ʽ)
 * ��ӦAFN : MC_AFN_13_ASKR
 * ��ӦCMD : MCMD_AFN_D_F71_EANGL_C
 * PN ���� : p0/����ն˺�
{*///
// �û���
typedef sMcAfn13f60 sMcEAngleC;

// ��֡��
// ת������
eMcErr emc_trans_afn13f71(eMcTrans eTrans, void* pUser, void* pFrame, UINT16* pusLen);
///*} 

/*******************************************
 * ��������: ������ƽ���(Ӧ���ʽ)
 * ��ӦAFN : MC_AFN_13_ASKR
 * ��ӦCMD : MCMD_AFN_D_F72_ELEC_UBL
 * PN ���� : p0/����ն˺�
{*///
// �û���
typedef sMcAfn13f60 sMcElecUbl;

// ��֡��
// ת������
eMcErr emc_trans_afn13f72(eMcTrans eTrans, void* pUser, void* pFrame, UINT16* pusLen);
///*} 

/*******************************************
 * ��������: ��A���ѹ����ֵ(Ӧ���ʽ)
 * ��ӦAFN : MC_AFN_13_ASKR
 * ��ӦCMD : MCMD_AFN_D_F73_VDMAX_A
 * PN ���� : p0/����ն˺�
{*///
// �û���
typedef sMcVoltA sMcVMaxA;

// ��֡��
// ת������
eMcErr emc_trans_afn13f73(eMcTrans eTrans, void* pUser, void* pFrame, UINT16* pusLen);
///*} 

/*******************************************
 * ��������: ��A���ѹ����ֵ����ʱ��(Ӧ���ʽ)
 * ��ӦAFN : MC_AFN_13_ASKR
 * ��ӦCMD : MCMD_AFN_D_F74_VDMAX_A_TIME
 * PN ���� : p0/����ն˺�
{*///
// �û���
typedef sMcAfn13f35 sMcVMaxATime;

// ��֡��
// ת������
eMcErr emc_trans_afn13f74(eMcTrans eTrans, void* pUser, void* pFrame, UINT16* pusLen);
///*} 

/*******************************************
 * ��������: ��B���ѹ����ֵ(Ӧ���ʽ)
 * ��ӦAFN : MC_AFN_13_ASKR
 * ��ӦCMD : MCMD_AFN_D_F75_VDMAX_B
 * PN ���� : p0/����ն˺�
{*///
// �û���
typedef sMcVoltA sMcVMaxB;

// ��֡��
// ת������
eMcErr emc_trans_afn13f75(eMcTrans eTrans, void* pUser, void* pFrame, UINT16* pusLen);
///*} 

/*******************************************
 * ��������: ��B���ѹ����ֵ����ʱ��(Ӧ���ʽ)
 * ��ӦAFN : MC_AFN_13_ASKR
 * ��ӦCMD : MCMD_AFN_D_F76_VDMAX_B_TIME
 * PN ���� : p0/����ն˺�
{*///
// �û���
typedef sMcAfn13f35 sMcVMaxBTime;

// ��֡��
// ת������
eMcErr emc_trans_afn13f76(eMcTrans eTrans, void* pUser, void* pFrame, UINT16* pusLen);
///*} 

/*******************************************
 * ��������: ��C���ѹ����ֵ(Ӧ���ʽ)
 * ��ӦAFN : MC_AFN_13_ASKR
 * ��ӦCMD : MCMD_AFN_D_F77_VDMAX_C
 * PN ���� : p0/����ն˺�
{*///
// �û���
typedef sMcVoltA sMcVMaxC;

// ��֡��
// ת������
eMcErr emc_trans_afn13f77(eMcTrans eTrans, void* pUser, void* pFrame, UINT16* pusLen);
///*} 

/*******************************************
 * ��������: ��C���ѹ����ֵ����ʱ��(Ӧ���ʽ)
 * ��ӦAFN : MC_AFN_13_ASKR
 * ��ӦCMD : MCMD_AFN_D_F78_VDMAX_C_TIME
 * PN ���� : p0/����ն˺�
{*///
// �û���
typedef sMcAfn13f35 sMcVMaxCTime;

// ��֡��
// ת������
eMcErr emc_trans_afn13f78(eMcTrans eTrans, void* pUser, void* pFrame, UINT16* pusLen);
///*} 

/*******************************************
 * ��������: ��A���������ֵ(Ӧ���ʽ)
 * ��ӦAFN : MC_AFN_13_ASKR
 * ��ӦCMD : MCMD_AFN_D_F81_IDMAX_A
 * PN ���� : p0/����ն˺�
{*///
// �û���
typedef sMcElecA sMcIMaxA;

// ��֡��
// ת������
eMcErr emc_trans_afn13f81(eMcTrans eTrans, void* pUser, void* pFrame, UINT16* pusLen);
///*} 

/*******************************************
 * ��������: ��A���������ֵ����ʱ��(Ӧ���ʽ)
 * ��ӦAFN : MC_AFN_13_ASKR
 * ��ӦCMD : MCMD_AFN_D_F82_IDMAX_A_TIME
 * PN ���� : p0/����ն˺�
{*///
// �û���
typedef sMcAfn13f35 sMcIMaxATime;

// ��֡��
// ת������
eMcErr emc_trans_afn13f82(eMcTrans eTrans, void* pUser, void* pFrame, UINT16* pusLen);
///*} 

/*******************************************
 * ��������: ��B���������ֵ(Ӧ���ʽ)
 * ��ӦAFN : MC_AFN_13_ASKR
 * ��ӦCMD : MCMD_AFN_D_F83_IDMAX_B
 * PN ���� : p0/����ն˺�
{*///
// �û���
typedef sMcElecA sMcIMaxB;

// ��֡��
// ת������
eMcErr emc_trans_afn13f83(eMcTrans eTrans, void* pUser, void* pFrame, UINT16* pusLen);
///*} 

/*******************************************
 * ��������: ��B���������ֵ����ʱ��(Ӧ���ʽ)
 * ��ӦAFN : MC_AFN_13_ASKR
 * ��ӦCMD : MCMD_AFN_D_F84_IDMAX_B_TIME
 * PN ���� : p0/����ն˺�
{*///
// �û���
typedef sMcAfn13f35 sMcIMaxBTime;

// ��֡��
// ת������
eMcErr emc_trans_afn13f84(eMcTrans eTrans, void* pUser, void* pFrame, UINT16* pusLen);
///*} 

/*******************************************
 * ��������: ��C���������ֵ(Ӧ���ʽ)
 * ��ӦAFN : MC_AFN_13_ASKR
 * ��ӦCMD : MCMD_AFN_D_F85_IDMAX_C
 * PN ���� : p0/����ն˺�
{*///
// �û���
typedef sMcElecA sMcIMaxC;

// ��֡��
// ת������
eMcErr emc_trans_afn13f85(eMcTrans eTrans, void* pUser, void* pFrame, UINT16* pusLen);
///*} 

/*******************************************
 * ��������: ��C���������ֵ����ʱ��(Ӧ���ʽ)
 * ��ӦAFN : MC_AFN_13_ASKR
 * ��ӦCMD : MCMD_AFN_D_F86_IDMAX_C_TIME
 * PN ���� : p0/����ն˺�
{*///
// �û���
typedef sMcAfn13f35 sMcIMaxCTime;

// ��֡��
// ת������
eMcErr emc_trans_afn13f86(eMcTrans eTrans, void* pUser, void* pFrame, UINT16* pusLen);
///*} 

/*******************************************
 * ��������: �ܻ����й�����(Ӧ���ʽ)
 * ��ӦAFN : MC_AFN_13_ASKR
 * ��ӦCMD : MCMD_AFN_D_F89_TFW_HAVE
 * PN ���� : p0/����ն˺�
{*///
// �û���
typedef sMcAfn13f25 sMcTfwHave;   // (Total Fundamental Wave)

// ��֡��
// ת������
eMcErr emc_trans_afn13f89(eMcTrans eTrans, void* pUser, void* pFrame, UINT16* pusLen);
///*} 

/*******************************************
 * ��������: �ܻ����޹�����(Ӧ���ʽ)
 * ��ӦAFN : MC_AFN_13_ASKR
 * ��ӦCMD : MCMD_AFN_D_F90_TFW_NONE
 * PN ���� : p0/����ն˺�
{*///
// �û���
typedef sMcAfn13f25 sMcTfwNone;   // (Total Fundamental Wave)

// ��֡��
// ת������
eMcErr emc_trans_afn13f90(eMcTrans eTrans, void* pUser, void* pFrame, UINT16* pusLen);
///*} 

/*******************************************
 * ��������: ��г���й�����(Ӧ���ʽ)
 * ��ӦAFN : MC_AFN_13_ASKR
 * ��ӦCMD : MCMD_AFN_D_F91_THW_HAVE
 * PN ���� : p0/����ն˺�
{*///
// �û���
typedef sMcAfn13f25 sMcThwHave;   // (Total Harmonic Wave)

// ��֡��
// ת������
eMcErr emc_trans_afn13f91(eMcTrans eTrans, void* pUser, void* pFrame, UINT16* pusLen);
///*} 

/*******************************************
 * ��������: �ܻ����޹�����(Ӧ���ʽ)
 * ��ӦAFN : MC_AFN_13_ASKR
 * ��ӦCMD : MCMD_AFN_D_F92_THW_NONE
 * PN ���� : p0/����ն˺�
{*///
// �û���
typedef sMcAfn13f25 sMcThwNone;   // (Total Harmonic Wave)

// ��֡��
// ת������
eMcErr emc_trans_afn13f92(eMcTrans eTrans, void* pUser, void* pFrame, UINT16* pusLen);
///*} 

/*******************************************
 * ��������: A���ѹԽ���������ۼ�ʱ��(Ӧ���ʽ)
 * ��ӦAFN : MC_AFN_13_ASKR
 * ��ӦCMD : MCMD_AFN_D_F97_VDPP_TIME_A
 * PN ���� : �����������
{*///
#define MC_BCD_XXXX_MAX  (9999)

// �û���
typedef struct
{
    UINT16    usMinutes;       // ʱ�� ���� ���ֵ MC_BCD_XXXX_MAX
    
}sMcVDppTimeA, sMcAfn13f97;  

// ��֡��
#pragma pack(1)
typedef struct
{
    UINT8 ucBCD[2];
    
}sMcVDppTimeA_f, sMcAfn13f97_f;
#pragma pack()

// ת������
eMcErr emc_trans_afn13f97(eMcTrans eTrans, void* pUser, void* pFrame, UINT16* pusLen);
///*} 

/*******************************************
 * ��������: B���ѹԽ���������ۼ�ʱ��(Ӧ���ʽ)
 * ��ӦAFN : MC_AFN_13_ASKR
 * ��ӦCMD : MCMD_AFN_D_F98_VDPP_TIME_B
 * PN ���� : �����������
{*///
// �û���
typedef sMcVDppTimeA sMcVDppTimeB;
// ת������
// ͬ eMcErr emc_trans_afn13f97(eMcTrans eTrans, void* pUser, void* pFrame, UINT16* pusLen);
///*} 

/*******************************************
 * ��������: C���ѹԽ���������ۼ�ʱ��(Ӧ���ʽ)
 * ��ӦAFN : MC_AFN_13_ASKR
 * ��ӦCMD : MCMD_AFN_D_F99_VDPP_TIME_C
 * PN ���� : �����������
{*///
// �û���
typedef sMcVDppTimeA sMcVDppTimeC;
// ת������
// ͬ eMcErr emc_trans_afn13f97(eMcTrans eTrans, void* pUser, void* pFrame, UINT16* pusLen);
///*} 


/*******************************************
 * ��������: A���ѹԽ���������ۼ�ʱ��(Ӧ���ʽ)
 * ��ӦAFN : MC_AFN_13_ASKR
 * ��ӦCMD : MCMD_AFN_D_F100_VDNN_TIME_A
 * PN ���� : �����������
{*///
// �û���
typedef sMcVDppTimeA sMcVDnnTimeA;
// ת������
// ͬ eMcErr emc_trans_afn13f97(eMcTrans eTrans, void* pUser, void* pFrame, UINT16* pusLen);
///*} 

/*******************************************
 * ��������: B���ѹԽ���������ۼ�ʱ��(Ӧ���ʽ)
 * ��ӦAFN : MC_AFN_13_ASKR
 * ��ӦCMD : MCMD_AFN_D_F101_VDNN_TIME_B
 * PN ���� : �����������
{*///
// �û���
typedef sMcVDppTimeA sMcVDnnTimeB;
// ת������
// ͬ eMcErr emc_trans_afn13f97(eMcTrans eTrans, void* pUser, void* pFrame, UINT16* pusLen);
///*} 

/*******************************************
 * ��������: C���ѹԽ���������ۼ�ʱ��(Ӧ���ʽ)
 * ��ӦAFN : MC_AFN_13_ASKR
 * ��ӦCMD : MCMD_AFN_D_F102_VDNN_TIME_C
 * PN ���� : �����������
{*///
// �û���
typedef sMcVDppTimeA sMcVDnnTimeC;
// ת������
// eMcErr emc_trans_afn13f97(eMcTrans eTrans, void* pUser, void* pFrame, UINT16* pusLen);
///*} 

/*******************************************
 * ��������: A���ѹԽ���������ۼ�ʱ��(Ӧ���ʽ)
 * ��ӦAFN : MC_AFN_13_ASKR
 * ��ӦCMD : MCMD_AFN_D_F105_VMPP_TIME_A
 * PN ���� : �����������
{*///
// �û���
typedef sMcPowerTimes sMcVMppTimeA;
// ת������
// ͬ eMcErr emc_trans_afn13f6(eMcTrans eTrans, void* pUser, void* pFrame, UINT16* pusLen);
///*} 

/*******************************************
 * ��������: B���ѹԽ���������ۼ�ʱ��(Ӧ���ʽ)
 * ��ӦAFN : MC_AFN_13_ASKR
 * ��ӦCMD : MCMD_AFN_D_F106_VMPP_TIME_B
 * PN ���� : �����������
{*///
// �û���
typedef sMcPowerTimes sMcVMppTimeB;
// ת������
// ͬ eMcErr emc_trans_afn13f6(eMcTrans eTrans, void* pUser, void* pFrame, UINT16* pusLen);
///*} 

/*******************************************
 * ��������: C���ѹԽ���������ۼ�ʱ��(Ӧ���ʽ)
 * ��ӦAFN : MC_AFN_13_ASKR
 * ��ӦCMD : MCMD_AFN_D_F107_VMPP_TIME_C
 * PN ���� : �����������
{*///
// �û���
typedef sMcPowerTimes sMcVMppTimeC;
// ת������
// ͬ eMcErr emc_trans_afn13f6(eMcTrans eTrans, void* pUser, void* pFrame, UINT16* pusLen);
///*} 

/*******************************************
 * ��������: A���ѹԽ���������ۼ�ʱ��(Ӧ���ʽ)
 * ��ӦAFN : MC_AFN_13_ASKR
 * ��ӦCMD : MCMD_AFN_D_F108_VMNN_TIME_A
 * PN ���� : �����������
{*///
// �û���
typedef sMcPowerTimes sMcVMnnTimeA;
// ת������
// ͬ eMcErr emc_trans_afn13f6(eMcTrans eTrans, void* pUser, void* pFrame, UINT16* pusLen);
///*} 

/*******************************************
 * ��������: B���ѹԽ���������ۼ�ʱ��(Ӧ���ʽ)
 * ��ӦAFN : MC_AFN_13_ASKR
 * ��ӦCMD : MCMD_AFN_D_F109_VMNN_TIME_B
 * PN ���� : �����������
{*///
// �û���
typedef sMcPowerTimes sMcVMnnTimeB;
// ת������
// ͬ eMcErr emc_trans_afn13f6(eMcTrans eTrans, void* pUser, void* pFrame, UINT16* pusLen);
///*} 

/*******************************************
 * ��������: C���ѹԽ���������ۼ�ʱ��(Ӧ���ʽ)
 * ��ӦAFN : MC_AFN_13_ASKR
 * ��ӦCMD : MCMD_AFN_D_F110_VMNN_TIME_C
 * PN ���� : �����������
{*///
// �û���
typedef sMcPowerTimes sMcVMnnTimeC;
// ת������
// ͬ eMcErr emc_trans_afn13f6(eMcTrans eTrans, void* pUser, void* pFrame, UINT16* pusLen);
///*} 

/*******************************************
 * ��������: A���ѹ�ܻ�����(Ӧ���ʽ)
 * ��ӦAFN : MC_AFN_13_ASKR
 * ��ӦCMD : MCMD_AFN_D_F113_VABR_TOTL_A
 * PN ���� : �����������
{*///
// �û���
typedef sMcAfn13f27 sMcVabrTotalA;
// ת������
// ͬ eMcErr emc_trans_afn13f27(eMcTrans eTrans, void* pUser, void* pFrame, UINT16* pusLen);
///*} 

/*******************************************
 * ��������: B���ѹ�ܻ�����(Ӧ���ʽ)
 * ��ӦAFN : MC_AFN_13_ASKR
 * ��ӦCMD : MCMD_AFN_D_F114_VABR_TOTL_B
 * PN ���� : �����������
{*///
// �û���
typedef sMcAfn13f27 sMcVabrTotalB;
// ת������
// ͬ eMcErr emc_trans_afn13f27(eMcTrans eTrans, void* pUser, void* pFrame, UINT16* pusLen);
///*} 

/*******************************************
 * ��������: C���ѹ�ܻ�����(Ӧ���ʽ)
 * ��ӦAFN : MC_AFN_13_ASKR
 * ��ӦCMD : MCMD_AFN_D_F115_VABR_TOTL_C
 * PN ���� : �����������
{*///
// �û���
typedef sMcAfn13f27 sMcVabrTotalC;
// ת������
// ͬ eMcErr emc_trans_afn13f27(eMcTrans eTrans, void* pUser, void* pFrame, UINT16* pusLen);
///*} 

/*******************************************
 * ��������: A������ܻ�����(Ӧ���ʽ)
 * ��ӦAFN : MC_AFN_13_ASKR
 * ��ӦCMD : MCMD_AFN_D_F116_EABR_TOTL_A
 * PN ���� : �����������
{*///
// �û���
typedef sMcAfn13f27 sMcEabrTotalA;
// ת������
// ͬ eMcErr emc_trans_afn13f27(eMcTrans eTrans, void* pUser, void* pFrame, UINT16* pusLen);
///*} 

/*******************************************
 * ��������: B������ܻ�����(Ӧ���ʽ)
 * ��ӦAFN : MC_AFN_13_ASKR
 * ��ӦCMD : MCMD_AFN_D_F117_EABR_TOTL_B
 * PN ���� : �����������
{*///
// �û���
typedef sMcAfn13f27 sMcEabrTotalB;
// ת������
// ͬ eMcErr emc_trans_afn13f27(eMcTrans eTrans, void* pUser, void* pFrame, UINT16* pusLen);
///*} 

/*******************************************
 * ��������: C������ܻ�����(Ӧ���ʽ)
 * ��ӦAFN : MC_AFN_13_ASKR
 * ��ӦCMD : MCMD_AFN_D_F118_EABR_TOTL_C
 * PN ���� : �����������
{*///
// �û���
typedef sMcAfn13f27 sMcEabrTotalC;
// ת������
// ͬ eMcErr emc_trans_afn13f27(eMcTrans eTrans, void* pUser, void* pFrame, UINT16* pusLen);
///*} 

/*******************************************
 * ��������: A���ѹ��λ�����(Ӧ���ʽ)
 * ��ӦAFN : MC_AFN_13_ASKR
 * ��ӦCMD : MCMD_AFN_D_F121_VABR_ODD_A
 * PN ���� : �����������
{*///
// �û���
typedef sMcAfn13f27 sMcVabrOddA;
// ת������
// ͬ eMcErr emc_trans_afn13f27(eMcTrans eTrans, void* pUser, void* pFrame, UINT16* pusLen);
///*} 

/*******************************************
 * ��������: A���ѹż�λ�����(Ӧ���ʽ)
 * ��ӦAFN : MC_AFN_13_ASKR
 * ��ӦCMD : MCMD_AFN_D_F122_VABR_EVN_A
 * PN ���� : �����������
{*///
// �û���
typedef sMcAfn13f27 sMcVabrEvnA;
// ת������
// ͬ eMcErr emc_trans_afn13f27(eMcTrans eTrans, void* pUser, void* pFrame, UINT16* pusLen);
///*} 

/*******************************************
 * ��������: B���ѹ��λ�����(Ӧ���ʽ)
 * ��ӦAFN : MC_AFN_13_ASKR
 * ��ӦCMD : MCMD_AFN_D_F123_VABR_ODD_B
 * PN ���� : �����������
{*///
// �û���
typedef sMcAfn13f27 sMcVabrOddB;
// ת������
// ͬ eMcErr emc_trans_afn13f27(eMcTrans eTrans, void* pUser, void* pFrame, UINT16* pusLen);
///*} 

/*******************************************
 * ��������: B���ѹż�λ�����(Ӧ���ʽ)
 * ��ӦAFN : MC_AFN_13_ASKR
 * ��ӦCMD : MCMD_AFN_D_F124_VABR_EVN_B
 * PN ���� : �����������
{*///
// �û���
typedef sMcAfn13f27 sMcVabrEvnB;
// ת������
// ͬ eMcErr emc_trans_afn13f27(eMcTrans eTrans, void* pUser, void* pFrame, UINT16* pusLen);
///*} 

/*******************************************
 * ��������: CS���ѹ��λ�����(Ӧ���ʽ)
 * ��ӦAFN : MC_AFN_13_ASKR
 * ��ӦCMD : MCMD_AFN_D_F125_VABR_ODD_C
 * PN ���� : �����������
{*///
// �û���
typedef sMcAfn13f27 sMcVabrOddC;
// ת������
// ͬ eMcErr emc_trans_afn13f27(eMcTrans eTrans, void* pUser, void* pFrame, UINT16* pusLen);
///*} 

/*******************************************
 * ��������: C���ѹż�λ�����(Ӧ���ʽ)
 * ��ӦAFN : MC_AFN_13_ASKR
 * ��ӦCMD : MCMD_AFN_D_F126_VABR_EVN_C
 * PN ���� : �����������
{*///
// �û���
typedef sMcAfn13f27 sMcVabrEvnC;
// ת������
// ͬ eMcErr emc_trans_afn13f27(eMcTrans eTrans, void* pUser, void* pFrame, UINT16* pusLen);
///*} 

/*******************************************
 * ��������: A���ѹ��λ�����(Ӧ���ʽ)
 * ��ӦAFN : MC_AFN_13_ASKR
 * ��ӦCMD : MCMD_AFN_D_F128_EABR_OOD_A
 * PN ���� : �����������
{*///
// �û���
typedef sMcAfn13f27 sMcEabrOddA;
// ת������
// ͬ eMcErr emc_trans_afn13f27(eMcTrans eTrans, void* pUser, void* pFrame, UINT16* pusLen);
///*} 

/*******************************************
 * ��������: A�����ż�λ�����(Ӧ���ʽ)
 * ��ӦAFN : MC_AFN_13_ASKR
 * ��ӦCMD : MCMD_AFN_D_F129_EABR_EVN_A
 * PN ���� : �����������
{*///
// �û���
typedef sMcAfn13f27 sMcEabrEvnA;
// ת������
// ͬ eMcErr emc_trans_afn13f27(eMcTrans eTrans, void* pUser, void* pFrame, UINT16* pusLen);
///*} 

/*******************************************
 * ��������: B�������λ�����(Ӧ���ʽ)
 * ��ӦAFN : MC_AFN_13_ASKR
 * ��ӦCMD : MCMD_AFN_D_F130_EABR_OOD_B
 * PN ���� : �����������
{*///
// �û���
typedef sMcAfn13f27 sMcEabrOddB;
// ת������
// ͬ eMcErr emc_trans_afn13f27(eMcTrans eTrans, void* pUser, void* pFrame, UINT16* pusLen);
///*} 

/*******************************************
 * ��������: B�����ż�λ�����(Ӧ���ʽ)
 * ��ӦAFN : MC_AFN_13_ASKR
 * ��ӦCMD : MCMD_AFN_D_F131_EABR_EVN_B
 * PN ���� : �����������
{*///
// �û���
typedef sMcAfn13f27 sMcEabrEvnB;
// ת������
// ͬ eMcErr emc_trans_afn13f27(eMcTrans eTrans, void* pUser, void* pFrame, UINT16* pusLen);
///*} 

/*******************************************
 * ��������: C�������λ�����(Ӧ���ʽ)
 * ��ӦAFN : MC_AFN_13_ASKR
 * ��ӦCMD : MCMD_AFN_D_F132_EABR_OOD_C
 * PN ���� : �����������
{*///
// �û���
typedef sMcAfn13f27 sMcEabrOddC;
// ת������
// ͬ eMcErr emc_trans_afn13f27(eMcTrans eTrans, void* pUser, void* pFrame, UINT16* pusLen);
///*} 

/*******************************************
 * ��������: C�����ż�λ�����(Ӧ���ʽ)
 * ��ӦAFN : MC_AFN_13_ASKR
 * ��ӦCMD : MCMD_AFN_D_F133_EABR_EVN_C
 * PN ���� : �����������
{*///
// �û���
typedef sMcAfn13f27 sMcEabrEvnC;
// ת������
// ͬ eMcErr emc_trans_afn13f27(eMcTrans eTrans, void* pUser, void* pFrame, UINT16* pusLen);
///*} 

/*******************************************
 * ��������: A���ʱ����(Ӧ���ʽ)
 * ��ӦAFN : MC_AFN_13_ASKR
 * ��ӦCMD : MCMD_AFN_D_F137_FLS_SHRT_A
 * PN ���� : �����������
{*///
// �û���
typedef sMcAfn13f27 sMcFlashShortA;
// ת������
// ͬ eMcErr emc_trans_afn13f27(eMcTrans eTrans, void* pUser, void* pFrame, UINT16* pusLen);
///*} 

/*******************************************
 * ��������: B���ʱ����(Ӧ���ʽ)
 * ��ӦAFN : MC_AFN_13_ASKR
 * ��ӦCMD : MCMD_AFN_D_F138_FLS_SHRT_B
 * PN ���� : �����������
{*///
// �û���
typedef sMcAfn13f27 sMcFlashShortB;
// ת������
// ͬ eMcErr emc_trans_afn13f27(eMcTrans eTrans, void* pUser, void* pFrame, UINT16* pusLen);
///*} 

/*******************************************
 * ��������: C���ʱ����(Ӧ���ʽ)
 * ��ӦAFN : MC_AFN_13_ASKR
 * ��ӦCMD : MCMD_AFN_D_F139_FLS_SHRT_C
 * PN ���� : �����������
{*///
// �û���
typedef sMcAfn13f27 sMcFlashShortC;
// ת������
// ͬ eMcErr emc_trans_afn13f27(eMcTrans eTrans, void* pUser, void* pFrame, UINT16* pusLen);
///*} 

/*******************************************
 * ��������: A�೤ʱ����(Ӧ���ʽ)
 * ��ӦAFN : MC_AFN_13_ASKR
 * ��ӦCMD : MCMD_AFN_D_F140_FLS_LONG_A
 * PN ���� : �����������
{*///
// �û���
typedef sMcAfn13f27 sMcFlashLongA;
// ת������
// ͬ eMcErr emc_trans_afn13f27(eMcTrans eTrans, void* pUser, void* pFrame, UINT16* pusLen);
///*} 

/*******************************************
 * ��������: B�೤ʱ����(Ӧ���ʽ)
 * ��ӦAFN : MC_AFN_13_ASKR
 * ��ӦCMD : MCMD_AFN_D_F141_FLS_LONG_B
 * PN ���� : �����������
{*///
// �û���
typedef sMcAfn13f27 sMcFlashLongB;
// ת������
// ͬ eMcErr emc_trans_afn13f27(eMcTrans eTrans, void* pUser, void* pFrame, UINT16* pusLen);
///*} 

/*******************************************
 * ��������: C�೤ʱ����(Ӧ���ʽ)
 * ��ӦAFN : MC_AFN_13_ASKR
 * ��ӦCMD : MCMD_AFN_D_F142_FLS_LONG_C
 * PN ���� : �����������
{*///
// �û���
typedef sMcAfn13f27 sMcFlashLongC;
// ת������
// ͬ eMcErr emc_trans_afn13f27(eMcTrans eTrans, void* pUser, void* pFrame, UINT16* pusLen);
///*} 

/*******************************************
 * ��������: A��N��г����ѹ(Ӧ���ʽ)
 * ��ӦAFN : MC_AFN_13_ASKR
 * ��ӦCMD : MCMD_AFN_D_F145_HARM_VOLT_A
 * PN ���� : �����������
{*///

#define MC_HARM_TIMES_MAX      (19) // г���������ֵ

// �û���
typedef struct
{
    UINT8        ucN;          // г������
    float    fXXX_X[1];        // 2 ~ n��г��  (����Ԫ�ظ���Ϊ ucN - 1)
}sMcHarmVoltA, sMcAfn13f145;

// ��֡��
#pragma pack(1)
typedef struct
{
    UINT8             ucN;      // г������
    sMcFmt08_f  fXXX_X[1];      // 2 ~ n��г��  (����Ԫ�ظ���Ϊ ucN - 1)
}sMcHarmVoltA_f, sMcAfn13f145_f;
#pragma pack()

// ת������
eMcErr emc_trans_afn13f145(eMcTrans eTrans, void* pUser, void* pFrame, UINT16* pusLen);
///*} 

/*******************************************
 * ��������: B��N��г����ѹ(Ӧ���ʽ)
 * ��ӦAFN : MC_AFN_13_ASKR
 * ��ӦCMD : MCMD_AFN_D_F146_HARM_VOLT_B
 * PN ���� : �����������
{*///
// �û���
typedef sMcHarmVoltA sMcHarmVoltB;
// ת������
// ͬ eMcErr emc_trans_afn13f145(eMcTrans eTrans, void* pUser, void* pFrame, UINT16* pusLen);
///*} 

/*******************************************
 * ��������: C��N��г����ѹ(Ӧ���ʽ)
 * ��ӦAFN : MC_AFN_13_ASKR
 * ��ӦCMD : MCMD_AFN_D_F147_HARM_VOLT_C
 * PN ���� : �����������
{*///
// �û���
typedef sMcHarmVoltA sMcHarmVoltC;
// ת������
// ͬ eMcErr emc_trans_afn13f145(eMcTrans eTrans, void* pUser, void* pFrame, UINT16* pusLen);
///*} 

/*******************************************
 * ��������: A��N��г������(Ӧ���ʽ)
 * ��ӦAFN : MC_AFN_13_ASKR
 * ��ӦCMD : MCMD_AFN_D_F148_HARM_ELEC_A
 * PN ���� : �����������
{*///
// �û���
typedef struct
{
    UINT8             ucN;          // г������
    float    fsXXX_XXX[1];          // 2 ~ n��г��  (����Ԫ�ظ���Ϊ ucN - 1)
}sMcHarmElecA, sMcAfn13f148;

// ��֡��
#pragma pack(1)
typedef struct
{
    UINT8                ucN;      // г������
    sMcFmt09_f  fsXXX_XXX[1];      // 2 ~ n��г��  (����Ԫ�ظ���Ϊ ucN - 1)
}sMcHarmElecA_f, sMcAfn13f148_f;
#pragma pack()

// ת������
eMcErr emc_trans_afn13f148(eMcTrans eTrans, void* pUser, void* pFrame, UINT16* pusLen);
///*} 

/*******************************************
 * ��������: B��N��г������(Ӧ���ʽ)
 * ��ӦAFN : MC_AFN_13_ASKR
 * ��ӦCMD : MCMD_AFN_D_F149_HARM_ELEC_B
 * PN ���� : �����������
{*///
// �û���
typedef sMcHarmElecA sMcHarmElecB;

// ת������
// ͬ eMcErr emc_trans_afn13f148(eMcTrans eTrans, void* pUser, void* pFrame, UINT16* pusLen);
///*} 

/*******************************************
 * ��������: C��N��г������(Ӧ���ʽ)
 * ��ӦAFN : MC_AFN_13_ASKR
 * ��ӦCMD : MCMD_AFN_D_F150_HARM_ELEC_C
 * PN ���� : �����������
{*///
// �û���
typedef sMcHarmElecA sMcHarmElecC;

// ת������
// ͬ eMcErr emc_trans_afn13f148(eMcTrans eTrans, void* pUser, void* pFrame, UINT16* pusLen);
///*} 

/*******************************************
 * ��������: A��N��г����ѹ������(Ӧ���ʽ)
 * ��ӦAFN : MC_AFN_13_ASKR
 * ��ӦCMD : MCMD_AFN_D_F153_HARM_VINC_A
 * PN ���� : �����������
{*///
// �û���
typedef struct
{
    UINT8             ucN;          // г������
    float       fXX_XX[1];          // 2 ~ n��г��������  (����Ԫ�ظ���Ϊ ucN - 1)
}sMcHarmVincA, sMcAfn13f153;

// ��֡��
#pragma pack(1)
typedef struct
{
    UINT8              ucN;      // г������
    sMcFmt10_f   fXX_XX[1];      // 2 ~ n��г��������  (����Ԫ�ظ���Ϊ ucN - 1)
}sMcHarmVincA_f, sMcAfn13f153_f;
#pragma pack()

// ת������
eMcErr emc_trans_afn13f153(eMcTrans eTrans, void* pUser, void* pFrame, UINT16* pusLen);
///*} 

/*******************************************
 * ��������: B��N��г����ѹ������(Ӧ���ʽ)
 * ��ӦAFN : MC_AFN_13_ASKR
 * ��ӦCMD : MCMD_AFN_D_F154_HARM_VINC_B
 * PN ���� : �����������
{*///
// �û���
typedef sMcHarmVincA sMcHarmVincB;

// ת������
// ͬ eMcErr emc_trans_afn13f153(eMcTrans eTrans, void* pUser, void* pFrame, UINT16* pusLen);
///*} 

/*******************************************
 * ��������: C��N��г����ѹ������(Ӧ���ʽ)
 * ��ӦAFN : MC_AFN_13_ASKR
 * ��ӦCMD : MCMD_AFN_D_F155_HARM_VINC_C
 * PN ���� : �����������
{*///
// �û���
typedef sMcHarmVincA sMcHarmVincC;

// ת������
// ͬ eMcErr emc_trans_afn13f153(eMcTrans eTrans, void* pUser, void* pFrame, UINT16* pusLen);
///*} 

/*******************************************
 * ��������: A��N��г������������(Ӧ���ʽ)
 * ��ӦAFN : MC_AFN_13_ASKR
 * ��ӦCMD : MCMD_AFN_D_F156_HARM_EINC_A
 * PN ���� : �����������
{*///
// �û���
typedef sMcHarmVincA sMcHarmEincA;

// ת������
// ͬ eMcErr emc_trans_afn13f153(eMcTrans eTrans, void* pUser, void* pFrame, UINT16* pusLen);
///*} 

/*******************************************
 * ��������: B��N��г������������(Ӧ���ʽ)
 * ��ӦAFN : MC_AFN_13_ASKR
 * ��ӦCMD : MCMD_AFN_D_F157_HARM_EINC_B
 * PN ���� : �����������
{*///
// �û���
typedef sMcHarmVincA sMcHarmEincB;

// ת������
// ͬ eMcErr emc_trans_afn13f153(eMcTrans eTrans, void* pUser, void* pFrame, UINT16* pusLen);
///*} 

/*******************************************
 * ��������: C��N��г������������(Ӧ���ʽ)
 * ��ӦAFN : MC_AFN_13_ASKR
 * ��ӦCMD : MCMD_AFN_D_F158_HARM_EINC_C
 * PN ���� : �����������
{*///
// �û���
typedef sMcHarmVincA sMcHarmEincC;

// ת������
// ͬ eMcErr emc_trans_afn13f153(eMcTrans eTrans, void* pUser, void* pFrame, UINT16* pusLen);
///*} 

/*******************************************
 * ��������: �ǵ�����(Ӧ���ʽ)
 * ��ӦAFN : MC_AFN_13_ASKR
 * ��ӦCMD : MCMD_AFN_D_F233_NELC_VALUE
 * PN ���� : �����������
{*///
// �û���
typedef struct
{
    eMcNElcType   eType;           // �ǵ���������
    sMcDouble   sDouble;           // �ǵ��������� ��ֵ
}sMcNelcValue, sMcAfn13f233;

// ��֡��
#pragma pack(1)
typedef struct
{
    UINT8         eType;       // �ǵ���������
    sMcFmt11_f   sDouble;      // �ǵ���������  ��ֵ
}sMcNelcValue_f, sMcAfn13f233_f;
#pragma pack()

// ת������
eMcErr emc_trans_afn13f233(eMcTrans eTrans, void* pUser, void* pFrame, UINT16* pusLen);
///*} 


/*******************************************
 * ��������: ���󣨶�ʱ�ϱ���������������(�������)
 * ��ӦAFN : MC_AFN_12_ASKT
 * ��ӦCMD : MCMD_AFN_C_F9_FREZ_AUTO
 * PN ���� : p0/����ն˺�
{*///
// �û���
typedef struct
{
    sMcYMDhm   sTs;    // ���󶳽����������е����ݵ���ʼʱ��ts����ʱ������
    sMcYMDhm   sTe;    // ���󶳽����������е����ݵĽ���ʱ��te����ʱ������

}sMcFrezAutoQ, sMcAfn12f9;

// ��֡��
#pragma pack(1)
typedef struct
{
    sMcFmt02_f           sTs;         // ���󶳽����������е����ݵ���ʼʱ��ts����ʱ������
    sMcFmt02_f           sTe;         // ���󶳽����������е����ݵĽ���ʱ��te����ʱ������
}sMcFrezAutoQ_f, sMcAfn12f9_f;
#pragma pack()

// ת������
eMcErr emc_trans_afn12f9_m2s(eMcTrans eTrans, void* pUser, void* pFrame, UINT16* pusLen);
///*} 

/*******************************************
 * ��������: ���󣨶�ʱ�ϱ���������������(Ӧ���ʽ)
 * ��ӦAFN : MC_AFN_12_ASKT
 * ��ӦCMD : MCMD_AFN_C_F9_FREZ_AUTO
 * PN ���� : p0/����ն˺�
{*///
// �û���
typedef union
{
     // MCMD_AFN_D_F1_CLOCK
    sMcUerClock           sUerClock;
    
    // MCMD_AFN_D_F2_PARA_STATE
    // ����״̬��־
    sMcParaState          sParaState;       

    // MCMD_AFN_D_F3_EVENT_1
    // ��Ҫ�¼���������ǰֵ
    UINT16                usEc1;            

    // MCMD_AFN_D_F4_EVENT_2
    // һ���¼���������ǰֵ
    UINT16                usEc2;           

    // MCMD_AFN_D_F5_EVENT_STATE
    // �¼�״̬��־
    sMcEventState         sEventState;      

    // MCMD_AFN_D_F6_POWR_TIMES
    sMcPowerTimes         sPowerTimes;

    // MCMD_AFN_D_F9_STATE 
    // ״̬������λ��־
    sMcState              sState;           
    
    // MCMD_AFN_D_F10_SWITCH 
    // ���������·���ؽ���״̬������λ��־
    sMcSwitch             sSwitch;           
  
    // MCMD_AFN_D_F25_POWR_HAVE_T  ���й�����
    sMcPowerHaveT         sPowerHaveT;
    
    // MCMD_AFN_D_F26_POWR_NONE_T         
    // ���޹�����
    sMcPowerNoneT         sPowerNoneT;      
    
    // �ܹ�������
    // MCMD_AFN_D_F27_FACTR_T               
    sMcFactorT            sFactorT;
    
    // MCMD_AFN_D_F28_FACTR_A               
    // A�๦������
    sMcFactorA            sFactorA;
    
    // MCMD_AFN_D_F29_FACTR_B               
    // B�๦������
    sMcFactorB            sFactorB;
    
    // MCMD_AFN_D_F30_FACTR_C               
    // C�๦������
    sMcFactorC            sFactorC;
    
    // MCMD_AFN_D_F33_DEMAND                
    // ����
    sMcDemand             sDemand;
    
    // MCMD_AFN_D_F34_DEMAND_MAX             
    // ���������
    sMcDemandMax          sDemandMax;

    // MCMD_AFN_D_F35_DEMAND_TIME           
    // �������������ʱ��
    sMcDemandTime         sDemandTime;

    // MCMD_AFN_D_F41_POWR_HAVE_A            
    // A���й�����
    sMcPowerHaveA         sPowerHaveA;

    // MCMD_AFN_D_F42_POWR_HAVE_B            
    // B���й�����
    sMcPowerHaveB sPowerHaveB;

    // MCMD_AFN_D_F43_POWR_HAVE_C           
    // C���й�����
    sMcPowerHaveC sPowerHaveC;

    // MCMD_AFN_D_F44_POWR_NONE_A           
    // A���޹�����
    sMcPowerNoneA sPowerNoneA;

    // MCMD_AFN_D_F45_POWR_NONE_B           
    // B���޹�����
    sMcPowerNoneB sPowerNoneB;

    // MCMD_AFN_D_F46_POWR_NONE_C            
    // C���޹�����
    sMcPowerNoneC sPowerNoneC;

    // MCMD_AFN_D_F49_POWR_HAVE_FRTH         
    // �������й��ܵ���ʾ��
    sMcPowerHaveFrth sPowerHaveFrth;

    // MCMD_AFN_D_F50_POWR_HAVE_BACK         
    // �������й��ܵ���ʾ��
    sMcPowerHaveBack sPowerHaveBack;

    // MCMD_AFN_D_F51_POWR_NONE_FRTH         
    // �������޹��ܵ���ʾ��
    sMcPowerNoneFrth sPowerNoneFrth;

    // MCMD_AFN_D_F52_POWR_NONE_BACK         
    // �������޹��ܵ���ʾ��
    sMcPowerNoneBack sPowerNoneBack;

    // MCMD_AFN_D_F57_VOLT_A                 
    // A���ѹ
    sMcVoltA sVoltA;

    // MCMD_AFN_D_F58_VOLT_B                
    // B���ѹ
    sMcVoltB sVoltB;

    // MCMD_AFN_D_F59_VOLT_C                
    // C���ѹ
    sMcVoltC sVoltC;

    // MCMD_AFN_D_F60_VANGL_A                
    // A���ѹ��λ��
    sMcVAngleA sVAngleA;

    // MCMD_AFN_D_F61_VANGL_B                
    // B���ѹ��λ��
    sMcVAngleB sVAngleB;

    // MCMD_AFN_D_F62_VANGL_C                
    // C���ѹ��λ��
    sMcVAngleC sVAngleC;

    // MCMD_AFN_D_F63_VOLT_UBL               
    // ��ѹ��ƽ���
    sMcVoltUbl sVoltUbl;

    // MCMD_AFN_D_F64_CIRCLE_V               
    // �ܲ�
    sMcVCircle sVCircle;

    // MCMD_AFN_D_F65_ELEC_A                 
    // A�����
    sMcElecA sElecA;

    // MCMD_AFN_D_F66_ELEC_B                 
    // B�����
    sMcElecB sElecB;

    // MCMD_AFN_D_F67_ELEC_C                  
    // C�����
    sMcElecC sElecC;

    // MCMD_AFN_D_F68_ELEC_M                  
    // �����ߵ���
    sMcElecM sElecM;

    // MCMD_AFN_D_F69_EANGL_A                 
    // A�������λ��
    sMcEAngleA sEAngleA;

    // MCMD_AFN_D_F70_EANGL_B                 
    // B�������λ��
    sMcEAngleB sEAngleB;

    // MCMD_AFN_D_F71_EANGL_C                 
    // C�������λ��
    sMcEAngleC sEAngleC;

    // MCMD_AFN_D_F72_ELEC_UBL               
    // ������ƽ���
    sMcElecUbl sElecUbl;

    // MCMD_AFN_D_F73_VDMAX_A                
    // ��A���ѹ����ֵ
    sMcVMaxA sVMaxA;

    // MCMD_AFN_D_F74_VDMAX_A_TIME            
    // ��A���ѹ����ֵ����ʱ��
    sMcVMaxATime sVMaxATime;

    // MCMD_AFN_D_F75_VDMAX_B                 
    // ��A���ѹ����ֵ
    sMcVMaxB sVMaxB;

    // MCMD_AFN_D_F76_VDMAX_B_TIME           
    // ��A���ѹ����ֵ����ʱ��
    sMcVMaxBTime sVMaxBTime;

    // MCMD_AFN_D_F77_VDMAX_C                
    // ��A���ѹ����ֵ
    sMcVMaxC sVMaxC;

    // MCMD_AFN_D_F78_VDMAX_C_TIME            
    // ��A���ѹ����ֵ����ʱ��
    sMcVMaxCTime sVMaxCTime;

    // MCMD_AFN_D_F81_IDMAX_A                 
    // ��A���������ֵ
    sMcIMaxA sIMaxA;

    // MCMD_AFN_D_F82_IDMAX_A_TIME            
    // ��A���������ֵ����ʱ��
    sMcIMaxATime sIMaxATime;

    // MCMD_AFN_D_F83_IDMAX_B                 
    // ��B���������ֵ
    sMcIMaxB sIMaxB;

    // MCMD_AFN_D_F84_IDMAX_B_TIME            
    // ��B���������ֵ����ʱ��
    sMcIMaxBTime sIMaxBTime;

    // MCMD_AFN_D_F85_IDMAX_C                
    // ��C���������ֵ
    sMcIMaxC sIMaxC;

    // MCMD_AFN_D_F86_IDMAX_C_TIME           
    // ��C���������ֵ����ʱ��
    sMcIMaxCTime sIMaxCTime;
    
    // MCMD_AFN_D_F89_TFW_HAVE              
    // �ܻ����й�����  
    sMcTfwHave sTfwHave;

    // MCMD_AFN_D_F90_TFW_NONE                
    // �ܻ����޹�����
    sMcTfwNone sTfwNone;
    
    // MCMD_AFN_D_F91_THW_HAVE                
    // ��г���й�����
    sMcThwHave sThwHave;
    
    // MCMD_AFN_D_F92_THW_NONE                
    // �ܻ����޹�����
    sMcThwNone sThwNone;
    
    // MCMD_AFN_D_F97_VDPP_TIME_A             
    // A���ѹԽ���������ۼ�ʱ��
    sMcVDppTimeA  sVDppTimeA;

    // MCMD_AFN_D_F98_VDPP_TIME_B             
    // B���ѹԽ���������ۼ�ʱ��
    sMcVDppTimeB  sVDppTimeB;

    // MCMD_AFN_D_F99_VDPP_TIME_C             
    // C���ѹԽ���������ۼ�ʱ��
    sMcVDppTimeC  sVDppTimeC;

    // MCMD_AFN_D_F100_VDNN_TIME_A            
    // A���ѹԽ���������ۼ�ʱ��
    sMcVDnnTimeA sVDnnTimeA;

    // MCMD_AFN_D_F101_VDNN_TIME_B            
    // B���ѹԽ���������ۼ�ʱ��
    sMcVDnnTimeB sVDnnTimeB;

    // MCMD_AFN_D_F102_VDNN_TIME_C            
    // C���ѹԽ���������ۼ�ʱ��
    sMcVDnnTimeC sVDnnTimeC;

    // MCMD_AFN_D_F105_VMPP_TIME_A            
    // A���ѹԽ���������ۼ�ʱ��
    sMcVMppTimeA  sVMppTimeA;

    // MCMD_AFN_D_F106_VMPP_TIME_B            
    // B���ѹԽ���������ۼ�ʱ��
    sMcVMppTimeB sVMppTimeB;

    // MCMD_AFN_D_F107_VMPP_TIME_C            
    // C���ѹԽ���������ۼ�ʱ��
    sMcVMppTimeC sVMppTimeC;

    // MCMD_AFN_D_F108_VMNN_TIME_A            
    // A���ѹԽ���������ۼ�ʱ��
    sMcVMnnTimeA sVMnnTimeA;

    // MCMD_AFN_D_F109_VMNN_TIME_B            
    // B���ѹԽ���������ۼ�ʱ��
    sMcVMnnTimeB sVMnnTimeB;

    // MCMD_AFN_D_F110_VMNN_TIME_C            
    // C���ѹԽ���������ۼ�ʱ��
    sMcVMnnTimeC sVMnnTimeC;

    // MCMD_AFN_D_F113_VABR_TOTL_A            
    // A���ѹ�ܻ�����
    sMcVabrTotalA sVabrTotalA;

    // MCMD_AFN_D_F114_VABR_TOTL_B            
    // B���ѹ�ܻ�����
    sMcVabrTotalB sVabrTotalB;

    // MCMD_AFN_D_F115_VABR_TOTL_C            
    // C���ѹ�ܻ�����
    sMcVabrTotalC sVabrTotalC;
    
    // MCMD_AFN_D_F116_EABR_TOTL_A            
    // A������ܻ�����
    sMcEabrTotalA sEabrTotalA;
    
    // MCMD_AFN_D_F117_EABR_TOTL_B            
    // B������ܻ�����
    sMcEabrTotalB sEabrTotalB;
    
    // MCMD_AFN_D_F118_EABR_TOTL_C            
    // C������ܻ�����
    sMcEabrTotalC sEabrTotalC;

    // MCMD_AFN_D_F121_VABR_ODD_A             
    // A���ѹ��λ�����
    sMcVabrOddA sVabrOddA;
    
    // MCMD_AFN_D_F122_VABR_EVN_A             
    // A���ѹż�λ�����
    sMcVabrEvnA sVabrEvnA;
    
    // MCMD_AFN_D_F123_VABR_ODD_B             
    // B���ѹ��λ�����
    sMcVabrOddB sVabrOddB;
    
    // MCMD_AFN_D_F124_VABR_EVN_B             
    // B���ѹż�λ�����
    sMcVabrEvnB sVabrEvnB;
    
    // MCMD_AFN_D_F125_VABR_ODD_C             
    // C���ѹ��λ�����
    sMcVabrOddC sVabrOddC;
    
    // MCMD_AFN_D_F126_VABR_EVN_C             
    // C���ѹż�λ�����
    sMcVabrEvnC sVabrEvnC;

    // MCMD_AFN_D_F128_EABR_OOD_A             
    // A�������λ�����
    sMcEabrOddA sEabrOddA;
    
    // MCMD_AFN_D_F129_EABR_EVN_A             
    // A�����ż�λ�����
    sMcEabrEvnA sEabrEvnA;
    
    // MCMD_AFN_D_F130_EABR_OOD_B             
    // B�������λ�����
    sMcEabrOddB sEabrOddB;
    
    // MCMD_AFN_D_F131_EABR_EVN_B             
    // B�����ż�λ�����
    sMcEabrEvnB sEabrEvnB;
    
    // MCMD_AFN_D_F132_EABR_OOD_C           
    // C�������λ�����
    sMcEabrOddC sEabrOddC;
    
    // MCMD_AFN_D_F133_EABR_EVN_C           
    // C�����ż�λ�����
    sMcEabrEvnC sEabrEvnC;

    // MCMD_AFN_D_F137_FLS_SHRT_A             
    // A���ʱ����
    sMcFlashShortA sFlashShortA;
    
    // MCMD_AFN_D_F138_FLS_SHRT_B            
    // B���ʱ����
    sMcFlashShortB sFlashShortB;
    
    // MCMD_AFN_D_F139_FLS_SHRT_C     
    // C���ʱ����
    sMcFlashShortC sFlashShortC;
    
    // MCMD_AFN_D_F140_FLS_LONG_A       
    // A�೤ʱ����
    sMcFlashLongA sFlashLongA;
    
    // MCMD_AFN_D_F141_FLS_LONG_B   
    // B�೤ʱ����
    sMcFlashLongB sFlashLongB;
    
    // MCMD_AFN_D_F142_FLS_LONG_C             
    // C�೤ʱ����
    sMcFlashLongC sFlashLongC;

    // MCMD_AFN_D_F145_HARM_VOLT_A            
    // A��N��г����ѹ
    sMcHarmVoltA sHarmVoltA;
    
    // MCMD_AFN_D_F146_HARM_VOLT_B          
    // B��N��г����ѹ
    sMcHarmVoltB sHarmVoltB;
    
    // MCMD_AFN_D_F147_HARM_VOLT_C          
    // C��N��г����ѹ
    sMcHarmVoltC sHarmVoltC;
    
    // MCMD_AFN_D_F148_HARM_ELEC_A             
    // A��N��г������
    sMcHarmElecA sHarmElecA;
    
    // MCMD_AFN_D_F149_HARM_ELEC_B            
    // B��N��г������
    sMcHarmElecB sHarmElecB;
    
    // MCMD_AFN_D_F150_HARM_ELEC_C            
    // C��N��г������
    sMcHarmElecC sHarmElecC;

    // MCMD_AFN_D_F153_HARM_VINC_A           
    // A��N��г����ѹ������
    sMcHarmVincA sHarmVincA;

    // MCMD_AFN_D_F154_HARM_VINC_B           
    // B��N��г����ѹ������
    sMcHarmVincB sHarmVincB;

    // MCMD_AFN_D_F155_HARM_VINC_C            
    // C��N��г����ѹ������
    sMcHarmVincC sHarmVincC;

    // MCMD_AFN_D_F156_HARM_EINC_A          
    // A��N��г������������
    sMcHarmEincA sHarmEincA;

    // MCMD_AFN_D_F157_HARM_EINC_B           
    // B��N��г������������
    sMcHarmEincB sHarmEincB;

    // MCMD_AFN_D_F158_HARM_EINC_C        
    // C��N��г������������
    sMcHarmEincC sHarmEincC;

    // ��30 pn:�ǵ����������
    // MCMD_AFN_D_F233_NELC_VALUE      
    // �ǵ�����
    sMcNelcValue sNelcValue;
}uMcFrezApp;

typedef struct
{
    sMcmdPn    sCmdPn;
    uMcFrezApp uApp[1];       // ucN��
}sMcFrezOne;

typedef struct
{
    sMcYMDhm            sTs;    // ���󶳽����������е����ݵ���ʼʱ��ts����ʱ������
    UINT16         usPeriod;    // �������� Ϊ��ʱ�����ʱ������Ϊ0��ʾɾ�����������
    eMcPeriodUnit     eUnit;    // �������ڵ�λ
    UINT8               ucN;    // ��������������ʾ�Զ�������Ϊ������足��Ĵ�����Ϊ0��ʾ���޴����� 
    UINT8               ucM;    // ����Ӧ���ϱ����Ķ����������������õ����ݵ�Ԫ��ʶ��m
    sMcFrezOne      sOne[1];    // ucM ��    
}sMcFrezAutoA, sMcAfn12f9A;

// ��֡��
#pragma pack(1)
typedef struct
{
    sMcFmt02_f          sTs;
    UINT16         usPeriod;     // �������� Ϊ��ʱ�����ʱ������Ϊ0��ʾɾ�����������
    UINT8             eUnit;     // �������ڵ�λ
    UINT8               ucN;     // ��������������ʾ�Զ�������Ϊ������足��Ĵ�����Ϊ0��ʾ���޴����� 
    UINT8               ucM;     // ����Ӧ���ϱ����Ķ����������������õ����ݵ�Ԫ��ʶ��m
    UINT8         ucDaDt[1];     // ����Ϊ�䳤
    
}sMcFrezAutoA_f, sMcAfn12f9A_f;
#pragma pack()

// ת������
eMcErr emc_trans_afn12f9_s2m(eMcTrans eTrans, void* pUser, void* pFrame, UINT16* pusLen);
///*} 

/*******************************************
 * ��������: ������Ҫ�¼�(�����ʽ)
 * ��ӦAFN : MC_AFN_14_ASKE
 * ��ӦCMD : MCMD_AFN_E_F1_EVENT_1
 * PN ���� : P0
 * ����˵��:
 *     ��������¼���¼����Y�������м��㹫ʽ��
 *     (1)��Pm��Pnʱ��Y= Pn-Pm
 *     (2)��Pm��Pnʱ��Y= 256��Pn-Pm
 * 
{*///
// �û���
typedef struct
{
    UINT8   ucPm;           // �����¼���¼��ʼָ��Pm
    UINT8   ucPn;           // �����¼���¼����ָ��Pn
}sMcEventImpQ, sMcAfn14f1;

// ��֡��
#pragma pack(1)
typedef struct
{
    UINT8   ucPm;           // �����¼���¼��ʼָ��Pm
    UINT8   ucPn;           // �����¼���¼����ָ��Pn
}sMcEventImpQ_f, sMcAfn14f1_f;
#pragma pack()

// ת������
eMcErr emc_trans_afn14f1_m2s(eMcTrans eTrans, void* pUser, void* pFrame, UINT16* pusLen);
///*} 

/*******************************************
 * ��������: ������Ҫ�¼�(�����ʽ)
 * ��ӦAFN : MC_AFN_14_ASKE
 * ��ӦCMD : MCMD_AFN_E_F2_EVENT_2
 * PN ���� : �����������
{*///
// �û���
typedef sMcEventImpQ sMcEventNmlQ;

// ��֡��

// ת������
// ͬ eMcErr emc_trans_afn14f1_m2s(eMcTrans eTrans, void* pUser, void* pFrame, UINT16* pusLen);
///*} 

/*******************************************
 * ��������: ����ָ���¼�(�����ʽ)
 * ��ӦAFN : MC_AFN_14_ASKE
 * ��ӦCMD : MCMD_AFN_E_F3_EVENT_3
 * PN ���� : P0
{*///
// �û���
typedef struct
{
    UINT8        ucN;           // �����¼���ʶ����
    eMcErc   eErc[1];           // �����¼���¼(��N��)
}sMcEventSpeQ, sMcAfn14f3;

// ��֡��
#pragma pack(1)
typedef struct
{
    UINT8        ucN;           // �����¼���ʶ����
    UINT8   ucErc[1];           // �����¼���¼(��N��)
}sMcEventSpeQ_f, sMcAfn14f3_f;
#pragma pack()

// ת������
eMcErr emc_trans_afn14f3_m2s(eMcTrans eTrans, void* pUser, void* pFrame, UINT16* pusLen);
///*}

/*******************************************
 * ��������: ����汾����¼�
 * ��ӦAFN : MC_AFN_14_ASKE
 * ��ӦERC : MC_ERC_1_RESET
 *
{*///
// �û���
typedef enum
{    
    MC_RESET_UNKOWN,           // δ֪��ʼ������
    MC_RESET_HARD_INIT,        // Ӳ����ʼ��
    MC_RESET_DATA_INIT,        // ��������ʼ��
    MC_RESET_FACTORY_RESET,    // ������ȫ����������ʼ�������ָ����������ã�
    MC_RESET_PARA_INIT,        // ����������ϵͳ��վͨ���йصģ���ȫ����������ʼ��
}eMcReset;
typedef struct
{
    UINT16               usPN; // P0/����ն˺�
    sMcYMDhm            sTime; // �¼�����ʱ��,��ʱ������
    eMcReset            eType; // ��λ���
}sMcErcReset, sMcErc1;

// ��֡��
#pragma pack(1)
typedef struct
{
    UINT16               usPN; // P0/����ն˺�
    sMcYMDhm_f          sTime; // �¼�����ʱ��,��ʱ������
    UINT8               eType; // ���ǰ����汾��
}sMcErcReset_f, sMcErc1_f;
#pragma pack()

// ת������
eMcErr emc_trans_erc_1(eMcTrans eTrans, void* pUser, void* pFrame, UINT16* pusLen);
///*}

/*******************************************
 * ��������: ָ�����������¼�
 * ��ӦAFN : MC_AFN_14_ASKE
 * ��ӦERC : MC_ERC_2_DATA_CLEAR
 * ��ע:     ��ʱ�ò���,��δʵ��
{*///
// �û���
typedef union
{
    // ֻ��ʵʱ����
}uMcDataPre;                  // ����ǰ������

typedef struct
{
    sMcmdPn       sCmdPn;     // �����ʶ
    uMcDataPre  uPreData;     // ����ǰ������
}sMcPreCmdPn;

typedef struct
{
    UINT16          usPN; // P0/����ն˺�
    sMcYMDhm       sTime; // �¼�����ʱ��,��ʱ������
    UINT8            ucN; // ��λ���
    sMcPreCmdPn  sOne[1]; // ����֮ǰ�����ݱ�ʶ����������       
}sMcErcDataClear, sMcErc2;

// ��֡��
#pragma pack(1)
typedef struct
{
    UINT16               usPN; // P0/����ն˺�
    sMcYMDhm_f          sTime; // �¼�����ʱ��,��ʱ������
    UINT8                 ucN; // ���ǰ����汾��
    /* �����Ǳ䳤
    sMcDaDt             sData;
    uMcData             uData[1]
    ......
    sMcDaDt             sData;
    uMcData             uData[1]
    */
}sMcErcDataClear_f, sMcErc2_f;
#pragma pack()

// ת������
eMcErr emc_trans_erc_2(eMcTrans eTrans, void* pUser, void* pFrame, UINT16* pusLen);
///*}

/*******************************************
 * ��������: ����汾����¼�
 * ��ӦAFN : MC_AFN_14_ASKE
 * ��ӦERC : MC_ERC_3_SOFT_CHANGE
 *
{*///
// �û���
typedef struct
{
    UINT16               usPN; // P0/����ն˺�
    sMcYMDhm            sTime; // �¼�����ʱ��,��ʱ������
    UINT8      ucPreVerson[4]; // ���ǰ����汾��
    sMcYMDhm         sPreTime; // ���ǰ����汾����ʱ��
    UINT8      ucNewVerson[4]; // ���������汾��
    sMcYMDhm         sNewTime; // ���������汾����ʱ��
}sMcErcSoftChange, sMcErc3;

// ��֡��
#pragma pack(1)
typedef struct
{
    UINT16               usPN; // P0/����ն˺�
    sMcYMDhm_f          sTime; // �¼�����ʱ��,��ʱ������
    UINT8      ucPreVerson[4]; // ���ǰ����汾��
    sMcYMDhm_f       sPreTime; // ���ǰ����汾����ʱ��
    UINT8      ucNewVerson[4]; // ���������汾��
    sMcYMDhm_f       sNewTime; // ���������汾����ʱ��
}sMcErcSoftChange_f, sMcErc3_f;
#pragma pack()

// ת������
eMcErr emc_trans_erc_3(eMcTrans eTrans, void* pUser, void* pFrame, UINT16* pusLen);
///*}

/*******************************************
 * ��������: ��������¼�
 * ��ӦAFN : MC_AFN_14_ASKE
 * ��ӦERC : MC_ERC_4_PARA_CHANGE
 *
{*///
// �û���
typedef struct
{
    UINT16               usPN; // P0/����ն˺�
    sMcYMDhm            sTime; // �¼�����ʱ��,��ʱ������
    UINT8                 ucN; // ����������ݵ�Ԫ��ʶ����
    sMcmdPn         sCmdPn[1]; // ���������ĵ�Ԫ��ʶ
}sMcErcParaChange, sMcErc4;

// ��֡��
#pragma pack(1)
typedef struct
{
    UINT16               usPN; // P0/����ն˺�
    sMcYMDhm_f          sTime; // �¼�����ʱ��,��ʱ������
    sMcDaDt          sDaDt[1]; // �����ɳ����le�������� UINT16* pusLen����
}sMcErcParaChange_f, sMcErc4_f;
#pragma pack()

// ת������
eMcErr emc_trans_erc_4(eMcTrans eTrans, void* pUser, void* pFrame, UINT16* pusLen);
///*}

/*******************************************
 * ��������: Уʱ�¼�
 * ��ӦAFN : MC_AFN_14_ASKE
 * ��ӦERC : MC_ERC_5_CHECK_TIME
 *
{*///
// �û���
typedef struct
{
    UINT16               usPN; // P0/����ն˺�
    sMcYMDhm            sTime; // �¼�����ʱ��,��ʱ������
    sMcYWMDhms         sClock; // Уʱʱ�� 
}sMcErcTimeCheck, sMcErc5;

// ��֡��
#pragma pack(1)
typedef struct
{
    UINT16               usPN;  // P0/����ն˺�
    sMcYMDhm_f          sTime;  // �¼�����ʱ��,��ʱ������
    sMcYWMDhms_f        sClock; // Уʱʱ�� 
}sMcErcTimeCheck_f, sMcErc5_f;
#pragma pack()

// ת������
eMcErr emc_trans_erc_5(eMcTrans eTrans, void* pUser, void* pFrame, UINT16* pusLen);
///*}

/*******************************************
 * ��������: ״̬����λ�¼�
 * ��ӦAFN : MC_AFN_14_ASKE
 * ��ӦERC : MC_ERC_6_STATE_CHANGE
 *
{*///
// �û���
typedef struct
{
    UINT16               usPN; // P0/����ն˺�
    sMcYMDhm            sTime; // �¼�����ʱ��,��ʱ������
    BOOL           bChange[8]; // 1-8·�Ƿ����仯
    BOOL               bSt[8]; // 1-8�仯��״̬ true:�� false:��
}sMcErcStateChange, sMcErc6;

// ��֡��
#pragma pack(1)
typedef struct
{
    UINT16               usPN; // P0/����ն˺�
    sMcYMDhm_f          sTime; // �¼�����ʱ��,��ʱ������
    UINT8             bChange; // 1-8·�Ƿ����仯
    UINT8                 bSt; // 1-8�仯��״̬ true:�� false:��
}sMcErcStateChange_f, sMcErc6_f;
#pragma pack()

// ת������
eMcErr emc_trans_erc_6(eMcTrans eTrans, void* pUser, void* pFrame, UINT16* pusLen);
///*}

/*******************************************
 * ��������: ң����բ�¼�
 * ��ӦAFN : MC_AFN_14_ASKE
 * ��ӦERC : MC_ERC_7_REMOTE_SWITCH
 *
{*///
// �û���
typedef struct
{
    UINT16               usPN; // P0/����ն˺�
    sMcYMDhm            sTime; // �¼�����ʱ��,��ʱ������
    BOOL           bCircle[8]; // ��բ���� (1-8)�����ִ��Ƿ���բ
    float              fPower; // ��բʱ�Ĺ���    (+)XX.XXXX
    float             fPower2; // ��բ��2���ӹ��� (+)XX.XXXX
}sMcErcRemoteSwitch, sMcErc7;

// ��֡��
#pragma pack(1)
typedef struct
{
    UINT16               usPN; // P0/����ն˺�
    sMcYMDhm_f          sTime; // �¼�����ʱ��,��ʱ������
    UINT8             bCircle; // ��բ���� (1-8)�����ִ��Ƿ���բ
    sMcFmt06_f         fPower; // ��բʱ�Ĺ���
    sMcFmt06_f        fPower2; // ��բ��2���ӹ���
}sMcErcRemoteSwitch_f, sMcErc7_f;
#pragma pack()

// ת������
eMcErr emc_trans_erc_7(eMcTrans eTrans, void* pUser, void* pFrame, UINT16* pusLen);
///*}

/*******************************************
 * ��������: ͣ/�ϵ��¼�
 * ��ӦAFN : MC_AFN_14_ASKE
 * ��ӦERC : MC_ERC_8_POWER_ON_OFF
 *
{*///
// �û���
typedef struct
{
    UINT16               usPN; // P0/����ն˺�
    BOOL               bStart; // �¼���ֹ
    sMcYMDhm            sTime; // �¼�����ʱ��,��ʱ������
}sMcErcPowerOnOff, sMcErc8;

// ��֡��
#pragma pack(1)
typedef struct
{
    UINT16               usPN; // P0/����ն˺�
    sMcYMDhm_f          sTime; // �¼�����ʱ��,��ʱ������
}sMcErcPowerOnOff_f, sMcErc8_f;
#pragma pack()

// ת������
eMcErr emc_trans_erc_8(eMcTrans eTrans, void* pUser, void* pFrame, UINT16* pusLen);
///*}

/*******************************************
 * ��������: �ܹ�������Խ���¼�
 * ��ӦAFN : MC_AFN_14_ASKE
 * ��ӦERC : MC_ERC_9_FACTOR_OVER
 *
{*///
// �û���
typedef struct
{
    UINT16               usPN; // P0/����ն˺�
    sMcYMDhm            sTime; // �¼�����ʱ��,��ʱ������
    float              fOccur; // Խ��ʱ�ܹ�������          (+)XX.XX
    float              fLimit; // Խ��ʱ�ܹ���Խ�޸澯��ֵ  (+)XX.XX
}sMcErcFactorOver, sMcErc9;

// ��֡��
#pragma pack(1)
typedef struct
{
    UINT16               usPN; // P0/����ն˺�
    sMcYMDhm_f          sTime; // �¼�����ʱ��,��ʱ������
    sMcFmt10_f         fOccur; // Խ��ʱ�ܹ�������          (+)XX.XX
    sMcFmt10_f         fLimit; // Խ��ʱ�ܹ���Խ�޸澯��ֵ  (+)XX.XX
}sMcErcFactorOver_f, sMcErc9_f;
#pragma pack()

// ת������
eMcErr emc_trans_erc_9(eMcTrans eTrans, void* pUser, void* pFrame, UINT16* pusLen);
///*}

/*******************************************
 * ��������: ��ѹƫ��Խ���¼�
 * ��ӦAFN : MC_AFN_14_ASKE
 * ��ӦERC : MC_ERC_10_VOLT_EXCP
 *
{*///
// �û���
typedef struct
{
    UINT16         usPN;           // P0/����ն˺�
    sMcYMDhm       sTime;          // �¼�����ʱ��,��ʱ������
    BOOL           bPhaseA;        // A�෢��Խ��
    BOOL           bPhaseB;        // B�෢��Խ��
    BOOL           bPhaseC;        // C�෢��Խ��
    BOOL           bOverUpUp;      // ��:ΪԽ������ ��:ΪԽ������
    float          fUa;            // ����ʱ��Ua/Uab  (+)XXX.X
    float          fUb;            // ����ʱ��Ub      (+)XXX.X
    float          fUc;            // ����ʱ��Ub      (+)XXX.X
}sMcErcVoltExcp, sMcErc10;

// ��֡��
#pragma pack(1)
typedef struct
{
    UINT16         usPN;           // P0/����ն˺�
    sMcYMDhm_f     sTime;          // �¼�����ʱ��,��ʱ������
    UINT8          ucExcp;         // Խ�ޱ�־
    sMcFmt08_f     fUa;
    sMcFmt08_f     fUb;
    sMcFmt08_f     fUc;
}sMcErcVoltExcp_f, sMcErc10_f;
#pragma pack()

// ת������
eMcErr emc_trans_erc_10(eMcTrans eTrans, void* pUser, void* pFrame, UINT16* pusLen);
///*}

/*******************************************
 * ��������: ��ѹ��·�쳣�¼�
 * ��ӦAFN : MC_AFN_14_ASKE
 * ��ӦERC : MC_ERC_11_VOLT_CIRCLE
 *
{*///
// �û���
typedef enum
{
    MC_VOLT_CIRCLE_UNKOWN,     // δ֪ ����
    MC_VOLT_CIRCLE_DROP,       // ����
    MC_VOLT_CIRCLE_LOSS,       // ʧѹ
        
}eMcVoltCircle;

typedef struct
{
    UINT16         usPN;           // P0/����ն˺�
    BOOL           bStart;         // TRUE ���� FALSE �ָ�
    sMcYMDhm       sTime;          // �¼�����ʱ��,��ʱ������
    eMcVoltCircle  eExcp;
    BOOL           bPhaseA;        // A ���Ƿ����쳣
    BOOL           bPhaseB;        // B ���Ƿ����쳣
    BOOL           bPhaseC;        // C ���Ƿ����쳣
    float          fUa;            // ����ʱ��Ua/Uab    (+)XXX.X
    float          fUb;            // ����ʱ��Ub        (+)XXX.X
    float          fUc;            // ����ʱ��Uc/Ucb    (+)XXX.X
    float          fIa;            // ����ʱ��Ia        (+/-)XXX.XXX
    float          fIb;            // ����ʱ��Ib        (+/-)XXX.XXX
    float          fIc;            // ����ʱ��Ic        (+/-)XXX.XXX
}sMcErcVoltCircle, sMcErc11;

// ��֡��
#pragma pack(1)
typedef struct
{
    UINT16         usPN;           // P0/����ն˺�
    sMcYMDhm_f     sTime;          // �¼�����ʱ��,��ʱ������
    UINT8          ucExcp;         // Խ�ޱ�־
    sMcFmt08_f     fUa;
    sMcFmt08_f     fUb;
    sMcFmt08_f     fUc;
    sMcFmt09_f     fIa;            // ����ʱ��Ia        (+/-)XXX.XXX
    sMcFmt09_f     fIb;            // ����ʱ��Ib        (+/-)XXX.XXX
    sMcFmt09_f     fIc;            // ����ʱ��Ic        (+/-)XXX.XXX
}sMcErcVoltCircle_f, sMcErc11_f;
#pragma pack()

// ת������
eMcErr emc_trans_erc_11(eMcTrans eTrans, void* pUser, void* pFrame, UINT16* pusLen);
///*}

/*******************************************
 * ��������: ������·�쳣�¼�
 * ��ӦAFN : MC_AFN_14_ASKE
 * ��ӦERC : MC_ERC_12_ELEC_CRICLE
 *
{*///
// �û���
typedef enum
{
    MC_ELEC_EXCP_UNKOWN,     // δ֪ ����
    MC_ELEC_EXCP_SHORT,      // ��·
    MC_ELEC_EXCP_CARVE,      // ��·
    MC_ELEC_EXCP_BACK,       // ����
}eMcElecExcp;

typedef struct
{
    UINT16         usPN;           // P0/����ն˺�
    BOOL           bStart;         // TRUE ���� FALSE �ָ�
    sMcYMDhm       sTime;          // �¼�����ʱ��,��ʱ������
    eMcElecExcp    eExcp;          // ������·�쳣����
    BOOL           bPhaseA;        // A ���Ƿ����쳣
    BOOL           bPhaseB;        // B ���Ƿ����쳣
    BOOL           bPhaseC;        // C ���Ƿ����쳣
    float          fUa;            // ����ʱ��Ua/Uab    (+)XXX.X
    float          fUb;            // ����ʱ��Ub        (+)XXX.X
    float          fUc;            // ����ʱ��Uc/Ucb    (+)XXX.X
    float          fIa;            // ����ʱ��Ia        (+/-)XXX.XXX
    float          fIb;            // ����ʱ��Ib        (+/-)XXX.XXX
    float          fIc;            // ����ʱ��Ic        (+/-)XXX.XXX
}sMcErcElecCircle, sMcErc12;

// ��֡��
#pragma pack(1)
typedef struct
{
    UINT16         usPN;           // P0/����ն˺�
    sMcYMDhm_f     sTime;          // �¼�����ʱ��,��ʱ������
    UINT8          ucExcp;         // Խ�ޱ�־
    sMcFmt08_f     fUa;
    sMcFmt08_f     fUb;
    sMcFmt08_f     fUc;
    sMcFmt09_f     fIa;            // ����ʱ��Ia        (+/-)XXX.XXX
    sMcFmt09_f     fIb;            // ����ʱ��Ib        (+/-)XXX.XXX
    sMcFmt09_f     fIc;            // ����ʱ��Ic        (+/-)XXX.XXX
}sMcErcElecCircle_f, sMcErc12_f;
#pragma pack()

// ת������
eMcErr emc_trans_erc_12(eMcTrans eTrans, void* pUser, void* pFrame, UINT16* pusLen);
///*}

/*******************************************
 * ��������: ��ѹԽ���¼�
 * ��ӦAFN : MC_AFN_14_ASKE
 * ��ӦERC : MC_ERC_13_VOLT_OVER
 *
{*///
// �û���
typedef struct
{
    UINT16         usPN;           // P0/����ն˺�
    BOOL           bStart;         // �¼���ֹ
    sMcYMDhm       sTime;          // �¼�����ʱ��,��ʱ������
    BOOL           bPhaseA;        // A�෢��Խ��
    BOOL           bPhaseB;        // B�෢��Խ��
    BOOL           bPhaseC;        // C�෢��Խ��
    BOOL           bOverUpUp;      // ��:ΪԽ������ ��:ΪԽ������
    float          fUa;            // ����ʱ��Ua/Uab  (+)XXX.X
    float          fUb;            // ����ʱ��Ub      (+)XXX.X
    float          fUc;            // ����ʱ��Ub      (+)XXX.X
}sMcErcVoltOver, sMcErc13;

// ��֡��
#pragma pack(1)
typedef struct
{
    UINT16         usPN;           // P0/����ն˺�
    sMcYMDhm_f     sTime;          // �¼�����ʱ��,��ʱ������
    UINT8          ucExcp;         // Խ�ޱ�־
    sMcFmt08_f     fUa;
    sMcFmt08_f     fUb;
    sMcFmt08_f     fUc;
}sMcErcVoltOver_f, sMcErc13_f;
#pragma pack()

// ת������
eMcErr emc_trans_erc_13(eMcTrans eTrans, void* pUser, void* pFrame, UINT16* pusLen);
///*}

/*******************************************
 * ��������: ����Խ���¼�
 * ��ӦAFN : MC_AFN_14_ASKE
 * ��ӦERC : MC_ERC_14_ELEC_OVER
 *
{*///
// �û���
typedef struct
{
    UINT16         usPN;           // P0/����ն˺�
    BOOL           bStart;         // �¼���ֹ
    sMcYMDhm       sTime;          // �¼�����ʱ��,��ʱ������
    BOOL           bPhaseA;        // A�෢��Խ��
    BOOL           bPhaseB;        // B�෢��Խ��
    BOOL           bPhaseC;        // C�෢��Խ��
    BOOL           bOverUpUp;      // ��:ΪԽ������ ��:ΪԽ����
    float          fIa;            // ����ʱ��Ia        (+/-)XXX.XXX
    float          fIb;            // ����ʱ��Ib        (+/-)XXX.XXX
    float          fIc;            // ����ʱ��Ic        (+/-)XXX.XXX
}sMcErcElecOver, sMcErc14;

// ��֡��
#pragma pack(1)
typedef struct
{
    UINT16         usPN;           // P0/����ն˺�
    sMcYMDhm_f     sTime;          // �¼�����ʱ��,��ʱ������
    UINT8          ucExcp;         // Խ�ޱ�־
    sMcFmt09_f     fIa;            // ����ʱ��Ia        (+/-)XXX.XXX
    sMcFmt09_f     fIb;            // ����ʱ��Ib        (+/-)XXX.XXX
    sMcFmt09_f     fIc;            // ����ʱ��Ic        (+/-)XXX.XXX
}sMcErcElecOver_f, sMcErc14_f;
#pragma pack()

// ת������
eMcErr emc_trans_erc_14(eMcTrans eTrans, void* pUser, void* pFrame, UINT16* pusLen);
///*}

/*******************************************
 * ��������: ��ѹ��ƽ���Խ���¼�
 * ��ӦAFN : MC_AFN_14_ASKE
 * ��ӦERC : MC_ERC_15_UNBL_OVER_V
 *
{*///
// �û���
typedef struct
{
    UINT16         usPN;           // P0/����ն˺�
    BOOL           bStart;         // �¼���ֹ
    sMcYMDhm       sTime;          // �¼�����ʱ��,��ʱ������
    float          fUbl;           // ����ʱ��ѹ��ƽ���  (+)XX.XX(%)
    float          fUa;            // ����ʱ��Ua/Uab      (+)XXX.X
    float          fUb;            // ����ʱ��Ub          (+)XXX.X
    float          fUc;            // ����ʱ��Ub          (+)XXX.X
}sMcErcUblOverV, sMcErc15;

// ��֡��
#pragma pack(1)
typedef struct
{
    UINT16         usPN;           // P0/����ն˺�
    sMcYMDhm_f     sTime;          // �¼�����ʱ��,��ʱ������
    sMcFmt10_f     fUbl;
    sMcFmt08_f     fUa;
    sMcFmt08_f     fUb;
    sMcFmt08_f     fUc;
}sMcErcUblOverV_f, sMcErc15_f;
#pragma pack()

// ת������
eMcErr emc_trans_erc_15(eMcTrans eTrans, void* pUser, void* pFrame, UINT16* pusLen);
///*}

/*******************************************
 * ��������: ������ƽ���Խ���¼�
 * ��ӦAFN : MC_AFN_14_ASKE
 * ��ӦERC : MC_ERC_16_UNBL_OVER_I
 *
{*///
// �û���
typedef struct
{
    UINT16         usPN;           // P0/����ն˺�
    BOOL           bStart;         // TRUE ���� FALSE �ָ�
    sMcYMDhm       sTime;          // �¼�����ʱ��,��ʱ������
    float          fUbl;           // ����ʱ������ƽ��� 
    float          fIa;            // ����ʱ��Ia        (+/-)XXX.XXX
    float          fIb;            // ����ʱ��Ib        (+/-)XXX.XXX
    float          fIc;            // ����ʱ��Ic        (+/-)XXX.XXX
}sMcErcUblOverI, sMcErc16;

// ��֡��
#pragma pack(1)
typedef struct
{
    UINT16         usPN;           // P0/����ն˺�
    sMcYMDhm_f     sTime;          // �¼�����ʱ��,��ʱ������
    sMcFmt10_f     fUbl;
    sMcFmt09_f     fIa;            // ����ʱ��Ia        (+/-)XXX.XXX
    sMcFmt09_f     fIb;            // ����ʱ��Ib        (+/-)XXX.XXX
    sMcFmt09_f     fIc;            // ����ʱ��Ic        (+/-)XXX.XXX
}sMcErcUblOverI_f, sMcErc16_f;
#pragma pack()

// ת������
eMcErr emc_trans_erc_16(eMcTrans eTrans, void* pUser, void* pFrame, UINT16* pusLen);
///*}

/*******************************************
 * ��������: г����ѹ������Խ���¼�
 * ��ӦAFN : MC_AFN_14_ASKE
 * ��ӦERC : MC_ERC_17_HUNBL_OVER_V
 *
{*///
// �û���
typedef struct
{
    UINT16         usPN;           // P0/����ն˺�
    sMcYMDhm       sTime;          // �¼�����ʱ��,��ʱ������
    BOOL           bPhaseA;        // A�෢��Խ��
    BOOL           bPhaseB;        // B�෢��Խ��
    BOOL           bPhaseC;        // C�෢��Խ��
    BOOL           bTotal;         // A�෢��Խ��
    BOOL           bOdd;           // B�෢��Խ��
    BOOL           bEven;          // C�෢��Խ��
    float          fTotal;         // ����ʱ��г����ѹ�ܻ�����   (+)XX.XX 
    float          fOdd;           // ����ʱ��г����ѹ��λ����� (+)XX.XX 
    float          fEven;          // ����ʱ��г����ѹż�λ����� (+)XX.XX 
}sMcErcHublOverV, sMcErc17;

// ��֡��
#pragma pack(1)
typedef struct
{
    UINT16         usPN;           // P0/����ն˺�
    sMcYMDhm_f     sTime;          // �¼�����ʱ��,��ʱ������
    UINT8          ucExcp;         // Խ�ޱ�־
    sMcFmt10_f     fTotal;         // ����ʱ��г����ѹ�ܻ�����   
    sMcFmt10_f     fOdd;           // ����ʱ��г����ѹ��λ�����
    sMcFmt10_f     fEven;          // ����ʱ��г����ѹż�λ�����
}sMcErcHublOverV_f, sMcErc17_f;
#pragma pack()

// ת������
eMcErr emc_trans_erc_17(eMcTrans eTrans, void* pUser, void* pFrame, UINT16* pusLen);
///*}

/*******************************************
 * ��������: г������������Խ���¼�
 * ��ӦAFN : MC_AFN_14_ASKE
 * ��ӦERC : MC_ERC_18_HUNBL_OVER_I
 *
{*///
// �û���
typedef sMcErcHublOverV sMcErcHublOverI, sMcErc18;

// ��֡��

// ת������
eMcErr emc_trans_erc_18(eMcTrans eTrans, void* pUser, void* pFrame, UINT16* pusLen);
///*}

/*******************************************
 * ��������: ����Խ���¼�
 * ��ӦAFN : MC_AFN_14_ASKE
 * ��ӦERC : MC_ERC_19_FLASH_OVER
 *
{*///
// �û���
typedef struct
{
    UINT16         usPN;           // P0/����ն˺�
    sMcYMDhm       sTime;          // �¼�����ʱ��,��ʱ������
    BOOL           bPhaseA;        // A�෢��Խ��
    BOOL           bPhaseB;        // B�෢��Խ��
    BOOL           bPhaseC;        // C�෢��Խ��
    BOOL           bLong;          // �Ƿ�Ϊ������ ��Ϊ������
    float          fA;             // ����ʱ��A������ֵ   (+)XX.XX 
    float          fB;             // ����ʱ��B������ֵ   (+)XX.XX 
    float          fC;             // ����ʱ��C������ֵ   (+)XX.XX 
}sMcErcFlashOver, sMcErc19;

// ��֡��
#pragma pack(1)
typedef struct
{
    UINT16         usPN;           // P0/����ն˺�
    sMcYMDhm_f     sTime;          // �¼�����ʱ��,��ʱ������
    UINT8          ucExcp;         // Խ�ޱ�־
    sMcFmt10_f     fA;             // ����ʱ��A������ֵ   
    sMcFmt10_f     fB;             // ����ʱ��B������ֵ
    sMcFmt10_f     fC;             // ����ʱ��C������ֵ
}sMcErcFlashOver_f, sMcErc19_f;
#pragma pack()

// ת������
eMcErr emc_trans_erc_19(eMcTrans eTrans, void* pUser, void* pFrame, UINT16* pusLen);
///*}

/*******************************************
 * ��������: �ǵ�����Խ���¼�
 * ��ӦAFN : MC_AFN_14_ASKE
 * ��ӦERC : MC_ERC_20_NELC_OVER
 *
{*///
// �û���
typedef struct
{
    UINT16         usPN;           // P0/����ն˺�
    BOOL           bStart;         // �¼���ֹ
    sMcYMDhm       sTime;          // �¼�����ʱ��,��ʱ������
    BOOL           bUp;            // A�෢��Խ��
    BOOL           bDown;          // B�෢��Խ��
    sMcNelcValue   sValue;
}sMcErcNelcOver, sMcErc20;

// ��֡��
#pragma pack(1)
typedef struct
{
    UINT16         usPN;           // P0/����ն˺�
    sMcYMDhm_f     sTime;          // �¼�����ʱ��,��ʱ������
    UINT8          ucExcp;         // Խ�ޱ�־
    sMcNelcValue_f sValue;
}sMcErcNelcOver_f, sMcErc20_f;
#pragma pack()

// ת������
eMcErr emc_trans_erc_20(eMcTrans eTrans, void* pUser, void* pFrame, UINT16* pusLen);
///*}

/*******************************************
 * ��������: ������Ҫ�¼�(Ӧ���ʽ)
 * ��ӦAFN : MC_AFN_14_ASKE
 * ��ӦCMD : MCMD_AFN_E_F1_EVENT_1
 * PN ���� : P0
 * ����˵��:
 *     ��������¼���¼����Y�������м��㹫ʽ��
 *     (1)��Pm��Pnʱ��Y= Pn-Pm
 *     (2)��Pm��Pnʱ��Y= 256��Pn-Pm
 * 
{*///
typedef union
{
    sMcErc1    sReset;           // ��Ӧ MC_ERC_1_RESET
    sMcErc2    sDataClear;       // ��Ӧ MC_ERC_2_DATA_CLEAR
    sMcErc3    sChangeSoft;      // ��Ӧ MC_ERC_3_SOFT_CHANGE
    sMcErc4    sParaChange;      // ��Ӧ MC_ERC_4_PARA_CHANGE
    sMcErc5    sTimeCheck;       // ��Ӧ MC_ERC_5_CHECK_TIME
    sMcErc6    sChangeState;     // ��Ӧ MC_ERC_6_STATE_CHANGE
    sMcErc7    sRemoteSwitch;    // ��Ӧ MC_ERC_7_REMOTE_SWITCH
    sMcErc8    sPowerOnOff;      // ��Ӧ MC_ERC_8_POWER_ON_OFF
    sMcErc9    sFactorOver;      // ��Ӧ MC_ERC_9_FACTOR_OVER
    sMcErc10   sVoltExcp;        // ��Ӧ MC_ERC_10_VOLT_EXCP
    sMcErc11   sVoltCircle;      // ��Ӧ MC_ERC_11_VOLT_CIRCLE
    sMcErc12   sElecCircle;      // ��Ӧ MC_ERC_12_ELEC_CRICLE
    sMcErc13   sVoltOver;        // ��Ӧ MC_ERC_13_VOLT_OVER
    sMcErc14   sElecOver;        // ��Ӧ MC_ERC_14_ELEC_OVER
    sMcErc15   sUblOverV;        // ��Ӧ MC_ERC_15_UNBL_OVER_V
    sMcErc16   sUblOverI;        // ��Ӧ MC_ERC_16_UNBL_OVER_I
    sMcErc17   sHublOverV;       // ��Ӧ MC_ERC_17_HUNBL_OVER_V
    sMcErc18   sHublOverI;       // ��Ӧ MC_ERC_18_HUNBL_OVER_I
    sMcErc19   sFlashOver;       // ��Ӧ MC_ERC_19_FLASH_OVER
    sMcErc20   sNelcOver;        // ��Ӧ MC_ERC_20_NELC_OVER
}uMcRec;       // �¼���¼���ݽṹ

typedef struct
{
    eMcErc   eType;          // �¼�����
    uMcRec    uRec;          // �¼���¼���ݽṹ
}sMcErc;

// �û���
typedef struct
{
    UINT16  usEc1;           // ��ǰ��Ҫ�¼�������EC1
    UINT16  usEc2;           // ��ǰһ���¼�������EC2
    UINT8    ucPm;           // �����¼���¼��ʼָ��Pm
    UINT8    ucPn;           // �����¼���¼����ָ��Pn
    sMcErc  sErc[1];         //  Y���¼���¼     
}sMcEventImpA, sMcAfn14f1A;

// ��֡��
#pragma pack(1)
typedef struct
{
    UINT16  usEc1;           // ��ǰ��Ҫ�¼�������EC1
    UINT16  usEc2;           // ��ǰһ���¼�������EC2
    UINT8   ucPm;            // �����¼���¼��ʼָ��Pm
    UINT8   ucPn;            // �����¼���¼����ָ��Pn
    UINT8   ucT1;            // �¼�����1 
    UINT8   ucLe1;           // �¼����ݳ���1
    UINT8   ucD1[1];         // �¼���������

    /*����Ϊ�䳤*/
}sMcEventImpA_f, sMcAfn14f1A_f;
#pragma pack()

// ��������
pMcFunc pMcGetRec(eMcErc eType);

// ת������
eMcErr emc_trans_afn14f1_s2m(eMcTrans eTrans, void* pUser, void* pFrame, UINT16* pusLen);
///*} 

/*******************************************
 * ��������: ����һ���¼�(Ӧ���ʽ)
 * ��ӦAFN : MC_AFN_14_ASKE
 * ��ӦCMD : MCMD_AFN_E_F2_EVENT_2
 * PN ���� : P0
 * ����˵��:
 *     ��������¼���¼����Y�������м��㹫ʽ��
 *     (1)��Pm��Pnʱ��Y= Pn-Pm
 *     (2)��Pm��Pnʱ��Y= 256��Pn-Pm
 * 
{*///
// �û���
typedef sMcEventImpA sMcEventNmlA;

// ��֡��

// ת������
eMcErr emc_trans_afn14f2_s2m(eMcTrans eTrans, void* pUser, void* pFrame, UINT16* pusLen);
///*} 

/*******************************************
 * ��������: ����ָ���¼�(Ӧ���ʽ)
 * ��ӦAFN : MC_AFN_14_ASKE
 * ��ӦCMD : MCMD_AFN_E_F3_EVENT_3
 * PN ���� : P0
 * 
{*///
// �û���
typedef struct
{
    eMcErc       eType;     // �¼�����
    UINT8          ucM;     // ���¼���¼������
    uMcRec   uRec[255];     // �¼���¼���ݽṹ (Ϊ��ռλ���ò�255)
                            // ��ʱ��Ϊ1,���ϲ�ռ䲻��,Ӧ��Ϊ255
}sMcSpeErc;

typedef struct
{
    UINT8      ucN;         // �¼���¼������n
    sMcSpeErc sErc[1];      //  ucN���¼���¼  
}sMcEventSpeA, sMcAfn14f3A;

// ��֡��
#pragma pack(1)
typedef struct
{
    UINT8     ucN;         // �¼���¼������n
    UINT8     ucErc1;      // ��һ���¼�����ERC  
    UINT8     ucM1;        // ��һ���¼�����ERC���¼���¼��m 
    UINT8     ucLe1;       // ��һ���¼�����ERC���¼���¼���ݵ�Ԫ����Le

    /* ����Ϊ�䳤
    // ��һ���¼�����ERC�ĵ�һ���¼���¼���ݵ�Ԫ
                 ...............
    // ��һ���¼�����ERC�ĵ�m ���¼���¼���ݵ�Ԫ


    // ��n ���¼�����ERC
    // ��n ���¼�����ERC���¼���¼��m 
    // ��n ���¼�����ERC���¼���¼���ݵ�Ԫ����Le
    // ��n ���¼�����ERC�ĵ�һ���¼���¼���ݵ�Ԫ
                 ...............
    // ��n ���¼�����ERC�ĵ�m ���¼���¼���ݵ�Ԫ
    */
}sMcEventSpeA_f, sMcAfn14f3A_f;
#pragma pack()
// ת������
eMcErr emc_trans_afn14f3_s2m(eMcTrans eTrans, void* pUser, void* pFrame, UINT16* pusLen);
///*} 

/*******************************************
 * ��������: �������(�����ʽ-����)
 * ��ӦAFN : MC_AFN_15_FILE
 * ��ӦCMD : MCMD_AFN_F_F1_SOFT_DOWN
 * PN ���� : P0
 *
{*///
// �û���
typedef struct
{
    UINT8   ucFlag;       // �����ʶ��
                          //��00H������������ļ����ָ�������ǰ״̬��
                          //��01H�����豸�����
                          //  ���� ����ģ���������
    UINT8   ucVersion[4]; // ����汾                      
    UINT8   ucPos;        // �ļ����ԣ�
                          //��00H������ʼ���м�֡��
                          //��01H��������֡��
                          //  ���� �����ã�
                          
    UINT8   ucWay;        // �ļ�ָ�
                          //��00H�������ķ�ʽ���䣻
                          //��01H����FTP��ʽ���䣻
                          //��02H�����������ַ��
                          //  ���� �����ã�    
    UINT16  usN;          // �ܶ���n
    UINT32  i;            // ��i �α�ʶ��ƫ�ƣ�i=0��n���������һ���⣬�������ȹ̶���
    UINT16  usLen;        // ��i �����ݳ���
    UINT8   ucData[1];    // �ļ����ݣ� ���� usLen 
                          // ���Ĵ���ʱ���ļ����� 
                          // FTP����ʱ��ftp��//�ļ�·�����˺�/���� 
                          //  ����ļ����������ַʱ����
                          
}sMcSoftDownQ, sMcAfn15f1Q;

// ��֡��
#pragma pack(1)
typedef struct
{
   UINT8   ucFlag;        // �����ʶ��
                          //��00H������������ļ����ָ�������ǰ״̬��
                          //��01H�����豸�����
                          //  ���� ����ģ���������
    UINT8   ucVersion[4]; // ����汾                      
    UINT8   ucPos;        // �ļ����ԣ�
                          //��00H������ʼ���м�֡��
                          //��01H��������֡��
                          //  ���� �����ã�
                          
    UINT8   ucWay;        // �ļ�ָ�
                          //��00H�������ķ�ʽ���䣻
                          //��01H����FTP��ʽ���䣻
                          //��02H�����������ַ��
                          //  ���� �����ã�    
    UINT16  usN;          // �ܶ���n
    UINT32  i;            // ��i �α�ʶ��ƫ�ƣ�i=0��n���������һ���⣬�������ȹ̶���
    UINT16  usLen;        // ��i �����ݳ���
    UINT8   ucData[1];    // �ļ����ݣ� ���� usLen 
                          // ���Ĵ���ʱ���ļ����� 
                          // FTP����ʱ��ftp��//�ļ�·�����˺�/���� 
                          //  ����ļ����������ַʱ����
}sMcSoftDownQ_f, sMcAfn15f1Q_f;
#pragma pack()

// ת������
eMcErr emc_trans_afn15f1_m2s(eMcTrans eTrans, void* pUser, void* pFrame, UINT16* pusLen);
///*} 


///*} 

/***************************************
 *  ͨ�ò��ַ�װ����  (�ͼ�����)
 *  �ڸú�����ʵ�ּ�������ܹ���
 *  �������͵�֡
 *  (1) �̶�֡
 *
 *  +------+------+------+------+------+------+------+------+
 *  |       ��ʼ�ַ�(10H)       |          �����ַ�         |
 *  |------+------+------+------+------+------+------+------|
 *  |          ������C          |                           |
 *  |------+------+------+------|                           |  
 *  |          ��ַ��A          |          �û�����         |
 *  |------+------+------+------|                           |  
 *  |        ��·�û�����       |                           |
 *  |------+------+------+------+------+------+------+------|  
 *  |          У���CS         |           ֡У��          |
 *  +------+------+------+------+------+------+------+------+  
 *  
 *  ��·�û�����
 *  +------+------+------+------+
 *  |         Э���ʶ          |
 *  +------+------+------+------+
 *
 *  (2) �ɱ�֡
 *
 *  +------+------+------+------+------+------+------+------+
 *  |        ��ʼ�ַ�(68H)      |                           |
 *  |------+------+------+------|                           |  
 *  |           ����L           |                           |
 *  |------+------+------+------|            ֡ͷ           |  
 *  |           ����L           |                           |
 *  |------+------+------+------|                         |  
 *  |        ��ʼ�ַ�(68H)      |                           |
 *  |------+------+------+------+------+------+------+------|  
 *  |          ������C          |                           |
 *  |------+------+------+------|                           |  
 *  |          ��ַ��A          |        �û�����           |
 *  |------+------+------+------|                           |  
 *  |        ��·�û�����       |                           |
 *  |------+------+------+------+------+------+------+------|  
 *  |          У���CS         |          ֡У��           |
 *  |------+------+------+------+------+------+------+------|  
 *  |        �����ַ�(16H)      |         ֡������          |
 *  +------+------+------+------+------+------+------+------+  
 *
 *  ��·�û�����
 *  +------+------+------+------+
 *  |         Э���ʶ          |
 *  |------+------+------+------|
 *  |        Ӧ�ÿ�����AC       |
 *  |------+------+------+------|
 *  |       ���ݵ�Ԫ��ʶ1       |
 *  |------+------+------+------|
 *  |         ���ݵ�Ԫ1         |
 *  |------+------+------+------|
 *  |         .........         |
 *  |------+------+------+------|
 *  |       ���ݵ�Ԫ��ʶn       |
 *  |------+------+------+------|
 *  |         ���ݵ�Ԫn         |
 *  |------+------+------+------|
 *  |       ������Ϣ��AUX       |
 *  +------+------+------+------+
 *
 *  ˵��:
 *  У���CS:ȫ���û����ݵ��㷨��, �����ǽ�λ
 *
{*///

// �û�������
typedef struct
{
    sMcAddress    sAddress;      // ��ַ�� A
    sMctrl        sCtrl;         // ������ C
    //sMcAc         sAc;           // Ӧ�ÿ�����Ac(Tp Ec Afn)    // �����ϲ㴦��
    BOOL          bFixed;        // �̶�֡ ���� �ɱ�֡ 
    UINT16        usA2CsLen;     // ��addr �� Cs ֮������ݳ���
    UINT8         *pA2CsData;    // ��addr �� Cs ֮�����������
    
}sMcPackCommon;


// ����֡ͷ
// �̶�֡


#pragma pack(1)
typedef struct
{
    UINT8   f10;      // ��ʼ�ַ�(10H) 
    UINT16  usC;      // ������C
    sMcA_f  stA;      // ��ַ��A
    UINT8   ucV;      // ��Э��汾 ��ֵ MC_PROTO_VERSION    
    UINT8   ucS;      // У���CS
    UINT8   ucE;      // ������
}sMcfHeadFixed;

// �ɱ�֡
typedef struct
{
    UINT8   f68;      // ��һ�� ��ʼ�ַ�(68H)
    UINT16  usL1;     // ��һ������L
    UINT16  usL2;     // �ڶ�������L
    UINT8   s68;      // �ڶ��� ��ʼ�ַ�(68H)
    UINT16  usC;      // ������C
    sMcA_f  stA;      // ��ַ��A
    UINT8   ucV;      // ��Э��汾 ��ֵ MC_PROTO_VERSION  
    UINT8   ucAc;     // Ӧ�ÿ�����AC
    
}sMcfHeadAlter;
#pragma pack()

// ������ͺ���(У�����ȫ���û����ݵ�������,�����ǽ�λ(ģ256))
UINT8 ucmc_get_check_sum(UINT8 *pStartPos, UINT16 usLen);

// ��װÿ��֡�Ĺ������� 
eMcErr emc_pack_common(sMcPackCommon *psCommon,  UINT16 *pusLen, UINT8  *pOutBuf); 

// ������������
// ��������
eMcErr emc_unpack_common(sMcPackCommon *psUnpack, UINT8* pInBuf, UINT16 usLen);
///*}

/*******************************************************
 *  �ⲿ�ӿ�(�û�ֻ��������½ӿ�)
 *
{*///

/***************************************
 *  Э��ģ���ʼ��
 *  ʹ��Э��API��Ҫ�Ƚ��г�ʼ��
 *  
{*///
typedef struct
{
    eMcRole eRole;                  // ��ݣ���վ���Ǵ�վ
    UINT8   ucPermitDelayMinutes;   // ����ʱ��

#if  MC_CFG_SPT_MST   
    UINT8   aucPw[MC_PW_LEN];       // ��Ϣ��֤�� �������б�����
#endif

#if MC_CFG_ENCRYPT
    peMcEncryptFunc   EncryptFunc;  // ���ܽӿ�
    peMcDecryptFunc   DecryptFunc;  // ���ܽӿ�
#endif
    
}sMcInit;                           // Э���ʼ�����ݽṹ

// ��ʼ������
eMcErr eMcInit(sMcInit* psInit);
///*}

// �ж��Ƿ�����һ��Ч֡
eMcErr emcIsValidPack(const UINT8* pInBuf, UINT16 usLen, BOOL *pbFiexed);

// �ҵ���һ����Ч��λ�ü��䳤��
eMcErr emcFindValidPack(UINT8* pinBuf, UINT16 usLen, UINT16* pusFirstOff, UINT16* pusFirstLen);

/***************************************************************************
 *  ���ݵ�Ԫ Ӧ�ò����ݽṹ����
 *  ����������ͬ���͵����ݽṹ��ʱ��һ����
 *  
 *  �ն�����Ӧ��վ���ն˵Ĳ�������������ʱ,
 *    ���ն�û�������ĳ��������,��Ӧ������DT�Ķ�Ӧ��־λ�����
 *    ���ն˽���û��ĳ���������еĲ������ݣ���Ӧ�����������е���ȱ����
 *    ���ݵ�ÿ���ֽ���д��EEH����
 *    ע��:����չӦ�ò����ݵ�Ԫʱ,��Ҫ��ÿ��������Ϊÿ����������� 
 *         ��/�޵ı�ʶ ������һ��BOOL ����ʾ 
 *  
{*///
typedef union
{
  /***************************************
     *  ������ͨ��
     *  ��վ����վ �� ��վ����վ
     *  ˫��ͬ�������ݽṹ
    {*///
    
    // MCMD_AFN_0_F1_ALL_OK_DENY
    // ȫ��ȷ��/���ϣ����յ������е�ȫ�����ݵ�Ԫ��ʶ����ȷ��/����
    eMcResCode            eResCode;         

    // MCMD_AFN_0_F2_ONE_BY_ONE
    // �����ݵ�Ԫ��ʶȷ�Ϻͷ��ϣ����յ������е�ȫ�����ݵ�Ԫ��ʶ�������ȷ��/����
    sMcOnebyOne           sOneByOne;        

    // MCMD_AFN_4_F1_CON_UP_CFG
    // MCMD_AFN_A_F1_CON_UP_CFG Ӧ��
    // ��Ϣ�����뽻���ն�����ͨ�ſ�ͨ�Ų��� 
    sMcUpCfg              sConUpCfg;       

    // MCMD_AFN_4_F2_MST_PARA
    // MCMD_AFN_A_F2_MST_PARA Ӧ��
    // ��Ϣ�����뽻���ն�����ͨ�ſ�ͨ�Ų���
    sMcMstPara            sMstPara;       

    // MCMD_AFN_4_F3_CON_AUTH_PARA
    // MCMD_AFN_A_F3_CON_AUTH_PARA
    // ��Ϣ�����뽻���ն�����ͨ����Ϣ��֤����
    sMcAuthPara           sAuthPara;       

    // MCMD_AFN_4_F4_TEAM_ADDR
    // MCMD_AFN_A_F4_TEAM_ADDR Ӧ��
    // ��Ϣ�����뽻���ն����ַ
    sMcTeamAddr           sTeamAddr;     
    
    // MCMD_AFN_4_F5_CON_IP_PORT
    // MCMD_AFN_A_F5_CON_IP_PORT Ӧ��
    // ��Ϣ�����뽻���ն�IP��ַ�Ͷ˿�
    sMcIpPort             sIpPort;          

    // MCMD_AFN_4_F6_CON_CASC
    // MCMD_AFN_A_F6_CON_CASC Ӧ��
    // ��ѯ��Ϣ�����뽻���ն˼���ͨ�Ų���
    sMcasc                sCasc;
    
    // MCMD_AFN_4_F7_CON_DOWN_CFG
    // ��Ϣ�����뽻���ն�������̫���˿�ͨ�Ų���
    sMcDownCfg            sDownCfg;        
    
    // MCMD_AFN_4_F9_CON_EVENT_CFG
    // MCMD_AFN_A_F9_CON_EVENT_CFG
    // �¼���¼����
    sMcEventCfg           sEventCfg;       

    // MCMD_AFN_4_F10_CON_STATE_INPUT
    // MCMD_AFN_A_F10_CON_STATE_INPUT Ӧ��
    // �豸״̬���������
    sMcStateInput         sStateInput;     
        
    // MCMD_AFN_4_F17_TML_UP_CFG
    // MCMD_AFN_A_F17_TML_UP_CFG Ӧ��
    // ����ն�����ͨ�Ų�������
    sMcTmlUpCfg           sTmlUpCfg;       

    // MCMD_AFN_4_F25_ELEC_MP_CFG
    // MCMD_AFN_A_F25_ELEC_MP_CFG Ӧ��
    // �������������ò���
    sMcElecMpCfg          sElecMpCfg;      

    // MCMD_AFN_4_F26_ELEC_MP_BASE
    // MCMD_AFN_A_F26_ELEC_MP_BASE Ӧ��
    // �����������������
    sMcElecMpBase         sElecMpBase;     

    // MCMD_AFN_4_F27_ELEC_LMIT_POWER
    // MCMD_AFN_A_F27_ELEC_LMIT_POWER Ӧ��
    // �����������������ֵ����
    sMcElecLimitPower     sElecLimitPower; 

    // MCMD_AFN_4_F28_ELEC_LMIT_FACTR
    // MCMD_AFN_A_F28_ELEC_LMIT_FACTR Ӧ��
    // ���������㹦������Խ��ֵ����
    sMcFactorLimit        sFactorLimit;    

    // MCMD_AFN_4_F29_ELEC_FIX_HARM
    // MCMD_AFN_A_F29_ELEC_FIX_HARM Ӧ��
    // ����������г��������Խ�޶�ֵ
    sMcElecFixHarm        sElecFixHarm;    

    // MCMD_AFN_4_F30_ELEC_FLASH
    // MCMD_AFN_A_F30_ELEC_FLASH Ӧ��
    // ��������������Խ�޲���
    sMcElecFlash          sElecFlash;      
    
    // MCMD_AFN_4_F33_NELC_MP_CFG
    // MCMD_AFN_A_F33_NELC_MP_CFG Ӧ��
    // �ǵ������������ò���
    sMcNelecMpCfg         sNelecMpCfg;   

    // MCMD_AFN_4_F34_NELC_MP_PARA
    // MCMD_AFN_A_F34_NELC_MP_PARA Ӧ��
    // �ǵ������������ݲ���
    sMcNelcMpPara          sNelcMpPara;      

    // MCMD_AFN_4_F35_NELC_MP_LMIT
    // MCMD_AFN_A_F35_NELC_MP_LMIT Ӧ��
    sMcNelcMpLimit        sNelcMpLimit;     
    // �ǵ���������Խ�����ݲ���
    
    // MCMD_AFN_4_F49_FREZ_TASK_PARA
    // MCMD_AFN_A_F49_FREZ_TASK_PARA
    // ���������������
    sMcFrezTaskPara       sFrezTaskPara;    
    ///*}

    /***************************************
     *  ����
     *  ��վ����վ
     *  ͨ����Ӧ�� ��Ӧ
     *  ���µ�������������
     * MCMD_AFN_2_F1_LOG_IN
     * MCMD_AFN_2_F2_LOG_OUT
     * MCMD_AFN_2_F3_HEART_BEAT
     *
     *
    {*///
 
    // MCMD_AFN_A_F7_CON_DOWN_CFG
    // ��Ϣ�����뽻���ն�������̫���˿�ͨ�Ų���
    sMcDownCfgA           sDownCfgA;        
    
    // MCMD_AFN_A_F11_CON_LOGIC_ADDR
    // �豸�߼���ַ
    sMcLogicAddr          sLogicAddr;      

    // MCMD_AFN_A_F12_CON_VERSION
    // ��ѯ�豸�汾��Ϣ
    sMcVersion            sVersion;        

    // MCMD_AFN_A_F13_ELEC_MP_INFO
    // �����õ�����������Ϣ
    sMcElecMpInfo         sElecMpInfo;      

    // MCMD_AFN_A_F14_NELC_MP_INFO
    // �����÷ǵ�����������Ϣ
    sMcNelcMpInfo         sNelcMpInfo;     

    // MCMD_AFN_A_F15_SUPT_EVENT
    // �豸֧�ֵ��¼���¼
    sMcSuptEvent          sSuptEvent;       

    // MCMD_AFN_A_F57_TML_CFG_INFO
    // ��ѯ�����ü���ն���Ϣ
    sMcTmlCfgInfo         sTmlCfgInfor;     

    // MCMD_AFN_D_F1_CLOCK
    sMcUerClock           sUerClock;
    
    // MCMD_AFN_D_F2_PARA_STATE
    // ����״̬��־
    sMcParaState          sParaState;       

    // MCMD_AFN_D_F3_EVENT_1
    // ��Ҫ�¼���������ǰֵ
    UINT16                usEc1;            

    // MCMD_AFN_D_F4_EVENT_2
    // һ���¼���������ǰֵ
    UINT16                usEc2;           

    // MCMD_AFN_D_F5_EVENT_STATE
    // �¼�״̬��־
    sMcEventState         sEventState;      

    // MCMD_AFN_D_F6_POWR_TIMES
    sMcPowerTimes         sPowerTimes;

    // MCMD_AFN_D_F9_STATE 
    // ״̬������λ��־
    sMcState              sState;           
    
    // MCMD_AFN_D_F10_SWITCH 
    // ���������·���ؽ���״̬������λ��־
    sMcSwitch             sSwitch;           
  
    // MCMD_AFN_D_F25_POWR_HAVE_T  ���й�����
    sMcPowerHaveT         sPowerHaveT;
    
    // MCMD_AFN_D_F26_POWR_NONE_T         
    // ���޹�����
    sMcPowerNoneT         sPowerNoneT;      
    
    // �ܹ�������
    // MCMD_AFN_D_F27_FACTR_T               
    sMcFactorT            sFactorT;
    
    // MCMD_AFN_D_F28_FACTR_A               
    // A�๦������
    sMcFactorA            sFactorA;
    
    // MCMD_AFN_D_F29_FACTR_B               
    // B�๦������
    sMcFactorB            sFactorB;
    
    // MCMD_AFN_D_F30_FACTR_C               
    // C�๦������
    sMcFactorC            sFactorC;
    
    // MCMD_AFN_D_F33_DEMAND                
    // ����
    sMcDemand             sDemand;
    
    // MCMD_AFN_D_F34_DEMAND_MAX             
    // ���������
    sMcDemandMax          sDemandMax;

    // MCMD_AFN_D_F35_DEMAND_TIME           
    // �������������ʱ��
    sMcDemandTime         sDemandTime;

    // MCMD_AFN_D_F41_POWR_HAVE_A            
    // A���й�����
    sMcPowerHaveA         sPowerHaveA;

    // MCMD_AFN_D_F42_POWR_HAVE_B            
    // B���й�����
    sMcPowerHaveB sPowerHaveB;

    // MCMD_AFN_D_F43_POWR_HAVE_C           
    // C���й�����
    sMcPowerHaveC sPowerHaveC;

    // MCMD_AFN_D_F44_POWR_NONE_A           
    // A���޹�����
    sMcPowerNoneA sPowerNoneA;

    // MCMD_AFN_D_F45_POWR_NONE_B           
    // B���޹�����
    sMcPowerNoneB sPowerNoneB;

    // MCMD_AFN_D_F46_POWR_NONE_C            
    // C���޹�����
    sMcPowerNoneC sPowerNoneC;

    // MCMD_AFN_D_F49_POWR_HAVE_FRTH         
    // �������й��ܵ���ʾ��
    sMcPowerHaveFrth sPowerHaveFrth;

    // MCMD_AFN_D_F50_POWR_HAVE_BACK         
    // �������й��ܵ���ʾ��
    sMcPowerHaveBack sPowerHaveBack;

    // MCMD_AFN_D_F51_POWR_NONE_FRTH         
    // �������޹��ܵ���ʾ��
    sMcPowerNoneFrth sPowerNoneFrth;

    // MCMD_AFN_D_F52_POWR_NONE_BACK         
    // �������޹��ܵ���ʾ��
    sMcPowerNoneBack sPowerNoneBack;

    // MCMD_AFN_D_F57_VOLT_A                 
    // A���ѹ
    sMcVoltA sVoltA;

    // MCMD_AFN_D_F58_VOLT_B                
    // B���ѹ
    sMcVoltB sVoltB;

    // MCMD_AFN_D_F59_VOLT_C                
    // C���ѹ
    sMcVoltC sVoltC;

    // MCMD_AFN_D_F60_VANGL_A                
    // A���ѹ��λ��
    sMcVAngleA sVAngleA;

    // MCMD_AFN_D_F61_VANGL_B                
    // B���ѹ��λ��
    sMcVAngleB sVAngleB;

    // MCMD_AFN_D_F62_VANGL_C                
    // C���ѹ��λ��
    sMcVAngleC sVAngleC;

    // MCMD_AFN_D_F63_VOLT_UBL               
    // ��ѹ��ƽ���
    sMcVoltUbl sVoltUbl;

    // MCMD_AFN_D_F64_CIRCLE_V               
    // �ܲ�
    sMcVCircle sVCircle;

    // MCMD_AFN_D_F65_ELEC_A                 
    // A�����
    sMcElecA sElecA;

    // MCMD_AFN_D_F66_ELEC_B                 
    // B�����
    sMcElecB sElecB;

    // MCMD_AFN_D_F67_ELEC_C                  
    // C�����
    sMcElecC sElecC;

    // MCMD_AFN_D_F68_ELEC_M                  
    // �����ߵ���
    sMcElecM sElecM;

    // MCMD_AFN_D_F69_EANGL_A                 
    // A�������λ��
    sMcEAngleA sEAngleA;

    // MCMD_AFN_D_F70_EANGL_B                 
    // B�������λ��
    sMcEAngleB sEAngleB;

    // MCMD_AFN_D_F71_EANGL_C                 
    // C�������λ��
    sMcEAngleC sEAngleC;

    // MCMD_AFN_D_F72_ELEC_UBL               
    // ������ƽ���
    sMcElecUbl sElecUbl;

    // MCMD_AFN_D_F73_VDMAX_A                
    // ��A���ѹ����ֵ
    sMcVMaxA sVMaxA;

    // MCMD_AFN_D_F74_VDMAX_A_TIME            
    // ��A���ѹ����ֵ����ʱ��
    sMcVMaxATime sVMaxATime;

    // MCMD_AFN_D_F75_VDMAX_B                 
    // ��A���ѹ����ֵ
    sMcVMaxB sVMaxB;

    // MCMD_AFN_D_F76_VDMAX_B_TIME           
    // ��A���ѹ����ֵ����ʱ��
    sMcVMaxBTime sVMaxBTime;

    // MCMD_AFN_D_F77_VDMAX_C                
    // ��A���ѹ����ֵ
    sMcVMaxC sVMaxC;

    // MCMD_AFN_D_F78_VDMAX_C_TIME            
    // ��A���ѹ����ֵ����ʱ��
    sMcVMaxCTime sVMaxCTime;

    // MCMD_AFN_D_F81_IDMAX_A                 
    // ��A���������ֵ
    sMcIMaxA sIMaxA;

    // MCMD_AFN_D_F82_IDMAX_A_TIME            
    // ��A���������ֵ����ʱ��
    sMcIMaxATime sIMaxATime;

    // MCMD_AFN_D_F83_IDMAX_B                 
    // ��B���������ֵ
    sMcIMaxB sIMaxB;

    // MCMD_AFN_D_F84_IDMAX_B_TIME            
    // ��B���������ֵ����ʱ��
    sMcIMaxBTime sIMaxBTime;

    // MCMD_AFN_D_F85_IDMAX_C                
    // ��C���������ֵ
    sMcIMaxC sIMaxC;

    // MCMD_AFN_D_F86_IDMAX_C_TIME           
    // ��C���������ֵ����ʱ��
    sMcIMaxCTime sIMaxCTime;
    
    // MCMD_AFN_D_F89_TFW_HAVE              
    // �ܻ����й�����  
    sMcTfwHave sTfwHave;

    // MCMD_AFN_D_F90_TFW_NONE                
    // �ܻ����޹�����
    sMcTfwNone sTfwNone;
    
    // MCMD_AFN_D_F91_THW_HAVE                
    // ��г���й�����
    sMcThwHave sThwHave;
    
    // MCMD_AFN_D_F92_THW_NONE                
    // �ܻ����޹�����
    sMcThwNone sThwNone;
    
    // MCMD_AFN_D_F97_VDPP_TIME_A             
    // A���ѹԽ���������ۼ�ʱ��
    sMcVDppTimeA  sVDppTimeA;

    // MCMD_AFN_D_F98_VDPP_TIME_B             
    // B���ѹԽ���������ۼ�ʱ��
    sMcVDppTimeB  sVDppTimeB;

    // MCMD_AFN_D_F99_VDPP_TIME_C             
    // C���ѹԽ���������ۼ�ʱ��
    sMcVDppTimeC  sVDppTimeC;

    // MCMD_AFN_D_F100_VDNN_TIME_A            
    // A���ѹԽ���������ۼ�ʱ��
    sMcVDnnTimeA sVDnnTimeA;

    // MCMD_AFN_D_F101_VDNN_TIME_B            
    // B���ѹԽ���������ۼ�ʱ��
    sMcVDnnTimeB sVDnnTimeB;

    // MCMD_AFN_D_F102_VDNN_TIME_C            
    // C���ѹԽ���������ۼ�ʱ��
    sMcVDnnTimeC sVDnnTimeC;

    // MCMD_AFN_D_F105_VMPP_TIME_A            
    // A���ѹԽ���������ۼ�ʱ��
    sMcVMppTimeA  sVMppTimeA;

    // MCMD_AFN_D_F106_VMPP_TIME_B            
    // B���ѹԽ���������ۼ�ʱ��
    sMcVMppTimeB sVMppTimeB;

    // MCMD_AFN_D_F107_VMPP_TIME_C            
    // C���ѹԽ���������ۼ�ʱ��
    sMcVMppTimeC sVMppTimeC;

    // MCMD_AFN_D_F108_VMNN_TIME_A            
    // A���ѹԽ���������ۼ�ʱ��
    sMcVMnnTimeA sVMnnTimeA;

    // MCMD_AFN_D_F109_VMNN_TIME_B            
    // B���ѹԽ���������ۼ�ʱ��
    sMcVMnnTimeB sVMnnTimeB;

    // MCMD_AFN_D_F110_VMNN_TIME_C            
    // C���ѹԽ���������ۼ�ʱ��
    sMcVMnnTimeC sVMnnTimeC;

    // MCMD_AFN_D_F113_VABR_TOTL_A            
    // A���ѹ�ܻ�����
    sMcVabrTotalA sVabrTotalA;

    // MCMD_AFN_D_F114_VABR_TOTL_B            
    // B���ѹ�ܻ�����
    sMcVabrTotalB sVabrTotalB;

    // MCMD_AFN_D_F115_VABR_TOTL_C            
    // C���ѹ�ܻ�����
    sMcVabrTotalC sVabrTotalC;
    
    // MCMD_AFN_D_F116_EABR_TOTL_A            
    // A������ܻ�����
    sMcEabrTotalA sEabrTotalA;
    
    // MCMD_AFN_D_F117_EABR_TOTL_B            
    // B������ܻ�����
    sMcEabrTotalB sEabrTotalB;
    
    // MCMD_AFN_D_F118_EABR_TOTL_C            
    // C������ܻ�����
    sMcEabrTotalC sEabrTotalC;

    // MCMD_AFN_D_F121_VABR_ODD_A             
    // A���ѹ��λ�����
    sMcVabrOddA sVabrOddA;
    
    // MCMD_AFN_D_F122_VABR_EVN_A             
    // A���ѹż�λ�����
    sMcVabrEvnA sVabrEvnA;
    
    // MCMD_AFN_D_F123_VABR_ODD_B             
    // B���ѹ��λ�����
    sMcVabrOddB sVabrOddB;
    
    // MCMD_AFN_D_F124_VABR_EVN_B             
    // B���ѹż�λ�����
    sMcVabrEvnB sVabrEvnB;
    
    // MCMD_AFN_D_F125_VABR_ODD_C             
    // C���ѹ��λ�����
    sMcVabrOddC sVabrOddC;
    
    // MCMD_AFN_D_F126_VABR_EVN_C             
    // C���ѹż�λ�����
    sMcVabrEvnC sVabrEvnC;

    // MCMD_AFN_D_F128_EABR_OOD_A             
    // A�������λ�����
    sMcEabrOddA sEabrOddA;
    
    // MCMD_AFN_D_F129_EABR_EVN_A             
    // A�����ż�λ�����
    sMcEabrEvnA sEabrEvnA;
    
    // MCMD_AFN_D_F130_EABR_OOD_B             
    // B�������λ�����
    sMcEabrOddB sEabrOddB;
    
    // MCMD_AFN_D_F131_EABR_EVN_B             
    // B�����ż�λ�����
    sMcEabrEvnB sEabrEvnB;
    
    // MCMD_AFN_D_F132_EABR_OOD_C           
    // C�������λ�����
    sMcEabrOddC sEabrOddC;
    
    // MCMD_AFN_D_F133_EABR_EVN_C           
    // C�����ż�λ�����
    sMcEabrEvnC sEabrEvnC;

    // MCMD_AFN_D_F137_FLS_SHRT_A             
    // A���ʱ����
    sMcFlashShortA sFlashShortA;
    
    // MCMD_AFN_D_F138_FLS_SHRT_B            
    // B���ʱ����
    sMcFlashShortB sFlashShortB;
    
    // MCMD_AFN_D_F139_FLS_SHRT_C     
    // C���ʱ����
    sMcFlashShortC sFlashShortC;
    
    // MCMD_AFN_D_F140_FLS_LONG_A       
    // A�೤ʱ����
    sMcFlashLongA sFlashLongA;
    
    // MCMD_AFN_D_F141_FLS_LONG_B   
    // B�೤ʱ����
    sMcFlashLongB sFlashLongB;
    
    // MCMD_AFN_D_F142_FLS_LONG_C             
    // C�೤ʱ����
    sMcFlashLongC sFlashLongC;

    // MCMD_AFN_D_F145_HARM_VOLT_A            
    // A��N��г����ѹ
    sMcHarmVoltA sHarmVoltA;
    
    // MCMD_AFN_D_F146_HARM_VOLT_B          
    // B��N��г����ѹ
    sMcHarmVoltB sHarmVoltB;
    
    // MCMD_AFN_D_F147_HARM_VOLT_C          
    // C��N��г����ѹ
    sMcHarmVoltC sHarmVoltC;
    
    // MCMD_AFN_D_F148_HARM_ELEC_A             
    // A��N��г������
    sMcHarmElecA sHarmElecA;
    
    // MCMD_AFN_D_F149_HARM_ELEC_B            
    // B��N��г������
    sMcHarmElecB sHarmElecB;
    
    // MCMD_AFN_D_F150_HARM_ELEC_C            
    // C��N��г������
    sMcHarmElecC sHarmElecC;

    // MCMD_AFN_D_F153_HARM_VINC_A           
    // A��N��г����ѹ������
    sMcHarmVincA sHarmVincA;

    // MCMD_AFN_D_F154_HARM_VINC_B           
    // B��N��г����ѹ������
    sMcHarmVincB sHarmVincB;

    // MCMD_AFN_D_F155_HARM_VINC_C            
    // C��N��г����ѹ������
    sMcHarmVincC sHarmVincC;

    // MCMD_AFN_D_F156_HARM_EINC_A          
    // A��N��г������������
    sMcHarmEincA sHarmEincA;

    // MCMD_AFN_D_F157_HARM_EINC_B           
    // B��N��г������������
    sMcHarmEincB sHarmEincB;

    // MCMD_AFN_D_F158_HARM_EINC_C        
    // C��N��г������������
    sMcHarmEincC sHarmEincC;

    // ��30 pn:�ǵ����������
    // MCMD_AFN_D_F233_NELC_VALUE      
    // �ǵ�����
    sMcNelcValue  sNelcValue;

    // MCMD_AFN_C_F9_FREZ_AUTO
    // ���󣨶�ʱ�ϱ���������������
    sMcFrezAutoA   sFrezAutoA;    

    // MCMD_AFN_E_F1_EVENT_1
    // ������Ҫ�¼�(Ӧ��ṹ)
    sMcEventImpA   sEventImpA;

    // MCMD_AFN_E_F2_EVENT_2
    // ����һ���¼�(Ӧ��ṹ)
    sMcEventNmlA   sEventNmlA;   

    // MCMD_AFN_E_F3_EVENT_3
    // ����ָ���¼�(Ӧ��ṹ) ��ʱ����������
    //sMcEventSpeA    sEventSpeA;
    ///*}
    
    /***************************************
     *  ����
     *  ��վ����վ
     *  ͨ�������� ����
     *
     *  ����������������
     * MCMD_AFN_1_F1_HARD_INIT
     * MCMD_AFN_1_F2_DATA_INIT
     * MCMD_AFN_1_F3_FACTORY_RESET
     * MCMD_AFN_1_F4_PARA_INIT
     * MCMD_AFN_2_F4_LINK_OK
     * MCMD_AFN_5_F3_AUTO_SAY_ON
     * MCMD_AFN_5_F4_AUTO_SAY_OFF
     * MCMD_AFN_5_F5_CON_LINK_ON
     * MCMD_AFN_5_F6_CON_LINK_OFF
     * MCMD_AFN_5_F25_REPT_FREZ_ON
     * MCMD_AFN_5_F26_REPT_FREZ_OFF
     * MCMD_AFN_5_F27_TASK_FREZ_ON
     * MCMD_AFN_5_F28_TASK_FREZ_OFF
     * MCMD_AFN_A_F1_CON_UP_CFG
     * MCMD_AFN_A_F3_CON_AUTH_PARA
     * MCMD_AFN_A_F4_TEAM_ADDR
     * MCMD_AFN_A_F5_CON_IP_PORT
     * MCMD_AFN_A_F6_CON_CASC
     * MCMD_AFN_A_F9_CON_EVENT_CFG
     * MCMD_AFN_A_F10_CON_STATE_INPUT
     * MCMD_AFN_A_F11_CON_LOGIC_ADDR
     * MCMD_AFN_A_F12_CON_VERSION
     * MCMD_AFN_A_F13_ELEC_MP_INFO
     * MCMD_AFN_A_F14_NELC_MP_INFO
     * MCMD_AFN_A_F15_SUPT_EVENT
     * MCMD_AFN_A_F17_TML_UP_CFG
     * MCMD_AFN_A_F25_ELEC_MP_CFG
     * MCMD_AFN_A_F26_ELEC_MP_BASE
     * MCMD_AFN_A_F28_ELEC_LMIT_POWER
     * MCMD_AFN_A_F29_ELEC_LMIT_FACTR
     * MCMD_AFN_A_F33_NELC_MP_CFG
     * MCMD_AFN_A_F34_NELC_MP_PARA
     * MCMD_AFN_A_F49_FREZ_TASK_PARA
     * MCMD_AFN_A_F57_TML_CFG_INFO
     * MCMD_AFN_C_F1_FREZ_TEMP
     * MCMD_AFN_D_F1_CLOCK 
     *
    {*///
    // MCMD_AFN_1_F5_DATA_CLEAR
    // ָ����������  
    sMcRtDataClear        sRtDataClear;    

    // MCMD_AFN_5_F1_CHECK_TIME
    // Уʱ����
    sMcUerClock           sCheckClock;    

    // MCMD_AFN_5_F2_FREZ_TEMP
    // ��ʱ��������
    sMcFrezTemp           sFrezTemp;        

    // MCMD_AFN_5_F9_REMOTE_OFF
    // ң����բ
    sMcRemoteOff          sRemoteOff;       

    // MCMD_AFN_5_F10_REMOTE_ON
    // �����բ
    sMcRemoteOn           sRemoteOn;        
    
    // MCMD_AFN_5_F17_NX_MODEL_ACT
    // ��Чģ����Ч
    sMcNxModelAct         sNxModelAct;     
    
    // MCMD_AFN_5_F18_NX_MODEL_CLR
    // ��Чģ�����
    sMcNxModelClr         sNxModelClr;      
    
    // MCMD_AFN_5_F19_RQ_RESPN_ACT
    // ������Ӧ��Ϣ��Ч
    sMcRqRespnAct         sRqRespnAct;     
    
    // MCMD_AFN_5_F20_RQ_RESPN_CLT
    // ������Ӧ��Ϣ���
    sMcRqRespnClr         sRqRespnClr;     

    // MCMD_AFN_A_F2_MST_PARA  �������
    // ��ѯ��(��)վ����
    sMcMstParaQ           sMstParaQ;       

    // MCMD_AFN_A_F7_CON_DOWN_CFG
    // ��Ϣ�����뽻���ն�������̫���˿�ͨ�Ų���
    sMcDownCfgQ           sDownCfgQ;        
    
    // MCMD_AFN_C_F9_FREZ_AUTO
    // ���󣨶�ʱ�ϱ���������������
    sMcFrezAutoQ          sFrezAutoQ;      

    // MCMD_AFN_E_F1_EVENT_1
    // ������Ҫ�¼�(�������)
    sMcEventImpQ          sEventImpQ;

    // MCMD_AFN_E_F2_EVENT_2
    // ����һ���¼�(�������)
    sMcEventNmlQ          sEventNmlQ;  

    // MCMD_AFN_E_F3_EVENT_3
    // ����ָ���¼�(�������) ��ʱ����������
    //sMcEventSpeQ         sEventSpeQ;
    ///*}
    
    // ������ռλ ��Ӧ������
    UINT8            ucRev[MC_UNIT_DATA_MAX];
    
}uMcApp;

/***************************************
 *  ֡�������ݽṹ �û���  (�ͼ�����)
 *  ���ڷ�װ�����
 *  �䳤�ṹ
{*///
typedef struct
{
    sMcPnFn    sPnFn;
    uMcApp     *puApp[MC_PN_INDEX_MAX][MC_FN_INDEX_MAX];   // �������64�����ݵ�Ԫ��ָ��
}sMcBaseData;

typedef struct
{
    sMcAddress    sAddress;        // ��ַ�� A
    sMctrl        sCtrl;           // ������ C
    BOOL          bFixed;          // �̶�֡���ǿɱ�֡ 

    // �ɱ�֡���������ֶ�
    sMcAc         sAc;             // Ӧ�ÿ�����Ac(Tp Ec Afn)
    sMcEc         sEc;             // �¼�������  ������ sMcAc ���е�bEc (ֻ���������б�����)
    sMcTp         sTp;             // ʱ���ǩ    ������ sMcAc ���е�bTp 
    UINT8         aPw[MC_PW_LEN];  // ��Ϣ��֤��  (ֻ��������Ҫ�����б�����)
    
    // ���ݵ�Ԫ��  �䳤��
    UINT16        usNum;           // ���ݵ�Ԫ��ĸ���
    sMcBaseData   sData[1];        // ���ݵ�Ԫ��
}smcBaskPack;

void vmc_free_base_data(sMcBaseData* pBaseData, INT32 Num);

// ��֡����
eMcErr emc_pack_base(smcBaskPack* psPack, UINT8* pOutBuf, UINT16* pusLen);   

// ��֡����
eMcErr emc_unPack_base(smcBaskPack *psUnpack, UINT8* pInBuf, UINT16 usLen);
///*}

/***************************************
 *  ���ݵ�Ԫ��ʶ���Ӧ�����ݵ�Ԫ (�߼�����)
 *  
 * ���ݵ�ԪΪ�����ݵ�Ԫ��ʶ����֯������,��������������ȡ�
 * ������֯��˳�������ɢ��ʽ
 * ���������ʶ ���ݵ�Ԫ һһ��Ӧ�ķ�ʽ
 * 
{*///
typedef struct
{
    eMcmd        eCmd;        // ������
    UINT16       usPN;        // Pn (0 <= pn <= 2040 )
    BOOL         bApp;        // �Ƿ������ݵ�Ԫ
    uMcApp       uApp;        // ��Ӧ��ͬ����������, ������������, Ӧ�ò�����ʱ��ʱ��
    
}sMcData;
///*}

/***************************************
 *  ��֡���֡(ͨ��) �û������ݽṹ (�߼�����)
 *  ���ڷ�װ�����װ 
 *  �䳤�ṹ
{*///
typedef struct
{    
    sMcAddress    sAddress;        // ��ַ�� A
    sMctrl        sCtrl;           // ������ C
    BOOL          bFixed;          // �̶�֡���ǿɱ�֡ 

    // �ɱ�֡�����¿�ѡ�ֶ�
    sMcAc         sAc;             // Ӧ�ÿ�����Ac(Tp Ec Afn)
    sMcEc         sEc;             // �¼�������  ������ sMcAc ���е�bEc (ֻ���������б�����)
    sMcTp         sTp;             // ʱ���ǩ    ������ sMcAc ���е�bTp 
    BOOL          bPw;             // �Ƿ���Pw�ֶ�(ֻ������Ҫ�����еı�����)
    UINT8         aPw[MC_PW_LEN];  // ��Ϣ��֤��  (ֻ��������Ҫ�����б�����)

    // ���ݵ�Ԫ��  �䳤��
    UINT16        usNum;          // ���ݵ�Ԫ��ĸ���
    sMcData       sData[1];       // usNum�����ݵ�Ԫ��
    
}smcPack;

// �߼��ӿ�(�û�ʹ��)
// ��װ����
eMcErr emcPack(smcPack* psPack, UINT8* pOutBuf, UINT16* pusLen);   

// ��֡����
eMcErr emcUnPack(smcPack *psUnpack, UINT8* pInBuf, UINT16 usLen);
///*}

/***************************************
 *  ��֡���֡(ͨ��) (�������ӿ� �߼�����)
 *  �������μ������಻��Ҫ���ĵ��ֶ�
 *  ���ڷ�װ�����װ 
 *  �䳤�ṹ
{*///
typedef struct
{
    sMcAddress    sAddress;        // ��ַ�� A
    BOOL          bReSend;         // �Ƿ�Ϊ�ط�  TRUE �ط���֡���������Զ�����1 FALSE ������1
    BOOL          bActive;         // �Ƿ�Ϊ�����ϱ� (����¼���������˳���¼��1��2�����������ϱ�ʱΪ��)
    UINT8         ucRSEQ;          // ��Ӧ֡��� RSEQ   (0~15)
                                   /*
                                      ��Ӧ֡��� RSEQ
                                       (1) ��Ӧ֡��� RSEQ �� PRM=0 ʱ�����Ӷ�֡����Ч��
                                           �ñ����ʾ 0~15�����ڶ���Ӷ�֡��Ӧһ������֡�Ĵ��䡣
                                       (2) ÿһ������վ�ʹӶ�վ֮����� 1 �������ļ�������
                                           ���ڼ�¼��ǰ RSEQ����ֻ��һ֡�Ӷ�֡��Ӧ����֡�ģ�
                                           RSEQ=0�������� n ��n��16��֡��Ӧ�ģ�RSEQ �� n-1 ��ݼ�������
                                           ÿ����һ֡�� 1��ֱ�����һ֡ RSEQ=0��
                                   */
    UINT16        usNum;           // �ð��к���������ĸ��� ������һ��������    
    sMcData       sData[1];        // usNum�����ݵ�Ԫ��
}sMcPackCon;

// ��װ����
eMcErr emcPackCon(sMcPackCon* psPack, UINT8* pOutBuf, UINT16* pusLen);   

// ��֡����
eMcErr emcUnPackCon(sMcPackCon *psUnpack, UINT8* pInBuf, UINT16 usLen);
///*}

/***************************************
 *  �����ڷ�֡ (��վ�ӿ� �߼�����)
 *  ����������վ�಻��Ҫ���ĵ��ֶ�
 *  ���ڷ�װ�����װ 
 *  �䳤�ṹ
{*///
typedef struct
{
    sMcAddress    sAddress;        // ��ַ�� A
    UINT8         ucPSEQ;          // ����֡��� PSEQ
    //UINT8         ucRSEQ;          // ��Ӧ֡��� RSEQ
    UINT8         aPw[MC_PW_LEN];  // ��Ϣ��֤��  (ֻ��������Ҫ�����б�����)

    // ���ݵ�Ԫ��  �䳤��
    UINT16        usNum;           // ���ݵ�Ԫ��ĸ���
    sMcData       sData[1];        // usNum�����ݵ�Ԫ��

}sMcPackMst;

// ��װ����
eMcErr emcPackMst(sMcPackMst* psPack, UINT8* pOutBuf, UINT16* pusLen);   

// �����ڽ��װ
typedef struct
{
    sMcAddress    sAddress;        // ��ַ�� A
    UINT8         ucPSEQ;          // ����֡��� PSEQ
    UINT8         ucRSEQ;          // ��Ӧ֡��� RSEQ
    // ���ݵ�Ԫ��  �䳤��
    UINT16        usNum;           // ���ݵ�Ԫ��ĸ���
    sMcData       sData[1];        // usNum�����ݵ�Ԫ��
}sMcUnpackMst;

// ��֡����
eMcErr emcUnPackMst(sMcPackMst *psUnpack, UINT8* pInBuf, UINT16 usLen);
///*}

#endif // _GBNX_31_API_H_
