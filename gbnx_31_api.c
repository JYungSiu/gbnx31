/******************************************************************************

                  ��Ȩ���� (C), 2005-2015, ���ҵ���ͨ�����õ缼���ֹ�˾

 ******************************************************************************
  �� �� ��   : gbnx_31_api.c
  �� �� ��   : ����
  ��    ��   : liming
  ��������   : 2013��10��17��
  ����޸�   :
  ��������   : GB/T XXXX.31 2013 ��վ��ɼ��ն�ͨ��Э�����api ʵ��Դ�ļ�
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2013��10��17��
    ��    ��   : liming
    �޸�����   : �����ļ�

******************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>
#include "gbnx_31_api.h"

// ���Կ���
#define MC_DBG
// #undef  MC_DBG           // ��ʽ��ʱȥ������ע��

#ifdef MC_DBG
#define MCDBG(format,...) printf("File: "__FILE__", Line: %d: "format"\n", __LINE__, ##__VA_ARGS__)

/*****************************************************************************
 �� �� ��  : smcGetErr
 ��������  : ���ش������������
 �������  : ��
 �������  : ��
 �� �� ֵ  : char
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��7��30�� ���ڶ�
    ��    ��   : liming
    �޸�����   : �����ɺ���

*****************************************************************************/
char * smcGetErr(eMcErr eErr)
{
    char *pStr = NULL;
    switch(eErr)
    {
        case MC_OK:
            pStr = "MC_OK";
            break;

        case MC_ERR_NULL:
            pStr = "MC_ERR_NULL";
            break;

        case MC_ERR_OUTRNG:
            pStr = "MC_ERR_OUTRNG";
            break;

        case MC_ERR_NONE:
            pStr = "MC_ERR_NONE";
            break;

        case MC_ERR_IO:
            pStr = "MC_ERR_IO";
            break;

        case MC_ERR_RES:
            pStr = "MC_ERR_RES";
            break;

        case MC_ERR_INIT:
            pStr = "MC_ERR_INIT";
            break;

        case MC_ERR_PARA:
            pStr = "MC_ERR_PARA";
            break;

        case MC_ERR_FN:
            pStr = "MC_ERR_FN";
            break;

        case MC_ERR_PN:
            pStr = "MC_ERR_PN";
            break;

        case MC_ERR_ADDR:
            pStr = "MC_ERR_ADDR";
            break;

        case MC_ERR_CTRL:
            pStr = "MC_ERR_CTRL";
            break;

        case MC_ERR_0x10:
            pStr = "MC_ERR_0x10";
            break;

        case MC_ERR_A2CS:
            pStr = "MC_ERR_A2CS";
            break;

         case MC_ERR_AFN:
            pStr = "MC_ERR_AFN";
            break;

        case MC_ERR_UNCOMP:
            pStr = "MC_ERR_UNCOMP";
            break;

        case MC_ERR_0x68:
            pStr = "MC_ERR_0x68";
            break;

        case MC_ERR_PROTO:
            pStr = "MC_ERR_PROTO";
            break;

        case MC_ERR_CS:
            pStr = "MC_ERR_CS";
            break;

        case MC_ERR_0x16:
            pStr = "MC_ERR_0x16";
            break;

        case MC_ERR_LOGIC:
            pStr = "MC_ERR_LOGIC";
            break;

        case MC_ERR_PACK:
            pStr = "MC_ERR_PACK";
            break;

        case MC_ERR_PFC:
            pStr = "MC_ERR_PFC";
            break;

        case MC_ERR_TIMEOUT:
            pStr = "MC_ERR_TIMEOUT";
            break;

        case MC_ERR_PRM:
            pStr = "MC_ERR_PRM";
            break;

        case MC_ERR_TEAM:
            pStr = "MC_ERR_TEAM";
            break;

         default:
            pStr = "Unkown Err";
            break;
    }

    return pStr;

}
#endif

/*******************************************************
 *  ȫ�ֲ�����Ϣ
 *  �ṩ�������� �� Pn���͡����������Ĺ�ϵӳ��
 *
{*////
BOOL      g_bMcInit = FALSE;             // Э���Ƿ��ʼ��
eMcRole   g_eMcRole = MC_ROLE_UNKOWN;    // ��ݣ���վ���Ǵ�վ
UINT8     g_ucMcPermitDelayMinutes = 0;  // ����ʱ��

// ����֡���к� �� ��Ӧ֡���к�
#if MC_CFG_SPT_CON
UINT8     g_ucMcPseq = 0;                // ����֡���к�
UINT8     g_ucMcRseq = 0;                // ��Ӧ֡���к�
#endif


#if MC_CFG_SPT_MST
UINT8     g_aucMcPw[MC_PW_LEN] = {0};    // ��Ϣ��֤�� ������վ����������������
#endif

#if MC_CFG_SPT_CON
sMcEc     g_sMcEc;                       // �¼������� ��������֧��
#endif

#if MC_CFG_ENCRYPT
    peMcEncryptFunc   g_peMcEncryptFunc = NULL;  // ���ܽӿ�
    peMcDecryptFunc   g_peMcDecryptFunc = NULL;  // ���ܽӿ�
#endif
///*}

/*******************************************************
 *  ������Ϣ��
 *  �ṩ�������� �� Pn���͡����������Ĺ�ϵӳ��
 *
{*////
const sMcmdInfor gmc_cmdinfor[] =
{
     /*******************************
     *  (0) ȷ��/���ϣ�AFN=00H��
     *
     *  ����: ������
     *  ����: ������
     *  ����: ����Ҫ
     *
    {*///
    {MCMD_AFN_0_F1_ALL_OK_DENY,      MC_DIR_M2S, MC_PN_P0,  emc_trans_afn00f1,     "ȫ��ȷ��/���ϣ����յ������е�ȫ�����ݵ�Ԫ��ʶ����ȷ��/����"},
    {MCMD_AFN_0_F1_ALL_OK_DENY,      MC_DIR_S2M, MC_PN_P0,  emc_trans_afn00f1,     "ȫ��ȷ��/���ϣ����յ������е�ȫ�����ݵ�Ԫ��ʶ����ȷ��/����"},
    {MCMD_AFN_0_F2_ONE_BY_ONE,       MC_DIR_S2M, MC_PN_P0,  emcTrans_OneByOne,     "�����ݵ�Ԫ��ʶȷ�Ϻͷ��ϣ����յ������е�ȫ�����ݵ�Ԫ��ʶ�������ȷ��/����"},
    ///*}

     /*******************************
     *  (1) ��λ���AFN=01H)
     *
     *  ����: AFN 00H ȷ��/����
     *  ����: ������
     *  ����: ��Ҫ
     *
    {*///
    {MCMD_AFN_1_F1_HARD_INIT,        MC_DIR_M2S, MC_PN_P0,  NULL,                  "Ӳ����ʼ��"},
    {MCMD_AFN_1_F2_DATA_INIT,        MC_DIR_M2S, MC_PN_P0,  NULL,                  "��������ʼ��"},
    {MCMD_AFN_1_F3_FACTORY_RESET,    MC_DIR_M2S, MC_PN_P0,  NULL,                  "������ȫ����������ʼ�������ָ����������ã�"},
    {MCMD_AFN_1_F4_PARA_INIT,        MC_DIR_M2S, MC_PN_P0,  NULL,                  "����������ϵͳ��վͨ���йصģ���ȫ����������ʼ��"},
    {MCMD_AFN_1_F5_DATA_CLEAR,       MC_DIR_M2S, MC_PN_P0,  emc_trans_afn01f5,     "ָ����������"},
    ///*}

     /*******************************
     *  (2) ��·�ӿڼ�⣨AFN=02H��
     *
     *  ����: ������
     *  ����: AFN 00H ȷ��/����
     *  ����: ����Ҫ
     *
    {*///
    {MCMD_AFN_2_F1_LOG_IN,            MC_DIR_S2M, MC_PN_P0,  NULL,                  "��¼"},
    {MCMD_AFN_2_F2_LOG_OUT,           MC_DIR_S2M, MC_PN_P0,  NULL,                  "�˳���¼"},
    {MCMD_AFN_2_F3_HEART_BEAT,        MC_DIR_S2M, MC_PN_P0,  NULL,                  "����"},
    {MCMD_AFN_2_F4_LINK_OK,           MC_DIR_M2S, MC_PN_P0,  NULL,                  "ȷ��((��¼/�˳�/����)"},
    ///*}

     /*******************************
     *  (4) ���ò���(AFN=04H��
     *
     *  ����: AFN 00H ȷ��/����
     *  ����: ������
     *  ����: ��Ҫ
     *
    {*///
    // ��1   pn:p0
    {MCMD_AFN_4_F1_CON_UP_CFG,        MC_DIR_M2S, MC_PN_P0,  emc_trans_afn04f1,     "��Ϣ�����뽻���ն�����ͨ�ſ�ͨ�Ų���"},
    {MCMD_AFN_4_F2_MST_PARA,          MC_DIR_M2S, MC_PN_P0,  emc_trans_afn04f2,     "��(��)վ����"},
    {MCMD_AFN_4_F3_CON_AUTH_PARA,     MC_DIR_M2S, MC_PN_P0,  emc_trans_afn04f3,     "��Ϣ�����뽻���ն�����ͨ����Ϣ��֤����"},
    {MCMD_AFN_4_F4_TEAM_ADDR,         MC_DIR_M2S, MC_PN_P0,  emc_trans_afn04f4,     "��Ϣ�����뽻���ն����ַ"},
    {MCMD_AFN_4_F5_CON_IP_PORT,       MC_DIR_M2S, MC_PN_P0,  emc_trans_afn04f5,     "��Ϣ�����뽻���ն�IP��ַ�Ͷ˿�"},
    {MCMD_AFN_4_F6_CON_CASC,          MC_DIR_M2S, MC_PN_P0,  emc_trans_afn04f6,     "��Ϣ�����뽻���ն˼���ͨ�Ų���"},
    {MCMD_AFN_4_F7_CON_DOWN_CFG,      MC_DIR_M2S, MC_PN_P0,  emc_trans_afn04f7,     "��Ϣ�����뽻���ն�������̫���˿�ͨ�Ų���"},

    // ��2   pn:p0
    {MCMD_AFN_4_F9_CON_EVENT_CFG,     MC_DIR_M2S, MC_PN_P0,  emc_trans_afn04f9,     "�¼���¼����"},
    {MCMD_AFN_4_F10_CON_STATE_INPUT,  MC_DIR_M2S, MC_PN_P0,  emc_trans_afn04f10,    "�豸״̬���������"},

    // ��3   pn:p0
    {MCMD_AFN_4_F17_TML_UP_CFG,       MC_DIR_M2S, MC_PN_P0,  emc_trans_afn04f17,    "����ն�����ͨ�Ų�������"},

    // ��4   pn:�������
    {MCMD_AFN_4_F25_ELEC_MP_CFG,      MC_DIR_M2S, MC_PN_MP,  emc_trans_afn04f25,    "�������������ò���"},
    {MCMD_AFN_4_F26_ELEC_MP_BASE,     MC_DIR_M2S, MC_PN_MP,  emc_trans_afn04f26,    "�����������������"},
    {MCMD_AFN_4_F27_ELEC_LMIT_POWER,  MC_DIR_M2S, MC_PN_MP,  emc_trans_afn04f27,    "�����������������ֵ����"},
    {MCMD_AFN_4_F28_ELEC_LMIT_FACTR,  MC_DIR_M2S, MC_PN_MP,  emc_trans_afn04f28,    "���������㹦������Խ��ֵ����"},
    {MCMD_AFN_4_F29_ELEC_FIX_HARM,    MC_DIR_M2S, MC_PN_MP,  emc_trans_afn04f29,    "����������г��������Խ�޶�ֵ"},
    {MCMD_AFN_4_F30_ELEC_FLASH,       MC_DIR_M2S, MC_PN_MP,  emc_trans_afn04f30,    "��������������Խ�޲���"},

    // ��5   pn:�������
    {MCMD_AFN_4_F33_NELC_MP_CFG,      MC_DIR_M2S, MC_PN_MP,  emc_trans_afn04f33,    "�ǵ������������ò���"},
    {MCMD_AFN_4_F34_NELC_MP_PARA,     MC_DIR_M2S, MC_PN_MP,  emc_trans_afn04f34,    "�ǵ������������ݲ���"},
    {MCMD_AFN_4_F35_NELC_MP_LMIT,     MC_DIR_M2S, MC_PN_MP,  emc_trans_afn04f35,    "�ǵ���������Խ�����ݲ���"},

    // ��7  pn:�����
    {MCMD_AFN_4_F49_FREZ_TASK_PARA,   MC_DIR_M2S, MC_PN_TK,  emc_trans_afn04f49,    "���������������"},
    ///*}

     /*******************************
     *  (5) ��������(AFN=05H��
     *
     *  ����: AFN 00H ȷ��/����
     *  ����: ������
     *  ����: ��Ҫ
     *
    {*///
    // ��1  pn:p0
    {MCMD_AFN_5_F1_CHECK_TIME,        MC_DIR_M2S, MC_PN_P0,  emc_trans_afn05f1,     "Уʱ����"},
    {MCMD_AFN_5_F2_FREZ_TEMP,         MC_DIR_M2S, MC_PN_P0,  emc_trans_afn05f2,     "��ʱ��������"},
    {MCMD_AFN_5_F3_AUTO_SAY_ON,       MC_DIR_M2S, MC_PN_P0,  NULL,      "������Ϣ�����뽻���ն������ϱ�"},
    {MCMD_AFN_5_F4_AUTO_SAY_OFF,      MC_DIR_M2S, MC_PN_P0,  NULL,      "��ֹ��Ϣ�����뽻���ն������ϱ�"},
    {MCMD_AFN_5_F5_CON_LINK_ON,       MC_DIR_M2S, MC_PN_P0,  NULL,      "������Ϣ�����뽻���ն�������(��)վ"},
    {MCMD_AFN_5_F6_CON_LINK_OFF,      MC_DIR_M2S, MC_PN_P0,  NULL,      "������Ϣ�����뽻���ն˶Ͽ�����"},

    // ��2  pn:p0/����ն˺�
    {MCMD_AFN_5_F9_REMOTE_OFF,        MC_DIR_M2S, MC_PN_MP,  emc_trans_afn05f9,     "ң����բ"},
    {MCMD_AFN_5_F10_REMOTE_ON,        MC_DIR_M2S, MC_PN_MP,  emc_trans_afn05f10,    "�����բ"},

    // ��3  pn:p0/����ն˺�
    {MCMD_AFN_5_F17_NX_MODEL_ACT,     MC_DIR_M2S, MC_PN_MP,  emc_trans_afn05f17,    "��Чģ����Ч"},
    {MCMD_AFN_5_F18_NX_MODEL_CLR,     MC_DIR_M2S, MC_PN_MP,  emc_trans_afn05f18,    "��Чģ�����"},
    {MCMD_AFN_5_F19_RQ_RESPN_ACT,     MC_DIR_M2S, MC_PN_MP,  emc_trans_afn05f19,    "������Ӧ��Ϣ��Ч"},
    {MCMD_AFN_5_F20_RQ_RESPN_CLT,     MC_DIR_M2S, MC_PN_MP,  emc_trans_afn05f20,    "������Ӧ��Ϣ���"},

    // ��4  pn:�����
    {MCMD_AFN_5_F25_REPT_FREZ_ON,     MC_DIR_M2S, MC_PN_TK,  NULL,      "������ʱ�ϱ�������������"},
    {MCMD_AFN_5_F26_REPT_FREZ_OFF,    MC_DIR_M2S, MC_PN_TK,  NULL,      "��ֹ��ʱ�ϱ�������������"},
    {MCMD_AFN_5_F27_TASK_FREZ_ON,     MC_DIR_M2S, MC_PN_TK,  NULL,      "����������������"},
    {MCMD_AFN_5_F28_TASK_FREZ_OFF,    MC_DIR_M2S, MC_PN_TK,  NULL,      "������������ֹͣ"},
    ///*}

     /*******************************
     *  (6) �����֤����ԿЭ��(AFN=06H��
     *
     *  ����: ������
     *  ����: ������
     *  ����: ����Ҫ
     *
    {*///
    // ����
    {MCMD_AFN_6_F1_ID_AUTH_Q,         MC_DIR_S2M, MC_PN_P0,  NULL,     "�����֤����"},
    {MCMD_AFN_6_F2_ID_AUTH_A,         MC_DIR_S2M, MC_PN_P0,  NULL,     "�����֤��Ӧ"},
    {MCMD_AFN_6_F3_RAND_Q,            MC_DIR_S2M, MC_PN_P0,  NULL,     "ȡ���������"},
    {MCMD_AFN_6_F4_RAND_A,            MC_DIR_S2M, MC_PN_P0,  NULL,     "ȡ�������Ӧ"},

    // ����
    {MCMD_AFN_6_F1_ID_AUTH_Q,         MC_DIR_M2S, MC_PN_P0,  NULL,     "�����֤����"},
    {MCMD_AFN_6_F2_ID_AUTH_A,         MC_DIR_M2S, MC_PN_P0,  NULL,     "�����֤��Ӧ"},
    {MCMD_AFN_6_F3_RAND_Q,            MC_DIR_M2S, MC_PN_P0,  NULL,     "ȡ���������"},
    {MCMD_AFN_6_F4_RAND_A,            MC_DIR_M2S, MC_PN_P0,  NULL,     "ȡ�������Ӧ"},
    ///*}

     /*******************************
     *  (7) ���󱻼����ն������ϱ�(AFN=08H��
     *
     *  ����: �������ϱ�������ʱ, �ֱ�������1�����ݺ�����2���������б��Ľ���Ӧ��
     *        �������ϱ�������ʱ, AFN 00H ���� MCMD_AFN_0_F2_ALL_DENY
     *  ����: ������
     *  ����: ����Ҫ
     *
    {*///
    {MCMD_AFN_8_F1_CALL_AUTO_REPT,    MC_DIR_M2S, MC_PN_P0,  NULL,                  "���󱻼����ն������ϱ�"},
    ///*}

     /*******************************
     *  (9) ��ѯ����(AFN=0AH��
     *
     *  ����: ������
     *  ����: ������
     *  ����: ����Ҫ
     *
    {*///
    /** { ���� **/
    // ��1   pn:p0
    {MCMD_AFN_A_F1_CON_UP_CFG,        MC_DIR_S2M, MC_PN_P0,  emc_trans_afn04f1,      "��ѯ��Ϣ�����뽻���ն�����ͨ�ſ�ͨ�Ų���"},
    {MCMD_AFN_A_F2_MST_PARA,          MC_DIR_S2M, MC_PN_P0,  emc_trans_afn10f2_s2m,  "��ѯ��(��)վ���� "},
    {MCMD_AFN_A_F3_CON_AUTH_PARA,     MC_DIR_S2M, MC_PN_P0,  emc_trans_afn04f3,      "��ѯ��Ϣ�����뽻���ն�����ͨ����Ϣ��֤����"},
    {MCMD_AFN_A_F4_TEAM_ADDR,         MC_DIR_S2M, MC_PN_P0,  emc_trans_afn04f4,      "��ѯ��Ϣ�����뽻���ն����ַ"},
    {MCMD_AFN_A_F5_CON_IP_PORT,       MC_DIR_S2M, MC_PN_P0,  emc_trans_afn04f5,      "��ѯ��Ϣ�����뽻���ն�IP��ַ�Ͷ˿�"},
    {MCMD_AFN_A_F6_CON_CASC,          MC_DIR_S2M, MC_PN_P0,  emc_trans_afn04f6,      "��ѯ��Ϣ�����뽻���ն˼���ͨ�Ų���"},
    {MCMD_AFN_A_F7_CON_DOWN_CFG,      MC_DIR_S2M, MC_PN_P0,  emc_trans_afn10f7_s2m,  "��Ϣ�����뽻���ն�������̫���˿�ͨ�Ų���"},

    // ��2   pn:p0/����ն˺�
    {MCMD_AFN_A_F9_CON_EVENT_CFG,     MC_DIR_S2M, MC_PN_P0,  emc_trans_afn04f9,      "��ѯ�¼���¼����"},
    {MCMD_AFN_A_F10_CON_STATE_INPUT,  MC_DIR_S2M, MC_PN_P0,  emc_trans_afn04f10,     "��ѯ�豸״̬���������"},
    {MCMD_AFN_A_F11_CON_LOGIC_ADDR,   MC_DIR_S2M, MC_PN_P0,  emc_trans_afn10f11,     "�豸�߼���ַ"},
    {MCMD_AFN_A_F12_CON_VERSION,      MC_DIR_S2M, MC_PN_P0,  emc_trans_afn10f12,     "��ѯ�豸�汾��Ϣ"},
    {MCMD_AFN_A_F13_ELEC_MP_INFO,     MC_DIR_S2M, MC_PN_P0,  emc_trans_afn10f13,     "�����õ�����������Ϣ"},
    {MCMD_AFN_A_F14_NELC_MP_INFO,     MC_DIR_S2M, MC_PN_P0,  emc_trans_afn10f14,     "�����÷ǵ�����������Ϣ"},
    {MCMD_AFN_A_F15_SUPT_EVENT,       MC_DIR_S2M, MC_PN_P0,  emc_trans_afn10f15,     "�豸֧�ֵ��¼���¼"},

    // ��3   pn:����ն˺�
    {MCMD_AFN_A_F17_TML_UP_CFG,       MC_DIR_S2M, MC_PN_TM,  emc_trans_afn04f17,     "��ѯ����ն˵�����ͨ�Ų���"},

    // ��4   pn:�������
    {MCMD_AFN_A_F25_ELEC_MP_CFG,      MC_DIR_S2M, MC_PN_MP,  emc_trans_afn04f25,     "��ѯ�������������ò���"},
    {MCMD_AFN_A_F26_ELEC_MP_BASE,     MC_DIR_S2M, MC_PN_MP,  emc_trans_afn04f26,     "��ѯ�����������������"},
    {MCMD_AFN_A_F27_ELEC_LMIT_POWER,  MC_DIR_S2M, MC_PN_MP,  emc_trans_afn04f27,     "��ѯ�����������������ֵ����"},
    {MCMD_AFN_A_F28_ELEC_LMIT_FACTR,  MC_DIR_S2M, MC_PN_MP,  emc_trans_afn04f28,     "��ѯ���������㹦������Խ��ֵ����"},
    {MCMD_AFN_A_F29_ELEC_FIX_HARM,    MC_DIR_S2M, MC_PN_MP,  emc_trans_afn04f29,     "��ѯ����������г��������Խ�޶�ֵ"},
    {MCMD_AFN_A_F30_ELEC_FLASH,       MC_DIR_S2M, MC_PN_MP,  emc_trans_afn04f30,     "��ѯ��������������Խ�޲���"},

    // ��5   pn:�ǵ����������
    {MCMD_AFN_A_F33_NELC_MP_CFG,      MC_DIR_S2M, MC_PN_MP,  emc_trans_afn04f33,     "��ѯ�ǵ������������ò���"},
    {MCMD_AFN_A_F34_NELC_MP_PARA,     MC_DIR_S2M, MC_PN_MP,  emc_trans_afn04f34,     "��ѯ�ǵ������������ݲ���"},
    {MCMD_AFN_A_F35_NELC_MP_LMIT,     MC_DIR_S2M, MC_PN_MP,  emc_trans_afn04f35,     "��ѯ�ǵ���������Խ�����ݲ���"},

    // ��7  pn:�����
    {MCMD_AFN_A_F49_FREZ_TASK_PARA,   MC_DIR_S2M, MC_PN_TK,  emc_trans_afn04f49,     "��ѯ���������������"},

    // ��8  pn:p0
    {MCMD_AFN_A_F57_TML_CFG_INFO,     MC_DIR_S2M, MC_PN_P0,  emc_trans_afn10f57,     "��ѯ�����ü���ն���Ϣ"},
     /** } ���� **/

    /** { ���� **/
    // ��1   pn:p0
    {MCMD_AFN_A_F1_CON_UP_CFG,        MC_DIR_M2S, MC_PN_P0,  NULL,      "��ѯ��Ϣ�����뽻���ն�����ͨ�ſ�ͨ�Ų���"},
    {MCMD_AFN_A_F2_MST_PARA,          MC_DIR_M2S, MC_PN_P0,  emc_trans_afn10f2_m2s,      "��ѯ��(��)վ���� "},
    {MCMD_AFN_A_F3_CON_AUTH_PARA,     MC_DIR_M2S, MC_PN_P0,  NULL,      "��ѯ��Ϣ�����뽻���ն�����ͨ����Ϣ��֤����"},
    {MCMD_AFN_A_F4_TEAM_ADDR,         MC_DIR_M2S, MC_PN_P0,  NULL,      "��ѯ��Ϣ�����뽻���ն����ַ"},
    {MCMD_AFN_A_F5_CON_IP_PORT,       MC_DIR_M2S, MC_PN_P0,  NULL,      "��ѯ��Ϣ�����뽻���ն�IP��ַ�Ͷ˿�"},
    {MCMD_AFN_A_F6_CON_CASC,          MC_DIR_M2S, MC_PN_P0,  NULL,      "��ѯ��Ϣ�����뽻���ն˼���ͨ�Ų���"},
    {MCMD_AFN_A_F7_CON_DOWN_CFG,      MC_DIR_M2S, MC_PN_P0,  emc_trans_afn10f7_m2s,    "��Ϣ�����뽻���ն�������̫���˿�ͨ�Ų���"},

    // ��2   pn:p0/����ն˺�
    {MCMD_AFN_A_F9_CON_EVENT_CFG,     MC_DIR_M2S, MC_PN_P0,  NULL,     "��ѯ�¼���¼����"},
    {MCMD_AFN_A_F10_CON_STATE_INPUT,  MC_DIR_M2S, MC_PN_P0,  NULL,     "��ѯ�豸״̬���������"},
    {MCMD_AFN_A_F11_CON_LOGIC_ADDR,   MC_DIR_M2S, MC_PN_P0,  NULL,     "�豸�߼���ַ"},
    {MCMD_AFN_A_F12_CON_VERSION,      MC_DIR_M2S, MC_PN_P0,  NULL,     "��ѯ�豸�汾��Ϣ"},
    {MCMD_AFN_A_F13_ELEC_MP_INFO,     MC_DIR_M2S, MC_PN_P0,  NULL,     "�����õ�����������Ϣ"},
    {MCMD_AFN_A_F14_NELC_MP_INFO,     MC_DIR_M2S, MC_PN_P0,  NULL,     "�����÷ǵ�����������Ϣ"},
    {MCMD_AFN_A_F15_SUPT_EVENT,       MC_DIR_M2S, MC_PN_P0,  NULL,     "�豸֧�ֵ��¼���¼"},

    // ��3   pn:����ն˺�
    {MCMD_AFN_A_F17_TML_UP_CFG,       MC_DIR_M2S, MC_PN_TM,  NULL,     "��ѯ����ն˵�����ͨ�Ų���"},

    // ��4   pn:�������
    {MCMD_AFN_A_F25_ELEC_MP_CFG,      MC_DIR_M2S, MC_PN_MP,  NULL,     "��ѯ�������������ò���"},
    {MCMD_AFN_A_F26_ELEC_MP_BASE,     MC_DIR_M2S, MC_PN_MP,  NULL,     "��ѯ�����������������"},
    {MCMD_AFN_A_F27_ELEC_LMIT_POWER,  MC_DIR_M2S, MC_PN_MP,  NULL,     "��ѯ�����������������ֵ����"},
    {MCMD_AFN_A_F28_ELEC_LMIT_FACTR,  MC_DIR_M2S, MC_PN_MP,  NULL,     "��ѯ���������㹦������Խ��ֵ����"},
    {MCMD_AFN_A_F29_ELEC_FIX_HARM,    MC_DIR_M2S, MC_PN_MP,  NULL,     "��ѯ����������г��������Խ�޶�ֵ"},
    {MCMD_AFN_A_F30_ELEC_FLASH,       MC_DIR_M2S, MC_PN_MP,  NULL,     "��ѯ��������������Խ�޲���"},

    // ��5   pn:�ǵ����������
    {MCMD_AFN_A_F33_NELC_MP_CFG,      MC_DIR_M2S, MC_PN_MP,  NULL,     "��ѯ�ǵ������������ò���"},
    {MCMD_AFN_A_F34_NELC_MP_PARA,     MC_DIR_M2S, MC_PN_MP,  NULL,     "��ѯ�ǵ������������ݲ���"},
    {MCMD_AFN_A_F35_NELC_MP_LMIT,     MC_DIR_M2S, MC_PN_MP,  NULL,     "��ѯ�ǵ���������Խ�����ݲ���"},

    // ��7  pn:�����
    {MCMD_AFN_A_F49_FREZ_TASK_PARA,   MC_DIR_M2S, MC_PN_TK,  NULL,     "��ѯ���������������"},

    // ��8  pn:p0
    {MCMD_AFN_A_F57_TML_CFG_INFO,     MC_DIR_M2S, MC_PN_P0,  NULL,     "��ѯ�����ü���ն���Ϣ"},
    /** } ���� **/
    ///*}

     /*******************************
     *  (10) ����(��ʱ�ϱ�)��������(AFN=0CH��
     *
     *  ����: ���ݲ�ͬ����,�ֱ�������1�����ݺ�����2���������б��Ľ���Ӧ��
     *  ����: ������
     *  ����: ����Ҫ
     *
    {*///
    // ��1   pn:p0
    {MCMD_AFN_C_F1_FREZ_TEMP,         MC_DIR_M2S, MC_PN_P0,  NULL,                  "������ʱ��������Ķ�������"},

    // ��2   pn:�����
    {MCMD_AFN_C_F9_FREZ_AUTO,         MC_DIR_M2S, MC_PN_TK,  emc_trans_afn12f9_m2s,  "���󣨶�ʱ�ϱ���������������"},
    {MCMD_AFN_C_F9_FREZ_AUTO,         MC_DIR_S2M, MC_PN_TK,  emc_trans_afn12f9_s2m,  "���󣨶�ʱ�ϱ���������������"},
    ///*}

     /*******************************
     *  (11) ����ʵʱ����(AFN=0DH��
     *
     *  ����: ������
     *  ����: ������
     *  ����: ����Ҫ
     *
    {*///
    /** { ���� **/
    // ��1   pn:p0/����ն˺�
    {MCMD_AFN_D_F1_CLOCK,             MC_DIR_S2M, MC_PN_P0,  emc_trans_afn13f1,     "����ʱ��"},
    {MCMD_AFN_D_F2_PARA_STATE,        MC_DIR_S2M, MC_PN_P0,  emc_trans_afn13f2,     "����״̬��־"},
    {MCMD_AFN_D_F3_EVENT_1,           MC_DIR_S2M, MC_PN_P0,  emc_trans_afn13f3,     "��Ҫ�¼���������ǰֵ"},
    {MCMD_AFN_D_F4_EVENT_2,           MC_DIR_S2M, MC_PN_P0,  emc_trans_afn13f4,     "һ���¼���������ǰֵ"},
    {MCMD_AFN_D_F5_EVENT_STATE,       MC_DIR_S2M, MC_PN_P0,  emc_trans_afn13f5,     "�¼�״̬��־"},
    {MCMD_AFN_D_F6_POWR_TIMES,        MC_DIR_S2M, MC_PN_P0,  emc_trans_afn13f6,     "�ϵ����"},

    // ��2   pn:p0/����ն˺�
    {MCMD_AFN_D_F9_STATE,             MC_DIR_S2M, MC_PN_P0,  emc_trans_afn13f9,     "״̬������λ��־"},
    {MCMD_AFN_D_F10_SWITCH,           MC_DIR_S2M, MC_PN_P0,  NULL,     "���������·���ؽ���״̬������λ��־"},

    // ��4   pn:p0/�����������
    {MCMD_AFN_D_F25_POWR_HAVE_T,      MC_DIR_S2M, MC_PN_MP,  emc_trans_afn13f25,    "���й�����"},
    {MCMD_AFN_D_F26_POWR_NONE_T,      MC_DIR_S2M, MC_PN_MP,  emc_trans_afn13f26,    "���޹�����"},
    {MCMD_AFN_D_F27_FACTR_T,          MC_DIR_S2M, MC_PN_MP,  emc_trans_afn13f27,    "�ܹ�������"},
    {MCMD_AFN_D_F28_FACTR_A,          MC_DIR_S2M, MC_PN_MP,  emc_trans_afn13f28,    "A�๦������"},
    {MCMD_AFN_D_F29_FACTR_B,          MC_DIR_S2M, MC_PN_MP,  emc_trans_afn13f29,    "B�๦������"},
    {MCMD_AFN_D_F30_FACTR_C,          MC_DIR_S2M, MC_PN_MP,  emc_trans_afn13f30,    "C�๦������"},

    // ��5   pn:�������
    {MCMD_AFN_D_F33_DEMAND,           MC_DIR_S2M, MC_PN_MP,  emc_trans_afn13f33,    "����"},
    {MCMD_AFN_D_F34_DEMAND_MAX,       MC_DIR_S2M, MC_PN_MP,  emc_trans_afn13f34,    "���������"},
    {MCMD_AFN_D_F35_DEMAND_TIME,      MC_DIR_S2M, MC_PN_MP,  emc_trans_afn13f35,    "�������������ʱ��"},

    // ��6  pn:�������
    {MCMD_AFN_D_F41_POWR_HAVE_A,      MC_DIR_S2M, MC_PN_MP,  emc_trans_afn13f41,    "A���й�����"},
    {MCMD_AFN_D_F42_POWR_HAVE_B,      MC_DIR_S2M, MC_PN_MP,  emc_trans_afn13f42,    "B���й�����"},
    {MCMD_AFN_D_F43_POWR_HAVE_C,      MC_DIR_S2M, MC_PN_MP,  emc_trans_afn13f43,    "C���й�����"},
    {MCMD_AFN_D_F44_POWR_NONE_A,      MC_DIR_S2M, MC_PN_MP,  emc_trans_afn13f44,    "A���޹�����"},
    {MCMD_AFN_D_F45_POWR_NONE_B,      MC_DIR_S2M, MC_PN_MP,  emc_trans_afn13f45,    "B���޹�����"},
    {MCMD_AFN_D_F46_POWR_NONE_C,      MC_DIR_S2M, MC_PN_MP,  emc_trans_afn13f46,    "C���޹�����"},

    // ��7  pn:�������
    {MCMD_AFN_D_F49_POWR_HAVE_FRTH,   MC_DIR_S2M, MC_PN_MP,  emc_trans_afn13f49,    "�������й��ܵ���ʾ��"},
    {MCMD_AFN_D_F50_POWR_HAVE_BACK,   MC_DIR_S2M, MC_PN_MP,  emc_trans_afn13f50,    "�������й��ܵ���ʾ��"},
    {MCMD_AFN_D_F51_POWR_NONE_FRTH,   MC_DIR_S2M, MC_PN_MP,  emc_trans_afn13f51,    "�������޹��ܵ���ʾ��"},
    {MCMD_AFN_D_F52_POWR_NONE_BACK,   MC_DIR_S2M, MC_PN_MP,  emc_trans_afn13f52,    "�������޹��ܵ���ʾ��"},

    // ��8  pn:�������
    {MCMD_AFN_D_F57_VOLT_A,           MC_DIR_S2M, MC_PN_MP,  emc_trans_afn13f57,    "A���ѹ"},
    {MCMD_AFN_D_F58_VOLT_B,           MC_DIR_S2M, MC_PN_MP,  emc_trans_afn13f58,    "B���ѹ"},
    {MCMD_AFN_D_F59_VOLT_C,           MC_DIR_S2M, MC_PN_MP,  emc_trans_afn13f59,    "C���ѹ"},
    {MCMD_AFN_D_F60_VANGL_A,          MC_DIR_S2M, MC_PN_MP,  emc_trans_afn13f60,    "A���ѹ��λ��"},
    {MCMD_AFN_D_F61_VANGL_B,          MC_DIR_S2M, MC_PN_MP,  emc_trans_afn13f61,    "B���ѹ��λ��"},
    {MCMD_AFN_D_F62_VANGL_C,          MC_DIR_S2M, MC_PN_MP,  emc_trans_afn13f62,    "C���ѹ��λ��"},
    {MCMD_AFN_D_F63_VOLT_UBL,         MC_DIR_S2M, MC_PN_MP,  emc_trans_afn13f63,    "��ѹ��ƽ���"},
    {MCMD_AFN_D_F64_CIRCLE_V,         MC_DIR_S2M, MC_PN_MP,  emc_trans_afn13f64,    "�ܲ�"},

    // ��9  pn:�������
    {MCMD_AFN_D_F65_ELEC_A,           MC_DIR_S2M, MC_PN_MP,  emc_trans_afn13f65,    "A�����"},
    {MCMD_AFN_D_F66_ELEC_B,           MC_DIR_S2M, MC_PN_MP,  emc_trans_afn13f66,    "B�����"},
    {MCMD_AFN_D_F67_ELEC_C,           MC_DIR_S2M, MC_PN_MP,  emc_trans_afn13f67,    "C�����"},
    {MCMD_AFN_D_F68_ELEC_M,           MC_DIR_S2M, MC_PN_MP,  emc_trans_afn13f68,    "�����ߵ���"},
    {MCMD_AFN_D_F69_EANGL_A,          MC_DIR_S2M, MC_PN_MP,  emc_trans_afn13f69,    "A�������λ��"},
    {MCMD_AFN_D_F70_EANGL_B,          MC_DIR_S2M, MC_PN_MP,  emc_trans_afn13f70,    "B�������λ��"},
    {MCMD_AFN_D_F71_EANGL_C,          MC_DIR_S2M, MC_PN_MP,  emc_trans_afn13f71,    "C�������λ��"},
    {MCMD_AFN_D_F72_ELEC_UBL,         MC_DIR_S2M, MC_PN_MP,  emc_trans_afn13f72,    "������ƽ���"},

    // ��10  pn:�����������
    {MCMD_AFN_D_F73_VDMAX_A,          MC_DIR_S2M, MC_PN_MP,  emc_trans_afn13f73,    "��A���ѹ����ֵ"},
    {MCMD_AFN_D_F74_VDMAX_A_TIME,     MC_DIR_S2M, MC_PN_MP,  emc_trans_afn13f74,    "��A���ѹ����ֵ����ʱ��"},
    {MCMD_AFN_D_F75_VDMAX_B,          MC_DIR_S2M, MC_PN_MP,  emc_trans_afn13f75,    "��B���ѹ����ֵ"},
    {MCMD_AFN_D_F76_VDMAX_B_TIME,     MC_DIR_S2M, MC_PN_MP,  emc_trans_afn13f76,    "��B���ѹ����ֵ����ʱ��"},
    {MCMD_AFN_D_F77_VDMAX_C,          MC_DIR_S2M, MC_PN_MP,  emc_trans_afn13f77,    "��C���ѹ����ֵ"},
    {MCMD_AFN_D_F78_VDMAX_C_TIME,     MC_DIR_S2M, MC_PN_MP,  emc_trans_afn13f78,    "��C���ѹ����ֵ����ʱ��"},

    // ��11  pn:����������
    {MCMD_AFN_D_F81_IDMAX_A,          MC_DIR_S2M, MC_PN_MP,  emc_trans_afn13f81,    "��A���������ֵ"},
    {MCMD_AFN_D_F82_IDMAX_A_TIME,     MC_DIR_S2M, MC_PN_MP,  emc_trans_afn13f82,    "��A���������ֵ����ʱ��"},
    {MCMD_AFN_D_F83_IDMAX_B,          MC_DIR_S2M, MC_PN_MP,  emc_trans_afn13f83,    "��B���������ֵ"},
    {MCMD_AFN_D_F84_IDMAX_B_TIME,     MC_DIR_S2M, MC_PN_MP,  emc_trans_afn13f84,    "��B���������ֵ����ʱ��"},
    {MCMD_AFN_D_F85_IDMAX_C,          MC_DIR_S2M, MC_PN_MP,  emc_trans_afn13f85,    "��C���������ֵ"},
    {MCMD_AFN_D_F86_IDMAX_C_TIME,     MC_DIR_S2M, MC_PN_MP,  emc_trans_afn13f86,    "��C���������ֵ����ʱ��"},

    // ��12 pn:�����������
    {MCMD_AFN_D_F89_TFW_HAVE,         MC_DIR_S2M, MC_PN_MP,  emc_trans_afn13f89,    "�ܻ����й�����"},
    {MCMD_AFN_D_F90_TFW_NONE,         MC_DIR_S2M, MC_PN_MP,  emc_trans_afn13f90,    "�ܻ����޹�����"},
    {MCMD_AFN_D_F91_THW_HAVE,         MC_DIR_S2M, MC_PN_MP,  emc_trans_afn13f91,    "��г���й�����"},
    {MCMD_AFN_D_F92_THW_NONE,         MC_DIR_S2M, MC_PN_MP,  emc_trans_afn13f92,    "�ܻ����޹�����"},

    // ��13 pn:�����������
    {MCMD_AFN_D_F97_VDPP_TIME_A,      MC_DIR_S2M, MC_PN_MP,  emc_trans_afn13f97,    "A���ѹԽ���������ۼ�ʱ��"},
    {MCMD_AFN_D_F98_VDPP_TIME_B,      MC_DIR_S2M, MC_PN_MP,  emc_trans_afn13f97,    "B���ѹԽ���������ۼ�ʱ��"},
    {MCMD_AFN_D_F99_VDPP_TIME_C,      MC_DIR_S2M, MC_PN_MP,  emc_trans_afn13f97,    "C���ѹԽ���������ۼ�ʱ��"},
    {MCMD_AFN_D_F100_VDNN_TIME_A,     MC_DIR_S2M, MC_PN_MP,  emc_trans_afn13f97,    "A���ѹԽ���������ۼ�ʱ��"},
    {MCMD_AFN_D_F101_VDNN_TIME_B,     MC_DIR_S2M, MC_PN_MP,  emc_trans_afn13f97,    "B���ѹԽ���������ۼ�ʱ��"},
    {MCMD_AFN_D_F102_VDNN_TIME_C,     MC_DIR_S2M, MC_PN_MP,  emc_trans_afn13f97,    "C���ѹԽ���������ۼ�ʱ��"},

    // ��14 pn:�������
    {MCMD_AFN_D_F105_VMPP_TIME_A,     MC_DIR_S2M, MC_PN_MP,  emc_trans_afn13f6,     "A���ѹԽ���������ۼ�ʱ��"},
    {MCMD_AFN_D_F106_VMPP_TIME_B,     MC_DIR_S2M, MC_PN_MP,  emc_trans_afn13f6,     "B���ѹԽ���������ۼ�ʱ��"},
    {MCMD_AFN_D_F107_VMPP_TIME_C,     MC_DIR_S2M, MC_PN_MP,  emc_trans_afn13f6,     "C���ѹԽ���������ۼ�ʱ��"},
    {MCMD_AFN_D_F108_VMNN_TIME_A,     MC_DIR_S2M, MC_PN_MP,  emc_trans_afn13f6,     "A���ѹԽ���������ۼ�ʱ��"},
    {MCMD_AFN_D_F109_VMNN_TIME_B,     MC_DIR_S2M, MC_PN_MP,  emc_trans_afn13f6,     "B���ѹԽ���������ۼ�ʱ��"},
    {MCMD_AFN_D_F110_VMNN_TIME_C,     MC_DIR_S2M, MC_PN_MP,  emc_trans_afn13f6,     "C���ѹԽ���������ۼ�ʱ��"},

    // ��15 pn:�����������
    {MCMD_AFN_D_F113_VABR_TOTL_A,     MC_DIR_S2M, MC_PN_MP,  emc_trans_afn13f27,    "A���ѹ�ܻ�����"},
    {MCMD_AFN_D_F114_VABR_TOTL_B,     MC_DIR_S2M, MC_PN_MP,  emc_trans_afn13f27,    "B���ѹ�ܻ�����"},
    {MCMD_AFN_D_F115_VABR_TOTL_C,     MC_DIR_S2M, MC_PN_MP,  emc_trans_afn13f27,    "C���ѹ�ܻ�����"},
    {MCMD_AFN_D_F116_EABR_TOTL_A,     MC_DIR_S2M, MC_PN_MP,  emc_trans_afn13f27,    "A������ܻ�����"},
    {MCMD_AFN_D_F117_EABR_TOTL_B,     MC_DIR_S2M, MC_PN_MP,  emc_trans_afn13f27,    "B������ܻ�����"},
    {MCMD_AFN_D_F118_EABR_TOTL_C,     MC_DIR_S2M, MC_PN_MP,  emc_trans_afn13f27,    "C������ܻ�����"},

    // ��16 pn:�����������
    {MCMD_AFN_D_F121_VABR_ODD_A,      MC_DIR_S2M, MC_PN_MP,  emc_trans_afn13f27,    "A���ѹ��λ�����"},
    {MCMD_AFN_D_F122_VABR_EVN_A,      MC_DIR_S2M, MC_PN_MP,  emc_trans_afn13f27,    "A���ѹż�λ�����"},
    {MCMD_AFN_D_F123_VABR_ODD_B,      MC_DIR_S2M, MC_PN_MP,  emc_trans_afn13f27,    "B���ѹ��λ�����"},
    {MCMD_AFN_D_F124_VABR_EVN_B,      MC_DIR_S2M, MC_PN_MP,  emc_trans_afn13f27,    "B���ѹż�λ�����"},
    {MCMD_AFN_D_F125_VABR_ODD_C,      MC_DIR_S2M, MC_PN_MP,  emc_trans_afn13f27,    "C���ѹ��λ�����"},
    {MCMD_AFN_D_F126_VABR_EVN_C,      MC_DIR_S2M, MC_PN_MP,  emc_trans_afn13f27,    "C���ѹż�λ�����"},

    // ��17 pn:�����������
    {MCMD_AFN_D_F128_EABR_OOD_A,      MC_DIR_S2M, MC_PN_MP,  emc_trans_afn13f27,    "A�������λ�����"},
    {MCMD_AFN_D_F129_EABR_EVN_A,      MC_DIR_S2M, MC_PN_MP,  emc_trans_afn13f27,    "A�����ż�λ�����"},
    {MCMD_AFN_D_F130_EABR_OOD_B,      MC_DIR_S2M, MC_PN_MP,  emc_trans_afn13f27,    "B�������λ�����"},
    {MCMD_AFN_D_F131_EABR_EVN_B,      MC_DIR_S2M, MC_PN_MP,  emc_trans_afn13f27,    "B�����ż�λ�����"},
    {MCMD_AFN_D_F132_EABR_OOD_C,      MC_DIR_S2M, MC_PN_MP,  emc_trans_afn13f27,    "C�������λ�����"},
    {MCMD_AFN_D_F133_EABR_EVN_C,      MC_DIR_S2M, MC_PN_MP,  emc_trans_afn13f27,    "C�����ż�λ�����"},

    // ��18 pn:�����������
    {MCMD_AFN_D_F137_FLS_SHRT_A,      MC_DIR_S2M, MC_PN_MP,  emc_trans_afn13f27,    "A���ʱ����"},
    {MCMD_AFN_D_F138_FLS_SHRT_B,      MC_DIR_S2M, MC_PN_MP,  emc_trans_afn13f27,    "B���ʱ����"},
    {MCMD_AFN_D_F139_FLS_SHRT_C,      MC_DIR_S2M, MC_PN_MP,  emc_trans_afn13f27,    "C���ʱ����"},
    {MCMD_AFN_D_F140_FLS_LONG_A,      MC_DIR_S2M, MC_PN_MP,  emc_trans_afn13f27,    "A�೤ʱ����"},
    {MCMD_AFN_D_F141_FLS_LONG_B,      MC_DIR_S2M, MC_PN_MP,  emc_trans_afn13f27,    "B�೤ʱ����"},
    {MCMD_AFN_D_F142_FLS_LONG_C,      MC_DIR_S2M, MC_PN_MP,  emc_trans_afn13f27,    "C�೤ʱ����"},

    // ��19 pn:�����������
    {MCMD_AFN_D_F145_HARM_VOLT_A,     MC_DIR_S2M, MC_PN_MP,  emc_trans_afn13f145,   "A��N��г����ѹ"},
    {MCMD_AFN_D_F146_HARM_VOLT_B,     MC_DIR_S2M, MC_PN_MP,  emc_trans_afn13f145,   "B��N��г����ѹ"},
    {MCMD_AFN_D_F147_HARM_VOLT_C,     MC_DIR_S2M, MC_PN_MP,  emc_trans_afn13f145,   "C��N��г����ѹ"},
    {MCMD_AFN_D_F148_HARM_ELEC_A,     MC_DIR_S2M, MC_PN_MP,  emc_trans_afn13f148,   "A��N��г������"},
    {MCMD_AFN_D_F149_HARM_ELEC_B,     MC_DIR_S2M, MC_PN_MP,  emc_trans_afn13f148,   "B��N��г������"},
    {MCMD_AFN_D_F150_HARM_ELEC_C,     MC_DIR_S2M, MC_PN_MP,  emc_trans_afn13f148,   "C��N��г������"},

    // ��20 pn:�����������
    {MCMD_AFN_D_F153_HARM_VINC_A,     MC_DIR_S2M, MC_PN_MP,  emc_trans_afn13f153,   "A��N��г����ѹ������"},
    {MCMD_AFN_D_F154_HARM_VINC_B,     MC_DIR_S2M, MC_PN_MP,  emc_trans_afn13f153,   "B��N��г����ѹ������"},
    {MCMD_AFN_D_F155_HARM_VINC_C,     MC_DIR_S2M, MC_PN_MP,  emc_trans_afn13f153,   "C��N��г����ѹ������"},
    {MCMD_AFN_D_F156_HARM_EINC_A,     MC_DIR_S2M, MC_PN_MP,  emc_trans_afn13f153,   "A��N��г������������"},
    {MCMD_AFN_D_F157_HARM_EINC_B,     MC_DIR_S2M, MC_PN_MP,  emc_trans_afn13f153,   "B��N��г������������"},
    {MCMD_AFN_D_F158_HARM_EINC_C,     MC_DIR_S2M, MC_PN_MP,  emc_trans_afn13f153,   "C��N��г������������"},

    // ��30 pn:�ǵ����������
    {MCMD_AFN_D_F233_NELC_VALUE,      MC_DIR_S2M, MC_PN_MP,  emc_trans_afn13f233,    "�ǵ�����"},
    /** } ���� **/

    /** { ���� **/
    // ��1   pn:p0/����ն˺�
    {MCMD_AFN_D_F1_CLOCK,             MC_DIR_M2S, MC_PN_P0,  NULL,     "����ʱ��"},
    {MCMD_AFN_D_F2_PARA_STATE,        MC_DIR_M2S, MC_PN_P0,  NULL,     "����״̬��־"},
    {MCMD_AFN_D_F3_EVENT_1,           MC_DIR_M2S, MC_PN_P0,  NULL,     "��Ҫ�¼���������ǰֵ"},
    {MCMD_AFN_D_F4_EVENT_2,           MC_DIR_M2S, MC_PN_P0,  NULL,     "һ���¼���������ǰֵ"},
    {MCMD_AFN_D_F5_EVENT_STATE,       MC_DIR_M2S, MC_PN_P0,  NULL,     "�¼�״̬��־"},
    {MCMD_AFN_D_F6_POWR_TIMES,        MC_DIR_M2S, MC_PN_P0,  NULL,     "�ϵ����"},

    // ��2   pn:p0/����ն˺�
    {MCMD_AFN_D_F9_STATE,             MC_DIR_M2S, MC_PN_P0,  NULL,     "״̬������λ��־"},
    {MCMD_AFN_D_F10_SWITCH,           MC_DIR_M2S, MC_PN_P0,  NULL,     "���������·���ؽ���״̬������λ��־"},

    // ��4   pn:p0/�����������
    {MCMD_AFN_D_F25_POWR_HAVE_T,      MC_DIR_M2S, MC_PN_MP,  NULL,     "���й�����"},
    {MCMD_AFN_D_F26_POWR_NONE_T,      MC_DIR_M2S, MC_PN_MP,  NULL,     "���޹�����"},
    {MCMD_AFN_D_F27_FACTR_T,          MC_DIR_M2S, MC_PN_MP,  NULL,     "�ܹ�������"},
    {MCMD_AFN_D_F28_FACTR_A,          MC_DIR_M2S, MC_PN_MP,  NULL,     "A�๦������"},
    {MCMD_AFN_D_F29_FACTR_B,          MC_DIR_M2S, MC_PN_MP,  NULL,     "B�๦������"},
    {MCMD_AFN_D_F30_FACTR_C,          MC_DIR_M2S, MC_PN_MP,  NULL,     "C�๦������"},

    // ��5   pn:�������
    {MCMD_AFN_D_F33_DEMAND,           MC_DIR_M2S, MC_PN_MP,  NULL,     "���й�����"},
    {MCMD_AFN_D_F34_DEMAND_MAX,       MC_DIR_M2S, MC_PN_MP,  NULL,     "���޹�����"},
    {MCMD_AFN_D_F35_DEMAND_TIME,      MC_DIR_M2S, MC_PN_MP,  NULL,     "�ܹ�������"},

    // ��6  pn:�������
    {MCMD_AFN_D_F41_POWR_HAVE_A,      MC_DIR_M2S, MC_PN_MP,  NULL,     "A���й�����"},
    {MCMD_AFN_D_F42_POWR_HAVE_B,      MC_DIR_M2S, MC_PN_MP,  NULL,     "B���й�����"},
    {MCMD_AFN_D_F43_POWR_HAVE_C,      MC_DIR_M2S, MC_PN_MP,  NULL,     "C���й�����"},
    {MCMD_AFN_D_F44_POWR_NONE_A,      MC_DIR_M2S, MC_PN_MP,  NULL,     "A���޹�����"},
    {MCMD_AFN_D_F45_POWR_NONE_B,      MC_DIR_M2S, MC_PN_MP,  NULL,     "B���޹�����"},
    {MCMD_AFN_D_F46_POWR_NONE_C,      MC_DIR_M2S, MC_PN_MP,  NULL,     "C���޹�����"},

    // ��7  pn:�������
    {MCMD_AFN_D_F49_POWR_HAVE_FRTH,   MC_DIR_M2S, MC_PN_MP,  NULL,     "�������й��ܵ���ʾ��"},
    {MCMD_AFN_D_F50_POWR_HAVE_BACK,   MC_DIR_M2S, MC_PN_MP,  NULL,     "�������й��ܵ���ʾ��"},
    {MCMD_AFN_D_F51_POWR_NONE_FRTH,   MC_DIR_M2S, MC_PN_MP,  NULL,     "�������޹��ܵ���ʾ��"},
    {MCMD_AFN_D_F52_POWR_NONE_BACK,   MC_DIR_M2S, MC_PN_MP,  NULL,     "�������޹��ܵ���ʾ��"},

    // ��8  pn:�������
    {MCMD_AFN_D_F57_VOLT_A,           MC_DIR_M2S, MC_PN_MP,  NULL,     "A���ѹ"},
    {MCMD_AFN_D_F58_VOLT_B,           MC_DIR_M2S, MC_PN_MP,  NULL,     "B���ѹ"},
    {MCMD_AFN_D_F59_VOLT_C,           MC_DIR_M2S, MC_PN_MP,  NULL,     "C���ѹ"},
    {MCMD_AFN_D_F60_VANGL_A,          MC_DIR_M2S, MC_PN_MP,  NULL,     "A���ѹ��λ��"},
    {MCMD_AFN_D_F61_VANGL_B,          MC_DIR_M2S, MC_PN_MP,  NULL,     "B���ѹ��λ��"},
    {MCMD_AFN_D_F62_VANGL_C,          MC_DIR_M2S, MC_PN_MP,  NULL,     "C���ѹ��λ��"},
    {MCMD_AFN_D_F63_VOLT_UBL,         MC_DIR_M2S, MC_PN_MP,  NULL,     "��ѹ��ƽ���"},
    {MCMD_AFN_D_F64_CIRCLE_V,         MC_DIR_M2S, MC_PN_MP,  NULL,     "�ܲ�"},

    // ��9  pn:�������
    {MCMD_AFN_D_F65_ELEC_A,           MC_DIR_M2S, MC_PN_MP,  NULL,     "A�����"},
    {MCMD_AFN_D_F66_ELEC_B,           MC_DIR_M2S, MC_PN_MP,  NULL,     "B�����"},
    {MCMD_AFN_D_F67_ELEC_C,           MC_DIR_M2S, MC_PN_MP,  NULL,     "C�����"},
    {MCMD_AFN_D_F68_ELEC_M,           MC_DIR_M2S, MC_PN_MP,  NULL,     "�����ߵ���"},
    {MCMD_AFN_D_F69_EANGL_A,          MC_DIR_M2S, MC_PN_MP,  NULL,     "A�������λ��"},
    {MCMD_AFN_D_F70_EANGL_B,          MC_DIR_M2S, MC_PN_MP,  NULL,     "B�������λ��"},
    {MCMD_AFN_D_F71_EANGL_C,          MC_DIR_M2S, MC_PN_MP,  NULL,     "C�������λ��"},
    {MCMD_AFN_D_F72_ELEC_UBL,         MC_DIR_M2S, MC_PN_MP,  NULL,     "������ƽ���"},

    // ��10  pn:�����������
    {MCMD_AFN_D_F73_VDMAX_A,          MC_DIR_M2S, MC_PN_MP,  NULL,     "��A���ѹ����ֵ"},
    {MCMD_AFN_D_F74_VDMAX_A_TIME,     MC_DIR_M2S, MC_PN_MP,  NULL,     "��A���ѹ����ֵ����ʱ��"},
    {MCMD_AFN_D_F75_VDMAX_B,          MC_DIR_M2S, MC_PN_MP,  NULL,     "��A���ѹ����ֵ"},
    {MCMD_AFN_D_F76_VDMAX_B_TIME,     MC_DIR_M2S, MC_PN_MP,  NULL,     "��A���ѹ����ֵ����ʱ��"},
    {MCMD_AFN_D_F77_VDMAX_C,          MC_DIR_M2S, MC_PN_MP,  NULL,     "��A���ѹ����ֵ"},
    {MCMD_AFN_D_F78_VDMAX_C_TIME,     MC_DIR_M2S, MC_PN_MP,  NULL,     "��A���ѹ����ֵ����ʱ��"},

    // ��11  pn:�����������
    {MCMD_AFN_D_F81_IDMAX_A,          MC_DIR_M2S, MC_PN_MP,  NULL,     "��A���������ֵ"},
    {MCMD_AFN_D_F82_IDMAX_A_TIME,     MC_DIR_M2S, MC_PN_MP,  NULL,     "��A���������ֵ����ʱ��"},
    {MCMD_AFN_D_F83_IDMAX_B,          MC_DIR_M2S, MC_PN_MP,  NULL,     "��A���������ֵ"},
    {MCMD_AFN_D_F84_IDMAX_B_TIME,     MC_DIR_M2S, MC_PN_MP,  NULL,     "��A���������ֵ����ʱ��"},
    {MCMD_AFN_D_F85_IDMAX_C,          MC_DIR_M2S, MC_PN_MP,  NULL,     "��A���������ֵ"},
    {MCMD_AFN_D_F86_IDMAX_C_TIME,     MC_DIR_M2S, MC_PN_MP,  NULL,     "��A���������ֵ����ʱ��"},

    // ��12 pn:�����������
    {MCMD_AFN_D_F89_TFW_HAVE,         MC_DIR_M2S, MC_PN_MP,  NULL,     "�ܻ����й�����"},
    {MCMD_AFN_D_F90_TFW_NONE,         MC_DIR_M2S, MC_PN_MP,  NULL,     "�ܻ����޹�����"},
    {MCMD_AFN_D_F91_THW_HAVE,         MC_DIR_M2S, MC_PN_MP,  NULL,     "��г���й�����"},
    {MCMD_AFN_D_F92_THW_NONE,         MC_DIR_M2S, MC_PN_MP,  NULL,     "�ܻ����޹�����"},

    // ��13 pn:�����������
    {MCMD_AFN_D_F97_VDPP_TIME_A,      MC_DIR_M2S, MC_PN_MP,  NULL,     "A���ѹԽ���������ۼ�ʱ��"},
    {MCMD_AFN_D_F98_VDPP_TIME_B,      MC_DIR_M2S, MC_PN_MP,  NULL,     "B���ѹԽ���������ۼ�ʱ��"},
    {MCMD_AFN_D_F99_VDPP_TIME_C,      MC_DIR_M2S, MC_PN_MP,  NULL,     "C���ѹԽ���������ۼ�ʱ��"},
    {MCMD_AFN_D_F100_VDNN_TIME_A,     MC_DIR_M2S, MC_PN_MP,  NULL,     "A���ѹԽ���������ۼ�ʱ��"},
    {MCMD_AFN_D_F101_VDNN_TIME_B,     MC_DIR_M2S, MC_PN_MP,  NULL,     "B���ѹԽ���������ۼ�ʱ��"},
    {MCMD_AFN_D_F102_VDNN_TIME_C,     MC_DIR_M2S, MC_PN_MP,  NULL,     "C���ѹԽ���������ۼ�ʱ��"},

    // ��14 pn:�������
    {MCMD_AFN_D_F105_VMPP_TIME_A,     MC_DIR_M2S, MC_PN_MP,  NULL,     "A���ѹԽ���������ۼ�ʱ��"},
    {MCMD_AFN_D_F106_VMPP_TIME_B,     MC_DIR_M2S, MC_PN_MP,  NULL,     "B���ѹԽ���������ۼ�ʱ��"},
    {MCMD_AFN_D_F107_VMPP_TIME_C,     MC_DIR_M2S, MC_PN_MP,  NULL,     "C���ѹԽ���������ۼ�ʱ��"},
    {MCMD_AFN_D_F108_VMNN_TIME_A,     MC_DIR_M2S, MC_PN_MP,  NULL,     "A���ѹԽ���������ۼ�ʱ��"},
    {MCMD_AFN_D_F109_VMNN_TIME_B,     MC_DIR_M2S, MC_PN_MP,  NULL,     "B���ѹԽ���������ۼ�ʱ��"},
    {MCMD_AFN_D_F110_VMNN_TIME_C,     MC_DIR_M2S, MC_PN_MP,  NULL,     "C���ѹԽ���������ۼ�ʱ��"},

    // ��15 pn:�����������
    {MCMD_AFN_D_F113_VABR_TOTL_A,     MC_DIR_M2S, MC_PN_MP,  NULL,     "A���ѹ�ܻ�����"},
    {MCMD_AFN_D_F114_VABR_TOTL_B,     MC_DIR_M2S, MC_PN_MP,  NULL,     "B���ѹ�ܻ�����"},
    {MCMD_AFN_D_F115_VABR_TOTL_C,     MC_DIR_M2S, MC_PN_MP,  NULL,     "C���ѹ�ܻ�����"},
    {MCMD_AFN_D_F116_EABR_TOTL_A,     MC_DIR_M2S, MC_PN_MP,  NULL,     "A������ܻ�����"},
    {MCMD_AFN_D_F117_EABR_TOTL_B,     MC_DIR_M2S, MC_PN_MP,  NULL,     "B������ܻ�����"},
    {MCMD_AFN_D_F118_EABR_TOTL_C,     MC_DIR_M2S, MC_PN_MP,  NULL,     "C������ܻ�����"},

    // ��16 pn:�����������
    {MCMD_AFN_D_F121_VABR_ODD_A,      MC_DIR_M2S, MC_PN_MP,  NULL,     "A���ѹ��λ�����"},
    {MCMD_AFN_D_F122_VABR_EVN_A,      MC_DIR_M2S, MC_PN_MP,  NULL,     "A���ѹż�λ�����"},
    {MCMD_AFN_D_F123_VABR_ODD_B,      MC_DIR_M2S, MC_PN_MP,  NULL,     "B���ѹ��λ�����"},
    {MCMD_AFN_D_F124_VABR_EVN_B,      MC_DIR_M2S, MC_PN_MP,  NULL,     "B���ѹż�λ�����"},
    {MCMD_AFN_D_F125_VABR_ODD_C,      MC_DIR_M2S, MC_PN_MP,  NULL,     "C���ѹ��λ�����"},
    {MCMD_AFN_D_F126_VABR_EVN_C,      MC_DIR_M2S, MC_PN_MP,  NULL,     "C���ѹż�λ�����"},

    // ��17 pn:�����������
    {MCMD_AFN_D_F128_EABR_OOD_A,      MC_DIR_M2S, MC_PN_MP,  NULL,     "A�������λ�����"},
    {MCMD_AFN_D_F129_EABR_EVN_A,      MC_DIR_M2S, MC_PN_MP,  NULL,     "A�����ż�λ�����"},
    {MCMD_AFN_D_F130_EABR_OOD_B,      MC_DIR_M2S, MC_PN_MP,  NULL,     "B�������λ�����"},
    {MCMD_AFN_D_F131_EABR_EVN_B,      MC_DIR_M2S, MC_PN_MP,  NULL,     "B�����ż�λ�����"},
    {MCMD_AFN_D_F132_EABR_OOD_C,      MC_DIR_M2S, MC_PN_MP,  NULL,     "C�������λ�����"},
    {MCMD_AFN_D_F133_EABR_EVN_C,      MC_DIR_M2S, MC_PN_MP,  NULL,     "C�����ż�λ�����"},

    // ��18 pn:�����������
    {MCMD_AFN_D_F137_FLS_SHRT_A,      MC_DIR_M2S, MC_PN_MP,  NULL,     "A���ʱ����"},
    {MCMD_AFN_D_F138_FLS_SHRT_B,      MC_DIR_M2S, MC_PN_MP,  NULL,     "B���ʱ����"},
    {MCMD_AFN_D_F139_FLS_SHRT_C,      MC_DIR_M2S, MC_PN_MP,  NULL,     "C���ʱ����"},
    {MCMD_AFN_D_F140_FLS_LONG_A,      MC_DIR_M2S, MC_PN_MP,  NULL,     "A�೤ʱ����"},
    {MCMD_AFN_D_F141_FLS_LONG_B,      MC_DIR_M2S, MC_PN_MP,  NULL,     "B�೤ʱ����"},
    {MCMD_AFN_D_F142_FLS_LONG_C,      MC_DIR_M2S, MC_PN_MP,  NULL,     "C�೤ʱ����"},

    // ��19 pn:�����������
    {MCMD_AFN_D_F145_HARM_VOLT_A,     MC_DIR_M2S, MC_PN_MP,  NULL,     "A��N��г����ѹ"},
    {MCMD_AFN_D_F146_HARM_VOLT_B,     MC_DIR_M2S, MC_PN_MP,  NULL,     "B��N��г����ѹ"},
    {MCMD_AFN_D_F147_HARM_VOLT_C,     MC_DIR_M2S, MC_PN_MP,  NULL,     "C��N��г����ѹ"},
    {MCMD_AFN_D_F148_HARM_ELEC_A,     MC_DIR_M2S, MC_PN_MP,  NULL,     "A��N��г������"},
    {MCMD_AFN_D_F149_HARM_ELEC_B,     MC_DIR_M2S, MC_PN_MP,  NULL,     "B��N��г������"},
    {MCMD_AFN_D_F150_HARM_ELEC_C,     MC_DIR_M2S, MC_PN_MP,  NULL,     "C��N��г������"},

    // ��20 pn:�����������
    {MCMD_AFN_D_F153_HARM_VINC_A,     MC_DIR_M2S, MC_PN_MP,  NULL,     "A��N��г����ѹ������"},
    {MCMD_AFN_D_F154_HARM_VINC_B,     MC_DIR_M2S, MC_PN_MP,  NULL,     "B��N��г����ѹ������"},
    {MCMD_AFN_D_F155_HARM_VINC_C,     MC_DIR_M2S, MC_PN_MP,  NULL,     "C��N��г����ѹ������"},
    {MCMD_AFN_D_F156_HARM_EINC_A,     MC_DIR_M2S, MC_PN_MP,  NULL,     "A��N��г������������"},
    {MCMD_AFN_D_F157_HARM_EINC_B,     MC_DIR_M2S, MC_PN_MP,  NULL,     "B��N��г������������"},
    {MCMD_AFN_D_F158_HARM_EINC_C,     MC_DIR_M2S, MC_PN_MP,  NULL,     "C��N��г������������"},

    // ��30 pn:�ǵ����������
    {MCMD_AFN_D_F233_NELC_VALUE,      MC_DIR_M2S, MC_PN_MP,  NULL,     "�ǵ�����"},
    /** } ���� **/
    ///*}

     /*******************************
     *  (13) ���������ϱ����¼���¼(AFN=0EH��
     *
     *  ����: ������
     *  ����: ������
     *  ����: ����Ҫ
     *
    {*///
    // ����
    {MCMD_AFN_E_F1_EVENT_1,           MC_DIR_S2M, MC_PN_P0,  emc_trans_afn14f1_s2m,  "������Ҫ�¼�"},
    {MCMD_AFN_E_F2_EVENT_2,           MC_DIR_S2M, MC_PN_P0,  emc_trans_afn14f2_s2m,  "����һ���¼�"},
    {MCMD_AFN_E_F3_EVENT_3,           MC_DIR_S2M, MC_PN_P0,  emc_trans_afn14f3_s2m,  "����ָ���¼�"},

    // ����
    {MCMD_AFN_E_F1_EVENT_1,           MC_DIR_M2S, MC_PN_P0,  emc_trans_afn14f1_m2s,  "������Ҫ�¼�"},
    {MCMD_AFN_E_F2_EVENT_2,           MC_DIR_M2S, MC_PN_P0,  emc_trans_afn14f1_m2s,  "����һ���¼�"},
    {MCMD_AFN_E_F3_EVENT_3,           MC_DIR_M2S, MC_PN_P0,  emc_trans_afn14f3_m2s,  "����ָ���¼�"},
    ///*}

     /*******************************
     *  (14) �ļ�����(AFN=0FH��
     *
     *  ����: ������
     *  ����: ������
     *  ����: ����Ҫ
     *
    {*///
    // ����
    // ��1   pn:p0/����ն˺�
    {MCMD_AFN_F_F1_SOFT_DOWN,          MC_DIR_S2M, MC_PN_P0,  NULL,  "�������"},
    {MCMD_AFN_F_F2_SOFT_LEFT,          MC_DIR_S2M, MC_PN_P0,  NULL,  "�������"},

    // ��2   pn:p0/����ն˺�
    {MCMD_AFN_F_F9_NXMD_DOWN,          MC_DIR_S2M, MC_PN_P0,  NULL,  "�������"},
    {MCMD_AFN_F_F10_NXMD_LEFT,         MC_DIR_S2M, MC_PN_P0,  NULL,  "�������"},

    // ��3   pn:p0/����ն˺�
    {MCMD_AFN_F_F17_REQS_DOWN,         MC_DIR_S2M, MC_PN_P0,  NULL,  "�������"},
    {MCMD_AFN_F_F18_REQS_LEFT,         MC_DIR_S2M, MC_PN_P0,  NULL,  "�������"},

    // ����
      // ��1   pn:p0/����ն˺�
    {MCMD_AFN_F_F1_SOFT_DOWN,          MC_DIR_M2S, MC_PN_P0,  NULL,  "�������"},
    {MCMD_AFN_F_F2_SOFT_LEFT,          MC_DIR_M2S, MC_PN_P0,  NULL,  "�������"},

    // ��2   pn:p0/����ն˺�
    {MCMD_AFN_F_F9_NXMD_DOWN,          MC_DIR_M2S, MC_PN_P0,  NULL,  "�������"},
    {MCMD_AFN_F_F10_NXMD_LEFT,         MC_DIR_M2S, MC_PN_P0,  NULL,  "�������"},

    // ��3   pn:p0/����ն˺�
    {MCMD_AFN_F_F17_REQS_DOWN,         MC_DIR_M2S, MC_PN_P0,  NULL,  "�������"},
    {MCMD_AFN_F_F18_REQS_LEFT,         MC_DIR_M2S, MC_PN_P0,  NULL,  "�������"},
    ///*}

     /*******************************
     *  (15) ����ת��(AFN=11H��
     *
     *  ����: ������
     *  ����: ������
     *  ����: ����Ҫ
     *
    {*///
    // ����
    {MCMD_AFN_10_F1_TRANSMIT,          MC_DIR_S2M, MC_PN_P0,  NULL,  "͸��ת��"},

    // ����
    {MCMD_AFN_10_F1_TRANSMIT,          MC_DIR_M2S, MC_PN_P0,  NULL,  "͸��ת��"},
    ///*}


     /*******************************
     *  (16) �������
     *
     *  �ڴ�֮����չ
     *  ����: ����Ҫ
     *
    {*///
    {MCMD_AFN_FN_MAX,                   MC_DIR_UNKOWN, MC_PN_P0,  NULL,  "�������ֵ"}
    ///*}
};

/*****************************************************************************
 �� �� ��  : MC_FREE
 ��������  : �ͷ�malloc������ڴ�ռ�
 �������  : UINT8 *pBuf
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��8��22��
    ��    ��   : liming
    �޸�����   : �����ɺ���

*****************************************************************************/
#define  MC_FREE(pBuf)\
if(pBuf != NULL)\
{\
    free(pBuf);\
    pBuf = NULL;\
}

/*****************************************************************************
 �� �� ��  : eMcGetCmdInfor
 ��������  : ͨ���������ͺͱ��ķ����ø������Ӧ�������Ϣ
 �������  : eMcmd eCmd
             eMcDir eDir
             sMcmdInfor *psInfor
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��10��22�� ���ڶ�
    ��    ��   : liming
    �޸�����   : �����ɺ���

*****************************************************************************/
eMcErr eMcGetCmdInfor(eMcmd eCmd, eMcDir eDir, sMcmdInfor* psInfor)
{
    INT32 i   = 0;
    INT32 Num = 0;

    if(!psInfor)
    {
        #ifdef MC_DBG
        MCDBG("eMcGetCmdInfor() pointer is null!");
        #endif
        return MC_ERR_NULL;
    }

    Num = sizeof(gmc_cmdinfor) / sizeof(sMcmdInfor);

    for(i = 0; i < Num; i++)
    {
        if(gmc_cmdinfor[i].eCmd == eCmd && gmc_cmdinfor[i].eDir == eDir)
        {
            psInfor->eCmd  = eCmd;
            psInfor->eDir  = eDir;
            psInfor->ePn   = gmc_cmdinfor[i].ePn;
            psInfor->pFunc = gmc_cmdinfor[i].pFunc;
            psInfor->pName = gmc_cmdinfor[i].pName;
            return MC_OK;
        }
    }

    return MC_ERR_NONE;
}

/*****************************************************************************
 �� �� ��  : ucmc_get_bcd_0
 ��������  : ���һ��char�������ݵ�BCD��λ
 �������  : UINT8 ucData
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��8��1�� ������
    ��    ��   : liming
    �޸�����   : �����ɺ���

*****************************************************************************/
UINT8 ucmc_get_bcd_0(UINT8 ucData)
{
    return (ucData % 10);
}

/*****************************************************************************
 �� �� ��  : ucmc_get_bcd_1
 ��������  : ���һ��char�������ݵ�BCD��λ
 �������  : UINT8 ucData
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��8��1�� ������
    ��    ��   : liming
    �޸�����   : �����ɺ���

*****************************************************************************/
UINT8 ucmc_get_bcd_1(UINT8 ucData)
{
    return (ucData / 10);
}

/*****************************************************************************
 �� �� ��  : emc_bcd_to_str
 ��������  : ������Ϊlen��BCD��תΪ2*len�����ַ���
 �������  : const UINT8 *pbcd
             UINT8 *pstr
             INT32 len
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��7��31�� ������
    ��    ��   : liming
    �޸�����   : �����ɺ���

*****************************************************************************/
eMcErr emc_bcd_to_str(const UINT8* pbcd, UINT8* pstr, INT32 len)
{
    INT32 i  = 0, j  = 0;
    UINT8 c1 = 0, c0 = 0;

    if(!pstr || !pbcd)
    {
        #ifdef MC_DBG
        MCDBG("emc_bcd_to_str() para pointer is null");
        #endif
        return MC_ERR_NULL;
    }

    if(len < 0)
    {
        #ifdef MC_DBG
        MCDBG("emc_bcd_to_str() para error");
        #endif
        return MC_ERR_PARA;
    }

    for(i = len - 1, j = 0; i >= 0; i--)
    {
        c0 = pbcd[i] & 0xF;
        c1 = (pbcd[i] >> 4) & 0xF;
        if(c1 >= 0 && c1 <= 9)
        {
            pstr[j++] = c1 + '0';
        }
        else
        {
            pstr[j++] = c1 + 'A';
        }

        if(c0 >= 0 && c0 <= 9)
        {
            pstr[j++] = c0 + '0';
        }
        else
        {
            pstr[j++] = c0 + 'A';
        }
    }

    return MC_OK;
}

/*****************************************************************************
 �� �� ��  : emc_str_to_bcd
 ��������  : ������Ϊlen���ַ���ת��ΪBCD ����Ϊ len/2
 �������  : const UINT8 *pstr
             UINT8  *pbcd
             INT32   len
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��7��31�� ������
    ��    ��   : liming
    �޸�����   : �����ɺ���

*****************************************************************************/
eMcErr emc_str_to_bcd(const UINT8* pstr, UINT8* pbcd, INT32 len)
{
    UINT8 tmpValue = 0;
    INT32        i = 0;
    INT32        j = 0;
    INT32        m = 0;
    INT32     sLen = 0;

    if(!pstr || !pbcd)
    {
        #ifdef MC_DBG
        MCDBG("emc_str_to_bcd() para pointer is null");
        #endif
        return MC_ERR_NULL;
    }

    if(len < 0)
    {
         #ifdef MC_DBG
         MCDBG("emc_str_to_bcd() para error");
         #endif
         return MC_ERR_PARA;
    }

    sLen = len;

    for(i = 0; i < sLen; i++)
    {
        if((pstr[i] < '0')
        ||((pstr[i] > '9') && (pstr[i] < 'A'))
        ||((pstr[i] > 'F') && (pstr[i] < 'a'))
        || (pstr[i] > 'f'))
        {
            sLen=i;
            break;
        }
    }

    sLen = ((sLen <= (len * 2)) ? sLen : sLen * 2);
    memset((void *)pbcd, 0x00, len);

    for(i = sLen-1, j = 0, m = 0; (i>=0) && (m<len); i--, j++)
    {
        if((pstr[i] >= '0') && (pstr[i] <= '9'))
        {
            tmpValue = pstr[i] - '0';
        }
        else if((pstr[i] >= 'A') && (pstr[i] <= 'F'))
        {
            tmpValue = (pstr[i] - 'A' + 0x0A);
        }
        else if((pstr[i] >= 'a') && (pstr[i] <= 'f'))
        {
            tmpValue = (pstr[i] - 'a' + 0x0A);
        }
        else
        {
            tmpValue = 0;
        }

        if((j % 2) == 0)
        {
            pbcd[m] = tmpValue;
        }
        else
        {
            pbcd[m++] |= (tmpValue << 4);
        }

        if((tmpValue == 0) && (pstr[i] != '0'))
        {
            break;
        }
    }

    return MC_OK;
}

/*****************************************************************************
 �� �� ��  : emc_trans_address
 ��������  : ��ַ���û������֡�����ݽṹת������
 �������  : eMcTrans eTrans

 �������  : sMcAddress   *psAddr_u
             sMcAddress_f *psAddr_f
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��10��22�� ���ڶ�
    ��    ��   : liming
    �޸�����   : �����ɺ���

*****************************************************************************/
eMcErr emc_trans_address(eMcTrans eTrans, sMcAddress *psAddr_u, sMcAddress_f *psAddr_f)
{
    if(!psAddr_u || !psAddr_f)
    {
        #ifdef MC_DBG
        MCDBG("emc_trans_address() para pointer is null!");
        #endif
        return MC_ERR_NULL;
    }

    if(MC_TRANS_U2F == eTrans)
    {
        if(0 == psAddr_u->ulConAddress)
        {
            #ifdef MC_DBG
            MCDBG("emc_trans_address() contrator address error!");
            #endif
            return MC_ERR_ADDR;
        }

        if(psAddr_u->ucMstAddress > MC_MST_ADDR_MAX ||
           psAddr_u->ucMstAddress < MC_MST_ADDR_MIN)
        {
            #ifdef MC_DBG
            MCDBG("emc_trans_address() master address error!");
            #endif
            return MC_ERR_ADDR;
        }

        (void)emc_str_to_bcd((UINT8*)(psAddr_u->acRegionCode), 
                             (UINT8*)(psAddr_f->acRegionCode), 
                             MC_REGN_LEN);

        psAddr_f->ulConAddress = psAddr_u->ulConAddress;
        psAddr_f->ucMstAddress = psAddr_u->ucMstAddress << 1;
        
        if(TRUE == psAddr_u->bTeam)
        {
            psAddr_f->ucMstAddress |= 0x01;
        }
        else
        {
            psAddr_f->ucMstAddress &= 0xFE;
        }
    }
    else if(MC_TRANS_F2U == eTrans)
    {
        (void)emc_bcd_to_str((UINT8*)(psAddr_f->acRegionCode), 
                             (UINT8*)(psAddr_u->acRegionCode), 
                             MC_A1_LEN);

        psAddr_u->ulConAddress = psAddr_f->ulConAddress;
        psAddr_u->bTeam        = (psAddr_f->ucMstAddress & 0x01) ? TRUE : FALSE;
        psAddr_u->ucMstAddress = (psAddr_f->ucMstAddress >> 1) & 0x7F;
    }
    else
    {
        #ifdef MC_DBG
        MCDBG("emc_trans_address() para error!");
        #endif
        return MC_ERR_PARA;
    }

    return MC_OK;
}

/*****************************************************************************
 �� �� ��  : emc_get_prm
 ��������  : ���ĳ����Ӧ�õ�prmֵ
 �������  : eMcDir eDir  
             eMcAFN eAfn  
             BOOL bAuto      �Ƿ�Ϊ�����ϱ�
 �������  : ��
 �� �� ֵ  : 
 ���ú���  : 
 ��������  : 
 
 �޸���ʷ      :
  1.��    ��   : 2013��11��28��
    ��    ��   : liming
    �޸�����   : �����ɺ���

*****************************************************************************/
eMcPRM emc_get_prm(eMcDir eDir, eMcAFN eAfn, BOOL bAuto)
{
    eMcPRM  ePrm = MC_PRM_UNKWON;

    if(eDir == MC_DIR_M2S)
    {
        switch ( eAfn )
        {
            case MC_AFN_00_CONF :
            case MC_AFN_02_LINK :
                ePrm = MC_PRM_P2A;
                break;
                
            case MC_AFN_01_RSET :
            case MC_AFN_04_SETP :
            case MC_AFN_05_CTRL :
            case MC_AFN_06_AUTH :
            case MC_AFN_08_CASC :
            case MC_AFN_10_GETP :
            case MC_AFN_12_ASKT :
            case MC_AFN_13_ASKR :
            case MC_AFN_14_ASKE :
            case MC_AFN_15_FILE :
            case MC_AFN_16_DATA:
                ePrm = MC_PRM_A2P;
                break;
          
            default:
                ePrm = MC_PRM_UNKWON;
                break;
        }
    }
    else
    {
        switch ( eAfn )
        {
            case MC_AFN_00_CONF :
            case MC_AFN_01_RSET :
            case MC_AFN_04_SETP :
            case MC_AFN_05_CTRL :
            case MC_AFN_06_AUTH :
            case MC_AFN_08_CASC :
            case MC_AFN_10_GETP :
            case MC_AFN_12_ASKT :
            case MC_AFN_13_ASKR :
            case MC_AFN_14_ASKE :
            case MC_AFN_15_FILE :
            case MC_AFN_16_DATA:
                ePrm = MC_PRM_P2A;
                break;
                
            case MC_AFN_02_LINK :
                ePrm = MC_PRM_A2P;
                break;
          
            default:
                ePrm = MC_PRM_UNKWON;
                break;
        }
    }
   
    return ePrm;
}

/*****************************************************************************
 �� �� ��  : emc_trans_ctrl
 ��������  : �������û������֡�����ݽṹת������
 �������  : eMcTrans eTrans

 �������  : sMctrl* puCtrl
             UINT16* pfCtrl

 �� �� ֵ  : eMcErr
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��10��23�� ������
    ��    ��   : liming
    �޸�����   : �����ɺ���

*****************************************************************************/
eMcErr emc_trans_ctrl(eMcTrans eTrans, sMctrl* puCtrl, UINT16* pfCtrl)
{
    UINT8  ucTmp   = 0;
    UINT16 usfCtrl = 0;

    if(!puCtrl || !pfCtrl)
    {
        #ifdef MC_DBG
        MCDBG("emc_trans_ctrl() para pointer is null!");
        #endif
        return MC_ERR_NULL;
    }

    // �û���ת��Ϊ֡��
    if(MC_TRANS_U2F == eTrans)
    {
        (puCtrl->eDir == MC_DIR_M2S) ? (usfCtrl &= 0x7FFF) : (usfCtrl |= 0x8000);
        (puCtrl->ePRM == MC_PRM_A2P) ? (usfCtrl |= 0x4000) : (usfCtrl &= 0xBF00);

        ucTmp = puCtrl->ucPSEQ;
        if(ucTmp > MC_PSEQ_MAX)
        {
            #ifdef MC_DBG
            MCDBG("emc_trans_ctrl() ucPSEQ is out range! ucPSEQ = %d", ucTmp);
            #endif
            return MC_ERR_OUTRNG;
        }
        else
        {
            usfCtrl |= (ucTmp << 8);
        }

        ucTmp = puCtrl->ucRSEQ;
        if(ucTmp > MC_RSEQ_MAX)
        {
            #ifdef MC_DBG
            MCDBG("emc_trans_ctrl() ucRSEQ is out range! ucRSEQ = %d", ucTmp);
            #endif
            return MC_ERR_OUTRNG;
        }
        else
        {
            usfCtrl |= (ucTmp << 4);
        }

        // Fcode
        ucTmp = (UINT8)(puCtrl->eFcode);

        if(ucTmp > MC_FCD_MAX)
        {
            #ifdef MC_DBG
            MCDBG("emc_trans_ctrl() eFcode is out range! eFcode = %d", ucTmp);
            #endif
            return MC_ERR_OUTRNG;
        }
        else
        {
            usfCtrl |= ucTmp;
        }

        *pfCtrl = usfCtrl;
    }
    // ֡��ת��Ϊ�û���
    else if(MC_TRANS_F2U == eTrans)
    {
        usfCtrl = *pfCtrl;
        puCtrl->eDir   = (usfCtrl & 0x8000) ? MC_DIR_S2M : MC_DIR_M2S;
        puCtrl->ePRM   = (usfCtrl & 0x4000) ? MC_PRM_A2P : MC_PRM_P2A;
        puCtrl->ucPSEQ = (usfCtrl & 0x1F00) >> 8;
        puCtrl->ucRSEQ = (usfCtrl & 0xF0)   >> 4;
        puCtrl->eFcode =  (eMcFcode)(usfCtrl & 0xF);
    }
    else
    {
        #ifdef MC_DBG
        MCDBG("emc_trans_ctrl() para error!");
        #endif
        return MC_ERR_PARA;
    }

    return MC_OK;
}

/*****************************************************************************
 �� �� ��  : emc_get_fcode
 ��������  : ���ĳ�����Ӧ�ķ�װ֡�Ĺ�����
 �������  : eMcmd eCmd
             eMcDir eDir
             eMcPRM ePRM
 �������  : eMcFcode * peFcode

 �� �� ֵ  : eMcFcode
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��10��23�� ������
    ��    ��   : liming
    �޸�����   : �����ɺ���

*****************************************************************************/
eMcErr emc_get_fcode(eMcmd eCmd, eMcDir eDir, eMcPRM ePRM, eMcFcode * peFcode)
{
    eMcErr   eRet   = MC_OK;
    eMcAFN   eAFN   = MC_AFN_NULL;
    eMcFcode eFcode = MC_FCD_MAX;

    if(eDir != MC_DIR_S2M && eDir != MC_DIR_M2S)
    {
        #ifdef MC_DBG
        MCDBG("emc_get_fcode() para eDir is error");
        #endif
        return MC_ERR_PARA;
    }

    if(ePRM != MC_PRM_A2P && ePRM != MC_PRM_P2A)
    {
        #ifdef MC_DBG
        MCDBG("emc_get_fcode() para ePRM is error");
        #endif
        return MC_ERR_PARA;
    }

    switch(eCmd)
    {
        // ��¼
        case MCMD_AFN_2_F1_LOG_IN:
        if(ePRM == MC_PRM_A2P && eDir == MC_DIR_S2M)
        {
            eFcode = MC_FCD_LOG_IN;
        }
        else
        {
            eRet = MC_ERR_LOGIC;
        }
        break;

        // �˳�
        case MCMD_AFN_2_F2_LOG_OUT:
        if(ePRM == MC_PRM_A2P && eDir == MC_DIR_S2M)
        {
            eFcode = MC_FCD_LOG_OUT;
        }
        else
        {
            eRet = MC_ERR_LOGIC;
        }
        break;

        // ����
        case MCMD_AFN_2_F3_HEART_BEAT:
        if(ePRM == MC_PRM_A2P && eDir == MC_DIR_S2M)
        {
            eFcode = MC_FCD_HEART_BEAT;
        }
        else
        {
            eRet = MC_ERR_LOGIC;
        }
        break;

        // ��·������ȷ��
        case MCMD_AFN_2_F4_LINK_OK:
        if(ePRM == MC_PRM_P2A && eDir == MC_DIR_M2S)
        {
            eFcode = MC_FCD_LINK_OK;
        }
        else
        {
            eRet = MC_ERR_LOGIC;
        }
        break;
        
        default:
        eAFN = eMcGetCmdAfn(eCmd);
        if(MC_DIR_M2S == eDir)
        {
            // M2S A2P
            if(MC_PRM_A2P == ePRM)
            {
                switch(eAFN)
                {
                    case MC_AFN_00_CONF:
                    case MC_AFN_01_RSET:
                    case MC_AFN_04_SETP:
                    case MC_AFN_05_CTRL:
                        eFcode = MC_FCD_CONF;
                        break;

                    case MC_AFN_06_AUTH:
                    case MC_AFN_08_CASC:
                    case MC_AFN_10_GETP:
                    case MC_AFN_12_ASKT:
                    case MC_AFN_13_ASKR:
                    case MC_AFN_14_ASKE:
                         eFcode = MC_FCD_ASK;
                         break;

                    case MC_AFN_15_FILE:
                    case MC_AFN_16_DATA:
                         eFcode = MC_FCD_NOTI;
                         break;

                    default:
                         eRet = MC_ERR_LOGIC;
                         break;
                }
            }
            // M2S P2A
            else
            {
                switch(eAFN)
                {
                    case MC_AFN_00_CONF:
                    case MC_AFN_01_RSET:
                    case MC_AFN_04_SETP:
                    case MC_AFN_05_CTRL:
                         eFcode = MC_FCD_CONF;
                         break;

                    case MC_AFN_06_AUTH:
                    case MC_AFN_08_CASC:
                    case MC_AFN_10_GETP:
                    case MC_AFN_12_ASKT:
                    case MC_AFN_13_ASKR:
                    case MC_AFN_14_ASKE:
                         eFcode = MC_FCD_ASK;
                         break;

                    case MC_AFN_15_FILE:
                    case MC_AFN_16_DATA:
                         eFcode = MC_FCD_NOTI;
                         break;
                        
                    default:
                         eRet = MC_ERR_LOGIC;
                         break;
                }
            }
        }
        else
        {
            // S2M A2P
            if(MC_PRM_A2P == ePRM)
            {
                switch(eAFN)
                {
                    case MC_AFN_00_CONF:
                    case MC_AFN_01_RSET:
                    case MC_AFN_04_SETP:
                    case MC_AFN_05_CTRL:
                        eFcode = MC_FCD_CONF;
                        break;

                    case MC_AFN_06_AUTH:
                    case MC_AFN_08_CASC:
                    case MC_AFN_10_GETP:
                    case MC_AFN_12_ASKT:
                    case MC_AFN_13_ASKR:
                    case MC_AFN_14_ASKE:
                        eFcode = MC_FCD_ASK;
                        break;

                    case MC_AFN_15_FILE:
                    case MC_AFN_16_DATA:
                        eFcode = MC_FCD_NOTI;
                        break;

                    default:
                        eRet = MC_ERR_LOGIC;
                        break;
                }
            }
            // S2M P2A
            else
            {
                switch(eAFN)
                {
                    //case MC_AFN_01_RSET:
                    //case MC_AFN_04_SETP:
                    //case MC_AFN_05_CTRL:
                    
                    case MC_AFN_00_CONF:
                         eFcode = MC_FCD_OK;
                         break;

                    case MC_AFN_06_AUTH:
                    case MC_AFN_08_CASC:
                    case MC_AFN_10_GETP:
                    case MC_AFN_12_ASKT:
                    case MC_AFN_13_ASKR:
                    case MC_AFN_14_ASKE:
                         eFcode = MC_FCD_ASK;
                         break;

                    case MC_AFN_15_FILE:
                    case MC_AFN_16_DATA:
                         eFcode = MC_FCD_NOTI;
                         break;
                    
                    default:
                         eRet = MC_ERR_LOGIC;
                         break;
                }
            }
        }

        break;
    }

    // �������
    *peFcode = eFcode;
    return eRet;
}

/*****************************************************************************
 �� �� ��  : emc_get_ctrl
 ��������  : ��÷�װ֡���û������������
 �������  : eMcTrans eTrans

 �������  : sMcAc* psAc
             UINT8* pucAc

 �� �� ֵ  : eMcErr
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��10��23�� ������
    ��    ��   : liming
    �޸�����   : �����ɺ���

*****************************************************************************/
eMcErr emc_get_ctrl(eMcAFN eAFN, eMcDir eDir, eMcPRM ePRM, sMctrl *psCtrl)
{
    if(!psCtrl)
    {
        #ifdef MC_DBG
        MCDBG("emc_get_ctrl() para pointer is null");
        #endif
        return MC_ERR_NULL;
    }

    if(MC_DIR_M2S != eDir && MC_DIR_S2M != eDir)
    {
        #ifdef MC_DBG
        MCDBG("emc_get_ctrl() eDir para error");
        #endif
        return MC_ERR_PARA;
    }

    if(MC_PRM_A2P != ePRM && MC_PRM_P2A != ePRM)
    {
        #ifdef MC_DBG
        MCDBG("emc_get_ctrl() ePRM para error");
        #endif
        return MC_ERR_PARA;
    }

    psCtrl->eDir   = eDir;
    psCtrl->ePRM   = ePRM;
    //psCtrl->ucPSEQ =

    return MC_OK;
}

/*****************************************************************************
 �� �� ��  : emc_trans_ac
 ��������  : Ӧ�ÿ�����AC �û������֡�����ݽṹת������
 �������  : eMcTrans eTrans

 �������  : sMcAc* psAc
             UINT8* pucAc

 �� �� ֵ  : eMcErr
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��10��23�� ������
    ��    ��   : liming
    �޸�����   : �����ɺ���

*****************************************************************************/
eMcErr emc_trans_ac(eMcTrans eTrans, sMcAc* puAc, UINT8* pfAc)
{
    UINT8 ucTmp = 0;
    UINT8 ucfAc = 0;

    if(!puAc || !pfAc)
    {
        #ifdef MC_DBG
        MCDBG("emc_trans_ac() para pointer is null!");
        #endif
        return MC_ERR_NULL;
    }

    // �û���ת��Ϊ֡��
    if(MC_TRANS_U2F == eTrans)
    {
        // tp
        if(TRUE == puAc->bTp)
        {
            ucfAc |= 0x80;
        }

        // ec
        if(TRUE == puAc->bEc)
        {
            ucfAc |= 0x40;
        }

        // afn
        switch(puAc->eAfn)
        {
            case MC_AFN_00_CONF:
            case MC_AFN_01_RSET:
            case MC_AFN_04_SETP:
            case MC_AFN_05_CTRL:
            case MC_AFN_06_AUTH:
            case MC_AFN_08_CASC:
            case MC_AFN_10_GETP:
            case MC_AFN_12_ASKT:
            case MC_AFN_13_ASKR:
            case MC_AFN_14_ASKE:
            case MC_AFN_15_FILE:
            case MC_AFN_16_DATA:

                 ucfAc |= (UINT8)(puAc->eAfn);
                 break;

            default:
                #ifdef MC_DBG
                MCDBG("emc_trans_ac() eFcode is out range! eFcode = %d", puAc->eAfn);
                #endif
                return MC_ERR_OUTRNG;
            //break;
        }

        // �������
        *pfAc = ucfAc;

    }
    // ֡��ת��Ϊ�û���
    else if(MC_TRANS_F2U == eTrans)
    {
        ucfAc = *pfAc;

        // tp
        puAc->bTp = (ucfAc & 0x80) ? TRUE : FALSE;

        // ec
        puAc->bEc = (ucfAc & 0x40) ? TRUE : FALSE;

        // afn
        ucTmp = ucfAc & 0xF;
        switch(ucTmp)
        {
            case MC_AFN_00_CONF:
            case MC_AFN_01_RSET:
            case MC_AFN_04_SETP:
            case MC_AFN_05_CTRL:
            case MC_AFN_06_AUTH:
            case MC_AFN_08_CASC:
            case MC_AFN_10_GETP:
            case MC_AFN_12_ASKT:
            case MC_AFN_13_ASKR:
            case MC_AFN_14_ASKE:
            case MC_AFN_15_FILE:
            case MC_AFN_16_DATA:

                 puAc->eAfn = (eMcAFN)ucTmp;
                 break;

            default:
                #ifdef MC_DBG
                MCDBG("emc_trans_ac() eFcode is out range! eFcode = %d", ucTmp);
                #endif
                return MC_ERR_OUTRNG;
            //break;
        }
    }
    else
    {
        #ifdef MC_DBG
        MCDBG("emc_trans_ac() para error!");
        #endif
        return MC_ERR_PARA;
    }

    return MC_OK;
}

/*****************************************************************************
 �� �� ��  : ucMcGetCmdFn
 ��������  : ��������FN
 �������  : eMcmd eCmd
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��8��8�� ������
    ��    ��   : liming
    �޸�����   : �����ɺ���

*****************************************************************************/
UINT8  ucMcGetCmdFn(eMcmd eCmd)
{
    UINT8 ucFn;
    ucFn = (UINT8)(eCmd & 0xFF);
    return ucFn;
}

/*****************************************************************************
 �� �� ��  : eMcGetCmdAfn
 ��������  : ͨ�������ֻ�ȡ�����Ӧ��AFN
 �������  : eMcmd eCmd
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��5��21�� ���ڶ�
    ��    ��   : liming
    �޸�����   : �����ɺ���

*****************************************************************************/
eMcAFN eMcGetCmdAfn(eMcmd eCmd)
{
    eMcAFN eAfn;
    UINT32 ulCmd = 0;
    UINT8  ucAfn = 0;
    ulCmd = (UINT32)eCmd;
    ucAfn = (UINT8)((ulCmd & 0x0000FF00) >> 8);
    eAfn  = (eMcAFN)ucAfn;

    switch(eAfn)
    {
        case MC_AFN_00_CONF:
        case MC_AFN_01_RSET:
        case MC_AFN_04_SETP:
        case MC_AFN_05_CTRL:
        case MC_AFN_06_AUTH:
        case MC_AFN_08_CASC:
        case MC_AFN_10_GETP:
        case MC_AFN_12_ASKT:
        case MC_AFN_13_ASKR:
        case MC_AFN_14_ASKE:
        case MC_AFN_15_FILE:
        case MC_AFN_16_DATA:
            break;

        default:
            eAfn = MC_AFN_NULL;
            break;
    }

    return eAfn;
}

/*****************************************************************************
 �� �� ��  : bmc_same_team_pn
 ��������  : �ж�һ����8��Ԫ�ص�Pn����,���8��Pn�Ƿ�����ͬһ����Ϣ����
             ������ЧPn
             �������ͬһ��,�����ȡ��
 �������  : UINT16 *pUsPn8
 �������  : ��
 �� �� ֵ  : ��ͬһ�鷵����
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��8��6�� ���ڶ�
    ��    ��   : liming
    �޸�����   : �����ɺ���

*****************************************************************************/
BOOL bmc_same_team_pn(UINT16 *pUsPn8, UINT8* pucDa2)
{
    if(!pUsPn8)
    {
        return FALSE;
    }

    UINT16 usPn[8]   = {0};
    UINT8  ucTeam[8] = {0}; // ÿ��Pn��Ӧ����Ϣ����
    INT32  nPnNum    = 0;   // ��ЧPn�ĸ���
    INT32  i         = 0;
    BOOL   bP0       = FALSE;

    // �ж��Ƿ���P0
    bP0 = bmc_is_p0(pUsPn8);
    if(TRUE == bP0)
    {
        if(pucDa2 != NULL)
        {
           *pucDa2 = 0;
        }

        return TRUE;
    }

    for(i = 0; i < 8; i++)
    {
        if(MC_PN_NONE == pUsPn8[i])
        {
            // �Ϸ�,������Ч��ֵ
        }
        else if(pUsPn8[i] < MC_PN_MIN || pUsPn8[i] > MC_PN_MAX)
        {
            #ifdef MC_DBG
            MCDBG("bmc_same_team_pn() Pn para err!");
            #endif
            return FALSE;
        }
        // ����һ��Ϊ0���������
        else if(0 == pUsPn8[i])
        {
            return FALSE;
        }
        else
        {
            usPn[nPnNum++] = pUsPn8[i];
        }
    }

    if(0 == nPnNum)
    {
        // ������Ч��ֵ,�������û������, Ҳһ��Ϊ����һ��
        return FALSE;
    }
    else if(1 == nPnNum)
    {
        // *pucTeam = (usPN[0] - 1) / 8  + 1;
        // return TRUE;
    }
    else
    {
        for(i = 0; i < nPnNum; i++)
        {
            ucTeam[i] = (usPn[i] - 1) / 8  + 1;
        }

        for(i = 1; i < nPnNum; i++)
        {
            if(ucTeam[i] != ucTeam[0])
            {
                return FALSE;
            }
        }
    }

    if(pucDa2 != NULL)
    {
       *pucDa2 = (usPn[0] - 1) / 8  + 1;
    }

    return TRUE;
}

/*****************************************************************************
 �� �� ��  : bmc_is_p0
 ��������  : �ж�һ��Pn�Ƿ�Ϊ0, ��P0
 �������  : UINT16 *pUsPn8
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��8��6�� ���ڶ�
    ��    ��   : liming
    �޸�����   : �����ɺ���

*****************************************************************************/
BOOL bmc_is_p0(UINT16 *pUsPn8)
{
    if(!pUsPn8)
    {
        return FALSE;
    }

    INT32 i = 0;
    for(i = 0; i < MC_PN_INDEX_MAX; i++)
    {
        if(pUsPn8[i] != 0)
        {
            return FALSE;
        }
    }

    return TRUE;
}

/*****************************************************************************
 �� �� ��  : ucmc_get_pn_team
 ��������  : ���1��Pn��Ӧ����Ϣ�����
 �������  : UINT16 usPn  
 �������  : ��
 �� �� ֵ  : 
 ���ú���  : 
 ��������  : 
 
 �޸���ʷ      :
  1.��    ��   : 2013��8��9�� ������
    ��    ��   : liming
    �޸�����   : �����ɺ���

*****************************************************************************/
UINT8 ucmc_get_pn_team(UINT16 usPn)
{
    UINT8 ucTeam;

    if(0 == usPn)
    {
        return 0;
    }

    ucTeam = (usPn - 1)/8 + 1;
    return ucTeam;
}

/*****************************************************************************
 �� �� ��  : ucmc_get_pn8_team
 ��������  : ���8��Pn��Ӧ����Ϣ�����
 �������  : UINT16 *pusPn
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��8��9�� ������
    ��    ��   : liming
    �޸�����   : �����ɺ���

*****************************************************************************/
UINT8 ucmc_get_pn8_team(UINT16 *pusPn)
{
    if(!pusPn)
    {
        return 0xFF;
    }

    BOOL bP0;
    bP0 = bmc_is_p0(pusPn);
    if(TRUE == bP0)
    {
        return 0;
    }

    int i = 0;
    UINT8 ucTeam;
    for(i = 0; i < 8; i++)
    {
        if(pusPn[i] != MC_PN_NONE)
        {
           ucTeam  = ucmc_get_pn_team(pusPn[i]);
           return ucTeam;
        }
    }

    return 0xFF;
}

/*****************************************************************************
 �� �� ��  : bmc_in_pn8
 ��������  : �ж�ĳһ��pn�Ƿ���һ��8��pn��
 �������  : UINT16 usPn
             UINT16 *pusPn8
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��9��17�� ���ڶ�
    ��    ��   : liming
    �޸�����   : �����ɺ���

*****************************************************************************/
BOOL bmc_in_pn8(UINT16 usPn, UINT16 *pusPn8)
{
    if((!pusPn8) || (usPn > MC_PN_MAX))
    {
        return FALSE;
    }

    INT32 i = 0;

    for(i = 0; i < 8; i++)
    {
        if(usPn == pusPn8[i])
        {
            return TRUE;
        }
    }

    return FALSE;
}

/*****************************************************************************
 �� �� ��  : bmc_same_team_fn
 ��������  : �ж�һ����8��Ԫ�ص�Fn����,���8��Fn�Ƿ�����ͬһ����Ϣ����
             ������ЧFn
             �������ͬһ��,�����ȡ��
 �������  : UINT16 *pUcFn8
 �������  : ��
 �� �� ֵ  : ��ͬһ�鷵����
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��8��6�� ���ڶ�
    ��    ��   : liming
    �޸�����   : �����ɺ���

*****************************************************************************/
BOOL bmc_same_team_fn(UINT8  *pUcFn8, UINT8* pucDt2)
{
    if(!pUcFn8)
    {
        return FALSE;
    }

    UINT8  ucFn[8]   = {0};
    UINT8  ucTeam[8] = {0}; // ÿ��Pn��Ӧ����Ϣ����
    INT32  nFnNum    = 0;   // ��ЧPn�ĸ���
    INT32  i         = 0;

    #if 0
    #ifdef MC_DBG
    MCDBG("[in]bmc_same_team_fn()");
    for(i = 0; i < 8; i++)
    {
        printf("fn[%d] = %d\n", i, (UINT8)pUcFn8[i]);
    }
    #endif
    #endif

    for(i = 0; i < 8; i++)
    {
        if(MC_FN_NONE == pUcFn8[i])
        {
            // �Ϸ�,������Ч��ֵ
        }
        else if(pUcFn8[i] < MC_FN_MIN || pUcFn8[i] > MC_FN_MAX)
        {
            #ifdef MC_DBG
            MCDBG("bmc_same_team_fn() Fn para err!");
            #endif
            return FALSE;
        }
        else
        {
            ucFn[nFnNum++] = pUcFn8[i];
        }
    }

    if(0 == nFnNum)
    {
        // ������Ч��ֵ,�������û������,Ҳ��Ϊ����һ��
        return FALSE;
    }
    else if(1 == nFnNum)
    {
        //*pucTeam = (usPN[0] - 1) / 8  + 1;
        //return TRUE;
    }
    else
    {
        for(i = 0; i < nFnNum; i++)
        {
            ucTeam[i] = (ucFn[i] - 1) / 8 ;
        }

        for(i = 1; i < nFnNum; i++)
        {
            if(ucTeam[i] != ucTeam[0])
            {
                return FALSE;
            }
        }
    }

    if(pucDt2 != NULL)
    {
        *pucDt2 = (ucFn[0] - 1) / 8;
    }

    return TRUE;
}

/*****************************************************************************
 �� �� ��  : ucmc_get_fn_team
 ��������  : ���һ��fn��Ӧ����Ϣ����
 �������  : UINT8 ucFn
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��8��9�� ������
    ��    ��   : liming
    �޸�����   : �����ɺ���

*****************************************************************************/
UINT8 ucmc_get_fn_team(UINT8 ucFn)
{
    UINT8 ucTeam = 0;

    // �ж��Ƿ��ǺϷ���Fn
    if(ucFn == MC_FN_NONE)
    {
        ucTeam = 0xFF;
    }
    else
    {
        if(ucFn > MC_FN_MAX || ucFn < MC_FN_MIN)
        {
            ucTeam = 0xFF;
            #ifdef MC_DBG
            MCDBG("ucmc_get_fn_team() Fn para err!");
            #endif
        }
        else
        {
            ucTeam = (ucFn - 1)/8 ;
        }
    }

    return ucTeam;
}

/*****************************************************************************
 �� �� ��  : ucmc_get_fn_bit
 ��������  : ���һ��Fn��Ӧĳ��Ϣ�����е�bitֵ
 �������  : UINT8 ucFn
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��9��12�� ������
    ��    ��   : liming
    �޸�����   : �����ɺ���

*****************************************************************************/
UINT8 ucmc_get_fn_bit(UINT8 ucFn)
{
    UINT8 ucBit = 0;

    // �ж��Ƿ��ǺϷ���Fn
    if(ucFn == MC_FN_NONE)
    {
        ucBit = 0xFF;
    }
    else
    {
        if(ucFn > MC_FN_MAX || ucFn < MC_FN_MIN)
        {
            ucBit = 0xFF;
            #ifdef MC_DBG
            MCDBG("ucmc_get_fn_bit() Fn para err ucFn = %d!", ucFn);
            #endif
        }
        else
        {
            ucBit = (0x01 << ((ucFn - 1) % 8));
        }
    }

    return ucBit;
}

/*****************************************************************************
 �� �� ��  : ucmc_get_fn8_team
 ��������  : ���8��fn��Ӧ����Ϣ����
 �������  : UINT8 *pucFn
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��8��9�� ������
    ��    ��   : liming
    �޸�����   : �����ɺ���

*****************************************************************************/
UINT8 ucmc_get_fn8_team(UINT8 *pucFn)
{
    if(!pucFn)
    {
        return 0xFF;
    }

    int i = 0;
    UINT8 ucTeam = 0xFF;

    for(i = 0 ;i < 8; i++)
    {
        if(pucFn[i] != MC_FN_NONE)
        {
            ucTeam = ucmc_get_fn_team(pucFn[i]);
            break;
        }
    }

    return ucTeam;
}

/*****************************************************************************
 �� �� ��  : bmc_in_fn8
 ��������  : �ж�ĳһ��fn�Ƿ���һ��8��fn��
 �������  : UINT8 ucFn
             UINT8 *pucFn8
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��9��17�� ���ڶ�
    ��    ��   : liming
    �޸�����   : �����ɺ���

*****************************************************************************/
BOOL bmc_in_fn8(UINT8 ucFn, UINT8 *pucFn8)
{
    if((ucFn < MC_FN_MIN) || (!pucFn8) || (ucFn > MC_FN_MAX))
    {
        return FALSE;
    }

    INT32 i = 0;

    for(i = 0; i < 8; i++)
    {
        if(ucFn == pucFn8[i])
        {
            return TRUE;
        }
    }

    return FALSE;
}

/*****************************************************************************
 �� �� ��  : emc_pnfn_to_dadt
 ��������  : ���ݵ�Ԫ��ʶת������
 �������  : sMcPnFn* psPnFn
             sMcDaDt* psDaDt
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��7��30�� ���ڶ�
    ��    ��   : liming
    �޸�����   : �����ɺ���

*****************************************************************************/
eMcErr emc_pnfn_to_dadt(sMcPnFn* psPnFn, sMcDaDt* psDaDt)
{
    INT32  i           = 0;
    UINT8  ucDa1       = 0;
    UINT8  ucDa2       = 0;
    UINT8  ucDt1       = 0;
    UINT8  ucDt2       = 0;
    const UINT8 ucMask = 0x01;
    UINT8  ucShit      = 0;  // λ�Ƹ���
    BOOL   bSameTeam   = FALSE;
    BOOL   bPn0        = FALSE;

    // �������
    if(!psPnFn || !psDaDt)
    {
        #ifdef MC_DBG
        MCDBG("emc_pnfn_to_dadt() para pointer is null !");
        #endif
        return MC_ERR_NULL;
    }

    // �ж�Pn �Ƿ���ͬһ����
    bSameTeam = bmc_same_team_pn(psPnFn->usPn, &ucDa2);
    if(FALSE == bSameTeam)
    {
        #ifdef MC_DBG
        MCDBG("emc_pnfn_to_dadt() Pn is not in a same team!");
        #endif
        return MC_ERR_TEAM;
    }

    // �ж�Fn �Ƿ���ͬһ����
    bSameTeam = bmc_same_team_fn(psPnFn->ucFn, &ucDt2);
    if(FALSE == bSameTeam)
    {
        #ifdef MC_DBG
        MCDBG("emc_pnfn_to_dadt() Fn is not in a same team!");
        #endif
        return MC_ERR_TEAM;
    }

    // ��װ Da1
    bPn0 = bmc_is_p0(psPnFn->usPn);
    if(TRUE == bPn0)
    {
         ucDa1 = 0;
    }
    else
    {
        for(i = 0; i < MC_PN_INDEX_MAX; i++)
        {
            if(MC_PN_NONE != psPnFn->usPn[i])
            {
                ucShit = (psPnFn->usPn[i] - 1) % 8;
                ucDa1 |= (ucMask << ucShit);
            }
        }
    }

    // ��װDt1
    for(i = 0; i < MC_FN_INDEX_MAX; i++)
    {
        if(MC_FN_NONE != psPnFn->ucFn[i])
        {
            ucShit = (psPnFn->ucFn[i] - 1) % 8;
            ucDt1 |= (ucMask << ucShit);
        }
    }

    // ���Ϸ���fn pn ��װ�� DaDt
    psDaDt->ucDA1 = ucDa1;
    psDaDt->ucDA2 = ucDa2;
    psDaDt->ucDT1 = ucDt1;
    psDaDt->ucDT2 = ucDt2;

    return MC_OK;
}

/*****************************************************************************
 �� �� ��  : emc_dadt_to_pnfn
 ��������  : ���ݱ�ʶ��Ԫת������
 �������  : sMcDaDt* psDaDt
             sMcPnFn* psPnFn
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��7��30�� ���ڶ�
    ��    ��   : liming
    �޸�����   : �����ɺ���

*****************************************************************************/
eMcErr emc_dadt_to_pnfn(sMcDaDt* psDaDt, sMcPnFn* psPnFn)
{
    INT32  i      = 0;
    UINT16 usPn   = 0;
    UINT8  ucFn   = 0;
    UINT8  ucMask = 0x01;
    UINT8  ucTmp  = 0;

    if(!psPnFn || !psDaDt)
    {
        #ifdef MC_DBG
        MCDBG("emc_dadt_to_pnfn() para pointer is null!");
        #endif
        return MC_ERR_NULL;
    }

    #if 0
    #ifdef MC_DBG
    MCDBG("[in]emc_dadt_to_pnfn()");
    MCDBG("ucDA1 = 0x%X", psDaDt->ucDA1);
    MCDBG("ucDA2 = 0x%X", psDaDt->ucDA2);
    MCDBG("ucDT1 = 0x%X", psDaDt->ucDT1);
    MCDBG("ucDT2 = 0x%X", psDaDt->ucDT2);
    #endif
    #endif

    // ��������ʼ��
    memset(psPnFn, 0x00, sizeof(sMcPnFn));

    // Fn
    if(psDaDt->ucDT2 > 30)
    {
        #ifdef MC_DBG
        MCDBG("emc_dadt_to_pnfn() para out of range! ucDT2 = %d", psDaDt->ucDT2);
        #endif
        return MC_ERR_OUTRNG;
    }
    else
    {
        for(i = 0; i < 8; i++)
        {
            ucTmp = ucMask << i;
            if(psDaDt->ucDT1 & ucTmp)
            {
                ucFn = ((psDaDt->ucDT2) * 8) + i + 1;
            }
            else
            {
                ucFn = MC_FN_NONE;
            }

            psPnFn->ucFn[i] = ucFn;
        }
    }

    // P0
    if(0 == psDaDt->ucDA2)
    {
        if(0 == psDaDt->ucDA1)
        {
            for(i = 0; i < 8; i++)
            {
               psPnFn->usPn[i] = 0;
            }
        }
        else
        {
           #ifdef MC_DBG
           MCDBG("emc_dadt_to_pnfn() para err!");
           #endif
           return MC_ERR_PARA;
        }
    }
    // Pn
    else
    {
        for(i = 0; i < 8; i++)
        {
            ucTmp = ucMask << i;
            if(psDaDt->ucDA1 & ucTmp)
            {
                usPn = (psDaDt->ucDA2-1) * 8 + i + 1;
            }
            else
            {
                usPn = MC_PN_NONE;
            }

            psPnFn->usPn[i] = usPn;
        }
    }

    #if 0
    #ifdef MC_DBG
    MCDBG("[out]emc_dadt_to_pnfn()");
    BOOL bP0 = bmt_is_p0(psPnFn->usPn);
    if(bP0 == TRUE)
    {
         MCDBG("usPn = 0");
    }
    else
    {
        for(i = 0; i < 8; i++)
        {
            if(psPnFn->usPn[i] == MC_PN_NONE)
            {
               MCDBG("Pn[%d] = NONE", i+1);
            }
            else
            {
               MCDBG("Pn[%d] = %d", i+1, psPnFn->usPn[i]);
            }
        }
    }

    for(i = 0; i < 8; i++)
    {
        if(psPnFn->ucFn[i] == MC_FN_NONE)
        {
            MCDBG("Fn[%d] = NONE", i+1);
        }
        else
        {
            MCDBG("Fn[%d] = %d", i+1, psPnFn->ucFn[i]);
        }
    }
    #endif
    #endif

    return MC_OK;
}

/*****************************************************************************
 �� �� ��  : emc_add_cmdpn
 ��������  : ����*pucNumCmdPn��sMcmdPn�������һ���µ�
             ����Ѿ�����һ��ͬ����������PN��,�����
             ������Ӻ����,����������
 �������  : sMcmdPn* psCmdPn
             UINT8 *pucNumCmdPn
             sMcmdPn sNewCmdPn
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��9��13�� ������
    ��    ��   : liming
    �޸�����   : �����ɺ���

*****************************************************************************/
eMcErr emc_add_cmdpn(sMcmdPn* psCmdPn,sMcmdPn sNewCmdPn, UINT8 *pucNumCmdPn)
{
    if(!psCmdPn || !pucNumCmdPn)
    {
        #ifdef MC_DBG
        MCDBG("emc_add_cmdpn() para pointer is null!");
        #endif
        return MC_ERR_NULL;
    }

    INT32 i   = 0;
    UINT8 ucN = 0;
    ucN = *pucNumCmdPn;

    for(i = 0; i < ucN; i++)
    {
        if(sNewCmdPn.eCmd == psCmdPn[i].eCmd)
        {
            if(sNewCmdPn.usPn == psCmdPn[i].usPn)
            {
                return MC_OK;
            }
        }
    }

    // û���ҵ�ͬ���������һ���µĽ�����
    psCmdPn[ucN].eCmd = sNewCmdPn.eCmd;
    psCmdPn[ucN].usPn = sNewCmdPn.usPn;

    *pucNumCmdPn = ucN + 1;
    return MC_OK;
}

/*****************************************************************************
 �� �� ��  : emc_pnfn_to_cmdpn
 ��������  : ʵ��ucNumPnFn ��sMcPnFn�ṹ���� �� sMcmdPn �ṹ���ݵ�ת��
             �����ת�����������
 �������  : eMcAFN eAfn
             sMcPnFn* psPnFn
             UINT8 ucNumPnFn

 �������  : sMcmdPn* psCmdPn
             UINT8 *pucNumCmdPn
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��9��13�� ������
    ��    ��   : liming
    �޸�����   : �����ɺ���

*****************************************************************************/
eMcErr emc_pnfn_to_cmdpn(eMcAFN eAfn, sMcPnFn* psPnFn, UINT8 ucNumPnFn,   sMcmdPn* psCmdPn, UINT8 *pucNumCmdPn)
{
    if(!psPnFn || !psCmdPn || !pucNumCmdPn)
    {
        #ifdef MC_DBG
        MCDBG("emc_pnfn_to_cmdpn() para pointer is null!");
        #endif
        return MC_ERR_NULL;
    }

    UINT8   ucFn  = 0;
    UINT8   ucAFN = 0;
    UINT16  usCmd = 0;
    INT32   i     = 0;
    INT32   j     = 0;
    INT32   k     = 0;
    eMcmd   eCmd  = MCMD_AFN_F_UNKOWN;
    eMcErr  eRet  = MC_OK;
    sMcDaDt sDaDt;
    sMcmdPn sNew;

    switch(eAfn)
    {
        case MC_AFN_00_CONF:
        case MC_AFN_01_RSET:
        case MC_AFN_04_SETP:
        case MC_AFN_05_CTRL:
        case MC_AFN_06_AUTH:
        case MC_AFN_08_CASC:
        case MC_AFN_10_GETP:
        case MC_AFN_12_ASKT:
        case MC_AFN_13_ASKR:
        case MC_AFN_14_ASKE:
        case MC_AFN_15_FILE:
        case MC_AFN_16_DATA:

            ucAFN = (UINT8)eAfn;
            break;

        default:
            #ifdef MC_DBG
            MCDBG("emc_pnfn_to_cmdpn() para err!");
            #endif
            return MC_ERR_PARA;
            //break;

    }

    for(i = 0; i < ucNumPnFn; i++)
    {
        eRet = emc_pnfn_to_dadt(&(psPnFn[i]), &sDaDt);
        if(MC_OK != eRet)
        {
            #ifdef MC_DBG
            MCDBG("emc_pnfn_to_cmdpn() emc_pnfn_to_dadt  err %d", eRet);
            #endif
            return eRet;
        }

        // p0�����
        if(0 == sDaDt.ucDA1 && 0 == sDaDt.ucDA2)
        {
            sNew.usPn = 0;

            for(j = 0; j < 8; j++)
            {
                if(sDaDt.ucDT1 & (0x01 << j))
                {
                    ucFn  = (sDaDt.ucDT2 * 8) + j + 1;
                    usCmd = (UINT16)(ucAFN << 8 | ucFn);
                    eCmd  = (eMcmd)usCmd;
                    sNew.eCmd = eCmd;
                    (void)emc_add_cmdpn(psCmdPn ,sNew,pucNumCmdPn);
                }
            }
        }
        else
        {
            for(k = 0; k < 8; k++)
            {
                if(sDaDt.ucDA1 & (0x01 << k))
                {
                    sNew.usPn = ((sDaDt.ucDA2-1) * 8 + k + 1);
                    for(j = 0; j < 8; j++)
                    {
                        if(sDaDt.ucDT1 & (0x01 << j))
                        {
                            ucFn  = (sDaDt.ucDT2 * 8) + j + 1;
                            usCmd = (UINT16)(ucAFN << 8 | ucFn);
                            eCmd  = (eMcmd)usCmd;
                            sNew.eCmd = eCmd;
                            (void)emc_add_cmdpn(psCmdPn ,sNew,pucNumCmdPn);
                        }
                    }
                }
            }
        }
    }

    return MC_OK;
}

/*****************************************************************************
 �� �� ��  : emc_cmdpn_to_pnfn
 ��������  : ʵ�ֽ�ucNumCmdPn��sMcmdPn���� ת����sMcPnFn����
             �����ת����ĸ���pucNumPnFn
 �������  : eMcAFN eAfn
             sMcPnFn* psPnFn
             UINT8 *pucNumPnFn
             sMcmdPn* psCmdPn
             UINT8  ucNumCmdPn
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��9��13�� ������
    ��    ��   : liming
    �޸�����   : �����ɺ���

*****************************************************************************/
eMcErr emc_cmdpn_to_pnfn(eMcAFN eAfn, sMcPnFn* psPnFn, UINT8 *pucNumPnFn, sMcmdPn* psCmdPn, UINT8  ucNumCmdPn)
{
    UINT8   ucTeamPn     = 0xFF;
    UINT8   ucTeamPnBase = 0xFF;
    UINT8   ucTeamFn     = 0xFF;
    UINT8   ucTeamFnBase = 0xFF;
    UINT8   ucFn         = 0;
    UINT8   ucNumPnFn    = 0;
    UINT16  usPn         = 0;
    INT32   i            = 0;
    INT32   j            = 0;
    INT32   k            = 0;
    INT32   FnIndex      = 0;
    INT32   PnIndex      = 0;
    INT32   nPos         = 0;
    BOOL    bFind        = FALSE;
    BOOL    bInFn8       = FALSE;
    eMcmd   eCmd         = MCMD_AFN_F_UNKOWN;
    eMcAFN  eCmdAfn      = MC_AFN_NULL;

    if(!psPnFn || !psCmdPn || !pucNumPnFn)
    {
        #ifdef MC_DBG
        MCDBG("pucNumPnFn() para pointer is null!");
        #endif
        return MC_ERR_NULL;
    }
    
    for(i = 0; i < ucNumCmdPn; i++)
    {
        eCmd    = psCmdPn[i].eCmd;
        usPn    = psCmdPn[i].usPn;
        ucFn    = ucMcGetCmdFn(eCmd);
        eCmdAfn = eMcGetCmdAfn(eCmd);

        if(eCmdAfn != eAfn)
        {
            #ifdef MC_DBG
            MCDBG("emc_cmdpn_to_pnfn() cmd is not is a same Afn eCmdAfn = %d  eAfn = %d",eCmdAfn, eAfn);
            #endif
            return MC_ERR_TEAM;
        }

        nPos = ucNumPnFn;

        // ��ʼ��PnFn��
        for(k = 0; k < 8; k++)
        {
            psPnFn[nPos].ucFn[k] = MC_FN_NONE;
            psPnFn[nPos].usPn[k] = MC_PN_NONE;
        }

        for(j = 0; j < ucNumPnFn; j++)
        {
            // �ҵ���nDataPos���ҵ���λ��
            // ���ж�Pn�Ƿ���ͬһ��
            ucTeamPn     = ucmc_get_pn_team(usPn);
            ucTeamPnBase = ucmc_get_pn8_team(psPnFn[j].usPn);

            if(ucTeamPn == ucTeamPnBase)
            {
                // ���ж�Fn�Ƿ�����ͬһ����
                ucTeamFn     = ucmc_get_fn_team(ucFn);
                ucTeamFnBase = ucmc_get_fn8_team(psPnFn[j].ucFn);

                if(ucTeamFn == ucTeamFnBase)
                {
                    bInFn8 = bmc_in_fn8(ucFn, psPnFn[j].ucFn);
                    if(TRUE == bInFn8)
                    {
                         bFind = TRUE;
                         nPos  = j;
                         break;
                    }
                }
            }
        }

         // δ�ҵ�������һ��
        if(FALSE == bFind)
        {
            ucNumPnFn  += 1;
        }

        if(0 == usPn)
        {
            PnIndex = 0;

            for(k = 0; k < 8; k++)
            {
                psPnFn[nPos].usPn[k] = 0;
            }
        }
        else
        {
            PnIndex = (usPn - 1) % 8;
            psPnFn[nPos].usPn[PnIndex] =  usPn;
        }

        FnIndex = (ucFn - 1) % 8;
        psPnFn[nPos].ucFn[FnIndex] = ucFn;

        // ����δ�ҵ�״̬
        bFind = FALSE;
    }

    *pucNumPnFn = ucNumPnFn;
    return MC_OK;
}

/*****************************************************************************
 �� �� ��  : emc_dadt_to_cmdpn
 ��������  : ʵ��ucNumDaDt ��sMcDaDt�ṹ���� �� sMcmdPn �ṹ���ݵ�ת��
             �����ת����ĸ���
 �������  : eMcAFN eAfn
             sMcDaDt* psDaDt
             UINT8 ucNumDaDt
             sMcmdPn* psCmdPn
             UINT8 *pucNumCmdPn
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��9��13�� ������
    ��    ��   : liming
    �޸�����   : �����ɺ���

*****************************************************************************/
eMcErr emc_dadt_to_cmdpn(eMcAFN eAfn, sMcDaDt* psDaDt, UINT8 ucNumDaDt, sMcmdPn* psCmdPn, UINT8 *pucNumCmdPn)
{
    UINT8   ucFn  = 0;
    UINT8   ucAFN = 0;
    UINT16  usCmd = 0;
    INT32   i     = 0;
    INT32   j     = 0;
    INT32   k     = 0;
    eMcmd  eCmd  = MCMD_AFN_F_UNKOWN;
    sMcDaDt sDaDt;
    sMcmdPn sNew;

    if(!psDaDt || !psCmdPn || !pucNumCmdPn)
    {
        #ifdef MC_DBG
        MCDBG("emc_dadt_to_cmdpn() para pointer is null!");
        #endif
        return MC_ERR_NULL;
    }
    
    switch(eAfn)
    {
        case MC_AFN_00_CONF:
        case MC_AFN_01_RSET:
        case MC_AFN_04_SETP:
        case MC_AFN_05_CTRL:
        case MC_AFN_06_AUTH:
        case MC_AFN_08_CASC:
        case MC_AFN_10_GETP:
        case MC_AFN_12_ASKT:
        case MC_AFN_13_ASKR:
        case MC_AFN_14_ASKE:
        case MC_AFN_15_FILE:
        case MC_AFN_16_DATA:

            ucAFN = (UINT8)eAfn;
            break;

        default:
            #ifdef MC_DBG
            MCDBG("emc_pnfn_to_cmdpn() para err!");
            #endif
            return MC_ERR_PARA;
            //break;
    }

    for(i = 0; i < ucNumDaDt; i++)
    {
        sDaDt.ucDA1 = psDaDt[i].ucDA1;
        sDaDt.ucDA2 = psDaDt[i].ucDA2;
        sDaDt.ucDT1 = psDaDt[i].ucDT1;
        sDaDt.ucDT2 = psDaDt[i].ucDT2;

        // p0�����
        if(0 == sDaDt.ucDA1 && 0 == sDaDt.ucDA2)
        {
            sNew.usPn = 0;

            for(j = 0; j < 8; j++)
            {
                if(sDaDt.ucDT1 & (0x01 << j))
                {
                    ucFn  = (sDaDt.ucDT2 * 8) + j + 1;
                    usCmd = (UINT16)(ucAFN << 8 | ucFn);
                    eCmd  = (eMcmd)usCmd;
                    sNew.eCmd = eCmd;
                    (void)emc_add_cmdpn(psCmdPn ,sNew,pucNumCmdPn);
                }
            }
        }
        else
        {
            for(k = 0; k < 8; k++)
            {
                if(sDaDt.ucDA1 & (0x01 << k))
                {
                    sNew.usPn = ((sDaDt.ucDA2-1) * 8 + k + 1);
                    for(j = 0; j < 8; j++)
                    {
                        if(sDaDt.ucDT1 & (0x01 << j))
                        {
                            ucFn  = (sDaDt.ucDT2 * 8) + j + 1;
                            usCmd = (UINT16)(ucAFN << 8 | ucFn);
                            eCmd  = (eMcmd)usCmd;
                            sNew.eCmd = eCmd;
                            (void)emc_add_cmdpn(psCmdPn, sNew, pucNumCmdPn);
                        }
                    }
                }
            }
        }
    }

    return MC_OK;
}

/*****************************************************************************
 �� �� ��  : emc_cmdpn_to_dadt
 ��������  : ʵ�ֽ�ucNumCmdPn��sMcmdPn���� ת����sMcDaDt����
             �����ת����ĸ���pucNumDaDt
 �������  : eMcAFN eAfn
             sMcDaDt* psDaDt
             UINT8 *pucNumDaDt
             sMcmdPn* psCmdPn
             UINT8  ucNumCmdPn
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��9��13�� ������
    ��    ��   : liming
    �޸�����   : �����ɺ���

*****************************************************************************/
eMcErr emc_cmdpn_to_dadt(eMcAFN eAfn, sMcDaDt* psDaDt, UINT8 *pucNumDaDt, sMcmdPn* psCmdPn, UINT8  ucNumCmdPn)
{
    sMcPnFn *psPnFn   = NULL;
    UINT8   ucNumPnFn = 0;
    INT32   i         = 0;
    eMcErr  eRet      = MC_OK;

    if(!psDaDt || !psCmdPn || !pucNumDaDt)
    {
        #ifdef MC_DBG
        MCDBG("emc_cmdpn_to_dadt() para pointer is null!");
        #endif
        return MC_ERR_NULL;
    }
    
    psPnFn = (sMcPnFn*)malloc(sizeof(sMcPnFn)*(ucNumCmdPn+1));
    if(!psPnFn)
    {
        #ifdef MC_DBG
        MCDBG("emc_cmdpn_to_dadt() MC_ERR_IO");
        #endif
        return MC_ERR_IO;
    }

    #if 0
    #ifdef MC_DBG
    printf("ucNumCmdPn = %d\n", ucNumCmdPn);
    for(i = 0; i < ucNumCmdPn; i++)
    {
       printf("psCmdPn[%d].eCmd = 0x%04X\n",i, psCmdPn[i].eCmd);
       printf("psCmdPn[%d].usPn = %d\n\n",i, psCmdPn[i].usPn);
    }
    #endif
    #endif

    eRet = emc_cmdpn_to_pnfn(eAfn, psPnFn, &ucNumPnFn, psCmdPn, ucNumCmdPn);
    if(MC_OK != eRet)
    {
        #ifdef MC_DBG
        MCDBG("emc_cmdpn_to_dadt() emc_cmdpn_to_pnfn() error = %d", eRet);
        #endif
        MC_FREE(psPnFn);
        return eRet;
    }

    #if 0
    #ifdef MC_DBG
    int j = 0;
    printf("ucNumPnFn = %d\n", ucNumPnFn);
    for(i = 0; i < ucNumPnFn; i++)
    {
        for(j = 0; j < 8; j++)
        {
            printf("psPnFn[%d].ucFn[%d] = %d\n", i,j ,psPnFn[i].ucFn[j]);
            printf("psPnFn[%d].usPn[%d] = %d\n\n", i,j ,psPnFn[i].usPn[j]);

        }
    }
    #endif
    #endif

    for(i = 0; i < ucNumPnFn; i++)
    {
        eRet = emc_pnfn_to_dadt(&(psPnFn[i]), &(psDaDt[i]));
        if(MC_OK != eRet)
        {
            #ifdef MC_DBG
            MCDBG("emc_cmdpn_to_dadt() emc_pnfn_to_dadt() error = %d", eRet);
            #endif
            MC_FREE(psPnFn);
            return eRet;
        }
    }

    *pucNumDaDt = ucNumPnFn;
    MC_FREE(psPnFn);
    return MC_OK;
}

/*****************************************************************************
 �� �� ��  : nmc_pow
 ��������  : ��10��N�η� (ע�������Ҫ����10)
 �������  : UINT8 exp
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��5��29��
    ��    ��   : ����
    �޸�����   : �����ɺ���

*****************************************************************************/
int  nmc_pow(UINT8 exp)
{
    if(exp > 10)
    {
        return -1;
    }

    if(exp == 0)
    {
        return 1;
    }

    return 10 * nmc_pow(exp -1);
}

/*****************************************************************************
 �� �� ��  : nmc_get_float_sign
 ��������  : ���һ��Float�ķ���λ  0 1
 �������  : float fVal
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��6��4��
    ��    ��   : ����
    �޸�����   : �����ɺ���

*****************************************************************************/
int   nmc_get_float_sign(float fVal)
{
    uMcFloatFmt floatFmt;
    floatFmt.v = fVal;
    return floatFmt.s.sign;
}

/*****************************************************************************
 �� �� ��  : vmc_set_float_sign
 ��������  : ����һ��������Float�ķ���λ
 �������  : float *pfVal
             int sign     ���ڵ���0Ϊ����С��0Ϊ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��6��4��
    ��    ��   : ����
    �޸�����   : �����ɺ���

*****************************************************************************/
void   vmc_set_float_sign(float *pfVal, int sign)
{
    uMcFloatFmt *pFloatFmt;
    pFloatFmt = (uMcFloatFmt *)pfVal;

    if(sign >= 0)
    {
        pFloatFmt->s.sign = 0;
    }
    else
    {
        pFloatFmt->s.sign = 1;
    }
}

/*****************************************************************************
 �� �� ��  : nmc_get_double_sign
 ��������  : ���һ��double �ķ���λ
 �������  : double dVal
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��5��30��
    ��    ��   : ����
    �޸�����   : �����ɺ���

*****************************************************************************/
int    nmc_get_double_sign(double dVal)
{
    uMcDoubleFmt  doubleFmt;
    doubleFmt.v = dVal;
    return doubleFmt.s.sign;
}

/*****************************************************************************
 �� �� ��  : vmc_set_double_sign
 ��������  : ���ø������ķ���λ
 �������  : int sign   >= 0 ʱ������Ϊ������ < 0ʱ����Ϊ����
 �������  : double *pdVal
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��5��30��
    ��    ��   : ����
    �޸�����   : �����ɺ���

*****************************************************************************/
void   vmc_set_double_sign(double *pdVal, int sign)
{
    uMcDoubleFmt  *pdoubleFmt;
    pdoubleFmt = (uMcDoubleFmt*)pdVal;

    if(sign >= 0)
    {
        pdoubleFmt->s.sign = 0;
    }
    else
    {
        pdoubleFmt->s.sign = 1;
    }
}

/*****************************************************************************
 �� �� ��  : emc_get_tp
 ��������  : ��õ�ǰ�û���Tp (�Զ�ȡ��ǰϵͳʱ��)
 �������  : sMcTp *psuTp
 �������  : sMcTp *psuTp
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��5��30��
    ��    ��   : ����
    �޸�����   : �����ɺ���
*****************************************************************************/
eMcErr emc_get_tp(sMcTp *psuTp)
{
    if(!psuTp)
    {
        #ifdef MC_DBG
        MCDBG("emc_get_tp() para pointer is null!");
        #endif
        return MC_ERR_NULL;
    }

    // ��ȡϵͳ��ǰʱ��
    time_t now;
    struct tm* timenow;
    time(&now);
    timenow = localtime(&now);

    psuTp->sTime.ucDD = timenow->tm_mday;
    psuTp->sTime.ucHH = timenow->tm_hour;
    psuTp->sTime.ucmm = timenow->tm_min;
    psuTp->sTime.ucss = timenow->tm_sec;

    psuTp->ucPermitDelayMinutes = g_ucMcPermitDelayMinutes;

    return MC_OK;
}

/*****************************************************************************
 �� �� ��  : bmc_tp_timeout
 ��������  : �Ե�ǰʱ��Ϊ��׼�ж�һ��tp�Ƿ�ʱ
 �������  : sMcTp *psTP
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��8��9�� ������
    ��    ��   : liming
    �޸�����   : �����ɺ���

*****************************************************************************/
BOOL  bmc_tp_timeout(sMcTp *psTP)
{
    time_t now;
    struct tm* timenow = NULL;
    UINT8 ucDelayMinutes = 0;  // ���ʹ�����ʱʱ��

    int cDay    = 0;
    int cHour   = 0;
    int cMin    = 0;
    int cSec    = 0;

    int rDay    = 0;
    int rHour   = 0;
    int rMin    = 0;
    int rSec    = 0;
    int minutes = 0;  // ��ص�����

    if(!psTP)
    {
        return TRUE;
    }
    
    // ��ȡϵͳ��ǰʱ��
    time(&now);
    timenow = localtime(&now);
    
    cDay  = timenow->tm_mday;
    cHour = timenow->tm_hour;
    cMin  = timenow->tm_min;
    cSec  = timenow->tm_sec;

    rDay  = psTP->sTime.ucDD;
    rHour = psTP->sTime.ucHH;
    rMin  = psTP->sTime.ucmm;
    rSec  = psTP->sTime.ucss;
    ucDelayMinutes = psTP->ucPermitDelayMinutes;
    minutes = (cDay - rDay)*60*24 + (cHour - rHour)*60 + (cMin - rMin) * 1;

    // pclint
    cSec = cSec;
    rSec = rSec;

    if(minutes < 0)
    {
        return TRUE;
    }

    if(minutes <= ucDelayMinutes)
    {
        return FALSE;
    }

    return TRUE;
}

/*****************************************************************************
 �� �� ��  : emc_trans_tp
 ��������  : Tp���ݽṹת������
 �������  : eMcTrans eTrans
 �������  : sMcTp* psUser
             sMcTp_f* psFrame
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��5��30��
    ��    ��   : ����
    �޸�����   : �����ɺ���

*****************************************************************************/
eMcErr emc_trans_tp(eMcTrans eTrans, sMcTp* psUser, sMcTp_f* psFrame)
{
    eMcErr eRet = MC_OK;

    if(!psFrame || !psUser)
    {
        #ifdef MC_DBG
        MCDBG("emc_trans_tp() para pointer is null!");
        #endif
        return MC_ERR_NULL;
    }

    // ֡�ൽ�û���
    if (MC_TRANS_F2U == eTrans)
    {
        psUser->ucPermitDelayMinutes = psFrame->ucPermitDelayMinutes;
        eRet = emc_trans_DDHHmmss(eTrans, &(psUser->sTime), &(psFrame->sTime));
        if(MC_OK != eRet)
        {
            #ifdef MC_DBG
            MCDBG("emc_trans_tp()emc_trans_DDHHmmss error %d!", eRet);
            #endif
            return eRet;
        }
    }
    // �û��ൽ֡��
    else if (MC_TRANS_U2F == eTrans)
    {
        psFrame->ucPermitDelayMinutes = psUser->ucPermitDelayMinutes;
        eRet = emc_trans_DDHHmmss(eTrans, &(psUser->sTime), &(psFrame->sTime));
        if(MC_OK != eRet)
        {
            #ifdef MC_DBG
            MCDBG("emc_trans_tp()emc_trans_DDHHmmss error %d!", eRet);
            #endif
            return eRet;
        }
    }
    else
    {
        #ifdef MC_DBG
        MCDBG("emc_trans_tp() para error!");
        #endif
        return MC_ERR_PARA;
    }

    return MC_OK;
}

/*****************************************************************************
 �� �� ��  : emc_trans_YWMDhms
 ��������  : ���ݸ�ʽ01 ���ڱ�A.1 ��ʽ
 �������  : eMcTrans eTrans

 �������  : sMcYWMDhms* psUser
             sMcYWMDhms_f* psFrame
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��8��21�� ������
    ��    ��   : liming
    �޸�����   : �����ɺ���

*****************************************************************************/
eMcErr emc_trans_YWMDhms(eMcTrans eTrans, sMcYWMDhms* psUser, sMcYWMDhms_f* psFrame)
{
    if(!psFrame || !psUser)
    {
        #ifdef MC_DBG
        MCDBG("emc_trans_YWMDhms() para pointer is null!");
        #endif
        return MC_ERR_NULL;
    }

    if (MC_TRANS_F2U == eTrans)  // ֡�ൽ�û���
    {
        psUser->ucYY  = psFrame->bcd_YY_0 + psFrame->bcd_YY_1 * 10;
        psUser->ucWW  = psFrame->bcd_WW_0;
        psUser->ucMM  = psFrame->bcd_MM_0 + psFrame->bcd_MM_1 * 10;
        psUser->ucDD  = psFrame->bcd_DD_0 + psFrame->bcd_DD_1 * 10;
        psUser->ucHH  = psFrame->bcd_HH_0 + psFrame->bcd_HH_1 * 10;
        psUser->ucmm  = psFrame->bcd_mm_0 + psFrame->bcd_mm_1 * 10;
        psUser->ucss  = psFrame->bcd_ss_0 + psFrame->bcd_ss_1 * 10;
    }
    else if (MC_TRANS_U2F == eTrans) // �û��ൽ֡��
    {
        // ��
        psFrame->bcd_YY_0 = ucmc_get_bcd_0(psUser->ucYY);
        psFrame->bcd_YY_1 = ucmc_get_bcd_1(psUser->ucYY);

        // ��
        if (psUser->ucMM > 12)
        {
             #ifdef MC_DBG
             MCDBG("emc_trans_YWMDhms() ucMM MC_ERR_OUTRNG!");
             #endif
             return MC_ERR_OUTRNG;
        }
        else
        {
            psFrame->bcd_MM_0 = ucmc_get_bcd_0(psUser->ucMM);
            psFrame->bcd_MM_1 = ucmc_get_bcd_1(psUser->ucMM);
        }

        // ����
        if (psUser->ucWW > 7)
        {
            #ifdef MC_DBG
            MCDBG("emc_trans_YWMDhms() ucWW MC_ERR_OUTRNG!");
            #endif
            return MC_ERR_OUTRNG;
        }
        else
        {
            psFrame->bcd_WW_0 = psUser->ucWW;
        }

        // ��
        if (psUser->ucDD > 31)
        {
            #ifdef MC_DBG
            MCDBG("emc_trans_YWMDhms() ucDD MC_ERR_OUTRNG!");
            #endif
            return MC_ERR_OUTRNG;
        }
        else
        {
            psFrame->bcd_DD_0 = ucmc_get_bcd_0(psUser->ucDD);
            psFrame->bcd_DD_1 = ucmc_get_bcd_1(psUser->ucDD);
        }

        // ʱ
        if(psUser->ucHH > 24)
        {
            #ifdef MC_DBG
            MCDBG("emc_trans_YWMDhms() ucHH MC_ERR_OUTRNG!");
            #endif
            return MC_ERR_OUTRNG;
        }
        else
        {
            psFrame->bcd_HH_0 = ucmc_get_bcd_0(psUser->ucHH);
            psFrame->bcd_HH_1 = ucmc_get_bcd_1(psUser->ucHH);
        }

        // ��
        if(psUser->ucmm > 60)
        {
            #ifdef MC_DBG
            MCDBG("emc_trans_YWMDhms() ucmm MC_ERR_OUTRNG!");
            #endif
            return MC_ERR_OUTRNG;
        }
        else
        {
            psFrame->bcd_mm_0 = ucmc_get_bcd_0(psUser->ucmm);
            psFrame->bcd_mm_1 = ucmc_get_bcd_1(psUser->ucmm);
        }

        // ��
        if(psUser->ucss > 60)
        {
            #ifdef MC_DBG
            MCDBG("emc_trans_YWMDhms() ucSencond MC_ERR_OUTRNG!");
            #endif
            return MC_ERR_OUTRNG;
        }
        else
        {
            psFrame->bcd_ss_0 = ucmc_get_bcd_0(psUser->ucss);
            psFrame->bcd_ss_1 = ucmc_get_bcd_1(psUser->ucss);
        }
    }
    else
    {
        #ifdef MC_DBG
        MCDBG("emc_trans_YWMDhms() para error!");
        #endif
        return MC_ERR_PARA;
    }

    return MC_OK;
}

/*****************************************************************************
 �� �� ��  : emc_trans_YYMMDDhhmm
 ��������  : ���ݸ�ʽת������  ���ݸ�ʽ2 ���ڱ�A.2 ��λ: ������ʱ��
 �������  : eMcTrans eTrans
             sMcYMDhm* psUser
             sMcYMDhm_f* psFrame
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��10��23�� ������
    ��    ��   : liming
    �޸�����   : �����ɺ���

*****************************************************************************/
eMcErr emc_trans_YYMMDDhhmm(eMcTrans eTrans, sMcYMDhm* psUser, sMcYMDhm_f* psFrame)
{
    if(!psUser || !psFrame)
    {
        #ifdef MC_DBG
        MCDBG("emc_trans_YYMMDDhhmm() para pointer is null!");
        #endif
        return MC_ERR_NULL;
    }

    if(MC_TRANS_U2F == eTrans)
    {
        // ��
        psFrame->bcd_YY_0 = ucmc_get_bcd_0(psUser->ucYY);
        psFrame->bcd_YY_1 = ucmc_get_bcd_1(psUser->ucYY);

        // ��
        if(psUser->ucMM > 12)
        {
            #ifdef MC_DBG
            MCDBG("emc_trans_YYMMDDhhmm() ucMM MC_ERR_OUTRNG!");
            #endif
            return MC_ERR_OUTRNG;
        }
        else
        {
            psFrame->bcd_MM_0 = ucmc_get_bcd_0(psUser->ucMM);
            psFrame->bcd_MM_1 = ucmc_get_bcd_1(psUser->ucMM);
        }

        // ��
        if(psUser->ucDD > 31)
        {
            #ifdef MC_DBG
            MCDBG("emc_trans_YYMMDDhhmm() ucDD MC_ERR_OUTRNG!");
            #endif
            return MC_ERR_OUTRNG;
        }
        else
        {
            psFrame->bcd_DD_0 = ucmc_get_bcd_0(psUser->ucDD);
            psFrame->bcd_DD_1 = ucmc_get_bcd_1(psUser->ucDD);
        }

        // ʱ
        if(psUser->ucHH > 24)
        {
            #ifdef MC_DBG
            MCDBG("emc_trans_YYMMDDhhmm() ucHH MC_ERR_OUTRNG!");
            #endif
            return MC_ERR_OUTRNG;
        }
        else
        {
            psFrame->bcd_hh_0 = ucmc_get_bcd_0(psUser->ucHH);
            psFrame->bcd_hh_1 = ucmc_get_bcd_1(psUser->ucHH);
        }

        // ��
        if(psUser->ucmm > 60)
        {
            #ifdef MC_DBG
            MCDBG("emc_trans_YYMMDDhhmm() ucmm MC_ERR_OUTRNG!");
            #endif
            return MC_ERR_OUTRNG;
        }
        else
        {
            psFrame->bcd_mm_0 = ucmc_get_bcd_0(psUser->ucmm);
            psFrame->bcd_mm_1 = ucmc_get_bcd_1(psUser->ucmm);
        }

    }
    else if(MC_TRANS_F2U == eTrans)
    {
        psUser->ucYY = psFrame->bcd_YY_0 + psFrame->bcd_YY_1 * 10;
        psUser->ucMM = psFrame->bcd_MM_0 + psFrame->bcd_MM_1 * 10;
        psUser->ucDD = psFrame->bcd_DD_0 + psFrame->bcd_DD_1 * 10;
        psUser->ucHH = psFrame->bcd_hh_0 + psFrame->bcd_hh_1 * 10;
        psUser->ucmm = psFrame->bcd_mm_0 + psFrame->bcd_mm_1 * 10;
    }
    else
    {
        #ifdef MC_DBG
        MCDBG("ucmc_get_bcd_0() para error!");
        #endif
        return MC_ERR_PARA;
    }

    return MC_OK;
}

/*****************************************************************************
 �� �� ��  : emc_trans_DDHHmmss
 ��������  : ���ݸ�ʽת������ ���ݸ�ʽ3 ���ڱ�A.3 ��λ: ��ʱ����
 �������  : eMcTrans eTrans
             sMcDDhhmmss* psDDhhmmss_u
             sMcDDhhmmss_f* psDDhhmmss_f
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��10��23�� ������
    ��    ��   : liming
    �޸�����   : �����ɺ���

*****************************************************************************/
eMcErr emc_trans_DDHHmmss(eMcTrans eTrans, sMcDDHHmmss* psDDHHmmss_u, sMcDDHHmmss_f* psDDHHmmss_f)
{
    if(!psDDHHmmss_u || !psDDHHmmss_f)
    {
        #ifdef MC_DBG
        MCDBG("emc_trans_DDhhmmss() para pointer is null!");
        #endif
        return MC_ERR_NULL;
    }

    if(MC_TRANS_U2F == eTrans)
    {
        if(psDDHHmmss_u->ucDD > 31 || psDDHHmmss_u->ucDD < 0)
        {
            #ifdef MC_DBG
            MCDBG("emc_trans_DDhhmmss() ucDD MC_ERR_OUTRNG!");
            #endif
            return MC_ERR_OUTRNG;
        }
        else
        {
            psDDHHmmss_f->bcd_DD_0 = ucmc_get_bcd_0(psDDHHmmss_u->ucDD);
            psDDHHmmss_f->bcd_DD_1 = ucmc_get_bcd_1(psDDHHmmss_u->ucDD);
        }

        if(psDDHHmmss_u->ucHH > 24)
        {
            #ifdef MC_DBG
            MCDBG("emc_trans_DDhhmmss() ucHH MC_ERR_OUTRNG!");
            #endif
            return MC_ERR_OUTRNG;
        }
        else
        {
            psDDHHmmss_f->bcd_HH_0 = ucmc_get_bcd_0(psDDHHmmss_u->ucHH);
            psDDHHmmss_f->bcd_HH_1 = ucmc_get_bcd_1(psDDHHmmss_u->ucHH);
        }

        if(psDDHHmmss_u->ucmm > 60)
        {
            #ifdef MC_DBG
            MCDBG("emc_trans_DDhhmmss() ucHH MC_ERR_OUTRNG!");
            #endif
            return MC_ERR_OUTRNG;
        }
        else
        {
            psDDHHmmss_f->bcd_mm_0 = ucmc_get_bcd_0(psDDHHmmss_u->ucmm);
            psDDHHmmss_f->bcd_mm_1 = ucmc_get_bcd_1(psDDHHmmss_u->ucmm);
        }

        if(psDDHHmmss_u->ucss > 60)
        {
            #ifdef MC_DBG
            MCDBG("emc_trans_DDhhmmss() ucHH MC_ERR_OUTRNG!");
            #endif
            return MC_ERR_OUTRNG;
        }
        else
        {
            psDDHHmmss_f->bcd_ss_0 = ucmc_get_bcd_0(psDDHHmmss_u->ucss);
            psDDHHmmss_f->bcd_ss_1 = ucmc_get_bcd_1(psDDHHmmss_u->ucss);
        }
    }
    else if(MC_TRANS_F2U == eTrans)
    {
        psDDHHmmss_u->ucDD = psDDHHmmss_f->bcd_DD_0 + psDDHHmmss_f->bcd_DD_1 * 10;
        psDDHHmmss_u->ucHH = psDDHHmmss_f->bcd_HH_0 + psDDHHmmss_f->bcd_HH_1 * 10;
        psDDHHmmss_u->ucmm = psDDHHmmss_f->bcd_mm_0 + psDDHHmmss_f->bcd_mm_1 * 10;
        psDDHHmmss_u->ucss = psDDHHmmss_f->bcd_ss_0 + psDDHHmmss_f->bcd_ss_1 * 10;
    }
    else
    {
        #ifdef MC_DBG
        MCDBG("emc_trans_DDhhmmss() para error!");
        #endif
        return MC_ERR_PARA;
    }

    return MC_OK;
}

/*****************************************************************************
 �� �� ��  : emc_trans_XXXXXX_XXXX
 ��������  : ���ݸ�ʽ4 ���ڱ�A.4 ��ʽ: (+)XXXXXX.XXXX
 �������  : eMcTrans eTrans
             float* psUser
             sMcFmt_XXXXXX_XXXX* psFrame
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��10��23�� ������
    ��    ��   : liming
    �޸�����   : �����ɺ���

*****************************************************************************/
eMcErr emc_trans_XXXXXX_XXXX(eMcTrans eTrans, double* psUser, sMcFmt_XXXXXX_XXXX* psFrame)
{
    if(!psFrame || !psUser)
    {
        #ifdef MC_DBG
        MCDBG("emc_trans_XXXXXX_XXXX() para pointer is null!");
        #endif
        return MC_ERR_NULL;
    }

    sMcFmt_XXXXXX_XXXX    *psFmtXXXXXX_XXXX;
    double                *pdXXXXXX_XXXX;

    psFmtXXXXXX_XXXX      = (sMcFmt_XXXXXX_XXXX *)psFrame;
    pdXXXXXX_XXXX         = (double *)psUser;
    double dXXXXXX_XXXX   = *pdXXXXXX_XXXX;

     // �û��ൽ֡��
    if(MC_TRANS_U2F == eTrans)
    {
        if(dXXXXXX_XXXX > 999999.9999 || dXXXXXX_XXXX < -999999.9999)
        {
            return MC_ERR_OUTRNG;
        }
        CHAR buf[7] = {0};

        //����ṹ
        psFmtXXXXXX_XXXX->BCD_5     = (UINT8)(dXXXXXX_XXXX / nmc_pow(5));
        dXXXXXX_XXXX -= psFmtXXXXXX_XXXX->BCD_5 * nmc_pow(5);
        psFmtXXXXXX_XXXX->BCD_4     = (UINT8)(dXXXXXX_XXXX / nmc_pow(4));
        dXXXXXX_XXXX -= psFmtXXXXXX_XXXX->BCD_4 * nmc_pow(4);
        psFmtXXXXXX_XXXX->BCD_3     = (UINT8)(dXXXXXX_XXXX / nmc_pow(3));
        dXXXXXX_XXXX -= psFmtXXXXXX_XXXX->BCD_3 * nmc_pow(3);
        psFmtXXXXXX_XXXX->BCD_2     = (UINT8)(dXXXXXX_XXXX / nmc_pow(2));
        dXXXXXX_XXXX -= psFmtXXXXXX_XXXX->BCD_2 * nmc_pow(2);
        psFmtXXXXXX_XXXX->BCD_1     = (UINT8)(dXXXXXX_XXXX / nmc_pow(1));
        dXXXXXX_XXXX -= psFmtXXXXXX_XXXX->BCD_1 * nmc_pow(1);
        psFmtXXXXXX_XXXX->BCD_0     = (UINT8)dXXXXXX_XXXX % nmc_pow(1);
        dXXXXXX_XXXX -= psFmtXXXXXX_XXXX->BCD_0;

        sprintf(buf,"%4.4f",dXXXXXX_XXXX);
        psFmtXXXXXX_XXXX->BCD_0_1   = buf[2] - '0';
        psFmtXXXXXX_XXXX->BCD_0_2   = buf[3] - '0';
        psFmtXXXXXX_XXXX->BCD_0_3   = buf[4] - '0';
        psFmtXXXXXX_XXXX->BCD_0_4   = buf[5] - '0';

    }
    // ֡�ൽ�û���
    else if(MC_TRANS_F2U == eTrans)
    {
        UINT8    bcd[10];
        int      i;
        UINT32   uiInt,uiFrac;

        uiInt  = 0;
        uiFrac = 0;

        bcd[0] = (UINT8)psFmtXXXXXX_XXXX->BCD_0_4;
        bcd[1] = (UINT8)psFmtXXXXXX_XXXX->BCD_0_3;
        bcd[2] = (UINT8)psFmtXXXXXX_XXXX->BCD_0_2;
        bcd[3] = (UINT8)psFmtXXXXXX_XXXX->BCD_0_1;
        bcd[4] = (UINT8)psFmtXXXXXX_XXXX->BCD_0;
        bcd[5] = (UINT8)psFmtXXXXXX_XXXX->BCD_1;
        bcd[6] = (UINT8)psFmtXXXXXX_XXXX->BCD_2;
        bcd[7] = (UINT8)psFmtXXXXXX_XXXX->BCD_3;
        bcd[8] = (UINT8)psFmtXXXXXX_XXXX->BCD_4;
        bcd[9] = (UINT8)psFmtXXXXXX_XXXX->BCD_5;

        for(i = 0; i < 4; i++)
        {
            uiFrac += bcd[i]*nmc_pow(i);
        }

        for ( ; i < 10; i++)
        {
            uiInt += bcd[i]*nmc_pow(i - 4);
        }

        dXXXXXX_XXXX = (DOUBLE)uiInt + (DOUBLE)uiFrac/10000.0;
        *pdXXXXXX_XXXX = dXXXXXX_XXXX;
    }
    else
    {
        #ifdef MC_DBG
        MCDBG("emc_trans_XXXXXX_XXXX() para error!");
        #endif
        return MC_ERR_PARA;
    }

    return MC_OK;
}

/*****************************************************************************
 �� �� ��  : emc_trans_XXXXXX_XX
 ��������  : ���ݸ�ʽ5 ���ڱ�A.5 ��ʽ: (+)XXXXXX.XX
 �������  : eMcTrans eTrans
             float* psUser
             sMcFmt_XXXXXX_XX* psFrame
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��10��23�� ������
    ��    ��   : liming
    �޸�����   : �����ɺ���

*****************************************************************************/
eMcErr emc_trans_XXXXXX_XX(eMcTrans eTrans, double* psUser, sMcFmt_XXXXXX_XX* psFrame)
{
    if(!psFrame || !psUser)
    {
        #ifdef MC_DBG
        MCDBG("emc_trans_XXXXXX_XX() para pointer is null!");
        #endif
        return MC_ERR_NULL;
    }

    sMcFmt_XXXXXX_XX    *psFmtXXXXXX_XX = NULL;
    double              *pdXXXXXX_XX;
    psFmtXXXXXX_XX      = (sMcFmt_XXXXXX_XX *)psFrame;
    pdXXXXXX_XX         = (double *)psUser;
    double dXXXXXX_XX   = *pdXXXXXX_XX;

    // �û��ൽ֡��
    if(MC_TRANS_U2F == eTrans)
    {
        if(dXXXXXX_XX > 999999.99 || dXXXXXX_XX < -999999.99)
        {
            return MC_ERR_OUTRNG;
        }

        char buf[5] = {0};
        //����ṹ
        psFmtXXXXXX_XX->BCD_5     = (UINT8)(dXXXXXX_XX / nmc_pow(5));
        dXXXXXX_XX -= psFmtXXXXXX_XX->BCD_5 * nmc_pow(5);
        psFmtXXXXXX_XX->BCD_4     = (UINT8)(dXXXXXX_XX / nmc_pow(4));
        dXXXXXX_XX -= psFmtXXXXXX_XX->BCD_4 * nmc_pow(4);
        psFmtXXXXXX_XX->BCD_3     = (UINT8)(dXXXXXX_XX / nmc_pow(3));
        dXXXXXX_XX -= psFmtXXXXXX_XX->BCD_3 * nmc_pow(3);
        psFmtXXXXXX_XX->BCD_2     = (UINT8)(dXXXXXX_XX / nmc_pow(2));
        dXXXXXX_XX -= psFmtXXXXXX_XX->BCD_2 * nmc_pow(2);
        psFmtXXXXXX_XX->BCD_1     = (UINT8)(dXXXXXX_XX / nmc_pow(1));
        dXXXXXX_XX -= psFmtXXXXXX_XX->BCD_1 * nmc_pow(1);
        psFmtXXXXXX_XX->BCD_0     = (UINT32)dXXXXXX_XX % nmc_pow(1);
        dXXXXXX_XX -= psFmtXXXXXX_XX->BCD_0;
        sprintf(buf,"%2.2f",dXXXXXX_XX);
        psFmtXXXXXX_XX->BCD_0_1   =  buf[2] - '0';
        psFmtXXXXXX_XX->BCD_0_2   =  buf[3] - '0';

     }
     // ֡�ൽ�û���
     else if(MC_TRANS_F2U == eTrans)
     {
        UINT8    bcd[8];
        int      i;
        UINT32   uiInt,uiFrac;

        uiInt = 0;
        uiFrac = 0;

        bcd[0] = (UINT8)psFmtXXXXXX_XX->BCD_0_2;
        bcd[1] = (UINT8)psFmtXXXXXX_XX->BCD_0_1;
        bcd[2] = (UINT8)psFmtXXXXXX_XX->BCD_0;
        bcd[3] = (UINT8)psFmtXXXXXX_XX->BCD_1;
        bcd[4] = (UINT8)psFmtXXXXXX_XX->BCD_2;
        bcd[5] = (UINT8)psFmtXXXXXX_XX->BCD_3;
        bcd[6] = (UINT8)psFmtXXXXXX_XX->BCD_4;
        bcd[7] = (UINT8)psFmtXXXXXX_XX->BCD_5;

        for(i = 0; i < 2; i++)
        {
            uiFrac += bcd[i]*nmc_pow(i);
        }

        for(; i < 8; i++)
        {
            uiInt+= bcd[i]*nmc_pow(i - 2);
        }

        dXXXXXX_XX = (DOUBLE)uiInt + (DOUBLE)uiFrac/100.0;
        *pdXXXXXX_XX = dXXXXXX_XX;
     }
    else
    {
        #ifdef MC_DBG
        MCDBG("emc_trans_XXXXXX_XX() para error!");
        #endif
        return MC_ERR_PARA;
    }

    return MC_OK;
}

/*****************************************************************************
 �� �� ��  : emc_trans_sXX_XXXX
 ��������  : ���ݸ�ʽ06 ���ڱ�A.6
 �������  : eMcTrans eTrans

 �������  : float* psUser
             sMcFmt06_f* psFrame
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��10��23�� ������
    ��    ��   : liming
    �޸�����   : �����ɺ���

*****************************************************************************/
eMcErr emc_trans_sXX_XXXX(eMcTrans eTrans, float* psUser, sMcFmt06_f* psFrame)
{
    if(!psFrame || !psUser)
     {
        #ifdef MC_DBG
        MCDBG("emc_trans_sXX_XXXX() para pointer is null!");
        #endif
        return MC_ERR_NULL;
     }

    sMcFmt_sXX_XXXX   *psFmtsXX_XXXX = NULL;
    float             *pfXX_XXXX     = NULL;
    float             fZhengshu      = 0.0f;  // ��������	
    psFmtsXX_XXXX  = (sMcFmt_sXX_XXXX *)psFrame;
    pfXX_XXXX      = (float *)psUser;
    float fXX_XXXX = *pfXX_XXXX;
    int sign       = 0;

    // �û��ൽ֡��
    if(MC_TRANS_U2F == eTrans)
    {
        if(fXX_XXXX > 79.9999f || fXX_XXXX < -79.9999f)
        {
            return MC_ERR_OUTRNG;
        }

        modff(fXX_XXXX * 10000.0f, &fZhengshu);
        sign = nmc_get_float_sign(fZhengshu);
        vmc_set_float_sign(&fZhengshu, 0);

        char buf[8] = {0};
        sprintf(buf, "%06.0lf\n", fZhengshu);

        //����ṹ
        psFmtsXX_XXXX->S       = sign;
        psFmtsXX_XXXX->BCD_1   = buf[0] - '0';
        psFmtsXX_XXXX->BCD_0   = buf[1] - '0';
        psFmtsXX_XXXX->BCD_0_1 = buf[2] - '0';
        psFmtsXX_XXXX->BCD_0_2 = buf[3] - '0';
        psFmtsXX_XXXX->BCD_0_3 = buf[4] - '0';
        psFmtsXX_XXXX->BCD_0_4 = buf[5] - '0';

    }
    // ֡�ൽ�û���
    else if(MC_TRANS_F2U == eTrans)
    {
        UINT8    bcd[6];
        int      i;
        float    valid = 0.0f;
        bcd[0] = (UINT8)psFmtsXX_XXXX->BCD_0_4;
        bcd[1] = (UINT8)psFmtsXX_XXXX->BCD_0_3;
        bcd[2] = (UINT8)psFmtsXX_XXXX->BCD_0_2;
        bcd[3] = (UINT8)psFmtsXX_XXXX->BCD_0_1;
        bcd[4] = (UINT8)psFmtsXX_XXXX->BCD_0;
        bcd[5] = (UINT8)psFmtsXX_XXXX->BCD_1;

        for(i = 0; i < 6; i++)
        {
            valid+= bcd[i]*nmc_pow(i);
        }

        fXX_XXXX = valid/10000.0f;
        *pfXX_XXXX = fXX_XXXX * (psFmtsXX_XXXX->S  == 0 ? 1.0f : -1.0f);

    }
    else
    {
        #ifdef MC_DBG
        MCDBG("emc_trans_sXX_XXXX() para error!");
        #endif
        return MC_ERR_PARA;
    }

    return MC_OK;
}

/*****************************************************************************
 �� �� ��  : emc_trans_sXXX_X
 ��������  : ���ݸ�ʽ07 ���ڱ�A.7
             ��ʽ: (+/1)XXX.X
 �������  : eMcTrans eTrans
             float* psUser
             sMcFmt05* psFrame
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��10��23�� ������
    ��    ��   : liming
    �޸�����   : �����ɺ���

*****************************************************************************/
eMcErr emc_trans_sXXX_X(eMcTrans eTrans, float* psUser, sMcFmt07_f* psFrame)
{
    if(!psFrame || !psUser)
    {
        #ifdef MC_DBG
        MCDBG("emc_trans_sXXX_X() para pointer is null!");
        #endif
        return MC_ERR_NULL;
    }

    sMcFmt_sXXX_X    *psFmtsXXX_X = NULL;
    float             *pfXXX_X    = NULL;
    float             fZhengshu   = 0.0f;  // ��������
    psFmtsXXX_X    = (sMcFmt07_f *)psFrame;
    pfXXX_X        = (float *)psUser;
    float fXXX_X   = *pfXXX_X;
    int sign       = 0;

    // �û��ൽ֡��
    if(MC_TRANS_U2F == eTrans)
    {
        if(fXXX_X > 799.9f || fXXX_X < -799.9f)
        {
            return MC_ERR_OUTRNG;
        }

        modff(fXXX_X*10, &fZhengshu);
        sign = nmc_get_float_sign(fZhengshu);
        vmc_set_float_sign(&fZhengshu, 0);

        char buf[8] = {0};
        sprintf(buf, "%04.0lf\n", fZhengshu);

        //����ṹ
        psFmtsXXX_X->S       = sign;
        psFmtsXXX_X->BCD_2   = buf[0] - '0';
        psFmtsXXX_X->BCD_1   = buf[1] - '0';
        psFmtsXXX_X->BCD_0   = buf[2] - '0';
        psFmtsXXX_X->BCD_0_1 = buf[3] - '0';

    }
    // ֡�ൽ�û���
    else if(MC_TRANS_F2U == eTrans)
    {
        UINT8    bcd[4];
        int      i;
        float    valid = 0.0f;
        bcd[0] = (UINT8)psFmtsXXX_X->BCD_0_1;
        bcd[1] = (UINT8)psFmtsXXX_X->BCD_0;
        bcd[2] = (UINT8)psFmtsXXX_X->BCD_1;
        bcd[3] = (UINT8)psFmtsXXX_X->BCD_2;

        for(i = 0; i < 4; i++)
        {
            valid+= bcd[i]*nmc_pow(i);
        }

        fXXX_X = valid/10.0f;
        *pfXXX_X = fXXX_X * (psFmtsXXX_X->S == 0 ? 1.0f : -1.0f);
    }
    else
    {
        #ifdef MC_DBG
        MCDBG("emc_trans_sXXX_X() para error!");
        #endif
        return MC_ERR_PARA;
    }

    return MC_OK;
}

/*****************************************************************************
 �� �� ��  : emc_trans_XXX_X
 ��������  : ���ݸ�ʽ08 ���ڱ�A.8 ��ʽ: (+)XXX.X
 �������  : eMcTrans eTrans
             float* psUser
             sMcFmt_XXX_X* psFrame
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��10��23�� ������
    ��    ��   : liming
    �޸�����   : �����ɺ���

*****************************************************************************/
eMcErr emc_trans_XXX_X(eMcTrans eTrans, float* psUser, sMcFmt08_f* psFrame)
{
    if(!psFrame || !psUser)
    {
         #ifdef MC_DBG
         MCDBG("emc_trans_XXX_X() para pointer is null!");
         #endif
         return MC_ERR_NULL;
    }

    sMcFmt08_f    *psFmtXXX_X   = NULL;
    float             *pfXXX_X  = NULL;
    float             fZhengshu = 0.0f;  // ��������
    psFmtXXX_X    = (sMcFmt08_f *)psFrame;
    pfXXX_X        = (float *)psUser;
    float fXXX_X   = *pfXXX_X;

    // �û��ൽ֡��
    if(MC_TRANS_U2F == eTrans)
    {
        if(fXXX_X > 999.9f || fXXX_X < 0.0f)
        {
            return MC_ERR_OUTRNG;
        }

        modff(fXXX_X*10, &fZhengshu);
        vmc_set_float_sign(&fZhengshu, 0);
        char buf[8] = {0};
        sprintf(buf, "%04.0lf\n", fZhengshu);

        //����ṹ
        psFmtXXX_X->BCD_2   = buf[0] - '0';
        psFmtXXX_X->BCD_1   = buf[1] - '0';
        psFmtXXX_X->BCD_0   = buf[2] - '0';
        psFmtXXX_X->BCD_0_1 = buf[3] - '0';

    }
    // ֡�ൽ�û���
    else if(MC_TRANS_F2U == eTrans)
    {
        UINT8    bcd[4];
        int      i;
        float    valid = 0.0f;
        bcd[0] = (UINT8)psFmtXXX_X->BCD_0_1;
        bcd[1] = (UINT8)psFmtXXX_X->BCD_0;
        bcd[2] = (UINT8)psFmtXXX_X->BCD_1;
        bcd[3] = (UINT8)psFmtXXX_X->BCD_2;

        for(i = 0; i < 4; i++)
        {
            valid+= bcd[i]*nmc_pow(i);
        }

        fXXX_X   = valid / 10.0f;
        *pfXXX_X = fXXX_X;
    }
    else
    {
        #ifdef MC_DBG
        MCDBG("emc_trans_XXX_X() para error!");
        #endif
        return MC_ERR_PARA;
    }

    return MC_OK;
}

/*****************************************************************************
 �� �� ��  : emc_trans_sXXX_XXX
 ��������  : ���ݸ�ʽ09 ���ڱ�A.9 ��ʽ: (+/1)XXX.XXX
 �������  : eMcTrans eTrans
             float* psUser
             sMcFmt_sXXX_XXX* psFrame
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��10��23�� ������
    ��    ��   : liming
    �޸�����   : �����ɺ���

*****************************************************************************/
eMcErr emc_trans_sXXX_XXX(eMcTrans eTrans, float* psUser, sMcFmt_sXXX_XXX* psFrame)
{
    if(!psFrame || !psUser)
    {
        #ifdef MC_DBG
        MCDBG("emc_trans_sXXX_XXX() para pointer is null!");
        #endif
        return MC_ERR_NULL;
    }

    sMcFmt_sXXX_XXX   *psFmtsXXX_XXX = NULL;
    float             *pfXXX_XXX     = NULL;
    float             fZhengshu      = 0.0f;  // ��������
    psFmtsXXX_XXX  = (sMcFmt_sXXX_XXX *)psFrame;
    pfXXX_XXX      = (float *)psUser;
    float fXXX_XXX = *pfXXX_XXX;
    int sign       = 0;

    // �û��ൽ֡��
    if(MC_TRANS_U2F == eTrans)
    {
        if(fXXX_XXX > 799.999f || fXXX_XXX < -799.999f)
        {
            return MC_ERR_OUTRNG;
        }

        modff(fXXX_XXX*1000.0f, &fZhengshu);
        sign = nmc_get_float_sign(fZhengshu);     // ��÷���λ
        vmc_set_float_sign(&fZhengshu, 0);        // ����Ϊ��

        char buf[8] = {0};
        sprintf(buf, "%06.0lf\n", fZhengshu);

        //����ṹ
        psFmtsXXX_XXX->S       = sign;
        psFmtsXXX_XXX->BCD_2   = buf[0] - '0';
        psFmtsXXX_XXX->BCD_1   = buf[1] - '0';
        psFmtsXXX_XXX->BCD_0   = buf[2] - '0';
        psFmtsXXX_XXX->BCD_0_1 = buf[3] - '0';
        psFmtsXXX_XXX->BCD_0_2 = buf[4] - '0';
        psFmtsXXX_XXX->BCD_0_3 = buf[5] - '0';
     }
     // ֡�ൽ�û���
     else if(MC_TRANS_F2U == eTrans)
     {
        UINT8    bcd[6];
        int      i;
        float    valid = 0.0f;
        bcd[0] = (UINT8)psFmtsXXX_XXX->BCD_0_3;
        bcd[1] = (UINT8)psFmtsXXX_XXX->BCD_0_2;
        bcd[2] = (UINT8)psFmtsXXX_XXX->BCD_0_1;
        bcd[3] = (UINT8)psFmtsXXX_XXX->BCD_0;
        bcd[4] = (UINT8)psFmtsXXX_XXX->BCD_1;
        bcd[5] = (UINT8)psFmtsXXX_XXX->BCD_2;

        for(i = 0; i < 6; i++)
        {
            valid+= bcd[i]*nmc_pow(i);
        }

        fXXX_XXX = valid/1000.0f;
        *pfXXX_XXX = fXXX_XXX * (psFmtsXXX_XXX->S  == 0 ? 1.0f : -1.0f);

    }
    else
    {
        #ifdef MC_DBG
        MCDBG("emc_trans_sXXX_XXX() para error!");
        #endif
        return MC_ERR_PARA;
    }

    return MC_OK;
}

/*****************************************************************************
 �� �� ��  : emc_trans_XXX_X
 ��������  : ���ݸ�ʽ10 ���ڱ�A.10 ��ʽ: (+)XXX.X
 �������  : eMcTrans eTrans

 �������  : float* psUser
             sMcFmt10_f* psFrame
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��10��23�� ������
    ��    ��   : liming
    �޸�����   : �����ɺ���

*****************************************************************************/
eMcErr emc_trans_XX_XX(eMcTrans eTrans, float* psUser, sMcFmt10_f* psFrame)
{
    if(!psFrame || !psUser)
    {
         #ifdef MC_DBG
         MCDBG("emc_trans_XX_XX() para pointer is null!");
         #endif
         return MC_ERR_NULL;
    }

    sMcFmt_XX_XX    *pf       = NULL;
    float           *pu       = NULL;
    float           fZhengshu = 0.0f;  // ��������
    pf    = (sMcFmt_XX_XX *)psFrame;
    pu    = (float *)psUser;
    float fXX_XX   = *pu;

    // �û��ൽ֡��
    if(MC_TRANS_U2F == eTrans)
    {
        if(fXX_XX > 99.99f || fXX_XX < 0.0f)
        {
            return MC_ERR_OUTRNG;
        }

        modff(fXX_XX*100, &fZhengshu);
        vmc_set_float_sign(&fZhengshu, 0);
        char buf[8] = {0};
        sprintf(buf, "%04.0lf\n", fZhengshu);

        //����ṹ
        pf->BCD_1   = buf[0] - '0';
        pf->BCD_0   = buf[1] - '0';
        pf->BCD_0_1 = buf[2] - '0';
        pf->BCD_0_2 = buf[3] - '0';

    }
    // ֡�ൽ�û���
    else if(MC_TRANS_F2U == eTrans)
    {
        UINT8    bcd[4];
        int      i;
        float    valid = 0.0f;
        bcd[0] = (UINT8)pf->BCD_0_2;
        bcd[1] = (UINT8)pf->BCD_0_1;
        bcd[2] = (UINT8)pf->BCD_0;
        bcd[3] = (UINT8)pf->BCD_1;

        for(i = 0; i < 4; i++)
        {
            valid+= bcd[i]*nmc_pow(i);
        }

        fXX_XX   = valid / 100.0f;
        *pu = fXX_XX;
    }
    else
    {
        #ifdef MC_DBG
        MCDBG("emc_trans_XX_XX() para error!");
        #endif
        return MC_ERR_PARA;
    }

    return MC_OK;
}

/*****************************************************************************
 �� �� ��  : emc_trans_sX7
 ��������  : ���ݸ�ʽ11 ���ڱ�A.11
             ��ʽ: (+/1)XXXXXXX (10(-3)~10(4))
 �������  : eMcTrans eTrans
             void* psUser
             void* psFrame
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��10��23�� ������
    ��    ��   : liming
    �޸�����   : �����ɺ���

*****************************************************************************/
eMcErr emc_trans_sX7(eMcTrans eTrans, void* psUser, void* psFrame)
{
    if(!psFrame || !psUser)
    {
         #ifdef MC_DBG
         MCDBG("emc_trans_sX7() para pointer is null!");
         #endif
         return MC_ERR_NULL;
    }

    int        valid  = 0;     
    int        sign   = 0;     
    int        i      = 0;
    int        index  = 6; 
    UINT8      bcd[8] = {0};
    UINT8      ucS    = 0;
    UINT8      ucG1   = 0;
    UINT8      ucG2   = 0;
    UINT8      ucG3   = 0;
    UINT8     ucSG123 = 0;
    double     dTmp   = 0.0;   
    double  dZhengshu = 0.0;     // ��������
    
    sMcFmt11_f  *pf = (sMcFmt11_f*)psFrame;
    sMcFmt11    *pu = (sMcFmt11*)psUser;
    
     // �û��ൽ֡��
    if(MC_TRANS_U2F == eTrans)
    {
        #ifdef MC_DBG
        MCDBG("emc_trans_sX7() u2f  ePrec =%d dValue =%f", pu->ePrec, pu->dValue);
        #endif

        dTmp = pu->dValue;
        
        switch(pu->ePrec)
        {
            case MC_PREC_P4:    
                {
                    if(dTmp == 0.0 || 
                      (dTmp >=  10000.0 && dTmp <=  99999990000.0) ||
                      (dTmp <= -10000.0 && dTmp >= -99999990000.0))
                      {
                          modf(dTmp/10000, &dZhengshu);
                          sign = nmc_get_double_sign(dZhengshu);
                          vmc_set_double_sign(&dZhengshu, 1);
     
                          ucS  = sign;
                          ucG1 = 0;
                          ucG2 = 0;
                          ucG3 = 0;
                      }
                      else
                      {
                          #ifdef MC_DBG
                          MCDBG("emc_trans_sX7() para MC_PREC_P4 is out of range!");
                          #endif
                          return MC_ERR_OUTRNG;
                      } 
                }
                break;
                
            case MC_PREC_P3:    
                {
                    if(dTmp == 0.0 || 
                      (dTmp >=  1000.0 && dTmp <=  9999999000.0) ||
                      (dTmp <= -1000.0 && dTmp >= -9999999000.0))
                      {
                          modf(dTmp/1000, &dZhengshu);
                          sign = nmc_get_double_sign(dZhengshu);
                          vmc_set_double_sign(&dZhengshu, 1);
     
                          ucS  = sign;
                          ucG1 = 1;
                          ucG2 = 0;
                          ucG3 = 0;
                      }
                      else
                      {
                          #ifdef MC_DBG
                          MCDBG("emc_trans_sX7() para MC_PREC_P4 is out of range!");
                          #endif
                          return MC_ERR_OUTRNG;
                      } 
                }
                break;
            
            case MC_PREC_P2:    
                {
                    if(dTmp == 0.0 || 
                      (dTmp >=  100.0 && dTmp <=  999999900.0) ||
                      (dTmp <= -100.0 && dTmp >= -999999900.0))
                      {
                          modf(dTmp/100, &dZhengshu);
                          sign = nmc_get_double_sign(dZhengshu);
                          vmc_set_double_sign(&dZhengshu, 1);
     
                          ucS  = sign;
                          ucG1 = 0;
                          ucG2 = 1;
                          ucG3 = 0;
                      }
                      else
                      {
                          #ifdef MC_DBG
                          MCDBG("emc_trans_sX7() para MC_PREC_P4 is out of range!");
                          #endif
                          return MC_ERR_OUTRNG;
                      } 
                }
                break;
            
            case MC_PREC_P1:    
                {
                    if(dTmp == 0.0 || 
                      (dTmp >=  10.0 && dTmp <=  99999990.0) ||
                      (dTmp <= -10.0 && dTmp >= -99999990.0))
                      {
                          modf(dTmp/10, &dZhengshu);
                          sign = nmc_get_double_sign(dZhengshu);
                          vmc_set_double_sign(&dZhengshu, 1);
     
                          ucS  = sign;
                          ucG1 = 1;
                          ucG2 = 1;
                          ucG3 = 0;
                      }
                      else
                      {
                          #ifdef MC_DBG
                          MCDBG("emc_trans_sX7() para MC_PREC_P4 is out of range!");
                          #endif
                          return MC_ERR_OUTRNG;
                      } 
                }
                break;
                
            case MC_PREC_P0:    
                {
                    if(dTmp == 0.0 || 
                      (dTmp >=  1.0 && dTmp <=  9999999.0) ||
                      (dTmp <= -1.0 && dTmp >= -9999999.0))
                      {
                          modf(dTmp, &dZhengshu);
                          sign = nmc_get_double_sign(dZhengshu);
                          vmc_set_double_sign(&dZhengshu, 1);
     
                          ucS  = sign;
                          ucG1 = 0;
                          ucG2 = 0;
                          ucG3 = 1;
                      }
                      else
                      {
                          #ifdef MC_DBG
                          MCDBG("emc_trans_sX7() para MC_PREC_P0 is out of range!");
                          #endif
                          return MC_ERR_OUTRNG;
                      } 
                }
                break;            

            case MC_PREC_N1:    
                {
                    if(dTmp == 0.0 || 
                      (dTmp >=  0.1 && dTmp <=  999999.9) ||
                      (dTmp <= -0.1 && dTmp >= -999999.9))
                      {
                          modf(dTmp * 10, &dZhengshu);
                          sign = nmc_get_double_sign(dZhengshu);
                          vmc_set_double_sign(&dZhengshu, 1);
     
                          ucS  = sign;
                          ucG1 = 1;
                          ucG2 = 0;
                          ucG3 = 1;
                      }
                      else
                      {
                          #ifdef MC_DBG
                          MCDBG("emc_trans_sX7() para MC_PREC_N1 is out of range!");
                          #endif
                          return MC_ERR_OUTRNG;
                      } 
                }
                break;  
                
            case MC_PREC_N2:    
                {
                   if(dTmp == 0.0 || 
                     (dTmp >=  0.01 && dTmp <=  99999.99) ||
                     (dTmp <= -0.01 && dTmp >= -99999.99))
                     {
                         modf(dTmp * 100, &dZhengshu);
                         sign = nmc_get_double_sign(dZhengshu);
                         vmc_set_double_sign(&dZhengshu, 1);
    
                         ucS  = sign;
                         ucG1 = 0;
                         ucG2 = 1;
                         ucG3 = 1;
                     }
                     else
                     {
                         #ifdef MC_DBG
                         MCDBG("emc_trans_sX7() para MC_PREC_N2 is out of range!");
                         #endif
                         return MC_ERR_OUTRNG;
                     } 
                }
                break;  
                
            case MC_PREC_N3:    
                {
                    if(dTmp == 0.0 || 
                      (dTmp >=  0.001 && dTmp <=  9999.999) ||
                      (dTmp <= -0.001 && dTmp >= -9999.999))
                      {
                          modf(dTmp * 1000, &dZhengshu);
                          sign = nmc_get_double_sign(dZhengshu);
                          vmc_set_double_sign(&dZhengshu, 1);
     
                          ucS  = sign;
                          ucG1 = 1;
                          ucG2 = 1;
                          ucG3 = 1;
                      }
                      else
                      {
                          #ifdef MC_DBG
                          MCDBG("emc_trans_sX7() para MC_PREC_N3 is out of range!");
                          #endif
                          return MC_ERR_OUTRNG;
                      } 
                }
            
                break;  

            default:
                #ifdef MC_DBG
                MCDBG("emc_trans_sX7() para ePrec is out of range!,%d",pu->ePrec);
                #endif
                return MC_ERR_OUTRNG;
                //break;
        }

        ucSG123 = ucS | (ucG1 << 1) | (ucG2 << 2) | (ucG3 << 3);

        char bcd[8] = {0};
        sprintf(bcd, "%07.0lf\n", dZhengshu);

        pf->BCD_0 = bcd[index - 0] - '0';
        pf->BCD_1 = bcd[index - 1] - '0';
        pf->BCD_2 = bcd[index - 2] - '0';
        pf->BCD_3 = bcd[index - 3] - '0';
        pf->BCD_4 = bcd[index - 4] - '0';
        pf->BCD_5 = bcd[index - 5] - '0';
        pf->BCD_6 = bcd[index - 6] - '0';
        pf->SG123 = ucSG123;

    }
    // ֡�ൽ�û���
    else if(MC_TRANS_F2U == eTrans)
    {
        bcd[0]  = (UINT8) pf->BCD_0;
        bcd[1]  = (UINT8) pf->BCD_1;
        bcd[2]  = (UINT8) pf->BCD_2;
        bcd[3]  = (UINT8) pf->BCD_3;
        bcd[4]  = (UINT8) pf->BCD_4;
        bcd[5]  = (UINT8) pf->BCD_5;
        bcd[6]  = (UINT8) pf->BCD_6;
        
        ucSG123 = pf->SG123;
        sign = (ucSG123 & 0x01) ? -1 : 1;
        ucG1 = (ucSG123 & 0x02) ?  1 : 0;
        ucG2 = (ucSG123 & 0x04) ?  1 : 0;
        ucG3 = (ucSG123 & 0x08) ?  1 : 0;
        
        for(i = 0; i < 7; i++)
        {
            if(bcd[i] > 9)
            {
                 #ifdef MC_DBG
                 MCDBG("emc_trans_sX7() bcd is out of range");
                 #endif
                 return MC_ERR_OUTRNG;
            }
        }

        for(i = 0; i < 7; i++)
        {
            valid += bcd[i] * nmc_pow(i);
        }


        if(ucG3 == 0)
        {
            if(ucG2 == 0 && ucG1 == 0)
            {
                dTmp = 10000.0;  // 4.0
                pu->ePrec = MC_PREC_P4;
            }

            if(ucG2 == 0 && ucG1 == 1)
            {
                dTmp = 1000.0;   // 3.0
                pu->ePrec = MC_PREC_P3;
            }

            if(ucG2 == 1 && ucG1 == 0)
            {
                dTmp = 100.0;    // 2.0
                pu->ePrec = MC_PREC_P2;

            }

            if(ucG2 == 1 && ucG1 == 1)
            {
                dTmp = 10.0;     // 1.0
                pu->ePrec = MC_PREC_P1;
            }
        }
        else
        {
            if(ucG2 == 0 && ucG1 == 0)
            {
                 dTmp = 1.0;     // 0.0
                 pu->ePrec = MC_PREC_P0;
            }

            if(ucG2 == 0 && ucG1 == 1)
            {
                 dTmp = 0.1;   // -1.0
                 pu->ePrec = MC_PREC_N1;
            }

            if(ucG2 == 1 && ucG1 == 0)
            {
                 dTmp = 0.01;  // -2.0 
                 pu->ePrec = MC_PREC_N2;
            }

            if(ucG2 == 1 && ucG1 == 1)
            {
                dTmp = 0.001;
                pu->ePrec = MC_PREC_N3;
            }
        }

        pu->dValue = sign * valid * dTmp;
    }
    else
    {
        #ifdef MC_DBG
        MCDBG("emc_trans_sX7() para error!");
        #endif
        return MC_ERR_PARA;
    }
        
    return MC_OK;
}

/*****************************************************************************
 �� �� ��  : emc_trans_ip
 ��������  : IP��ַת������
 �������  : eMcTrans eTrans  
             void* pUser      
             void* pFrame     
             UINT16* pusLen   
 �������  : ��
 �� �� ֵ  : 
 ���ú���  : 
 ��������  : 
 
 �޸���ʷ      :
  1.��    ��   : 2013��11��6��
    ��    ��   : liming
    �޸�����   : �����ɺ���

*****************************************************************************/
eMcErr emc_trans_ip(eMcTrans eTrans, void* pUser, void* pFrame, UINT16* pusLen)
{
    sMcIp   *pu = (sMcIp*)pUser;
    sMcIp_f *pf = (sMcIp_f*)pFrame;
    INT32     i = 0;

    if(!pUser || !pFrame || !pusLen)
    {
        #ifdef MC_DBG
        MCDBG("emc_trans_ip() para pointer is null!");
        #endif
        return MC_ERR_NULL;
    }

     // �û��ൽ��֡��
    if(MC_TRANS_U2F == eTrans)
    {   
        // ucVersion
        switch(pu->eVersion)
        {
            case MC_IP_V4:
            pf->ucVersion = 1;
            break;

            case MC_IP_V6:
            pf->ucVersion = 2;
            break;

            default:
            #ifdef MC_DBG
            MCDBG("emc_trans_ip() eVersion is error!");
            #endif
            return MC_ERR_PARA;
            //break;
        }

        // ip
        for(i = 0; i < MC_IP_LEN; i++)
        {
            pf->ip[i] = pu->ip[MC_IP_LEN - i - 1];
        }
        
    }
    // ��֡�ൽ�û���
    else
    {   
        // ucVersion
        switch(pf->ucVersion)
        {
            case 1:
            pu->eVersion = MC_IP_V4;
            break;

            case 2:
            pu->eVersion = MC_IP_V6;
            break;

            default:
            #ifdef MC_DBG
            MCDBG("emc_trans_ip() ucVersion is error %d!", pf->ucVersion);
            #endif
            return MC_ERR_PARA;
            //break;
        }

        // ip
        for(i = 0; i < MC_IP_LEN; i++)
        {
            pu->ip[i] = pf->ip[MC_IP_LEN - i - 1];
        }
    }

    * pusLen = MC_IP_LEN + 1;
    return MC_OK;
}

/*****************************************************************************
 �� �� ��  : emc_trans_afn00f1
 ��������  : MCMD_AFN_0_F1_ALL_OK_DENY ��Ӧ�����ݽṹת������
 �������  : eMcTrans eTrans       
                
 �������  : eMcResCode *peResCode  
             UINT8* pucResCode  
             UINT16* pusLen  ��֡����ֳ�
 �� �� ֵ  : 
 ���ú���  : 
 ��������  : 
 
 �޸���ʷ      :
  1.��    ��   : 2013��11��1��
    ��    ��   : liming
    �޸�����   : �����ɺ���

*****************************************************************************/
eMcErr emc_trans_afn00f1(eMcTrans eTrans, void* pUser, void* pFrame, UINT16* pusLen)
{   
    UINT8      ucResCode   = 0;
    eMcResCode eResCode    = MC_RES_OK;
    eMcResCode *pU         = NULL;
    UINT8      *pF         = NULL;
    
    if(!pUser || !pFrame || !pusLen)
    {
        #ifdef MC_DBG
        MCDBG("emc_trans_afn00f1() para pointer is null!");
        #endif
        return MC_ERR_NULL;
    }

    pU = (eMcResCode *)pUser;
    pF = (UINT8 *)pFrame;
    

    // �û��ൽ��֡��
    if(MC_TRANS_U2F == eTrans)
    {   
        eResCode = *pU;
        switch(eResCode)   
        {
           case MC_RES_OK:
           case MC_RES_NONE:
           case MC_RES_NOT_READY:
           case MC_RES_REMOVE:
           case MC_RES_DATA_OTRNG:
           case MC_RES_PARA_OTRNG:
           case MC_RES_NOT_SAME:          
           case MC_RES_NOT_SUPT:
           case MC_RES_DENY:  
               break;
               
           default:
               #ifdef MC_DBG
               MCDBG("emc_trans_afn00f1() eResCode is error %d", eResCode);
               #endif
               return MC_ERR_PARA;
               //break;
        }

        ucResCode  = (UINT8)eResCode;
        *pF        = ucResCode;
    }
    // ��֡�ൽ�û���
    else
    {
        ucResCode = *pF;
        switch(ucResCode)   
        {
           case MC_RES_OK:
           case MC_RES_NONE:
           case MC_RES_NOT_READY:
           case MC_RES_REMOVE:
           case MC_RES_DATA_OTRNG:
           case MC_RES_PARA_OTRNG:
           case MC_RES_NOT_SAME:          
           case MC_RES_NOT_SUPT:
           case MC_RES_DENY:  
               break;
               
           default:
               #ifdef MC_DBG
               MCDBG("emc_trans_afn00f1() ucResCode is error %d", ucResCode);
               #endif
               return MC_ERR_PARA;
               //break;
        }
        
        eResCode = (eMcResCode)ucResCode;
        *pU      = eResCode;
    }

    // �����֡����ֳ�
    *pusLen = sizeof(UINT8);
    return MC_OK;
}

/*****************************************************************************
 �� �� ��  : emcTrans_OneByOne
 ��������  : MCMD_AFN_0_F2_ONE_BY_ONE ��Ӧ�����ݽṹת������
 �������  : eMcTrans eTrans       
                
 �������  : eMcResCode *peResCode  
             UINT8* pucResCode  
             UINT16* pusLen  ��֡����ֳ�
 �� �� ֵ  : 
 ���ú���  : 
 ��������  : 
 
 �޸���ʷ      :
  1.��    ��   : 2013��11��1��
    ��    ��   : liming
    �޸�����   : �����ɺ���

*****************************************************************************/
eMcErr emcTrans_OneByOne(eMcTrans eTrans,void* psUser, void* psFrame, UINT16* pusfLen)
{
    sMcOneByOne_f *psOneByOne_f = (sMcOneByOne_f *)psFrame;
    sMcOnebyOne   *psOneByOne_u = (sMcOnebyOne   *)psUser;
    INT32       i         = 0;
    INT32       j         = 0;
    INT32       k         = 0;
    INT32       fi        = 0;
    INT32       pi        = 0;
    eMcErr      eRet      = MC_OK;
    INT32       nNum      = 0;  
    INT32       nDaDtNum  = 0;      // ��װpackbase����Ϣ��ʶ��64�����ݵ�Ԫ����ܸ���
    INT32       nDaDtPos  = 0;      // ÿ��Ӧ����packbase����Ϣ��ʶ�������
    UINT16      usCMD     = 0;
    UINT16      usPn      = 0;
    UINT8       ucFn      = 0;
    eMcmd       eCmd      = MCMD_AFN_F_UNKOWN;
    eMcAFN      eAFN      = MC_AFN_NULL;
    eMcAFN      eAFNCmd   = MC_AFN_NULL;
    eMcResCode  eResCode  = MC_RES_OK;
    BOOL        bFindDaDt = FALSE;  // �Ƿ��ҵ�֮ǰ���ڵ���
    BOOL        bP0       = FALSE;
    INT32       nCyc      = 0;
    sMcPnFn     sPnFn;
    UINT8*      pMem      = NULL;
    sMcFnPnErr* psFnPnErr = NULL;
    #define     MT_TEAM_MAX  (50)   // ���ܵ��������

    if(!psFrame || !psUser || !pusfLen)
    {
        #ifdef MC_DBG
        MCDBG("emcTrans_OneByOne() pointer is null");
        #endif
        return MC_ERR_NULL;
    }

    memset(&(sPnFn), 0, sizeof(sMcPnFn));

    // ֡��תΪ�û���
    if(MC_TRANS_F2U == eTrans)
    {
        // ����ʱ����Ӧ�ò����ݳ���
        nNum = (int)*pusfLen;
        nNum -= sizeof(UINT8);
        nNum /= sizeof(sMcOne_f); // ���㺬��ȷ�Ϸ��ϸ���

        if(nNum > MC_FN_MAX)
        {
            #ifdef MC_DBG
            MCDBG("emcTrans_OneByOne() MC_ERR_OUTRNG");
            #endif
            return MC_ERR_OUTRNG;
        }

        eAFN = (eMcAFN)psOneByOne_f->ucAFN;
        psOneByOne_u->eAFN = eAFN;
        for(i = 0; i < nNum; i++)
        {
            switch(psOneByOne_f->sOne[i].ucErr)   
            {
               case MC_RES_OK:
               case MC_RES_NONE:
               case MC_RES_NOT_READY:
               case MC_RES_REMOVE:
               case MC_RES_DATA_OTRNG:
               case MC_RES_NOT_SAME:          
               case MC_RES_NOT_SUPT:
               case MC_RES_DENY:  
                   break;
                   
               default:
                   #ifdef MC_DBG
                   MCDBG("emc_trans_afn00f1() ucResCode is error %d", psOneByOne_f->sOne[i].ucErr);
                   #endif
                   return MC_ERR_PARA;
                   //break;
            }

            eResCode = (eMcResCode)(psOneByOne_f->sOne[i].ucErr);
            
            eRet = emc_dadt_to_pnfn(&(psOneByOne_f->sOne[i].sDaDt), &sPnFn);
            if(eRet != MC_OK)
            {   
                #ifdef MC_DBG
                MCDBG("Error:emc_dadt_to_pnfn() error = %d %s\n", eRet, smcGetErr(eRet));
                #endif
                return eRet;
            }

            // �Ƿ�Ϊp0�����
            bP0 = bmc_is_p0(sPnFn.usPn);
            if(TRUE == bP0)
            {
                nCyc = 1;
            }
            else
            {
                nCyc = MC_PN_INDEX_MAX;
            }
            
            for(pi = 0; pi < nCyc; pi++)
            {
                if(MC_PN_NONE != sPnFn.usPn[pi])
                {
                    for(fi = 0; fi < MC_FN_INDEX_MAX; fi++)
                    {
                        if(MC_FN_NONE != sPnFn.ucFn[fi])
                        { 
                            usCMD = (UINT16)((eAFN << 8) | sPnFn.ucFn[fi]);
                            eCmd  = (eMcmd)usCMD; 
                            psOneByOne_u->sOne[j].eResCode = eResCode;
                            psOneByOne_u->sOne[j].usPn = sPnFn.usPn[pi];
                            psOneByOne_u->sOne[j].eCmd = eCmd;
                            j++;
                        }
                    }
                }            
            }
        }

        psOneByOne_u->ucNum = j;
        nDaDtNum = nNum;
    }
    else 
    // �û���תΪ֡��
    {
        eAFN = psOneByOne_u->eAFN;
        psOneByOne_f->ucAFN  = (UINT8)psOneByOne_u->eAFN;

        pMem = (UINT8*)malloc(sizeof(sMcFnPnErr) * MT_TEAM_MAX);
        if(!pMem)
        {
            #ifdef MC_DBG
            MCDBG("emcTrans_OneByOne() MC_ERR_IO");
            #endif
            return MC_ERR_IO;
        }
            
        psFnPnErr = (sMcFnPnErr*)pMem;
            
        for(i = 0; i < psOneByOne_u->ucNum; i++)
        {
            // �жϸ������Ƿ�����AFN��������
            eAFNCmd = eMcGetCmdAfn(psOneByOne_u->sOne[i].eCmd);
            if(eAFNCmd != eAFN)  
            {
                #ifdef MC_DBG
                MCDBG("emcTrans_OneByOne() cmd is not is a same Afn ");
                MCDBG("eAFNCmd = %d", eAFNCmd);
                MCDBG("eAFN = %d", eAFN);
                MCDBG("eCmd[%d] = %04X", i,  psOneByOne_u->sOne[i].eCmd);
                #endif
                MC_FREE(pMem);
                return MC_ERR_TEAM;
            }

            usPn      = psOneByOne_u->sOne[i].usPn;
            ucFn      = ucMcGetCmdFn(psOneByOne_u->sOne[i].eCmd);
            eResCode  = psOneByOne_u->sOne[i].eResCode;

            /*
                �жϸúϷ������ݵ�Ԫ��ʶ,�����ݵ�Ԫ�Ƿ��Ѿ�����Ӧ��λ�� psBasePack
                ����ظ�,���߸���ǰ��,Da2 �벻ͬ��Dt2���, 
                �������ͬ�ı�ʶ�����ݵ�Ԫ��,����nDaTaNum�ĸ���
                
            */
            nDaDtPos = nDaDtNum;
            // ��ʼ��PnFn��
            for(k = 0; k < 8; k++)
            {
                psFnPnErr[nDaDtPos].sPnFn.ucFn[k] = MC_FN_NONE;
                psFnPnErr[nDaDtPos].sPnFn.usPn[k] = MC_PN_NONE;
            }
            
            if(nDaDtPos > MT_TEAM_MAX)
            {
                #ifdef MC_DBG
                MCDBG("emcTrans_OneByOne() MC_TEAM_MAX too small");
                #endif
                MC_FREE(pMem);
                return MC_ERR_OUTRNG;
            }
            
            for(j = 0; j < nDaDtNum; j++)
            {
                // �ҵ���nDataPos���ҵ���λ��
                // ���ж�Pn�Ƿ���ͬһ��
                UINT8 ucTeamPn     = 0xFF;
                UINT8 ucTeamPnBase = 0xFF;
                ucTeamPn     = ucmc_get_pn_team(usPn);
                ucTeamPnBase = ucmc_get_pn8_team(psFnPnErr[j].sPnFn.usPn);
                
                if(ucTeamPn == ucTeamPnBase)
                {
                    // ���ж�Fn�Ƿ�����ͬһ����
                    UINT8 ucTeamFn     = 0xFF;
                    UINT8 ucTeamFnBase = 0xFF;
                    ucTeamFn     = ucmc_get_fn_team(ucFn);
                    ucTeamFnBase = ucmc_get_fn8_team(psFnPnErr[j].sPnFn.ucFn);

                    if(ucTeamFn == ucTeamFnBase)
                    {
                        BOOL bInFn8 = bmc_in_fn8(ucFn, psFnPnErr[j].sPnFn.ucFn);
                        if((eResCode == psFnPnErr[j].eResCode) && (TRUE == bInFn8))
                        {
                            bFindDaDt = TRUE;
                            nDaDtPos  = j;
                            break;
                        }   
                    }
                }
            }

            // δ�ҵ���nDaTaNum++
            if(FALSE == bFindDaDt)
            {
                nDaDtNum  += 1; // ����һ��  
            }
            
            // ���� DaTa�鼰���ݵ�Ԫ
            if(0 == usPn)
            {
                pi = 0;
                for(k = 0; k < 8; k++)
                {
                    psFnPnErr[nDaDtPos].sPnFn.usPn[k] = 0;
                }
            }
            else
            {
                pi = (usPn - 1) % 8; 
                psFnPnErr[nDaDtPos].sPnFn.usPn[pi] = usPn;
            }
          
            fi = (ucFn - 1) % 8;
            psFnPnErr[nDaDtPos].sPnFn.ucFn[fi] = ucFn;

            // ���ݵ�Ԫ
            psFnPnErr[j].eResCode = eResCode;
            
            // ����δ�ҵ�״̬
            bFindDaDt = FALSE;
        }

        //sMcFnPnErr ʵ�� sMcOne_f ת��
        for(i = 0; i < nDaDtNum; i++)
        {
            eRet = emc_pnfn_to_dadt(&psFnPnErr[i].sPnFn, &(psOneByOne_f->sOne[i].sDaDt));
            if(eRet != MC_OK)
            {
                 #ifdef MC_DBG
                 MCDBG("Error:emc_pnfn_to_dadt() error = %d %s\n", eRet, smcGetErr(eRet));
                 #endif
                 MC_FREE(pMem);
                 return eRet;
            }
                    
            // right or error
            psOneByOne_f->sOne[i].ucErr = psFnPnErr[i].eResCode;
        }

        MC_FREE(pMem);
     }

    // ������֡����ֽڳ���
    *pusfLen = sizeof(UINT8) + sizeof(sMcOne_f) * nDaDtNum;
    return MC_OK;
}   

/*****************************************************************************
 �� �� ��  : emc_trans_afn01f5
 ��������  : ���ݽṹת������
 ��Ӧ����  : MCMD_AFN_1_F5_DATA_CLEAR
 ����˵��  : ������������ AFN Ӧ��ΪMC_AFN_13_ASKR 
             ��ʵʱ���ݵ����ݵ�Ԫ��ʶ
 �������  : eMcTrans eTrans  
             void* pUser      
             void* pFrame     
 �������  : UINT16* pusLen  ���֡����ֽ���
 �� �� ֵ  : 
 ���ú���  : 
 ��������  : 
 
 �޸���ʷ      :
  1.��    ��   : 2013��11��5��
    ��    ��   : liming
    �޸�����   : �����ɺ���

*****************************************************************************/
eMcErr emc_trans_afn01f5(eMcTrans eTrans, void* pUser, void* pFrame, UINT16* pusLen)
{   
    eMcErr        eRet = MC_OK;
    eMcAFN        eAfn = MC_AFN_NULL;
    UINT8     ucNumCmd = 0;
    UINT8    ucNumDaDt = 0;
    sMcAfn01f5     *pu = NULL;
    sMcAfn01f5_f   *pf = NULL;
    
    if(!pUser || !pFrame || !pusLen)
    {
        #ifdef MC_DBG
        MCDBG("emc_trans_afn01f5() para pointer is null!");
        #endif
        return MC_ERR_NULL;
    }

    pu = (sMcAfn01f5   *)pUser;
    pf = (sMcAfn01f5_f *)pFrame;
    
    // �û��ൽ��֡��
    if(MC_TRANS_U2F == eTrans)
    {   
        eAfn = eMcGetCmdAfn(pu->sCmdPn[0].eCmd);
        if(MC_AFN_13_ASKR != eAfn)
        {
            #ifdef MC_DBG
            MCDBG("emc_trans_afn01f5() afn is not MC_AFN_13_ASKR  %d!", eAfn);
            #endif
            return MC_ERR_PARA; 
        }

        eRet = emc_cmdpn_to_dadt(MC_AFN_13_ASKR, &(pf->sDaDt[0]), &ucNumDaDt, &(pu->sCmdPn[0]), pu->ucNum);
        if(MC_OK != eRet)
        {
            #ifdef MC_DBG
            MCDBG("emc_trans_afn01f5() emc_cmdpn_to_dadt() error %d!", eRet);
            #endif
            return eRet;
        }

        pf->ucNum = ucNumDaDt;
    }
    // ��֡�ൽ�û���
    else
    {   
        eRet = emc_dadt_to_cmdpn(MC_AFN_13_ASKR, &(pf->sDaDt[0]), pf->ucNum, &(pu->sCmdPn[0]), &ucNumCmd);
        if(MC_OK != eRet)
        {
            #ifdef MC_DBG
            MCDBG("emc_trans_afn01f5() emc_cmdpn_to_dadt() error %d!", eRet);
            #endif
            return eRet;
        }
        
        ucNumDaDt = pf->ucNum;
        pu->ucNum = ucNumCmd;
    }

    // �����֡����ֳ�
    *pusLen = sizeof(sMcDaDt) * ucNumDaDt + 1;
    return MC_OK;
}

/*****************************************************************************
 �� �� ��  : emc_trans_afn04f1
 ��������  : ���ݽṹת������
 ��Ӧ����  : MCMD_AFN_4_F1_CON_UP_CFG
 �������  : eMcTrans eTrans  
             void* pUser      
             void* pFrame     
 �������  : UINT16* pusLen  ���֡����ֽ���
 �� �� ֵ  : 
 ���ú���  : 
 ��������  : 
 
 �޸���ʷ      :
  1.��    ��   : 2013��11��5��
    ��    ��   : liming
    �޸�����   : �����ɺ���

*****************************************************************************/
eMcErr emc_trans_afn04f1(eMcTrans eTrans, void* pUser, void* pFrame, UINT16* pusLen)
{   
    UINT8       bs8Con = 0;
    sMcUpCfg      *pu  = NULL;
    sMcUpCfg_f    *pf  = NULL;

    if(!pUser || !pFrame || !pusLen)
    {
        #ifdef MC_DBG
        MCDBG("emc_trans_afn04f1() para pointer is null!");
        #endif
        return MC_ERR_NULL;
    }

    pu = (sMcUpCfg   *)pUser;
    pf = (sMcUpCfg_f *)pFrame;
    
    // �û��ൽ��֡��
    if(MC_TRANS_U2F == eTrans)
    {
        pf->ucPermitDelayM = pu->ucPermitDelayM;
        pf->ucHeartBeat    = pu->ucHeartBeat;
        pf->ucSWTS1        = (pu->usWaitTimeoutS & 0xFF);
        pf->ucSWTS2        = ((pu->usWaitTimeoutS & 0x0F00) >> 8);
        pf->ucSWTS2       |= ((pu->ucReSendTimes & 0x03) << 4);
        
        if(pu->bPermitRt == TRUE)
        {
            bs8Con |= 0x01;
        }

        if(pu->bPermitTk == TRUE)
        {
            bs8Con |= 0x02;
        }

        if(pu->bPermitEv == TRUE)
        {
            bs8Con |= 0x04;
        }

        pf->bs8Con   = bs8Con;
    }
    // ��֡�ൽ�û���
    else
    {
        pu->ucPermitDelayM   = pf->ucPermitDelayM;
        pu->ucHeartBeat      = pf->ucHeartBeat;
        pu->usWaitTimeoutS   = (((pf->ucSWTS2 & 0x0F) << 8)  | pf->ucSWTS1);
        pu->ucReSendTimes    = (pf->ucSWTS2 >> 4) & 0x03;
        pu->bPermitRt        = ((pf->bs8Con & 0x01) ? TRUE : FALSE);
        pu->bPermitTk        = ((pf->bs8Con & 0x02) ? TRUE : FALSE);
        pu->bPermitEv        = ((pf->bs8Con & 0x04) ? TRUE : FALSE);
    }

    // �����֡����ֳ�
    *pusLen = sizeof(sMcUpCfg_f);
    return MC_OK;
}

/*****************************************************************************
 �� �� ��  : emc_trans_afn04f2
 ��������  : ���ݽṹת������
 ��Ӧ����  : MCMD_AFN_4_F2_MST_PARA
 �������  : eMcTrans eTrans  
             void* pUser      
             void* pFrame     
 �������  : UINT16* pusLen  ���֡����ֽ���
 �� �� ֵ  : 
 ���ú���  : 
 ��������  : 
 ʵ��˵��  : �������������������
 
 �޸���ʷ      :
  1.��    ��   : 2013��11��5��
    ��    ��   : liming
    �޸�����   : �����ɺ���

*****************************************************************************/
eMcErr emc_trans_afn04f2(eMcTrans eTrans, void* pUser, void* pFrame, UINT16* pusLen)
{  
    sMcAfn04f2   *pu = NULL;
    sMcAfn04f2_f *pf = NULL;
    INT32           i = 0;
    UINT16   usLenTmp = 0;
    UINT8         ucN = 0;
    UINT8   ucDaDtNum = 0;
    eMcErr       eRet = MC_OK;
    sMcDaDt     sDaDt;
    sMcIp_f      sIpF;
    sMcIp        sIpU;
    
    if(!pUser || !pFrame || !pusLen)
    {
        #ifdef MC_DBG
        MCDBG("emc_trans_afn04f2() para pointer is null!");
        #endif
        return MC_ERR_NULL;
    }
   
    pu = (sMcAfn04f2*)pUser;
    pf = (sMcAfn04f2_f *)pFrame;
    memset(&sDaDt, 0, sizeof(sMcDaDt));
    memset(&sIpF,  0, sizeof(sMcIp_f));
    memset(&sIpU,  0, sizeof(sMcIp));

    // �û��ൽ��֡��
    if(MC_TRANS_U2F == eTrans)
    {
        // ucN
        pf->ucN = pu->ucN;
        ucN = pf->ucN;

        // sOne
        for(i = 0; i < ucN; i++)
        {
            // id
            pf->sOne[i].ucID = pu->sOne[i].ucID;
            
            // bValid
            pf->sOne[i].bs8Valid = (pu->sOne[i].bValid == TRUE ? 1:0);

            // sCmdPn
            if(pu->sOne[i].ucNoNum > 8)
            {
               #ifdef MC_DBG
               MCDBG("emc_trans_afn04f2() para ucNoNum is out of range! = %d", pu->sOne[i].ucNoNum);
               #endif
               return MC_ERR_OUTRNG;
            }
            
            sDaDt = pf->sOne[i].sDaDt;
            eRet = emc_cmdpn_to_dadt(MC_AFN_04_SETP, &sDaDt, &ucDaDtNum, 
                                    &(pu->sOne[i].sCmdPn[0]), pu->sOne[i].ucNoNum);
            if(MC_OK != eRet)
            {
                #ifdef MC_DBG
                MCDBG("emc_trans_afn04f2() emc_cmdpn_to_dadt() error %d!", eRet);
                #endif
                return eRet;
            }

            // sMainIP
            sIpU = pu->sOne[i].sMainIP;
            eRet = emc_trans_ip(eTrans, &sIpU, &sIpF, &usLenTmp);
            if(eRet != MC_OK)
            {
                #ifdef MC_DBG
                MCDBG("emc_trans_afn04f2() emc_trans_ip() error %d!", eRet);
                #endif
                return eRet;
            }
            
            pf->sOne[i].sMainIP = sIpF;

            // usMainPort
            pf->sOne[i].usMainPort = pu->sOne[i].usMainPort;

            // sBackIP
            sIpU = pu->sOne[i].sBackIP;
            eRet = emc_trans_ip(eTrans, &sIpU, &sIpF, &usLenTmp);
            if(eRet != MC_OK)
            {
                #ifdef MC_DBG
                MCDBG("emc_trans_afn04f2() emc_trans_ip() error %d!", eRet);
                #endif
                return eRet;
            }
            
            pf->sOne[i].sBackIP = sIpF;

            // usBackPort
            pf->sOne[i].usBackPort = pu->sOne[i].usBackPort;

            // ucascAPN
            memcpy(pf->sOne[i].ucascAPN, pu->sOne[i].ucascAPN, 16);
            memcpy(pf->sOne[i].usr, pu->sOne[i].usr, 32);
            memcpy(pf->sOne[i].pwd, pu->sOne[i].pwd, 32);
        }
    }
    // ��֡�ൽ�û���
    else if(MC_TRANS_F2U == eTrans)
    {
        // ucN
        pu->ucN = pf->ucN;
        ucN = pf->ucN;

        // sOne
        for(i = 0; i < ucN; i++)
        {
           // id
            pu->sOne[i].ucID = pf->sOne[i].ucID;
            
            // bValid
            pu->sOne[i].bValid = (pf->sOne[i].bs8Valid & 0x01) ? TRUE : FALSE;


            // sCmdPn
            eRet = emc_dadt_to_cmdpn(MC_AFN_04_SETP, &sDaDt, 1, 
                                    &(pu->sOne[i].sCmdPn[0]), &ucDaDtNum);
            if(MC_OK != eRet)
            {
                #ifdef MC_DBG
                MCDBG("emc_trans_afn04f2() emc_dadt_to_cmdpn() error %d!", eRet);
                #endif
                return eRet;
            }

            pf->sOne[i].sDaDt = sDaDt;

            // sCmdPn
            pu->sOne[i].ucNoNum = ucDaDtNum;
            if(pu->sOne[i].ucNoNum > 8)
            {
               #ifdef MC_DBG
               MCDBG("emc_trans_afn04f2() para ucNoNum is out of range! = %d", pu->sOne[i].ucNoNum);
               #endif
               return MC_ERR_OUTRNG;
            }
            
            // sMainIP
            sIpF = pf->sOne[i].sMainIP;
            eRet = emc_trans_ip(eTrans, &sIpU, &sIpF, &usLenTmp);
            if(eRet != MC_OK)
            {
                #ifdef MC_DBG
                MCDBG("emc_trans_afn04f2() emc_trans_ip() error %d!", eRet);
                #endif
                return eRet;
            }
            
            pu->sOne[i].sMainIP = sIpU;

            // usMainPort
            pu->sOne[i].usMainPort = pf->sOne[i].usMainPort;

            // sBackIP
            sIpF = pf->sOne[i].sBackIP;
            eRet = emc_trans_ip(eTrans, &sIpU, &sIpF, &usLenTmp);
            if(eRet != MC_OK)
            {
                #ifdef MC_DBG
                MCDBG("emc_trans_afn04f2() emc_trans_ip() error %d!", eRet);
                #endif
                return eRet;
            }
            
            pu->sOne[i].sBackIP = sIpU;

            // usBackPort
            pu->sOne[i].usBackPort = pf->sOne[i].usBackPort;

            // ucascAPN
            memcpy(pu->sOne[i].ucascAPN, pf->sOne[i].ucascAPN, 16);
            memcpy(pu->sOne[i].usr, pf->sOne[i].usr, 32);
            memcpy(pu->sOne[i].pwd, pf->sOne[i].pwd, 32);
        }
    }
    else
    {
         #ifdef MC_DBG
         MCDBG("emc_trans_afn04f2() eTrans is out of range!");
         #endif
         return MC_ERR_OUTRNG;    
    }
   
    // �������
    *pusLen = sizeof(sMcMstParaOne_f) * ucN + sizeof(UINT8);
    return MC_OK;
}

/*****************************************************************************
 �� �� ��  : emc_trans_afn04f3
 ��������  : ���ݽṹת������
 ��Ӧ����  : MCMD_AFN_4_F3_CON_AUTH_PARA
 �������  : eMcTrans eTrans  
             void* pUser      
             void* pFrame     
 �������  : UINT16* pusLen  ���֡����ֽ���
 �� �� ֵ  : 
 ���ú���  : 
 ��������  : 
 
 �޸���ʷ      :
  1.��    ��   : 2013��11��5��
    ��    ��   : liming
    �޸�����   : �����ɺ���

*****************************************************************************/
eMcErr emc_trans_afn04f3(eMcTrans eTrans, void* pUser, void* pFrame, UINT16* pusLen)
{
    sMcAfn04f3      *pu  = NULL;
    sMcAfn04f3_f    *pf  = NULL;

    if(!pUser || !pFrame || !pusLen)
    {
        #ifdef MC_DBG
        MCDBG("emc_trans_afn04f3() para pointer is null!");
        #endif
        return MC_ERR_NULL;
    }

    pu = (sMcAfn04f3   *)pUser;
    pf = (sMcAfn04f3_f *)pFrame;

    // �û��ൽ��֡��
    if(MC_TRANS_U2F == eTrans)
    {
        pf->ucTypeID   = pu->ucTypeID;
        pf->usAuthPara = pu->usAuthPara;
    }
    // ��֡�ൽ�û���
    else
    {
        pu->ucTypeID   = pf->ucTypeID;
        pu->usAuthPara = pf->usAuthPara;
    }

    *pusLen = sizeof(sMcAfn04f3_f);
    return MC_OK;
}

/*****************************************************************************
 �� �� ��  : emc_trans_afn04f4
 ��������  : ���ݽṹת������
 ��Ӧ����  : MCMD_AFN_4_F4_TEAM_ADDR
 �������  : eMcTrans eTrans  
             void* pUser      
             void* pFrame     
 �������  : UINT16* pusLen  ���֡����ֽ���
 �� �� ֵ  : 
 ���ú���  : 
 ��������  : 
 
 �޸���ʷ      :
  1.��    ��   : 2013��11��5��
    ��    ��   : liming
    �޸�����   : �����ɺ���

*****************************************************************************/
eMcErr emc_trans_afn04f4(eMcTrans eTrans, void* pUser, void* pFrame, UINT16* pusLen)
{     
    sMcAfn04f4      *pU  = NULL;
    sMcAfn04f4_f    *pF  = NULL;

    if(!pUser || !pFrame || !pusLen)
    {
        #ifdef MC_DBG
        MCDBG("emc_trans_afn04f4() para pointer is null!");
        #endif
        return MC_ERR_NULL;
    }

    pU = (sMcAfn04f4   *)pUser;
    pF = (sMcAfn04f4_f *)pFrame;

    // �û��ൽ��֡��
    if(MC_TRANS_U2F == eTrans)
    {
        memcpy(pF, pU, sizeof(sMcAfn04f4_f));
    }
    // ��֡�ൽ�û���
    else
    {
        memcpy(pU, pF, sizeof(sMcAfn04f4_f));
    }
    
    *pusLen = sizeof(sMcAfn04f4_f);
    return MC_OK;
}

/*****************************************************************************
 �� �� ��  : emc_trans_afn04f5
 ��������  : ���ݽṹת������
 ��Ӧ����  : MCMD_AFN_4_F5_CON_IP_PORT
 �������  : eMcTrans eTrans  
             void* pUser      
             void* pFrame     
 �������  : UINT16* pusLen  ���֡����ֽ���
 �� �� ֵ  : 
 ���ú���  : 
 ��������  : 
 
 �޸���ʷ      :
  1.��    ��   : 2013��11��5��
    ��    ��   : liming
    �޸�����   : �����ɺ���

*****************************************************************************/
eMcErr emc_trans_afn04f5(eMcTrans eTrans, void* pUser, void* pFrame, UINT16* pusLen)
{     
    eMcErr           eRet = MC_OK;
    UINT16       usLenOut = 0;
    UINT16       usLenTmp = 0;
    sMcAfn04f5      *pu   = NULL;
    sMcAfn04f5_f    *pf   = NULL;
    UINT8           *pTmp = NULL;
    sMcIp_f        sIp_f;     
    
    if(!pUser || !pFrame || !pusLen)
    {
        #ifdef MC_DBG
        MCDBG("emc_trans_afn04f5() para pointer is null!");
        #endif
        return MC_ERR_NULL;
    }

    pu = (sMcAfn04f5   *)pUser;
    pf = (sMcAfn04f5_f *)pFrame;
    memset(&sIp_f, 0, sizeof(sMcIp_f));

    // �û��ൽ��֡��
    if(MC_TRANS_U2F == eTrans)
    {
        // usPort
        pf->usPort = pu->usPort;
        usLenOut = 2;

        // sConIp
        eRet = emc_trans_ip(eTrans, &(pu->sConIp), &sIp_f, &usLenTmp);
        if(eRet != MC_OK)
        {
            #ifdef MC_DBG
            MCDBG("emc_trans_afn04f5() emc_trans_ip() error %d!", eRet);
            #endif
            return eRet;
        }
        
        pf->sConIp = sIp_f;
        usLenOut += usLenTmp;

        // sMask
        eRet = emc_trans_ip(eTrans, &(pu->sMask), &sIp_f, &usLenTmp);
        if(eRet != MC_OK)
        {
            #ifdef MC_DBG
            MCDBG("emc_trans_afn04f5() emc_trans_ip() error %d!", eRet);
            #endif
            return eRet;
        }

        pf->sMask = sIp_f;
        usLenOut += usLenTmp;

        // sGateIp
        eRet = emc_trans_ip(eTrans, &(pu->sGateIp), &sIp_f, &usLenTmp);
        if(eRet != MC_OK)
        {
            #ifdef MC_DBG
            MCDBG("emc_trans_afn04f5() emc_trans_ip() error %d!", eRet);
            #endif
            return eRet;
        }
        
        pf->sGateIp = sIp_f;
        usLenOut += usLenTmp;

        // eDelegate
        switch(pu->eDelegate)
        {
            case MC_DELG_NULL:
                pf->ucDelegate = 0;
                break;
                
            case MC_DELG_HTTP:
                pf->ucDelegate = 1;
                break;
                
            case MC_DELG_SOCK4:
                pf->ucDelegate = 2;
                break;
                
            case MC_DELG_SOCK5:
                pf->ucDelegate = 3;
                break;

            default:
                #ifdef MC_DBG
                MCDBG("emc_trans_afn04f5() para eDelegate is error!");
                #endif
                return MC_ERR_PARA;
                //break;
        }
        
        usLenOut += 1;
        
        // sDelgIp
        eRet = emc_trans_ip(eTrans, &(pu->sDelgIp), &sIp_f, &usLenTmp);
        if(eRet != MC_OK)
        {
            #ifdef MC_DBG
            MCDBG("emc_trans_afn04f5() emc_trans_ip() error %d!", eRet);
            #endif
            return eRet;
        }
        
        pf->sDelgIp = sIp_f;
        usLenOut += usLenTmp;

        // usDelgPort
        pf->usDelgPort = pu->usDelgPort;
        usLenOut += 2;

        // eDelgLink
        if(MC_DELK_ANYONE == pu->eDelgLink)
        {
            pf->ucDelgLink = 0;
        }
        else if(MC_DELK_USRPWD == pu->eDelgLink)
        {
            pf->ucDelgLink = 1;
        }
        else
        {
            #ifdef MC_DBG
            MCDBG("emc_trans_afn04f5() eDelgLink para error %d!", pu->eDelgLink);
            #endif
            return MC_ERR_PARA;
        }
        
        usLenOut += 1;

        // bDlegUsr
        if(TRUE == pu->bDlegUsr && 0 == pu->ucDlegUsrLen)
        {
            #ifdef MC_DBG
            MCDBG("emc_trans_afn04f5() bDlegUsr ucDlegUsrLen error");
            #endif
            return MC_ERR_PARA;
        }

        // ucUsrLen
        pf->ucUsrLen = pu->ucDlegUsrLen;
        usLenOut += 1;

        // ucDlegUsr
        pTmp = (UINT8*)(&(pf->ucUsrLen) + 1);
        memcpy(pTmp, pu->ucDlegUsr, pu->ucDlegUsrLen);
        usLenOut += pu->ucDlegUsrLen;

        // bDlegPwd
        if(TRUE == pu->bDlegPwd && 0 == pu->ucDlegPwdLen)
        {
            #ifdef MC_DBG
            MCDBG("emc_trans_afn04f5() bDlegPwd ucDlegPwdLen error");
            #endif
            return MC_ERR_PARA;
        }
        
        // ucDlegPwdLen
        pTmp += pu->ucDlegUsrLen;
        *pTmp = pu->ucDlegPwdLen;
        usLenOut += 1;

        // ucDlegPwd
        pTmp += 1; 
        memcpy(pTmp, pu->ucDlegPwd, pu->ucDlegPwdLen);
        usLenOut += pu->ucDlegPwdLen;
       
    }
    // ��֡�ൽ�û���
    else
    {
        // usPort
        pu->usPort = pf->usPort;
        usLenOut = 2;

        // sConIp
        sIp_f = pf->sConIp;
        eRet = emc_trans_ip(eTrans, &(pu->sConIp), &sIp_f, &usLenTmp);
        if(eRet != MC_OK)
        {
            #ifdef MC_DBG
            MCDBG("emc_trans_afn04f5() emc_trans_ip() error %d!", eRet);
            #endif
            return eRet;
        }
        
        usLenOut += usLenTmp;

        // sMask
        sIp_f = pf->sMask;
        eRet = emc_trans_ip(eTrans, &(pu->sMask), &sIp_f, &usLenTmp);
        if(eRet != MC_OK)
        {
            #ifdef MC_DBG
            MCDBG("emc_trans_afn04f5() emc_trans_ip() error %d!", eRet);
            #endif
            return eRet;
        }
        
        usLenOut += usLenTmp;

        // sGateIp
        sIp_f = pf->sGateIp;
        eRet = emc_trans_ip(eTrans, &(pu->sGateIp), &sIp_f, &usLenTmp);
        if(eRet != MC_OK)
        {
            #ifdef MC_DBG
            MCDBG("emc_trans_afn04f5() emc_trans_ip() error %d!", eRet);
            #endif
            return eRet;
        }
        
        usLenOut += usLenTmp;

        // eDelegate
        switch(pf->ucDelegate)
        {
            case 0:
                pu->eDelegate = MC_DELG_NULL;
                break;
                
            case 1:
                pu->eDelegate = MC_DELG_HTTP;
                break;
                
            case 2:
                pu->eDelegate = MC_DELG_SOCK4;
                break;
                
            case 3:
                pu->eDelegate = MC_DELG_SOCK5;
                break;

            default:
                #ifdef MC_DBG
                MCDBG("emc_trans_afn04f5() para eDelegate is error!");
                #endif
                pu->eDelegate = MC_DELG_UNKOWN;
                break;
        }
        
        usLenOut += 1;
        
        // sDelgIp
        sIp_f = pf->sDelgIp;
        eRet = emc_trans_ip(eTrans, &(pu->sDelgIp), &sIp_f, &usLenTmp);
        if(eRet != MC_OK)
        {
            #ifdef MC_DBG
            MCDBG("emc_trans_afn04f5() emc_trans_ip() error %d!", eRet);
            #endif
            return eRet;
        }
        
        usLenOut += usLenTmp;

        // usDelgPort
        pu->usDelgPort = pf->usDelgPort;
        usLenOut += 2;

        // eDelgLink
        if(0 == pf->ucDelgLink)
        {
            pu->eDelgLink = MC_DELK_ANYONE;
        }
        else if(1 == pf->ucDelgLink)
        {
            pu->eDelgLink = MC_DELK_USRPWD;
        }
        else
        {
            #ifdef MC_DBG
            MCDBG("emc_trans_afn04f5() ucDelgLink para error %d!", pf->ucDelgLink);
            #endif
            pu->eDelgLink = MC_DELK_UNKOWN;
            //return MC_ERR_PARA;
        }
        
        usLenOut += 1;

        // ucUsrLen
        pu->ucDlegUsrLen = pf->ucUsrLen;
        usLenOut += 1;

        pTmp = &pf->ucUsrLen;

        // bDlegUsr
        if(0 == pu->ucDlegUsrLen)
        {
            pu->bDlegUsr = FALSE;
        }
        else
        {      
            pu->bDlegUsr = TRUE;

            // ucDlegUsr
            pTmp += 1;
            memcpy(pu->ucDlegUsr, pTmp, pu->ucDlegUsrLen);
            usLenOut += pu->ucDlegUsrLen;
        }
 
        // ucDlegPwdLen
        if(pu->ucDlegUsrLen == 0)
        {
            pTmp += 1;
        }
        else
        {
            pTmp += pu->ucDlegUsrLen;
        }

        pu->ucDlegPwdLen = *pTmp;
        usLenOut += 1;
        
         // bDlegPwd
         if(0 == pu->ucDlegPwdLen)
         {
            pu->bDlegPwd = FALSE;
         }
         else
         {
            pu->bDlegPwd = TRUE;
            
            // ucDlegPwd
            pTmp += 1; 
            memcpy(pu->ucDlegPwd, pTmp, pu->ucDlegPwdLen);
            usLenOut += pu->ucDlegPwdLen;
         }
    }
    
    *pusLen = usLenOut;
    return MC_OK;
}

/*****************************************************************************
 �� �� ��  : emc_trans_serial
 ��������  : ���ݽṹת������ 
 �������  : eMcTrans eTrans  
             void* pUser      
             void* pFrame     
             UINT16* pusLen   
 �������  : ��
 �� �� ֵ  : 
 ���ú���  : 
 ��������  : 
 
 �޸���ʷ      :
  1.��    ��   : 2013��12��5��
    ��    ��   : liming
    �޸�����   : �����ɺ���

*****************************************************************************/
eMcErr emc_trans_serial(eMcTrans eTrans, void* pUser, void* pFrame, UINT16* pusLen)
{
    sMcAcsParaSer *pu = NULL;
    UINT8         *pf = NULL;
    UINT8       ucSer = 0; 

    if(!pUser || !pFrame || !pusLen)
    {
        #ifdef MC_DBG
        MCDBG("emc_trans_serial() para pointer is null!");
        #endif
        return MC_ERR_NULL;
    }

    pu = (sMcAcsParaSer*)pUser;
    pf = (UINT8*)pFrame;

    if(MC_TRANS_U2F == eTrans)
    {
        // eMcSerBaud
        switch ( pu->eBaud)
        {
            case MC_BAUD_DEFAULT:
                 //ucSer |= 0;
                 break;

            case MC_BAUD_1200:
                 ucSer |= (1 << 5);
                 break;

            case MC_BAUD_2400:
                 ucSer |= (2 << 5);
                 break;

            case MC_BAUD_4800:
                ucSer |= (3 << 5);
                break;

            case MC_BAUD_9600:
                ucSer |= (4 << 5);
                break;

            case MC_BAUD_19200:
                ucSer |= (5 << 5);
                break;

            case MC_BAUD_38400:
                ucSer |= (6 << 5);
                break; 

            case MC_BAUD_76800:
                ucSer |= (7 << 5);
                break;   

            default:
               #ifdef MC_DBG
               MCDBG("emc_trans_serial() para eBaud is error!");
               #endif
               return MC_ERR_PARA;
               // break;
        }

        // bStop1
        if(TRUE != pu->bStop1)
        {
           ucSer |= (1 << 4);
        }
        // bCheck
        if(TRUE == pu->bCheck)
        {
           ucSer |= (1 << 3);
        }
        
        // bOdd
        if(TRUE == pu->bOdd)
        {
           ucSer |= (1 << 2);
        }    

        // eBit
        switch(pu->eBit)
        {
            case MC_SBIT_5:
                break;
                
            case MC_SBIT_6:
                ucSer |= 1;
                break;
                
            case MC_SBIT_7:
                ucSer |= 2;
                break;
                
            case MC_SBIT_8:
                ucSer |= 3;
                break;
                
            default:                         
                #ifdef MC_DBG
                MCDBG("emc_trans_serial() para eBit is error!");
                #endif
                return MC_ERR_PARA;
               // break;
        }

        // �������
        *(pf) = ucSer;
    }
    else if(MC_TRANS_F2U == eTrans)
    {
        ucSer = *pf;
        switch(ucSer & 0xE0 >> 5)
        {                 
            case 0:
                pu->eBaud = MC_BAUD_DEFAULT;
                break;
                
             case 1:
                 pu->eBaud =  MC_BAUD_1200;
                 break;
                
             case 2:
                 pu->eBaud = MC_BAUD_2400;
                 break;
                
             case 3:
                 pu->eBaud = MC_BAUD_4800;
                 break;
                
             case 4:
                 pu->eBaud = MC_BAUD_9600;
                 break;
                
             case 5:
                 pu->eBaud = MC_BAUD_19200;
                 break;
                
             case 6:
                 pu->eBaud = MC_BAUD_38400;
                 break;  
                   
             case 7:
                 pu->eBaud = MC_BAUD_76800;
                 break;  

             default:
                 #ifdef MC_DBG
                 MCDBG("emc_trans_serial() para eBaud is error!");
                 #endif
                 pu->eBaud = MC_BAUD_UNKOWN;
                 //return MC_ERR_PARA;
                 break;
        }

        // bStop1
        if(ucSer & (1 << 4))
        {
            pu->bStop1 = FALSE;
        }
        else
        {
            pu->bStop1 = TRUE;
        }
        
        // bCheck
        if(ucSer & (1 << 3))
        {
            pu->bCheck = TRUE;
        }
        else
        {
            pu->bCheck = FALSE;
        }
        
        
        // bOdd          
        if(ucSer & (1 << 2))
        {
            pu->bOdd = TRUE;
        }
        else
        {
            pu->bOdd = FALSE;
        }

        // eBit
        switch(ucSer & 0x03)
        {
            case 0:
                pu->eBit = MC_SBIT_5;
                break;
                
            case 1:
                pu->eBit = MC_SBIT_6;
                break;
                
            case 2:
                pu->eBit = MC_SBIT_7;
                break;
                
            case 3:
                pu->eBit = MC_SBIT_8;
                break;
                
            default:                         
                #ifdef MC_DBG
                MCDBG("emc_trans_serial() para eBit is error!");
                #endif
                return MC_ERR_PARA;
               // break;
        }
    }
    else
    {
        #ifdef MC_DBG
        MCDBG("emc_trans_serial() para eTrans is out of range!");
        #endif
        return MC_ERR_OUTRNG;
    }

    // �������
    * pusLen = sizeof(UINT8);
    return MC_OK;
}

/*****************************************************************************
 �� �� ��  : emc_trans_afn04f6
 ��������  : ���ݽṹת������
 ��Ӧ����  : MCMD_AFN_4_F6_CON_CASC
 �������  : eMcTrans eTrans  
             void* pUser      
             void* pFrame     
 �������  : UINT16* pusLen  ���֡����ֽ���
 �� �� ֵ  : 
 ���ú���  : 
 ��������  : 
 
 �޸���ʷ      :
  1.��    ��   : 2013��11��5��
    ��    ��   : liming
    �޸�����   : �����ɺ���

*****************************************************************************/
eMcErr emc_trans_afn04f6(eMcTrans eTrans, void* pUser, void* pFrame, UINT16* pusLen)
{
    eMcErr           eRet = MC_OK;
    UINT16       usLenTmp = 0;
    INT32               i = 0;
    sMcAfn04f6      *pu   = NULL;
    sMcAfn04f6_f    *pf   = NULL;
    
    if(!pUser || !pFrame || !pusLen)
    {
        #ifdef MC_DBG
        MCDBG("emc_trans_afn04f6() para pointer is null!");
        #endif
        return MC_ERR_NULL;
    }

    pu = (sMcAfn04f6*)pUser;
    pf = (sMcAfn04f6_f*)pFrame;

    if(MC_TRANS_U2F == eTrans)
    {
        // eType
        switch(pu->eType)
        {
            case MC_CASC_NULL:
                pf->eType = 0;
                break;
                
            case MC_CASC_RS485:
                pf->eType = 1;
                break;
                
            case MC_CASC_ETH:
                pf->eType = 2;
                break;
            
            default:
                #ifdef MC_DBG
                MCDBG("emc_trans_afn04f6() para eType is out of range!");
                #endif
                return MC_ERR_OUTRNG;
                //break;
        }

        // sSer
        eRet = emc_trans_serial(eTrans, &(pu->sSer), &(pf->sSer), &usLenTmp);
        if(MC_OK != eRet)
        {
            #ifdef MC_DBG
            MCDBG("emc_trans_afn04f6() emc_trans_serial() error %d!", eRet);
            #endif
            return eRet;
        }

        pf->ucWaitP  = pu->ucWaitP;
        pf->ucWaitC  = pu->ucWaitC;
        pf->ucReTry  = pu->ucReTry;
        pf->ucPeriod = pu->ucPeriod;
        pf->ucN      = pu->ucN;

        // sOne
        for(i = 0; i < pu->ucN; i++)
        {
            // acRegionCode
            eRet = emc_str_to_bcd((UINT8*)(pu->sOne[i].acRegionCode), 
                                  (UINT8*)(pf->sOne[i].acRegionCode),
                                  MC_REGN_LEN);
            if(MC_OK != eRet)
            {
                #ifdef MC_DBG
                MCDBG("emc_trans_afn04f6() emc_str_to_bcd() error %d!", eRet);
                #endif
                return eRet;
            }

            // ulConAddr
            pf->sOne[i].ulConAddr = pu->sOne[i].ulConAddr;

            // sIp
            eRet = emc_trans_ip(eTrans, &(pu->sOne[i].sIp), &(pf->sOne[i].sIp), &usLenTmp);
            if(MC_OK != eRet)
            {
                #ifdef MC_DBG
                MCDBG("emc_trans_afn04f6() emc_trans_ip() error %d!", eRet);
                #endif
                return eRet;
            }

            // usPort
            pf->sOne[i].usPort = pu->sOne[i].usPort;    
        }
    }
    else if(MC_TRANS_F2U == eTrans)
    {
        // eType
        switch(pf->eType)
        {
            case 0:
                pu->eType = MC_CASC_NULL;
                break;
                
            case 1:
                pu->eType = MC_CASC_RS485;
                break;
                
            case 2:
                pu->eType = MC_CASC_ETH;
                break;
            
            default:
                #ifdef MC_DBG
                MCDBG("emc_trans_afn04f6() para eType is out of range!");
                #endif
                pu->eType = MC_CASC_UNKOWN;
                break;
        }

        // sSer
        eRet = emc_trans_serial(eTrans, &(pu->sSer), &(pf->sSer), &usLenTmp);
        if(MC_OK != eRet)
        {
            #ifdef MC_DBG
            MCDBG("emc_trans_afn04f6() emc_trans_serial() error %d!", eRet);
            #endif
            return eRet;
        }

        pu->ucWaitP  = pf->ucWaitP;
        pu->ucWaitC  = pf->ucWaitC;
        pu->ucReTry  = pf->ucReTry;
        pu->ucPeriod = pf->ucPeriod;
        pu->ucN      = pf->ucN;

        // sOne
        for(i = 0; i < pu->ucN; i++)
        {
            // acRegionCode
            eRet = emc_bcd_to_str((UINT8*)(pf->sOne[i].acRegionCode), 
                                  (UINT8*)(pu->sOne[i].acRegionCode),
                                  MC_A1_LEN);
            if(MC_OK != eRet)
            {
                #ifdef MC_DBG
                MCDBG("emc_trans_afn04f6() emc_bcd_to_str() error %d!", eRet);
                #endif
                return eRet;
            }

            // ulConAddr
            pu->sOne[i].ulConAddr = pf->sOne[i].ulConAddr;

            // sIp
            eRet = emc_trans_ip(eTrans, &(pu->sOne[i].sIp), &(pf->sOne[i].sIp), &usLenTmp);
            if(MC_OK != eRet)
            {
                #ifdef MC_DBG
                MCDBG("emc_trans_afn04f6() emc_trans_ip() error %d!", eRet);
                #endif
                return eRet;
            }

            // usPort
            pu->sOne[i].usPort = pf->sOne[i].usPort;    
        }
    }
    else
    {
         #ifdef MC_DBG
         MCDBG("emc_trans_afn04f6() eTrans is out of range!");
         #endif
         return MC_ERR_OUTRNG;    
    }

    // �������
    *pusLen = sizeof(UINT8) * 7 + sizeof(sMcascAddr_f) * pu->ucN;
    return MC_OK;
}

/*****************************************************************************
 �� �� ��  : emc_trans_afn04f7
 ��������  : ���ݽṹת������
 ��Ӧ����  : MCMD_AFN_4_F7_CON_DOWN_CFG
 �������  : eMcTrans eTrans  
             void* pUser      
             void* pFrame     
 �������  : UINT16* pusLen  ���֡����ֽ���
 �� �� ֵ  : 
 ���ú���  : 
 ��������  : 
 
 �޸���ʷ      :
  1.��    ��   : 2013��11��5��
    ��    ��   : liming
    �޸�����   : �����ɺ���

*****************************************************************************/
eMcErr emc_trans_afn04f7(eMcTrans eTrans, void* pUser, void* pFrame, UINT16* pusLen)
{
    eMcErr      eRet = MC_OK;
    sMcAfn04f7_f *pf = NULL;
    sMcAfn04f7   *pu = NULL;
    UINT16     usLen = 0;
    sMcIp_f    sIp_f;

    if(!pUser || !pFrame || !pusLen)
    {
        #ifdef MC_DBG
        MCDBG("emc_trans_afn04f7() para pointer is null!");
        #endif
        return MC_ERR_NULL;
    }

    pf = (sMcAfn04f7_f*)pFrame;
    pu = (sMcAfn04f7  *)pUser;
    memset(&sIp_f, 0, sizeof(sMcIp_f));

    if(MC_TRANS_U2F == eTrans)
    {
        pf->ucPort      = pu->ucPort;
        pf->usMainPort  = pu->usMainPort;
        pf->usBackPort  = pu->usBackPort; 
        memcpy(pf->ucAPN, pu->ucAPN, MC_APN_LEN); 
        memcpy(pf->ucUsr, pu->ucUsr, 32);
        memcpy(pf->ucPwd, pu->ucPwd, 32);

        // sMainIp
        eRet = emc_trans_ip(eTrans, &(pu->sMainIp), &sIp_f, &usLen);
        if(MC_OK != eRet)
        {
            #ifdef MC_DBG
            MCDBG("XXemc_trans_afn04f7() emc_trans_ip() error %d!", eRet);
            #endif
            return eRet;
        }
        
        pf->sMainIp = sIp_f;
        
        // sBackIp
        eRet = emc_trans_ip(eTrans, &(pu->sBackIp), &sIp_f, &usLen);
        if(MC_OK != eRet)
        {
            #ifdef MC_DBG
            MCDBG("XXemc_trans_afn04f7() emc_trans_ip() error %d!", eRet);
            #endif
            return eRet;
        } 
        
        pf->sBackIp = sIp_f ;
    }
    else if(MC_TRANS_F2U == eTrans)
    {
        pu->ucPort      = pf->ucPort;
        pu->usMainPort  = pf->usMainPort;
        pu->usBackPort  = pf->usBackPort;  
        memcpy(pu->ucAPN, pf->ucAPN, MC_APN_LEN); 
        memcpy(pu->ucUsr, pf->ucUsr, 32);
        memcpy(pu->ucPwd, pf->ucPwd, 32);

        // sMainIp       
        sIp_f = pf->sMainIp;
        eRet = emc_trans_ip(eTrans, &(pu->sMainIp), &sIp_f, &usLen);
        if(MC_OK != eRet)
        {
            #ifdef MC_DBG
            MCDBG("XXemc_trans_afn04f7() emc_trans_ip() error %d!", eRet);
            #endif
            return eRet;
        }
        
        // sBackIp
        sIp_f = pf->sBackIp;
        eRet = emc_trans_ip(eTrans, &(pu->sBackIp), &sIp_f, &usLen);
        if(MC_OK != eRet)
        {
            #ifdef MC_DBG
            MCDBG("XXemc_trans_afn04f7() emc_trans_ip() error %d!", eRet);
            #endif
            return eRet;
        } 
    }
    else
    {
        #ifdef MC_DBG
        MCDBG("emc_trans_afn04f7() para eTrans is out of range!");
        #endif
        return MC_ERR_OUTRNG;
    }

    // ���֡�೤��
    * pusLen = sizeof(sMcAfn04f7_f);
    return MC_OK;
}

/*****************************************************************************
 �� �� ��  : emc_trans_afn04f9
 ��������  : ���ݽṹת������
 ��Ӧ����  : MCMD_AFN_4_F9_CON_EVENT_CFG
 �������  : eMcTrans eTrans  
             void* pUser      
             void* pFrame     
 �������  : UINT16* pusLen  ���֡����ֽ���
 �� �� ֵ  : 
 ���ú���  : 
 ��������  : 
 
 �޸���ʷ      :
  1.��    ��   : 2013��11��5��
    ��    ��   : liming
    �޸�����   : �����ɺ���

*****************************************************************************/
eMcErr emc_trans_afn04f9(eMcTrans eTrans, void* pUser, void* pFrame, UINT16* pusLen)
{
    sMcAfn04f9_f   *pf  = NULL;
    sMcAfn04f9     *pu  = NULL;  
    INT32          i    = 0;
    INT32          ai   = 0;      // ��Ϊ��������
    INT32          bi   = 0;      // ��λ����
    eMcErc         eErc = MC_ERC_UNKOWN;
    UINT8         ucErc = 0;
    UINT8         ucTmp = 0;
    
    if(!pUser || !pFrame || !pusLen)
    {
        #ifdef MC_DBG
        MCDBG("emc_trans_afn04f9() para pointer is null!");
        #endif
        return MC_ERR_NULL;
    }

    pf = (sMcAfn04f9_f*)pFrame;
    pu = (sMcAfn04f9  *)pUser;

    // �û��ൽ��֡��
    if(MC_TRANS_U2F == eTrans)
    {
        // aNeed
        if(pu->ucNeed > MC_ERC_NUM_MAX)
        {
            #ifdef MC_DBG
            MCDBG("emc_trans_afn04f9() para ucNeed is out of range %d!", pu->ucNeed);
            #endif
            return MC_ERR_OUTRNG;
        }

        for(i = 0; i < pu->ucNeed; i++)
        {
            eErc = pu->aNeed[i];
            if(eErc > MC_ERC_NUM_MAX || eErc == MC_ERC_UNKOWN)
            {
                #ifdef MC_DBG
                MCDBG("emc_trans_afn04f9() para eErc is out of range %d!", eErc);
                #endif
                return MC_ERR_OUTRNG;
            }

            // ��������bs64�е�λ��
            ucErc = (UINT8)eErc;
            ai = (ucErc - 1) / 8;
            bi = (ucErc - 1) % 8;
            pf->aNeed[ai] |= (0x01 << bi);
        }

        // ucImpt
        if(pu->ucImpt > MC_ERC_NUM_MAX)
        {
            #ifdef MC_DBG
            MCDBG("emc_trans_afn04f9() para ucImpt is out of range %d!", pu->ucImpt);
            #endif
            return MC_ERR_OUTRNG;
        }

        if(pu->ucImpt > pu->ucNeed)
        {
            #ifdef MC_DBG
            MCDBG("emc_trans_afn04f9() ucImpt > ucNeed (%d - %d)!", pu->ucImpt, pu->ucNeed);
            #endif
            return MC_ERR_LOGIC;
        }
        
        for(i = 0; i < pu->ucImpt; i++)
        {
            eErc = pu->aImpt[i];
            if(eErc > MC_ERC_NUM_MAX || eErc == MC_ERC_UNKOWN)
            {
                #ifdef MC_DBG
                MCDBG("emc_trans_afn04f9() para eErc is out of range %d!", eErc);
                #endif
                return MC_ERR_OUTRNG;
            }

            // ��������bs64�е�λ��
            ucErc = (UINT8)eErc;
            ai = (ucErc -1) / 8;
            bi = (ucErc -1) % 8;
            pf->aImpt[ai] |= (0x01 << bi);
        }

        pf->usImpRecNum = pu->usImpRecNum;
        pf->usNmlRecNum = pu->usNmlRecNum;    
    }
    // ��֡�ൽ�û���
    else if(MC_TRANS_F2U == eTrans)
    {
        // aNeed
        for(ai = 0; ai < 8; ai++)
        {
            ucTmp = pf->aNeed[ai];
            for(bi = 0; bi < 8; bi++)
            {
                if(ucTmp & (0x01 << bi))
                {
                    ucErc = ai * 8 + bi + 1;
                    eErc = (eMcErc)ucErc;
                    pu->aNeed[i++] = eErc;
                }
            }
        }

        pu->ucNeed = i;
       
        // aImpt 
        i = 0;
        for(ai = 0; ai < 8; ai++)
        {
            ucTmp = pf->aImpt[ai];
            for(bi = 0; bi < 8; bi++)
            {
                if(ucTmp & (0x01 << bi))
                {
                    ucErc = ai * 8 + bi + 1;
                    eErc = (eMcErc)ucErc;
                    pu->aImpt[i++] = eErc;
                }
            }
        }

        pu->ucImpt = i;
        pu->usImpRecNum = pf->usImpRecNum;
        pu->usNmlRecNum = pf->usNmlRecNum;
    }
    else
    {
       #ifdef MC_DBG
       MCDBG("emc_trans_afn04f9() para eTrans is out of range!");
       #endif
       return MC_ERR_OUTRNG;
    }
    // �������
    * pusLen = sizeof(sMcAfn04f9_f);
    return MC_OK;
}

/*****************************************************************************
 �� �� ��  : emc_trans_afn04f10
 ��������  : ���ݽṹת������
 ��Ӧ����  : MCMD_AFN_4_F10_CON_STATE_INPUT
 �������  : eMcTrans eTrans  
             void* pUser      
             void* pFrame     
 �������  : UINT16* pusLen  ���֡����ֽ���
 �� �� ֵ  : 
 ���ú���  : 
 ��������  : 
 
 �޸���ʷ      :
  1.��    ��   : 2013��11��7��
    ��    ��   : liming
    �޸�����   : �����ɺ���

*****************************************************************************/
eMcErr emc_trans_afn04f10(eMcTrans eTrans, void* pUser, void* pFrame, UINT16* pusLen)
{
    sMcAfn04f10_f    *pf = NULL;
    sMcAfn04f10      *pu = NULL;  
    INT32              i = 0;
    UINT8         ucMask = 0;

    if(!pUser || !pFrame || !pusLen)
    {
        #ifdef MC_DBG
        MCDBG("emc_trans_afn04f10() para pointer is null!");
        #endif
        return MC_ERR_NULL;
    }

    pf = (sMcAfn04f10_f*)pFrame;
    pu = (sMcAfn04f10  *)pUser;

    // �û��ൽ��֡��
    if(MC_TRANS_U2F == eTrans)
    {
       pf->bIn = 0;
       for(i = 0; i < 8; i++)
       {    
           ucMask = (0x01 << i);
           // bIn
           if(TRUE == pu->bIn[i])
           {
              pf->bIn |= ucMask;
           }

           // bOn
           if(TRUE == pu->bOn[i])
           {
              pf->bOn |= ucMask;
           }
       }
    }
    // ��֡�ൽ�û���
    else
    {
        for(i = 0; i < 8; i++)
        {
            ucMask = (0x01 << i);

            // bIn
            if(pf->bIn & ucMask)
            {
                pu->bIn[i] = TRUE;
            }
            else
            {  
                pu->bIn[i] = FALSE;
            }

            // bOn
            if(pf->bOn & ucMask)
            {
                pu->bOn[i] = TRUE;
            }
            else
            {  
                pu->bOn[i] = FALSE;
            }
        }
    }

    // �������
    * pusLen = sizeof(sMcAfn04f10_f);
    return MC_OK;
}

/*****************************************************************************
 �� �� ��  : emc_trans_afn04f17
 ��������  : ���ݽṹת������
 ��Ӧ����  : MCMD_AFN_4_F17_TML_UP_CFG
 �������  : eMcTrans eTrans  
             void* pUser      
             void* pFrame     
 �������  : UINT16* pusLen  ���֡����ֽ���
 �� �� ֵ  : 
 ���ú���  : 
 ��������  : 
 
 �޸���ʷ      :
  1.��    ��   : 2013��11��7��
    ��    ��   : liming
    �޸�����   : �����ɺ���

*****************************************************************************/
eMcErr emc_trans_afn04f17(eMcTrans eTrans, void* pUser, void* pFrame, UINT16* pusLen)
{
    sMcAfn04f17_f      *pf    = NULL;
    sMcAfn04f17        *pu    = NULL;  
    UINT8            *pTmp    = NULL;
    eMcErr            eRet    = MC_OK;
    UINT16           usLen    = 0;
    UINT16        usTmpLen    = 0;
    sMcAfn04f1_f *pAfn04f01_f = NULL;
    sMcAfn04f1    sAfn04f01   = {0};
    sMcA_f            sA_f;    
    sMcIp_f          sIp_f; 
    sMcMask_f      sMask_f;

    if(!pUser || !pFrame || !pusLen)
    {
        #ifdef MC_DBG
        MCDBG("emc_trans_afn04f17() para pointer is null!");
        #endif
        return MC_ERR_NULL;
    }

    memset(&sA_f,    0, sizeof(sMcA_f));
    memset(&sIp_f,   0, sizeof(sMcIp_f));
    memset(&sMask_f, 0, sizeof(sMcMask_f));

    pf = (sMcAfn04f17_f*)pFrame;
    pu = (sMcAfn04f17  *)pUser;

    // �û��ൽ��֡��
    if(MC_TRANS_U2F == eTrans)
    {
        // ucDownPort
        pf->ucDownPort = pu->ucDownPort;
        usLen += sizeof(UINT8);
        
        // usListenPort
        pf->usListenPort = pu->usListenPort;
        usLen += sizeof(UINT16);
        
        // eUpPara
        switch(pu->eUpPara)
        {
            case MC_TUPP_DEL:
                pf->ucUpPara = 0;
                break;

            case MC_TUPP_SER:
                pf->ucUpPara = 1;
                break;

            case MC_TUPP_ETH:
                pf->ucUpPara = 2;
                break;
            default:
                #ifdef MC_DBG
                MCDBG("emc_trans_afn04f17() para eUpPara error");
                #endif
                return MC_ERR_PARA;
                //break;
        }
        
        usLen += sizeof(UINT8);

        // sUpAddr
        eRet = emc_trans_address(eTrans, &(pu->sUpAddr), &sA_f);
        if(eRet != MC_OK)
        {
            #ifdef MC_DBG
            MCDBG("emc_trans_afn04f17() emc_trans_address() error %d!", eRet);
            #endif
            return eRet;
        }
        
        pf->sUpAddr = sA_f;
        usLen += sizeof(sMcAddress_f);

        // ucUpProto
        pf->ucUpProto = pu->ucUpProto;
        usLen += sizeof(UINT8);

        // sUpIp
        eRet = emc_trans_ip(eTrans, &(pu->sUpIp), &sIp_f, &usTmpLen);
        if(eRet != MC_OK)
        {
            #ifdef MC_DBG
            MCDBG("emc_trans_afn04f17() emc_trans_ip() error %d!", eRet);
            #endif
            return eRet;
        }

        pf->sUpIp = sIp_f;
        usLen += usTmpLen;

        // sUpMask
        eRet = emc_trans_ip(eTrans, &(pu->sUpMask), &sMask_f, &usTmpLen);
        if(eRet != MC_OK)
        {
            #ifdef MC_DBG
            MCDBG("emc_trans_afn04f17() emc_trans_ip() error %d!", eRet);
            #endif
            return eRet;
        }

        pf->sUpMask = sMask_f;
        usLen += usTmpLen;

        // sGateIp
        eRet = emc_trans_ip(eTrans, &(pu->sGateIp), &sIp_f, &usTmpLen);
        if(eRet != MC_OK)
        {
            #ifdef MC_DBG
            MCDBG("emc_trans_afn04f17() emc_trans_ip() error %d!", eRet);
            #endif
            return eRet;
        }

        pf->sGateIp = sIp_f;
        usLen += usTmpLen;

        // eDelegate
        switch(pu->eDelegate)
        {
            case MC_DELG_NULL:
                pf->ucDelegate = 0;
                break;
                
            case MC_DELG_HTTP:
                pf->ucDelegate = 1;
                break;
                
            case MC_DELG_SOCK4:
                pf->ucDelegate = 2;
                break;
                
            case MC_DELG_SOCK5:
                pf->ucDelegate = 3;
                break;

            default:
                #ifdef MC_DBG
                MCDBG("emc_trans_afn04f17() para eDelegate is error!");
                #endif
                return MC_ERR_PARA;
                //break;
        }

        usLen += sizeof(UINT8);

        // sDelgIp
        eRet = emc_trans_ip(eTrans, &(pu->sDelgIp), &sIp_f, &usTmpLen);
        if(eRet != MC_OK)
        {
            #ifdef MC_DBG
            MCDBG("emc_trans_afn04f17() emc_trans_ip() error %d!", eRet);
            #endif
            return eRet;
        }

        pf->sDelgIp = sIp_f;
        usLen += usTmpLen;

        // usDelgPort
        pf->usDelgPort = pu->usDelgPort;
        usLen += sizeof(UINT16);

        // eDelgLink
        if(MC_DELK_ANYONE == pu->eDelgLink)
        {
            pf->ucDelgLink = 0;
        }
        else if(MC_DELK_USRPWD == pu->eDelgLink)
        {
            pf->ucDelgLink = 1;
        }
        else
        {
            #ifdef MC_DBG
            MCDBG("emc_trans_afn04f17() eDelgLink para error %d!", pu->eDelgLink);
            #endif
            return MC_ERR_PARA;
        }
        
        usLen += 1;

        // bDlegUsr
        if(TRUE == pu->bDlegUsr && 0 == pu->ucDlegUsrLen)
        {
            #ifdef MC_DBG
            MCDBG("emc_trans_afn04f17() bDlegUsr ucDlegUsrLen error");
            #endif
            return MC_ERR_PARA;
        }

        // ucUsrLen
        pf->ucUsrLen = pu->ucDlegUsrLen;
        usLen += 1;

        // ucDlegUsr
        pTmp = (UINT8*)(&(pf->ucUsrLen) + 1);
        memcpy(pTmp, pu->ucDlegUsr, pu->ucDlegUsrLen);
        usLen += pu->ucDlegUsrLen;

        // bDlegPwd
        if(TRUE == pu->bDlegPwd && 0 == pu->ucDlegPwdLen)
        {
            #ifdef MC_DBG
            MCDBG("emc_trans_afn04f17() bDlegPwd ucDlegPwdLen error");
            #endif
            return MC_ERR_PARA;
        }
        
        // ucDlegPwdLen
        pTmp += pu->ucDlegUsrLen;
        *pTmp = pu->ucDlegPwdLen;
        usLen += 1;

        // ucDlegPwd
        pTmp += 1; 
        memcpy(pTmp, pu->ucDlegPwd, pu->ucDlegPwdLen);
        usLen += pu->ucDlegPwdLen;

        // sAfn04f01 
        pTmp += pu->ucDlegPwdLen;
        pAfn04f01_f = (sMcAfn04f1_f *)pTmp;
        
        sAfn04f01.ucPermitDelayM = pu->ucPermitDelayM;
        sAfn04f01.ucReSendTimes  = pu->ucReSendTimes;
        sAfn04f01.ucHeartBeat    = pu->ucHeartBeat;
        sAfn04f01.usWaitTimeoutS = pu->usWaitTimeoutS;
        sAfn04f01.bPermitRt      = pu->bPermitRt;
        sAfn04f01.bPermitTk      = pu->bPermitTk;
        sAfn04f01.bPermitEv      = pu->bPermitEv;
        
        eRet = emc_trans_afn04f1(eTrans, &sAfn04f01, pAfn04f01_f, &usTmpLen);
        if(MC_OK != eRet)
        {
            #ifdef MC_DBG
            MCDBG("emc_trans_afn04f17() emc_trans_afn04f1() error %d!", eRet);
            #endif
            return eRet;
        }

        usLen += usTmpLen;
    }
    // ��֡�ൽ�û���
    else
    {
        // ucDownPort
        pu->ucDownPort = pf->ucDownPort;
        usLen += sizeof(UINT8);
        
        // usListenPort
        pu->usListenPort = pf->usListenPort;
        usLen += sizeof(UINT16);
        
        // eUpPara
        switch(pf->ucUpPara)
        {
            case 0:
                pu->eUpPara = MC_TUPP_DEL;
                break;
                
            case 1:
                pu->eUpPara = MC_TUPP_SER;
                break;
                
            case 2:
                pu->eUpPara = MC_TUPP_ETH;
                break;
  
            default:
                #ifdef MC_DBG
                MCDBG("emc_trans_afn04f17() para eUpPara error");
                #endif
                pu->eUpPara = MC_TUPP_UNKOWN;

                //return MC_ERR_PARA;
                break;
        }
        
        usLen += sizeof(UINT8);

        // sUpAddr
        sA_f = pf->sUpAddr;
        eRet = emc_trans_address(eTrans, &(pu->sUpAddr), &sA_f);
        if(eRet != MC_OK)
        {
            #ifdef MC_DBG
            MCDBG("emc_trans_afn04f17() emc_trans_address() error %d!", eRet);
            #endif
            return eRet;
        }
        
        usLen += sizeof(sMcAddress_f);

        // ucUpProto
        pu->ucUpProto = pf->ucUpProto;
        usLen += sizeof(UINT8);

        // sUpIp
        eRet = emc_trans_ip(eTrans, &(pu->sUpIp), &(pf->sUpIp), &usTmpLen);
        if(eRet != MC_OK)
        {
            #ifdef MC_DBG
            MCDBG("emc_trans_afn04f17() emc_trans_ip() error %d!", eRet);
            #endif
            return eRet;
        }
        
        usLen += usTmpLen;

        // sUpMask
        eRet = emc_trans_ip(eTrans, &(pu->sUpMask), &(pf->sUpMask), &usTmpLen);
        if(eRet != MC_OK)
        {
            #ifdef MC_DBG
            MCDBG("emc_trans_afn04f17() emc_trans_ip() error %d!", eRet);
            #endif
            return eRet;
        }
        
        usLen += usTmpLen;

        // sGateIp
        eRet = emc_trans_ip(eTrans, &(pu->sGateIp), &(pf->sGateIp), &usTmpLen);
        if(eRet != MC_OK)
        {
            #ifdef MC_DBG
            MCDBG("emc_trans_afn04f17() emc_trans_ip() error %d!", eRet);
            #endif
            return eRet;
        }
        
        usLen += usTmpLen;
        
        // eDelegate
        switch(pf->ucDelegate)
        {
            case 0:
                pu->eDelegate = MC_DELG_NULL;
                break;
                
            case 1:
                pu->eDelegate = MC_DELG_HTTP;
                break;
                
            case 2:
                pu->eDelegate = MC_DELG_SOCK4;
                break;
                
            case 3:
                pu->eDelegate = MC_DELG_SOCK5;
                break;

            default:
                #ifdef MC_DBG
                MCDBG("emc_trans_afn04f17() para eDelegate is error!");
                #endif
                pu->eDelegate = MC_DELG_UNKOWN;
                break;
        }

        usLen += sizeof(UINT8);

        // sDelgIp
        sIp_f = pf->sDelgIp;
        eRet = emc_trans_ip(eTrans, &(pu->sDelgIp), &sIp_f, &usTmpLen);
        if(eRet != MC_OK)
        {
            #ifdef MC_DBG
            MCDBG("emc_trans_afn04f17() emc_trans_ip() error %d!", eRet);
            #endif
            return eRet;
        }
        
        usLen += usTmpLen;

        // usDelgPort
        pu->usDelgPort = pf->usDelgPort;
        usLen += sizeof(UINT16);

        // eDelgLink
        if(0 == pf->ucDelgLink)
        {
            pu->eDelgLink = MC_DELK_ANYONE;
        }
        else if(1 == pf->ucDelgLink)
        {
            pu->eDelgLink = MC_DELK_USRPWD;
        }
        else
        {
            #ifdef MC_DBG
            MCDBG("emc_trans_afn04f17() ucDelgLink para error %d!", pf->ucDelgLink);
            #endif
            pu->eDelgLink = MC_DELK_UNKOWN;
            //return MC_ERR_PARA;
        }
        
        usLen += 1;

         // ucUsrLen
        pu->ucDlegUsrLen = pf->ucUsrLen;
        usLen += 1;

        // bDlegUsr
        pTmp = (UINT8*)&(pf->ucUsrLen);
        if(0 == pu->ucDlegUsrLen)
        {
            pu->bDlegUsr = FALSE;
        }
        else
        {      
            pu->bDlegUsr = TRUE;

            // ucDlegUsr
            pTmp += 1;
            memcpy(pu->ucDlegUsr, pTmp, pu->ucDlegUsrLen);
            usLen += pu->ucDlegUsrLen;
        }
 
        // ucDlegPwdLen
        if(0 == pu->ucDlegUsrLen)
        {
            pTmp += 1;
        }
        else
        {
            pTmp += pu->ucDlegUsrLen;
        }

        pu->ucDlegPwdLen = *pTmp;
        usLen += 1;
        
        // bDlegPwd
        if(0 == pu->ucDlegPwdLen)
        {
            pu->bDlegPwd = FALSE;
        }
        else
        {
            pu->bDlegPwd = TRUE;

            // ucDlegPwd
            pTmp += 1; 
            memcpy(pu->ucDlegPwd, pTmp, pu->ucDlegPwdLen);
            usLen += pu->ucDlegPwdLen;
        }

        // sAfn04f01 
        if(0 == pu->ucDlegPwdLen)
        {
            pTmp += 1; 
        }
        else
        {
            pTmp += pu->ucDlegPwdLen;
        }
        
        pAfn04f01_f = (sMcAfn04f1_f *)pTmp;
        eRet = emc_trans_afn04f1(eTrans, &sAfn04f01, pAfn04f01_f, &usTmpLen);
        if(MC_OK != eRet)
        {
            #ifdef MC_DBG
            MCDBG("emc_trans_afn04f17() emc_trans_afn04f1() error %d!", eRet);
            #endif
            return eRet;
        }
        
        pu->ucPermitDelayM = sAfn04f01.ucPermitDelayM;
        pu->ucReSendTimes  = sAfn04f01.ucReSendTimes;
        pu->ucHeartBeat    = sAfn04f01.ucHeartBeat;
        pu->usWaitTimeoutS = sAfn04f01.usWaitTimeoutS;
        pu->bPermitRt      = sAfn04f01.bPermitRt;
        pu->bPermitTk      = sAfn04f01.bPermitTk;
        pu->bPermitEv      = sAfn04f01.bPermitEv;
        
        usLen += usTmpLen;
    }

    // �������
    * pusLen = usLen;
    return MC_OK;
}

/*****************************************************************************
 �� �� ��  : emc_trans_afn04f25
 ��������  : ���ݽṹת������
 ��Ӧ����  : MCMD_AFN_4_F25_ELEC_MP_CFG
 �������  : eMcTrans eTrans  
             void* pUser      
             void* pFrame     
 �������  : UINT16* pusLen  ���֡����ֽ���
 �� �� ֵ  : 
 ���ú���  : 
 ��������  : 
 
 �޸���ʷ      :
  1.��    ��   : 2013��11��7��
    ��    ��   : liming
    �޸�����   : �����ɺ���

*****************************************************************************/
eMcErr emc_trans_afn04f25(eMcTrans eTrans, void* pUser, void* pFrame, UINT16* pusLen)
{
    sMcAfn04f25_f      *pf = NULL;
    sMcAfn04f25        *pu = NULL;  
    UINT8            *pTmp = NULL;
    eMcErr            eRet = MC_OK;
    UINT16           usLen = 0;
    UINT16        usTmpLen = 0;    
    UINT8            ucSer = 0;       // MC_ACS_PORT_SER  �������в���
    sMcAcsParaEth_f *psEth = NULL;    // MC_ACS_PORT_ETH  ��̫�����в���
    UINT32    *pulAddrZigb = NULL;    // MC_ACS_PORT_ZIGB Zigbee��ַ 
    UINT16     *pusAcsPort = NULL;    // �����豸�����˿ں�
    sMcMask_f      *psMask = NULL;    // ���������ַ
    //sMcIp_f      *psGateIp = NULL;    // ���ص�ַ

    if(!pUser || !pFrame || !pusLen)
    {
        #ifdef MC_DBG
        MCDBG("emc_trans_afn04f25() para pointer is null!");
        #endif
        return MC_ERR_NULL;
    }

    pf = (sMcAfn04f25_f*)pFrame;
    pu = (sMcAfn04f25  *)pUser;

    // �û��ൽ��֡��
    if(MC_TRANS_U2F == eTrans)
    {
        // usID
        pf->usID = pu->usID;
        usLen += sizeof(UINT16);

        // ucPort
        pf->ucPort = pu->ucPort;
        usLen += sizeof(UINT8);

        // ucAddr
        eRet = emc_str_to_bcd(pu->ucAddr, pf->ucAddrBcd, 16);
        if(MC_OK != eRet)
        {
            #ifdef MC_DBG
            MCDBG("emc_trans_afn04f25() emc_str_to_bcd() error %d!", eRet);
            #endif
            return eRet;
        }

        usLen += 8;

        // eAcsProto
        switch(pu->eAcsProto)
        {
            case MC_ACS_PROT_GBNX_32:
                pf->eAcsProto = 1;
                break;       
                    
            case MC_ACS_PROT_DLT645_97:
                pf->eAcsProto = 2;
                break;         
                
            case MC_ACS_PROT_DLT645_07:
                pf->eAcsProto = 3;
                break;      
                
            case MC_ACS_PROT_MODBUS:
                pf->eAcsProto = 4;
                break;
                
            default:
                pf->eAcsProto = pu->eAcsProto;
                break;
        }
        
        usLen += sizeof(UINT8);
        
        // ucPwd
        memcpy(pf->ucPwd, pu->ucPwd, 6);
        usLen += 6;

        // eAcsPort
        pTmp = &(pf->ucAcsParaLen);
        pTmp++;
        switch(pu->eAcsPort)
        {
            case MC_ACS_PORT_DC:
                pf->eAcsPort = 1;
                pf->ucAcsParaLen = 0;// �޲���
                break;
                
            case MC_ACS_PORT_AC:
                pf->eAcsPort = 2;
                pf->ucAcsParaLen = 0;// �޲���
                break;
                
            case MC_ACS_PORT_SER:
                pf->eAcsPort = 3;
                pf->ucAcsParaLen = 1; 
                switch(pu->uPortPara.sSer.eBaud)
                {
                    case MC_BAUD_DEFAULT:
                        //ucSer |= 0;
                        break;
                        
                     case MC_BAUD_1200:
                         ucSer |= (1 << 5);
                         break;
                        
                     case MC_BAUD_2400:
                         ucSer |= (2 << 5);
                         break;
                        
                     case MC_BAUD_4800:
                         ucSer |= (3 << 5);
                         break;
                        
                     case MC_BAUD_9600:
                         ucSer |= (4 << 5);
                         break;
                        
                     case MC_BAUD_19200:
                         ucSer |= (5 << 5);
                         break;
                        
                      case MC_BAUD_38400:
                           ucSer |= (6 << 5);
                           break; 
                           
                     case MC_BAUD_76800:
                           ucSer |= (7 << 5);
                           break;   
                           
                      default:
                            #ifdef MC_DBG
                            MCDBG("emc_trans_afn04f25() para eBaud is error!");
                            #endif
                            return MC_ERR_PARA;
                            // break;
                }
             
                // bStop1
                if(TRUE != pu->uPortPara.sSer.bStop1)
                {
                   ucSer |= (1 << 4);
                }
                // bCheck
                if(TRUE == pu->uPortPara.sSer.bCheck)
                {
                   ucSer |= (1 << 3);
                }
                
                // bOdd
                if(TRUE == pu->uPortPara.sSer.bOdd)
                {
                   ucSer |= (1 << 2);
                }    

                // eBit
                switch(pu->uPortPara.sSer.eBit)
                {
                    case MC_SBIT_5:
                        break;
                        
                    case MC_SBIT_6:
                        ucSer |= 1;
                        break;
                        
                    case MC_SBIT_7:
                        ucSer |= 2;
                        break;
                        
                    case MC_SBIT_8:
                        ucSer |= 3;
                        break;
                        
                    default:                         
                        #ifdef MC_DBG
                        MCDBG("emc_trans_afn04f25() para eBit is error!");
                        #endif
                        return MC_ERR_PARA;
                       // break;
                }

                // �������
                *(pTmp) = ucSer;
                break;
                
            case MC_ACS_PORT_ETH:
                pf->eAcsPort = 4;     
                pf->ucAcsParaLen = sizeof(sMcAcsParaEth_f); 
                psEth = (sMcAcsParaEth_f *)pTmp;

                // usPort
                psEth->usPort = pu->uPortPara.sEth.usPort;

                // sIP  
                eRet = emc_trans_ip(eTrans, &(pu->uPortPara.sEth.sAccess), &(psEth->sAccess), &usTmpLen);
                if(eRet != MC_OK)
                {
                    #ifdef MC_DBG
                    MCDBG("emc_trans_afn04f25() emc_trans_ip() error %d!", eRet);
                    #endif
                    return eRet;
                }
                
                /*
                // sMask  
                eRet = emc_trans_ip(eTrans, &(pu->uPortPara.sEth.sMask), &(psEth->sMask), &usTmpLen);
                if(eRet != MC_OK)
                {
                    #ifdef MC_DBG
                    MCDBG("emc_trans_afn04f25() emc_trans_ip() error %d!", eRet);
                    #endif
                    return eRet;
                }
                
                // sGate
                eRet = emc_trans_ip(eTrans, &(pu->uPortPara.sEth.sGate), &(psEth->sGate), &usTmpLen);
                if(eRet != MC_OK)
                {
                    #ifdef MC_DBG
                    MCDBG("emc_trans_afn04f25() emc_trans_ip() error %d!", eRet);
                    #endif
                    return eRet;
                }
                */
                
                // �Ѿ��ں�߼��㳤��, ����ֻΪȥ������
                usTmpLen = usTmpLen;
                break;
                
            case MC_ACS_PORT_ZIGB:
                pf->eAcsPort = 5;      
                pf->ucAcsParaLen = 4; 
                pulAddrZigb = (UINT32*)pTmp;
                *pulAddrZigb = pu->uPortPara.ulAddrZigb;
                break;
                
            default:
                #ifdef MC_DBG
                MCDBG("emc_trans_afn04f25() para eAcsPort is error!");
                #endif
                return MC_ERR_OUTRNG;
                //break;

        }

        // ���㳤��
        usLen += sizeof(UINT8) * 2 + pf->ucAcsParaLen;

        pTmp += pf->ucAcsParaLen;
        
        // usAcsPort
        pusAcsPort = (UINT16*)pTmp;
        *pusAcsPort = pu->usAcsPort;
        usLen += sizeof(UINT16);

       // ���Ժ�ڲ������ 2013/12/24
        // sIp
        pTmp += sizeof(UINT16);
        psMask = (sMcMask_f*)pTmp;
        eRet = emc_trans_ip(eTrans, &(pu->sAccess), psMask, &usTmpLen);
        if(eRet != MC_OK)
        {
            #ifdef MC_DBG
            MCDBG("emc_trans_afn04f25() emc_trans_ip() error %d!", eRet);
            #endif
            return eRet;
        }
        
        usLen += usTmpLen;
        
        /* ���Ժ�ڲ����޸� 2013/12/24
        // sMask
        pTmp += sizeof(UINT16);
        psMask = (sMcMask_f*)pTmp;
        eRet = emc_trans_ip(eTrans, &(pu->sMask), psMask, &usTmpLen);
        if(eRet != MC_OK)
        {
            #ifdef MC_DBG
            MCDBG("emc_trans_afn04f25() emc_trans_ip() error %d!", eRet);
            #endif
            return eRet;
        }
        
        usLen += usTmpLen;
        
        // sGateIp
        pTmp += sizeof(sMcMask_f);
        psGateIp = (sMcIp_f*)pTmp;
        eRet = emc_trans_ip(eTrans, &(pu->sGateIp), psGateIp, &usTmpLen);
        if(eRet != MC_OK)
        {
            #ifdef MC_DBG
            MCDBG("emc_trans_afn04f25() emc_trans_ip() error %d!", eRet);
            #endif
            return eRet;
        }
        
        usLen += usTmpLen;
        */
    }
    // ��֡�ൽ�û���
    else
    {
        // usID
        pu->usID = pf->usID;
        usLen += sizeof(UINT16);

        // ucPort
        pu->ucPort = pf->ucPort;
        usLen += sizeof(UINT8);

        // ucAddr
        eRet = emc_bcd_to_str(pf->ucAddrBcd, pu->ucAddr, 8);
        if(MC_OK != eRet)
        {
            #ifdef MC_DBG
            MCDBG("emc_trans_afn04f25() emc_bcd_to_str() error %d!", eRet);
            #endif
            return eRet;
        }

        usLen += 8;

        // eAcsProto
        switch(pf->eAcsProto)
        {
            case 1:
                pu->eAcsProto = MC_ACS_PROT_GBNX_32;
                break;  
                
             case 2:
                pu->eAcsProto = MC_ACS_PROT_DLT645_97;
                break;    
                
             case 3:
                pu->eAcsProto = MC_ACS_PROT_DLT645_07;
                break;     
                
             case 4:
                pu->eAcsProto = MC_ACS_PROT_MODBUS;
                break;     

              default:
                pu->eAcsProto = MC_ACS_PROT_UNKOWN;
                break;
        }
        
        usLen += sizeof(UINT8);
        
        // ucPwd
        memcpy(pu->ucPwd, pf->ucPwd, 6);
        usLen += 6;

        // eAcsPort
        pTmp = &(pf->ucAcsParaLen);
        pTmp++;
        switch(pf->eAcsPort)
        {
            case 1:
                pu->eAcsPort = MC_ACS_PORT_DC;
                if(pf->ucAcsParaLen != 0)
                {
                    #ifdef MC_DBG
                    MCDBG("emc_trans_afn04f25() ucAcsParaLen error %d!", pf->ucAcsParaLen);
                    #endif
                    return MC_ERR_LOGIC;
                }
                break;
                
            case 2:
                pu->eAcsPort = MC_ACS_PORT_AC;
                if(pf->ucAcsParaLen != 0)
                {
                    #ifdef MC_DBG
                    MCDBG("emc_trans_afn04f25() ucAcsParaLen error %d!", pf->ucAcsParaLen);
                    #endif
                    return MC_ERR_LOGIC;
                }
                break;
                
            case 3:
                // ȡ�ò���
                ucSer = *(pTmp);
                pu->eAcsPort = MC_ACS_PORT_SER;
                if(pf->ucAcsParaLen != 1)
                {
                    #ifdef MC_DBG
                    MCDBG("emc_trans_afn04f25() ucAcsParaLen error %d!", pf->ucAcsParaLen);
                    #endif
                    return MC_ERR_LOGIC;
                }

                switch(ucSer & 0xE0 >> 5)
                {                 
                    case 0:
                        pu->uPortPara.sSer.eBaud = MC_BAUD_DEFAULT;
                        break;
                        
                     case 1:
                         pu->uPortPara.sSer.eBaud =  MC_BAUD_1200;
                         break;
                        
                     case 2:
                         pu->uPortPara.sSer.eBaud = MC_BAUD_2400;
                         break;
                        
                     case 3:
                         pu->uPortPara.sSer.eBaud = MC_BAUD_4800;
                         break;
                        
                     case 4:
                         pu->uPortPara.sSer.eBaud = MC_BAUD_9600;
                         break;
                        
                     case 5:
                         pu->uPortPara.sSer.eBaud = MC_BAUD_19200;
                         break;
                        
                      case 6:
                           pu->uPortPara.sSer.eBaud = MC_BAUD_38400;
                           break;  
                           
                      case 7:
                           pu->uPortPara.sSer.eBaud = MC_BAUD_76800;
                           break;  
                      default:
                            #ifdef MC_DBG
                            MCDBG("emc_trans_afn04f25() para eBaud is error!");
                            #endif
                            pu->uPortPara.sSer.eBaud = MC_BAUD_UNKOWN;
                            //return MC_ERR_PARA;
                             break;
                }

                // bStop1
                if(ucSer & (1 << 4))
                {
                    pu->uPortPara.sSer.bStop1 = FALSE;
                }
                else
                {
                    pu->uPortPara.sSer.bStop1 = TRUE;
                }
                
                // bCheck
                if(ucSer & (1 << 3))
                {
                    pu->uPortPara.sSer.bCheck = TRUE;
                }
                else
                {
                    pu->uPortPara.sSer.bCheck = FALSE;
                }
                
                
                // bOdd          
                if(ucSer & (1 << 2))
                {
                    pu->uPortPara.sSer.bOdd = TRUE;
                }
                else
                {
                    pu->uPortPara.sSer.bOdd = FALSE;
                }

                // eBit
                switch(ucSer & 0x03)
                {
                    case 0:
                        pu->uPortPara.sSer.eBit = MC_SBIT_5;
                        break;
                        
                    case 1:
                        pu->uPortPara.sSer.eBit = MC_SBIT_6;
                        break;
                        
                    case 2:
                        pu->uPortPara.sSer.eBit = MC_SBIT_7;
                        break;
                        
                    case 3:
                        pu->uPortPara.sSer.eBit = MC_SBIT_8;
                        break;
                        
                    default:                         
                        #ifdef MC_DBG
                        MCDBG("emc_trans_afn04f25() para eBit is error!");
                        #endif
                        return MC_ERR_PARA;
                       // break;
                }
                   
                break;
                
            case 4:
                pu->eAcsPort = MC_ACS_PORT_ETH;     
                if(pf->ucAcsParaLen != sizeof(sMcAcsParaEth_f))
                {
                    #ifdef MC_DBG
                    MCDBG("emc_trans_afn04f25() ucAcsParaLen error %d!", pf->ucAcsParaLen);
                    #endif
                    return MC_ERR_LOGIC;
                }

                psEth = (sMcAcsParaEth_f *)pTmp;

                // usPort
                pu->uPortPara.sEth.usPort = psEth->usPort;

                // sIp  
                eRet = emc_trans_ip(eTrans, &(pu->uPortPara.sEth.sAccess), &(psEth->sAccess), &usTmpLen);
                if(eRet != MC_OK)
                {
                    #ifdef MC_DBG
                    MCDBG("emc_trans_afn04f25() emc_trans_ip() error %d!", eRet);
                    #endif
                    return eRet;
                }
                
                /*
                // sMask  
                eRet = emc_trans_ip(eTrans, &(pu->uPortPara.sEth.sMask), &(psEth->sMask), &usTmpLen);
                if(eRet != MC_OK)
                {
                    #ifdef MC_DBG
                    MCDBG("emc_trans_afn04f25() emc_trans_ip() error %d!", eRet);
                    #endif
                    return eRet;
                }
                
                // sGate
                eRet = emc_trans_ip(eTrans, &(pu->uPortPara.sEth.sGate), &(psEth->sGate), &usTmpLen);
                if(eRet != MC_OK)
                {
                    #ifdef MC_DBG
                    MCDBG("emc_trans_afn04f25() emc_trans_ip() error %d!", eRet);
                    #endif
                    return eRet;
                }
               */
                
                // �Ѿ��ں�߼��㳤��, ����ֻΪȥ������
                usTmpLen = usTmpLen;
                break;
                
            case 5:
                pu->eAcsPort = MC_ACS_PORT_ZIGB;      
                if(pf->ucAcsParaLen != sizeof(UINT32))
                {
                    #ifdef MC_DBG
                    MCDBG("emc_trans_afn04f25() ucAcsParaLen error %d!", pf->ucAcsParaLen);
                    #endif
                    return MC_ERR_LOGIC;
                }

                pulAddrZigb = (UINT32*)pTmp;
                pu->uPortPara.ulAddrZigb = *pulAddrZigb;
                break;
                
            default:
                #ifdef MC_DBG
                MCDBG("emc_trans_afn04f25() para eAcsPort is error!");
                #endif
                return MC_ERR_OUTRNG;
                //break;

        }

        // ���㳤��
        usLen += sizeof(UINT8) * 2 + pf->ucAcsParaLen;

        pTmp += pf->ucAcsParaLen;
        
        // usAcsPort
        pusAcsPort = (UINT16*)pTmp;
        pu->usAcsPort = *pusAcsPort;
        usLen += sizeof(UINT16);

        // ���Ժ�ڲ����޸� 2013/12/24
        // sIp
        pTmp += sizeof(UINT16);
        psMask = (sMcMask_f*)pTmp;
        eRet = emc_trans_ip(eTrans, &(pu->sAccess), psMask, &usTmpLen);
        if(eRet != MC_OK)
        {
            #ifdef MC_DBG
            MCDBG("emc_trans_afn04f25() emc_trans_ip() error %d!", eRet);
            #endif
            return eRet;
        }
        
        usLen += usTmpLen;

        /* ���Ժ�ڲ����޸� 2013/12/24
        // sMask
        pTmp += sizeof(UINT16);
        psMask = (sMcMask_f*)pTmp;
        eRet = emc_trans_ip(eTrans, &(pu->sMask), psMask, &usTmpLen);
        if(eRet != MC_OK)
        {
            #ifdef MC_DBG
            MCDBG("emc_trans_afn04f25() emc_trans_ip() error %d!", eRet);
            #endif
            return eRet;
        }
        
        usLen += usTmpLen;
        
        // sGateIp
        pTmp += sizeof(sMcMask_f);
        psGateIp = (sMcIp_f*)pTmp;
        eRet = emc_trans_ip(eTrans, &(pu->sGateIp), psGateIp, &usTmpLen);
        if(eRet != MC_OK)
        {
            #ifdef MC_DBG
            MCDBG("emc_trans_afn04f25() emc_trans_ip() error %d!", eRet);
            #endif
            return eRet;
        }
        
        usLen += usTmpLen;
        */
    }

    // �������
    * pusLen = usLen;
    return MC_OK;
}

/*****************************************************************************
 �� �� ��  : emc_trans_afn04f26
 ��������  : ���ݽṹת������
 ��Ӧ����  : MCMD_AFN_4_F26_ELEC_MP_BASE
 �������  : eMcTrans eTrans  
             void* pUser      
             void* pFrame     
 �������  : UINT16* pusLen  ���֡����ֽ���
 �� �� ֵ  : 
 ���ú���  : 
 ��������  : 
 
 �޸���ʷ      :
  1.��    ��   : 2013��11��8��
    ��    ��   : liming
    �޸�����   : �����ɺ���

*****************************************************************************/
eMcErr emc_trans_afn04f26(eMcTrans eTrans, void* pUser, void* pFrame, UINT16* pusLen)
{
    sMcAfn04f26_f      *pf = NULL;
    sMcAfn04f26        *pu = NULL;  
    UINT8            ucTmp = 0;
    eMcErr            eRet = MC_OK;
    UINT16           usLen = 0;
    sMcFmt_XXX_X     fU_f;
    sMcFmt_sXXX_XXX  fI_f;

    if(!pUser || !pFrame || !pusLen)
    {
        #ifdef MC_DBG
        MCDBG("emc_trans_afn04f26() para pointer is null!");
        #endif
        return MC_ERR_NULL;
    }

    pf = (sMcAfn04f26_f*)pFrame;
    pu = (sMcAfn04f26  *)pUser;

    // �û��ൽ��֡��
    if(MC_TRANS_U2F == eTrans)
    {
        // sDigit
        if(MC_DNUM_INTGR_MIN > pu->sDigit.ucInteger ||
           MC_DNUM_INTGR_MAX < pu->sDigit.ucInteger)
        {
           #ifdef MC_DBG
           MCDBG("emc_trans_afn04f26() sDigit.ucInteger is out of range! ucInteger = %d", pu->sDigit.ucInteger);
           #endif
           return MC_ERR_OUTRNG;   
        }
 
        if(MC_DNUM_DECIM_MIN > pu->sDigit.ucDecimal ||
           MC_DNUM_DECIM_MAX < pu->sDigit.ucDecimal)
        {
           #ifdef MC_DBG
           MCDBG("emc_trans_afn04f26() sDigit.ucDecimal is out of range! ucDecimal = %d", pu->sDigit.ucDecimal);
           #endif
           return MC_ERR_OUTRNG;   
        }

        // ʹ����0~3��
        pf->sDigit = 0; 
        ucTmp = pu->sDigit.ucDecimal - 1;
        pf->sDigit |= ucTmp;
        
        // ʹ����0~3��
        ucTmp = (pu->sDigit.ucInteger - 4) << 2;
        pf->sDigit |= ucTmp;
        usLen += sizeof(UINT8);       

        // usTimesU
        pf->usTimesU = pu->usTimesU;
        usLen += sizeof(UINT16);       

        // usTimesI
        pf->usTimesI = pu->usTimesI;
        usLen += sizeof(UINT16);     
        
        // fU
        eRet = emc_trans_XXX_X(eTrans, &(pu->fU), &fU_f);
        if(MC_OK != eRet)
        {
            #ifdef MC_DBG
            MCDBG("emc_trans_afn04f26() emc_trans_XXX_X() error %d!", eRet);
            #endif
            return eRet;
        }
        
        pf->fU = fU_f;
        usLen += sizeof(sMcFmt_XXX_X);

        // fI
        eRet = emc_trans_sXXX_XXX(eTrans, &(pu->fI), &fI_f);
        if(MC_OK != eRet)
        {
            #ifdef MC_DBG
            MCDBG("emc_trans_afn04f26() emc_trans_sXXX_XXX() error %d!", eRet);
            #endif
            return eRet;
        }
        
        pf->fI = fI_f;
        usLen += sizeof(sMcFmt_sXXX_XXX);  

        // sLinkWay
        pf->sLinkWay = 0;
        switch(pu->sLinkWay.eLink)
        {
            case MC_LINK_P3_L3:
                pf->sLinkWay = 1;
                break;
                
            case MC_LINK_P3_L4:
                pf->sLinkWay = 2;
                break;
                
            case MC_LINK_P1:
                pf->sLinkWay = 3;
                break;
                
            default:
               #ifdef MC_DBG
               MCDBG("emc_trans_afn04f26() sLinkWay.eLink is out of range!");
               #endif
               return MC_ERR_OUTRNG; 
               //break;
            
        }

        // ePhase
         switch(pu->sLinkWay.ePhase)
        {
            case MC_PHASE_UNKOWN:
                //pf->sLinkWay = 1;
                break;
                
            case MC_PHASE_A:
                pf->sLinkWay |= (1 << 2);
                break;
                
            case MC_PHASE_B:
                pf->sLinkWay |= (2 << 2);
                break;
                
            case MC_PHASE_C:
                pf->sLinkWay |= (3 << 2);
                break;
                
            default:
               #ifdef MC_DBG
               MCDBG("emc_trans_afn04f26() sLinkWay.ePhase is out of range!");
               #endif
               return MC_ERR_OUTRNG; 
               //break;
            
        }
         
        usLen += sizeof(UINT8);    
    }
    // ��֡�ൽ�û���
    else
    {
        // sDigit
        ucTmp = pf->sDigit & 0x03; 
        pu->sDigit.ucDecimal = ucTmp + 1;
        ucTmp = (UINT8)(pf->sDigit & 0x0C >> 2);
        pu->sDigit.ucInteger = ucTmp + 4;
        usLen += sizeof(UINT8);       

        // usTimesU
        pu->usTimesU = pf->usTimesU;
        usLen += sizeof(UINT16);       

        // usTimesI
        pu->usTimesI = pf->usTimesI;
        usLen += sizeof(UINT16);     
        
        // fU
        fU_f = pf->fU;
        eRet = emc_trans_XXX_X(eTrans, &(pu->fU), &fU_f);
        if(MC_OK != eRet)
        {
            #ifdef MC_DBG
            MCDBG("emc_trans_afn04f26() emc_trans_XXX_X() error %d!", eRet);
            #endif
            return eRet;
        }

        usLen += sizeof(sMcFmt_XXX_X);

        // fI
        fI_f = pf->fI;
        eRet = emc_trans_sXXX_XXX(eTrans, &(pu->fI), &fI_f);
        if(MC_OK != eRet)
        {
            #ifdef MC_DBG
            MCDBG("emc_trans_afn04f26() emc_trans_sXXX_XXX() error %d!", eRet);
            #endif
            return eRet;
        }

        usLen += sizeof(sMcFmt_sXXX_XXX);    
        
        // sLinkWay
        ucTmp = pf->sLinkWay & 0x03;
        switch(ucTmp)
        {
            case 1:
                pu->sLinkWay.eLink = MC_LINK_P3_L3;
                break;
                
            case 2:
                pu->sLinkWay.eLink = MC_LINK_P3_L4;
                break;
                
            case 3:
                pu->sLinkWay.eLink = MC_LINK_P1;
                break;
                
            default:
                #ifdef MC_DBG
                MCDBG("emc_trans_afn04f26() sLinkWay.eLink is out of range!");
                #endif
                pu->sLinkWay.eLink = MC_LINK_UNKOWN;
                break;
            
        }

        // ePhase
        ucTmp = (pf->sLinkWay & 0x0C) >> 2;

        switch(ucTmp)
        {
            case 0:
                pu->sLinkWay.ePhase = MC_PHASE_UNKOWN;
                break;
                
            case 1:
                pu->sLinkWay.ePhase = MC_PHASE_A;
                break;
                
            case 2:
                pu->sLinkWay.ePhase = MC_PHASE_B;
                break;
                
            case 3:
                pu->sLinkWay.ePhase = MC_PHASE_C;
                break;
                
            default:
                #ifdef MC_DBG
                MCDBG("emc_trans_afn04f26() sLinkWay.ePhase is out of range!");
                #endif
                return MC_ERR_OUTRNG; 
                //break;
        }
         
        usLen += sizeof(UINT8);        
    }

    // �������
    * pusLen = usLen;
    return MC_OK;
}

/*****************************************************************************
 �� �� ��  : emc_trans_afn04f27
 ��������  : ���ݽṹת������
 ��Ӧ����  : MCMD_AFN_4_F27_ELEC_LMIT_POWER
 �������  : eMcTrans eTrans  
             void* pUser      
             void* pFrame     
 �������  : UINT16* pusLen  ���֡����ֽ���
 �� �� ֵ  : 
 ���ú���  : 
 ��������  : 
 
 �޸���ʷ      :
  1.��    ��   : 2013��11��8��
    ��    ��   : liming
    �޸�����   : �����ɺ���

*****************************************************************************/
eMcErr emc_trans_afn04f27(eMcTrans eTrans, void* pUser, void* pFrame, UINT16* pusLen)
{
    eMcErr eRet       = MC_OK;
    sMcAfn04f27   *pu = NULL;
    sMcAfn04f27_f *pf = NULL;
    sMcFmt06_f     sFmt06_f;
    sMcFmt08_f     sFmt08_f;
    sMcFmt09_f     sFmt09_f;
    sMcFmt10_f     sFmt10_f;
    
    if(!pUser || !pFrame || !pusLen)
    {
        #ifdef MC_DBG
        MCDBG("emc_trans_afn04f27() para pointer is null!");
        #endif
        return MC_ERR_NULL;
    }

    pu = (sMcAfn04f27*)pUser;
    pf = (sMcAfn04f27_f*)pFrame;

    memset(&sFmt06_f, 0, sizeof(sMcFmt06_f));
    memset(&sFmt08_f, 0, sizeof(sMcFmt08_f));
    memset(&sFmt09_f, 0, sizeof(sMcFmt09_f));
    memset(&sFmt10_f, 0, sizeof(sMcFmt10_f));
    
    // �û��ൽ��֡��
    if(MC_TRANS_U2F == eTrans)
    {
        pf->ucTimeLossV    = pu->ucTimeLossV;
        pf->sOverV.ucTime  = pu->sOverI.ucTime;
        pf->sLossV.ucTime  = pu->sLossV.ucTime;  
        pf->sOverI.ucTime  = pu->sOverI.ucTime; 
        pf->sSuperI.ucTime = pu->sSuperI.ucTime; 
        pf->sZeroI.ucTime  = pu->sZeroI.ucTime;  
        pf->sUblV.ucTime   = pu->sUblV.ucTime; 
        pf->sUblI.ucTime   = pu->sUblI.ucTime; 

        // fDropV
        eRet = emc_trans_XXX_X(eTrans, &(pu->fDropV), &sFmt08_f);
        if(MC_OK != eRet)
        {
            #ifdef MC_DBG
            MCDBG("emc_trans_afn04f27() emc_trans_XXX_X() error %d!", eRet);
            #endif
            return eRet;
        }

        pf->fDropV = sFmt08_f;

        // sOverV.fUpUp
        eRet = emc_trans_XXX_X(eTrans, &(pu->sOverV.fUpUp), &sFmt08_f);
        if(MC_OK != eRet)
        {
            #ifdef MC_DBG
            MCDBG("emc_trans_afn04f27() emc_trans_sXXX_XXX() error %d!", eRet);
            #endif
            return eRet;
        }

        pf->sOverV.fUpUp = sFmt08_f;

        // sOverV.fFactor
        eRet = emc_trans_XX_XX(eTrans, &(pu->sOverV.fFactor), &sFmt10_f);
        if(MC_OK != eRet)
        {
            #ifdef MC_DBG
            MCDBG("emc_trans_afn04f27() emc_trans_XX_XX() error %d!", eRet);
            #endif
            return eRet;
        }

        pf->sOverV.fFactor = sFmt10_f;
        
        // sLossV.fDownDown
        eRet = emc_trans_XXX_X(eTrans, &(pu->sLossV.fDownDown), &sFmt08_f);
        if(MC_OK != eRet)
        {
            #ifdef MC_DBG
            MCDBG("emc_trans_afn04f27() emc_trans_XXX_X() error %d!", eRet);
            #endif
            return eRet;
        }

        pf->sLossV.fDownDown = sFmt08_f;

        // sLossV.fFactor
        eRet = emc_trans_XX_XX(eTrans, &(pu->sLossV.fFactor), &sFmt10_f);
        if(MC_OK != eRet)
        {
            #ifdef MC_DBG
            MCDBG("emc_trans_afn04f27() emc_trans_XX_XX() error %d!", eRet);
            #endif
            return eRet;
        }
        pf->sLossV.fFactor = sFmt10_f;

        // sOverI.fUpUp
        eRet = emc_trans_sXXX_XXX(eTrans, &(pu->sOverI.fUpUp), &sFmt09_f);
        if(MC_OK != eRet)
        {
            #ifdef MC_DBG
            MCDBG("emc_trans_afn04f27() emc_trans_sXXX_XXX() error %d!", eRet);
            #endif
            return eRet;
        }
        pf->sOverI.fUpUp = sFmt09_f;

        // sOverI.fFactor
        eRet = emc_trans_XX_XX(eTrans, &(pu->sOverI.fFactor), &sFmt10_f);
        if(MC_OK != eRet)
        {
            #ifdef MC_DBG
            MCDBG("emc_trans_afn04f27() emc_trans_XX_XX() error %d!", eRet);
            #endif
            return eRet;
        }

        pf->sOverI.fFactor = sFmt10_f;

        // sSuperI.fUp
        eRet = emc_trans_sXXX_XXX(eTrans, &(pu->sSuperI.fUp), &sFmt09_f);
        if(MC_OK != eRet)
        {
            #ifdef MC_DBG
            MCDBG("emc_trans_afn04f27() emc_trans_sXXX_XXX() error %d!", eRet);
            #endif
            return eRet;
        }

        pf->sSuperI.fUp = sFmt09_f;

        // sSuperI.fFactor
        eRet = emc_trans_XX_XX(eTrans, &(pu->sSuperI.fFactor), &sFmt10_f);
        if(MC_OK != eRet)
        {
            #ifdef MC_DBG
            MCDBG("emc_trans_afn04f27() emc_trans_XX_XX() error %d!", eRet);
            #endif
            return eRet;
        }

        pf->sSuperI.fFactor = sFmt10_f;

        // sZeroI.fUpUp
        eRet = emc_trans_sXXX_XXX(eTrans, &(pu->sZeroI.fUp), &sFmt09_f);
        if(MC_OK != eRet)
        {
            #ifdef MC_DBG
            MCDBG("emc_trans_afn04f27() emc_trans_sXXX_XXX() error %d!", eRet);
            #endif
            return eRet;
        }
        pf->sZeroI.fUp = sFmt09_f;

        // sZeroI.fFactor
        eRet = emc_trans_XX_XX(eTrans, &(pu->sZeroI.fFactor), &sFmt10_f);
        if(MC_OK != eRet)
        {
            #ifdef MC_DBG
            MCDBG("emc_trans_afn04f27() emc_trans_XX_XX() error %d!", eRet);
            #endif
            return eRet;
        }
        pf->sZeroI.fFactor = sFmt10_f;
        
        // sUblV.fLimit
        eRet = emc_trans_sXX_XXXX(eTrans, &(pu->sUblV.fLimit), &sFmt06_f);
        if(MC_OK != eRet)
        {
            #ifdef MC_DBG
            MCDBG("emc_trans_afn04f27() emc_trans_sXX_XXXX() error %d!", eRet);
            #endif
            return eRet;
        }
        pf->sUblV.fLimit = sFmt06_f;
        
        // sUblV.fFactor
        eRet = emc_trans_XX_XX(eTrans, &(pu->sUblV.fFactor), &sFmt10_f);
        if(MC_OK != eRet)
        {
            #ifdef MC_DBG
            MCDBG("emc_trans_afn04f27() emc_trans_XX_XX() error %d!", eRet);
            #endif
            return eRet;
        }
        pf->sUblV.fFactor = sFmt10_f;
        
        // sUblI.fLimit
        eRet = emc_trans_sXX_XXXX(eTrans, &(pu->sUblI.fLimit), &sFmt06_f);
        if(MC_OK != eRet)
        {
            #ifdef MC_DBG
            MCDBG("emc_trans_afn04f27() emc_trans_sXX_XXXX() error %d!", eRet);
            #endif
            return eRet;
        }
        pf->sUblI.fLimit = sFmt06_f;
        
        // sUblI.fFactor
        eRet = emc_trans_XX_XX(eTrans, &(pu->sUblI.fFactor), &sFmt10_f);
        if(MC_OK != eRet)
        {
            #ifdef MC_DBG
            MCDBG("emc_trans_afn04f27() emc_trans_XX_XX() error %d!", eRet);
            #endif
            return eRet;
        }

        pf->sUblI.fFactor = sFmt10_f;

    }
    // ��֡�ൽ�û���
    else if(MC_TRANS_F2U == eTrans)
    {
        pu->ucTimeLossV    = pf->ucTimeLossV;
        pu->sOverV.ucTime  = pf->sOverI.ucTime;
        pu->sLossV.ucTime  = pf->sLossV.ucTime;
        pu->sOverI.ucTime  = pf->sOverI.ucTime;
        pu->sSuperI.ucTime = pf->sSuperI.ucTime; 
        pu->sZeroI.ucTime  = pf->sZeroI.ucTime;  
        pu->sUblV.ucTime   = pf->sUblV.ucTime; 
        pu->sUblI.ucTime   = pf->sUblI.ucTime; 

        // fDropV
        sFmt08_f = pf->fDropV;
        eRet = emc_trans_XXX_X(eTrans, &(pu->fDropV), &sFmt08_f);
        if(MC_OK != eRet)
        {
            #ifdef MC_DBG
            MCDBG("emc_trans_afn04f27() emc_trans_XXX_X() error %d!", eRet);
            #endif
            return eRet;
        }

        // sOverV.fUpUp
        sFmt08_f = pf->sOverV.fUpUp ;
        eRet = emc_trans_XXX_X(eTrans, &(pu->sOverV.fUpUp), &sFmt08_f);
        if(MC_OK != eRet)
        {
            #ifdef MC_DBG
            MCDBG("emc_trans_afn04f27() emc_trans_sXXX_XXX() error %d!", eRet);
            #endif
            return eRet;
        }

        // sOverV.fFactor
        sFmt10_f  =  pf->sOverV.fFactor;
        eRet = emc_trans_XX_XX(eTrans, &(pu->sOverV.fFactor), &sFmt10_f);
        if(MC_OK != eRet)
        {
            #ifdef MC_DBG
            MCDBG("emc_trans_afn04f27() emc_trans_XX_XX() error %d!", eRet);
            #endif
            return eRet;
        }

        // sLossV.fDownDown
        sFmt08_f =  pf->sLossV.fDownDown;
        eRet = emc_trans_XXX_X(eTrans, &(pu->sLossV.fDownDown), &sFmt08_f);
        if(MC_OK != eRet)
        {
            #ifdef MC_DBG
            MCDBG("emc_trans_afn04f27() emc_trans_XXX_X() error %d!", eRet);
            #endif
            return eRet;
        }

        // sLossV.fFactor
        sFmt10_f = pf->sLossV.fFactor;

        eRet = emc_trans_XX_XX(eTrans, &(pu->sLossV.fFactor), &sFmt10_f);
        if(MC_OK != eRet)
        {
            #ifdef MC_DBG
            MCDBG("emc_trans_afn04f27() emc_trans_XX_XX() error %d!", eRet);
            #endif
            return eRet;
        }

        // sOverI.fUpUp
        sFmt09_f = pf->sOverI.fUpUp;
        eRet = emc_trans_sXXX_XXX(eTrans, &(pu->sOverI.fUpUp), &sFmt09_f);
        if(MC_OK != eRet)
        {
            #ifdef MC_DBG
            MCDBG("emc_trans_afn04f27() emc_trans_sXXX_XXX() error %d!", eRet);
            #endif
            return eRet;
        }

        // sOverI.fFactor
        sFmt10_f =  pf->sOverI.fFactor;
        eRet = emc_trans_XX_XX(eTrans, &(pu->sOverI.fFactor), &sFmt10_f);
        if(MC_OK != eRet)
        {
            #ifdef MC_DBG
            MCDBG("emc_trans_afn04f27() emc_trans_XX_XX() error %d!", eRet);
            #endif
            return eRet;
        }

        // sSuperI.fUp
        sFmt09_f = pf->sSuperI.fUp;
        eRet = emc_trans_sXXX_XXX(eTrans, &(pu->sSuperI.fUp), &sFmt09_f);
        if(MC_OK != eRet)
        {
            #ifdef MC_DBG
            MCDBG("emc_trans_afn04f27() emc_trans_sXXX_XXX() error %d!", eRet);
            #endif
            return eRet;
        }

        // sSuperI.fFactor
        sFmt10_f = pf->sSuperI.fFactor;
        eRet = emc_trans_XX_XX(eTrans, &(pu->sSuperI.fFactor), &sFmt10_f);
        if(MC_OK != eRet)
        {
            #ifdef MC_DBG
            MCDBG("emc_trans_afn04f27() emc_trans_XX_XX() error %d!", eRet);
            #endif
            return eRet;
        }

        // sZeroI.fUpUp
        sFmt09_f = pf->sZeroI.fUp;
        eRet = emc_trans_sXXX_XXX(eTrans, &(pu->sZeroI.fUp), &sFmt09_f);
        if(MC_OK != eRet)
        {
            #ifdef MC_DBG
            MCDBG("emc_trans_afn04f27() emc_trans_sXXX_XXX() error %d!", eRet);
            #endif
            return eRet;
        }

        // sZeroI.fFactor
        sFmt10_f = pf->sZeroI.fFactor;
        eRet = emc_trans_XX_XX(eTrans, &(pu->sZeroI.fFactor), &sFmt10_f);
        if(MC_OK != eRet)
        {
            #ifdef MC_DBG
            MCDBG("emc_trans_afn04f27() emc_trans_XX_XX() error %d!", eRet);
            #endif
            return eRet;
        }

        // sUblV.fLimit
        sFmt06_f = pf->sUblV.fLimit ;
        eRet = emc_trans_sXX_XXXX(eTrans, &(pu->sUblV.fLimit), &sFmt06_f);
        if(MC_OK != eRet)
        {
            #ifdef MC_DBG
            MCDBG("emc_trans_afn04f27() emc_trans_sXX_XXXX() error %d!", eRet);
            #endif
            return eRet;
        }

        // sUblV.fFactor
        sFmt10_f = pf->sUblV.fFactor;
        eRet = emc_trans_XX_XX(eTrans, &(pu->sUblV.fFactor), &sFmt10_f);
        if(MC_OK != eRet)
        {
            #ifdef MC_DBG
            MCDBG("emc_trans_afn04f27() emc_trans_XX_XX() error %d!", eRet);
            #endif
            return eRet;
        }

        // sUblI.fLimit
        sFmt06_f = pf->sUblI.fLimit;
        eRet = emc_trans_sXX_XXXX(eTrans, &(pu->sUblI.fLimit), &sFmt06_f);
        if(MC_OK != eRet)
        {
            #ifdef MC_DBG
            MCDBG("emc_trans_afn04f27() emc_trans_sXX_XXXX() error %d!", eRet);
            #endif
            return eRet;
        }

        // sUblI.fFactor
        sFmt10_f = pf->sUblI.fFactor;
        eRet = emc_trans_XX_XX(eTrans, &(pu->sUblI.fFactor), &sFmt10_f);
        if(MC_OK != eRet)
        {
            #ifdef MC_DBG
            MCDBG("emc_trans_afn04f27() emc_trans_XX_XX() error %d!", eRet);
            #endif
            return eRet;
        }
    }
    else
    {
        #ifdef MC_DBG
        MCDBG("emc_trans_afn04f27() para eTrans is out of range!");
        #endif
        return MC_ERR_OUTRNG;
    }

    // ���֡�೤��
    *pusLen = sizeof(sMcAfn04f27_f);
    return MC_OK;
}

/*****************************************************************************
 �� �� ��  : emc_trans_afn04f28
 ��������  : ���ݽṹת������
 ��Ӧ����  : MCMD_AFN_4_F28_ELEC_LMIT_FACTR
 �������  : eMcTrans eTrans  
             void* pUser      
             void* pFrame     
 �������  : UINT16* pusLen  ���֡����ֽ���
 �� �� ֵ  : 
 ���ú���  : 
 ��������  : 
 
 �޸���ʷ      :
  1.��    ��   : 2013��11��8��
    ��    ��   : liming
    �޸�����   : �����ɺ���

*****************************************************************************/
eMcErr emc_trans_afn04f28(eMcTrans eTrans, void* pUser, void* pFrame, UINT16* pusLen)
{
    eMcErr        eRet = MC_OK;
    sMcAfn04F28    *pu = NULL;
    sMcAfn04F28_f  *pf = NULL;
    sMcFmt10_f    sFmt10_f;

    if(!pUser || !pFrame || !pusLen)
    {
        #ifdef MC_DBG
        MCDBG("emc_trans_afn04f28() para pointer is null!");
        #endif
        return MC_ERR_NULL;
    }

    pu = (sMcAfn04F28*)pUser;
    pf = (sMcAfn04F28_f*)pFrame;
    memset(&sFmt10_f, 0, sizeof(sMcFmt10_f));

    if(MC_TRANS_F2U == eTrans)
    {
        // fPara1
        sFmt10_f = pf->fPara1;
        eRet = emc_trans_XX_XX(eTrans, &(pu->fPara1), &sFmt10_f);
        if(MC_OK != eRet)
        {
            #ifdef MC_DBG
            MCDBG("emc_trans_afn04f28() emc_trans_XX_XX() error %d!", eRet);
            #endif
            return eRet;
        }

        // fPara2
        sFmt10_f = pf->fPara2;
        eRet = emc_trans_XX_XX(eTrans, &(pu->fPara2), &sFmt10_f);
        if(MC_OK != eRet)
        {
            #ifdef MC_DBG
            MCDBG("emc_trans_afn04f28() emc_trans_XX_XX() error %d!", eRet);
            #endif
            return eRet;
        }

        // fWarning
        sFmt10_f = pf->fWarning;
        eRet = emc_trans_XX_XX(eTrans, &(pu->fWarning), &sFmt10_f);
        if(MC_OK != eRet)
        {
            #ifdef MC_DBG
            MCDBG("emc_trans_afn04f28() emc_trans_XX_XX() error %d!", eRet);
            #endif
            return eRet;
        }
        
    }
    else if( MC_TRANS_U2F == eTrans)
    {
        // fPara1
        eRet = emc_trans_XX_XX(eTrans, &(pu->fPara1), &sFmt10_f);
        if(MC_OK != eRet)
        {
            #ifdef MC_DBG
            MCDBG("emc_trans_afn04f28() emc_trans_XX_XX() error %d!", eRet);
            #endif
            return eRet;
        }
        pf->fPara1 = sFmt10_f;
        
        // fPara2
        eRet = emc_trans_XX_XX(eTrans, &(pu->fPara2), &sFmt10_f);
        if(MC_OK != eRet)
        {
            #ifdef MC_DBG
            MCDBG("emc_trans_afn04f28() emc_trans_XX_XX() error %d!", eRet);
            #endif
            return eRet;
        }
        pf->fPara2 = sFmt10_f;

        // fWarning
        eRet = emc_trans_XX_XX(eTrans, &(pu->fWarning), &sFmt10_f);
        if(MC_OK != eRet)
        {
            #ifdef MC_DBG
            MCDBG("emc_trans_afn04f28() emc_trans_XX_XX() error %d!", eRet);
            #endif
            return eRet;
        }
   
        pf->fWarning = sFmt10_f;
    }
    else
    {
       #ifdef MC_DBG
       MCDBG("emc_trans_afn04f28() para eTrans is out of range!");
       #endif
       return MC_ERR_OUTRNG;
    }

    // �������
    *pusLen = sizeof(sMcFactorLimit_f);
    return MC_OK;
}

/*****************************************************************************
 �� �� ��  : emc_trans_afn04f29
 ��������  : ���ݽṹת������
 ��Ӧ����  : MCMD_AFN_4_F29_ELEC_FIX_HARM
 �������  : eMcTrans eTrans  
             void* pUser      
             void* pFrame     
 �������  : UINT16* pusLen  ���֡����ֽ���
 �� �� ֵ  : 
 ���ú���  : 
 ��������  : 
 
 �޸���ʷ      :
  1.��    ��   : 2013��11��8��
    ��    ��   : liming
    �޸�����   : �����ɺ���

*****************************************************************************/
eMcErr emc_trans_afn04f29(eMcTrans eTrans, void* pUser, void* pFrame, UINT16* pusLen)
{
    eMcErr          eRet = MC_OK;
    sMcAfn04F29      *pu = NULL;
    sMcAfn04F29_f    *pf = NULL;
    sMcFmt10_f  sFmt10_f = {0};
    
    if(!pUser || !pFrame || !pusLen)
    {
        #ifdef MC_DBG
        MCDBG("emc_trans_afn04f29() para pointer is null!");
        #endif
        return MC_ERR_NULL;
    }

    pu = (sMcAfn04F29*)pUser;
    pf = (sMcAfn04F29_f*)pFrame;

    if(MC_TRANS_F2U == eTrans)
    {
        // (1)sVa
        // fTotal
        sFmt10_f = pf->sVa.fTotal;
        eRet = emc_trans_XX_XX(eTrans, &(pu->sVa.fTotal), &sFmt10_f);
        if(MC_OK != eRet)
        {
            #ifdef MC_DBG
            MCDBG("emc_trans_afn04f29() emc_trans_XX_XX() error %d!", eRet);
            #endif
            return eRet;
        }

        // fOdd
        sFmt10_f = pf->sVa.fOdd;
        eRet = emc_trans_XX_XX(eTrans, &(pu->sVa.fOdd), &sFmt10_f);
        if(MC_OK != eRet)
        {
            #ifdef MC_DBG
            MCDBG("emc_trans_afn04f29() emc_trans_XX_XX() error %d!", eRet);
            #endif
            return eRet;
        }

        // fEven
        sFmt10_f = pf->sVa.fEven;
        eRet = emc_trans_XX_XX(eTrans, &(pu->sVa.fEven), &sFmt10_f);
        if(MC_OK != eRet)
        {
            #ifdef MC_DBG
            MCDBG("emc_trans_afn04f29() emc_trans_XX_XX() error %d!", eRet);
            #endif
            return eRet;
        }

        // (2)sVb
        // fTotal
        sFmt10_f = pf->sVb.fTotal;
        eRet = emc_trans_XX_XX(eTrans, &(pu->sVb.fTotal), &sFmt10_f);
        if(MC_OK != eRet)
        {
            #ifdef MC_DBG
            MCDBG("emc_trans_afn04f29() emc_trans_XX_XX() error %d!", eRet);
            #endif
            return eRet;
        }

        // fOdd
        sFmt10_f = pf->sVb.fOdd;
        eRet = emc_trans_XX_XX(eTrans, &(pu->sVb.fOdd), &sFmt10_f);
        if(MC_OK != eRet)
        {
            #ifdef MC_DBG
            MCDBG("emc_trans_afn04f29() emc_trans_XX_XX() error %d!", eRet);
            #endif
            return eRet;
        }

        // fEven
        sFmt10_f = pf->sVb.fEven;
        eRet = emc_trans_XX_XX(eTrans, &(pu->sVb.fEven), &sFmt10_f);
        if(MC_OK != eRet)
        {
            #ifdef MC_DBG
            MCDBG("emc_trans_afn04f29() emc_trans_XX_XX() error %d!", eRet);
            #endif
            return eRet;
        }

        // (3)sVc
        // fTotal
        sFmt10_f = pf->sVc.fTotal;
        eRet = emc_trans_XX_XX(eTrans, &(pu->sVc.fTotal), &sFmt10_f);
        if(MC_OK != eRet)
        {
            #ifdef MC_DBG
            MCDBG("emc_trans_afn04f29() emc_trans_XX_XX() error %d!", eRet);
            #endif
            return eRet;
        }

        // fOdd
        sFmt10_f = pf->sVc.fOdd;
        eRet = emc_trans_XX_XX(eTrans, &(pu->sVc.fOdd), &sFmt10_f);
        if(MC_OK != eRet)
        {
            #ifdef MC_DBG
            MCDBG("emc_trans_afn04f29() emc_trans_XX_XX() error %d!", eRet);
            #endif
            return eRet;
        }

        // fEven
        sFmt10_f = pf->sVc.fEven;
        eRet = emc_trans_XX_XX(eTrans, &(pu->sVc.fEven), &sFmt10_f);
        if(MC_OK != eRet)
        {
            #ifdef MC_DBG
            MCDBG("emc_trans_afn04f29() emc_trans_XX_XX() error %d!", eRet);
            #endif
            return eRet;
        }

        // (4)sIa
        // fTotal
        sFmt10_f = pf->sIa.fTotal;
        eRet = emc_trans_XX_XX(eTrans, &(pu->sIa.fTotal), &sFmt10_f);
        if(MC_OK != eRet)
        {
            #ifdef MC_DBG
            MCDBG("emc_trans_afn04f29() emc_trans_XX_XX() error %d!", eRet);
            #endif
            return eRet;
        }

        // fOdd
        sFmt10_f = pf->sIa.fOdd;
        eRet = emc_trans_XX_XX(eTrans, &(pu->sIa.fOdd), &sFmt10_f);
        if(MC_OK != eRet)
        {
            #ifdef MC_DBG
            MCDBG("emc_trans_afn04f29() emc_trans_XX_XX() error %d!", eRet);
            #endif
            return eRet;
        }

        // fEven
        sFmt10_f = pf->sIa.fEven;
        eRet = emc_trans_XX_XX(eTrans, &(pu->sIa.fEven), &sFmt10_f);
        if(MC_OK != eRet)
        {
            #ifdef MC_DBG
            MCDBG("emc_trans_afn04f29() emc_trans_XX_XX() error %d!", eRet);
            #endif
            return eRet;
        }

        // (5)sIb
        // fTotal
        sFmt10_f = pf->sIb.fTotal;
        eRet = emc_trans_XX_XX(eTrans, &(pu->sIb.fTotal), &sFmt10_f);
        if(MC_OK != eRet)
        {
            #ifdef MC_DBG
            MCDBG("emc_trans_afn04f29() emc_trans_XX_XX() error %d!", eRet);
            #endif
            return eRet;
        }

        // fOdd
        sFmt10_f = pf->sIb.fOdd;
        eRet = emc_trans_XX_XX(eTrans, &(pu->sIb.fOdd), &sFmt10_f);
        if(MC_OK != eRet)
        {
            #ifdef MC_DBG
            MCDBG("emc_trans_afn04f29() emc_trans_XX_XX() error %d!", eRet);
            #endif
            return eRet;
        }

        // fEven
        sFmt10_f = pf->sIb.fEven;
        eRet = emc_trans_XX_XX(eTrans, &(pu->sIb.fEven), &sFmt10_f);
        if(MC_OK != eRet)
        {
            #ifdef MC_DBG
            MCDBG("emc_trans_afn04f29() emc_trans_XX_XX() error %d!", eRet);
            #endif
            return eRet;
        }

        // (6)sIc
        // fTotal
        sFmt10_f = pf->sIc.fTotal;
        eRet = emc_trans_XX_XX(eTrans, &(pu->sIc.fTotal), &sFmt10_f);
        if(MC_OK != eRet)
        {
            #ifdef MC_DBG
            MCDBG("emc_trans_afn04f29() emc_trans_XX_XX() error %d!", eRet);
            #endif
            return eRet;
        }

        // fOdd
        sFmt10_f = pf->sVb.fOdd;
        eRet = emc_trans_XX_XX(eTrans, &(pu->sIc.fOdd), &sFmt10_f);
        if(MC_OK != eRet)
        {
            #ifdef MC_DBG
            MCDBG("emc_trans_afn04f29() emc_trans_XX_XX() error %d!", eRet);
            #endif
            return eRet;
        }

        // fEven
        sFmt10_f = pf->sIc.fEven;
        eRet = emc_trans_XX_XX(eTrans, &(pu->sIc.fEven), &sFmt10_f);
        if(MC_OK != eRet)
        {
            #ifdef MC_DBG
            MCDBG("emc_trans_afn04f29() emc_trans_XX_XX() error %d!", eRet);
            #endif
            return eRet;
        }
    }
    else if(MC_TRANS_U2F == eTrans)
    {
        // (1)sVa
        // fTotal
        eRet = emc_trans_XX_XX(eTrans, &(pu->sVa.fTotal), &sFmt10_f);
        if(MC_OK != eRet)
        {
            #ifdef MC_DBG
            MCDBG("emc_trans_afn04f29() emc_trans_XX_XX() error %d!", eRet);
            #endif
            return eRet;
        }
        pf->sVa.fTotal = sFmt10_f;
            
        // fOdd
        eRet = emc_trans_XX_XX(eTrans, &(pu->sVa.fOdd), &sFmt10_f);
        if(MC_OK != eRet)
        {
            #ifdef MC_DBG
            MCDBG("emc_trans_afn04f29() emc_trans_XX_XX() error %d!", eRet);
            #endif
            return eRet;
        }
        pf->sVa.fOdd = sFmt10_f;
            
        // fEven
        eRet = emc_trans_XX_XX(eTrans, &(pu->sVa.fEven), &sFmt10_f);
        if(MC_OK != eRet)
        {
            #ifdef MC_DBG
            MCDBG("emc_trans_afn04f29() emc_trans_XX_XX() error %d!", eRet);
            #endif
            return eRet;
        }
        pf->sVa.fEven = sFmt10_f;
        
        // (2)sVb
        // fTotal
        eRet = emc_trans_XX_XX(eTrans, &(pu->sVb.fTotal), &sFmt10_f);
        if(MC_OK != eRet)
        {
            #ifdef MC_DBG
            MCDBG("emc_trans_afn04f29() emc_trans_XX_XX() error %d!", eRet);
            #endif
            return eRet;
        }
        pf->sVb.fTotal = sFmt10_f;
        
        // fOdd
        eRet = emc_trans_XX_XX(eTrans, &(pu->sVb.fOdd), &sFmt10_f);
        if(MC_OK != eRet)
        {
            #ifdef MC_DBG
            MCDBG("emc_trans_afn04f29() emc_trans_XX_XX() error %d!", eRet);
            #endif
            return eRet;
        }
        pf->sVb.fOdd = sFmt10_f;
        
        // fEven
        eRet = emc_trans_XX_XX(eTrans, &(pu->sVb.fEven), &sFmt10_f);
        if(MC_OK != eRet)
        {
            #ifdef MC_DBG
            MCDBG("emc_trans_afn04f29() emc_trans_XX_XX() error %d!", eRet);
            #endif
            return eRet;
        }
        pf->sVb.fEven = sFmt10_f;
        
        // (3)sVc
        // fTotal
        eRet = emc_trans_XX_XX(eTrans, &(pu->sVc.fTotal), &sFmt10_f);
        if(MC_OK != eRet)
        {
            #ifdef MC_DBG
            MCDBG("emc_trans_afn04f29() emc_trans_XX_XX() error %d!", eRet);
            #endif
            return eRet;
        }
        pf->sVc.fTotal = sFmt10_f;
        
        // fOdd
        eRet = emc_trans_XX_XX(eTrans, &(pu->sVc.fOdd), &sFmt10_f);
        if(MC_OK != eRet)
        {
            #ifdef MC_DBG
            MCDBG("emc_trans_afn04f29() emc_trans_XX_XX() error %d!", eRet);
            #endif
            return eRet;
        }
        pf->sVc.fOdd = sFmt10_f;
        
        // fEven
        eRet = emc_trans_XX_XX(eTrans, &(pu->sVc.fEven), &sFmt10_f);
        if(MC_OK != eRet)
        {
            #ifdef MC_DBG
            MCDBG("emc_trans_afn04f29() emc_trans_XX_XX() error %d!", eRet);
            #endif
            return eRet;
        }
        pf->sVc.fEven = sFmt10_f;
        
        // (4)sIa
        // fTotal
        eRet = emc_trans_XX_XX(eTrans, &(pu->sIa.fTotal), &sFmt10_f);
        if(MC_OK != eRet)
        {
            #ifdef MC_DBG
            MCDBG("emc_trans_afn04f29() emc_trans_XX_XX() error %d!", eRet);
            #endif
            return eRet;
        }
        pf->sIa.fTotal = sFmt10_f;
        
        // fOdd
        eRet = emc_trans_XX_XX(eTrans, &(pu->sIa.fOdd), &sFmt10_f);
        if(MC_OK != eRet)
        {
            #ifdef MC_DBG
            MCDBG("emc_trans_afn04f29() emc_trans_XX_XX() error %d!", eRet);
            #endif
            return eRet;
        }
        pf->sIa.fOdd = sFmt10_f;
        
        // fEven
        eRet = emc_trans_XX_XX(eTrans, &(pu->sIa.fEven), &sFmt10_f);
        if(MC_OK != eRet)
        {
            #ifdef MC_DBG
            MCDBG("emc_trans_afn04f29() emc_trans_XX_XX() error %d!", eRet);
            #endif
            return eRet;
        }
        pf->sIa.fEven = sFmt10_f;
        
        // (5)sIb
        // fTotal
        eRet = emc_trans_XX_XX(eTrans, &(pu->sIb.fTotal), &sFmt10_f);
        if(MC_OK != eRet)
        {
            #ifdef MC_DBG
            MCDBG("emc_trans_afn04f29() emc_trans_XX_XX() error %d!", eRet);
            #endif
            return eRet;
        }
        pf->sIb.fTotal = sFmt10_f;
        
        // fOdd
        eRet = emc_trans_XX_XX(eTrans, &(pu->sIb.fOdd), &sFmt10_f);
        if(MC_OK != eRet)
        {
            #ifdef MC_DBG
            MCDBG("emc_trans_afn04f29() emc_trans_XX_XX() error %d!", eRet);
            #endif
            return eRet;
        }
        pf->sIb.fOdd = sFmt10_f;
        
        // fEven
        eRet = emc_trans_XX_XX(eTrans, &(pu->sIb.fEven), &sFmt10_f);
        if(MC_OK != eRet)
        {
            #ifdef MC_DBG
            MCDBG("emc_trans_afn04f29() emc_trans_XX_XX() error %d!", eRet);
            #endif
            return eRet;
        }

        pf->sIb.fEven = sFmt10_f;
        
        // (6)sIc
        // fTotal
        eRet = emc_trans_XX_XX(eTrans, &(pu->sIc.fTotal), &sFmt10_f);
        if(MC_OK != eRet)
        {
            #ifdef MC_DBG
            MCDBG("emc_trans_afn04f29() emc_trans_XX_XX() error %d!", eRet);
            #endif
            return eRet;
        }
        pf->sIc.fTotal = sFmt10_f;
        
        // fOdd
        eRet = emc_trans_XX_XX(eTrans, &(pu->sIc.fOdd), &sFmt10_f);
        if(MC_OK != eRet)
        {
            #ifdef MC_DBG
            MCDBG("emc_trans_afn04f29() emc_trans_XX_XX() error %d!", eRet);
            #endif
            return eRet;
        }
        pf->sVb.fOdd = sFmt10_f;
        
        // fEven
        eRet = emc_trans_XX_XX(eTrans, &(pu->sIc.fEven), &sFmt10_f);
        if(MC_OK != eRet)
        {
            #ifdef MC_DBG
            MCDBG("emc_trans_afn04f29() emc_trans_XX_XX() error %d!", eRet);
            #endif
            return eRet;
        }
        pf->sIc.fEven = sFmt10_f;
    }
    else
    {
       #ifdef MC_DBG
       MCDBG("emc_trans_afn04f29() para eTrans is out of range!");
       #endif
       return MC_ERR_OUTRNG;
    }
        
    // �������
    *pusLen = sizeof(sMcElecFixHarm_f);
    return MC_OK;
}

/*****************************************************************************
 �� �� ��  : emc_trans_afn04f30
 ��������  : ���ݽṹת������
 ��Ӧ����  : MCMD_AFN_4_F30_ELEC_FLASH
 �������  : eMcTrans eTrans  
             void* pUser      
             void* pFrame     
 �������  : UINT16* pusLen  ���֡����ֽ���
 �� �� ֵ  : 
 ���ú���  : 
 ��������  : 
 
 �޸���ʷ      :
  1.��    ��   : 2013��11��11��
    ��    ��   : liming
    �޸�����   : �����ɺ���

*****************************************************************************/
eMcErr emc_trans_afn04f30(eMcTrans eTrans, void* pUser, void* pFrame, UINT16* pusLen)
{
    eMcErr        eRet = MC_OK;
    sMcAfn04f30    *pu = NULL;
    sMcAfn04f30_f  *pf = NULL;
    sMcFmt10_f sFmt10_f;
    
    if(!pUser || !pFrame || !pusLen)
    {
        #ifdef MC_DBG
        MCDBG("emc_trans_afn04f30() para pointer is null!");
        #endif
        return MC_ERR_NULL;
    }

    pu = (sMcAfn04f30*)pUser;
    pf = (sMcAfn04f30_f*)pFrame;
    memset(&sFmt10_f, 0, sizeof(sMcFmt10_f));

    if(MC_TRANS_F2U == eTrans)
    {
        // fLong
        sFmt10_f = pf->fLong;
        eRet = emc_trans_XX_XX(eTrans, &(pu->fLong), &sFmt10_f);
        if(MC_OK != eRet)
        {
            #ifdef MC_DBG
            MCDBG("emc_trans_afn04f30() emc_trans_XX_XX() error %d!", eRet);
            #endif
            return eRet;
        }

        // fShort
        sFmt10_f = pf->fShort;
        eRet = emc_trans_XX_XX(eTrans, &(pu->fShort), &sFmt10_f);
        if(MC_OK != eRet)
        {
            #ifdef MC_DBG
            MCDBG("emc_trans_afn04f30() emc_trans_XX_XX() error %d!", eRet);
            #endif
            return eRet;
        }
    }
    else if(MC_TRANS_U2F == eTrans)
    {
        // fLong
        eRet = emc_trans_XX_XX(eTrans, &(pu->fLong), &sFmt10_f);
        if(MC_OK != eRet)
        {
            #ifdef MC_DBG
            MCDBG("emc_trans_afn04f30() emc_trans_XX_XX() error %d!", eRet);
            #endif
            return eRet;
        }
        
        pf->fLong = sFmt10_f;
        
        // fShort
        eRet = emc_trans_XX_XX(eTrans, &(pu->fShort), &sFmt10_f);
        if(MC_OK != eRet)
        {
            #ifdef MC_DBG
            MCDBG("emc_trans_afn04f30() emc_trans_XX_XX() error %d!", eRet);
            #endif
            return eRet;
        }
        
        pf->fShort = sFmt10_f;
    }
    else
    {
       #ifdef MC_DBG
       MCDBG("emc_trans_afn04f30() para eTrans is out of range!");
       #endif
       return MC_ERR_OUTRNG;
    }
    
    // �������
    *pusLen = sizeof(sMcElecFlash_f);
    return MC_OK;
}

/*****************************************************************************
 �� �� ��  : emc_trans_afn04f33
 ��������  : ���ݽṹת������
 ��Ӧ����  : MCMD_AFN_4_F33_NELC_MP_CFG
 �������  : eMcTrans eTrans  
             void* pUser      
             void* pFrame     
 �������  : UINT16* pusLen  ���֡����ֽ���
 �� �� ֵ  : 
 ���ú���  : 
 ��������  : 
 
 �޸���ʷ      :
  1.��    ��   : 2013��11��11��
    ��    ��   : liming
    �޸�����   : �����ɺ���

*****************************************************************************/
eMcErr emc_trans_afn04f33(eMcTrans eTrans, void* pUser, void* pFrame, UINT16* pusLen)
{
    return emc_trans_afn04f25(eTrans, pUser, pFrame,  pusLen);
}

/*****************************************************************************
 �� �� ��  : emc_trans_afn04f34
 ��������  : ���ݽṹת������
 ��Ӧ����  : MCMD_AFN_4_F34_NELC_MP_PARA
 �������  : eMcTrans eTrans  
             void* pUser      
             void* pFrame     
 �������  : UINT16* pusLen  ���֡����ֽ���
 �� �� ֵ  : 
 ���ú���  : 
 ��������  : 
 
 �޸���ʷ      :
  1.��    ��   : 2013��11��11��
    ��    ��   : liming
    �޸�����   : �����ɺ���

*****************************************************************************/
eMcErr emc_trans_afn04f34(eMcTrans eTrans, void* pUser, void* pFrame, UINT16* pusLen)
{
    eMcErr        eRet = MC_OK;
    UINT8        ucTmp = 0;
    sMcAfn04f34    *pu = NULL;
    sMcAfn04f34_f  *pf = NULL;
    sMcFmt11_f     sDouble_f;            
    sMcDouble      sDouble;     
    sMcDouble      sUp;          
    sMcDouble      sDown;  

    if(!pUser || !pFrame || !pusLen)
    {
        #ifdef MC_DBG
        MCDBG("emc_trans_afn04f34() para pointer is null!");
        #endif
        return MC_ERR_NULL;
    }

    pu = (sMcAfn04f34*)pUser;
    pf = (sMcAfn04f34_f*)pFrame;
    memset(&sDouble_f, 0, sizeof(sMcFmt11_f));
    memset(&sDouble, 0, sizeof(sMcDouble));
    memset(&sUp, 0, sizeof(sMcDouble));
    memset(&sDown, 0, sizeof(sMcDouble));

    // �û��ൽ��֡��
    if(MC_TRANS_U2F == eTrans)
    {
        sUp.ePrec    = pu->sUp.ePrec;
        sUp.dValue   = pu->sUp.dValue;
        sDown.ePrec  = pu->sDown.ePrec;
        sDown.dValue = pu->sDown.dValue;

        #ifdef MC_DBG
        MCDBG("emc_trans_afn04f34()u2f pu->sUp ePrec =%d dValue =%f", pu->sUp.ePrec, pu->sUp.dValue);
        MCDBG("emc_trans_afn04f34() u2f pu->sDown ePrec =%d dValue =%f", pu->sDown.ePrec, pu->sDown.dValue);
        #endif

        // eType
        switch(pu->eType)
        {
            case MC_NELC_TEMP:
                ucTmp = 1;
                break;
                
            case MC_NELC_FLOW:
                ucTmp = 2;
                break;

            case MC_NELC_FV:
                ucTmp = 3;
                break;
                
            case MC_NELC_PRESS:
                ucTmp = 4;
                break;    
                
            case MC_NELC_HUMI:
                ucTmp = 5;
                break;
                
            case MC_NELC_LIGHT:
                ucTmp = 6;
                break;
                
            case MC_NELC_RV:
                ucTmp = 7;
                break;
                
            case MC_NELC_420MA:
                ucTmp = 8;
                break;
                
            default:
                #ifdef MC_DBG
                MCDBG("emc_trans_afn04f34() eType is out of range!");
                #endif
                return MC_ERR_OUTRNG;      
               // break;
        }
        
        pf->eType = ucTmp;

        // sUp
        eRet = emc_trans_sX7(eTrans, &sUp, &sDouble_f);
        if(MC_OK != eRet)
        {
            #ifdef MC_DBG
            MCDBG("emc_trans_afn04f34() emc_trans_sX7() error %d!", eRet);
            #endif
            return eRet;
        }

        pf->sUp = sDouble_f;

        // sDown
        eRet = emc_trans_sX7(eTrans, &sDown, &sDouble_f);
        if(MC_OK != eRet)
        {
            #ifdef MC_DBG
            MCDBG("emc_trans_afn04f34() emc_trans_sX7() error %d!", eRet);
            #endif
            return eRet;
        }

        pf->sDown = sDouble_f;
    }
    // ��֡�ൽ�û���
    else if (MC_TRANS_F2U == eTrans)
    {
        switch(pf->eType)
        {
            case 1:
                pu->eType = MC_NELC_TEMP;
                break;
                
            case 2:
                pu->eType = MC_NELC_FLOW;
                break;

            case 3:
                pu->eType = MC_NELC_FV;
                break;

            case 4:
                pu->eType = MC_NELC_PRESS;
                break;

            case 5:
                pu->eType = MC_NELC_HUMI;
                break;
                
            case 6:
                pu->eType = MC_NELC_LIGHT;
                break;
                
            case 7:
                pu->eType = MC_NELC_RV;
                break;
                
            case 8:
                pu->eType = MC_NELC_420MA;
                break;
                
            default:
                pu->eType = MC_NELC_UNKOWN;
                break;
        }

        // sUp
        sDouble_f  = pf->sUp ;
        eRet = emc_trans_sX7(eTrans, &sDouble, &sDouble_f);
        if(MC_OK != eRet)
        {
            #ifdef MC_DBG
            MCDBG("emc_trans_afn04f34() emc_trans_sX7() error %d!", eRet);
            #endif
            return eRet;
        }
        
        pu->sUp = sDouble;
        
        // sDown
        sDouble_f  = pf->sDown ;
        eRet = emc_trans_sX7(eTrans, &sDouble, &sDouble_f);
        if(MC_OK != eRet)
        {
            #ifdef MC_DBG
            MCDBG("emc_trans_afn04f34() emc_trans_sX7() error %d!", eRet);
            #endif
            return eRet;
        }

        pu->sDown = sDouble;

        #ifdef MC_DBG
        MCDBG("emc_trans_afn04f34() f2u pu->sUp ePrec =%d dValue =%f", pu->sUp.ePrec, pu->sUp.dValue);
        MCDBG("emc_trans_afn04f34() f2u pu->sDown ePrec =%d dValue =%f", pu->sDown.ePrec, pu->sDown.dValue);
        #endif
    }
    else
    {
         #ifdef MC_DBG
         MCDBG("emc_trans_afn04f34() eTrans is out of range!");
         #endif
         return MC_ERR_OUTRNG;    
    }
    
    // �������
    *pusLen = sizeof(sMcAfn04f34_f);
    return MC_OK;
}

/*****************************************************************************
 �� �� ��  : emc_trans_afn04f35
 ��������  : ���ݽṹת������
 ��Ӧ����  : MCMD_AFN_4_F35_NELC_MP_LMIT
 �������  : eMcTrans eTrans  
             void* pUser      
             void* pFrame     
 �������  : UINT16* pusLen  ���֡����ֽ���
 �� �� ֵ  : 
 ���ú���  : 
 ��������  : 
 
 �޸���ʷ      :
  1.��    ��   : 2013��11��11��
    ��    ��   : liming
    �޸�����   : �����ɺ���

*****************************************************************************/
eMcErr emc_trans_afn04f35(eMcTrans eTrans, void* pUser, void* pFrame, UINT16* pusLen)
{
    return emc_trans_afn04f34(eTrans, pUser, pFrame, pusLen);
}

/*****************************************************************************
 �� �� ��  : emc_trans_afn04f49
 ��������  : ���ݽṹת������
 ��Ӧ����  : MCMD_AFN_4_F49_FREZ_TASK_PARA
 �������  : eMcTrans eTrans  
             void* pUser      
             void* pFrame     
 �������  : UINT16* pusLen  ���֡����ֽ���
 �� �� ֵ  : 
 ���ú���  : 
 ��������  : 
 
 �޸���ʷ      :
  1.��    ��   : 2013��11��12��
    ��    ��   : liming
    �޸�����   : �����ɺ���

*****************************************************************************/
eMcErr emc_trans_afn04f49(eMcTrans eTrans, void* pUser, void* pFrame, UINT16* pusLen)
{
    eMcErr          eRet       = MC_OK;
    UINT8           ucNum      = 0;
    sMcAfn04f49     *pu        = NULL;
    sMcAfn04f49_f   *pf        = NULL;
    sMcDaDt         *pDaDt     = NULL;
    sMcFmt01_f      *psTime_f  = NULL;
    UINT8           *pucTmp    = NULL;
    UINT16          usLen      = 0;
    sMcFmt01_f      sFmt01_f;
    
    if(!pUser || !pFrame || !pusLen)
    {
        #ifdef MC_DBG
        MCDBG("emc_trans_afn04f49() para pointer is null!");
        #endif
        return MC_ERR_NULL;
    }

    pu = (sMcAfn04f49*)pUser;
    pf = (sMcAfn04f49_f*)pFrame;
    memset(&sFmt01_f, 0, sizeof(sMcFmt01_f));

    // �û��ൽ��֡��
    if(MC_TRANS_U2F == eTrans)
    {
        // sTime
        eRet = emc_trans_YWMDhms(eTrans, &(pu->sTimeFrez), &sFmt01_f);
        if(MC_OK != eRet)
        {       
            #ifdef MC_DBG
            MCDBG("emc_trans_afn04f49() emc_trans_YWMDhms() error %d!", eRet);
            #endif
            return eRet;
        }
        pf->sTimeFrez = sFmt01_f;
        usLen += sizeof(sMcFmt01_f);
        
        // sFreez.usPeriod
        pf->sFreez.usPeriod = pu->sFreez.usPeriod;
   
        // sFreez.eUnit
        switch(pu->sFreez.eUnit)
        {
            case MC_PUNT_MONTH:
                pf->sFreez.eUnit = 1;
                break;
                
            case MC_PUNT_DAY:
                pf->sFreez.eUnit = 2;
                break;
                    
            case MC_PUNT_HOUR:
                pf->sFreez.eUnit = 3;
                break;

            case MC_PUNT_MIN:
                pf->sFreez.eUnit = 4;
                break;

            case MC_PUNT_SEC:
                pf->sFreez.eUnit = 5;
                break;
                    
            case MC_PUNT_MS:
                pf->sFreez.eUnit = 6;
                break;
           default:
                #ifdef MC_DBG
                MCDBG("emc_trans_afn04f49() para pointer is error!");
                #endif
                return MC_ERR_PARA;
                //break;
        }

        // sFreez.ucTimes
        pf->sFreez.ucTimes = pu->sFreez.ucTimes;
        usLen += sizeof(sMcFrezPeriod_f);
        
        // cmd pn 
        pDaDt = (sMcDaDt*)(&(pf->ucDaDtNum) + 1);
        eRet = emc_cmdpn_to_dadt(MC_AFN_13_ASKR, pDaDt, &ucNum, &(pu->sCmdPn[0]), pu->uCmdPnNum);
        if(MC_OK != eRet)
        {       
            #ifdef MC_DBG
            MCDBG("emc_trans_afn04f49() emc_cmdpn_to_dadt() error %d!", eRet);
            #endif
            return eRet;
        }

        pf->ucDaDtNum = ucNum;
        usLen += sizeof(sMcDaDt) * ucNum + sizeof(UINT8); 
        
        // sTimeRprt
        pucTmp = (UINT8*)(pDaDt + ucNum);
        psTime_f = (sMcFmt01_f *)pucTmp; 
        eRet = emc_trans_YWMDhms(eTrans, &(pu->sTimeRprt), psTime_f);
        if(MC_OK != eRet)
        {       
            #ifdef MC_DBG
            MCDBG("emc_trans_afn04f49() emc_trans_YWMDhms() error %d!", eRet);
            #endif
            return eRet;
        }
        
        usLen += sizeof(sMcFmt01_f);

        // ucPeriodRpt
        pucTmp += sizeof(sMcFmt01_f);
        *pucTmp = pu->ucPeriodRpt;
        usLen += sizeof(UINT8);

        // eUnitRpt
        pucTmp += 1;
        switch(pu->eUnitRpt)
        {
            case MC_PUNT_MONTH:
                *pucTmp = 4;
                break;
                
            case MC_PUNT_DAY:
                *pucTmp = 3;
                break;
                    
            case MC_PUNT_HOUR:
                *pucTmp = 2;
                break;

            case MC_PUNT_MIN:
                *pucTmp = 1;
                break;
                
           default:
                #ifdef MC_DBG
                MCDBG("emc_trans_afn04f49() para eUnitRpt is error!,%d",pu->eUnitRpt);
                #endif
                return MC_ERR_PARA;
                //break;
        }

        usLen += sizeof(UINT8); 
    }
    // ��֡�ൽ�û���
    else if (MC_TRANS_F2U == eTrans)
    {
        // sTime
        sFmt01_f = pf->sTimeFrez;
        eRet = emc_trans_YWMDhms(eTrans, &(pu->sTimeFrez), &sFmt01_f);
        if(MC_OK != eRet)
        {       
            #ifdef MC_DBG
            MCDBG("emc_trans_afn04f49() emc_trans_YWMDhms() error %d!", eRet);
            #endif
            return eRet;
        }

        usLen += sizeof(sMcFmt01_f);
        
        // sFreez.usPeriod
        pu->sFreez.usPeriod = pf->sFreez.usPeriod;

        // sFreez.eUnit
        switch(pf->sFreez.eUnit)
        {
            case 1:
                pu->sFreez.eUnit = MC_PUNT_MONTH;
                break;
                
            case 2:
                pu->sFreez.eUnit = MC_PUNT_DAY;
                break;
                    
            case 3:
                pu->sFreez.eUnit = MC_PUNT_HOUR;
                break;

            case 4:
                pu->sFreez.eUnit = MC_PUNT_MIN;
                break;

            case 5:
                pu->sFreez.eUnit = MC_PUNT_SEC;
                break;
                    
            case 6:
                pu->sFreez.eUnit = MC_PUNT_MS;
                break;
                
           default:
                #ifdef MC_DBG
                MCDBG("emc_trans_afn04f49() para pointer is error!");
                #endif
                pu->sFreez.eUnit = MC_PUNT_UNKOWN;
                break;
        }

        // sFreez.ucTimes
        pu->sFreez.ucTimes = pf->sFreez.ucTimes;
        usLen += sizeof(sMcFrezPeriod_f);

        // cmd pn 
        pDaDt = (sMcDaDt*)(&(pf->ucDaDtNum) + 1);
        eRet = emc_dadt_to_cmdpn(MC_AFN_13_ASKR, pDaDt, pf->ucDaDtNum, &(pu->sCmdPn[0]), &ucNum);
        if(MC_OK != eRet)
        {       
            #ifdef MC_DBG
            MCDBG("emc_trans_afn04f49() emc_dadt_to_cmdpn() error %d!", eRet);
            #endif
            return eRet;
        }

        pu->uCmdPnNum = ucNum;
        usLen += sizeof(sMcDaDt) * ucNum + sizeof(UINT8); 
        
        // sTimeRprt
        pucTmp = (UINT8*)(pDaDt + pf->ucDaDtNum);
        psTime_f = (sMcFmt01_f *)pucTmp; 
        eRet = emc_trans_YWMDhms(eTrans, &(pu->sTimeRprt), psTime_f);
        if(MC_OK != eRet)
        {       
            #ifdef MC_DBG
            MCDBG("emc_trans_afn04f49() emc_trans_YWMDhms() error %d!", eRet);
            #endif
            return eRet;
        }
        
        usLen += sizeof(sMcFmt01_f);

        // ucPeriodRpt
        pucTmp += sizeof(sMcFmt01_f);
        pu->ucPeriodRpt = *pucTmp;
        usLen += sizeof(UINT8);

        // eUnitRpt
        pucTmp += 1;
        switch(*pucTmp)
        {
            case 4:
                pu->eUnitRpt = MC_PUNT_MONTH;
                break;
                
            case 3:
                pu->eUnitRpt = MC_PUNT_DAY;
                break;
                    
            case 2:
                pu->eUnitRpt = MC_PUNT_HOUR;
                break;

            case 1:
                pu->eUnitRpt = MC_PUNT_MIN;
                break;
                
           default:
                #ifdef MC_DBG
                MCDBG("emc_trans_afn04f49() para eUnitRpt is error!");
                #endif
                pu->eUnitRpt = MC_PUNT_UNKOWN;
                //return MC_ERR_PARA;
                break;
        }

        usLen += sizeof(UINT8);  
    }
    else
    {
         #ifdef MC_DBG
         MCDBG("emc_trans_afn04f49() eTrans is out of range!");
         #endif
         return MC_ERR_OUTRNG;    
    }

    // �������
    *pusLen = usLen;
    return MC_OK;
}

/*****************************************************************************
 �� �� ��  : emc_trans_afn05f1
 ��������  : ���ݽṹת������
 ��Ӧ����  : MCMD_AFN_5_F1_CHECK_TIME
 �������  : eMcTrans eTrans  
             void* pUser      
             void* pFrame     
 �������  : UINT16* pusLen  ���֡����ֽ���
 �� �� ֵ  : 
 ���ú���  : 
 ��������  : 
 
 �޸���ʷ      :
  1.��    ��   : 2013��11��12��
    ��    ��   : liming
    �޸�����   : �����ɺ���

*****************************************************************************/
eMcErr emc_trans_afn05f1(eMcTrans eTrans, void* pUser, void* pFrame, UINT16* pusLen)
{
    eMcErr       eRet = MC_OK;
    sMcYWMDhms    *pu = NULL;
    sMcYWMDhms_f  *pf = NULL;
    
    if(!pUser || !pFrame || !pusLen)
    {
        #ifdef MC_DBG
        MCDBG("emc_trans_afn05f1() para pointer is null!");
        #endif
        return MC_ERR_NULL;
    }
    
    pu = (sMcYWMDhms*)pUser;
    pf = (sMcYWMDhms_f *)pFrame;
    
    eRet = emc_trans_YWMDhms(eTrans, pu, pf);
    if(MC_OK != eRet)
    {
        #ifdef MC_DBG
        MCDBG("emc_trans_afn05f1() emc_trans_YWMDhms() error %d!", eRet);
        #endif
        return eRet;
    }

    // �������
    *pusLen = sizeof(sMcYWMDhms_f);
    return MC_OK;
}

/*****************************************************************************
 �� �� ��  : emc_trans_afn05f2
 ��������  : ���ݽṹת������
 ��Ӧ����  : MCMD_AFN_5_F2_FREZ_TEMP
 �������  : eMcTrans eTrans  
             void* pUser      
             void* pFrame     
 �������  : UINT16* pusLen  ���֡����ֽ���
 �� �� ֵ  : 
 ���ú���  : 
 ��������  : 
 
 �޸���ʷ      :
  1.��    ��   : 2013��11��12��
    ��    ��   : liming
    �޸�����   : �����ɺ���

*****************************************************************************/
eMcErr emc_trans_afn05f2(eMcTrans eTrans, void* pUser, void* pFrame, UINT16* pusLen)
{  
    eMcErr       eRet = MC_OK;
    sMcAfn05f2    *pu = NULL;
    sMcAfn05f2_f  *pf = NULL;
    UINT8       ucTmp = 0;
    
    if(!pUser || !pFrame || !pusLen)
    {
        #ifdef MC_DBG
        MCDBG("emc_trans_afn05f1() para pointer is null!");
        #endif
        return MC_ERR_NULL;
    }
    
    pu = (sMcAfn05f2*)pUser;
    pf = (sMcAfn05f2_f *)pFrame;

    // �û��ൽ��֡��
    if(MC_TRANS_U2F == eTrans)
    {
        eRet = emc_cmdpn_to_dadt(MC_AFN_13_ASKR, &(pf->sDaDt[0]), &ucTmp, &(pu->sCmdPn[0]), pu->ucNum);
        if(MC_OK != eRet)
        {
            #ifdef MC_DBG
            MCDBG("emc_trans_afn05f2() emc_cmdpn_to_dadt() error %d!", eRet);
            #endif
            return eRet;
        }

        // ucNum
        pf->ucNum = ucTmp;
    }
    // ��֡�ൽ�û���
    else if(MC_TRANS_F2U == eTrans)
    {
        eRet = emc_dadt_to_cmdpn(MC_AFN_13_ASKR, &(pf->sDaDt[0]), pf->ucNum, &(pu->sCmdPn[0]), &ucTmp);
        if(MC_OK != eRet)
        {
            #ifdef MC_DBG
            MCDBG("emc_trans_afn05f2() emc_dadt_to_cmdpn() error %d!", eRet);
            #endif
            return eRet;
        }

        pu->ucNum = ucTmp;
    }
    else
    {
         #ifdef MC_DBG
         MCDBG("emc_trans_afn05f2() eTrans is out of range!");
         #endif
         return MC_ERR_OUTRNG;    
    }
    
    // �������
    *pusLen = sizeof(sMcDaDt)*ucTmp + sizeof(pf->ucNum);
    return MC_OK;
}

/*****************************************************************************
 �� �� ��  : emc_trans_afn05f9
 ��������  : ���ݽṹת������
 ��Ӧ����  : MCMD_AFN_5_F9_REMOTE_OFF
 �������  : eMcTrans eTrans  
             void* pUser      
             void* pFrame     
 �������  : UINT16* pusLen  ���֡����ֽ���
 �� �� ֵ  : 
 ���ú���  : 
 ��������  : 
 
 �޸���ʷ      :
  1.��    ��   : 2013��11��12��
    ��    ��   : liming
    �޸�����   : �����ɺ���

*****************************************************************************/
eMcErr emc_trans_afn05f9(eMcTrans eTrans, void* pUser, void* pFrame, UINT16* pusLen)
{  
    eMcErr       eRet = MC_OK;
    sMcAfn05f9    *pu = NULL;
    sMcAfn05f9_f  *pf = NULL;
    INT32           i = 0;
    sMcYMDhm_f sYMDhm_f;
    
    if(!pUser || !pFrame || !pusLen)
    {
        #ifdef MC_DBG
        MCDBG("emc_trans_afn05f9() para pointer is null!");
        #endif
        return MC_ERR_NULL;
    }
   
    pu = (sMcAfn05f9*)pUser;
    pf = (sMcAfn05f9_f *)pFrame;
    memset(&sYMDhm_f, 0, sizeof(sMcYMDhm_f));

    // �û��ൽ��֡��
    if(MC_TRANS_U2F == eTrans)
    {
        // bOff
        pf->bOff = 0;
        for(i = 0; i < 8; i++)
        {
            if(TRUE == pu->bOff[i])
            {
                pf->bOff |= (0x01 << i);
            }
        }
        
        // sTimeStart
        eRet = emc_trans_YYMMDDhhmm(eTrans, &(pu->sTimeStart), &sYMDhm_f);
        if ( MC_OK != eRet )
        {
            #ifdef MC_DBG
            MCDBG("emc_trans_afn05f9() emc_trans_YYMMDDhhmm() error %d!", eRet);
            #endif
            return eRet;
        }
        
        pf->sTimeStart = sYMDhm_f;
            
        // sTimeEnd
        eRet = emc_trans_YYMMDDhhmm(eTrans, &(pu->sTimeEnd), &sYMDhm_f);
        if ( MC_OK != eRet )
        {
            #ifdef MC_DBG
            MCDBG("emc_trans_afn05f9() emc_trans_YYMMDDhhmm() error %d!", eRet);
            #endif
            return eRet;
        } 
        
        pf->sTimeEnd = sYMDhm_f;
    }
    // ��֡�ൽ�û���
    else if(MC_TRANS_F2U == eTrans)
    {
        for (i = 0; i < 8; i++)
        {
            if (pf->bOff & (0x01 << i))
            {
                pu->bOff[i] = TRUE;
            }
            else
            {
                pu->bOff[i] = FALSE;
            }
        }

        // sTimeStart
        sYMDhm_f = pf->sTimeStart;
        eRet = emc_trans_YYMMDDhhmm(eTrans, &(pu->sTimeStart), &sYMDhm_f);
        if ( MC_OK != eRet )
        {
            #ifdef MC_DBG
            MCDBG("emc_trans_afn05f9() emc_trans_YYMMDDhhmm() error %d!", eRet);
            #endif
            return eRet;
        }

        // sTimeEnd
        sYMDhm_f = pf->sTimeEnd;
        eRet = emc_trans_YYMMDDhhmm(eTrans, &(pu->sTimeEnd), &sYMDhm_f);
        if ( MC_OK != eRet )
        {
            #ifdef MC_DBG
            MCDBG("emc_trans_afn05f9() emc_trans_YYMMDDhhmm() error %d!", eRet);
            #endif
            return eRet;
        } 
    }
    else
    {
         #ifdef MC_DBG
         MCDBG("emc_trans_afn05f9() eTrans is out of range!");
         #endif
         return MC_ERR_OUTRNG;    
    }

    // �������
    *pusLen = sizeof(sMcRemoteOn_f);
    return MC_OK;
}

/*****************************************************************************
 �� �� ��  : emc_trans_afn05f10
 ��������  : ���ݽṹת������
 ��Ӧ����  : MCMD_AFN_5_F10_REMOTE_ON
 �������  : eMcTrans eTrans  
             void* pUser      
             void* pFrame     
 �������  : UINT16* pusLen  ���֡����ֽ���
 �� �� ֵ  : 
 ���ú���  : 
 ��������  : 
 
 �޸���ʷ      :
  1.��    ��   : 2013��11��12��
    ��    ��   : liming
    �޸�����   : �����ɺ���

*****************************************************************************/
eMcErr emc_trans_afn05f10(eMcTrans eTrans, void* pUser, void* pFrame, UINT16* pusLen)
{  
    sMcAfn05f10    *pu = NULL;
    sMcAfn05f10_f  *pf = NULL;
    INT32           i = 0;
    
    if(!pUser || !pFrame || !pusLen)
    {
        #ifdef MC_DBG
        MCDBG("emc_trans_afn05f10() para pointer is null!");
        #endif
        return MC_ERR_NULL;
    }
   
    pu = (sMcAfn05f10*)pUser;
    pf = (sMcAfn05f10_f *)pFrame;

    // �û��ൽ��֡��
    if(MC_TRANS_U2F == eTrans)
    {
        // bOff
        pf->bOn = 0;
        for(i = 0; i < 8; i++)
        {
            if(TRUE == pu->bOn[i])
            {
                pf->bOn |= (0x01 << i);
            }
        }
    }
    // ��֡�ൽ�û���
    else if(MC_TRANS_F2U == eTrans)
    {
        for (i = 0; i < 8; i++)
        {
            if (pf->bOn & (0x01 << i))
            {
                pu->bOn[i] = TRUE;
            }
            else
            {
                pu->bOn[i] = FALSE;
            }
        }
    }
    else
    {
         #ifdef MC_DBG
         MCDBG("emc_trans_afn05f10() eTrans is out of range!");
         #endif
         return MC_ERR_OUTRNG;    
    }

    // �������
    *pusLen = sizeof(UINT8);
    return MC_OK;
}

/*****************************************************************************
 �� �� ��  : emc_trans_afn05f17
 ��������  : ���ݽṹת������
 ��Ӧ����  : MCMD_AFN_5_F17_NX_MODEL_ACT
 �������  : eMcTrans eTrans  
             void* pUser      
             void* pFrame     
 �������  : UINT16* pusLen  ���֡����ֽ���
 �� �� ֵ  : 
 ���ú���  : 
 ��������  : 
 
 �޸���ʷ      :
  1.��    ��   : 2013��11��13��
    ��    ��   : liming
    �޸�����   : �����ɺ���

*****************************************************************************/
eMcErr emc_trans_afn05f17(eMcTrans eTrans, void* pUser, void* pFrame, UINT16* pusLen)
{  
    sMcAfn05f17   *pu = NULL;
    sMcAfn05f17_f *pf = NULL;
    INT32           i = 0;
    UINT8         ucN = 0;
    eMcErr       eRet = MC_OK;
    sMcYWMDhms_f sYWMDhms_f;
    
    if(!pUser || !pFrame || !pusLen)
    {
        #ifdef MC_DBG
        MCDBG("emc_trans_afn05f17() para pointer is null!");
        #endif
        return MC_ERR_NULL;
    }
   
    pu = (sMcAfn05f17*)pUser;
    pf = (sMcAfn05f17_f *)pFrame;
    memset(&sYWMDhms_f, 0, sizeof(sMcYWMDhms_f));

    // �û��ൽ��֡��
    if(MC_TRANS_U2F == eTrans)
    {
        // ucN
        pf->ucN = pu->ucN;
        ucN = pf->ucN;

        // sOne
        for(i = 0; i < ucN; i++)
        {
            // id
            pf->sOne[i].ucID = pu->sOne[i].ucID;
            
            // sTime
            eRet = emc_trans_YWMDhms(eTrans, &(pu->sOne[i].sTime), &sYWMDhms_f);
            if (MC_OK != eRet)
            {
                #ifdef MC_DBG
                MCDBG("emc_trans_afn05f17() emc_trans_YWMDhms() error %d!", eRet);
                #endif
                return eRet;
            }

            pf->sOne[i].sTime = sYWMDhms_f;
        }
    }
    // ��֡�ൽ�û���
    else if(MC_TRANS_F2U == eTrans)
    {
        // ucN
        pu->ucN = pf->ucN;
        ucN = pf->ucN;

        // sOne
        for(i = 0; i < ucN; i++)
        {
            // id
            pu->sOne[i].ucID = pf->sOne[i].ucID;

            // sTime
            sYWMDhms_f = pf->sOne[i].sTime;
            eRet = emc_trans_YWMDhms(eTrans, &(pu->sOne[i].sTime), &sYWMDhms_f);
            if (MC_OK != eRet)
            {
                #ifdef MC_DBG
                MCDBG("emc_trans_afn05f17() emc_trans_YWMDhms() error %d!", eRet);
                #endif
                return eRet;
            }
        }
    }
    else
    {
         #ifdef MC_DBG
         MCDBG("emc_trans_afn05f17() eTrans is out of range!");
         #endif
         return MC_ERR_OUTRNG;    
    }
   
    // �������
    *pusLen = sizeof(sMcYWMDhms_f) * ucN + sizeof(UINT8);
    return MC_OK;
}

/*****************************************************************************
 �� �� ��  : emc_trans_afn05f18
 ��������  : ���ݽṹת������
 ��Ӧ����  : MCMD_AFN_5_F18_NX_MODEL_CLR
 �������  : eMcTrans eTrans  
             void* pUser      
             void* pFrame     
 �������  : UINT16* pusLen  ���֡����ֽ���
 �� �� ֵ  : 
 ���ú���  : 
 ��������  : 
 
 �޸���ʷ      :
  1.��    ��   : 2013��11��13��
    ��    ��   : liming
    �޸�����   : �����ɺ���

*****************************************************************************/
eMcErr emc_trans_afn05f18(eMcTrans eTrans, void* pUser, void* pFrame, UINT16* pusLen)
{  
    sMcAfn05f18   *pu = NULL;
    sMcAfn05f18_f *pf = NULL;
    INT32           i = 0;
    UINT8         ucN = 0;
    
    if(!pUser || !pFrame || !pusLen)
    {
        #ifdef MC_DBG
        MCDBG("emc_trans_afn05f18() para pointer is null!");
        #endif
        return MC_ERR_NULL;
    }
   
    pu = (sMcAfn05f18*)pUser;
    pf = (sMcAfn05f18_f *)pFrame;

    // �û��ൽ��֡��
    if(MC_TRANS_U2F == eTrans)
    {
        // ucN
        pf->ucN = pu->ucN;

        // sOne
        for(i = 0; i < ucN; i++)
        {
           pf->ucID[i] = pu->ucID[i];
        }
    }
    // ��֡�ൽ�û���
    else if(MC_TRANS_F2U == eTrans)
    {
        // ucN
        pu->ucN = pf->ucN;

        // sOne
        for(i = 0; i < ucN; i++)
        {
           pu->ucID[i] = pf->ucID[i];
        }
    }
    else
    {
         #ifdef MC_DBG
         MCDBG("emc_trans_afn05f18() eTrans is out of range!");
         #endif
         return MC_ERR_OUTRNG;    
    }
   
    // �������
    *pusLen = sizeof(UINT8) * (pf->ucN) + sizeof(UINT8);
    return MC_OK;
}

/*****************************************************************************
 �� �� ��  : emc_trans_afn05f19
 ��������  : ���ݽṹת������
 ��Ӧ����  : MCMD_AFN_5_F19_RQ_RESPN_ACT
 �������  : eMcTrans eTrans  
             void* pUser      
             void* pFrame     
 �������  : UINT16* pusLen  ���֡����ֽ���
 �� �� ֵ  : 
 ���ú���  : 
 ��������  : 
 
 �޸���ʷ      :
  1.��    ��   : 2013��11��13��
    ��    ��   : liming
    �޸�����   : �����ɺ���

*****************************************************************************/
eMcErr emc_trans_afn05f19(eMcTrans eTrans, void* pUser, void* pFrame, UINT16* pusLen)
{
    return emc_trans_afn05f18(eTrans, pUser, pFrame, pusLen);
}

/*****************************************************************************
 �� �� ��  : emc_trans_afn05f20
 ��������  : ���ݽṹת������
 ��Ӧ����  : MCMD_AFN_5_F20_RQ_RESPN_CLT
 �������  : eMcTrans eTrans  
             void* pUser      
             void* pFrame     
 �������  : UINT16* pusLen  ���֡����ֽ���
 �� �� ֵ  : 
 ���ú���  : 
 ��������  : 
 
 �޸���ʷ      :
  1.��    ��   : 2013��11��13��
    ��    ��   : liming
    �޸�����   : �����ɺ���

*****************************************************************************/
eMcErr emc_trans_afn05f20(eMcTrans eTrans, void* pUser, void* pFrame, UINT16* pusLen)
{
    return emc_trans_afn05f18(eTrans, pUser, pFrame, pusLen);
}

/*****************************************************************************
 �� �� ��  : emc_trans_afn10f2_m2s (ѯ��)
 ��������  : ���ݽṹת������
 ��Ӧ����  : MCMD_AFN_A_F2_MST_PARA
 �������  : eMcTrans eTrans  
             void* pUser      
             void* pFrame     
 �������  : UINT16* pusLen  ���֡����ֽ���
 �� �� ֵ  : 
 ���ú���  : 
 ��������  : 
 
 �޸���ʷ      :
  1.��    ��   : 2013��11��13��
    ��    ��   : liming
    �޸�����   : �����ɺ���

*****************************************************************************/
eMcErr emc_trans_afn10f2_m2s(eMcTrans eTrans, void* pUser, void* pFrame, UINT16* pusLen)
{
    return emc_trans_afn05f18(eTrans, pUser, pFrame, pusLen);
}

/*****************************************************************************
 �� �� ��  : emc_trans_afn10f2_s2m  (Ӧ��)
 ��������  : ���ݽṹת������
 ��Ӧ����  : MCMD_AFN_A_F2_MST_PARA
 �������  : eMcTrans eTrans  
             void* pUser      
             void* pFrame     
 �������  : UINT16* pusLen  ���֡����ֽ���
 �� �� ֵ  : 
 ���ú���  : 
 ��������  : 
 
 �޸���ʷ      :
  1.��    ��   : 2013��11��13��
    ��    ��   : liming
    �޸�����   : �����ɺ���

*****************************************************************************/
eMcErr emc_trans_afn10f2_s2m(eMcTrans eTrans, void* pUser, void* pFrame, UINT16* pusLen)
{
    return emc_trans_afn05f18(eTrans, pUser, pFrame, pusLen);
}

/*****************************************************************************
 �� �� ��  : emc_trans_afn10f7_m2s (��ѯ)
 ��������  : ���ݽṹת������
 ��Ӧ����  : MCMD_AFN_A_F7_CON_DOWN_CFG
 �������  : eMcTrans eTrans  
             void* pUser      
             void* pFrame     
 �������  : UINT16* pusLen  ���֡����ֽ���
 �� �� ֵ  : 
 ���ú���  : 
 ��������  : 
 
 �޸���ʷ      :
  1.��    ��   : 2013��11��13��
    ��    ��   : liming
    �޸�����   : �����ɺ���

*****************************************************************************/
eMcErr emc_trans_afn10f7_m2s(eMcTrans eTrans, void* pUser, void* pFrame, UINT16* pusLen)
{  
    sMcAfn10f7q   *pu = NULL;
    sMcAfn10f7q_f *pf = NULL;
    INT32           i = 0;
    UINT8         ucN = 0;
    
    if(!pUser || !pFrame || !pusLen)
    {
        #ifdef MC_DBG
        MCDBG("emc_trans_afn10f7_m2s() para pointer is null!");
        #endif
        return MC_ERR_NULL;
    }
   
    pu = (sMcAfn10f7q*)pUser;
    pf = (sMcAfn10f7q_f *)pFrame;

    // �û��ൽ��֡��
    if(MC_TRANS_U2F == eTrans)
    {
        // ucN
        pf->usN = pu->usN;

        // usPort
        for(i = 0; i < ucN; i++)
        {
           pf->usPort[i] = pu->usPort[i];
        }
    }
    // ��֡�ൽ�û���
    else if(MC_TRANS_F2U == eTrans)
    {
        // ucN
        pu->usN = pf->usN;

        // usPort
        for(i = 0; i < ucN; i++)
        {
           pu->usPort[i] = pf->usPort[i];
        }
    }
    else
    {
         #ifdef MC_DBG
         MCDBG("emc_trans_afn10f7_m2s() eTrans is out of range!");
         #endif
         return MC_ERR_OUTRNG;    
    }
   
    // �������
    *pusLen = sizeof(UINT16) * (pf->usN) + sizeof(UINT16);
    return MC_OK;
}

/*****************************************************************************
 �� �� ��  : emc_trans_afn10f7_s2m  (Ӧ��)
 ��������  : ���ݽṹת������
 ��Ӧ����  : MCMD_AFN_A_F7_CON_DOWN_CFG
 �������  : eMcTrans eTrans  
             void* pUser      
             void* pFrame     
 �������  : UINT16* pusLen  ���֡����ֽ���
 �� �� ֵ  : 
 ���ú���  : 
 ��������  : 
 
 �޸���ʷ      :
  1.��    ��   : 2013��11��13��
    ��    ��   : liming
    �޸�����   : �����ɺ���

*****************************************************************************/
eMcErr emc_trans_afn10f7_s2m(eMcTrans eTrans, void* pUser, void* pFrame, UINT16* pusLen)
{  
    sMcAfn10f7a   *pu = NULL;
    sMcAfn10f7a_f *pf = NULL;
    INT32           i = 0;
    UINT8         ucN = 0;
    eMcErr       eRet = MC_OK;
    UINT16   usLenTmp = 0;
    sMcDownCfg_f sDownCfg_f;
    
    if(!pUser || !pFrame || !pusLen)
    {
        #ifdef MC_DBG
        MCDBG("emc_trans_afn10f7_s2m() para pointer is null!");
        #endif
        return MC_ERR_NULL;
    }
   
    pu = (sMcAfn10f7a*)pUser;
    pf = (sMcAfn10f7a_f *)pFrame;
    memset(&sDownCfg_f, 0, sizeof(sMcDownCfg_f));

    // �û��ൽ��֡��
    if(MC_TRANS_U2F == eTrans)
    {
        pf->ucN = pu->ucN;
        for(i = 0; i < ucN; i++)
        {
            eRet = emc_trans_afn04f7(eTrans, &(pu->sOne[i]), &sDownCfg_f, &usLenTmp);
            if(MC_OK != eRet)
            {
                #ifdef MC_DBG
                MCDBG("emc_trans_afn10f7_s2m() emc_trans_afn04f7() error %d!", eRet);
                #endif
                return eRet;
            }

            pf->sOne[i] = sDownCfg_f;
        }
    }
    // ��֡�ൽ�û���
    else if(MC_TRANS_F2U == eTrans)
    {
        pu->ucN = pf->ucN;
        for(i = 0; i < ucN; i++)
        {
            sDownCfg_f = pf->sOne[i];
            eRet = emc_trans_afn04f7(eTrans, &(pu->sOne[i]), &sDownCfg_f, &usLenTmp);
            if(MC_OK != eRet)
            {
                #ifdef MC_DBG
                MCDBG("emc_trans_afn10f7_s2m() emc_trans_afn04f7() error %d!", eRet);
                #endif
                return eRet;
            }
        }
    }
    else
    {
         #ifdef MC_DBG
         MCDBG("emc_trans_afn10f7_s2m() eTrans is out of range!");
         #endif
         return MC_ERR_OUTRNG;    
    }

    // ȥ����
    usLenTmp = usLenTmp;
    
    // �������
    *pusLen = sizeof(sMcAfn04f7_f) * (pf->ucN) + sizeof(UINT8);
    return MC_OK;
}

/*****************************************************************************
 �� �� ��  : emc_trans_afn10f11  (Ӧ��)
 ��������  : ���ݽṹת������
 ��Ӧ����  : MCMD_AFN_A_F11_CON_LOGIC_ADDR
 �������  : eMcTrans eTrans  
             void* pUser      
             void* pFrame     
 �������  : UINT16* pusLen  ���֡����ֽ���
 �� �� ֵ  : 
 ���ú���  : 
 ��������  : 
 
 �޸���ʷ      :
  1.��    ��   : 2013��11��13��
    ��    ��   : liming
    �޸�����   : �����ɺ���

*****************************************************************************/
eMcErr emc_trans_afn10f11(eMcTrans eTrans, void* pUser, void* pFrame, UINT16* pusLen)
{  
    sMcA      *pu = NULL;
    sMcA_f    *pf = NULL;
    eMcErr   eRet = MC_OK;
    
    if(!pUser || !pFrame || !pusLen)
    {
        #ifdef MC_DBG
        MCDBG("emc_trans_afn10f11() para pointer is null!");
        #endif
        return MC_ERR_NULL;
    }
   
    pu = (sMcA*)pUser;
    pf = (sMcA_f *)pFrame;

    if(MC_TRANS_U2F != eTrans && MC_TRANS_F2U == eTrans)
    {
         #ifdef MC_DBG
         MCDBG("emc_trans_afn10f7_s2m() eTrans is out of range!");
         #endif
         return MC_ERR_OUTRNG;    
    }

    eRet = emc_trans_address(eTrans, pu, pf);
    if(MC_OK != eRet)
    {
        #ifdef MC_DBG
        MCDBG("emc_trans_afn10f11() emc_trans_address() error %d!", eRet);
        #endif
        return eRet;
    }
    
    // �������
    *pusLen = sizeof(sMcA_f);
    return MC_OK;
}

/*****************************************************************************
 �� �� ��  : emc_trans_afn10f12  (Ӧ��)
 ��������  : ���ݽṹת������
 ��Ӧ����  : MCMD_AFN_A_F12_CON_VERSION
 �������  : eMcTrans eTrans  
             void* pUser      
             void* pFrame     
 �������  : UINT16* pusLen  ���֡����ֽ���
 �� �� ֵ  : 
 ���ú���  : 
 ��������  : 
 
 �޸���ʷ      :
  1.��    ��   : 2013��11��13��
    ��    ��   : liming
    �޸�����   : �����ɺ���

*****************************************************************************/
eMcErr emc_trans_afn10f12(eMcTrans eTrans, void* pUser, void* pFrame, UINT16* pusLen)
{  
    sMcAfn10f12   *pu = NULL;
    sMcAfn10f12_f *pf = NULL;
    INT32           i = 0;
    eMcErr       eRet = MC_OK;
    UINT16   usLenTmp = 0;
    sMcYMDhm_f  sYMDhm_f;
    
    if(!pUser || !pFrame || !pusLen)
    {
        #ifdef MC_DBG
        MCDBG("emc_trans_afn10f12() para pointer is null!");
        #endif
        return MC_ERR_NULL;
    }
   
    pu = (sMcAfn10f12*)pUser;
    pf = (sMcAfn10f12_f *)pFrame;
    memset(&sYMDhm_f, 0, sizeof(sMcYMDhm_f));

    // �û��ൽ��֡��
    if(MC_TRANS_U2F == eTrans)
    {
        // strFactory
        memcpy(pf->strFactory, pu->strFactory, 4);
        usLenTmp += 4;
        
        // ucDevId
        eRet = emc_str_to_bcd(pu->ucDevId, pf->ucDevId, 12);
        if(MC_OK != eRet)
        {
            #ifdef MC_DBG
            MCDBG("emc_trans_afn10f12() emc_str_to_bcd() error %d!", eRet);
            #endif
            return eRet;
        }

        usLenTmp += 6;

        // strCap
        memcpy(pf->strCap, pu->strCap, 11);
        usLenTmp += 11;
 
        // strSoft
        memcpy(pf->strSoft, pu->strSoft, 4);  
        usLenTmp += 4;

        // strHard
        memcpy(pf->strHard, pu->strHard, 4);
        usLenTmp += 4;

        // sTime
        eRet = emc_trans_YYMMDDhhmm(eTrans, &(pu->sTime), &sYMDhm_f);
        if(MC_OK != eRet)
        {
            #ifdef MC_DBG
            MCDBG("emc_trans_afn10f12() emc_trans_YYMMDDhhmm() error %d!", eRet);
            #endif
            return eRet;
        }
        
        pf->sTime = sYMDhm_f;

        usLenTmp += sizeof(sMcYMDhm_f);

        // ucN
        pf->ucN = pu->ucN;
        usLenTmp += sizeof(UINT8);
 
        // sOne
        for(i = 0; i < pf->ucN; i++)
        {
            // ucID
            pf->sOne[i].ucID = pu->sOne[i].ucID;
 
            // strVersion
            memcpy(pf->sOne[i].strVersion, pu->sOne[i].strVersion, 4);
 
            // stime
            eRet = emc_trans_YYMMDDhhmm(eTrans, &(pu->sOne[i].sTime), &sYMDhm_f);
            if(MC_OK != eRet)
            {
                #ifdef MC_DBG
                MCDBG("emc_trans_afn10f12() emc_trans_YYMMDDhhmm() error %d!", eRet);
                #endif
                return eRet;
            }
            
            pf->sOne[i].sTime = sYMDhm_f;
        } 

        usLenTmp += (sizeof(sMcVerModel_f) * pf->ucN);

    }
    // ��֡�ൽ�û���
    else if(MC_TRANS_F2U == eTrans)
    {
        // strFactory
        memcpy(pu->strFactory, pf->strFactory, 4);
        usLenTmp += 4;
        
        // ucDevId
        eRet = emc_bcd_to_str(pf->ucDevId, pu->ucDevId,  6);
        if(MC_OK != eRet)
        {
            #ifdef MC_DBG
            MCDBG("emc_trans_afn10f12() emc_bcd_to_str() error %d!", eRet);
            #endif
            return eRet;
        }

        usLenTmp += 6;

        // strCap
        memcpy(pu->strCap, pf->strCap, 11);
        usLenTmp += 11;
 
        // strSoft
        memcpy(pu->strSoft, pf->strSoft, 4);  
        usLenTmp += 4;

        // strHard
        memcpy(pu->strHard, pf->strHard, 4);
        usLenTmp += 4;

        // sTime
        sYMDhm_f = pf->sTime;
        eRet = emc_trans_YYMMDDhhmm(eTrans, &(pu->sTime), &sYMDhm_f);
        if(MC_OK != eRet)
        {
            #ifdef MC_DBG
            MCDBG("emc_trans_afn10f12() emc_trans_YYMMDDhhmm() error %d!", eRet);
            #endif
            return eRet;
        }

        usLenTmp += sizeof(sMcYMDhm_f);

        // ucN
        pf->ucN = pu->ucN;
        usLenTmp += sizeof(UINT8);
 
        // sOne
        for(i = 0; i < pf->ucN; i++)
        {
            // ucID
            pu->sOne[i].ucID = pf->sOne[i].ucID;
 
            // strVersion
            memcpy(pu->sOne[i].strVersion, pf->sOne[i].strVersion, 4);
 
            // stime
            sYMDhm_f = pf->sOne[i].sTime;
            eRet = emc_trans_YYMMDDhhmm(eTrans, &(pu->sOne[i].sTime), &sYMDhm_f);
            if(MC_OK != eRet)
            {
                #ifdef MC_DBG
                MCDBG("emc_trans_afn10f12() emc_trans_YYMMDDhhmm() error %d!", eRet);
                #endif
                return eRet;
            }
        } 

        usLenTmp += (sizeof(sMcVerModel_f) * pf->ucN);
    }
    else
    {
         #ifdef MC_DBG
         MCDBG("emc_trans_afn10f12() eTrans is out of range!");
         #endif
         return MC_ERR_OUTRNG;    
    }

    // �������
    *pusLen = usLenTmp;
    return MC_OK;
}

/*****************************************************************************
 �� �� ��  : emc_trans_afn10f13
 ��������  : ���ݽṹת������
 ��Ӧ����  : MCMD_AFN_A_F13_ELEC_MP_INFO
 �������  : eMcTrans eTrans  
             void* pUser      
             void* pFrame     
 �������  : UINT16* pusLen  ���֡����ֽ���
 �� �� ֵ  : 
 ���ú���  : 
 ��������  : 
 
 �޸���ʷ      :
  1.��    ��   : 2013��11��13��
    ��    ��   : liming
    �޸�����   : �����ɺ���

*****************************************************************************/
eMcErr emc_trans_afn10f13(eMcTrans eTrans, void* pUser, void* pFrame, UINT16* pusLen)
{  
    sMcAfn10f13   *pu = NULL;
    sMcAfn10f13_f *pf = NULL;
    INT32           i = 0;
    INT32           k = 0;
    INT32           j = 0;
    INT32        kMax = 0;
    UINT8       ucDa1 = 0;
    UINT16    usPn    = 0;
    UINT16    usPnMin = 0;
    
    if(!pUser || !pFrame || !pusLen)
    {
        #ifdef MC_DBG
        MCDBG("emc_trans_afn10f13() para pointer is null!");
        #endif
        return MC_ERR_NULL;
    }
   
    pu = (sMcAfn10f13*)pUser;
    pf = (sMcAfn10f13_f *)pFrame;

    // �û��ൽ��֡��
    if(MC_TRANS_U2F == eTrans)
    {
        // ucSprt
        pf->ucSprt = pu->ucSprt;

        // �ҵ�pn��Сֵȷ����ʼDa2
        usPnMin = pu->usPn[0];
        for(i = 0; i < pu->usNum; i++)
        {
            usPn = pu->usPn[i];
            if(usPn < MC_PN_MIN || usPn > MC_PN_MAX)
            {
                #ifdef MC_DBG
                MCDBG("emc_trans_afn10f13() para usPn is out of range!");
                #endif
                return MC_ERR_OUTRNG;
            }

            // ȡ��pn��Сֵ
            usPnMin = (usPnMin < usPn) ? usPnMin : usPn;
        }

        // ����С��Da2
        pf->ucSDa2 = ((usPnMin - 1) / 8 + 1);

        // Da1
        for(i = 0; i < pu->usNum; i++)
        {
            usPn = pu->usPn[i];

            // ����ڱ����е�Da2������
            k = ((usPn - 1) / 8 + 1) - pf->ucSDa2;
            pf->ucDa1[k] |= 0x01 << ((usPn - 1) % 8);

            // ȡ��KMax
            kMax = kMax > k ? kMax : k;
        }

        pf->ucK = kMax + 1;
    }
    // ��֡�ൽ�û���
    else if(MC_TRANS_F2U == eTrans)
    {
        // ucSprt
        pu->ucSprt = pf->ucSprt;

        // usPn
        for(i = 0; i < pf->ucK; i++)
        {
            ucDa1 = pf->ucDa1[i];
            for(k = 0; k < 8; k++)
            {
                if(ucDa1 & (0x01 << k))
                {
                    pu->usPn[j++] = (i + pf->ucSDa2 - 1) * 8 + k + 1;
                }
            }
        }

        pu->usNum = j;
    }
    else
    {
         #ifdef MC_DBG
         MCDBG("emc_trans_afn10f13() eTrans is out of range!");
         #endif
         return MC_ERR_OUTRNG;    
    }
   
    // �������
   *pusLen = sizeof(UINT8) * (pf->ucK) + sizeof(UINT8)* 3;
    return MC_OK;
}

/*****************************************************************************
 �� �� ��  : emc_trans_afn10f14
 ��������  : ���ݽṹת������
 ��Ӧ����  : MCMD_AFN_A_F14_NELC_MP_INFO
 �������  : eMcTrans eTrans  
             void* pUser      
             void* pFrame     
             UINT16* pusLen   
 �������  : ��
 �� �� ֵ  : 
 ���ú���  : 
 ��������  : 
 
 �޸���ʷ      :
  1.��    ��   : 2013��11��14��
    ��    ��   : liming
    �޸�����   : �����ɺ���

*****************************************************************************/
eMcErr emc_trans_afn10f14(eMcTrans eTrans, void* pUser, void* pFrame, UINT16* pusLen)
{
    return emc_trans_afn10f13(eTrans, pUser, pFrame, pusLen);
}

/*****************************************************************************
 �� �� ��  : emc_trans_afn10f15
 ��������  : ���ݽṹת������
 ��Ӧ����  : MCMD_AFN_A_F15_SUPT_EVENT
 �������  : eMcTrans eTrans  
             void* pUser      
             void* pFrame     
             UINT16* pusLen   
 �������  : ��
 �� �� ֵ  : 
 ���ú���  : 
 ��������  : 
 
 �޸���ʷ      :
  1.��    ��   : 2013��11��14��
    ��    ��   : liming
    �޸�����   : �����ɺ���

*****************************************************************************/
eMcErr emc_trans_afn10f15(eMcTrans eTrans, void* pUser, void* pFrame, UINT16* pusLen)
{  
    sMcAfn10f15   *pu = NULL;
    sMcAfn10f15_f *pf = NULL;
    INT32           i = 0;

    if(!pUser || !pFrame || !pusLen)
    {
        #ifdef MC_DBG
        MCDBG("emc_trans_afn10f15() para pointer is null!");
        #endif
        return MC_ERR_NULL;
    }
   
    pu = (sMcAfn10f15*)pUser;
    pf = (sMcAfn10f15_f *)pFrame;

    // �û��ൽ��֡��
    if(MC_TRANS_U2F == eTrans)
    {
        // ֡��������0
        memset(pf, 0x0, sizeof(sMcAfn10f15_f));
        
        for(i = 0; i < MC_ERC_NUM_MAX; i++)
        {
            if(TRUE == pu->bSuprt[i])
            {
                pf->ucEvent[i/8] |= (0x01 << (i%8));
            }
        }
    }
    // ��֡�ൽ�û���
    else if(MC_TRANS_F2U == eTrans)
    {
        for(i = 0; i < MC_ERC_NUM_MAX; i++)
        {
            if((UINT8)(pf->ucEvent[i/8]) & (0x01 << (i%8)))
            {
                pu->bSuprt[i] = TRUE;
            }
            else
            {
                pu->bSuprt[i] = FALSE;
            }
        }
    }
    else
    {
         #ifdef MC_DBG
         MCDBG("emc_trans_afn10f15() eTrans is out of range!");
         #endif
         return MC_ERR_OUTRNG;    
    }
   
    // �������
   *pusLen = sizeof(sMcAfn10f15_f);
    return MC_OK;
}

/*****************************************************************************
 �� �� ��  : emc_trans_afn10f57
 ��������  : ���ݽṹת������
 ��Ӧ����  : MCMD_AFN_A_F57_TML_CFG_INFO
 �������  : eMcTrans eTrans  
             void* pUser      
             void* pFrame     
             UINT16* pusLen   
 �������  : ��
 �� �� ֵ  : 
 ���ú���  : 
 ��������  : 
 
 �޸���ʷ      :
  1.��    ��   : 2013��11��14��
    ��    ��   : liming
    �޸�����   : �����ɺ���

*****************************************************************************/
eMcErr emc_trans_afn10f57(eMcTrans eTrans, void* pUser, void* pFrame, UINT16* pusLen)
{
    return emc_trans_afn10f13(eTrans, pUser, pFrame, pusLen);
}

/*****************************************************************************
 �� �� ��  : emc_trans_afn12f9_m2s  (�������)
 ��������  : ���ݽṹת������
 ��Ӧ����  : MCMD_AFN_C_F9_FREZ_AUTO
 �������  : eMcTrans eTrans  
             void* pUser      
             void* pFrame     
             UINT16* pusLen   
 �������  : ��
 �� �� ֵ  : 
 ���ú���  : 
 ��������  : 
 
 �޸���ʷ      :
  1.��    ��   : 2013��11��14��
    ��    ��   : liming
    �޸�����   : �����ɺ���

*****************************************************************************/
eMcErr emc_trans_afn12f9_m2s(eMcTrans eTrans, void* pUser, void* pFrame, UINT16* pusLen)
{  
    sMcAfn12f9    *pu = NULL;
    sMcAfn12f9_f  *pf = NULL;
    eMcErr       eRet = MC_OK;
    sMcFmt02_f sFmt02_f;

    if(!pUser || !pFrame || !pusLen)
    {
        #ifdef MC_DBG
        MCDBG("emc_trans_afn12f9_m2s() para pointer is null!");
        #endif
        return MC_ERR_NULL;
    }
    
    pu = (sMcAfn12f9*)pUser;
    pf = (sMcAfn12f9_f *)pFrame;
    memset(&sFmt02_f, 0, sizeof(sFmt02_f));

    if(MC_TRANS_U2F == eTrans)
    {
        // sTs
        eRet = emc_trans_YYMMDDhhmm(eTrans, &(pu->sTs), &sFmt02_f);
        if(MC_OK != eRet)
        {
            #ifdef MC_DBG
            MCDBG("emc_trans_afn12f9_m2s() emc_trans_YYMMDDhhmm() error %d!", eRet);
            #endif
            return eRet;
        }
        
        pf->sTs = sFmt02_f;
        
        // sTe
        eRet = emc_trans_YYMMDDhhmm(eTrans, &(pu->sTe), &sFmt02_f);
        if(MC_OK != eRet)
        {
            #ifdef MC_DBG
            MCDBG("emc_trans_afn12f9_m2s() emc_trans_YYMMDDhhmm() error %d!", eRet);
            #endif
            return eRet;
        }
        
        pf->sTe = sFmt02_f;
    }
    else if(MC_TRANS_F2U == eTrans)
    {
        // sTs
        sFmt02_f = pf->sTs;
        eRet = emc_trans_YYMMDDhhmm(eTrans, &(pu->sTs), &sFmt02_f);
        if(MC_OK != eRet)
        {
            #ifdef MC_DBG
            MCDBG("emc_trans_afn12f9_m2s() emc_trans_YYMMDDhhmm() error %d!", eRet);
            #endif
            return eRet;
        }

        // sTe
        sFmt02_f = pf->sTe;
        eRet = emc_trans_YYMMDDhhmm(eTrans, &(pu->sTe), &sFmt02_f);
        if(MC_OK != eRet)
        {
            #ifdef MC_DBG
            MCDBG("emc_trans_afn12f9_m2s() emc_trans_YYMMDDhhmm() error %d!", eRet);
            #endif
            return eRet;
        }
    }
    else
    {
         #ifdef MC_DBG
         MCDBG("emc_trans_afn12f9_m2s() eTrans is out of range!");
         #endif
         return MC_ERR_OUTRNG;    
    }

    // �������
   *pusLen = sizeof(sMcAfn12f9_f);
    return MC_OK;
}

/*****************************************************************************
 �� �� ��  : emc_trans_afn12f9_s2m
 ��������  : ���ݽṹת������
 ��Ӧ����  : MCMD_AFN_C_F9_FREZ_AUTO
 �������  : eMcTrans eTrans  
             void* pUser      
             void* pFrame     
             UINT16* pusLen   
 �������  : ��
 �� �� ֵ  : 
 ���ú���  : 
 ��������  : 
 
 �޸���ʷ      :
  1.��    ��   : 2013��12��2��
    ��    ��   : liming
    �޸�����   : �����ɺ���

*****************************************************************************/
eMcErr emc_trans_afn12f9_s2m(eMcTrans eTrans, void* pUser, void* pFrame, UINT16* pusLen)
{
    sMcAfn12f9A    *pu = NULL;
    sMcAfn12f9A_f  *pf = NULL;
    sMcDaDt   * psDaDt = NULL;
    pMcFunc      pFunc = NULL;   
    UINT8      *pTmp   = NULL;
    UINT8     ucNumTmp = 0;
    eMcErr        eRet = MC_OK;
    INT32            n = 0;
    INT32            m = 0;
    UINT16    usLenTmp = 0;
    UINT16    usLenOut = 0;
    eMcmd         eCmd = MCMD_AFN_F_UNKOWN;
    sMcmdInfor  sCmdInfor;
    eMcAFN        eAfn = MC_AFN_NULL;
    sMcYMDhm_f sYMDhm_f;
    
    if(!pUser || !pFrame || !pusLen)
    {
        #ifdef MC_DBG
        MCDBG("emc_trans_afn12f9_s2m() para pointer is null!");
        #endif
        return MC_ERR_NULL;
    }

    pu = (sMcAfn12f9A*)pUser;
    pf = (sMcAfn12f9A_f*)pFrame;
    memset(&sYMDhm_f, 0, sizeof(sMcYMDhm_f));

    // �û��ൽ��֡��
    if(MC_TRANS_U2F == eTrans)
    {
        // usPeriod
        pf->usPeriod = pu->usPeriod;
        usLenOut += sizeof(UINT16);
        
        // eUnit
        switch(pu->eUnit)
        {
            case MC_PUNT_MONTH:
                pf->eUnit = 1;
                break;
                
            case MC_PUNT_DAY:
                pf->eUnit = 2;
                break;
                    
            case MC_PUNT_HOUR:
                pf->eUnit = 3;
                break;

            case MC_PUNT_MIN:
                pf->eUnit = 4;
                break;

            case MC_PUNT_SEC:
                pf->eUnit = 5;
                break;
                    
            case MC_PUNT_MS:
                pf->eUnit = 6;
                break;
                
           default:
                #ifdef MC_DBG
                MCDBG("emc_trans_afn12f9_s2m() para pointer is error!");
                #endif
                return MC_ERR_PARA;
                //break;
        }

        usLenOut += 1;
         
        // ucN
        pf->ucN = pu->ucN;
        usLenOut += 1;
        
        // ucM
        pf->ucM = pu->ucM;
        usLenOut += 1;
            
        // sOne
        pTmp = &(pf->ucDaDt[0]);
        for(m = 0; m < pf->ucM; m++)
        {
            ucNumTmp = 0;
            // ��Ԫ��ʶ
            psDaDt = (sMcDaDt*)pTmp;
            eRet = emc_cmdpn_to_dadt(MC_AFN_13_ASKR, psDaDt, &ucNumTmp, &(pu->sOne[m].sCmdPn), 1);

            #if 0
            #ifdef MC_DBG
            MCDBG("emc_trans_afn12f9_s2m() eCmd = %04X!", pu->sOne[m].sCmdPn.eCmd);
            MCDBG("emc_trans_afn12f9_s2m() sMcDaDt ucDA1= %d!", psDaDt->ucDA1);
            MCDBG("emc_trans_afn12f9_s2m() sMcDaDt ucDA2= %d!", psDaDt->ucDA2);
            MCDBG("emc_trans_afn12f9_s2m() sMcDaDt ucDT1= %d!", psDaDt->ucDT1);
            MCDBG("emc_trans_afn12f9_s2m() sMcDaDt ucDT2= %d!", psDaDt->ucDT2);
            #endif    
            #endif    
            
            if(MC_OK != eRet)
            {
                #ifdef MC_DBG
                MCDBG("emc_trans_afn12f9_s2m() emc_pnfn_to_dadt() error %d!", eRet);
                #endif
                return eRet;
            }

            eCmd = pu->sOne[m].sCmdPn.eCmd;
            eAfn = eMcGetCmdAfn(eCmd);
            if(MC_AFN_13_ASKR != eAfn)
            {
               #ifdef MC_DBG
               MCDBG("emc_trans_afn12f9_s2m() eCmd is out of range!");
               #endif
               return MC_ERR_OUTRNG;    
            }
            
            eRet = eMcGetCmdInfor(eCmd, MC_DIR_S2M, &sCmdInfor);
            if(MC_OK != eRet)
            {
                #ifdef MC_DBG
                MCDBG("emc_trans_afn12f9_s2m() eMcGetCmdInfor() error %d!", eRet);
                #endif
                return eRet;
            }
            
            pFunc = sCmdInfor.pFunc;
            if(NULL == pFunc)
            {
               #ifdef MC_DBG
               MCDBG("emc_trans_afn12f9_s2m() eCmd is out of range!");
               #endif
               return MC_ERR_OUTRNG;  
            }
            
            // ���ݵ�Ԫ
            pTmp += sizeof(sMcDaDt);
            usLenOut += sizeof(sMcDaDt);
            for(n = 0; n < pu->ucN; n++)
            {
               eRet = pFunc(eTrans, &(pu->sOne[m].uApp[n]), pTmp, &usLenTmp);
               if(MC_OK != eRet)
               {
                   #ifdef MC_DBG
                   MCDBG("emc_trans_afn12f9_s2m() pFunc() error %d!", eRet);
                   #endif
                   return eRet;
               }

               pTmp += usLenTmp;
               usLenOut += usLenTmp;
            }     
        }

        // sTs
        eRet = emc_trans_YYMMDDhhmm(eTrans, &(pu->sTs), &sYMDhm_f);
        if(MC_OK != eRet)
        {
            #ifdef MC_DBG
            MCDBG("emc_trans_afn12f9_m2s() emc_trans_YYMMDDhhmm() error %d!", eRet);
            #endif
            return eRet;
        }
        
        pf->sTs = sYMDhm_f;
        usLenOut += sizeof(sMcFmt02_f);
    }
    // ��֡�ൽ�û���
    else if(MC_TRANS_F2U == eTrans)
    {
        // usPeriod
        pu->usPeriod = pf->usPeriod;
        usLenOut += sizeof(UINT16);

         // eUnit
        switch(pf->eUnit)
        {
            case 1:
                pu->eUnit = MC_PUNT_MONTH;
                break;
                
            case 2:
                pu->eUnit = MC_PUNT_DAY;
                break;
                    
            case 3:
                pu->eUnit = MC_PUNT_HOUR;
                break;

            case 4:
                pu->eUnit = MC_PUNT_MIN;
                break;

            case 5:
                pu->eUnit = MC_PUNT_SEC;
                break;
                    
            case 6:
                pu->eUnit = MC_PUNT_MS;
                break;
                
           default:
                #ifdef MC_DBG
                MCDBG("emc_trans_afn12f9_s2m() para pointer is error!");
                #endif
                pu->eUnit = MC_PUNT_UNKOWN;
                break;
        }

        usLenOut += 1;

        // ucN
        pu->ucN = pf->ucN;
        usLenOut += 1;

        // usPeriod
        pu->ucM = pf->ucM;
        usLenOut += 1;
        
        // sOne
        pTmp = &(pf->ucDaDt[0]);
        
        for(m = 0; m < pf->ucM; m++)
        {
            ucNumTmp = 0;
            
            // ��Ԫ��ʶ
            psDaDt = (sMcDaDt*)pTmp;
            eRet = emc_dadt_to_cmdpn(MC_AFN_13_ASKR, psDaDt, 1, &(pu->sOne[m].sCmdPn), &ucNumTmp);
            if(MC_OK != eRet)
            {
                #ifdef MC_DBG
                MCDBG("emc_trans_afn12f9_s2m() emc_dadt_to_cmdpn() error %d!", eRet);
                #endif
                return eRet;
            }

            eCmd = pu->sOne[m].sCmdPn.eCmd;

            #ifdef MC_DBG
            MCDBG("emc_trans_afn12f9_s2m() eCmd = %04X", eCmd);
            #endif
               
            eAfn = eMcGetCmdAfn(eCmd);
            if(MC_AFN_13_ASKR != eAfn)
            {
               #ifdef MC_DBG
               MCDBG("emc_trans_afn12f9_s2m() eCmd is out of range!");
               #endif
               return MC_ERR_OUTRNG;    
            }
            
            eRet = eMcGetCmdInfor(eCmd, MC_DIR_S2M, &sCmdInfor);
            if(MC_OK != eRet)
            {
                #ifdef MC_DBG
                MCDBG("emc_trans_afn12f9_s2m() eMcGetCmdInfor() error %d!", eRet);
                #endif
                return eRet;
            }
            
            pFunc = sCmdInfor.pFunc;
            if(NULL == pFunc)
            {
               #ifdef MC_DBG
               MCDBG("emc_trans_afn12f9_s2m() eCmd is out of range!");
               #endif
               return MC_ERR_OUTRNG;  
            }
            
            // ���ݵ�Ԫ
            pTmp += sizeof(sMcDaDt);
            usLenOut += sizeof(sMcDaDt);
                       
            for(n = 0; n < pu->ucN; n++)
            {
               eRet = pFunc(eTrans, &(pu->sOne[m].uApp[n]), pTmp, &usLenTmp);
               if(MC_OK != eRet)
               {
                   #ifdef MC_DBG
                   MCDBG("emc_trans_afn12f9_s2m() pFunc() error %d!", eRet);
                   #endif
                   return eRet;
               }

               pTmp += usLenTmp;
               usLenOut += usLenTmp;
            }     
        }

        // sTs
        sYMDhm_f = pf->sTs;
        eRet = emc_trans_YYMMDDhhmm(eTrans, &(pu->sTs), &sYMDhm_f);
        if(MC_OK != eRet)
        {
            #ifdef MC_DBG
            MCDBG("emc_trans_afn12f9_m2s() emc_trans_YYMMDDhhmm() error %d!", eRet);
            #endif
            return eRet;
        }

        usLenOut += sizeof(sMcFmt02_f);
    }
    else
    {
         #ifdef MC_DBG
         MCDBG("emc_trans_afn12f9_s2m() eTrans is out of range!");
         #endif
         return MC_ERR_OUTRNG;    
    }

    // �������
    * pusLen = usLenOut;
    return MC_OK;
}

/*****************************************************************************
 �� �� ��  : emc_trans_afn13f1
 ��������  : ���ݽṹת������
 ��Ӧ����  : MCMD_AFN_D_F1_CLOCK
 �������  : eMcTrans eTrans  
             void* pUser      
             void* pFrame     
             UINT16* pusLen   
 �������  : ��
 �� �� ֵ  : 
 ���ú���  : 
 ��������  : 
 
 �޸���ʷ      :
  1.��    ��   : 2013��11��14��
    ��    ��   : liming
    �޸�����   : �����ɺ���

*****************************************************************************/
eMcErr emc_trans_afn13f1(eMcTrans eTrans, void* pUser, void* pFrame, UINT16* pusLen)
{
    eMcErr eRet = MC_OK;
    eRet = emc_trans_YWMDhms(eTrans, (sMcYWMDhms*)pUser, (sMcYWMDhms_f*)pFrame);
    if(MC_OK != eRet)
    {
        #ifdef MC_DBG
        MCDBG("emc_trans_afn13f1() emc_trans_YWMDhms() error %d!", eRet);
        #endif
        return eRet;
    }

    *pusLen = sizeof(sMcYWMDhms_f);
    return MC_OK;
}

/*****************************************************************************
 �� �� ��  : emc_trans_afn13f2
 ��������  : ���ݽṹת������
 ��Ӧ����  : MCMD_AFN_D_F2_PARA_STATE
 �������  : eMcTrans eTrans  
             void* pUser      
             void* pFrame     
             UINT16* pusLen   
 �������  : ��
 �� �� ֵ  : 
 ���ú���  : 
 ��������  : 
 
 �޸���ʷ      :
  1.��    ��   : 2013��11��14��
    ��    ��   : liming
    �޸�����   : �����ɺ���

*****************************************************************************/
eMcErr emc_trans_afn13f2(eMcTrans eTrans, void* pUser, void* pFrame, UINT16* pusLen)
{  
    sMcAfn13f2   *pu = NULL;
    sMcAfn13f2_f *pf = NULL;
    INT32          i = 0;
    INT32          j = 0;
    UINT8      ucTmp = 0;
    UINT8      ucVal = 0;
    eMcmd       eCmd = MCMD_AFN_F_UNKOWN;

    if(!pUser || !pFrame || !pusLen)
    {
        #ifdef MC_DBG
        MCDBG("emc_trans_afn13f2() para pointer is null!");
        #endif
        return MC_ERR_NULL;
    }
   
    pu = (sMcAfn13f2*)pUser;
    pf = (sMcAfn13f2_f *)pFrame;

    // �û��ൽ��֡��
    if(MC_TRANS_U2F == eTrans)
    {
        // �����Ϸ���
        // �Ȳ�������,���������û��ڷ�֡ʱ�����Դ����ظ���������
        // MC_SET_NUM_MAX
        
        // ��������
        memset(pf->ucSet, 0x0, sizeof(sMcAfn13f2_f));
        
        // ��������
        for(i = 0; i < pu->ucNum; i++)
        {
            eCmd = pu->eCmd[i];

            // �жϸ������Ƿ������ò�������
            switch ( eCmd )
            {
                case MCMD_AFN_4_F1_CON_UP_CFG :
                case MCMD_AFN_4_F2_MST_PARA:
                case MCMD_AFN_4_F3_CON_AUTH_PARA :
                case MCMD_AFN_4_F4_TEAM_ADDR :
                case MCMD_AFN_4_F5_CON_IP_PORT :
                case MCMD_AFN_4_F6_CON_CASC :
                case MCMD_AFN_4_F7_CON_DOWN_CFG :
                case MCMD_AFN_4_F9_CON_EVENT_CFG :
                case MCMD_AFN_4_F10_CON_STATE_INPUT :
                case MCMD_AFN_4_F17_TML_UP_CFG :
                case MCMD_AFN_4_F25_ELEC_MP_CFG :
                case MCMD_AFN_4_F26_ELEC_MP_BASE :
                case MCMD_AFN_4_F27_ELEC_LMIT_POWER :
                case MCMD_AFN_4_F28_ELEC_LMIT_FACTR :
                case MCMD_AFN_4_F29_ELEC_FIX_HARM :
                case MCMD_AFN_4_F30_ELEC_FLASH :
                case MCMD_AFN_4_F33_NELC_MP_CFG :
                case MCMD_AFN_4_F34_NELC_MP_PARA :
                case MCMD_AFN_4_F35_NELC_MP_LMIT :
                case MCMD_AFN_4_F49_FREZ_TASK_PARA :
                    break;
                    
                default:
                    #ifdef MC_DBG
                    MCDBG("emc_trans_afn13f2() eCmd para is out of range");
                    #endif
                    return MC_ERR_PARA;
                    // break;
            }

            // ��������Ӧ�����к�
            ucTmp = (UINT8)(eCmd & 0xFF);

            // ��������31���ֽ������е�λ��
            j = (ucTmp-1) / 8;
            ucVal = 0x01 << ((ucTmp-1) % 8);
            pf->ucSet[j] |= ucVal;
        }
    }
    // ��֡�ൽ�û���
    else if(MC_TRANS_F2U == eTrans)
    {
        for(i = 0; i < 31; i++)
        {
            ucVal = pf->ucSet[i];
            for(j = 0; j < 8; j++)
            {
                if(ucVal & (0x01 << j))
                {
                    // ��������ݶ�Ӧ��������
                    eCmd = (eMcmd)(0x0400 | ((i * 8) + j + 1));

                    // �жϸ��������Ƿ���Ч
                    switch ( eCmd )
                    {
                        case MCMD_AFN_4_F1_CON_UP_CFG :
                        case MCMD_AFN_4_F2_MST_PARA:
                        case MCMD_AFN_4_F3_CON_AUTH_PARA :
                        case MCMD_AFN_4_F4_TEAM_ADDR :
                        case MCMD_AFN_4_F5_CON_IP_PORT :
                        case MCMD_AFN_4_F6_CON_CASC :
                        case MCMD_AFN_4_F7_CON_DOWN_CFG :
                        case MCMD_AFN_4_F9_CON_EVENT_CFG :
                        case MCMD_AFN_4_F10_CON_STATE_INPUT :
                        case MCMD_AFN_4_F17_TML_UP_CFG :
                        case MCMD_AFN_4_F25_ELEC_MP_CFG :
                        case MCMD_AFN_4_F26_ELEC_MP_BASE :
                        case MCMD_AFN_4_F27_ELEC_LMIT_POWER :
                        case MCMD_AFN_4_F28_ELEC_LMIT_FACTR :
                        case MCMD_AFN_4_F29_ELEC_FIX_HARM :
                        case MCMD_AFN_4_F30_ELEC_FLASH :
                        case MCMD_AFN_4_F33_NELC_MP_CFG :
                        case MCMD_AFN_4_F34_NELC_MP_PARA :
                        case MCMD_AFN_4_F35_NELC_MP_LMIT :
                        case MCMD_AFN_4_F49_FREZ_TASK_PARA :
                            break;
                            
                        default:
                            #ifdef MC_DBG
                            MCDBG("emc_trans_afn13f2() eCmd para is out of range");
                            #endif
                            return MC_ERR_PARA;
                            // break;
                    }

                    // ת������
                    pu->eCmd[ucTmp++] = eCmd;
                    
                }
            }
        }

        // ����Ѿ����õĲ�������
        pu->ucNum = ucTmp;
    }
    else
    {
         #ifdef MC_DBG
         MCDBG("emc_trans_afn13f2() eTrans is out of range!");
         #endif
         return MC_ERR_OUTRNG;    
    }
   
    // �������
   *pusLen = sizeof(sMcAfn13f2_f);   
    return MC_OK;
}

/*****************************************************************************
 �� �� ��  : emc_trans_afn13f3
 ��������  : ���ݽṹת������
 ��Ӧ����  : MCMD_AFN_D_F3_EVENT_1
 �������  : eMcTrans eTrans  
             void* pUser      
             void* pFrame     
             UINT16* pusLen   
 �������  : ��
 �� �� ֵ  : 
 ���ú���  : 
 ��������  : 
 
 �޸���ʷ      :
  1.��    ��   : 2013��11��14��
    ��    ��   : liming
    �޸�����   : �����ɺ���

*****************************************************************************/
eMcErr emc_trans_afn13f3(eMcTrans eTrans, void* pUser, void* pFrame, UINT16* pusLen)
{  
    UINT16       *pu = NULL;
    UINT16       *pf = NULL;
   
    if(!pUser || !pFrame || !pusLen)
    {
        #ifdef MC_DBG
        MCDBG("emc_trans_afn13f3() para pointer is null!");
        #endif
        return MC_ERR_NULL;
    }
   
    pu = (UINT16*)pUser;
    pf = (UINT16*)pFrame;

    // �û��ൽ��֡��
    if(MC_TRANS_U2F == eTrans)
    {
        *pf = *pu;
    }
    // ��֡�ൽ�û���
    else if(MC_TRANS_F2U == eTrans)
    {
        *pu = *pf;
    }
    else
    {
         #ifdef MC_DBG
         MCDBG("emc_trans_afn13f3() eTrans is out of range!");
         #endif
         return MC_ERR_OUTRNG;    
    }
   
    // �������
    *pusLen = sizeof(UINT16);
    return MC_OK;
}

/*****************************************************************************
 �� �� ��  : emc_trans_afn13f4
 ��������  : ���ݽṹת������
 ��Ӧ����  : MCMD_AFN_D_F4_EVENT_2
 �������  : eMcTrans eTrans  
             void* pUser      
             void* pFrame     
             UINT16* pusLen   
 �������  : ��
 �� �� ֵ  : 
 ���ú���  : 
 ��������  : 
 
 �޸���ʷ      :
  1.��    ��   : 2013��11��14��
    ��    ��   : liming
    �޸�����   : �����ɺ���

*****************************************************************************/
eMcErr emc_trans_afn13f4(eMcTrans eTrans, void* pUser, void* pFrame, UINT16* pusLen)
{
    return emc_trans_afn13f3(eTrans, pUser, pFrame, pusLen);
}

/*****************************************************************************
 �� �� ��  : emc_trans_afn13f5
 ��������  : ���ݽṹת������
 ��Ӧ����  : MCMD_AFN_D_F5_EVENT_STATE
 �������  : eMcTrans eTrans  
             void* pUser      
             void* pFrame     
             UINT16* pusLen   
 �������  : ��
 �� �� ֵ  : 
 ���ú���  : 
 ��������  : 
 
 �޸���ʷ      :
  1.��    ��   : 2013��11��14��
    ��    ��   : liming
    �޸�����   : �����ɺ���

*****************************************************************************/
eMcErr emc_trans_afn13f5(eMcTrans eTrans, void* pUser, void* pFrame, UINT16* pusLen)
{  
    sMcAfn13f5    *pu = NULL;
    sMcAfn13f5_f  *pf = NULL;
    INT32           i = 0;
    INT32           j = 0;
    INT32       index = 0;
   
    if(!pUser || !pFrame || !pusLen)
    {
        #ifdef MC_DBG
        MCDBG("emc_trans_afn13f5() para pointer is null!");
        #endif
        return MC_ERR_NULL;
    }
   
    pu = (sMcAfn13f5*)pUser;
    pf = (sMcAfn13f5_f*)pFrame;

    // �û��ൽ��֡��
    if(MC_TRANS_U2F == eTrans)
    {
        for(i = 0; i < MC_ERC_NUM_MAX; i++)
        {
            if(TRUE == pu->bHave[i])
            {
                pf->ucHave[i/8] |= (0x01 << (i%8));
            }
        }
    }
    // ��֡�ൽ�û���
    else if(MC_TRANS_F2U == eTrans)
    {
        for(i = 0; i < 8; i++)
        {
            for(j = 0; j < 8; j++)
            {
                index = i*8+j;
                if(index > MC_ERC_NUM_MAX)
                {
                    i = 100; // ��ѭ����������8�ϲ�Ҳ���˳�ѭ��
                    break;
                }
                
                if( pf->ucHave[i] & (0x01 << j))
                {
                    pu->bHave[index] = TRUE;
                }
                else
                {
                    pu->bHave[index] = FALSE;
                }
            }
        }
    }
    else
    {
         #ifdef MC_DBG
         MCDBG("emc_trans_afn13f5() eTrans is out of range!");
         #endif
         return MC_ERR_OUTRNG;    
    }
   
    // �������
    *pusLen = sizeof(sMcAfn13f5_f);
    return MC_OK;
}

/*****************************************************************************
 �� �� ��  : emc_trans_afn13f6
 ��������  : ���ݽṹת������
 ��Ӧ����  : MCMD_AFN_D_F6_POWR_TIMES
 �������  : eMcTrans eTrans  
             void* pUser      
             void* pFrame     
             UINT16* pusLen   
 �������  : ��
 �� �� ֵ  : 
 ���ú���  : 
 ��������  : 
 
 �޸���ʷ      :
  1.��    ��   : 2013��11��14��
    ��    ��   : liming
    �޸�����   : �����ɺ���

*****************************************************************************/
eMcErr emc_trans_afn13f6(eMcTrans eTrans, void* pUser, void* pFrame, UINT16* pusLen)
{  
    sMcAfn13f6    *pu = NULL;
    sMcAfn13f6_f  *pf = NULL;
    eMcErr       eRet = MC_OK;
    INT32           i = 0;
    UINT32      ulPow = 0;
    UINT32     ulData = 0;
    UINT8       ucTmp = 0;
    UINT8   ucData[7] = {0};
    
    if(!pUser || !pFrame || !pusLen)
    {
        #ifdef MC_DBG
        MCDBG("emc_trans_afn13f6() para pointer is null!");
        #endif
        return MC_ERR_NULL;
    }
   
    pu = (sMcAfn13f6*)pUser;
    pf = (sMcAfn13f6_f*)pFrame;

    // �û��ൽ��֡��
    if(MC_TRANS_U2F == eTrans)
    {
        // �ж����ݵ���Ч��
        if(pu->ulTimes > MC_POWR_TIMES_MAX)
        {
            #ifdef MC_DBG
            MCDBG("emc_trans_afn13f6() para ulPowerTimes is out of range!");
            #endif
            return MC_ERR_OUTRNG;
        }
        
        // ������ת��Ϊ����
        ulData = pu->ulTimes;

        for(i = 0; i < 6; i++)
        {
            ulPow     = nmc_pow(6-i);
            ucTmp     = ulData / ulPow;
            ulData   -= ucTmp  * ulPow; 
            ucData[i] = ucTmp  + '0';
        }
      
        // ת����bcd       
        eRet = emc_str_to_bcd((const UINT8*)ucData, pf->ucBcd, 6);
        if(MC_OK != eRet)
        {
            #ifdef MC_DBG
            MCDBG("emc_trans_afn13f6() emc_str_to_bcd() error %d!", eRet);
            #endif
            return eRet;
        }
    }
    // ��֡�ൽ�û���
    else if(MC_TRANS_F2U == eTrans)
    {
        // ת����strs       
        eRet = emc_bcd_to_str((const UINT8*)&(pf->ucBcd[0]), (UINT8*)ucData, 3);
        if(MC_OK != eRet)
        {
            #ifdef MC_DBG
            MCDBG("emc_trans_afn13f6() emc_bcd_to_str() error %d!", eRet);
            #endif
            return eRet;
        }

        // ת��������
        pu->ulTimes = atol((const char*)ucData);
    }
    else
    {
         #ifdef MC_DBG
         MCDBG("emc_trans_afn13f6() eTrans is out of range!");
         #endif
         return MC_ERR_OUTRNG;    
    }
   
    // �������
    *pusLen = sizeof(sMcAfn13f6_f);
    return MC_OK;
}

/*****************************************************************************
 �� �� ��  : emc_trans_afn13f5
 ��������  : ���ݽṹת������
 ��Ӧ����  : MCMD_AFN_D_F9_STATE
 �������  : eMcTrans eTrans  
             void* pUser      
             void* pFrame     
             UINT16* pusLen   
 �������  : ��
 �� �� ֵ  : 
 ���ú���  : 
 ��������  : 
 
 �޸���ʷ      :
  1.��    ��   : 2013��11��14��
    ��    ��   : liming
    �޸�����   : �����ɺ���

*****************************************************************************/
eMcErr emc_trans_afn13f9(eMcTrans eTrans, void* pUser, void* pFrame, UINT16* pusLen)
{  
    sMcAfn13f9    *pu = NULL;
    sMcAfn13f9_f  *pf = NULL;
    INT32           i = 0;
  
    if(!pUser || !pFrame || !pusLen)
    {
        #ifdef MC_DBG
        MCDBG("emc_trans_afn13f9() para pointer is null!");
        #endif
        return MC_ERR_NULL;
    }
   
    pu = (sMcAfn13f9*)pUser;
    pf = (sMcAfn13f9_f*)pFrame;

    // �û��ൽ��֡��
    if(MC_TRANS_U2F == eTrans)
    {
        // bSt
        pf->ucSt8 = 0;
        for(i = 0; i < 8; i++)
        {
            if(TRUE == pu->bSt[i])
            {
                pf->ucSt8 |= (0x01 << i);
            }
        }
        
        // bCd
        pf->ucCd8 = 0;
        for(i = 0; i < 8; i++)
        {
            if(TRUE == pu->bCd[i])
            {
                pf->ucCd8 |= (0x01 << i);
            }
        }        
    }
    // ��֡�ൽ�û���
    else if(MC_TRANS_F2U == eTrans)
    {
        // ucSt8
        for(i = 0; i < 8; i++)
        {
            if((0x01 << i) & pf->ucSt8)
            {
                pu->bSt[i] = TRUE;
            }
            else
            {
                pu->bSt[i] = FALSE;
            }
        }

        // ucCd8
        for(i = 0; i < 8; i++)
        {
            if((0x01 << i) & pf->ucCd8)
            {
                pu->bCd[i] = TRUE;
            }
            else
            {
                pu->bCd[i] = FALSE;
            }
        }
    }
    else
    {
         #ifdef MC_DBG
         MCDBG("emc_trans_afn13f9() eTrans is out of range!");
         #endif
         return MC_ERR_OUTRNG;    
    }
   
    // �������
    *pusLen = sizeof(sMcAfn13f9_f);
    return MC_OK;
}

/*****************************************************************************
 �� �� ��  : emc_trans_afn13f25
 ��������  : ���ݽṹת������
 ��Ӧ����  : MCMD_AFN_D_F25_POWR_HAVE_T
 �������  : eMcTrans eTrans  
             void* pUser      
             void* pFrame     
             UINT16* pusLen   
 �������  : ��
 �� �� ֵ  : 
 ���ú���  : 
 ��������  : 
 
 �޸���ʷ      :
  1.��    ��   : 2013��11��15��
    ��    ��   : liming
    �޸�����   : �����ɺ���

*****************************************************************************/
eMcErr emc_trans_afn13f25(eMcTrans eTrans, void* pUser, void* pFrame, UINT16* pusLen)
{  
    sMcAfn13f25    *pu = NULL;
    sMcAfn13f25_f  *pf = NULL;
    eMcErr        eRet = MC_OK;  
    sMcFmt_sXX_XXXX fXX_XXXX;
    
    if(!pUser || !pFrame || !pusLen)
    {
        #ifdef MC_DBG
        MCDBG("emc_trans_afn13f25() para pointer is null!");
        #endif
        return MC_ERR_NULL;
    }
   
    pu = (sMcAfn13f25*)pUser;
    pf = (sMcAfn13f25_f*)pFrame;
    memset(&fXX_XXXX, 0, sizeof(sMcFmt_sXX_XXXX));

    if(MC_TRANS_U2F == eTrans)
    {
        eRet = emc_trans_sXX_XXXX(eTrans, &(pu->fXX_XXXX), &fXX_XXXX);
        if(MC_OK != eRet)
        {
            #ifdef MC_DBG
            MCDBG("emc_trans_afn13f25() emc_trans_sXX_XXXX() error %d!", eRet);
            #endif
            return eRet;
        }

        pf->fXX_XXXX = fXX_XXXX;
    }
    else if(MC_TRANS_F2U == eTrans)
    {
        fXX_XXXX = pf->fXX_XXXX ;
        eRet = emc_trans_sXX_XXXX(eTrans, &(pu->fXX_XXXX), &fXX_XXXX);
        if(MC_OK != eRet)
        {
            #ifdef MC_DBG
            MCDBG("emc_trans_afn13f25() emc_trans_sXX_XXXX() error %d!", eRet);
            #endif
            return eRet;
        }
    }
    else
    {
         #ifdef MC_DBG
         MCDBG("emc_trans_afn13f25() eTrans is out of range!");
         #endif
         return MC_ERR_OUTRNG;    
    }

    // �������
    *pusLen = sizeof(sMcAfn13f25_f);
    return MC_OK;
}

/*****************************************************************************
 �� �� ��  : emc_trans_afn13f26
 ��������  : ���ݽṹת������
 ��Ӧ����  : MCMD_AFN_D_F26_POWR_NONE_T
 �������  : eMcTrans eTrans  
             void* pUser      
             void* pFrame     
             UINT16* pusLen   
 �������  : ��
 �� �� ֵ  : 
 ���ú���  : 
 ��������  : 
 
 �޸���ʷ      :
  1.��    ��   : 2013��11��15��
    ��    ��   : liming
    �޸�����   : �����ɺ���

*****************************************************************************/
eMcErr emc_trans_afn13f26(eMcTrans eTrans, void* pUser, void* pFrame, UINT16* pusLen)
{
    return emc_trans_afn13f25(eTrans, pUser, pFrame, pusLen);
}

/*****************************************************************************
 �� �� ��  : emc_trans_afn13f27
 ��������  : ���ݽṹת������
 ��Ӧ����  : MCMD_AFN_D_F27_FACTR_T
 �������  : eMcTrans eTrans  
             void* pUser      
             void* pFrame     
             UINT16* pusLen   
 �������  : ��
 �� �� ֵ  : 
 ���ú���  : 
 ��������  : 
 
 �޸���ʷ      :
  1.��    ��   : 2013��11��15��
    ��    ��   : liming
    �޸�����   : �����ɺ���

*****************************************************************************/
eMcErr emc_trans_afn13f27(eMcTrans eTrans, void* pUser, void* pFrame, UINT16* pusLen)
{  
    sMcAfn13f27    *pu = NULL;
    sMcAfn13f27_f  *pf = NULL;
    eMcErr        eRet = MC_OK;  
    sMcFmt_XX_XX fXX_XX;
    
    if(!pUser || !pFrame || !pusLen)
    {
        #ifdef MC_DBG
        MCDBG("emc_trans_afn13f27() para pointer is null!");
        #endif
        return MC_ERR_NULL;
    }
    
    pu = (sMcAfn13f27*)pUser;
    pf = (sMcAfn13f27_f*)pFrame;
    memset(&fXX_XX, 0, sizeof(sMcFmt_XX_XX));
    
    if(MC_TRANS_U2F == eTrans)
    {
        eRet = emc_trans_XX_XX(eTrans, &(pu->fXX_XX), &fXX_XX);
        if(MC_OK != eRet)
        {
            #ifdef MC_DBG
            MCDBG("emc_trans_afn13f27() emc_trans_XX_XX() error %d!", eRet);
            #endif
            return eRet;
        }
        
        pf->fXX_XX = fXX_XX;
    }
    else if(MC_TRANS_F2U == eTrans)
    {
        fXX_XX = pf->fXX_XX;
        eRet = emc_trans_XX_XX(eTrans, &(pu->fXX_XX), &fXX_XX);
        if(MC_OK != eRet)
        {
            #ifdef MC_DBG
            MCDBG("emc_trans_afn13f27() emc_trans_XX_XX() error %d!", eRet);
            #endif
            return eRet;
        }
    }
    else
    {
         #ifdef MC_DBG
         MCDBG("emc_trans_afn13f27() eTrans is out of range!");
         #endif
         return MC_ERR_OUTRNG;  
    }

    // �������
    *pusLen = sizeof(sMcAfn13f27_f);
    return MC_OK;
}

/*****************************************************************************
 �� �� ��  : emc_trans_afn13f28
 ��������  : ���ݽṹת������
 ��Ӧ����  : MCMD_AFN_D_F28_FACTR_A
 �������  : eMcTrans eTrans  
             void* pUser      
             void* pFrame     
             UINT16* pusLen   
 �������  : ��
 �� �� ֵ  : 
 ���ú���  : 
 ��������  : 
 
 �޸���ʷ      :
  1.��    ��   : 2013��11��15��
    ��    ��   : liming
    �޸�����   : �����ɺ���

*****************************************************************************/
eMcErr emc_trans_afn13f28(eMcTrans eTrans, void* pUser, void* pFrame, UINT16* pusLen)
{
    return emc_trans_afn13f27(eTrans, pUser, pFrame, pusLen);
}

/*****************************************************************************
 �� �� ��  : emc_trans_afn13f29
 ��������  : ���ݽṹת������
 ��Ӧ����  : MCMD_AFN_D_F29_FACTR_B
 �������  : eMcTrans eTrans  
             void* pUser      
             void* pFrame     
             UINT16* pusLen   
 �������  : ��
 �� �� ֵ  : 
 ���ú���  : 
 ��������  : 
 
 �޸���ʷ      :
  1.��    ��   : 2013��11��15��
    ��    ��   : liming
    �޸�����   : �����ɺ���

*****************************************************************************/
eMcErr emc_trans_afn13f29(eMcTrans eTrans, void* pUser, void* pFrame, UINT16* pusLen)
{
    return emc_trans_afn13f27(eTrans, pUser, pFrame, pusLen);
}

/*****************************************************************************
 �� �� ��  : emc_trans_afn13f30
 ��������  : ���ݽṹת������
 ��Ӧ����  : MCMD_AFN_D_F30_FACTR_C
 �������  : eMcTrans eTrans  
             void* pUser      
             void* pFrame     
             UINT16* pusLen   
 �������  : ��
 �� �� ֵ  : 
 ���ú���  : 
 ��������  : 
 
 �޸���ʷ      :
  1.��    ��   : 2013��11��15��
    ��    ��   : liming
    �޸�����   : �����ɺ���

*****************************************************************************/
eMcErr emc_trans_afn13f30(eMcTrans eTrans, void* pUser, void* pFrame, UINT16* pusLen)
{
    return emc_trans_afn13f27(eTrans, pUser, pFrame, pusLen);
}

/*****************************************************************************
 �� �� ��  : emc_trans_afn13f33
 ��������  : ���ݽṹת������
 ��Ӧ����  : MCMD_AFN_D_F33_DEMAND
 �������  : eMcTrans eTrans  
             void* pUser      
             void* pFrame     
             UINT16* pusLen   
 �������  : ��
 �� �� ֵ  : 
 ���ú���  : 
 ��������  : 
 
 �޸���ʷ      :
  1.��    ��   : 2013��11��15��
    ��    ��   : liming
    �޸�����   : �����ɺ���

*****************************************************************************/
eMcErr emc_trans_afn13f33(eMcTrans eTrans, void* pUser, void* pFrame, UINT16* pusLen)
{
    return emc_trans_afn13f25(eTrans, pUser, pFrame, pusLen);
}

/*****************************************************************************
 �� �� ��  : emc_trans_afn13f34
 ��������  : ���ݽṹת������
 ��Ӧ����  : MCMD_AFN_D_F34_DEMAND_MAX
 �������  : eMcTrans eTrans  
             void* pUser      
             void* pFrame     
             UINT16* pusLen   
 �������  : ��
 �� �� ֵ  : 
 ���ú���  : 
 ��������  : 
 
 �޸���ʷ      :
  1.��    ��   : 2013��11��15��
    ��    ��   : liming
    �޸�����   : �����ɺ���

*****************************************************************************/
eMcErr emc_trans_afn13f34(eMcTrans eTrans, void* pUser, void* pFrame, UINT16* pusLen)
{
    return emc_trans_afn13f25(eTrans, pUser, pFrame, pusLen);
}

/*****************************************************************************
 �� �� ��  : emc_trans_afn13f35
 ��������  : ���ݽṹת������
 ��Ӧ����  : MCMD_AFN_D_F35_DEMAND_TIME
 �������  : eMcTrans eTrans  
             void* pUser      
             void* pFrame     
             UINT16* pusLen   
 �������  : ��
 �� �� ֵ  : 
 ���ú���  : 
 ��������  : 
 
 �޸���ʷ      :
  1.��    ��   : 2013��11��15��
    ��    ��   : liming
    �޸�����   : �����ɺ���

*****************************************************************************/
eMcErr emc_trans_afn13f35(eMcTrans eTrans, void* pUser, void* pFrame, UINT16* pusLen)
{
    sMcAfn13f35    *pu = NULL;
    sMcAfn13f35_f  *pf = NULL;
    eMcErr        eRet = MC_OK;  
    sMcFmt02_f   sFmt02_f;
    
    if(!pUser || !pFrame || !pusLen)
    {
        #ifdef MC_DBG
        MCDBG("emc_trans_afn13f35() para pointer is null!");
        #endif
        return MC_ERR_NULL;
    }
   
    pu = (sMcAfn13f35*)pUser;
    pf = (sMcAfn13f35_f*)pFrame;
    memset(&sFmt02_f, 0, sizeof(sMcFmt02_f));

    if(MC_TRANS_U2F == eTrans)
    {
        eRet = emc_trans_YYMMDDhhmm(eTrans, &(pu->sTime), &sFmt02_f);
        if(MC_OK != eRet)
        {
            #ifdef MC_DBG
            MCDBG("emc_trans_afn13f35() emc_trans_YYMMDDhhmm() error %d!", eRet);
            #endif
            return eRet;
        }
        
        pf->sTime = sFmt02_f;
    }
    else if(MC_TRANS_F2U == eTrans)
    {    
        pf->sTime = sFmt02_f;
        eRet = emc_trans_YYMMDDhhmm(eTrans, &(pu->sTime), &sFmt02_f);
        if(MC_OK != eRet)
        {
            #ifdef MC_DBG
            MCDBG("emc_trans_afn13f35() emc_trans_YYMMDDhhmm() error %d!", eRet);
            #endif
            return eRet;
        }
    }
    else
    {
         #ifdef MC_DBG
         MCDBG("emc_trans_afn13f35() eTrans is out of range!");
         #endif
         return MC_ERR_OUTRNG;    
    }
 
    // �������
    *pusLen = sizeof(sMcYMDhm_f);
    return MC_OK;
}

/*****************************************************************************
 �� �� ��  : emc_trans_afn13f41
 ��������  : ���ݽṹת������
 ��Ӧ����  : MCMD_AFN_D_F41_POWR_HAVE_A
 �������  : eMcTrans eTrans  
             void* pUser      
             void* pFrame     
             UINT16* pusLen   
 �������  : ��
 �� �� ֵ  : 
 ���ú���  : 
 ��������  : 
 
 �޸���ʷ      :
  1.��    ��   : 2013��11��15��
    ��    ��   : liming
    �޸�����   : �����ɺ���

*****************************************************************************/
eMcErr emc_trans_afn13f41(eMcTrans eTrans, void* pUser, void* pFrame, UINT16* pusLen)
{
    return emc_trans_afn13f25(eTrans, pUser, pFrame, pusLen);
}

/*****************************************************************************
 �� �� ��  : emc_trans_afn13f42
 ��������  : ���ݽṹת������
 ��Ӧ����  : MCMD_AFN_D_F42_POWR_HAVE_B
 �������  : eMcTrans eTrans  
             void* pUser      
             void* pFrame     
             UINT16* pusLen   
 �������  : ��
 �� �� ֵ  : 
 ���ú���  : 
 ��������  : 
 
 �޸���ʷ      :
  1.��    ��   : 2013��11��15��
    ��    ��   : liming
    �޸�����   : �����ɺ���

*****************************************************************************/
eMcErr emc_trans_afn13f42(eMcTrans eTrans, void* pUser, void* pFrame, UINT16* pusLen)
{
    return emc_trans_afn13f25(eTrans, pUser, pFrame, pusLen);
}

/*****************************************************************************
 �� �� ��  : emc_trans_afn13f43
 ��������  : ���ݽṹת������
 ��Ӧ����  : MCMD_AFN_D_F43_POWR_HAVE_C
 �������  : eMcTrans eTrans  
             void* pUser      
             void* pFrame     
             UINT16* pusLen   
 �������  : ��
 �� �� ֵ  : 
 ���ú���  : 
 ��������  : 
 
 �޸���ʷ      :
  1.��    ��   : 2013��11��15��
    ��    ��   : liming
    �޸�����   : �����ɺ���

*****************************************************************************/
eMcErr emc_trans_afn13f43(eMcTrans eTrans, void* pUser, void* pFrame, UINT16* pusLen)
{
    return emc_trans_afn13f25(eTrans, pUser, pFrame, pusLen);
}

/*****************************************************************************
 �� �� ��  : emc_trans_afn13f44
 ��������  : ���ݽṹת������
 ��Ӧ����  : MCMD_AFN_D_F44_POWR_NONE_A
 �������  : eMcTrans eTrans  
             void* pUser      
             void* pFrame     
             UINT16* pusLen   
 �������  : ��
 �� �� ֵ  : 
 ���ú���  : 
 ��������  : 
 
 �޸���ʷ      :
  1.��    ��   : 2013��11��15��
    ��    ��   : liming
    �޸�����   : �����ɺ���

*****************************************************************************/
eMcErr emc_trans_afn13f44(eMcTrans eTrans, void* pUser, void* pFrame, UINT16* pusLen)
{
    return emc_trans_afn13f25(eTrans, pUser, pFrame, pusLen);
}

/*****************************************************************************
 �� �� ��  : emc_trans_afn13f45
 ��������  : ���ݽṹת������
 ��Ӧ����  : MCMD_AFN_D_F45_POWR_NONE_B
 �������  : eMcTrans eTrans  
             void* pUser      
             void* pFrame     
             UINT16* pusLen   
 �������  : ��
 �� �� ֵ  : 
 ���ú���  : 
 ��������  : 
 
 �޸���ʷ      :
  1.��    ��   : 2013��11��15��
    ��    ��   : liming
    �޸�����   : �����ɺ���

*****************************************************************************/
eMcErr emc_trans_afn13f45(eMcTrans eTrans, void* pUser, void* pFrame, UINT16* pusLen)
{
    return emc_trans_afn13f25(eTrans, pUser, pFrame, pusLen);
}

/*****************************************************************************
 �� �� ��  : emc_trans_afn13f46
 ��������  : ���ݽṹת������
 ��Ӧ����  : MCMD_AFN_D_F46_POWR_NONE_C
 �������  : eMcTrans eTrans  
             void* pUser      
             void* pFrame     
             UINT16* pusLen   
 �������  : ��
 �� �� ֵ  : 
 ���ú���  : 
 ��������  : 
 
 �޸���ʷ      :
  1.��    ��   : 2013��11��15��
    ��    ��   : liming
    �޸�����   : �����ɺ���

*****************************************************************************/
eMcErr emc_trans_afn13f46(eMcTrans eTrans, void* pUser, void* pFrame, UINT16* pusLen)
{
    return emc_trans_afn13f25(eTrans, pUser, pFrame, pusLen);
}

/*****************************************************************************
 �� �� ��  : emc_trans_afn13f49
 ��������  : ���ݽṹת������
 ��Ӧ����  : MCMD_AFN_D_F49_POWR_HAVE_FRTH
 �������  : eMcTrans eTrans  
             void* pUser      
             void* pFrame     
             UINT16* pusLen   
 �������  : ��
 �� �� ֵ  : 
 ���ú���  : 
 ��������  : 
 
 �޸���ʷ      :
  1.��    ��   : 2013��11��15��
    ��    ��   : liming
    �޸�����   : �����ɺ���

*****************************************************************************/
eMcErr emc_trans_afn13f49(eMcTrans eTrans, void* pUser, void* pFrame, UINT16* pusLen)
{
    sMcAfn13f49   *pu = NULL;
    sMcAfn13f49_f  *pf = NULL;
    eMcErr        eRet = MC_OK;  
    sMcFmt04_f dXXXXXX_XXXX;
    
    if(!pUser || !pFrame || !pusLen)
    {
        #ifdef MC_DBG
        MCDBG("emc_trans_afn13f49() para pointer is null!");
        #endif
        return MC_ERR_NULL;
    }
   
    pu = (sMcAfn13f49*)pUser;
    pf = (sMcAfn13f49_f*)pFrame;
    memset(&dXXXXXX_XXXX, 0, sizeof(sMcFmt04_f));

    if(MC_TRANS_U2F == eTrans)
    {
        eRet = emc_trans_XXXXXX_XXXX(eTrans, &(pu->dXXXXXX_XXXX), &dXXXXXX_XXXX);
        if(MC_OK != eRet)
        {
            #ifdef MC_DBG
            MCDBG("emc_trans_afn13f49() emc_trans_XXXXXX_XXXX() error %d!", eRet);
            #endif
            return eRet;
        }
        
        pf->dXXXXXX_XXXX = dXXXXXX_XXXX;
    }
    else if(MC_TRANS_F2U == eTrans)
    {
        dXXXXXX_XXXX = pf->dXXXXXX_XXXX;
        eRet = emc_trans_XXXXXX_XXXX(eTrans, &(pu->dXXXXXX_XXXX), &dXXXXXX_XXXX);
        if(MC_OK != eRet)
        {
            #ifdef MC_DBG
            MCDBG("emc_trans_afn13f49() emc_trans_XXXXXX_XXXX() error %d!", eRet);
            #endif
            return eRet;
        }
    }
    else
    {
         #ifdef MC_DBG
         MCDBG("emc_trans_afn13f49() eTrans is out of range!");
         #endif
         return MC_ERR_OUTRNG;    
    }
    
    // �������
    *pusLen = sizeof(sMcFmt04_f);
    return MC_OK;
}

/*****************************************************************************
 �� �� ��  : emc_trans_afn13f50
 ��������  : ���ݽṹת������
 ��Ӧ����  : MCMD_AFN_D_F50_POWR_HAVE_BACK
 �������  : eMcTrans eTrans  
             void* pUser      
             void* pFrame     
             UINT16* pusLen   
 �������  : ��
 �� �� ֵ  : 
 ���ú���  : 
 ��������  : 
 
 �޸���ʷ      :
  1.��    ��   : 2013��11��15��
    ��    ��   : liming
    �޸�����   : �����ɺ���

*****************************************************************************/
eMcErr emc_trans_afn13f50(eMcTrans eTrans, void* pUser, void* pFrame, UINT16* pusLen)
{
    return emc_trans_afn13f49(eTrans, pUser, pFrame, pusLen);
}

/*****************************************************************************
 �� �� ��  : emc_trans_afn13f51
 ��������  : ���ݽṹת������
 ��Ӧ����  : MCMD_AFN_D_F51_POWR_NONE_FRTH
 �������  : eMcTrans eTrans  
             void* pUser      
             void* pFrame     
             UINT16* pusLen   
 �������  : ��
 �� �� ֵ  : 
 ���ú���  : 
 ��������  : 
 
 �޸���ʷ      :
  1.��    ��   : 2013��11��15��
    ��    ��   : liming
    �޸�����   : �����ɺ���

*****************************************************************************/
eMcErr emc_trans_afn13f51(eMcTrans eTrans, void* pUser, void* pFrame, UINT16* pusLen)
{
    sMcAfn13f51    *pu = NULL;
    sMcAfn13f51_f  *pf = NULL;
    eMcErr        eRet = MC_OK;  
    sMcFmt05_f dXXXXXX_XX;
    
    if(!pUser || !pFrame || !pusLen)
    {
        #ifdef MC_DBG
        MCDBG("emc_trans_afn13f51() para pointer is null!");
        #endif
        return MC_ERR_NULL;
    }
   
    pu = (sMcAfn13f51*)pUser;
    pf = (sMcAfn13f51_f*)pFrame;
    memset(&dXXXXXX_XX, 0, sizeof(sMcFmt05_f));
    
    if(MC_TRANS_U2F == eTrans)
    {
        eRet = emc_trans_XXXXXX_XX(eTrans, &(pu->dXXXXXX_XX), &dXXXXXX_XX);
        if(MC_OK != eRet)
        {
            #ifdef MC_DBG
            MCDBG("emc_trans_afn13f51() emc_trans_XXXXXX_XX() error %d!", eRet);
            #endif
            return eRet;
        }
        
        pf->dXXXXXX_XX = dXXXXXX_XX;
    }
    else if(MC_TRANS_F2U == eTrans)
    {
        dXXXXXX_XX = pf->dXXXXXX_XX;
        eRet = emc_trans_XXXXXX_XX(eTrans, &(pu->dXXXXXX_XX), &dXXXXXX_XX);
        if(MC_OK != eRet)
        {
            #ifdef MC_DBG
            MCDBG("emc_trans_afn13f51() emc_trans_XXXXXX_XX() error %d!", eRet);
            #endif
            return eRet;
        }   
    }
    else
    {
         #ifdef MC_DBG
         MCDBG("emc_trans_afn13f51() eTrans is out of range!");
         #endif
         return MC_ERR_OUTRNG;    
    }
    
    // �������
    * pusLen = sizeof(sMcFmt05_f);
    return MC_OK;
}

/*****************************************************************************
 �� �� ��  : emc_trans_afn13f52
 ��������  : ���ݽṹת������
 ��Ӧ����  : MCMD_AFN_D_F52_POWR_NONE_BACK
 �������  : eMcTrans eTrans  
             void* pUser      
             void* pFrame     
             UINT16* pusLen   
 �������  : ��
 �� �� ֵ  : 
 ���ú���  : 
 ��������  : 
 
 �޸���ʷ      :
  1.��    ��   : 2013��11��15��
    ��    ��   : liming
    �޸�����   : �����ɺ���

*****************************************************************************/
eMcErr emc_trans_afn13f52(eMcTrans eTrans, void* pUser, void* pFrame, UINT16* pusLen)
{
    return emc_trans_afn13f51(eTrans, pUser, pFrame, pusLen);
}

/*****************************************************************************
 �� �� ��  : emc_trans_afn13f57
 ��������  : ���ݽṹת������
 ��Ӧ����  : MCMD_AFN_D_F57_VOLT_A
 �������  : eMcTrans eTrans  
             void* pUser      
             void* pFrame     
             UINT16* pusLen   
 �������  : ��
 �� �� ֵ  : 
 ���ú���  : 
 ��������  : 
 
 �޸���ʷ      :
  1.��    ��   : 2013��11��15��
    ��    ��   : liming
    �޸�����   : �����ɺ���

*****************************************************************************/
eMcErr emc_trans_afn13f57(eMcTrans eTrans, void* pUser, void* pFrame, UINT16* pusLen)
{
    sMcAfn13f57    *pu = NULL;
    sMcAfn13f57_f  *pf = NULL;
    eMcErr        eRet = MC_OK;  
    sMcFmt_XXX_X fXXX_X;
    
    if(!pUser || !pFrame || !pusLen)
    {
        #ifdef MC_DBG
        MCDBG("emc_trans_afn13f57() para pointer is null!");
        #endif
        return MC_ERR_NULL;
    }
   
    pu = (sMcAfn13f57*)pUser;
    pf = (sMcAfn13f57_f*)pFrame;
    memset(&fXXX_X, 0, sizeof(sMcFmt_XXX_X));
    
    if(MC_TRANS_U2F == eTrans)
    {
        
        eRet = emc_trans_XXX_X(eTrans, &(pu->fXXX_X), &fXXX_X);
        if(MC_OK != eRet)
        {
            #ifdef MC_DBG
            MCDBG("emc_trans_afn13f57() emc_trans_XXX_X() error %d!", eRet);
            #endif
            return eRet;
        }
        
        pf->fXXX_X = fXXX_X;
    }
    else if(MC_TRANS_F2U == eTrans)
    {
        fXXX_X = pf->fXXX_X;
        eRet = emc_trans_XXX_X(eTrans, &(pu->fXXX_X), &fXXX_X);
        if(MC_OK != eRet)
        {
            #ifdef MC_DBG
            MCDBG("emc_trans_afn13f57() emc_trans_XXX_X() error %d!", eRet);
            #endif
            return eRet;
        }
    }
    else
    {
         #ifdef MC_DBG
         MCDBG("emc_trans_afn13f57() eTrans is out of range!");
         #endif
         return MC_ERR_OUTRNG;    
    }
    
    // �������
    * pusLen = sizeof(sMcAfn13f57_f);
    return MC_OK;
}

/*****************************************************************************
 �� �� ��  : emc_trans_afn13f58
 ��������  : ���ݽṹת������
 ��Ӧ����  : MCMD_AFN_D_F58_VOLT_B
 �������  : eMcTrans eTrans  
             void* pUser      
             void* pFrame     
             UINT16* pusLen   
 �������  : ��
 �� �� ֵ  : 
 ���ú���  : 
 ��������  : 
 
 �޸���ʷ      :
  1.��    ��   : 2013��11��15��
    ��    ��   : liming
    �޸�����   : �����ɺ���

*****************************************************************************/
eMcErr emc_trans_afn13f58(eMcTrans eTrans, void* pUser, void* pFrame, UINT16* pusLen)
{
    return emc_trans_afn13f57(eTrans, pUser, pFrame, pusLen);
}


/*****************************************************************************
 �� �� ��  : emc_trans_afn13f59
 ��������  : ���ݽṹת������
 ��Ӧ����  : MCMD_AFN_D_F59_VOLT_C
 �������  : eMcTrans eTrans  
             void* pUser      
             void* pFrame     
             UINT16* pusLen   
 �������  : ��
 �� �� ֵ  : 
 ���ú���  : 
 ��������  : 
 
 �޸���ʷ      :
  1.��    ��   : 2013��11��15��
    ��    ��   : liming
    �޸�����   : �����ɺ���

*****************************************************************************/
eMcErr emc_trans_afn13f59(eMcTrans eTrans, void* pUser, void* pFrame, UINT16* pusLen)
{
    return emc_trans_afn13f57(eTrans, pUser, pFrame, pusLen);
}

/*****************************************************************************
 �� �� ��  : emc_trans_afn13f60
 ��������  : ���ݽṹת������
 ��Ӧ����  : MCMD_AFN_D_F60_VANGL_A
 �������  : eMcTrans eTrans  
             void* pUser      
             void* pFrame     
             UINT16* pusLen   
 �������  : ��
 �� �� ֵ  : 
 ���ú���  : 
 ��������  : 
 
 �޸���ʷ      :
  1.��    ��   : 2013��11��15��
    ��    ��   : liming
    �޸�����   : �����ɺ���

*****************************************************************************/
eMcErr emc_trans_afn13f60(eMcTrans eTrans, void* pUser, void* pFrame, UINT16* pusLen)
{
    sMcAfn13f60   *pu = NULL;
    sMcAfn13f60_f  *pf = NULL;
    eMcErr        eRet = MC_OK;  
    sMcFmt07_f fsXXX_X;
    
    if(!pUser || !pFrame || !pusLen)
    {
        #ifdef MC_DBG
        MCDBG("emc_trans_afn13f60() para pointer is null!");
        #endif
        return MC_ERR_NULL;
    }
   
    pu = (sMcAfn13f60*)pUser;
    pf = (sMcAfn13f60_f*)pFrame;
    memset(&fsXXX_X, 0, sizeof(sMcFmt07_f));

    if(MC_TRANS_U2F == eTrans)
    {
        eRet = emc_trans_sXXX_X(eTrans, &(pu->fsXXX_X), &fsXXX_X);
        if(MC_OK != eRet)
        {
            #ifdef MC_DBG
            MCDBG("emc_trans_afn13f60() emc_trans_sXXX_X() error %d!", eRet);
            #endif
            return eRet;
        }

        pf->fsXXX_X = fsXXX_X;
    }
    else if(MC_TRANS_F2U == eTrans)
    {
        fsXXX_X = pf->fsXXX_X;
        eRet = emc_trans_sXXX_X(eTrans, &(pu->fsXXX_X), &fsXXX_X);
        if(MC_OK != eRet)
        {
            #ifdef MC_DBG
            MCDBG("emc_trans_afn13f60() emc_trans_sXXX_X() error %d!", eRet);
            #endif
            return eRet;
        }
    }
    else
    {
         #ifdef MC_DBG
         MCDBG("emc_trans_afn13f57() eTrans is out of range!");
         #endif
         return MC_ERR_OUTRNG;    
    }

    // �������
    * pusLen = sizeof(sMcAfn13f60_f);
    return MC_OK;
}

/*****************************************************************************
 �� �� ��  : emc_trans_afn13f61
 ��������  : ���ݽṹת������
 ��Ӧ����  : MCMD_AFN_D_F61_VANGL_B
 �������  : eMcTrans eTrans  
             void* pUser      
             void* pFrame     
             UINT16* pusLen   
 �������  : ��
 �� �� ֵ  : 
 ���ú���  : 
 ��������  : 
 
 �޸���ʷ      :
  1.��    ��   : 2013��11��15��
    ��    ��   : liming
    �޸�����   : �����ɺ���

*****************************************************************************/
eMcErr emc_trans_afn13f61(eMcTrans eTrans, void* pUser, void* pFrame, UINT16* pusLen)
{
    return emc_trans_afn13f60(eTrans, pUser, pFrame, pusLen);
}

/*****************************************************************************
 �� �� ��  : emc_trans_afn13f62
 ��������  : ���ݽṹת������
 ��Ӧ����  : MCMD_AFN_D_F62_VANGL_C
 �������  : eMcTrans eTrans  
             void* pUser      
             void* pFrame     
             UINT16* pusLen   
 �������  : ��
 �� �� ֵ  : 
 ���ú���  : 
 ��������  : 
 
 �޸���ʷ      :
  1.��    ��   : 2013��11��15��
    ��    ��   : liming
    �޸�����   : �����ɺ���

*****************************************************************************/
eMcErr emc_trans_afn13f62(eMcTrans eTrans, void* pUser, void* pFrame, UINT16* pusLen)
{
    return emc_trans_afn13f60(eTrans, pUser, pFrame, pusLen);
}

/*****************************************************************************
 �� �� ��  : emc_trans_afn13f63
 ��������  : ���ݽṹת������
 ��Ӧ����  : MCMD_AFN_D_F63_VOLT_UBL
 �������  : eMcTrans eTrans  
             void* pUser      
             void* pFrame     
             UINT16* pusLen   
 �������  : ��
 �� �� ֵ  : 
 ���ú���  : 
 ��������  : 
 
 �޸���ʷ      :
  1.��    ��   : 2013��11��15��
    ��    ��   : liming
    �޸�����   : �����ɺ���

*****************************************************************************/
eMcErr emc_trans_afn13f63(eMcTrans eTrans, void* pUser, void* pFrame, UINT16* pusLen)
{
    return emc_trans_afn13f27(eTrans, pUser, pFrame, pusLen);
}

/*****************************************************************************
 �� �� ��  : emc_trans_afn13f64
 ��������  : ���ݽṹת������
 ��Ӧ����  : MCMD_AFN_D_F64_CIRCLE_V
 �������  : eMcTrans eTrans  
             void* pUser      
             void* pFrame     
             UINT16* pusLen   
 �������  : ��
 �� �� ֵ  : 
 ���ú���  : 
 ��������  : 
 
 �޸���ʷ      :
  1.��    ��   : 2013��11��15��
    ��    ��   : liming
    �޸�����   : �����ɺ���

*****************************************************************************/
eMcErr emc_trans_afn13f64(eMcTrans eTrans, void* pUser, void* pFrame, UINT16* pusLen)
{
    return emc_trans_afn13f25(eTrans, pUser, pFrame, pusLen);
}

/*****************************************************************************
 �� �� ��  : emc_trans_afn13f65
 ��������  : ���ݽṹת������
 ��Ӧ����  : MCMD_AFN_D_F65_ELEC_A
 �������  : eMcTrans eTrans  
             void* pUser      
             void* pFrame     
             UINT16* pusLen   
 �������  : ��
 �� �� ֵ  : 
 ���ú���  : 
 ��������  : 
 
 �޸���ʷ      :
  1.��    ��   : 2013��11��15��
    ��    ��   : liming
    �޸�����   : �����ɺ���

*****************************************************************************/
eMcErr emc_trans_afn13f65(eMcTrans eTrans, void* pUser, void* pFrame, UINT16* pusLen)
{
    sMcAfn13f65   *pu = NULL;
    sMcAfn13f65_f  *pf = NULL;
    eMcErr        eRet = MC_OK;  
    sMcFmt09_f fsXXX_XXX;
    
    if(!pUser || !pFrame || !pusLen)
    {
        #ifdef MC_DBG
        MCDBG("emc_trans_afn13f65() para pointer is null!");
        #endif
        return MC_ERR_NULL;
    }
   
    pu = (sMcAfn13f65*)pUser;
    pf = (sMcAfn13f65_f*)pFrame;
    memset(&fsXXX_XXX, 0, sizeof(sMcFmt09_f));
    
    if(MC_TRANS_U2F == eTrans)
    {
        eRet = emc_trans_sXXX_XXX(eTrans, &(pu->fsXXX_XXX), &fsXXX_XXX);
        if(MC_OK != eRet)
        {
            #ifdef MC_DBG
            MCDBG("emc_trans_afn13f65() emc_trans_sXXX_XXX() error %d!", eRet);
            #endif
            return eRet;
        }
        
        pf->fsXXX_XXX = fsXXX_XXX;
    }
    else if(MC_TRANS_F2U == eTrans)
    {
        fsXXX_XXX = pf->fsXXX_XXX;
        eRet = emc_trans_sXXX_XXX(eTrans, &(pu->fsXXX_XXX), &fsXXX_XXX);
        if(MC_OK != eRet)
        {
            #ifdef MC_DBG
            MCDBG("emc_trans_afn13f65() emc_trans_sXXX_XXX() error %d!", eRet);
            #endif
            return eRet;
        }
    }
    else
    {
         #ifdef MC_DBG
         MCDBG("emc_trans_afn13f57() eTrans is out of range!");
         #endif
         return MC_ERR_OUTRNG;    
    }

    // �������
    * pusLen = sizeof(sMcAfn13f65_f);
    return MC_OK;
}

/*****************************************************************************
 �� �� ��  : emc_trans_afn13f66
 ��������  : ���ݽṹת������
 ��Ӧ����  : MCMD_AFN_D_F66_ELEC_B
 �������  : eMcTrans eTrans  
             void* pUser      
             void* pFrame     
             UINT16* pusLen   
 �������  : ��
 �� �� ֵ  : 
 ���ú���  : 
 ��������  : 
 
 �޸���ʷ      :
  1.��    ��   : 2013��11��15��
    ��    ��   : liming
    �޸�����   : �����ɺ���

*****************************************************************************/
eMcErr emc_trans_afn13f66(eMcTrans eTrans, void* pUser, void* pFrame, UINT16* pusLen)
{
    return emc_trans_afn13f65(eTrans, pUser, pFrame, pusLen);
}

/*****************************************************************************
 �� �� ��  : emc_trans_afn13f67
 ��������  : ���ݽṹת������
 ��Ӧ����  : MCMD_AFN_D_F67_ELEC_C
 �������  : eMcTrans eTrans  
             void* pUser      
             void* pFrame     
             UINT16* pusLen   
 �������  : ��
 �� �� ֵ  : 
 ���ú���  : 
 ��������  : 
 
 �޸���ʷ      :
  1.��    ��   : 2013��11��15��
    ��    ��   : liming
    �޸�����   : �����ɺ���

*****************************************************************************/
eMcErr emc_trans_afn13f67(eMcTrans eTrans, void* pUser, void* pFrame, UINT16* pusLen)
{
    return emc_trans_afn13f65(eTrans, pUser, pFrame, pusLen);
}

/*****************************************************************************
 �� �� ��  : emc_trans_afn13f68
 ��������  : ���ݽṹת������
 ��Ӧ����  : MCMD_AFN_D_F68_ELEC_M
 �������  : eMcTrans eTrans  
             void* pUser      
             void* pFrame     
             UINT16* pusLen   
 �������  : ��
 �� �� ֵ  : 
 ���ú���  : 
 ��������  : 
 
 �޸���ʷ      :
  1.��    ��   : 2013��11��15��
    ��    ��   : liming
    �޸�����   : �����ɺ���

*****************************************************************************/
eMcErr emc_trans_afn13f68(eMcTrans eTrans, void* pUser, void* pFrame, UINT16* pusLen)
{
    return emc_trans_afn13f65(eTrans, pUser, pFrame, pusLen);
}

/*****************************************************************************
 �� �� ��  : emc_trans_afn13f69
 ��������  : ���ݽṹת������
 ��Ӧ����  : MCMD_AFN_D_F69_EANGL_A
 �������  : eMcTrans eTrans  
             void* pUser      
             void* pFrame     
             UINT16* pusLen   
 �������  : ��
 �� �� ֵ  : 
 ���ú���  : 
 ��������  : 
 
 �޸���ʷ      :
  1.��    ��   : 2013��11��15��
    ��    ��   : liming
    �޸�����   : �����ɺ���

*****************************************************************************/
eMcErr emc_trans_afn13f69(eMcTrans eTrans, void* pUser, void* pFrame, UINT16* pusLen)
{
    return emc_trans_afn13f60(eTrans, pUser, pFrame, pusLen);
}

/*****************************************************************************
 �� �� ��  : emc_trans_afn13f70
 ��������  : ���ݽṹת������
 ��Ӧ����  : MCMD_AFN_D_F70_EANGL_B
 �������  : eMcTrans eTrans  
             void* pUser      
             void* pFrame     
             UINT16* pusLen   
 �������  : ��
 �� �� ֵ  : 
 ���ú���  : 
 ��������  : 
 
 �޸���ʷ      :
  1.��    ��   : 2013��11��15��
    ��    ��   : liming
    �޸�����   : �����ɺ���

*****************************************************************************/
eMcErr emc_trans_afn13f70(eMcTrans eTrans, void* pUser, void* pFrame, UINT16* pusLen)
{
    return emc_trans_afn13f60(eTrans, pUser, pFrame, pusLen);
}

/*****************************************************************************
 �� �� ��  : emc_trans_afn13f71
 ��������  : ���ݽṹת������
 ��Ӧ����  : MCMD_AFN_D_F71_EANGL_C
 �������  : eMcTrans eTrans  
             void* pUser      
             void* pFrame     
             UINT16* pusLen   
 �������  : ��
 �� �� ֵ  : 
 ���ú���  : 
 ��������  : 
 
 �޸���ʷ      :
  1.��    ��   : 2013��11��15��
    ��    ��   : liming
    �޸�����   : �����ɺ���

*****************************************************************************/
eMcErr emc_trans_afn13f71(eMcTrans eTrans, void* pUser, void* pFrame, UINT16* pusLen)
{
    return emc_trans_afn13f60(eTrans, pUser, pFrame, pusLen);
}

/*****************************************************************************
 �� �� ��  : emc_trans_afn13f72
 ��������  : ���ݽṹת������
 ��Ӧ����  : MCMD_AFN_D_F72_ELEC_UBL
 �������  : eMcTrans eTrans  
             void* pUser      
             void* pFrame     
             UINT16* pusLen   
 �������  : ��
 �� �� ֵ  : 
 ���ú���  : 
 ��������  : 
 
 �޸���ʷ      :
  1.��    ��   : 2013��11��15��
    ��    ��   : liming
    �޸�����   : �����ɺ���

*****************************************************************************/
eMcErr emc_trans_afn13f72(eMcTrans eTrans, void* pUser, void* pFrame, UINT16* pusLen)
{
    return emc_trans_afn13f60(eTrans, pUser, pFrame, pusLen);
}

/*****************************************************************************
 �� �� ��  : emc_trans_afn13f73
 ��������  : ���ݽṹת������
 ��Ӧ����  : MCMD_AFN_D_F73_VDMAX_A
 �������  : eMcTrans eTrans  
             void* pUser      
             void* pFrame     
             UINT16* pusLen   
 �������  : ��
 �� �� ֵ  : 
 ���ú���  : 
 ��������  : 
 
 �޸���ʷ      :
  1.��    ��   : 2013��11��15��
    ��    ��   : liming
    �޸�����   : �����ɺ���

*****************************************************************************/
eMcErr emc_trans_afn13f73(eMcTrans eTrans, void* pUser, void* pFrame, UINT16* pusLen)
{
    return emc_trans_afn13f57(eTrans, pUser, pFrame, pusLen);
}

/*****************************************************************************
 �� �� ��  : emc_trans_afn13f74
 ��������  : ���ݽṹת������
 ��Ӧ����  : MCMD_AFN_D_F74_VDMAX_A_TIME
 �������  : eMcTrans eTrans  
             void* pUser      
             void* pFrame     
             UINT16* pusLen   
 �������  : ��
 �� �� ֵ  : 
 ���ú���  : 
 ��������  : 
 
 �޸���ʷ      :
  1.��    ��   : 2013��11��15��
    ��    ��   : liming
    �޸�����   : �����ɺ���

*****************************************************************************/
eMcErr emc_trans_afn13f74(eMcTrans eTrans, void* pUser, void* pFrame, UINT16* pusLen)
{
    return emc_trans_afn13f35(eTrans, pUser, pFrame, pusLen);
}

/*****************************************************************************
 �� �� ��  : emc_trans_afn13f75
 ��������  : ���ݽṹת������
 ��Ӧ����  : MCMD_AFN_D_F75_VDMAX_B
 �������  : eMcTrans eTrans  
             void* pUser      
             void* pFrame     
             UINT16* pusLen   
 �������  : ��
 �� �� ֵ  : 
 ���ú���  : 
 ��������  : 
 
 �޸���ʷ      :
  1.��    ��   : 2013��11��15��
    ��    ��   : liming
    �޸�����   : �����ɺ���

*****************************************************************************/
eMcErr emc_trans_afn13f75(eMcTrans eTrans, void* pUser, void* pFrame, UINT16* pusLen)
{
    return emc_trans_afn13f57(eTrans, pUser, pFrame, pusLen);
}

/*****************************************************************************
 �� �� ��  : emc_trans_afn13f76
 ��������  : ���ݽṹת������
 ��Ӧ����  : MCMD_AFN_D_F76_VDMAX_B_TIME
 �������  : eMcTrans eTrans  
             void* pUser      
             void* pFrame     
             UINT16* pusLen   
 �������  : ��
 �� �� ֵ  : 
 ���ú���  : 
 ��������  : 
 
 �޸���ʷ      :
  1.��    ��   : 2013��11��15��
    ��    ��   : liming
    �޸�����   : �����ɺ���

*****************************************************************************/
eMcErr emc_trans_afn13f76(eMcTrans eTrans, void* pUser, void* pFrame, UINT16* pusLen)
{
    return emc_trans_afn13f35(eTrans, pUser, pFrame, pusLen);
}

/*****************************************************************************
 �� �� ��  : emc_trans_afn13f77
 ��������  : ���ݽṹת������
 ��Ӧ����  : MCMD_AFN_D_F77_VDMAX_C
 �������  : eMcTrans eTrans  
             void* pUser      
             void* pFrame     
             UINT16* pusLen   
 �������  : ��
 �� �� ֵ  : 
 ���ú���  : 
 ��������  : 
 
 �޸���ʷ      :
  1.��    ��   : 2013��11��15��
    ��    ��   : liming
    �޸�����   : �����ɺ���

*****************************************************************************/
eMcErr emc_trans_afn13f77(eMcTrans eTrans, void* pUser, void* pFrame, UINT16* pusLen)
{
    return emc_trans_afn13f57(eTrans, pUser, pFrame, pusLen);
}

/*****************************************************************************
 �� �� ��  : emc_trans_afn13f78
 ��������  : ���ݽṹת������
 ��Ӧ����  : MCMD_AFN_D_F78_VDMAX_C_TIME
 �������  : eMcTrans eTrans  
             void* pUser      
             void* pFrame     
             UINT16* pusLen   
 �������  : ��
 �� �� ֵ  : 
 ���ú���  : 
 ��������  : 
 
 �޸���ʷ      :
  1.��    ��   : 2013��11��15��
    ��    ��   : liming
    �޸�����   : �����ɺ���

*****************************************************************************/
eMcErr emc_trans_afn13f78(eMcTrans eTrans, void* pUser, void* pFrame, UINT16* pusLen)
{
    return emc_trans_afn13f35(eTrans, pUser, pFrame, pusLen);
}

/*****************************************************************************
 �� �� ��  : emc_trans_afn13f81
 ��������  : ���ݽṹת������
 ��Ӧ����  : MCMD_AFN_D_F81_IDMAX_A
 �������  : eMcTrans eTrans  
             void* pUser      
             void* pFrame     
             UINT16* pusLen   
 �������  : ��
 �� �� ֵ  : 
 ���ú���  : 
 ��������  : 
 
 �޸���ʷ      :
  1.��    ��   : 2013��11��15��
    ��    ��   : liming
    �޸�����   : �����ɺ���

*****************************************************************************/
eMcErr emc_trans_afn13f81(eMcTrans eTrans, void* pUser, void* pFrame, UINT16* pusLen)
{
    return emc_trans_afn13f65(eTrans, pUser, pFrame, pusLen);
}

/*****************************************************************************
 �� �� ��  : emc_trans_afn13f82
 ��������  : ���ݽṹת������
 ��Ӧ����  : MCMD_AFN_D_F82_IDMAX_A_TIME
 �������  : eMcTrans eTrans  
             void* pUser      
             void* pFrame     
             UINT16* pusLen   
 �������  : ��
 �� �� ֵ  : 
 ���ú���  : 
 ��������  : 
 
 �޸���ʷ      :
  1.��    ��   : 2013��11��15��
    ��    ��   : liming
    �޸�����   : �����ɺ���

*****************************************************************************/
eMcErr emc_trans_afn13f82(eMcTrans eTrans, void* pUser, void* pFrame, UINT16* pusLen)
{
    return emc_trans_afn13f35(eTrans, pUser, pFrame, pusLen);
}

/*****************************************************************************
 �� �� ��  : emc_trans_afn13f83
 ��������  : ���ݽṹת������
 ��Ӧ����  : MCMD_AFN_D_F83_IDMAX_B
 �������  : eMcTrans eTrans  
             void* pUser      
             void* pFrame     
             UINT16* pusLen   
 �������  : ��
 �� �� ֵ  : 
 ���ú���  : 
 ��������  : 
 
 �޸���ʷ      :
  1.��    ��   : 2013��11��15��
    ��    ��   : liming
    �޸�����   : �����ɺ���

*****************************************************************************/
eMcErr emc_trans_afn13f83(eMcTrans eTrans, void* pUser, void* pFrame, UINT16* pusLen)
{
    return emc_trans_afn13f65(eTrans, pUser, pFrame, pusLen);
}

/*****************************************************************************
 �� �� ��  : emc_trans_afn13f84
 ��������  : ���ݽṹת������
 ��Ӧ����  : MCMD_AFN_D_F84_IDMAX_B_TIME
 �������  : eMcTrans eTrans  
             void* pUser      
             void* pFrame     
             UINT16* pusLen   
 �������  : ��
 �� �� ֵ  : 
 ���ú���  : 
 ��������  : 
 
 �޸���ʷ      :
  1.��    ��   : 2013��11��15��
    ��    ��   : liming
    �޸�����   : �����ɺ���

*****************************************************************************/
eMcErr emc_trans_afn13f84(eMcTrans eTrans, void* pUser, void* pFrame, UINT16* pusLen)
{
    return emc_trans_afn13f35(eTrans, pUser, pFrame, pusLen);
}

/*****************************************************************************
 �� �� ��  : emc_trans_afn13f85
 ��������  : ���ݽṹת������
 ��Ӧ����  : MCMD_AFN_D_F85_IDMAX_C
 �������  : eMcTrans eTrans  
             void* pUser      
             void* pFrame     
             UINT16* pusLen   
 �������  : ��
 �� �� ֵ  : 
 ���ú���  : 
 ��������  : 
 
 �޸���ʷ      :
  1.��    ��   : 2013��11��15��
    ��    ��   : liming
    �޸�����   : �����ɺ���

*****************************************************************************/
eMcErr emc_trans_afn13f85(eMcTrans eTrans, void* pUser, void* pFrame, UINT16* pusLen)
{
    return emc_trans_afn13f65(eTrans, pUser, pFrame, pusLen);
}

/*****************************************************************************
 �� �� ��  : emc_trans_afn13f86
 ��������  : ���ݽṹת������
 ��Ӧ����  : MCMD_AFN_D_F86_IDMAX_C_TIME
 �������  : eMcTrans eTrans  
             void* pUser      
             void* pFrame     
             UINT16* pusLen   
 �������  : ��
 �� �� ֵ  : 
 ���ú���  : 
 ��������  : 
 
 �޸���ʷ      :
  1.��    ��   : 2013��11��15��
    ��    ��   : liming
    �޸�����   : �����ɺ���

*****************************************************************************/
eMcErr emc_trans_afn13f86(eMcTrans eTrans, void* pUser, void* pFrame, UINT16* pusLen)
{
    return emc_trans_afn13f35(eTrans, pUser, pFrame, pusLen);
}

/*****************************************************************************
 �� �� ��  : emc_trans_afn13f89
 ��������  : ���ݽṹת������
 ��Ӧ����  : MCMD_AFN_D_F89_TFW_HAVE
 �������  : eMcTrans eTrans  
             void* pUser      
             void* pFrame     
             UINT16* pusLen   
 �������  : ��
 �� �� ֵ  : 
 ���ú���  : 
 ��������  : 
 
 �޸���ʷ      :
  1.��    ��   : 2013��11��15��
    ��    ��   : liming
    �޸�����   : �����ɺ���

*****************************************************************************/
eMcErr emc_trans_afn13f89(eMcTrans eTrans, void* pUser, void* pFrame, UINT16* pusLen)
{
    return emc_trans_afn13f25(eTrans, pUser, pFrame, pusLen);
}

/*****************************************************************************
 �� �� ��  : emc_trans_afn13f90
 ��������  : ���ݽṹת������
 ��Ӧ����  : MCMD_AFN_D_F90_TFW_NONE
 �������  : eMcTrans eTrans  
             void* pUser      
             void* pFrame     
             UINT16* pusLen   
 �������  : ��
 �� �� ֵ  : s
 ���ú���  : 
 ��������  : 
 
 �޸���ʷ      :
  1.��    ��   : 2013��11��15��
    ��    ��   : liming
    �޸�����   : �����ɺ���

*****************************************************************************/
eMcErr emc_trans_afn13f90(eMcTrans eTrans, void* pUser, void* pFrame, UINT16* pusLen)
{
    return emc_trans_afn13f25(eTrans, pUser, pFrame, pusLen);
}

/*****************************************************************************
 �� �� ��  : emc_trans_afn13f91
 ��������  : ���ݽṹת������
 ��Ӧ����  : MCMD_AFN_D_F91_THW_HAVE
 �������  : eMcTrans eTrans  
             void* pUser      
             void* pFrame     
             UINT16* pusLen   
 �������  : ��
 �� �� ֵ  : 
 ���ú���  : 
 ��������  : 
 
 �޸���ʷ      :
  1.��    ��   : 2013��11��15��
    ��    ��   : liming
    �޸�����   : �����ɺ���

*****************************************************************************/
eMcErr emc_trans_afn13f91(eMcTrans eTrans, void* pUser, void* pFrame, UINT16* pusLen)
{
    return emc_trans_afn13f25(eTrans, pUser, pFrame, pusLen);
}

/*****************************************************************************
 �� �� ��  : emc_trans_afn13f92
 ��������  : ���ݽṹת������
 ��Ӧ����  : MCMD_AFN_D_F92_THW_NONE
 �������  : eMcTrans eTrans  
             void* pUser      
             void* pFrame     
             UINT16* pusLen   
 �������  : ��
 �� �� ֵ  : 
 ���ú���  : 
 ��������  : 
 
 �޸���ʷ      :
  1.��    ��   : 2013��11��15��
    ��    ��   : liming
    �޸�����   : �����ɺ���

*****************************************************************************/
eMcErr emc_trans_afn13f92(eMcTrans eTrans, void* pUser, void* pFrame, UINT16* pusLen)
{
    return emc_trans_afn13f25(eTrans, pUser, pFrame, pusLen);
}

/*****************************************************************************
 �� �� ��  : emc_trans_afn13f97
 ��������  : ���ݽṹת������
 ��Ӧ����  : MCMD_AFN_D_F97_VDPP_TIME_A
 �������  : eMcTrans eTrans  
             void* pUser      
             void* pFrame     
             UINT16* pusLen   
 �������  : ��
 �� �� ֵ  : 
 ���ú���  : 
 ��������  : 
 
 �޸���ʷ      :
  1.��    ��   : 2013��11��15��
    ��    ��   : liming
    �޸�����   : �����ɺ���

*****************************************************************************/
eMcErr emc_trans_afn13f97(eMcTrans eTrans, void* pUser, void* pFrame, UINT16* pusLen)
{  
    sMcAfn13f97    *pu = NULL;
    sMcAfn13f97_f  *pf = NULL;
    eMcErr        eRet = MC_OK;  
    INT32            i = 0;
    UINT16       usPow = 0;
    UINT16      usData = 0;
    UINT8        ucTmp = 0;
    UINT8    ucData[5] = {0};
        
    if(!pUser || !pFrame || !pusLen)
    {
        #ifdef MC_DBG
        MCDBG("emc_trans_afn13f97() para pointer is null!");
        #endif
        return MC_ERR_NULL;
    }
   
    pu = (sMcAfn13f97*)pUser;
    pf = (sMcAfn13f97_f*)pFrame;

    // �û��ൽ��֡��
    if(MC_TRANS_U2F == eTrans)
    {
        if(pu->usMinutes > MC_BCD_XXXX_MAX)
        {
           #ifdef MC_DBG
           MCDBG("emc_trans_afn13f97() para usMinutes is out of range! usMinutes = %d", pu->usMinutes);
           #endif
           return MC_ERR_OUTRNG;
        }
        
        // ������ת��Ϊ����
        usData = pu->usMinutes;

        for(i = 0; i < 4; i++)
        {
            usPow     = nmc_pow(4-i);
            ucTmp     = usData / usPow;
            usData   -= ucTmp  * usPow; 
            ucData[i] = ucTmp  + '0';
        }

        // ת��Ϊbcd       
        eRet = emc_str_to_bcd(ucData, pf->ucBCD, 4);
        if(MC_OK != eRet)
        {
            #ifdef MC_DBG
            MCDBG("emc_trans_afn13f97() emc_str_to_bcd() error %d!", eRet);
            #endif
            return eRet;
        }
    }
    // ��֡�ൽ�û���
    else if(MC_TRANS_F2U == eTrans)
    {
        // ת����strs       
        eRet = emc_bcd_to_str(pf->ucBCD, ucData, 2);
        if(MC_OK != eRet)
        {
            #ifdef MC_DBG
            MCDBG("emc_trans_afn13f97() emc_bcd_to_str() error %d!", eRet);
            #endif
            return eRet;
        }

        // ת��������
        pu->usMinutes = (UINT16)atol((const char*)ucData);
    }
    else
    {
         #ifdef MC_DBG
         MCDBG("emc_trans_afn13f97() eTrans is out of range!");
         #endif
         return MC_ERR_OUTRNG;    
    }
   
    // �������
    *pusLen = sizeof(sMcAfn13f97_f);
    return MC_OK;
}

/*****************************************************************************
 �� �� ��  : emc_trans_afn13f145
 ��������  : ���ݽṹת������
 ��Ӧ����  : MCMD_AFN_D_F145_HARM_VOLT_A
 �������  : eMcTrans eTrans  
             void* pUser      
             void* pFrame     
             UINT16* pusLen   
 �������  : ��
 �� �� ֵ  : 
 ���ú���  : 
 ��������  : 
 
 �޸���ʷ      :
  1.��    ��   : 2013��11��15��
    ��    ��   : liming
    �޸�����   : �����ɺ���

*****************************************************************************/
eMcErr emc_trans_afn13f145(eMcTrans eTrans, void* pUser, void* pFrame, UINT16* pusLen)
{  
    sMcAfn13f145     *pu = NULL;
    sMcAfn13f145_f   *pf = NULL;
    UINT8            ucN = 0;
    INT32              i = 0;
    eMcErr          eRet = MC_OK;
    sMcFmt08_f  fXXX_X;
   
    if(!pUser || !pFrame || !pusLen)
    {
        #ifdef MC_DBG
        MCDBG("emc_trans_afn13f145() para pointer is null!");
        #endif
        return MC_ERR_NULL;
    }
   
    pu = (sMcAfn13f145*)pUser;
    pf = (sMcAfn13f145_f*)pFrame;
    memset(&fXXX_X, 0, sizeof(sMcFmt08_f));

    // �û��ൽ��֡��
    if(MC_TRANS_U2F == eTrans)
    {
        ucN = pu->ucN;
        pf->ucN = ucN;

        // fXXX_X
        for(i = 0; i < ucN; i++)
        {
            eRet = emc_trans_XXX_X(eTrans, &(pu->fXXX_X[i]), &fXXX_X);
            if(MC_OK != eRet)
            {
                #ifdef MC_DBG
                MCDBG("emc_trans_afn13f145() emc_trans_XXX_X() error %d!", eRet);
                #endif
                return eRet;
            }
            
            pf->fXXX_X[i] = fXXX_X;
        }
    }
    // ��֡�ൽ�û���
    else if(MC_TRANS_F2U == eTrans)
    {
        ucN = pf->ucN;
        pu->ucN = ucN;

        // fXXX_X
        for(i = 0; i < ucN; i++)
        {
            fXXX_X = pf->fXXX_X[i];
            eRet = emc_trans_XXX_X(eTrans, &(pu->fXXX_X[i]), &fXXX_X);
            if(MC_OK != eRet)
            {
                #ifdef MC_DBG
                MCDBG("emc_trans_afn13f145() emc_trans_XXX_X() error %d!", eRet);
                #endif
                return eRet;
            }
        }
    }
    else
    {
         #ifdef MC_DBG
         MCDBG("emc_trans_afn13f145() eTrans is out of range!");
         #endif
         return MC_ERR_OUTRNG;    
    }

    if(ucN > MC_HARM_TIMES_MAX)
    {
        #ifdef MC_DBG
        MCDBG("emc_trans_afn13f145() para ucN is out of range! ucN = %d", ucN);
        #endif
        return MC_ERR_OUTRNG;
    }
            
    // �������
    *pusLen = sizeof(sMcFmt08_f) * ucN + 1;
    return MC_OK;
}

/*****************************************************************************
 �� �� ��  : emc_trans_afn13f148
 ��������  : ���ݽṹת������
 ��Ӧ����  : MCMD_AFN_D_F148_HARM_ELEC_A
 �������  : eMcTrans eTrans  
             void* pUser      
             void* pFrame     
             UINT16* pusLen   
 �������  : ��
 �� �� ֵ  : 
 ���ú���  : 
 ��������  : 
 
 �޸���ʷ      :
  1.��    ��   : 2013��11��15��
    ��    ��   : liming
    �޸�����   : �����ɺ���

*****************************************************************************/
eMcErr emc_trans_afn13f148(eMcTrans eTrans, void* pUser, void* pFrame, UINT16* pusLen)
{  
    sMcAfn13f148     *pu = NULL;
    sMcAfn13f148_f   *pf = NULL;
    UINT8            ucN = 0;
    INT32              i = 0;
    eMcErr          eRet = MC_OK;
    sMcFmt09_f  fsXXX_XXX;
   
    if(!pUser || !pFrame || !pusLen)
    {
        #ifdef MC_DBG
        MCDBG("emc_trans_afn13f148() para pointer is null!");
        #endif
        return MC_ERR_NULL;
    }
   
    pu = (sMcAfn13f148*)pUser;
    pf = (sMcAfn13f148_f*)pFrame;
    memset(&fsXXX_XXX, 0, sizeof(sMcFmt09_f));
    
    // �û��ൽ��֡��
    if(MC_TRANS_U2F == eTrans)
    {
        ucN = pu->ucN;
        pf->ucN = ucN;

        // fXXX_X
        for(i = 0; i < ucN; i++)
        {
            eRet = emc_trans_sXXX_XXX(eTrans, &(pu->fsXXX_XXX[i]), &fsXXX_XXX);
            if(MC_OK != eRet)
            {
                #ifdef MC_DBG
                MCDBG("emc_trans_afn13f148() emc_trans_XXX_X() error %d!", eRet);
                #endif
                return eRet;
            }

            pf->fsXXX_XXX[i] = fsXXX_XXX;
        }
    }
    // ��֡�ൽ�û���
    else if(MC_TRANS_F2U == eTrans)
    {
        ucN = pf->ucN;
        pu->ucN = ucN;

        // fXXX_X
        for(i = 0; i < ucN; i++)
        {
            fsXXX_XXX = pf->fsXXX_XXX[i];
            eRet = emc_trans_sXXX_XXX(eTrans, &(pu->fsXXX_XXX[i]), &fsXXX_XXX);
            if(MC_OK != eRet)
            {
                #ifdef MC_DBG
                MCDBG("emc_trans_afn13f148() emc_trans_XXX_X() error %d!", eRet);
                #endif
                return eRet;
            }
        }
    }
    else
    {
         #ifdef MC_DBG
         MCDBG("emc_trans_afn13f148() eTrans is out of range!");
         #endif
         return MC_ERR_OUTRNG;    
    }

    if(ucN > MC_HARM_TIMES_MAX)
    {
        #ifdef MC_DBG
        MCDBG("emc_trans_afn13f148() para ucN is out of range! ucN = %d", ucN);
        #endif
        return MC_ERR_OUTRNG;
    }
  
    // �������
    *pusLen = sizeof(sMcFmt09_f) * ucN + 1;
    return MC_OK;
}

/*****************************************************************************
 �� �� ��  : emc_trans_afn13f153
 ��������  : ���ݽṹת������
 ��Ӧ����  : MCMD_AFN_D_F153_HARM_VINC_A
 �������  : eMcTrans eTrans  
             void* pUser      
             void* pFrame     
             UINT16* pusLen   
 �������  : ��
 �� �� ֵ  : 
 ���ú���  : 
 ��������  : 
 
 �޸���ʷ      :
  1.��    ��   : 2013��11��15��
    ��    ��   : liming
    �޸�����   : �����ɺ���

*****************************************************************************/
eMcErr emc_trans_afn13f153(eMcTrans eTrans, void* pUser, void* pFrame, UINT16* pusLen)
{  
    sMcAfn13f153     *pu = NULL;
    sMcAfn13f153_f   *pf = NULL;
    UINT8            ucN = 0;
    INT32              i = 0;
    eMcErr          eRet = MC_OK;
    sMcFmt10_f   fXX_XX;
    
    if(!pUser || !pFrame || !pusLen)
    {
        #ifdef MC_DBG
        MCDBG("emc_trans_afn13f153() para pointer is null!");
        #endif
        return MC_ERR_NULL;
    }
   
    pu = (sMcAfn13f153*)pUser;
    pf = (sMcAfn13f153_f*)pFrame;
    memset(&fXX_XX, 0, sizeof(sMcFmt10_f));
    
    // �û��ൽ��֡��
    if(MC_TRANS_U2F == eTrans)
    {
        ucN = pu->ucN;
        pf->ucN = ucN;

        // fXXX_X
        for(i = 0; i < ucN; i++)
        {
            eRet = emc_trans_XX_XX(eTrans, &(pu->fXX_XX[i]), &fXX_XX);
            if(MC_OK != eRet)
            {
                #ifdef MC_DBG
                MCDBG("emc_trans_afn13f148() emc_trans_XX_XX() error %d!", eRet);
                #endif
                return eRet;
            }

            pf->fXX_XX[i] = fXX_XX;
        }
    }
    // ��֡�ൽ�û���
    else if(MC_TRANS_F2U == eTrans)
    {
        ucN = pf->ucN;
        pu->ucN = ucN;

        // fXXX_X
        for(i = 0; i < ucN; i++)
        {
            fXX_XX = pf->fXX_XX[i];
            eRet = emc_trans_XX_XX(eTrans, &(pu->fXX_XX[i]), &fXX_XX);
            if(MC_OK != eRet)
            {
                #ifdef MC_DBG
                MCDBG("emc_trans_afn13f148() emc_trans_XX_XX() error %d!", eRet);
                #endif
                return eRet;
            }
        }
    }
    else
    {
         #ifdef MC_DBG
         MCDBG("emc_trans_afn13f153() eTrans is out of range!");
         #endif
         return MC_ERR_OUTRNG;    
    }

    if(ucN > MC_HARM_TIMES_MAX)
    {
        #ifdef MC_DBG
        MCDBG("emc_trans_afn13f153() para ucN is out of range! ucN = %d", ucN);
        #endif
        return MC_ERR_OUTRNG;
    }
            
    // �������
    *pusLen = sizeof(sMcFmt10_f) * ucN + 1;
    return MC_OK;
}

/*****************************************************************************
 �� �� ��  : emc_trans_afn13f233
 ��������  : ���ݽṹת������
 ��Ӧ����  : MCMD_AFN_D_F233_NELC_VALUE
 �������  : eMcTrans eTrans  
             void* pUser      
             void* pFrame     
 �������  : UINT16* pusLen  ���֡����ֽ���
 �� �� ֵ  : 
 ���ú���  : 
 ��������  : 
 
 �޸���ʷ      :
  1.��    ��   : 2013��11��11��
    ��    ��   : liming
    �޸�����   : �����ɺ���

*****************************************************************************/
eMcErr emc_trans_afn13f233(eMcTrans eTrans, void* pUser, void* pFrame, UINT16* pusLen)
{
    eMcErr        eRet = MC_OK;
    UINT8        ucTmp = 0;
    sMcAfn13f233    *pu = NULL;
    sMcAfn13f233_f  *pf = NULL;
    sMcFmt11_f     sDouble_f;  

    if(!pUser || !pFrame || !pusLen)
    {
        #ifdef MC_DBG
        MCDBG("emc_trans_afn13f233() para pointer is null!");
        #endif
        return MC_ERR_NULL;
    }

    pu = (sMcAfn13f233*)pUser;
    pf = (sMcAfn13f233_f*)pFrame;

    // �û��ൽ��֡��
    if(MC_TRANS_U2F == eTrans)
    {
        // eType
        switch(pu->eType)
        {
            case MC_NELC_TEMP:
                ucTmp = 1;
                break;
                
            case MC_NELC_FLOW:
                ucTmp = 2;
                break;

            case MC_NELC_FV:
                ucTmp = 3;
                break;
                
            case MC_NELC_PRESS:
                ucTmp = 4;
                break;    
                
            case MC_NELC_HUMI:
                ucTmp = 5;
                break;
                
            case MC_NELC_LIGHT:
                ucTmp = 6;
                break;
                
            case MC_NELC_RV:
                ucTmp = 7;
                break;
                
            case MC_NELC_420MA:
                ucTmp = 8;
                break;
                
            default:
                #ifdef MC_DBG
                MCDBG("emc_trans_afn13f233() eType is out of range!");
                #endif
                return MC_ERR_OUTRNG;      
               // break;
        }
        
        pf->eType = ucTmp;

        // sValue
        eRet = emc_trans_sX7(eTrans, &(pu->sDouble), &sDouble_f);
        if(MC_OK != eRet)
        {
            #ifdef MC_DBG
            MCDBG("emc_trans_afn13f233() emc_trans_sX7() error %d!", eRet);
            #endif
            return eRet;
        }
        
        pf->sDouble = sDouble_f;   
    }
    // ��֡�ൽ�û���
    else if (MC_TRANS_F2U == eTrans)
    {
        switch(pf->eType)
        {
            case 1:
                pu->eType = MC_NELC_TEMP;
                break;
                
            case 2:
                pu->eType = MC_NELC_FLOW;
                break;

            case 3:
                pu->eType = MC_NELC_FV;
                break;

            case 4:
                pu->eType = MC_NELC_PRESS;
                break;

            case 5:
                pu->eType = MC_NELC_HUMI;
                break;
                
            case 6:
                pu->eType = MC_NELC_LIGHT;
                break;
                
            case 7:
                pu->eType = MC_NELC_RV;
                break;
                
            case 8:
                pu->eType = MC_NELC_420MA;
                break;
                
            default:
                pu->eType = MC_NELC_UNKOWN;
                break;

        }
  
        // sValue
        sDouble_f = pf->sDouble;
        eRet = emc_trans_sX7(eTrans, &(pu->sDouble), &sDouble_f);
        if(MC_OK != eRet)
        {
            #ifdef MC_DBG
            MCDBG("emc_trans_afn13f233() emc_trans_sX7() error %d!", eRet);
            #endif
            return eRet;
        }
    }
    else
    {
         #ifdef MC_DBG
         MCDBG("emc_trans_afn13f233() eTrans is out of range!");
         #endif
         return MC_ERR_OUTRNG;    
    }

    // �������
    *pusLen = sizeof(sMcFmt11_f) + sizeof(UINT8);
    return MC_OK;
}

/*****************************************************************************
 �� �� ��  : emc_trans_afn14f1_m2s
 ��������  : ���ݽṹת������
 ��Ӧ����  : MCMD_AFN_E_F1_EVENT_1
 �������  : eMcTrans eTrans  
             void* pUser      
             void* pFrame     
 �������  : UINT16* pusLen  ���֡����ֽ���
 �� �� ֵ  : 
 ���ú���  : 
 ��������  : 
 
 �޸���ʷ      :
  1.��    ��   : 2013��11��18��
    ��    ��   : liming
    �޸�����   : �����ɺ���

*****************************************************************************/
eMcErr emc_trans_afn14f1_m2s(eMcTrans eTrans, void* pUser, void* pFrame, UINT16* pusLen)
{
    sMcAfn14f1    *pu = NULL;
    sMcAfn14f1_f  *pf = NULL;

    if(!pUser || !pFrame || !pusLen)
    {
        #ifdef MC_DBG
        MCDBG("emc_trans_afn14f1_m2s() para pointer is null!");
        #endif
        return MC_ERR_NULL;
    }

    pu = (sMcAfn14f1*)pUser;
    pf = (sMcAfn14f1_f*)pFrame;

    // �û��ൽ��֡��
    if(MC_TRANS_U2F == eTrans)
    {
        pf->ucPm = pu->ucPm;
        pf->ucPn = pu->ucPn;
    }
    // ��֡�ൽ�û���
    else if (MC_TRANS_F2U == eTrans)
    {
        pu->ucPm = pf->ucPm;
        pu->ucPn = pf->ucPn;
    }
    else
    {
         #ifdef MC_DBG
         MCDBG("emc_trans_afn14f1_m2s() eTrans is out of range!");
         #endif
         return MC_ERR_OUTRNG;    
    }

    // �������
    *pusLen = sizeof(sMcAfn14f1_f);
    return MC_OK;
}

/*****************************************************************************
 �� �� ��  : emc_trans_afn14f3_m2s
 ��������  : ���ݽṹת������
 ��Ӧ����  : MCMD_AFN_E_F3_EVENT_3
 �������  : eMcTrans eTrans  
             void* pUser      
             void* pFrame     
 �������  : UINT16* pusLen  ���֡����ֽ���
 �� �� ֵ  : 
 ���ú���  : 
 ��������  : 
 
 �޸���ʷ      :
  1.��    ��   : 2013��11��18��
    ��    ��   : liming
    �޸�����   : �����ɺ���

*****************************************************************************/
eMcErr emc_trans_afn14f3_m2s(eMcTrans eTrans, void* pUser, void* pFrame, UINT16* pusLen)
{
    sMcAfn14f3    *pu = NULL;
    sMcAfn14f3_f  *pf = NULL;
    INT32           i = 0;

    if(!pUser || !pFrame || !pusLen)
    {
        #ifdef MC_DBG
        MCDBG("emc_trans_afn14f3_m2s() para pointer is null!");
        #endif
        return MC_ERR_NULL;
    }

    pu = (sMcAfn14f3*)pUser;
    pf = (sMcAfn14f3_f*)pFrame;

    // �û��ൽ��֡��
    if(MC_TRANS_U2F == eTrans)
    {
        pf->ucN = pu->ucN;
        
        for(i = 0; i < pu->ucN; i++)
        {
            pf->ucErc[i] = (UINT8)pu->eErc[i];
        }
    }
    // ��֡�ൽ�û���
    else if (MC_TRANS_F2U == eTrans)
    {
        pu->ucN = pf->ucN;
                
        for(i = 0; i < pf->ucN; i++)
        {
            pu->eErc[i] = (eMcErc)pf->ucErc[i];
        }
    }
    else
    {
         #ifdef MC_DBG
         MCDBG("emc_trans_afn14f3_m2s() eTrans is out of range!");
         #endif
         return MC_ERR_OUTRNG;    
    }

    // �������
    *pusLen = sizeof(UINT8) * (pf->ucN + 1);
    return MC_OK;
}

/*****************************************************************************
 �� �� ��  : emc_trans_erc_1
 ��������  : �¼���¼����ת������
 ��Ӧ�¼�  : MC_ERC_1_RESET
 �������  : eMcTrans eTrans  
             void* pUser      
             void* pFrame     
             UINT16* pusLen   
 �������  : ��
 �� �� ֵ  : 
 ���ú���  : 
 ��������  : 
 
 �޸���ʷ      :
  1.��    ��   : 2013��11��18��
    ��    ��   : liming
    �޸�����   : �����ɺ���

*****************************************************************************/
eMcErr emc_trans_erc_1(eMcTrans eTrans, void* pUser, void* pFrame, UINT16* pusLen)
{
    eMcErr    eRet = MC_OK;
    sMcErc1    *pu = NULL;
    sMcErc1_f  *pf = NULL;
    sMcYMDhm_f  sTime_f;
    
    if(!pUser || !pFrame || !pusLen)
    {
        #ifdef MC_DBG
        MCDBG("emc_trans_erc_1() para pointer is null!");
        #endif
        return MC_ERR_NULL;
    }

    pu = (sMcErc1*)pUser;
    pf = (sMcErc1_f*)pFrame;
    memset(&sTime_f, 0, sizeof(sMcYMDhm_f));

    // �û��ൽ��֡��
    if(MC_TRANS_U2F == eTrans)
    {
        // Pn
        if(pu->usPN > MC_PN_MAX)
        {
            #ifdef MC_DBG
            MCDBG("emc_trans_erc_1() para Pn is out of range! usPN = %d", pu->usPN);
            #endif
            return MC_ERR_OUTRNG;
        }

        pf->usPN = pu->usPN;

       switch(pu->eType)
       {
           case MC_RESET_HARD_INIT:
                pf->eType = 1;
                break;
                
            case MC_RESET_DATA_INIT:
                pf->eType = 2;
                break;

            case MC_RESET_FACTORY_RESET:
                pf->eType = 3;
                break;
                
            case MC_RESET_PARA_INIT:
                pf->eType = 4;
                break;
            default:
                #ifdef MC_DBG
                MCDBG("emc_trans_erc_1() para eTypeis out of range!");
                #endif
                return MC_ERR_OUTRNG;
                // break;
       }
        
       // sTime
       eRet = emc_trans_YYMMDDhhmm(eTrans, &(pu->sTime), &sTime_f);
       if(MC_OK != eRet)
       {
           #ifdef MC_DBG
           MCDBG("emc_trans_erc_1() emc_trans_YYMMDDhhmm() error %d!", eRet);
           #endif
           return eRet;
       }
        
        pf->sTime = sTime_f;
    }
    // ��֡�ൽ�û���
    else if (MC_TRANS_F2U == eTrans)
    {
        // Pn
        if(pf->usPN > MC_PN_MAX)
        {
            #ifdef MC_DBG
            MCDBG("emc_trans_erc_1() para Pn is out of range! usPN = %d", pf->usPN);
            #endif
            return MC_ERR_OUTRNG;
        }

        pu->usPN = pf->usPN;

       switch (pf->eType)
       {
           case 1 :
               pu->eType = MC_RESET_HARD_INIT;
               break;
           case 2 :
               pu->eType = MC_RESET_DATA_INIT;
               break;
           case 3 :
               pu->eType = MC_RESET_FACTORY_RESET;
               break;
           case 4 :
               pu->eType = MC_RESET_PARA_INIT;
               break;
           default:
               pu->eType = MC_RESET_UNKOWN;
               break;
       }

        // sTime
        sTime_f = pf->sTime;
        eRet = emc_trans_YYMMDDhhmm(eTrans, &(pu->sTime), &sTime_f);
        if(MC_OK != eRet)
        {
            #ifdef MC_DBG
            MCDBG("emc_trans_erc_1() emc_trans_YYMMDDhhmm() error %d!", eRet);
            #endif
            return eRet;
        }
    }
    else
    {
         #ifdef MC_DBG
         MCDBG("emc_trans_erc_1() eTrans is out of range!");
         #endif
         return MC_ERR_OUTRNG;    
    }

    // �������
    *pusLen = sizeof(sMcErcReset_f);
    return MC_OK;
}

/*****************************************************************************
 �� �� ��  : emc_trans_erc_2
 ��������  : �¼���¼����ת������
 ��Ӧ�¼�  : MC_ERC_2_DATA_CLEAR
 �������  : eMcTrans eTrans  
             void* pUser      
             void* pFrame     
             UINT16* pusLen   
 �������  : ��
 �� �� ֵ  : 
 ���ú���  : 
 ��������  : 
 
 �޸���ʷ      :
  1.��    ��   : 2013��11��18��
    ��    ��   : liming
    �޸�����   : �����ɺ���

*****************************************************************************/
eMcErr emc_trans_erc_2(eMcTrans eTrans, void* pUser, void* pFrame, UINT16* pusLen)
{
    eMcErr    eRet = MC_OK;
    sMcErc3    *pu = NULL;
    sMcErc3_f  *pf = NULL;
    sMcYMDhm_f  sTime_f;
        
    if(!pUser || !pFrame || !pusLen)
    {
        #ifdef MC_DBG
        MCDBG("emc_trans_erc_2() para pointer is null!");
        #endif
        return MC_ERR_NULL;
    }

    pu = (sMcErc3*)pUser;
    pf = (sMcErc3_f*)pFrame;
    memset(&sTime_f, 0, sizeof(sMcYMDhm_f));

    // �û��ൽ��֡��
    if(MC_TRANS_U2F == eTrans)
    {
        // Pn
        if(pu->usPN > MC_PN_MAX)
        {
            #ifdef MC_DBG
            MCDBG("emc_trans_erc_2() para Pn is out of range! usPN = %d", pu->usPN);
            #endif
            return MC_ERR_OUTRNG;
        }

        pf->usPN = pu->usPN;

        // ucPreVerson
        memcpy(pf->ucPreVerson, pu->ucPreVerson, 4);

        // ucNewVerson
        memcpy(pf->ucNewVerson, pu->ucNewVerson, 4);

        // sTime
        eRet = emc_trans_YYMMDDhhmm(eTrans, &(pu->sTime), &sTime_f);
        if(MC_OK != eRet)
        {
            #ifdef MC_DBG
            MCDBG("emc_trans_erc_2() emc_trans_YYMMDDhhmm() error %d!", eRet);
            #endif
            return eRet;
        }
        
        pf->sTime = sTime_f;
        
        // sPreTime
        eRet = emc_trans_YYMMDDhhmm(eTrans, &(pu->sPreTime), &sTime_f);
        if(MC_OK != eRet)
        {
            #ifdef MC_DBG
            MCDBG("emc_trans_erc_2() emc_trans_YYMMDDhhmm() error %d!", eRet);
            #endif
            return eRet;
        }
        
        pf->sPreTime = sTime_f;
        
        // sNewTime
        eRet = emc_trans_YYMMDDhhmm(eTrans, &(pu->sNewTime), &sTime_f);
        if(MC_OK != eRet)
        {
            #ifdef MC_DBG
            MCDBG("emc_trans_erc_2() emc_trans_YYMMDDhhmm() error %d!", eRet);
            #endif
            return eRet;
        }
        
        pf->sNewTime = sTime_f;
    }
    // ��֡�ൽ�û���
    else if (MC_TRANS_F2U == eTrans)
    {
        // Pn
        if(pf->usPN > MC_PN_MAX)
        {
            #ifdef MC_DBG
            MCDBG("emc_trans_erc_2() para Pn is out of range! usPN = %d", pf->usPN);
            #endif
            return MC_ERR_OUTRNG;
        }

        pu->usPN = pf->usPN;

        // ucPreVerson
        memcpy(pu->ucPreVerson, pf->ucPreVerson, 4);

        // ucNewVerson
        memcpy(pu->ucNewVerson, pf->ucNewVerson, 4);

        // sTime
        sTime_f = pf->sTime;
        eRet = emc_trans_YYMMDDhhmm(eTrans, &(pu->sTime), &sTime_f);
        if(MC_OK != eRet)
        {
            #ifdef MC_DBG
            MCDBG("emc_trans_erc_2() emc_trans_YYMMDDhhmm() error %d!", eRet);
            #endif
            return eRet;
        }
            
        // sPreTime
        sTime_f = pf->sPreTime;
        eRet = emc_trans_YYMMDDhhmm(eTrans, &(pu->sPreTime), &sTime_f);
        if(MC_OK != eRet)
        {
            #ifdef MC_DBG
            MCDBG("emc_trans_erc_2() emc_trans_YYMMDDhhmm() error %d!", eRet);
            #endif
            return eRet;
        }
        
        // sNewTime
        sTime_f = pf->sNewTime;
        eRet = emc_trans_YYMMDDhhmm(eTrans, &(pu->sNewTime), &sTime_f);
        if(MC_OK != eRet)
        {
            #ifdef MC_DBG
            MCDBG("emc_trans_erc_2() emc_trans_YYMMDDhhmm() error %d!", eRet);
            #endif
            return eRet;
        }
    }
    else
    {
         #ifdef MC_DBG
         MCDBG("emc_trans_erc_2() eTrans is out of range!");
         #endif
         return MC_ERR_OUTRNG;    
    }
    
    // �������
    *pusLen = sizeof(sMcErcReset_f);
    return MC_OK;
}
/*****************************************************************************
 �� �� ��  : emc_trans_erc_3
 ��������  : �¼���¼����ת������
 ��Ӧ�¼�  : MC_ERC_3_SOFT_CHANGE
 �������  : eMcTrans eTrans  
             void* pUser      
             void* pFrame     
             UINT16* pusLen   
 �������  : ��
 �� �� ֵ  : 
 ���ú���  : 
 ��������  : 
 
 �޸���ʷ      :
  1.��    ��   : 2013��11��18��
    ��    ��   : liming
    �޸�����   : �����ɺ���

*****************************************************************************/
eMcErr emc_trans_erc_3(eMcTrans eTrans, void* pUser, void* pFrame, UINT16* pusLen)
{
    eMcErr    eRet = MC_OK;
    sMcErc3    *pu = NULL;
    sMcErc3_f  *pf = NULL;
    sMcYMDhm_f  sTime_f;
    
    if(!pUser || !pFrame || !pusLen)
    {
        #ifdef MC_DBG
        MCDBG("emc_trans_erc_3() para pointer is null!");
        #endif
        return MC_ERR_NULL;
    }

    pu = (sMcErc3*)pUser;
    pf = (sMcErc3_f*)pFrame;
    memset(&sTime_f, 0, sizeof(sMcYMDhm_f));

    // �û��ൽ��֡��
    if(MC_TRANS_U2F == eTrans)
    {
        // Pn
        if(pu->usPN > MC_PN_MAX)
        {
            #ifdef MC_DBG
            MCDBG("emc_trans_erc_3() para Pn is out of range! usPN = %d", pu->usPN);
            #endif
            return MC_ERR_OUTRNG;
        }

        pf->usPN = pu->usPN;

        // ucPreVerson
        memcpy(pf->ucPreVerson, pu->ucPreVerson, 4);

        // ucNewVerson
        memcpy(pf->ucNewVerson, pu->ucNewVerson, 4);

        // sTime
        eRet = emc_trans_YYMMDDhhmm(eTrans, &(pu->sTime), &sTime_f);
        if(MC_OK != eRet)
        {
            #ifdef MC_DBG
            MCDBG("emc_trans_erc_3() emc_trans_YYMMDDhhmm() error %d!", eRet);
            #endif
            return eRet;
        }
        
        pf->sTime = sTime_f;
            
        // sPreTime
        eRet = emc_trans_YYMMDDhhmm(eTrans, &(pu->sPreTime), &sTime_f);
        if(MC_OK != eRet)
        {
            #ifdef MC_DBG
            MCDBG("emc_trans_erc_1() emc_trans_YYMMDDhhmm() error %d!", eRet);
            #endif
            return eRet;
        }
        
        pf->sPreTime = sTime_f;
            
        // sNewTime
        eRet = emc_trans_YYMMDDhhmm(eTrans, &(pu->sNewTime), &sTime_f);
        if(MC_OK != eRet)
        {
            #ifdef MC_DBG
            MCDBG("emc_trans_erc_3() emc_trans_YYMMDDhhmm() error %d!", eRet);
            #endif
            return eRet;
        }
        pf->sNewTime = sTime_f;
    }
    // ��֡�ൽ�û���
    else if (MC_TRANS_F2U == eTrans)
    {
        // Pn
        if(pf->usPN > MC_PN_MAX)
        {
            #ifdef MC_DBG
            MCDBG("emc_trans_erc_3() para Pn is out of range! usPN = %d", pf->usPN);
            #endif
            return MC_ERR_OUTRNG;
        }

        pu->usPN = pf->usPN;

        // ucPreVerson
        memcpy(pu->ucPreVerson, pf->ucPreVerson, 4);

        // ucNewVerson
        memcpy(pu->ucNewVerson, pf->ucNewVerson, 4);

        // sTime
        sTime_f = pf->sTime;
        eRet = emc_trans_YYMMDDhhmm(eTrans, &(pu->sTime), &sTime_f);
        if(MC_OK != eRet)
        {
            #ifdef MC_DBG
            MCDBG("emc_trans_erc_3() emc_trans_YYMMDDhhmm() error %d!", eRet);
            #endif
            return eRet;
        }
            
        // sPreTime        
        sTime_f = pf->sPreTime;
        eRet = emc_trans_YYMMDDhhmm(eTrans, &(pu->sPreTime), &sTime_f);
        if(MC_OK != eRet)
        {
            #ifdef MC_DBG
            MCDBG("emc_trans_erc_1() emc_trans_YYMMDDhhmm() error %d!", eRet);
            #endif
            return eRet;
        }
        
        // sNewTime
        sTime_f = pf->sNewTime;
        eRet = emc_trans_YYMMDDhhmm(eTrans, &(pu->sNewTime), &sTime_f);
        if(MC_OK != eRet)
        {
            #ifdef MC_DBG
            MCDBG("emc_trans_erc_3() emc_trans_YYMMDDhhmm() error %d!", eRet);
            #endif
            return eRet;
        }
    }
    else
    {
         #ifdef MC_DBG
         MCDBG("emc_trans_afn14f3_m2s() eTrans is out of range!");
         #endif
         return MC_ERR_OUTRNG;    
    }

    // �������
    *pusLen = sizeof(sMcErcReset_f);
    return MC_OK;
}

/*****************************************************************************
 �� �� ��  : emc_trans_erc_4
 ��������  : �¼���¼����ת������
 ��Ӧ�¼�  : MC_ERC_4_PARA_CHANGE
 �������  : eMcTrans eTrans  
             void* pUser      
             void* pFrame     
             UINT16* pusLen   
 �������  : ��
 �� �� ֵ  : 
 ���ú���  : 
 ��������  : 
 
 �޸���ʷ      :
  1.��    ��   : 2013��11��18��
    ��    ��   : liming
    �޸�����   : �����ɺ���

*****************************************************************************/
eMcErr emc_trans_erc_4(eMcTrans eTrans, void* pUser, void* pFrame, UINT16* pusLen)
{
    eMcErr     eRet = MC_OK;
    sMcErc4     *pu = NULL;
    sMcErc4_f   *pf = NULL;
    UINT8 ucDaDtNum = 0;
    UINT16    usLen = 0;
    sMcYMDhm_f   sTime_f;
    
    if(!pUser || !pFrame || !pusLen)
    {
        #ifdef MC_DBG
        MCDBG("emc_trans_erc_4() para pointer is null!");
        #endif
        return MC_ERR_NULL;
    }

    pu = (sMcErc4*)pUser;
    pf = (sMcErc4_f*)pFrame;
    memset(&sTime_f, 0, sizeof(sMcYMDhm_f));
    
    // �û��ൽ��֡��
    if(MC_TRANS_U2F == eTrans)
    {
        // Pn
        if(pu->usPN > MC_PN_MAX)
        {
            #ifdef MC_DBG
            MCDBG("emc_trans_erc_4() para Pn is out of range! usPN = %d", pu->usPN);
            #endif
            return MC_ERR_OUTRNG;
        }

        pf->usPN = pu->usPN;

        // ���ݵ�Ԫ��ʶ
        eRet = emc_cmdpn_to_dadt(MC_AFN_13_ASKR, &(pf->sDaDt[0]), &ucDaDtNum, &(pu->sCmdPn[0]), pu->ucN);
        if(MC_OK != eRet)
        {
            #ifdef MC_DBG
            MCDBG("emc_trans_erc_4() emc_dadt_to_cmdpn() error %d!", eRet);
            #endif
            return eRet;
        }

        // sTime
        eRet = emc_trans_YYMMDDhhmm(eTrans, &(pu->sTime), &sTime_f);
        if(MC_OK != eRet)
        {
            #ifdef MC_DBG
            MCDBG("emc_trans_erc_4() emc_trans_YYMMDDhhmm() error %d!", eRet);
            #endif
            return eRet;
        }
        
        pf->sTime = sTime_f;
    }
    // ��֡�ൽ�û���
    else if (MC_TRANS_F2U == eTrans)
    {
        // Pn
        if(pf->usPN > MC_PN_MAX)
        {
            #ifdef MC_DBG
            MCDBG("emc_trans_erc_4() para Pn is out of range! usPN = %d", pf->usPN);
            #endif
            return MC_ERR_OUTRNG;
        }

        pu->usPN = pf->usPN;

        // ���ݵ�Ԫ��ʶ
        // �������ݵ�Ԫ��ʶ
        usLen = *pusLen;
        usLen = usLen - sizeof(UINT16) - sizeof(sMcYMDhm_f);

        // �ж��ܲ��ܱ�4����
        if(usLen % 4 != 0)
        {
            #ifdef MC_DBG
            MCDBG("emc_trans_erc_4() para (* pusLen) is error!");
            #endif
            return MC_ERR_PARA;
        }

        ucDaDtNum = usLen / 4;
        pu->ucN = 0;
        eRet = emc_dadt_to_cmdpn(MC_AFN_13_ASKR, &(pf->sDaDt[0]), ucDaDtNum, &(pu->sCmdPn[0]), &(pu->ucN));
        if(MC_OK != eRet)
        {
            #ifdef MC_DBG
            MCDBG("emc_trans_erc_4() emc_cmdpn_to_dadt() error %d!", eRet);
            #endif
            return eRet;
        }

        // sTime
        sTime_f = pf->sTime;
        eRet = emc_trans_YYMMDDhhmm(eTrans, &(pu->sTime), &sTime_f);
        if(MC_OK != eRet)
        {
            #ifdef MC_DBG
            MCDBG("emc_trans_erc_4() emc_trans_YYMMDDhhmm() error %d!", eRet);
            #endif
            return eRet;
        }   
    }
    else
    {
         #ifdef MC_DBG
         MCDBG("emc_trans_erc_4() eTrans is out of range!");
         #endif
         return MC_ERR_OUTRNG;    
    }

    // �������
    *pusLen = sizeof(sMcDaDt) * ucDaDtNum + sizeof(UINT16) + sizeof(sMcYMDhm_f);
    return MC_OK;
}    

/*****************************************************************************
 �� �� ��  : emc_trans_erc_5
 ��������  : �¼���¼����ת������
 ��Ӧ�¼�  : MC_ERC_5_CHECK_TIME
 �������  : eMcTrans eTrans  
             void* pUser      
             void* pFrame     
             UINT16* pusLen   
 �������  : ��
 �� �� ֵ  : 
 ���ú���  : 
 ��������  : 
 
 �޸���ʷ      :
  1.��    ��   : 2013��11��18��
    ��    ��   : liming
    �޸�����   : �����ɺ���

*****************************************************************************/
eMcErr emc_trans_erc_5(eMcTrans eTrans, void* pUser, void* pFrame, UINT16* pusLen)
{
    eMcErr        eRet = MC_OK;
    sMcErc5        *pu = NULL;
    sMcErc5_f      *pf = NULL;
    sMcYMDhm_f     sTime_f;  
    sMcYWMDhms_f   sClock_f; 
    
    if(!pUser || !pFrame || !pusLen)
    {
        #ifdef MC_DBG
        MCDBG("emc_trans_erc_5() para pointer is null!");
        #endif
        return MC_ERR_NULL;
    }

    pu = (sMcErc5*)pUser;
    pf = (sMcErc5_f*)pFrame;
    memset(&sTime_f, 0, sizeof(sMcYMDhm_f));
    memset(&sClock_f, 0, sizeof(sMcYWMDhms_f));

    // �û��ൽ��֡��
    if(MC_TRANS_U2F == eTrans)
    {
        // Pn
        if(pu->usPN > MC_PN_MAX)
        {
            #ifdef MC_DBG
            MCDBG("emc_trans_erc_5() para Pn is out of range! usPN = %d", pu->usPN);
            #endif
            return MC_ERR_OUTRNG;
        }

        pf->usPN = pu->usPN;

        // sTime
        eRet = emc_trans_YYMMDDhhmm(eTrans, &(pu->sTime), &sTime_f);
        if(MC_OK != eRet)
        {
            #ifdef MC_DBG
            MCDBG("emc_trans_erc_5() emc_trans_YYMMDDhhmm() error %d!", eRet);
            #endif
            return eRet;
        }
        
        pf->sTime = sTime_f;
        
        // sClock
        eRet = emc_trans_YWMDhms(eTrans, &(pu->sClock), &sClock_f);
        if(MC_OK != eRet)
        {
            #ifdef MC_DBG
            MCDBG("emc_trans_erc_5() emc_trans_YWMDhms() error %d!", eRet);
            #endif
            return eRet;
        }
        
        pf->sClock = sClock_f;
    }
    // ��֡�ൽ�û���
    else if (MC_TRANS_F2U == eTrans)
    {
        // Pn
        if(pf->usPN > MC_PN_MAX)
        {
            #ifdef MC_DBG
            MCDBG("emc_trans_erc_5() para Pn is out of range! usPN = %d", pf->usPN);
            #endif
            return MC_ERR_OUTRNG;
        }

        pu->usPN = pf->usPN;

        // sTime
        sTime_f = pf->sTime;
        eRet = emc_trans_YYMMDDhhmm(eTrans, &(pu->sTime), &sTime_f);
        if(MC_OK != eRet)
        {
            #ifdef MC_DBG
            MCDBG("emc_trans_erc_5() emc_trans_YYMMDDhhmm() error %d!", eRet);
            #endif
            return eRet;
        }

        // sClock
        sClock_f = pf->sClock;
        eRet = emc_trans_YWMDhms(eTrans, &(pu->sClock), &sClock_f);
        if(MC_OK != eRet)
        {
            #ifdef MC_DBG
            MCDBG("emc_trans_erc_5() emc_trans_YWMDhms() error %d!", eRet);
            #endif
            return eRet;
        }
    }
    else
    {
         #ifdef MC_DBG
         MCDBG("emc_trans_erc_5() eTrans is out of range!");
         #endif
         return MC_ERR_OUTRNG;    
    }

    // �������
    *pusLen = sizeof(sMcErc5_f);
    return MC_OK;
}

/*****************************************************************************
 �� �� ��  : emc_trans_erc_6
 ��������  : �¼���¼����ת������
 ��Ӧ�¼�  : MC_ERC_6_STATE_CHANGE
 �������  : eMcTrans eTrans  
             void* pUser      
             void* pFrame     
             UINT16* pusLen   
 �������  : ��
 �� �� ֵ  : 
 ���ú���  : 
 ��������  : 
 
 �޸���ʷ      :
  1.��    ��   : 2013��11��18��
    ��    ��   : liming
    �޸�����   : �����ɺ���

*****************************************************************************/
eMcErr emc_trans_erc_6(eMcTrans eTrans, void* pUser, void* pFrame, UINT16* pusLen)
{
    eMcErr     eRet = MC_OK;
    sMcErc6     *pu = NULL;
    sMcErc6_f   *pf = NULL;
    INT32         i = 0;
    sMcYMDhm_f   sTime_f;
    
    if(!pUser || !pFrame || !pusLen)
    {
        #ifdef MC_DBG
        MCDBG("emc_trans_erc_6() para pointer is null!");
        #endif
        return MC_ERR_NULL;
    }

    pu = (sMcErc6*)pUser;
    pf = (sMcErc6_f*)pFrame;
    memset(&sTime_f, 0, sizeof(sMcYMDhm_f));

    // �û��ൽ��֡��
    if(MC_TRANS_U2F == eTrans)
    {
        // Pn
        if(pu->usPN > MC_PN_MAX)
        {
            #ifdef MC_DBG
            MCDBG("emc_trans_erc_6() para Pn is out of range! usPN = %d", pu->usPN);
            #endif
            return MC_ERR_OUTRNG;
        }

        pf->usPN = pu->usPN;

        pf->bChange = 0;
        pf->bSt = 0;
        
        for(i = 0; i < 8; i++)
        {
            // bChange
            if(TRUE == pu->bChange[i])
            {
                pf->bChange |= (UINT8)(0x01 << i);
            }

            // bSt
            if(TRUE == pu->bSt[i])
            {
                pf->bSt |= (UINT8)(0x01 << i);
            }
        }

        // sTime
        eRet = emc_trans_YYMMDDhhmm(eTrans, &(pu->sTime), &sTime_f);
        if(MC_OK != eRet)
        {
            #ifdef MC_DBG
            MCDBG("emc_trans_erc_6() emc_trans_YYMMDDhhmm() error %d!", eRet);
            #endif
            return eRet;
        }
        
        pf->sTime = sTime_f;
    }
    // ��֡�ൽ�û���
    else if (MC_TRANS_F2U == eTrans)
    {
        // Pn
        if(pf->usPN > MC_PN_MAX)
        {
            #ifdef MC_DBG
            MCDBG("emc_trans_erc_6() para Pn is out of range! usPN = %d", pf->usPN);
            #endif
            return MC_ERR_OUTRNG;
        }

        pu->usPN = pf->usPN;

        // bChange bSt
        for(i = 0; i < 8; i++)
        {
            if(pf->bChange & (0x01 << i))
            {
                pu->bChange[i] = TRUE;
            }
            else
            {
                pu->bChange[i] = FALSE;
            }

            // bSt
            if(pf->bSt& (0x01 << i))
            {
                pu->bSt[i] = TRUE;
            }
            else
            {
                pu->bSt[i] = FALSE;
            }
        }

        // sTime
        sTime_f = pf->sTime;
        eRet = emc_trans_YYMMDDhhmm(eTrans, &(pu->sTime), &sTime_f);
        if(MC_OK != eRet)
        {
            #ifdef MC_DBG
            MCDBG("emc_trans_erc_6() emc_trans_YYMMDDhhmm() error %d!", eRet);
            #endif
            return eRet;
        }
    }
    else
    {
         #ifdef MC_DBG
         MCDBG("emc_trans_erc_6() eTrans is out of range!");
         #endif
         return MC_ERR_OUTRNG;    
    }

    // �������
    *pusLen = sizeof(sMcErc6_f);
    return MC_OK;
}

/*****************************************************************************
 �� �� ��  : emc_trans_erc_7
 ��������  : �¼���¼����ת������
 ��Ӧ�¼�  : MC_ERC_7_REMOTE_SWITCH
 �������  : eMcTrans eTrans  
             void* pUser      
             void* pFrame     
             UINT16* pusLen   
 �������  : ��
 �� �� ֵ  : 
 ���ú���  : 
 ��������  : 
 
 �޸���ʷ      :
  1.��    ��   : 2013��11��18��
    ��    ��   : liming
    �޸�����   : �����ɺ���

*****************************************************************************/
eMcErr emc_trans_erc_7(eMcTrans eTrans, void* pUser, void* pFrame, UINT16* pusLen)
{
    eMcErr     eRet = MC_OK;
    sMcErc7     *pu = NULL;
    sMcErc7_f   *pf = NULL;
    INT32         i = 0;
    sMcYMDhm_f      sTime_f; 
    sMcFmt06_f     fPower_f; 
    
    if(!pUser || !pFrame || !pusLen)
    {
        #ifdef MC_DBG
        MCDBG("emc_trans_erc_7() para pointer is null!");
        #endif
        return MC_ERR_NULL;
    }

    pu = (sMcErc7*)pUser;
    pf = (sMcErc7_f*)pFrame;
    memset(&sTime_f,  0, sizeof(sMcYMDhm_f));
    memset(&fPower_f, 0, sizeof(sMcFmt06_f));
    
    // �û��ൽ��֡��
    if(MC_TRANS_U2F == eTrans)
    {
        // Pn
        if(pu->usPN > MC_PN_MAX)
        {
            #ifdef MC_DBG
            MCDBG("emc_trans_erc_7() para Pn is out of range! usPN = %d", pu->usPN);
            #endif
            return MC_ERR_OUTRNG;
        }

        pf->usPN = pu->usPN;

        // bCircle
        pf->bCircle = 0;
        for(i = 0; i < 8; i++)
        {
            if(TRUE == pu->bCircle[i])
            {
                pf->bCircle |= (UINT8)(0x01 << i);
            }
        }

        // sTime
        eRet = emc_trans_YYMMDDhhmm(eTrans, &(pu->sTime), &sTime_f);
        if(MC_OK != eRet)
        {
            #ifdef MC_DBG
            MCDBG("emc_trans_erc_7() emc_trans_YYMMDDhhmm() error %d!", eRet);
            #endif
            return eRet;
        }
        
        pf->sTime = sTime_f;

        // fPower
        eRet = emc_trans_sXX_XXXX(eTrans, &(pu->fPower), &fPower_f);
        if(MC_OK != eRet)
        {
            #ifdef MC_DBG
            MCDBG("emc_trans_erc_7() emc_trans_sXX_XXXX() error %d!", eRet);
            #endif
            return eRet;
        }
        
        pf->fPower = fPower_f;
            
        // fPower2
        eRet = emc_trans_sXX_XXXX(eTrans, &(pu->fPower2), &fPower_f);
        if(MC_OK != eRet)
        {
            #ifdef MC_DBG
            MCDBG("emc_trans_erc_7() emc_trans_sXX_XXXX() error %d!", eRet);
            #endif
            return eRet;
        }
        
        pf->fPower2 = fPower_f;
    }
    // ��֡�ൽ�û���
    else if (MC_TRANS_F2U == eTrans)
    {
        // Pn
        if(pf->usPN > MC_PN_MAX)
        {
            #ifdef MC_DBG
            MCDBG("emc_trans_erc_7() para Pn is out of range! usPN = %d", pf->usPN);
            #endif
            return MC_ERR_OUTRNG;
        }

        pu->usPN = pf->usPN;

        // bCircle
        for(i = 0; i < 8; i++)
        {
            if(pf->bCircle & (0x01 << i))
            {
                pu->bCircle[i] = TRUE;
            }
            else
            {
                pu->bCircle[i] = FALSE;
            }
        }
        
        // sTime
        sTime_f = pf->sTime;
        eRet = emc_trans_YYMMDDhhmm(eTrans, &(pu->sTime), &sTime_f);
        if(MC_OK != eRet)
        {
            #ifdef MC_DBG
            MCDBG("emc_trans_erc_7() emc_trans_YYMMDDhhmm() error %d!", eRet);
            #endif
            return eRet;
        }

        // fPower
        fPower_f = pf->fPower;
        eRet = emc_trans_sXX_XXXX(eTrans, &(pu->fPower), &fPower_f);
        if(MC_OK != eRet)
        {
            #ifdef MC_DBG
            MCDBG("emc_trans_erc_7() emc_trans_sXX_XXXX() error %d!", eRet);
            #endif
            return eRet;
        }

        // fPower2
        fPower_f = pf->fPower2;
        eRet = emc_trans_sXX_XXXX(eTrans, &(pu->fPower2), &fPower_f);
        if(MC_OK != eRet)
        {
            #ifdef MC_DBG
            MCDBG("emc_trans_erc_7() emc_trans_sXX_XXXX() error %d!", eRet);
            #endif
            return eRet;
        }
    }
    else
    {
         #ifdef MC_DBG
         MCDBG("emc_trans_erc_7() eTrans is out of range!");
         #endif
         return MC_ERR_OUTRNG;    
    }

    // �������
    *pusLen = sizeof(sMcErc7_f);
    return MC_OK;
}

/*****************************************************************************
 �� �� ��  : emc_trans_erc_8
 ��������  : �¼���¼����ת������
 ��Ӧ�¼�  : MC_ERC_8_POWER_ON_OFF
 �������  : eMcTrans eTrans  
             void* pUser      
             void* pFrame     
             UINT16* pusLen   
 �������  : ��
 �� �� ֵ  : 
 ���ú���  : 
 ��������  : 
 
 �޸���ʷ      :
  1.��    ��   : 2013��11��18��
    ��    ��   : liming
    �޸�����   : �����ɺ���

*****************************************************************************/
eMcErr emc_trans_erc_8(eMcTrans eTrans, void* pUser, void* pFrame, UINT16* pusLen)
{
    eMcErr     eRet = MC_OK;
    sMcErc8     *pu = NULL;
    sMcErc8_f   *pf = NULL;
    UINT16     usPn = 0;
    sMcYMDhm_f   sTime_f;

    if(!pUser || !pFrame || !pusLen)
    {
        #ifdef MC_DBG
        MCDBG("emc_trans_erc_8() para pointer is null!");
        #endif
        return MC_ERR_NULL;
    }

    pu = (sMcErc8*)pUser;
    pf = (sMcErc8_f*)pFrame;
    memset(&sTime_f, 0, sizeof(sMcYMDhm_f));

    // �û��ൽ��֡��
    if(MC_TRANS_U2F == eTrans)
    {
        // Pn
        if(pu->usPN > MC_PN_MAX)
        {
            #ifdef MC_DBG
            MCDBG("emc_trans_erc_8() para Pn is out of range! usPN = %d", pu->usPN);
            #endif
            return MC_ERR_OUTRNG;
        }
        
        usPn = pu->usPN;

        if(pu->bStart == TRUE)
        {
            usPn |= 0x8000;
        }
        
        pf->usPN = usPn;

        // sTime
        eRet = emc_trans_YYMMDDhhmm(eTrans, &(pu->sTime), &sTime_f);
        if(MC_OK != eRet)
        {
            #ifdef MC_DBG
            MCDBG("emc_trans_erc_8() emc_trans_YYMMDDhhmm() error %d!", eRet);
            #endif
            return eRet;
        }

        pf->sTime = sTime_f;
    }
    // ��֡�ൽ�û���
    else if (MC_TRANS_F2U == eTrans)
    {
        // Pn
        usPn = pf->usPN & 0x7FFF;
        if(usPn > MC_PN_MAX)
        {
            #ifdef MC_DBG
            MCDBG("emc_trans_erc_8() para Pn is out of range! usPN = %d", pf->usPN);
            #endif
            return MC_ERR_OUTRNG;
        }

        pu->usPN = usPn;

        if(pf->usPN & 0x8000)
        {
            pu->bStart = TRUE;
        }
        else
        {
            pu->bStart = FALSE;
        }

        // sTime
        sTime_f = pf->sTime;
        eRet = emc_trans_YYMMDDhhmm(eTrans, &(pu->sTime), &sTime_f);
        if(MC_OK != eRet)
        {
            #ifdef MC_DBG
            MCDBG("emc_trans_erc_8() emc_trans_YYMMDDhhmm() error %d!", eRet);
            #endif
            return eRet;
        }
    }
    else
    {
         #ifdef MC_DBG
         MCDBG("emc_trans_erc_8() eTrans is out of range!");
         #endif
         return MC_ERR_OUTRNG;    
    }

    // �������
    *pusLen = sizeof(sMcErc8_f);
    return MC_OK;
}

/*****************************************************************************
 �� �� ��  : emc_trans_erc_9
 ��������  : �¼���¼����ת������
 ��Ӧ�¼�  : MC_ERC_9_FACTOR_OVER
 �������  : eMcTrans eTrans  
             void* pUser      
             void* pFrame     
             UINT16* pusLen   
 �������  : ��
 �� �� ֵ  : 
 ���ú���  : 
 ��������  : 
 
 �޸���ʷ      :
  1.��    ��   : 2013��11��18��
    ��    ��   : liming
    �޸�����   : �����ɺ���

*****************************************************************************/
eMcErr emc_trans_erc_9(eMcTrans eTrans, void* pUser, void* pFrame, UINT16* pusLen)
{
    eMcErr     eRet = MC_OK;
    sMcErc9     *pu = NULL;
    sMcErc9_f   *pf = NULL;
    sMcYMDhm_f   sTime_f;
    sMcFmt10_f   sFmt10_f;

    if(!pUser || !pFrame || !pusLen)
    {
        #ifdef MC_DBG
        MCDBG("emc_trans_erc_9() para pointer is null!");
        #endif
        return MC_ERR_NULL;
    }

    pu = (sMcErc9*)pUser;
    pf = (sMcErc9_f*)pFrame;
    memset(&sTime_f,  0, sizeof(sMcYMDhm_f));
    memset(&sFmt10_f, 0, sizeof(sMcFmt10_f));
    
    // �û��ൽ��֡��
    if(MC_TRANS_U2F == eTrans)
    {
        // Pn
        if(pu->usPN > MC_PN_MAX)
        {
            #ifdef MC_DBG
            MCDBG("emc_trans_erc_9() para Pn is out of range! usPN = %d", pu->usPN);
            #endif
            return MC_ERR_OUTRNG;
        }

        pf->usPN = pu->usPN;

        // sTime
        eRet = emc_trans_YYMMDDhhmm(eTrans, &(pu->sTime), &sTime_f);
        if(MC_OK != eRet)
        {
            #ifdef MC_DBG
            MCDBG("emc_trans_erc_9() emc_trans_YYMMDDhhmm() error %d!", eRet);
            #endif
            return eRet;
        }
        
        pf->sTime = sTime_f;
        
        // fOccur
        eRet = emc_trans_XX_XX(eTrans, &(pu->fOccur), &sFmt10_f);
        if(MC_OK != eRet)
        {
            #ifdef MC_DBG
            MCDBG("emc_trans_erc_9() emc_trans_XX_XX() error %d!", eRet);
            #endif
            return eRet;
        }
        
        pf->fOccur = sFmt10_f;
        
        // fLimit
        eRet = emc_trans_XX_XX(eTrans, &(pu->fLimit), &sFmt10_f);
        if(MC_OK != eRet)
        {
            #ifdef MC_DBG
            MCDBG("emc_trans_erc_9() emc_trans_XX_XX() error %d!", eRet);
            #endif
            return eRet;
        }  
        
        pf->fLimit = sFmt10_f; 
    }
    // ��֡�ൽ�û���
    else if (MC_TRANS_F2U == eTrans)
    {
        // Pn
        if(pf->usPN > MC_PN_MAX)
        {
            #ifdef MC_DBG
            MCDBG("emc_trans_erc_9() para Pn is out of range! usPN = %d", pf->usPN);
            #endif
            return MC_ERR_OUTRNG;
        }

        pu->usPN = pf->usPN;

        // sTime
        sTime_f = pf->sTime;
        eRet = emc_trans_YYMMDDhhmm(eTrans, &(pu->sTime), &sTime_f);
        if(MC_OK != eRet)
        {
            #ifdef MC_DBG
            MCDBG("emc_trans_erc_9() emc_trans_YYMMDDhhmm() error %d!", eRet);
            #endif
            return eRet;
        }

        // fOccur
        sFmt10_f = pf->fOccur;
        eRet = emc_trans_XX_XX(eTrans, &(pu->fOccur), &sFmt10_f);
        if(MC_OK != eRet)
        {
            #ifdef MC_DBG
            MCDBG("emc_trans_erc_9() emc_trans_XX_XX() error %d!", eRet);
            #endif
            return eRet;
        }
        
        // fLimit
        sFmt10_f = pf->fLimit;
        eRet = emc_trans_XX_XX(eTrans, &(pu->fLimit), &sFmt10_f);
        if(MC_OK != eRet)
        {
            #ifdef MC_DBG
            MCDBG("emc_trans_erc_9() emc_trans_XX_XX() error %d!", eRet);
            #endif
            return eRet;
        }   
    }
    else
    {
         #ifdef MC_DBG
         MCDBG("emc_trans_erc_9() eTrans is out of range!");
         #endif
         return MC_ERR_OUTRNG;    
    }

    // �������
    *pusLen = sizeof(sMcErc8_f);
    return MC_OK;
}

/*****************************************************************************
 �� �� ��  : emc_trans_erc_10
 ��������  : �¼���¼����ת������
 ��Ӧ�¼�  : MC_ERC_10_VOLT_EXCP
 �������  : eMcTrans eTrans  
             void* pUser      
             void* pFrame     
             UINT16* pusLen   
 �������  : ��
 �� �� ֵ  : 
 ���ú���  : 
 ��������  : 
 
 �޸���ʷ      :
  1.��    ��   : 2013��11��20��
    ��    ��   : liming
    �޸�����   : �����ɺ���

*****************************************************************************/
eMcErr emc_trans_erc_10(eMcTrans eTrans, void* pUser, void* pFrame, UINT16* pusLen)
{
    eMcErr     eRet = MC_OK;
    sMcErc10     *pu = NULL;
    sMcErc10_f   *pf = NULL;
    UINT8      ucTmp = 9;
    sMcYMDhm_f   sTime_f;
    sMcFmt_XXX_X  fU_f;
        
    if(!pUser || !pFrame || !pusLen)
    {
        #ifdef MC_DBG
        MCDBG("emc_trans_erc_10() para pointer is null!");
        #endif
        return MC_ERR_NULL;
    }

    pu = (sMcErc10*)pUser;
    pf = (sMcErc10_f*)pFrame;
    memset(&sTime_f,  0, sizeof(sMcYMDhm_f));
    memset(&fU_f,  0, sizeof(sMcFmt_XXX_X));
    
    // �û��ൽ��֡��
    if(MC_TRANS_U2F == eTrans)
    {
        // Pn
        if(pu->usPN > MC_PN_MAX)
        {
            #ifdef MC_DBG
            MCDBG("emc_trans_erc_10() para Pn is out of range! usPN = %d", pu->usPN);
            #endif
            return MC_ERR_OUTRNG;
        }

        pf->usPN = pu->usPN;

        // bPhaseA
        pf->ucExcp = 0;
        if(pu->bPhaseA == TRUE)
        {
            pf->ucExcp |= 0x01;
        }

        // bPhaseB
        if(pu->bPhaseB == TRUE)
        {
            pf->ucExcp |= 0x02;
        }
       
        // bPhaseC
        if(pu->bPhaseC == TRUE)
        {
            pf->ucExcp |= 0x04;
        }

        // bOverUpUp
        if(pu->bOverUpUp == TRUE)
        {
            pf->ucExcp |= 0x20;;
        }
        else 
        {
            pf->ucExcp |= 0x40;;
        }

        // sTime
        eRet = emc_trans_YYMMDDhhmm(eTrans, &(pu->sTime), &sTime_f);
        if(MC_OK != eRet)
        {
            #ifdef MC_DBG
            MCDBG("emc_trans_erc_9() emc_trans_YYMMDDhhmm() error %d!", eRet);
            #endif
            return eRet;
        }

        pf->sTime = sTime_f;

        // fUa
        eRet = emc_trans_XXX_X(eTrans, &(pu->fUa), &fU_f);
        if(MC_OK != eRet)
        {
            #ifdef MC_DBG
            MCDBG("emc_trans_erc_10() emc_trans_XX_XX() error %d!", eRet);
            #endif
            return eRet;
        }

        pf->fUa = fU_f;

        // fUb
        eRet = emc_trans_XXX_X(eTrans, &(pu->fUb), &fU_f);
        if(MC_OK != eRet)
        {
            #ifdef MC_DBG
            MCDBG("emc_trans_erc_10() emc_trans_XX_XX() error %d!", eRet);
            #endif
            return eRet;
        } 
        
        pf->fUb = fU_f;
        
        // fUc
        eRet = emc_trans_XXX_X(eTrans, &(pu->fUc), &fU_f);
        if(MC_OK != eRet)
        {
            #ifdef MC_DBG
            MCDBG("emc_trans_erc_10() emc_trans_XX_XX() error %d!", eRet);
            #endif
            return eRet;
        } 

        pf->fUc = fU_f;  
    }
    // ��֡�ൽ�û���
    else if (MC_TRANS_F2U == eTrans)
    {
        // Pn
        if(pf->usPN > MC_PN_MAX)
        {
            #ifdef MC_DBG
            MCDBG("emc_trans_erc_10() para Pn is out of range! usPN = %d", pf->usPN);
            #endif
            return MC_ERR_OUTRNG;
        }

        pu->usPN = pf->usPN;

        // bPhaseA
        if(pf->ucExcp & 0x01)
        {
            pu->bPhaseA = TRUE;
        }
        else
        {
            pu->bPhaseA = FALSE;
        }

        // bPhaseB
        if(pf->ucExcp & 0x02)
        {
            pu->bPhaseB = TRUE;
        }
        else
        {
            pu->bPhaseB = FALSE;
        }

        // bPhaseC
        if(pf->ucExcp & 0x04)
        {
            pu->bPhaseC = TRUE;
        }
        else
        {
            pu->bPhaseC = FALSE;
        }

        // bOverUpUp
        ucTmp = (pf->ucExcp & 0x60) >> 5;
        if(1 == ucTmp)
        {
            pu->bOverUpUp = TRUE;
        }
        else if(2 == ucTmp)
        {
            pu->bOverUpUp = FALSE;
        }
        else
        {
            #ifdef MC_DBG
            MCDBG("emc_trans_erc_10() para error ucTmp = %d", ucTmp);
            #endif
            return MC_ERR_OUTRNG;
        }

        // sTime
        sTime_f = pf->sTime;
        eRet = emc_trans_YYMMDDhhmm(eTrans, &(pu->sTime), &sTime_f);
        if(MC_OK != eRet)
        {
            #ifdef MC_DBG
            MCDBG("emc_trans_erc_9() emc_trans_YYMMDDhhmm() error %d!", eRet);
            #endif
            return eRet;
        }

        // fUa
        fU_f = pf->fUa;
        eRet = emc_trans_XXX_X(eTrans, &(pu->fUa), &fU_f);
        if(MC_OK != eRet)
        {
            #ifdef MC_DBG
            MCDBG("emc_trans_erc_10() emc_trans_XX_XX() error %d!", eRet);
            #endif
            return eRet;
        }
        
        // fUb        
        fU_f = pf->fUb;
        eRet = emc_trans_XXX_X(eTrans, &(pu->fUb), &fU_f);
        if(MC_OK != eRet)
        {
            #ifdef MC_DBG
            MCDBG("emc_trans_erc_10() emc_trans_XX_XX() error %d!", eRet);
            #endif
            return eRet;
        }   
        
        // fUc
        fU_f = pf->fUc;
        eRet = emc_trans_XXX_X(eTrans, &(pu->fUc), &fU_f);
        if(MC_OK != eRet)
        {
            #ifdef MC_DBG
            MCDBG("emc_trans_erc_10() emc_trans_XX_XX() error %d!", eRet);
            #endif
            return eRet;
        }   
    }
    else
    {
         #ifdef MC_DBG
         MCDBG("emc_trans_erc_10() eTrans is out of range!");
         #endif
         return MC_ERR_OUTRNG;    
    }

    // �������
    *pusLen = sizeof(sMcErc10_f);
    return MC_OK;
}

/*****************************************************************************
 �� �� ��  : emc_trans_erc_11
 ��������  : �¼���¼����ת������
 ��Ӧ�¼�  : MC_ERC_11_VOLT_CIRCLE
 �������  : eMcTrans eTrans  
             void* pUser      
             void* pFrame     
             UINT16* pusLen   
 �������  : ��
 �� �� ֵ  : 
 ���ú���  : 
 ��������  : 
 
 �޸���ʷ      :
  1.��    ��   : 2013��11��20��
    ��    ��   : liming
    �޸�����   : �����ɺ���

*****************************************************************************/
eMcErr emc_trans_erc_11(eMcTrans eTrans, void* pUser, void* pFrame, UINT16* pusLen)
{
    eMcErr     eRet = MC_OK;
    sMcErc11     *pu = NULL;
    sMcErc11_f   *pf = NULL;
    UINT8      ucTmp = 9;
    UINT16      usPn = 0;
    sMcYMDhm_f  sYMDhm_f;
    sMcFmt08_f  sFmt08_f;
    sMcFmt09_f  sFmt09_f;
    
    if(!pUser || !pFrame || !pusLen)
    {
        #ifdef MC_DBG
        MCDBG("emc_trans_erc_11() para pointer is null!");
        #endif
        return MC_ERR_NULL;
    }

    pu = (sMcErc11*)pUser;
    pf = (sMcErc11_f*)pFrame;
    memset(&sYMDhm_f, 0, sizeof(sMcYMDhm_f));
    memset(&sFmt08_f, 0, sizeof(sMcFmt08_f));
    memset(&sFmt09_f, 0, sizeof(sMcFmt09_f));
    
    // �û��ൽ��֡��
    if(MC_TRANS_U2F == eTrans)
    {
        // Pn
        if(pu->usPN > MC_PN_MAX)
        {
            #ifdef MC_DBG
            MCDBG("emc_trans_erc_11() para Pn is out of range! usPN = %d", pu->usPN);
            #endif
            return MC_ERR_OUTRNG;
        }

        usPn = pu->usPN;
        
        if(pu->bStart == TRUE)
        {
            usPn |= 0x8000;
        }
        
        pf->usPN = usPn;

        // bPhaseA
        pf->ucExcp = 0;
        if(pu->bPhaseA == TRUE)
        {
            pf->ucExcp |= 0x01;
        }

        // bPhaseB
        if(pu->bPhaseB == TRUE)
        {
            pf->ucExcp |= 0x02;
        }
       
        // bPhaseC
        if(pu->bPhaseC == TRUE)
        {
            pf->ucExcp |= 0x04;
        }

        // excptype
        switch(pu->eExcp)
        {
            case MC_VOLT_CIRCLE_DROP:
                ucTmp = 1;
                break;
                
            case MC_VOLT_CIRCLE_LOSS:
                ucTmp = 2;
                break;
                
            default:
                ucTmp = 0;
                break;
        }

        pf->ucExcp |= (ucTmp << 6);

        // sTime
        eRet = emc_trans_YYMMDDhhmm(eTrans, &(pu->sTime), &sYMDhm_f);
        if(MC_OK != eRet)
        {
            #ifdef MC_DBG
            MCDBG("emc_trans_erc_11() emc_trans_YYMMDDhhmm() error %d!", eRet);
            #endif
            return eRet;
        }

        pf->sTime = sYMDhm_f;
        
        // fUa
        eRet = emc_trans_XXX_X(eTrans, &(pu->fUa), &sFmt08_f);
        if(MC_OK != eRet)
        {
            #ifdef MC_DBG
            MCDBG("emc_trans_erc_11() emc_trans_XX_XX() error %d!", eRet);
            #endif
            return eRet;
        }
        
        pf->fUa = sFmt08_f;
        
        // fUb
        eRet = emc_trans_XXX_X(eTrans, &(pu->fUb), &sFmt08_f);
        if(MC_OK != eRet)
        {
            #ifdef MC_DBG
            MCDBG("emc_trans_erc_11() emc_trans_XX_XX() error %d!", eRet);
            #endif
            return eRet;
        }   
        
        pf->fUb = sFmt08_f;
            
        // fUc
        eRet = emc_trans_XXX_X(eTrans, &(pu->fUc), &sFmt08_f);
        if(MC_OK != eRet)
        {
            #ifdef MC_DBG
            MCDBG("emc_trans_erc_11() emc_trans_XX_XX() error %d!", eRet);
            #endif
            return eRet;
        }  
        
        pf->fUc = sFmt08_f;
        
        // fIa
        eRet = emc_trans_sXXX_XXX(eTrans, &(pu->fIa), &sFmt09_f);
        if(MC_OK != eRet)
        {
            #ifdef MC_DBG
            MCDBG("emc_trans_erc_11() emc_trans_sXXX_XXX() error %d!", eRet);
            #endif
            return eRet;
        }
        
        pf->fIa = sFmt09_f;
        
        // fIb
        eRet = emc_trans_sXXX_XXX(eTrans, &(pu->fIb), &sFmt09_f);
        if(MC_OK != eRet)
        {
            #ifdef MC_DBG
            MCDBG("emc_trans_erc_11() emc_trans_sXXX_XXX() error %d!", eRet);
            #endif
            return eRet;
        }
        
        pf->fIb = sFmt09_f;

        // fIc
        eRet = emc_trans_sXXX_XXX(eTrans, &(pu->fIc), &sFmt09_f);
        if(MC_OK != eRet)
        {
            #ifdef MC_DBG
            MCDBG("emc_trans_erc_11() emc_trans_sXXX_XXX() error %d!", eRet);
            #endif
            return eRet;
        }
        
        pf->fIc = sFmt09_f;

    }
    // ��֡�ൽ�û���
    else if (MC_TRANS_F2U == eTrans)
    {
        // Pn
        usPn = pf->usPN & 0x7FFF;
        if(usPn > MC_PN_MAX)
        {
            #ifdef MC_DBG
            MCDBG("emc_trans_erc_11() para Pn is out of range! usPN = %d", pf->usPN);
            #endif
            return MC_ERR_OUTRNG;
        }

        pu->usPN = usPn;

        if(pf->usPN & 0x8000)
        {
            pu->bStart = TRUE;
        }
        else
        {
            pu->bStart = FALSE;
        }
        
        // bPhaseA
        if(pf->ucExcp & 0x01)
        {
            pu->bPhaseA = TRUE;
        }
        else
        {
            pu->bPhaseA = FALSE;
        }

        // bPhaseB
        if(pf->ucExcp & 0x02)
        {
            pu->bPhaseB = TRUE;
        }
        else
        {
            pu->bPhaseB = FALSE;
        }

        // bPhaseC
        if(pf->ucExcp & 0x04)
        {
            pu->bPhaseC = TRUE;
        }
        else
        {
            pu->bPhaseC = FALSE;
        }

        // excptype
        ucTmp = (pf->ucExcp >> 6);
        if(ucTmp == 1)
        {
            pu->eExcp = MC_VOLT_CIRCLE_DROP;
        }
        else if(ucTmp == 2)
        {
            pu->eExcp = MC_VOLT_CIRCLE_LOSS;
        }
        else
        {
            #ifdef MC_DBG
            MCDBG("emc_trans_erc_11() para error ucExcp = %d", ucTmp);
            #endif
            pu->eExcp = MC_VOLT_CIRCLE_UNKOWN;
            //return MC_ERR_OUTRNG;
        }

        // sTime
        sYMDhm_f = pf->sTime;
        eRet = emc_trans_YYMMDDhhmm(eTrans, &(pu->sTime), &sYMDhm_f);
        if(MC_OK != eRet)
        {
            #ifdef MC_DBG
            MCDBG("emc_trans_erc_11() emc_trans_YYMMDDhhmm() error %d!", eRet);
            #endif
            return eRet;
        }

        // fUa
        sFmt08_f = pf->fUa;
        eRet = emc_trans_XXX_X(eTrans, &(pu->fUa), &sFmt08_f);
        if(MC_OK != eRet)
        {
            #ifdef MC_DBG
            MCDBG("emc_trans_erc_11() emc_trans_XX_XX() error %d!", eRet);
            #endif
            return eRet;
        }
        
        // fUb
        sFmt08_f = pf->fUb;
        eRet = emc_trans_XXX_X(eTrans, &(pu->fUb), &sFmt08_f);
        if(MC_OK != eRet)
        {
            #ifdef MC_DBG
            MCDBG("emc_trans_erc_11() emc_trans_XX_XX() error %d!", eRet);
            #endif
            return eRet;
        }   
        
        // fUc
        sFmt08_f = pf->fUc;
        eRet = emc_trans_XXX_X(eTrans, &(pu->fUc), &sFmt08_f);
        if(MC_OK != eRet)
        {
            #ifdef MC_DBG
            MCDBG("emc_trans_erc_11() emc_trans_XX_XX() error %d!", eRet);
            #endif
            return eRet;
        }   

        // fIa
        sFmt09_f = pf->fIa;
        eRet = emc_trans_sXXX_XXX(eTrans, &(pu->fIa), &sFmt09_f);
        if(MC_OK != eRet)
        {
            #ifdef MC_DBG
            MCDBG("emc_trans_erc_11() emc_trans_sXXX_XXX() error %d!", eRet);
            #endif
            return eRet;
        }

        // fIb
        sFmt09_f = pf->fIb;
        eRet = emc_trans_sXXX_XXX(eTrans, &(pu->fIb), &sFmt09_f);
        if(MC_OK != eRet)
        {
            #ifdef MC_DBG
            MCDBG("emc_trans_erc_11() emc_trans_sXXX_XXX() error %d!", eRet);
            #endif
            return eRet;
        }

        // fIc
        sFmt09_f = pf->fIc;
        eRet = emc_trans_sXXX_XXX(eTrans, &(pu->fIc), &sFmt09_f);
        if(MC_OK != eRet)
        {
            #ifdef MC_DBG
            MCDBG("emc_trans_erc_11() emc_trans_sXXX_XXX() error %d!", eRet);
            #endif
            return eRet;
        }
    }
    else
    {
         #ifdef MC_DBG
         MCDBG("emc_trans_erc_11() eTrans is out of range!");
         #endif
         return MC_ERR_OUTRNG;    
    }

    // �������
    *pusLen = sizeof(sMcErc11_f);
    return MC_OK;
}

/*****************************************************************************
 �� �� ��  : emc_trans_erc_12
 ��������  : �¼���¼����ת������
 ��Ӧ�¼�  : MC_ERC_12_ELEC_CRICLE
 �������  : eMcTrans eTrans  
             void* pUser      
             void* pFrame     
             UINT16* pusLen   
 �������  : ��
 �� �� ֵ  : 
 ���ú���  : 
 ��������  : 
 
 �޸���ʷ      :
  1.��    ��   : 2013��11��20��
    ��    ��   : liming
    �޸�����   : �����ɺ���

*****************************************************************************/
eMcErr emc_trans_erc_12(eMcTrans eTrans, void* pUser, void* pFrame, UINT16* pusLen)
{
    eMcErr     eRet = MC_OK;
    sMcErc12     *pu = NULL;
    sMcErc12_f   *pf = NULL;
    UINT8      ucTmp = 9;
    UINT16      usPn = 0;
    sMcYMDhm_f  sYMDhm_f;
    sMcFmt08_f  sfU_f;
    sMcFmt09_f  sfI_f;
    
    if(!pUser || !pFrame || !pusLen)
    {
        #ifdef MC_DBG
        MCDBG("emc_trans_erc_12() para pointer is null!");
        #endif
        return MC_ERR_NULL;
    }

    pu = (sMcErc12*)pUser;
    pf = (sMcErc12_f*)pFrame;
    memset(&sYMDhm_f, 0, sizeof(sMcYMDhm_f));
    memset(&sfU_f,    0, sizeof(sMcFmt08_f));
    memset(&sfI_f,    0, sizeof(sMcFmt09_f));
    
    // �û��ൽ��֡��
    if(MC_TRANS_U2F == eTrans)
    {
        // Pn
        if(pu->usPN > MC_PN_MAX)
        {
            #ifdef MC_DBG
            MCDBG("emc_trans_erc_12() para Pn is out of range! usPN = %d", pu->usPN);
            #endif
            return MC_ERR_OUTRNG;
        }
        
        usPn = pu->usPN;
        
        if(pu->bStart == TRUE)
        {
            usPn |= 0x8000;
        }
        
        pf->usPN = usPn;

        // bPhaseA
        pf->ucExcp = 0;
        if(pu->bPhaseA == TRUE)
        {
            pf->ucExcp |= 0x01;
        }

        // bPhaseB
        if(pu->bPhaseB == TRUE)
        {
            pf->ucExcp |= 0x02;
        }
       
        // bPhaseC
        if(pu->bPhaseC == TRUE)
        {
            pf->ucExcp |= 0x04;
        }

        // excptype
        switch(pu->eExcp)
        {
            case MC_ELEC_EXCP_SHORT:
                ucTmp = 1;
                break;
                
            case MC_ELEC_EXCP_CARVE:
                ucTmp = 2;
                break;         

            case MC_ELEC_EXCP_BACK:
                ucTmp = 3;
                break;
                
            default:
                ucTmp = 0;
                break;
        }

        pf->ucExcp |= (ucTmp << 6);

        // sTime
        eRet = emc_trans_YYMMDDhhmm(eTrans, &(pu->sTime), &sYMDhm_f);
        if(MC_OK != eRet)
        {
            #ifdef MC_DBG
            MCDBG("emc_trans_erc_12() emc_trans_YYMMDDhhmm() error %d!", eRet);
            #endif
            return eRet;
        }

        pf->sTime = sYMDhm_f;

        // fUa
        eRet = emc_trans_XXX_X(eTrans, &(pu->fUa), &sfU_f);
        if(MC_OK != eRet)
        {
            #ifdef MC_DBG
            MCDBG("emc_trans_erc_12() emc_trans_XX_XX() error %d!", eRet);
            #endif
            return eRet;
        }

        pf->fUa = sfU_f;
        
        // fUb
        eRet = emc_trans_XXX_X(eTrans, &(pu->fUb), &sfU_f);
        if(MC_OK != eRet)
        {
            #ifdef MC_DBG
            MCDBG("emc_trans_erc_12() emc_trans_XX_XX() error %d!", eRet);
            #endif
            return eRet;
        } 
        
        pf->fUb = sfU_f;
        
        // fUc
        eRet = emc_trans_XXX_X(eTrans, &(pu->fUc), &sfU_f);
        if(MC_OK != eRet)
        {
            #ifdef MC_DBG
            MCDBG("emc_trans_erc_12() emc_trans_XX_XX() error %d!", eRet);
            #endif
            return eRet;
        }   

        pf->fUc = sfU_f;
        
        // fIa
        eRet = emc_trans_sXXX_XXX(eTrans, &(pu->fIa), &sfI_f);
        if(MC_OK != eRet)
        {
            #ifdef MC_DBG
            MCDBG("emc_trans_erc_12() emc_trans_sXXX_XXX() error %d!", eRet);
            #endif
            return eRet;
        }
        
        pf->fIa = sfI_f;
        
        // fIb
        eRet = emc_trans_sXXX_XXX(eTrans, &(pu->fIb), &sfI_f);
        if(MC_OK != eRet)
        {
            #ifdef MC_DBG
            MCDBG("emc_trans_erc_12() emc_trans_sXXX_XXX() error %d!", eRet);
            #endif
            return eRet;
        }
        
        pf->fIb = sfI_f;
        
        // fIc
        eRet = emc_trans_sXXX_XXX(eTrans, &(pu->fIc), &sfI_f);
        if(MC_OK != eRet)
        {
            #ifdef MC_DBG
            MCDBG("emc_trans_erc_12() emc_trans_sXXX_XXX() error %d!", eRet);
            #endif
            return eRet;
        }
        
        pf->fIc = sfI_f;
    }
    // ��֡�ൽ�û���
    else if (MC_TRANS_F2U == eTrans)
    {
        // Pn
        usPn = pf->usPN & 0x7FFF;
        if(usPn > MC_PN_MAX)
        {
            #ifdef MC_DBG
            MCDBG("emc_trans_erc_12() para Pn is out of range! usPN = %d", pf->usPN);
            #endif
            return MC_ERR_OUTRNG;
        }

        pu->usPN = usPn;

        // bStart
        if(pf->usPN & 0x8000)
        {
            pu->bStart = TRUE;
        }
        else
        {
            pu->bStart = FALSE;
        }

        // bPhaseA
        if(pf->ucExcp & 0x01)
        {
            pu->bPhaseA = TRUE;
        }
        else
        {
            pu->bPhaseA = FALSE;
        }

        // bPhaseB
        if(pf->ucExcp & 0x02)
        {
            pu->bPhaseB = TRUE;
        }
        else
        {
            pu->bPhaseB = FALSE;
        }

        // bPhaseC
        if(pf->ucExcp & 0x04)
        {
            pu->bPhaseC = TRUE;
        }
        else
        {
            pu->bPhaseC = FALSE;
        }

        // excptype
        ucTmp = (pf->ucExcp >> 6);
        if(ucTmp == 1)
        {
            pu->eExcp = MC_ELEC_EXCP_SHORT;
        }
        else if(ucTmp == 2)
        {
            pu->eExcp = MC_ELEC_EXCP_CARVE;
        }
        else if(ucTmp == 3)
        {
            pu->eExcp = MC_ELEC_EXCP_BACK;
        }
        else
        {
            #ifdef MC_DBG
            MCDBG("emc_trans_erc_12() para error ucExcp = %d", ucTmp);
            #endif
            pu->eExcp = MC_ELEC_EXCP_UNKOWN;
            //return MC_ERR_OUTRNG;
        }

        // sTime
        sYMDhm_f = pf->sTime;
        eRet = emc_trans_YYMMDDhhmm(eTrans, &(pu->sTime), &sYMDhm_f);
        if(MC_OK != eRet)
        {
            #ifdef MC_DBG
            MCDBG("emc_trans_erc_12() emc_trans_YYMMDDhhmm() error %d!", eRet);
            #endif
            return eRet;
        }

        // fUa
        sfU_f = pf->fUa;
        eRet = emc_trans_XXX_X(eTrans, &(pu->fUa), &sfU_f);
        if(MC_OK != eRet)
        {
            #ifdef MC_DBG
            MCDBG("emc_trans_erc_12() emc_trans_XX_XX() error %d!", eRet);
            #endif
            return eRet;
        }
        
        // fUb
        sfU_f = pf->fUb;
        eRet = emc_trans_XXX_X(eTrans, &(pu->fUb), &sfU_f);
        if(MC_OK != eRet)
        {
            #ifdef MC_DBG
            MCDBG("emc_trans_erc_12() emc_trans_XX_XX() error %d!", eRet);
            #endif
            return eRet;
        }   
        
        // fUc
        sfU_f = pf->fUc;
        eRet = emc_trans_XXX_X(eTrans, &(pu->fUc), &sfU_f);
        if(MC_OK != eRet)
        {
            #ifdef MC_DBG
            MCDBG("emc_trans_erc_12() emc_trans_XX_XX() error %d!", eRet);
            #endif
            return eRet;
        }   

        // fIa
        sfI_f = pf->fIa;
        eRet = emc_trans_sXXX_XXX(eTrans, &(pu->fIa), &sfI_f);
        if(MC_OK != eRet)
        {
            #ifdef MC_DBG
            MCDBG("emc_trans_erc_12() emc_trans_sXXX_XXX() error %d!", eRet);
            #endif
            return eRet;
        }

        // fIb
        sfI_f = pf->fIb;
        eRet = emc_trans_sXXX_XXX(eTrans, &(pu->fIb), &sfI_f);
        if(MC_OK != eRet)
        {
            #ifdef MC_DBG
            MCDBG("emc_trans_erc_12() emc_trans_sXXX_XXX() error %d!", eRet);
            #endif
            return eRet;
        }

        // fIc
        sfI_f = pf->fIc;
        eRet = emc_trans_sXXX_XXX(eTrans, &(pu->fIc), &sfI_f);
        if(MC_OK != eRet)
        {
            #ifdef MC_DBG
            MCDBG("emc_trans_erc_12() emc_trans_sXXX_XXX() error %d!", eRet);
            #endif
            return eRet;
        }
    }
    else
    {
         #ifdef MC_DBG
         MCDBG("emc_trans_erc_12() eTrans is out of range!");
         #endif
         return MC_ERR_OUTRNG;    
    }

    // �������
    *pusLen = sizeof(sMcErc12_f);
    return MC_OK;
}

/*****************************************************************************
 �� �� ��  : emc_trans_erc_13
 ��������  : �¼���¼����ת������
 ��Ӧ�¼�  : MC_ERC_13_VOLT_OVER
 �������  : eMcTrans eTrans  
             void* pUser      
             void* pFrame     
             UINT16* pusLen   
 �������  : ��
 �� �� ֵ  : 
 ���ú���  : 
 ��������  : 
 
 �޸���ʷ      :
  1.��    ��   : 2013��11��20��
    ��    ��   : liming
    �޸�����   : �����ɺ���

*****************************************************************************/
eMcErr emc_trans_erc_13(eMcTrans eTrans, void* pUser, void* pFrame, UINT16* pusLen)
{
    eMcErr     eRet = MC_OK;
    sMcErc13     *pu = NULL;
    sMcErc13_f   *pf = NULL;
    UINT8      ucTmp = 9;
    UINT16      usPn = 0;
    sMcYMDhm_f  sYMDhm_f;
    sMcFmt08_f  sfU_f;

    if(!pUser || !pFrame || !pusLen)
    {
        #ifdef MC_DBG
        MCDBG("emc_trans_erc_13() para pointer is null!");
        #endif
        return MC_ERR_NULL;
    }

    pu = (sMcErc13*)pUser;
    pf = (sMcErc13_f*)pFrame;
    memset(&sYMDhm_f, 0, sizeof(sMcYMDhm_f));
    memset(&sfU_f,    0, sizeof(sMcFmt08_f));
    
    // �û��ൽ��֡��
    if(MC_TRANS_U2F == eTrans)
    {
        // Pn
        if(pu->usPN > MC_PN_MAX)
        {
            #ifdef MC_DBG
            MCDBG("emc_trans_erc_13() para Pn is out of range! usPN = %d", pu->usPN);
            #endif
            return MC_ERR_OUTRNG;
        }
        
        usPn = pu->usPN;
        
        if(pu->bStart == TRUE)
        {
            usPn |= 0x8000;
        }
        
        pf->usPN = usPn;

        // bPhaseA
        pf->ucExcp = 0;
        if(pu->bPhaseA == TRUE)
        {
            pf->ucExcp |= 0x01;
        }

        // bPhaseB
        if(pu->bPhaseB == TRUE)
        {
            pf->ucExcp |= 0x02;
        }
       
        // bPhaseC
        if(pu->bPhaseC == TRUE)
        {
            pf->ucExcp |= 0x04;
        }

        // bOverUpUp
        if(pu->bOverUpUp == TRUE)
        {
            pf->ucExcp |= 0x20;;
        }
        else 
        {
            pf->ucExcp |= 0x40;;
        }

         // sTime
        eRet = emc_trans_YYMMDDhhmm(eTrans, &(pu->sTime), &sYMDhm_f);
        if(MC_OK != eRet)
        {
            #ifdef MC_DBG
            MCDBG("emc_trans_erc_13() emc_trans_YYMMDDhhmm() error %d!", eRet);
            #endif
            return eRet;
        }
        pf->sTime = sYMDhm_f;

        // fUa
        eRet = emc_trans_XXX_X(eTrans, &(pu->fUa), &sfU_f);
        if(MC_OK != eRet)
        {
            #ifdef MC_DBG
            MCDBG("emc_trans_erc_13() emc_trans_XX_XX() error %d!", eRet);
            #endif
            return eRet;
        }
        
        pf->fUa = sfU_f;
        
        // fUb
        eRet = emc_trans_XXX_X(eTrans, &(pu->fUb), &sfU_f);
        if(MC_OK != eRet)
        {
            #ifdef MC_DBG
            MCDBG("emc_trans_erc_13() emc_trans_XX_XX() error %d!", eRet);
            #endif
            return eRet;
        } 
        
        pf->fUb = sfU_f;

        // fUc
        eRet = emc_trans_XXX_X(eTrans, &(pu->fUc), &sfU_f);
        if(MC_OK != eRet)
        {
            #ifdef MC_DBG
            MCDBG("emc_trans_erc_13() emc_trans_XX_XX() error %d!", eRet);
            #endif
            return eRet;
        }  
        
        pf->fUc = sfU_f;
    }
    // ��֡�ൽ�û���
    else if (MC_TRANS_F2U == eTrans)
    {
        // Pn
        usPn = pf->usPN & 0x7FFF;
        if(usPn > MC_PN_MAX)
        {
            #ifdef MC_DBG
            MCDBG("emc_trans_erc_13() para Pn is out of range! usPN = %d", pf->usPN);
            #endif
            return MC_ERR_OUTRNG;
        }

        pu->usPN = usPn;

        // bStart
        if(pf->usPN & 0x8000)
        {
            pu->bStart = TRUE;
        }
        else
        {
            pu->bStart = FALSE;
        }

        // bPhaseA
        if(pf->ucExcp & 0x01)
        {
            pu->bPhaseA = TRUE;
        }
        else
        {
            pu->bPhaseA = FALSE;
        }

        // bPhaseB
        if(pf->ucExcp & 0x02)
        {
            pu->bPhaseB = TRUE;
        }
        else
        {
            pu->bPhaseB = FALSE;
        }

        // bPhaseC
        if(pf->ucExcp & 0x04)
        {
            pu->bPhaseC = TRUE;
        }
        else
        {
            pu->bPhaseC = FALSE;
        }

        // bOverUpUp
        ucTmp = (pf->ucExcp & 0x60) >> 5;
        if(1 == ucTmp)
        {
            pu->bOverUpUp = TRUE;
        }
        else if(2 == ucTmp)
        {
            pu->bOverUpUp = FALSE;
        }
        else
        {
            #ifdef MC_DBG
            MCDBG("emc_trans_erc_13() para error ucTmp = %d", ucTmp);
            #endif
            return MC_ERR_OUTRNG;
        }

        // sTime
        sYMDhm_f = pf->sTime;
        eRet = emc_trans_YYMMDDhhmm(eTrans, &(pu->sTime), &sYMDhm_f);
        if(MC_OK != eRet)
        {
            #ifdef MC_DBG
            MCDBG("emc_trans_erc_13() emc_trans_YYMMDDhhmm() error %d!", eRet);
            #endif
            return eRet;
        }

        // fUa
        sfU_f = pf->fUa;
        eRet = emc_trans_XXX_X(eTrans, &(pu->fUa), &sfU_f);
        if(MC_OK != eRet)
        {
            #ifdef MC_DBG
            MCDBG("emc_trans_erc_13() emc_trans_XX_XX() error %d!", eRet);
            #endif
            return eRet;
        }
        
        // fUb
        sfU_f = pf->fUb;
        eRet = emc_trans_XXX_X(eTrans, &(pu->fUb), &sfU_f);
        if(MC_OK != eRet)
        {
            #ifdef MC_DBG
            MCDBG("emc_trans_erc_13() emc_trans_XX_XX() error %d!", eRet);
            #endif
            return eRet;
        }   
        
        // fUc
        sfU_f = pf->fUc;
        eRet = emc_trans_XXX_X(eTrans, &(pu->fUc), &sfU_f);
        if(MC_OK != eRet)
        {
            #ifdef MC_DBG
            MCDBG("emc_trans_erc_13() emc_trans_XX_XX() error %d!", eRet);
            #endif
            return eRet;
        }   
    }
    else
    {
         #ifdef MC_DBG
         MCDBG("emc_trans_erc_13() eTrans is out of range!");
         #endif
         return MC_ERR_OUTRNG;    
    }
   
    // �������
    *pusLen = sizeof(sMcErc10_f);
    return MC_OK;
}

/*****************************************************************************
 �� �� ��  : emc_trans_erc_14
 ��������  : �¼���¼����ת������
 ��Ӧ�¼�  : MC_ERC_14_ELEC_OVER
 �������  : eMcTrans eTrans  
             void* pUser      
             void* pFrame     
             UINT16* pusLen   
 �������  : ��
 �� �� ֵ  : 
 ���ú���  : 
 ��������  : 
 
 �޸���ʷ      :
  1.��    ��   : 2013��11��20��
    ��    ��   : liming
    �޸�����   : �����ɺ���

*****************************************************************************/
eMcErr emc_trans_erc_14(eMcTrans eTrans, void* pUser, void* pFrame, UINT16* pusLen)
{
    eMcErr     eRet = MC_OK;
    sMcErc14     *pu = NULL;
    sMcErc14_f   *pf = NULL;
    UINT8      ucTmp = 9;
    UINT16      usPn = 0;
    sMcYMDhm_f  sYMDhm_f;
    sMcFmt09_f  sfI_f;

    if(!pUser || !pFrame || !pusLen)
    {
        #ifdef MC_DBG
        MCDBG("emc_trans_erc_14() para pointer is null!");
        #endif
        return MC_ERR_NULL;
    }

    pu = (sMcErc14*)pUser;
    pf = (sMcErc14_f*)pFrame;
    memset(&sYMDhm_f, 0, sizeof(sMcYMDhm_f));
    memset(&sfI_f,    0, sizeof(sMcFmt09_f));
    
    // �û��ൽ��֡��
    if(MC_TRANS_U2F == eTrans)
    {
        // Pn
        if(pu->usPN > MC_PN_MAX)
        {
            #ifdef MC_DBG
            MCDBG("emc_trans_erc_14() para Pn is out of range! usPN = %d", pu->usPN);
            #endif
            return MC_ERR_OUTRNG;
        }
        
        usPn = pu->usPN;
        
        if(pu->bStart == TRUE)
        {
            usPn |= 0x8000;
        }
        
        pf->usPN = usPn;

        // bPhaseA
        pf->ucExcp = 0;
        if(pu->bPhaseA == TRUE)
        {
            pf->ucExcp |= 0x01;
        }

        // bPhaseB
        if(pu->bPhaseB == TRUE)
        {
            pf->ucExcp |= 0x02;
        }
       
        // bPhaseC
        if(pu->bPhaseC == TRUE)
        {
            pf->ucExcp |= 0x04;
        }

        // bOverUpUp
        if(pu->bOverUpUp == TRUE)
        {
            pf->ucExcp |= 0x20;;
        }
        else 
        {
            pf->ucExcp |= 0x40;;
        }
        
        // sTime
        eRet = emc_trans_YYMMDDhhmm(eTrans, &(pu->sTime), &sYMDhm_f);
        if(MC_OK != eRet)
        {
            #ifdef MC_DBG
            MCDBG("emc_trans_erc_14() emc_trans_YYMMDDhhmm() error %d!", eRet);
            #endif
            return eRet;
        }
        
        pf->sTime = sYMDhm_f;
        
        // fIa
        eRet = emc_trans_sXXX_XXX(eTrans, &(pu->fIa), &sfI_f);
        if(MC_OK != eRet)
        {
            #ifdef MC_DBG
            MCDBG("emc_trans_erc_14() emc_trans_sXXX_XXX() error %d!", eRet);
            #endif
            return eRet;
        }
        
        pf->fIa = sfI_f;
        
        // fIb
        eRet = emc_trans_sXXX_XXX(eTrans, &(pu->fIb), &sfI_f);
        if(MC_OK != eRet)
        {
            #ifdef MC_DBG
            MCDBG("emc_trans_erc_14() emc_trans_sXXX_XXX() error %d!", eRet);
            #endif
            return eRet;
        }   
        
        pf->fIb = sfI_f;
        
        // fIc
        eRet = emc_trans_sXXX_XXX(eTrans, &(pu->fIc), &sfI_f);
        if(MC_OK != eRet)
        {
            #ifdef MC_DBG
            MCDBG("emc_trans_erc_14() emc_trans_sXXX_XXX() error %d!", eRet);
            #endif
            return eRet;
        }  
        
        pf->fIc = sfI_f;
    }
    // ��֡�ൽ�û���
    else if (MC_TRANS_F2U == eTrans)
    {
        // Pn
        usPn = pf->usPN & 0x7FFF;
        if(usPn > MC_PN_MAX)
        {
            #ifdef MC_DBG
            MCDBG("emc_trans_erc_14() para Pn is out of range! usPN = %d", pf->usPN);
            #endif
            return MC_ERR_OUTRNG;
        }

        pu->usPN = usPn;

        // bStart
        if(pf->usPN & 0x8000)
        {
            pu->bStart = TRUE;
        }
        else
        {
            pu->bStart = FALSE;
        }

        // bPhaseA
        if(pf->ucExcp & 0x01)
        {
            pu->bPhaseA = TRUE;
        }
        else
        {
            pu->bPhaseA = FALSE;
        }

        // bPhaseB
        if(pf->ucExcp & 0x02)
        {
            pu->bPhaseB = TRUE;
        }
        else
        {
            pu->bPhaseB = FALSE;
        }

        // bPhaseC
        if(pf->ucExcp & 0x04)
        {
            pu->bPhaseC = TRUE;
        }
        else
        {
            pu->bPhaseC = FALSE;
        }

        // bOverUpUp
        ucTmp = (pf->ucExcp & 0x60) >> 5;
        if(1 == ucTmp)
        {
            pu->bOverUpUp = TRUE;
        }
        else if(2 == ucTmp)
        {
            pu->bOverUpUp = FALSE;
        }
        else
        {
            #ifdef MC_DBG
            MCDBG("emc_trans_erc_14() para error ucTmp = %d", ucTmp);
            #endif
            return MC_ERR_OUTRNG;
        }
        
        // sTime
        sYMDhm_f = pf->sTime;
        eRet = emc_trans_YYMMDDhhmm(eTrans, &(pu->sTime), &sYMDhm_f);
        if(MC_OK != eRet)
        {
            #ifdef MC_DBG
            MCDBG("emc_trans_erc_14() emc_trans_YYMMDDhhmm() error %d!", eRet);
            #endif
            return eRet;
        }

        // fIa
        sfI_f = pf->fIa;
        eRet = emc_trans_sXXX_XXX(eTrans, &(pu->fIa), &sfI_f);
        if(MC_OK != eRet)
        {
            #ifdef MC_DBG
            MCDBG("emc_trans_erc_14() emc_trans_sXXX_XXX() error %d!", eRet);
            #endif
            return eRet;
        }
        
        // fIb
        sfI_f = pf->fIb;
        eRet = emc_trans_sXXX_XXX(eTrans, &(pu->fIb), &sfI_f);
        if(MC_OK != eRet)
        {
            #ifdef MC_DBG
            MCDBG("emc_trans_erc_14() emc_trans_sXXX_XXX() error %d!", eRet);
            #endif
            return eRet;
        }   
        
        // fIc
        sfI_f = pf->fIc;
        eRet = emc_trans_sXXX_XXX(eTrans, &(pu->fIc), &sfI_f);
        if(MC_OK != eRet)
        {
            #ifdef MC_DBG
            MCDBG("emc_trans_erc_14() emc_trans_sXXX_XXX() error %d!", eRet);
            #endif
            return eRet;
        }   
    }
    else
    {
         #ifdef MC_DBG
         MCDBG("emc_trans_erc_14() eTrans is out of range!");
         #endif
         return MC_ERR_OUTRNG;    
    }

    // �������
    *pusLen = sizeof(sMcErc14_f);
    return MC_OK;
}

/*****************************************************************************
 �� �� ��  : emc_trans_erc_15
 ��������  : �¼���¼����ת������
 ��Ӧ�¼�  : MC_ERC_15_UNBL_OVER_V
 �������  : eMcTrans eTrans  
             void* pUser      
             void* pFrame     
             UINT16* pusLen   
 �������  : ��
 �� �� ֵ  : 
 ���ú���  : 
 ��������  : 
 
 �޸���ʷ      :
  1.��    ��   : 2013��11��20��
    ��    ��   : liming
    �޸�����   : �����ɺ���

*****************************************************************************/
eMcErr emc_trans_erc_15(eMcTrans eTrans, void* pUser, void* pFrame, UINT16* pusLen)
{
    eMcErr      eRet = MC_OK;
    sMcErc15     *pu = NULL;
    sMcErc15_f   *pf = NULL;
    UINT16      usPn = 0;
    sMcYMDhm_f  sYMDhm_f;
    sMcFmt08_f  sfU_f;
    sMcFmt10_f  fUbl_f;

    if(!pUser || !pFrame || !pusLen)
    {
        #ifdef MC_DBG
        MCDBG("emc_trans_erc_15() para pointer is null!");
        #endif
        return MC_ERR_NULL;
    }

    pu = (sMcErc15*)pUser;
    pf = (sMcErc15_f*)pFrame;
    memset(&sYMDhm_f, 0, sizeof(sMcYMDhm_f));
    memset(&sfU_f,    0, sizeof(sMcFmt08_f));
    memset(&fUbl_f,   0, sizeof(sMcFmt10_f));

    // �û��ൽ��֡��
    if(MC_TRANS_U2F == eTrans)
    {
        // Pn
        if(pu->usPN > MC_PN_MAX)
        {
            #ifdef MC_DBG
            MCDBG("emc_trans_erc_15() para Pn is out of range! usPN = %d", pu->usPN);
            #endif
            return MC_ERR_OUTRNG;
        }
        
        usPn = pu->usPN;
        
        if(pu->bStart == TRUE)
        {
            usPn |= 0x8000;
        }
        
        pf->usPN = usPn;

        // sTime
        eRet = emc_trans_YYMMDDhhmm(eTrans, &(pu->sTime), &sYMDhm_f);
        if(MC_OK != eRet)
        {
            #ifdef MC_DBG
            MCDBG("emc_trans_erc_15() emc_trans_YYMMDDhhmm() error %d!", eRet);
            #endif
            return eRet;
        }
        
        pf->sTime = sYMDhm_f;
        
        // fUbl
        eRet = emc_trans_XX_XX(eTrans, &(pu->fUbl), &fUbl_f);
        if(MC_OK != eRet)
        {
            #ifdef MC_DBG
            MCDBG("emc_trans_erc_15() emc_trans_XX_XX() error %d!", eRet);
            #endif
            return eRet;
        }
        
        pf->fUbl = fUbl_f;
        
        // fUa
        eRet = emc_trans_XXX_X(eTrans, &(pu->fUa), &(pf->fUa));
        if(MC_OK != eRet)
        {
            #ifdef MC_DBG
            MCDBG("emc_trans_erc_15() emc_trans_XXX_X() error %d!", eRet);
            #endif
            return eRet;
        }
        
        // fUb
        eRet = emc_trans_XXX_X(eTrans, &(pu->fUb), &(pf->fUb));
        if(MC_OK != eRet)
        {
            #ifdef MC_DBG
            MCDBG("emc_trans_erc_15() emc_trans_XXX_X() error %d!", eRet);
            #endif
            return eRet;
        }   
        
        // fUc
        eRet = emc_trans_XXX_X(eTrans, &(pu->fUc), &(pf->fUc));
        if(MC_OK != eRet)
        {
            #ifdef MC_DBG
            MCDBG("emc_trans_erc_15() emc_trans_XXX_X() error %d!", eRet);
            #endif
            return eRet;
        }  
    }
    // ��֡�ൽ�û���
    else if (MC_TRANS_F2U == eTrans)
    {
        // Pn
        usPn = pf->usPN & 0x7FFF;
        if(usPn > MC_PN_MAX)
        {
            #ifdef MC_DBG
            MCDBG("emc_trans_erc_15() para Pn is out of range! usPN = %d", pf->usPN);
            #endif
            return MC_ERR_OUTRNG;
        }

        pu->usPN = usPn;

        // bStart
        if(pf->usPN & 0x8000)
        {
            pu->bStart = TRUE;
        }
        else
        {
            pu->bStart = FALSE;
        }

        // sTime
        sYMDhm_f = pf->sTime;
        eRet = emc_trans_YYMMDDhhmm(eTrans, &(pu->sTime), &sYMDhm_f);
        if(MC_OK != eRet)
        {
            #ifdef MC_DBG
            MCDBG("emc_trans_erc_15() emc_trans_YYMMDDhhmm() error %d!", eRet);
            #endif
            return eRet;
        }
        
        
        // fUbl
        fUbl_f = pf->fUbl;
        eRet = emc_trans_XX_XX(eTrans, &(pu->fUbl), &fUbl_f);
        if(MC_OK != eRet)
        {
            #ifdef MC_DBG
            MCDBG("emc_trans_erc_15() emc_trans_XX_XX() error %d!", eRet);
            #endif
            return eRet;
        }
        
        // fUa
        sfU_f = pf->fUa;
        eRet = emc_trans_XXX_X(eTrans, &(pu->fUa), &sfU_f);
        if(MC_OK != eRet)
        {
            #ifdef MC_DBG
            MCDBG("emc_trans_erc_15() emc_trans_XXX_X() error %d!", eRet);
            #endif
            return eRet;
        }
        
        // fUb
        sfU_f = pf->fUb;
        eRet = emc_trans_XXX_X(eTrans, &(pu->fUb), &sfU_f);
        if(MC_OK != eRet)
        {
            #ifdef MC_DBG
            MCDBG("emc_trans_erc_15() emc_trans_XXX_X() error %d!", eRet);
            #endif
            return eRet;
        }   
        
        // fUc
        sfU_f = pf->fUc;
        eRet = emc_trans_XXX_X(eTrans, &(pu->fUc), &sfU_f);
        if(MC_OK != eRet)
        {
            #ifdef MC_DBG
            MCDBG("emc_trans_erc_15() emc_trans_XXX_X() error %d!", eRet);
            #endif
            return eRet;
        }  
    }
    else
    {
         #ifdef MC_DBG
         MCDBG("emc_trans_erc_15() eTrans is out of range!");
         #endif
         return MC_ERR_OUTRNG;    
    }
    
    // �������
    *pusLen = sizeof(sMcErc15_f);
    return MC_OK;
}

/*****************************************************************************
 �� �� ��  : emc_trans_erc_16
 ��������  : �¼���¼����ת������
 ��Ӧ�¼�  : MC_ERC_16_UNBL_OVER_I
 �������  : eMcTrans eTrans  
             void* pUser      
             void* pFrame     
             UINT16* pusLen   
 �������  : ��
 �� �� ֵ  : 
 ���ú���  : 
 ��������  : 
 
 �޸���ʷ      :
  1.��    ��   : 2013��11��20��
    ��    ��   : liming
    �޸�����   : �����ɺ���

*****************************************************************************/
eMcErr emc_trans_erc_16(eMcTrans eTrans, void* pUser, void* pFrame, UINT16* pusLen)
{
    eMcErr     eRet = MC_OK;
    sMcErc16     *pu = NULL;
    sMcErc16_f   *pf = NULL;
    UINT16      usPn = 0;
    sMcYMDhm_f  sYMDhm_f;
    sMcFmt09_f  sfI_f;
    sMcFmt10_f  fUbl_f;

    if(!pUser || !pFrame || !pusLen)
    {
        #ifdef MC_DBG
        MCDBG("emc_trans_erc_16() para pointer is null!");
        #endif
        return MC_ERR_NULL;
    }

    pu = (sMcErc16*)pUser;
    pf = (sMcErc16_f*)pFrame;
    memset(&sYMDhm_f, 0, sizeof(sMcYMDhm_f));
    memset(&sfI_f,    0, sizeof(sMcFmt09_f));
    memset(&fUbl_f,   0, sizeof(sMcFmt10_f));
    
    // �û��ൽ��֡��
    if(MC_TRANS_U2F == eTrans)
    {
        // Pn
        if(pu->usPN > MC_PN_MAX)
        {
            #ifdef MC_DBG
            MCDBG("emc_trans_erc_16() para Pn is out of range! usPN = %d", pu->usPN);
            #endif
            return MC_ERR_OUTRNG;
        }
        
        usPn = pu->usPN;
        
        if(pu->bStart == TRUE)
        {
            usPn |= 0x8000;
        }
        
        pf->usPN = usPn;

        // sTime
        eRet = emc_trans_YYMMDDhhmm(eTrans, &(pu->sTime), &sYMDhm_f);
        if(MC_OK != eRet)
        {
            #ifdef MC_DBG
            MCDBG("emc_trans_erc_16() emc_trans_YYMMDDhhmm() error %d!", eRet);
            #endif
            return eRet;
        }
        
        pf->sTime = sYMDhm_f;
        
        // fUbl
        eRet = emc_trans_XX_XX(eTrans, &(pu->fUbl), &fUbl_f);
        if(MC_OK != eRet)
        {
            #ifdef MC_DBG
            MCDBG("emc_trans_erc_16() emc_trans_XX_XX() error %d!", eRet);
            #endif
            return eRet;
        }

        pf->fUbl = fUbl_f;
        
        // fIa
        eRet = emc_trans_sXXX_XXX(eTrans, &(pu->fIa), &sfI_f);
        if(MC_OK != eRet)
        {
            #ifdef MC_DBG
            MCDBG("emc_trans_erc_16() emc_trans_sXXX_XXX() error %d!", eRet);
            #endif
            return eRet;
        }
        
        pf->fIa = sfI_f;
        
        // fIb
        eRet = emc_trans_sXXX_XXX(eTrans, &(pu->fIb), &sfI_f);
        if(MC_OK != eRet)
        {
            #ifdef MC_DBG
            MCDBG("emc_trans_erc_16() emc_trans_sXXX_XXX() error %d!", eRet);
            #endif
            return eRet;
        }   
        
        pf->fIb = sfI_f;
        
        // fIc
        eRet = emc_trans_sXXX_XXX(eTrans, &(pu->fIc), &sfI_f);
        if(MC_OK != eRet)
        {
            #ifdef MC_DBG
            MCDBG("emc_trans_erc_16() emc_trans_sXXX_XXX() error %d!", eRet);
            #endif
            return eRet;
        }  
        
        pf->fIc = sfI_f;
    }
    // ��֡�ൽ�û���
    else if (MC_TRANS_F2U == eTrans)
    {
        // Pn
        usPn = pf->usPN & 0x7FFF;
        if(usPn > MC_PN_MAX)
        {
            #ifdef MC_DBG
            MCDBG("emc_trans_erc_16() para Pn is out of range! usPN = %d", pf->usPN);
            #endif
            return MC_ERR_OUTRNG;
        }

        pu->usPN = usPn;

        // bStart
        if(pf->usPN & 0x8000)
        {
            pu->bStart = TRUE;
        }
        else
        {
            pu->bStart = FALSE;
        }

        // sTime
        eRet = emc_trans_YYMMDDhhmm(eTrans, &(pu->sTime), &(pf->sTime));
        if(MC_OK != eRet)
        {
            #ifdef MC_DBG
            MCDBG("emc_trans_erc_16() emc_trans_YYMMDDhhmm() error %d!", eRet);
            #endif
            return eRet;
        }

        // fUbl
        fUbl_f = pf->fUbl;
        eRet = emc_trans_XX_XX(eTrans, &(pu->fUbl), &fUbl_f);
        if(MC_OK != eRet)
        {
            #ifdef MC_DBG
            MCDBG("emc_trans_erc_16() emc_trans_XX_XX() error %d!", eRet);
            #endif
            return eRet;
        }
        
        // fIa
        sfI_f = pf->fIa;
        eRet = emc_trans_sXXX_XXX(eTrans, &(pu->fIa), &sfI_f);
        if(MC_OK != eRet)
        {
            #ifdef MC_DBG
            MCDBG("emc_trans_erc_16() emc_trans_sXXX_XXX() error %d!", eRet);
            #endif
            return eRet;
        }
        
        // fIb
        sfI_f = pf->fIb;
        eRet = emc_trans_sXXX_XXX(eTrans, &(pu->fIb), &sfI_f);
        if(MC_OK != eRet)
        {
            #ifdef MC_DBG
            MCDBG("emc_trans_erc_16() emc_trans_sXXX_XXX() error %d!", eRet);
            #endif
            return eRet;
        }   
        
        // fIc
        sfI_f = pf->fIc;
        eRet = emc_trans_sXXX_XXX(eTrans, &(pu->fIc), &sfI_f);
        if(MC_OK != eRet)
        {
            #ifdef MC_DBG
            MCDBG("emc_trans_erc_16() emc_trans_sXXX_XXX() error %d!", eRet);
            #endif
            return eRet;
        }   
    }
    else
    {
         #ifdef MC_DBG
         MCDBG("emc_trans_erc_16() eTrans is out of range!");
         #endif
         return MC_ERR_OUTRNG;    
    }

    // �������
    *pusLen = sizeof(sMcErc16_f);
    return MC_OK;
}

/*****************************************************************************
 �� �� ��  : emc_trans_erc_17
 ��������  : �¼���¼����ת������
 ��Ӧ�¼�  : MC_ERC_17_HUNBL_OVER_V
 �������  : eMcTrans eTrans  
             void* pUser      
             void* pFrame     
             UINT16* pusLen   
 �������  : ��
 �� �� ֵ  : 
 ���ú���  : 
 ��������  : 
 
 �޸���ʷ      :
  1.��    ��   : 2013��11��20��
    ��    ��   : liming
    �޸�����   : �����ɺ���

*****************************************************************************/
eMcErr emc_trans_erc_17(eMcTrans eTrans, void* pUser, void* pFrame, UINT16* pusLen)
{
    eMcErr     eRet = MC_OK;
    sMcErc17     *pu = NULL;
    sMcErc17_f   *pf = NULL;
    sMcYMDhm_f  sYMDhm_f;
    sMcFmt10_f  fXX_XX_f;

    if(!pUser || !pFrame || !pusLen)
    {
        #ifdef MC_DBG
        MCDBG("emc_trans_erc_17() para pointer is null!");
        #endif
        return MC_ERR_NULL;
    }

    pu = (sMcErc17*)pUser;
    pf = (sMcErc17_f*)pFrame;
    memset(&sYMDhm_f, 0, sizeof(sMcYMDhm_f));
    memset(&fXX_XX_f, 0, sizeof(sMcFmt10_f));

    // �û��ൽ��֡��
    if(MC_TRANS_U2F == eTrans)
    {
        // Pn
        if(pu->usPN > MC_PN_MAX)
        {
            #ifdef MC_DBG
            MCDBG("emc_trans_erc_17() para Pn is out of range! usPN = %d", pu->usPN);
            #endif
            return MC_ERR_OUTRNG;
        }

        pf->usPN = pu->usPN;

        // bPhaseA
        pf->ucExcp = 0;
        if(pu->bPhaseA == TRUE)
        {
            pf->ucExcp |= 0x01;
        }

        // bPhaseB
        if(pu->bPhaseB == TRUE)
        {
            pf->ucExcp |= 0x02;
        }
       
        // bPhaseC
        if(pu->bPhaseC == TRUE)
        {
            pf->ucExcp |= 0x04;
        }

        // bTotal
        if(pu->bTotal== TRUE)
        {
            pf->ucExcp |= 0x10;
        }

        // bOdd
        if(pu->bOdd == TRUE)
        {
            pf->ucExcp |= 0x20;
        }
       
        // bEven
        if(pu->bEven == TRUE)
        {
            pf->ucExcp |= 0x40;
        }
        
        // sTime
        eRet = emc_trans_YYMMDDhhmm(eTrans, &(pu->sTime), &sYMDhm_f);
        if(MC_OK != eRet)
        {
            #ifdef MC_DBG
            MCDBG("emc_trans_erc_17() emc_trans_YYMMDDhhmm() error %d!", eRet);
            #endif
            return eRet;
        }

        pf->sTime = sYMDhm_f;

        // fUbl
        eRet = emc_trans_XX_XX(eTrans, &(pu->fTotal), &fXX_XX_f);
        if(MC_OK != eRet)
        {
            #ifdef MC_DBG
            MCDBG("emc_trans_erc_17() emc_trans_XX_XX() error %d!", eRet);
            #endif
            return eRet;
        }
        
        pf->fTotal = fXX_XX_f;
        
        // fOdd
        eRet = emc_trans_XX_XX(eTrans, &(pu->fOdd), &fXX_XX_f);
        if(MC_OK != eRet)
        {
            #ifdef MC_DBG
            MCDBG("emc_trans_erc_17() emc_trans_XX_XX() error %d!", eRet);
            #endif
            return eRet;
        }
        
        pf->fOdd = fXX_XX_f;

        // fEven
        eRet = emc_trans_XX_XX(eTrans, &(pu->fEven), &fXX_XX_f);
        if(MC_OK != eRet)
        {
            #ifdef MC_DBG
            MCDBG("emc_trans_erc_17() emc_trans_XX_XX() error %d!", eRet);
            #endif
            return eRet;
        }
        
        pf->fEven = fXX_XX_f;
    }
    // ��֡�ൽ�û���
    else if (MC_TRANS_F2U == eTrans)
    {
        // Pn
        if(pf->usPN > MC_PN_MAX)
        {
            #ifdef MC_DBG
            MCDBG("emc_trans_erc_17() para Pn is out of range! usPN = %d", pf->usPN);
            #endif
            return MC_ERR_OUTRNG;
        }

        pu->usPN = pf->usPN;

        // bPhaseA
        if(pf->ucExcp & 0x01)
        {
            pu->bPhaseA = TRUE;
        }
        else
        {
            pu->bPhaseA = FALSE;
        }

        // bPhaseB
        if(pf->ucExcp & 0x02)
        {
            pu->bPhaseB = TRUE;
        }
        else
        {
            pu->bPhaseB = FALSE;
        }

        // bPhaseC
        if(pf->ucExcp & 0x04)
        {
            pu->bPhaseC = TRUE;
        }
        else
        {
            pu->bPhaseC = FALSE;
        }

        // bTotal
        if(pf->ucExcp & 0x10)
        {
            pu->bTotal = TRUE;
        }
        else
        {
            pu->bTotal = FALSE;
        }

        // bOdd
        if(pf->ucExcp & 0x20)
        {
            pu->bOdd = TRUE;
        }
        else
        {
            pu->bOdd = FALSE;
        }

        // bEven
        if(pf->ucExcp & 0x40)
        {
            pu->bEven = TRUE;
        }
        else
        {
            pu->bEven = FALSE;
        }
        
        // sTime
        sYMDhm_f = pf->sTime;
        eRet = emc_trans_YYMMDDhhmm(eTrans, &(pu->sTime), &sYMDhm_f);
        if(MC_OK != eRet)
        {
            #ifdef MC_DBG
            MCDBG("emc_trans_erc_17() emc_trans_YYMMDDhhmm() error %d!", eRet);
            #endif
            return eRet;
        }

        // fUbl
        fXX_XX_f = pf->fTotal;
        eRet = emc_trans_XX_XX(eTrans, &(pu->fTotal), &fXX_XX_f);
        if(MC_OK != eRet)
        {
            #ifdef MC_DBG
            MCDBG("emc_trans_erc_17() emc_trans_XX_XX() error %d!", eRet);
            #endif
            return eRet;
        }
        
        // fOdd
        fXX_XX_f = pf->fOdd;
        eRet = emc_trans_XX_XX(eTrans, &(pu->fOdd), &fXX_XX_f);
        if(MC_OK != eRet)
        {
            #ifdef MC_DBG
            MCDBG("emc_trans_erc_17() emc_trans_XX_XX() error %d!", eRet);
            #endif
            return eRet;
        }
        
        // fEven
        fXX_XX_f = pf->fEven;
        eRet = emc_trans_XX_XX(eTrans, &(pu->fEven), &fXX_XX_f);
        if(MC_OK != eRet)
        {
            #ifdef MC_DBG
            MCDBG("emc_trans_erc_17() emc_trans_XX_XX() error %d!", eRet);
            #endif
            return eRet;
        }
    }
    else
    {
         #ifdef MC_DBG
         MCDBG("emc_trans_erc_17() eTrans is out of range!");
         #endif
         return MC_ERR_OUTRNG;    
    }
 
    // �������
    *pusLen = sizeof(sMcErc17_f);
    return MC_OK;
}

/*****************************************************************************
 �� �� ��  : emc_trans_erc_18
 ��������  : �¼���¼����ת������
 ��Ӧ�¼�  : MC_ERC_18_HUNBL_OVER_I
 �������  : eMcTrans eTrans  
               
 �������  : UINT16* pusLen 
               void* pUser      
               void* pFrame  
 �� �� ֵ  : 
 ���ú���  : 
 ��������  : 
 
 �޸���ʷ      :
  1.��    ��   : 2013��11��20��
    ��    ��   : liming
    �޸�����   : �����ɺ���

*****************************************************************************/
eMcErr emc_trans_erc_18(eMcTrans eTrans, void* pUser, void* pFrame, UINT16* pusLen)
{
    return emc_trans_erc_17(eTrans, pUser, pFrame, pusLen);
}

/*****************************************************************************
 �� �� ��  : emc_trans_erc_19
 ��������  : �¼���¼����ת������
 ��Ӧ�¼�  : MC_ERC_19_FLASH_OVER
 �������  : eMcTrans eTrans  
             void* pUser      
             void* pFrame     
             UINT16* pusLen   
 �������  : ��
 �� �� ֵ  : 
 ���ú���  : 
 ��������  : 
 
 �޸���ʷ      :
  1.��    ��   : 2013��11��20��
    ��    ��   : liming
    �޸�����   : �����ɺ���

*****************************************************************************/
eMcErr emc_trans_erc_19(eMcTrans eTrans, void* pUser, void* pFrame, UINT16* pusLen)
{
    eMcErr     eRet = MC_OK;
    sMcErc19     *pu = NULL;
    sMcErc19_f   *pf = NULL;
    sMcYMDhm_f  sYMDhm_f;
    sMcFmt10_f  fXX_XX_f;
    
    if(!pUser || !pFrame || !pusLen)
    {
        #ifdef MC_DBG
        MCDBG("emc_trans_erc_19() para pointer is null!");
        #endif
        return MC_ERR_NULL;
    }

    pu = (sMcErc19*)pUser;
    pf = (sMcErc19_f*)pFrame;
    memset(&sYMDhm_f, 0, sizeof(sMcYMDhm_f));
    memset(&fXX_XX_f, 0, sizeof(sMcFmt10_f));

    // �û��ൽ��֡��
    if(MC_TRANS_U2F == eTrans)
    {
        // Pn
        if(pu->usPN > MC_PN_MAX)
        {
            #ifdef MC_DBG
            MCDBG("emc_trans_erc_19() para Pn is out of range! usPN = %d", pu->usPN);
            #endif
            return MC_ERR_OUTRNG;
        }

        pf->usPN = pu->usPN;

        // bPhaseA
        pf->ucExcp = 0;
        if(pu->bPhaseA == TRUE)
        {
            pf->ucExcp |= 0x01;
        }

        // bPhaseB
        if(pu->bPhaseB == TRUE)
        {
            pf->ucExcp |= 0x02;
        }
       
        // bPhaseC
        if(pu->bPhaseC == TRUE)
        {
            pf->ucExcp |= 0x04;
        }

        // bTotal
        if(pu->bLong == TRUE)
        {
            pf->ucExcp |= 0x80;
        }
        
        // sTime
        eRet = emc_trans_YYMMDDhhmm(eTrans, &(pu->sTime), &sYMDhm_f);
        if(MC_OK != eRet)
        {
            #ifdef MC_DBG
            MCDBG("emc_trans_erc_17() emc_trans_YYMMDDhhmm() error %d!", eRet);
            #endif
            return eRet;
        }

        pf->sTime = sYMDhm_f;

        // fA
        eRet = emc_trans_XX_XX(eTrans, &(pu->fA), &fXX_XX_f);
        if(MC_OK != eRet)
        {
            #ifdef MC_DBG
            MCDBG("emc_trans_erc_19() emc_trans_XX_XX() error %d!", eRet);
            #endif
            return eRet;
        }
        
        pf->fA = fXX_XX_f;
        
        // fB
        eRet = emc_trans_XX_XX(eTrans, &(pu->fB), &fXX_XX_f);
        if(MC_OK != eRet)
        {
            #ifdef MC_DBG
            MCDBG("emc_trans_erc_19() emc_trans_XX_XX() error %d!", eRet);
            #endif
            return eRet;
        }
        
        pf->fB = fXX_XX_f;
        
        // fC
        eRet = emc_trans_XX_XX(eTrans, &(pu->fC), &fXX_XX_f);
        if(MC_OK != eRet)
        {
            #ifdef MC_DBG
            MCDBG("emc_trans_erc_19() emc_trans_XX_XX() error %d!", eRet);
            #endif
            return eRet;
        }
        
        pf->fC = fXX_XX_f;
    }
    // ��֡�ൽ�û���
    else if (MC_TRANS_F2U == eTrans)
    {
        // Pn
        if(pf->usPN > MC_PN_MAX)
        {
            #ifdef MC_DBG
            MCDBG("emc_trans_erc_19() para Pn is out of range! usPN = %d", pf->usPN);
            #endif
            return MC_ERR_OUTRNG;
        }

        pu->usPN = pf->usPN;

        // bPhaseA
        if(pf->ucExcp & 0x01)
        {
            pu->bPhaseA = TRUE;
        }
        else
        {
            pu->bPhaseA = FALSE;
        }

        // bPhaseB
        if(pf->ucExcp & 0x02)
        {
            pu->bPhaseB = TRUE;
        }
        else
        {
            pu->bPhaseB = FALSE;
        }

        // bPhaseC
        if(pf->ucExcp & 0x04)
        {
            pu->bPhaseC = TRUE;
        }
        else
        {
            pu->bPhaseC = FALSE;
        }

        // bTotal
        if(pf->ucExcp & 0x80)
        {
            pu->bLong = TRUE;
        }
        else
        {
            pu->bLong = FALSE;
        }

        // sTime
        sYMDhm_f = pf->sTime;
        eRet = emc_trans_YYMMDDhhmm(eTrans, &(pu->sTime), &sYMDhm_f);
        if(MC_OK != eRet)
        {
            #ifdef MC_DBG
            MCDBG("emc_trans_erc_17() emc_trans_YYMMDDhhmm() error %d!", eRet);
            #endif
            return eRet;
        }

        // fA
        fXX_XX_f = pf->fA;
        eRet = emc_trans_XX_XX(eTrans, &(pu->fA), &fXX_XX_f);
        if(MC_OK != eRet)
        {
            #ifdef MC_DBG
            MCDBG("emc_trans_erc_19() emc_trans_XX_XX() error %d!", eRet);
            #endif
            return eRet;
        }
        
        // fB
        fXX_XX_f = pf->fB;
        eRet = emc_trans_XX_XX(eTrans, &(pu->fB), &fXX_XX_f);
        if(MC_OK != eRet)
        {
            #ifdef MC_DBG
            MCDBG("emc_trans_erc_19() emc_trans_XX_XX() error %d!", eRet);
            #endif
            return eRet;
        }
        
        // fC
        fXX_XX_f = pf->fC;
        eRet = emc_trans_XX_XX(eTrans, &(pu->fC), &fXX_XX_f);
        if(MC_OK != eRet)
        {
            #ifdef MC_DBG
            MCDBG("emc_trans_erc_19() emc_trans_XX_XX() error %d!", eRet);
            #endif
            return eRet;
        }
             
    }
    else
    {
         #ifdef MC_DBG
         MCDBG("emc_trans_erc_19() eTrans is out of range!");
         #endif
         return MC_ERR_OUTRNG;    
    }

    // �������
    *pusLen = sizeof(sMcErc19_f);
    return MC_OK;
}

/*****************************************************************************
 �� �� ��  : emc_trans_erc_20
 ��������  : �¼���¼����ת������
 ��Ӧ�¼�  : MC_ERC_19_FLASH_OVER
 �������  : eMcTrans eTrans  
             void* pUser      
             void* pFrame     
             UINT16* pusLen   
 �������  : ��
 �� �� ֵ  : 
 ���ú���  : 
 ��������  : 
 
 �޸���ʷ      :
  1.��    ��   : 2013��11��20��
    ��    ��   : liming
    �޸�����   : �����ɺ���

*****************************************************************************/
eMcErr emc_trans_erc_20(eMcTrans eTrans, void* pUser, void* pFrame, UINT16* pusLen)
{
    eMcErr      eRet = MC_OK;
    sMcErc20     *pu = NULL;
    sMcErc20_f   *pf = NULL;
    UINT16     usLen = 0;
    UINT16      usPn = 0;
    sMcYMDhm_f     sYMDhm_f;
    sMcNelcValue_f sValue_f;

    if(!pUser || !pFrame || !pusLen)
    {
        #ifdef MC_DBG
        MCDBG("emc_trans_erc_20() para pointer is null!");
        #endif
        return MC_ERR_NULL;
    }

    pu = (sMcErc20*)pUser;
    pf = (sMcErc20_f*)pFrame;
    memset(&sYMDhm_f, 0, sizeof(sMcYMDhm_f));
    memset(&sValue_f, 0, sizeof(sMcNelcValue_f));

    // �û��ൽ��֡��
    if(MC_TRANS_U2F == eTrans)
    {
        // Pn
        if(pu->usPN > MC_PN_MAX)
        {
            #ifdef MC_DBG
            MCDBG("emc_trans_erc_16() para Pn is out of range! usPN = %d", pu->usPN);
            #endif
            return MC_ERR_OUTRNG;
        }
        
        usPn = pu->usPN;
        
        if(pu->bStart == TRUE)
        {
            usPn |= 0x8000;
        }
        
        pf->usPN = usPn;

        // bUp
        pf->ucExcp = 0;
        if(pu->bUp == TRUE)
        {
            pf->ucExcp |= 0x01;
        }

        // bDown
        if(pu->bDown == TRUE)
        {
            pf->ucExcp |= 0x02;
        }

        // sTime
        eRet = emc_trans_YYMMDDhhmm(eTrans, &(pu->sTime), &sYMDhm_f);
        if(MC_OK != eRet)
        {
            #ifdef MC_DBG
            MCDBG("emc_trans_erc_20() emc_trans_YYMMDDhhmm() error %d!", eRet);
            #endif
            return eRet;
        }
        
        pf->sTime = sYMDhm_f;
        
        // sValue
        eRet = emc_trans_afn13f233(eTrans, &(pu->sValue), &sValue_f, &usLen);
        if(MC_OK != eRet)
        {
            #ifdef MC_DBG
            MCDBG("emc_trans_erc_20() emc_trans_afn13f233() error %d!", eRet);
            #endif
            return eRet;
        }

        pf->sValue = sValue_f;
    }
    // ��֡�ൽ�û���
    else if (MC_TRANS_F2U == eTrans)
    {
        // Pn
        usPn = pf->usPN & 0x7FFF;
        if(usPn > MC_PN_MAX)
        {
            #ifdef MC_DBG
            MCDBG("emc_trans_erc_16() para Pn is out of range! usPN = %d", pf->usPN);
            #endif
            return MC_ERR_OUTRNG;
        }

        pu->usPN = usPn;

        // bStart
        if(pf->usPN & 0x8000)
        {
            pu->bStart = TRUE;
        }
        else
        {
            pu->bStart = FALSE;
        }

        // bUp
        if(pf->ucExcp & 0x01)
        {
            pu->bUp = TRUE;
        }
        else
        {
            pu->bUp = FALSE;
        }

        // bDown
        if(pf->ucExcp & 0x02)
        {
            pu->bDown = TRUE;
        }
        else
        {
            pu->bDown = FALSE;
        }

        // sTime
        sYMDhm_f = pf->sTime;
        eRet = emc_trans_YYMMDDhhmm(eTrans, &(pu->sTime), &sYMDhm_f);
        if(MC_OK != eRet)
        {
            #ifdef MC_DBG
            MCDBG("emc_trans_erc_20() emc_trans_YYMMDDhhmm() error %d!", eRet);
            #endif
            return eRet;
        }

        // sValue
        sValue_f = pf->sValue;
        eRet = emc_trans_afn13f233(eTrans, &(pu->sValue), &sValue_f, &usLen);
        if(MC_OK != eRet)
        {
            #ifdef MC_DBG
            MCDBG("emc_trans_erc_20() emc_trans_afn13f233() error %d!", eRet);
            #endif
            return eRet;
        }
    }
    else
    {
         #ifdef MC_DBG
         MCDBG("emc_trans_erc_20() eTrans is out of range!");
         #endif
         return MC_ERR_OUTRNG;    
    }

    // ȥ����
    usLen = usLen;
    
    // �������
    *pusLen = sizeof(sMcErc20_f);
    return MC_OK;
}

/*****************************************************************************
 �� �� ��  : pMcGetRec
 ��������  : ͨ���¼����ͱ�ʶ, ��ö�Ӧ���¼����ݽṹת������
 �������  : eMcErc eType  
 �������  : ��
 �� �� ֵ  : pMcFunc
 ���ú���  : 
 ��������  : 
 
 �޸���ʷ      :
  1.��    ��   : 2013��11��20��
    ��    ��   : liming
    �޸�����   : �����ɺ���

*****************************************************************************/
pMcFunc pMcGetRec(eMcErc eType)
{
    pMcFunc pFunc = NULL;
    
    switch ( eType )
    {
        case MC_ERC_1_RESET :
            pFunc = emc_trans_erc_1;
            break;
            
        case MC_ERC_2_DATA_CLEAR :
            pFunc = emc_trans_erc_2;
            break;
            
        case MC_ERC_3_SOFT_CHANGE :
            pFunc = emc_trans_erc_3;
            break;
            
        case MC_ERC_4_PARA_CHANGE :
            pFunc = emc_trans_erc_4;
            break;
            
        case MC_ERC_5_CHECK_TIME :
            pFunc = emc_trans_erc_5;
            break;
            
        case MC_ERC_6_STATE_CHANGE :
            pFunc = emc_trans_erc_6;
            break;
            
        case MC_ERC_7_REMOTE_SWITCH :
            pFunc = emc_trans_erc_7;
            break;
            
        case MC_ERC_8_POWER_ON_OFF :
            pFunc = emc_trans_erc_8;
            break;
            
        case MC_ERC_9_FACTOR_OVER :
            pFunc = emc_trans_erc_9;
            break;
            
        case MC_ERC_10_VOLT_EXCP :
            pFunc = emc_trans_erc_10;
            break;
            
        case MC_ERC_11_VOLT_CIRCLE :
            pFunc = emc_trans_erc_11;
            break;
            
        case MC_ERC_12_ELEC_CRICLE :
            pFunc = emc_trans_erc_12;
            break;
            
        case MC_ERC_13_VOLT_OVER :
            pFunc = emc_trans_erc_13;
            break;
            
        case MC_ERC_14_ELEC_OVER :
            pFunc = emc_trans_erc_14;
            break;
            
        case MC_ERC_15_UNBL_OVER_V :
            pFunc = emc_trans_erc_15;
            break;
            
        case MC_ERC_16_UNBL_OVER_I :
            pFunc = emc_trans_erc_16;
            break;
            
        case MC_ERC_17_HUNBL_OVER_V :
            pFunc = emc_trans_erc_17;
            break;
            
        case MC_ERC_18_HUNBL_OVER_I :
            pFunc = emc_trans_erc_18;
            break;
            
        case MC_ERC_19_FLASH_OVER :
            pFunc = emc_trans_erc_19;
            break;
            
        case MC_ERC_20_NELC_OVER :
            pFunc = emc_trans_erc_20;
            break;
            
        default:
            break;
    }

    return pFunc;
}

/*****************************************************************************
 �� �� ��  : emc_trans_afn14f1_s2m
 ��������  : ���ݽṹת������
 ��Ӧ����  : MCMD_AFN_E_F1_EVENT_1
 �������  : eMcTrans eTrans  
             void* pUser      
             void* pFrame     
             UINT16* pusLen   
 �������  : ��
 �� �� ֵ  : 
 ���ú���  : 
 ��������  : 
 
 �޸���ʷ      :
  1.��    ��   : 2013��11��20��
    ��    ��   : liming
    �޸�����   : �����ɺ���

*****************************************************************************/
eMcErr emc_trans_afn14f1_s2m(eMcTrans eTrans, void* pUser, void* pFrame, UINT16* pusLen)
{
    eMcErr           eRet = MC_OK;
    sMcAfn14f1A       *pu = NULL;
    sMcAfn14f1A_f     *pf = NULL;
    pMcFunc         pFunc = NULL;
    UINT8         *pucTmp = NULL;
    UINT8          *pucLe = NULL;
    UINT16           usLe = 0;
    UINT8             ucN = 0;     // �¼���¼����
    UINT16          usLen = 0;     // ͳ��֡�౨���ֳ�
    INT32               i = 0;
    
    if(!pUser || !pFrame || !pusLen)
    {
        #ifdef MC_DBG
        MCDBG("emc_trans_afn14f1_s2m() para pointer is null!");
        #endif
        return MC_ERR_NULL;
    }

    pu = (sMcAfn14f1A*)pUser;
    pf = (sMcAfn14f1A_f*)pFrame;

    // �û��ൽ��֡��
    if(MC_TRANS_U2F == eTrans)
    {
        pf->usEc1 = pu->usEc1;
        pf->usEc2 = pu->usEc2;
        pf->ucPm  = pu->ucPm;
        pf->ucPn  = pu->ucPn;

        /*
         *     ��������¼���¼����Y�������м��㹫ʽ��
         *     (1)��Pm��Pnʱ��Y= Pn-Pm
         *     (2)��Pm��Pnʱ��Y= 256��Pn-Pm
         */
        
        if((pf->ucPm) < (pf->ucPn))
        {
            ucN = (pf->ucPn) - (pf->ucPm);
        }
        else
        {
            ucN = 256 + (pf->ucPn) - (pf->ucPm);
        }

        usLen += (sizeof(UINT16) + sizeof(UINT8)) * 2;

        // �¼���¼��Ϣ
        pucTmp = &(pf->ucT1);
        for(i = 0; i < ucN; i++)
        {
            // type
            *pucTmp  = (UINT8)(pu->sErc[i].eType);

            // le
            pucLe = ++pucTmp;
            usLen += 2;
            
            // ����¼����ݽṹת������
            pFunc = pMcGetRec(pu->sErc[i].eType);

            if(!pFunc)
            {
                #ifdef MC_DBG
                MCDBG("emc_trans_afn14f1_s2m() para pFunc is NULL!");
                #endif
                return MC_ERR_NULL;
            }
            
            // rec
            pucTmp++;

            eRet = pFunc(eTrans, &(pu->sErc[i].uRec), &pucTmp, &usLe);
            if(MC_OK != eRet)
            {
                #ifdef MC_DBG
                MCDBG("emc_trans_afn14f1_s2m() pFunc() error %d!", eRet);
                #endif
                return eRet;
            }

            // le
            *pucLe = (UINT8)usLe;
                        
            // ������һ��λ��
            pucTmp += usLe;

            // ���㳤��
            usLen += usLe;
        }
    }
    // ��֡�ൽ�û���
    else if (MC_TRANS_F2U == eTrans)
    {
        pu->usEc1 = pf->usEc1;
        pu->usEc2 = pf->usEc2;
        pu->ucPm  = pf->ucPm;
        pu->ucPn  = pf->ucPn;

        /*
         *     ��������¼���¼����Y�������м��㹫ʽ��
         *     (1)��Pm��Pnʱ��Y= Pn-Pm
         *     (2)��Pm��Pnʱ��Y= 256��Pn-Pm
         */
        
        if((pf->ucPm) < (pf->ucPn))
        {
            ucN = (pf->ucPn) - (pf->ucPm);
        }
        else
        {
            ucN = 256 + (pf->ucPn) - (pf->ucPm);
        }

        usLen += (sizeof(UINT16) + sizeof(UINT8)) * 2;

        // �¼���¼��Ϣ
        pucTmp = &(pf->ucT1);
        for(i = 0; i < ucN; i++)
        {
            // type
            pu->sErc[i].eType = (eMcErc)*pucTmp;

            // le
            pucLe = ++pucTmp;
            usLen += 2;
            
            // ����¼����ݽṹת������
            pFunc = pMcGetRec(pu->sErc[i].eType);

            if(!pFunc)
            {
                #ifdef MC_DBG
                MCDBG("emc_trans_afn14f1_s2m() para pFunc is NULL!");
                #endif
                return MC_ERR_NULL;
            }
            
            // rec
            pucTmp++;

            eRet = pFunc(eTrans, &(pu->sErc[i].uRec), &pucTmp, &usLe);
            if(MC_OK != eRet)
            {
                #ifdef MC_DBG
                MCDBG("emc_trans_afn14f1_s2m() pFunc() error %d!", eRet);
                #endif
                return eRet;
            }

            // le
            if(*pucLe == usLe)
            {
                #ifdef MC_DBG
                MCDBG("emc_trans_afn14f1_s2m() usLe is not equel! fLe = %d, uLe = %d", *pucLe, usLe);
                #endif
                return MC_ERR_OUTRNG;
            }
                        
            // ������һ��λ��
            pucTmp += usLe;

            // ���㳤��
            usLen += usLe;
        }
    }
    else
    {
         #ifdef MC_DBG
         MCDBG("emc_trans_erc_20() eTrans is out of range!");
         #endif
         return MC_ERR_OUTRNG;    
    }

    // �������
    *pusLen = usLen;
    return MC_OK;
}

/*****************************************************************************
 �� �� ��  : emc_trans_afn14f2_s2m
 ��������  : ���ݽṹת������
 ��Ӧ����  : MCMD_AFN_E_F1_EVENT_1
 �������  : eMcTrans eTrans  
             void* pUser      
             void* pFrame     
             UINT16* pusLen   
 �������  : ��
 �� �� ֵ  : 
 ���ú���  : 
 ��������  : 
 
 �޸���ʷ      :
  1.��    ��   : 2013��11��20��
    ��    ��   : liming
    �޸�����   : �����ɺ���

*****************************************************************************/
eMcErr emc_trans_afn14f2_s2m(eMcTrans eTrans, void* pUser, void* pFrame, UINT16* pusLen)
{
    return emc_trans_afn14f1_s2m(eTrans, pUser, pFrame, pusLen); 
}

/*****************************************************************************
 �� �� ��  : emc_trans_afn14f3_s2m
 ��������  : ���ݽṹת������
 ��Ӧ����  : MCMD_AFN_E_F3_EVENT_3
 �������  : eMcTrans eTrans  
             void* pUser      
             void* pFrame     
             UINT16* pusLen   
 �������  : ��
 �� �� ֵ  : 
 ���ú���  : 
 ��������  : 
 
 �޸���ʷ      :
  1.��    ��   : 2013��11��20��
    ��    ��   : liming
    �޸�����   : �����ɺ���

*****************************************************************************/
eMcErr emc_trans_afn14f3_s2m(eMcTrans eTrans, void* pUser, void* pFrame, UINT16* pusLen)
{
    eMcErr           eRet = MC_OK;
    sMcAfn14f3A       *pu = NULL;
    sMcAfn14f3A_f     *pf = NULL;
    pMcFunc         pFunc = NULL;
    UINT8         *pucTmp = NULL;
    UINT8          *pucLe = NULL;
    UINT16           usLe = 0;
    UINT8             ucN = 0;     // �¼���¼����
    UINT8             ucM = 0;     // �¼���¼����
    UINT16          usLen = 0;     // ͳ��֡�౨���ֳ�
    INT32               i = 0;
    INT32               j = 0;
    
    if(!pUser || !pFrame || !pusLen)
    {
        #ifdef MC_DBG
        MCDBG("emc_trans_afn14f3_s2m() para pointer is null!");
        #endif
        return MC_ERR_NULL;
    }

    pu = (sMcAfn14f3A*)pUser;
    pf = (sMcAfn14f3A_f*)pFrame;

    // �û��ൽ��֡��
    if(MC_TRANS_U2F == eTrans)
    {
        ucN = pu->ucN;
        pf->ucN = ucN;
        usLen += sizeof(UINT8);

        // �¼���¼��Ϣ
        pucTmp = &(pf->ucErc1);

        for(i = 0; i < ucN; i++)
        {
            // ucErc1
            *pucTmp++ = (UINT8)(pu->sErc[i].eType);
            usLen += sizeof(UINT8);
            
            // M
            ucM = pu->sErc[i].ucM; 
            *pucTmp++ = ucM;
            usLen += sizeof(UINT8);
            
            // le
            pucLe = pucTmp++;
            usLen += sizeof(UINT8);
            
            // ����¼����ݽṹת������
            pFunc = pMcGetRec(pu->sErc[i].eType);
            if(!pFunc)
            {
                #ifdef MC_DBG
                MCDBG("emc_trans_afn14f3_s2m() para pFunc is NULL!");
                #endif
                return MC_ERR_NULL;
            } 
            
            for(j = 0; j < ucM; j++)
            {
                eRet = pFunc(eTrans, &(pu->sErc[i].uRec[j]), &pucTmp, &usLe);
                if(MC_OK != eRet)
                {
                    #ifdef MC_DBG
                    MCDBG("emc_trans_afn14f3_s2m() pFunc() error %d!", eRet);
                    #endif
                    return eRet;
                }

                pucTmp += usLe;

                // ���㳤��
                usLen += usLe;
            }
            
            // le
            *pucLe = (UINT8)usLe;
        }
    }
    // ��֡�ൽ�û���
    else if (MC_TRANS_F2U == eTrans)
    {
        // ucN
        ucN = pf->ucN;
        pu->ucN = ucN;
        usLen += sizeof(UINT8);

        // �¼���¼��Ϣ
        pucTmp = &(pf->ucErc1);
        
        for(i = 0; i < ucN; i++)
        {
            // type
            pu->sErc[i].eType = (eMcErc)(*pucTmp++);
            usLen += sizeof(UINT8);

            // M
            ucM = *pucTmp++;
            pu->sErc[i].ucM = ucM;
            usLen += sizeof(UINT8);
            
            // le
            pucLe = pucTmp++;
            usLen += sizeof(UINT8);

            // ����¼����ݽṹת������
            pFunc = pMcGetRec(pu->sErc[i].eType);

            if(!pFunc)
            {
                #ifdef MC_DBG
                MCDBG("emc_trans_afn14f3_s2m() para pFunc is NULL!");
                #endif
                return MC_ERR_NULL;
            }
            
            for(j = 0; j < ucM; j++)
            {
                eRet = pFunc(eTrans, &(pu->sErc[i].uRec[j]), &pucTmp, &usLe);
                if(MC_OK != eRet)
                {
                    #ifdef MC_DBG
                    MCDBG("emc_trans_afn14f3_s2m() pFunc() error %d!", eRet);
                    #endif
                    return eRet;
                }

                pucTmp += usLe;

                // le
                if(*pucLe == usLe)
                {
                    #ifdef MC_DBG
                    MCDBG("emc_trans_afn14f3_s2m() usLe is not equel! fLe = %d, uLe = %d", *pucLe, usLe);
                    #endif
                    return MC_ERR_OUTRNG;
                }
            
                // ���㳤��
                usLen += usLe;
            }
        }
    }
    else
    {
         #ifdef MC_DBG
         MCDBG("emc_trans_afn14f3_s2m() eTrans is out of range!");
         #endif
         return MC_ERR_OUTRNG;    
    }

    // �������
    *pusLen = usLen;
    return MC_OK;
}
/*****************************************************************************
 �� �� ��  : ucmc_get_check_sum
 ��������  : ����У��ͺ���(У�����ȫ���û����ݵ�������,�����ǽ�λ(ģ256))
             �û�������:
             (1)������C
             (2)��ַ��A
             (3)��·�û�����

 �������  : UINT8 *pStartPos
             UINT16 usLen
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��1��16��
    ��    ��   : liming
    �޸�����   : �����ɺ���

*****************************************************************************/
UINT8 ucmc_get_check_sum(UINT8 *pStartPos, UINT16 usLen)
{
    UINT8 ucCheckSum = 0;
    int i = 0;

    for(i = 0; i < usLen; i++)
    {
        ucCheckSum += pStartPos[i];
    }

    return ucCheckSum;
}

/*****************************************************************************
 �� �� ��  : eMcInit
 ��������  : Э���ʼ��
 �������  : sMcInit* sInit
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��10��25�� ������
    ��    ��   : liming
    �޸�����   : �����ɺ���

*****************************************************************************/
eMcErr eMcInit(sMcInit* psInit)
{
    if(g_bMcInit == TRUE)
    {
        return MC_OK;
    }

    if(!psInit)
    {
        #ifdef MC_DBG
        MCDBG("eMcInit() pointer is null!");
        #endif
        return MC_ERR_NULL;
    }

    if(MC_ROLE_MASTER != psInit->eRole && MC_ROLE_CONTOR != psInit->eRole)
    {
        #ifdef MC_DBG
        MCDBG("eMcInit() para error!");
        #endif
        return MC_ERR_PARA;
    }

    g_ucMcPermitDelayMinutes = psInit->ucPermitDelayMinutes;
    g_eMcRole = psInit->eRole;

    #if MC_CFG_SPT_CON
    if(psInit->eRole == MC_ROLE_CONTOR)
    {
        g_sMcEc.usEC1 = 0;
        g_sMcEc.usEC2 = 0;
    }
    #endif

    //pw
    #if MC_CFG_SPT_MST
    memcpy(g_aucMcPw, psInit->aucPw, MC_PW_LEN);
    #endif

    // ����������㷨
#if MC_CFG_ENCRYPT
    g_peMcEncryptFunc = psInit->EncryptFunc;  // ���ܽӿ�
    g_peMcDecryptFunc = psInit->DecryptFunc;  // ���ܽӿ�
#endif

    g_bMcInit = TRUE;
    return MC_OK;
}

/*****************************************************************************
 �� �� ��  : emcIsValidPack
 ��������  : �ж�һ��֡�Ƿ�����Ч��֡, �������ȷ�ķ������ǹ̶�֡���ǿɱ�֡
 �������  : const UINT8* pInBuf
             UINT16 usLen

 �������  : BOOL *pbFiexed
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��10��25�� ������
    ��    ��   : liming
    �޸�����   : �����ɺ���

*****************************************************************************/
eMcErr emcIsValidPack(const UINT8* pInBuf, UINT16 usLen, BOOL *pbFiexed)
{
    UINT8  ucFrmCS       = 0;    // ֡�еļ����
    UINT8  ucCalCS       = 0;    // ���������У���
    UINT8  uc0x16        = 0;    // ֡������
    UINT16 usUserLen     = 0;
    UINT8  ucHead        = 0;

    sMcfHeadFixed *psHeadFixed = NULL;
    sMcfHeadAlter *psHeadAlter = NULL;

    if(!pInBuf || !pbFiexed)
    {
       #ifdef MC_DBG
       MCDBG("emcIsValidPack() pointer is null!");
       #endif
       return MC_ERR_NULL;
    }

    if(MC_FRM_LEN_MIN > usLen)
    {
        #ifdef MC_DBG
        MCDBG("emcIsValidPack() frame is not completed!");
        #endif
        return MC_ERR_UNCOMP;
    }

    ucHead = (UINT8)(*pInBuf);

    // �̶�֡
    if(MC_STCHAR_FIXED == ucHead)
    {
        psHeadFixed = (sMcfHeadFixed *)pInBuf;

        if(MC_PROTO_VERSION != psHeadFixed->ucV)
        {
            #ifdef MC_DBG
            MCDBG("emcIsValidPack() proto version is error!");
            #endif
            return MC_ERR_PROTO;
        }

        // ֡�е�ʵ��У���
        ucFrmCS = psHeadFixed->ucS;

        // ���������У���
        ucCalCS = ucmc_get_check_sum((UINT8*)&(psHeadFixed->usC), MC_FIXED_USR_LEN);

        // ������
        //uc0x16 = psHeadFixed->ucE;

        // �������
        *pbFiexed = TRUE;
    }
    // �ɱ�֡
    else if(MC_STCHAR_ALTER == ucHead)
    {
        psHeadAlter = (sMcfHeadAlter *)pInBuf;
        if(0x68 != psHeadAlter->f68 || 0x68 != psHeadAlter->s68)
        {
            #ifdef MC_DBG
            MCDBG("emcIsValidPack() start chart 0x68 is error!");
            #endif
            return MC_ERR_0x68;
        }

        // L1 L2
        if(psHeadAlter->usL1 != psHeadAlter->usL2)
        {
            #ifdef MC_DBG
            MCDBG("emcIsValidPack() L1 and L2 is not equal!");
            #endif
            return MC_ERR_L1L2;
        }
        else
        {
            usUserLen = psHeadAlter->usL1;
            if(usLen < (usUserLen + MC_ALTER_BUT_USER_LEN))
            {
                #ifdef MC_DBG
                MCDBG("emcIsValidPack() frame is not completed!");
                #endif
                return MC_ERR_UNCOMP;
            }
        }

        // ֡�е�ʵ��У���
        ucFrmCS =  *(UINT8*)((UINT8*)&(psHeadAlter->usC) + usUserLen);

        // ���������У���
        ucCalCS = ucmc_get_check_sum((UINT8*)&(psHeadAlter->usC), usUserLen);

        // ������
        uc0x16 = *(UINT8*)((UINT8*)&(psHeadAlter->usC) + usUserLen + 1);

        // �������
        *pbFiexed = FALSE;
    }
    else
    {
        #ifdef MC_DBG
        MCDBG("emcIsValidPack() is not gbnx31 frame!");
        #endif
        return MC_ERR_PACK;
    }

    // У���
    if(ucCalCS != ucFrmCS)
    {
        #ifdef MC_DBG
        MCDBG("emcIsValidPack() check sum is error! CalCS = %02X, FrmCS = %02X", ucCalCS, ucFrmCS);
        #endif
        return MC_ERR_CS;
    }

    // ������(ֻ�ɱ�֡�н�����)
    if(MC_STCHAR_ALTER == ucHead)
    {
        if(MC_FRM_END_CHAR != uc0x16)
        {
            #ifdef MC_DBG
            MCDBG("emcIsValidPack() end char 0x16 is error!");
            #endif
            return MC_ERR_0x16;
        }
    }
    
    return MC_OK;
}

/*****************************************************************************
 �� �� ��  : emcFindValidPack
 ��������  : �ҵ���һ����Ч֡��λ�ò������䳤��
 �������  : UINT8* pinBuf        
             UINT16 usLen         
             UINT16* pusFirstOff  
             UINT16* pusFirstLen  
 �������  : ��
 �� �� ֵ  : 
 ���ú���  : 
 ��������  : 
 
 �޸���ʷ      :
  1.��    ��   : 2013��11��21��
    ��    ��   : liming
    �޸�����   : �����ɺ���

*****************************************************************************/
eMcErr emcFindValidPack(UINT8* pinBuf, UINT16 usLen, UINT16* pusFirstOff, UINT16* pusFirstLen)
{
    eMcErr       eRet = MC_OK;  
    INT32           i = 0; 
    INT32           j = 0;
    UINT16 usValidLen = 0;
    BOOL       bFixed = FALSE;
    
    if(!pinBuf || !pusFirstOff || !pusFirstLen)
    {
        #ifdef MC_DBG
        MCDBG("emcFindValidPack() para pointer is null!");
        #endif
        return MC_ERR_NULL;
    }

    if(usLen < MC_FRM_LEN_MIN)
    {
        #ifdef MC_DBG
        MCDBG("emcFindValidPack() frame is not complete usLen = %d!", usLen);
        #endif
        return MC_ERR_UNCOMP;
    }
    
    for(i = 0; i < usLen; i++)
    {
        // �̶�֡
        if(MC_STCHAR_FIXED == pinBuf[i])
        {
             eRet = emcIsValidPack((UINT8*)(pinBuf + i), MC_FRM_LEN_MIN, &bFixed);
             if(MC_OK == eRet)
             {
                 *pusFirstOff = i;
                 *pusFirstLen = MC_FRM_LEN_MIN;
                 return MC_OK;
             }
        }
        
        // �ɱ�֡
        if(MC_STCHAR_ALTER == pinBuf[i])
        {   
            // �ж��������ֽ�λ���ǲ���0x68 usLen
            if(MC_STCHAR_ALTER == pinBuf[i+5])
             {
                for(j = i+6; j < usLen; j++)
                {
                    if(pinBuf[j] == MC_FRM_END_CHAR)
                    {    
                        usValidLen = j + 1;
                        eRet = emcIsValidPack((UINT8*)(pinBuf + i), usValidLen, &bFixed);
                        if(MC_OK == eRet)
                        {
                            *pusFirstOff = i;
                            *pusFirstLen = usValidLen;
                            return MC_OK;
                        }
                    }
                }

                continue;
            }
        }
    }

    return MC_ERR_NONE;
}

/*****************************************************************************
 �� �� ��  : emc_pack_common
 ��������  : �������� ���ķ�װ����
 �������  : sMcPackCommon *psCommon

 �������  : UINT16 *pusLen     ��װ���֡��
             UINT8  *pOutBuf    ��װ���֡����
             pusLen pOutBuf ���û�����ռ�
 �� �� ֵ  :
 ���ú���  :
 ��������  : emcLitePack

 �޸���ʷ      :
  1.��    ��   : 2013��10��25�� ������
    ��    ��   : liming
    �޸�����   : �����ɺ���

*****************************************************************************/
eMcErr emc_pack_common(sMcPackCommon *psCommon,  UINT16 *pusLen, UINT8  *pOutBuf)
{
    eMcErr        eRet         = MC_OK;
    UINT16        usBufLen     = 0;
    UINT16        usUsrLen     = 0;      // �û�������(������C����ַ��A����·�û�����D)�ֳ�
    BOOL          bFixed       = FALSE;  // �Ƿ�Ϊ�̶�֡
    UINT8         *pA2CsData   = NULL;
    UINT8         *pucCS       = NULL;   // ���ڼ���CS
    sMcfHeadFixed *psHeadFixed = NULL;
    sMcfHeadAlter *psHeadAlter = NULL;
    UINT16        usC          = 0;      // ������C
    sMcA_f        stA;                   // ��ַ��A

    if(!psCommon || !pusLen || !pOutBuf)
    {
        #ifdef MC_DBG
        MCDBG("emc_pack_common() pointer is null!");
        #endif
        return MC_ERR_NULL;
    }

    /*
    if(g_bMcInit != TRUE)
    {
        #ifdef MC_DBG
        MCDBG("emc_pack_common() protocol is not init!");
        #endif
        return MC_ERR_INIT;
    }
   */

    // ֡���Ƿ���
    if(psCommon->usA2CsLen > MC_SEQ2CS_MAX)
    {
        #ifdef MC_DBG
        MCDBG("emc_pack_common() usAddr2CsLen out of range! len =  %d", psCommon->usA2CsLen);
        #endif
        return MC_ERR_OUTRNG;
    }

    if(!(psCommon->pA2CsData))
    {
        #ifdef MC_DBG
        MCDBG("emc_pack_common() pAddr2CsData pointer is null!");
        #endif
        return MC_ERR_A2CS;
    }

    // �̶�֡
    bFixed = psCommon->bFixed;
    if(TRUE == bFixed)
    {
        psHeadFixed = (sMcfHeadFixed*)pOutBuf;

        // 10H
        psHeadFixed->f10 = MC_STCHAR_FIXED;

        // ctrl
        eRet = emc_trans_ctrl(MC_TRANS_U2F, &(psCommon->sCtrl), &usC);
        if(MC_OK != eRet)
        {
            #ifdef MC_DBG
            MCDBG("emc_pack_common()-> emc_trans_ctrl() error: %d!", eRet);
            #endif
            return eRet;
        }

        psHeadFixed->usC = usC;
        // address
        eRet = emc_trans_address(MC_TRANS_U2F, &(psCommon->sAddress), &stA);
        if(MC_OK != eRet)
        {
            #ifdef MC_DBG
            MCDBG("emc_pack_common()-> emc_trans_address() error: %d!", eRet);
            #endif
            return eRet;
        }

        psHeadFixed->stA = stA;
            
        // �����û����� (�̶�֡�н�һ�ֽڵ�Э��汾) �ϲ�����Ѿ���ֵ
        psHeadFixed->ucV = MC_PROTO_VERSION;

        // У���CS
        usUsrLen = MC_FIXED_USR_LEN;
        psHeadFixed->ucS = ucmc_get_check_sum((UINT8*)&(psHeadFixed->usC), usUsrLen);
    
        // ֡����
        usBufLen = MC_FIXED_LEN;
        psHeadFixed->ucE = MC_FRM_END_CHAR;
    }
    // �ɱ�֡
    else
    {
        psHeadAlter = (sMcfHeadAlter*)pOutBuf;

        // ��ʼ�ַ�
        psHeadAlter->f68 = MC_STCHAR_ALTER;
        psHeadAlter->s68 = MC_STCHAR_ALTER;

        // L1 L2(������C����ַ��A����·�û����� �ֽ��ܳ�)
        usUsrLen = psCommon->usA2CsLen + MC_ALTER_USR_OTHER_LEN;
        psHeadAlter->usL1 = usUsrLen;
        psHeadAlter->usL2 = usUsrLen;

        // ctrl
        eRet = emc_trans_ctrl(MC_TRANS_U2F, &(psCommon->sCtrl), &usC);
        if(MC_OK != eRet)
        {
            #ifdef MC_DBG
            MCDBG("emc_pack_common()-> emc_trans_ctrl() error: %d!", eRet);
            #endif
            return eRet;
        }

        psHeadAlter->usC = usC;
        
        // address
        eRet = emc_trans_address(MC_TRANS_U2F, &(psCommon->sAddress), &stA);
        if(MC_OK != eRet)
        {
            #ifdef MC_DBG
            MCDBG("emc_pack_common()-> emc_trans_address() error: %d!", eRet);
            #endif
            return eRet;
        }

        psHeadAlter->stA = stA;

        // �����û����� (�̶�֡�н�һ�ֽڵ�Э��汾)
        psHeadAlter->ucV = MC_PROTO_VERSION;

        // AC �����ϲ��ʼ��
        // �û�������
        pA2CsData = (UINT8*)&(psHeadAlter->ucV);
        memcpy((void*)pA2CsData, (void*)(psCommon->pA2CsData), psCommon->usA2CsLen);

        // У���CS
        pucCS  = (UINT8*)(pA2CsData + psCommon->usA2CsLen);
        *pucCS = ucmc_get_check_sum((UINT8*)&(psHeadAlter->usC), usUsrLen);
        
        // ֡����
        usBufLen = psCommon->usA2CsLen + MC_ALTER_OTHER_LEN;

        // ������
        *(pucCS+1) = MC_FRM_END_CHAR;
    }

    // �������
    *pusLen = usBufLen;
    return MC_OK;
}

/*****************************************************************************
 �� �� ��  : emc_unpack_common
 ��������  : �������Ľ���
 �������  : sMcPackCommon *psUnpack  
             UINT8* pInBuf            
             UINT16 usLen             
 �������  : sMcPackCommon *psUnpack
 �� �� ֵ  : 
 ���ú���  : 
 ��������  : 
 
 �޸���ʷ      :
  1.��    ��   : 2013��10��31��
    ��    ��   : liming
    �޸�����   : �����ɺ���

*****************************************************************************/
eMcErr emc_unpack_common(sMcPackCommon *psUnpack, UINT8* pInBuf, UINT16 usLen)
{
    BOOL          bFixed          = FALSE;    // �Ƿ�Ϊ�̶�֡
    sMcfHeadFixed *psHeadFixed    = NULL;
    sMcfHeadAlter *psHeadAlter    = NULL;
    eMcErr        eRet            = MC_OK;
    sMcA_f        stA_f;     
    UINT16        usC_f           = 0;        // ������C

    if(!psUnpack || !psUnpack || !usLen)
    {
        #ifdef MC_DBG
        MCDBG("emc_unpack_common() pointer is null!");
        #endif
        return MC_ERR_NULL;
    }

    memset(&stA_f, 0, sizeof(sMcA_f));
    
    eRet = emcIsValidPack(pInBuf, usLen, &bFixed);
    if(MC_OK != eRet)
    {
        #ifdef MC_DBG
        MCDBG("emc_unpack_common() is not a valid frame %d!", eRet);
        #endif
        return eRet;
    }

    psUnpack->bFixed = bFixed;
    
    // �̶�֡
    if(TRUE == bFixed)
    {
        psHeadFixed = (sMcfHeadFixed *)pInBuf;

        // addr
        stA_f = psHeadFixed->stA;
        eRet = emc_trans_address(MC_TRANS_F2U, &(psUnpack->sAddress), &stA_f);
        if(MC_OK != eRet)
        {
            #ifdef MC_DBG
            MCDBG("emc_unpack_common() emc_trans_address() error %d!", eRet);
            #endif
            return eRet;     
        }

        // ������C
        usC_f = psHeadFixed->usC;
        eRet  = emc_trans_ctrl(MC_TRANS_F2U, &(psUnpack->sCtrl), &usC_f);
        if(MC_OK != eRet)
        {
            #ifdef MC_DBG
            MCDBG("emc_unPack_base()-> emc_trans_ctrl() error eRet = %d", eRet);
            #endif
            return eRet;
        }

        psUnpack->usA2CsLen = 1;
        psUnpack->pA2CsData = &(psHeadFixed->ucV);
        
    }
    // �ɱ�֡
    else
    {
        psHeadAlter = (sMcfHeadAlter *)pInBuf;

        // addr
        stA_f = psHeadAlter->stA;
        eRet = emc_trans_address(MC_TRANS_F2U, &(psUnpack->sAddress), &stA_f);
        if(MC_OK != eRet)
        {
            #ifdef MC_DBG
            MCDBG("emc_unpack_common() emc_trans_address() error %d!", eRet);
            #endif
            return eRet;     
        }

        // ������C
        usC_f = psHeadAlter->usC;
        eRet = emc_trans_ctrl(MC_TRANS_F2U, &(psUnpack->sCtrl), &usC_f);
        if(MC_OK != eRet)
        {
            #ifdef MC_DBG
            MCDBG("emc_unPack_base()-> emc_trans_ctrl() error eRet = %d", eRet);
            #endif
            return eRet;
        }

        psUnpack->usA2CsLen = psHeadAlter->usL1 - MC_CA_LEN;
        psUnpack->pA2CsData = &(psHeadAlter->ucV);
        
    }
    
    return MC_OK;
}

/*****************************************************************************
 �� �� ��  : bmc_is_0xEE
 ��������  : �ж�usLen����pData���������Ƿ���0xEE
 �������  : UINT8* pData
             UINT16 usLen
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��11��12�� ����һ
    ��    ��   : liming
    �޸�����   : �����ɺ���

*****************************************************************************/
BOOL   bmc_is_0xEE(UINT8* pData, UINT16 usLen)
{
    if(!pData)
    {
        return FALSE;
    }

    INT32 i = 0;
    for(i = 0; i < usLen; i++)
    {
        if(0xEE != pData[i])
        {
            return FALSE;
        }
    }

    return TRUE;
}

/*****************************************************************************
 �� �� ��  : vmc_set_0xEE
 ��������  : ��usLen������pData�����ݶ�����Ϊ0xEE
 �������  : UINT8* pData
             UINT16 usLen
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��8��12�� ����һ
    ��    ��   : liming
    �޸�����   : �����ɺ���

*****************************************************************************/
void   vmc_set_0xEE(UINT8* pData, UINT16 usLen)
{
    INT32 i = 0;

    if(!pData)
    {
        return;
    }

    for(i = 0; i < usLen; i++)
    {
        pData[i] = 0xEE;
    }
}

/*****************************************************************************
 �� �� ��  : bmc_is_none
 ��������  : �Ƿ�һ��������Ϊȱʡ
 �������  : UINT8* pData
             UINT16 usLen
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��8��12�� ����һ
    ��    ��   : liming
    �޸�����   : �����ɺ���

*****************************************************************************/
BOOL   bmc_is_none(UINT8* pData, UINT16 usLen)
{
    return bmc_is_0xEE(pData, usLen);
}

/*****************************************************************************
 �� �� ��  : vmc_set_none
 ��������  : ��ĳ����������Ϊȱʡ
 �������  : UINT8* pData
             UINT16 usLen
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��8��12�� ����һ
    ��    ��   : liming
    �޸�����   : �����ɺ���

*****************************************************************************/
void   vmc_set_none(UINT8* pData, UINT16 usLen)
{
    vmc_set_0xEE(pData, usLen);
}

/*****************************************************************************
 �� �� ��  : bmc_have_ec
 ��������  : ���౨�����Ƿ�Ӧ�ú���ec�ֶ�
 �������  : eMcAFN eAFN
             eMcDir eDir
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��2��27��
    ��    ��   : liming
    �޸�����   : �����ɺ���

*****************************************************************************/
BOOL   bmc_have_ec(eMcAFN eAFN, eMcDir eDir)
{
    if(MC_DIR_S2M == eDir)
    {
        if(MC_AFN_15_FILE == eAFN || 
           MC_AFN_06_AUTH == eAFN)
        {
            return FALSE;
        }
    }
    else
    {
        return FALSE;
    }

    return TRUE;
}

/*****************************************************************************
 �� �� ��  : bmc_have_pw
 ��������  : �˱������Ƿ�Ӧ�û���pw�ֶ�
 �������  : eMcAFN eAFN
             eMcDir eDir
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��2��27��
    ��    ��   : liming
    �޸�����   : �����ɺ���

*****************************************************************************/
BOOL   bmc_have_pw(eMcAFN eAFN, eMcDir eDir)
{
    if((MC_DIR_M2S == eDir)  &&
        (MC_AFN_01_RSET == eAFN  ||
         MC_AFN_04_SETP == eAFN  ||
         MC_AFN_05_CTRL == eAFN  ||
         MC_AFN_16_DATA == eAFN  ||
        (MC_AFN_06_AUTH == eAFN)) )          // ˫�������֤�����ж���PW
    {
        return TRUE;
    }

    return FALSE;
}

/*****************************************************************************
 �� �� ��  : bmc_have_tp
 ��������  : �˱���(�� eRole ���͵ı���)���Ƿ�Ӧ�û���tp�ֶ�
             Ŀǰ���б��ĸ�ʽĬ������¶���TP
 �������  : eMcAFN eAFN
             eMcDir eDir
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��2��27��
    ��    ��   : liming
    �޸�����   : �����ɺ���

*****************************************************************************/
BOOL  bmc_have_tp(eMcAFN eAFN, eMcDir eDir)
{
    if(MC_CFG_TP == 1)
    {
        // �������û��tp
        if(MC_AFN_08_CASC == eAFN && MC_DIR_M2S == eDir)
        {
            return FALSE;
        }
        
        return TRUE;
    }
    else
    {
        return FALSE;
    }        
}

/*****************************************************************************
 �� �� ��  : vmc_set_ec
 ��������  : �����¼���������ֵ
 �������  : sMcEc *psEc  
 �������  : ��
 �� �� ֵ  : 
 ���ú���  : 
 ��������  : 
 
 �޸���ʷ      :
  1.��    ��   : 2013��11��28��
    ��    ��   : liming
    �޸�����   : �����ɺ���

*****************************************************************************/
void vmc_set_ec(sMcEc *psEc)
{
    if(!psEc)
    {
        #ifdef MC_DBG
        MCDBG("vmc_set_ec() pointer is null!");
        #endif
        return;
    }

    g_sMcEc.usEC1 = psEc->usEC1;
    g_sMcEc.usEC2 = psEc->usEC2;
}   

/*****************************************************************************
 �� �� ��  : usmc_get_aux_len
 ��������  : ��õ�ǰ���͵ı����и���������ֳ�(ec pw tp)
 �������  : eMcAFN eAFN
             eMcDir eDir
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��10��29�� ���ڶ�
    ��    ��   : liming
    �޸�����   : �����ɺ���

*****************************************************************************/
UINT16 usmc_get_aux_len(eMcAFN eAFN, eMcDir eDir, BOOL bEc, BOOL bTp)
{
    UINT16 usAuxLen = 0;

    BOOL   bPw = FALSE;

    bPw = bmc_have_pw(eAFN, eDir);

    if(TRUE == bEc)
    {
        usAuxLen += sizeof(sMcEc);
    }

    if(TRUE == bPw)
    {
    usAuxLen += MC_PW_LEN;
    }

    if(TRUE == bTp)
    {
        usAuxLen += sizeof(sMcTp_f);
    }

    return usAuxLen;
}

/*****************************************************************************
 �� �� ��  : emc_pack_base
 ��������  : ʵ�ֻ����ı��ķ�װ, ��Ӧ��һ�����ݵ�Ԫ��ʶ, ֮�����64�����ݵ�Ԫ
             ��������㷨�ӿ�,�ô���Ӧ�ò����ݼ��� ���ܺ���ܿ��ܻ�ı䳤��,
             ���ܵ�������������Ӧ�ò㹦���롢���ݵ�Ԫ��ʶ�����ݵ�Ԫ����
             Ӧ�ò������,���ϲ㴫��Ŀռ�,�����ȽϽ�ʡ�ڴ�

 �������  : smcBaskPack* psPack

 �������  : UINT16* pusLen
             UINT8* pOutBuf
 �� �� ֵ  :
 ���ú���  : emc_pack_common()
 ��������  : emcPack()

 �޸���ʷ      :
  1.��    ��   : 2013��10��25�� ������
    ��    ��   : liming
    �޸�����   : �����ɺ���

*****************************************************************************/
eMcErr emc_pack_base(smcBaskPack* psPack, UINT8* pOutBuf, UINT16* pusLen)
{

    eMcErr         eRet        = MC_OK;
    eMcmd          eCmd        = MCMD_AFN_F_UNKOWN;
    eMcDir         eDir        = MC_DIR_UNKOWN;
    eMcAFN         eAFN        = MC_AFN_NULL;
    BOOL           bSameTeam   = FALSE;
    BOOL           bP0         = FALSE;
    UINT8          ucPnNum     = 0;
    UINT16         usA2CsLen   = 0;
    UINT16         usA2CsPos   = 0;
    UINT16         usfDataLen  = 0;      // ֡�����ݵ�Ԫ�ֳ�
    UINT16         usCMD       = 0;
    INT32          i           = 0;
    INT32          j           = 0;
    INT32          fi          = 0;
    INT32          pi          = 0;
    UINT8*         pA2Cs       = NULL;   // ��·�û����ݲ�
    UINT8*         puData      = NULL;   // ���ݵ�Ԫ�û�������
    UINT8*         pData       = NULL;   // ���ݵ�Ԫ
    UINT8*         pUcAc       = NULL;   // �û�������Ac�û���ָ��
    sMcDaDt*       pDaDt       = NULL;   // ���ݵ�Ԫ��ʶ
    sMcTp_f*       psfTp       = NULL;   // ֡��Tp�ֶ�
    pMcFunc        pFunc       = NULL;
    sMcmdInfor     sCmdInfor;
    sMcTp          suTp;                 // �û���Tp�ֶ���Ϣ
    sMcPnFn        sPnFn;
    sMcPackCommon  sPackCommon;

    // ����
    #if MC_CFG_ENCRYPT
    UINT8*         pEncry_in   = NULL;  // ��Ҫ���ܲ��ֵ��׵�ַ ����
    INT32          nLen_in     = 0;     // ���ĵ����ֳ�
    UINT8*         pEncry_out  = NULL;  // ��Ҫ���ܲ��ֵ��׵�ַ ���
    INT32          nLen_out    = 0;     // ���ĵ����ֳ�
    #endif

    memset(&(sPnFn), 0x00, sizeof(sMcPnFn));
    memset(&sPackCommon, 0x00, sizeof(sMcPackCommon));

    if(!psPack || !pusLen || !pOutBuf)
    {
        #ifdef MC_DBG
        MCDBG("emc_pack_base() pointer is null!");
        #endif
        return MC_ERR_NULL;
    }

    if(TRUE != g_bMcInit)
    {
        #ifdef MC_DBG
        MCDBG("emc_pack_base() protocol isn't init!");
        #endif
        return MC_ERR_INIT;
    }

    if(MC_ROLE_MASTER == g_eMcRole)
    {
        eDir = MC_DIR_M2S;
    }
    else
    {
        eDir = MC_DIR_S2M;
    }

    /* ��װsMcPackCommon ��� */
    // ����ͨ�÷������
    pA2Cs = (UINT8*)malloc(MC_A2CS_BYTE_MAX);
    if(!pA2Cs)
    {
        #ifdef MC_DBG
        MCDBG("emc_pack_base() malloc failed!");
        #endif
        return MC_ERR_IO;
    }

    // ������·����������
    // �̶�֡
    if(TRUE == psPack->bFixed)
    {
        // �̶�֡����·�����ݽ�Ϊһ���汾��Ϣ
        *pA2Cs = MC_PROTO_VERSION;
        usA2CsPos += 1;
    }
    // �ɱ�֡
    else
    {
        // Э���ʶ
        *pA2Cs = MC_PROTO_VERSION;
         usA2CsPos += 1;

        // Ӧ�ÿ�����AC
        pUcAc = (UINT8*)(pA2Cs + usA2CsPos);
        eRet  = emc_trans_ac(MC_TRANS_U2F, &(psPack->sAc), pUcAc);
        if(MC_OK != eRet)
        {
            #ifdef MC_DBG
            MCDBG("emc_pack_base() emc_trans_ac error %d!", eRet);
            #endif
            MC_FREE(pA2Cs);
            return eRet;
        }

        usA2CsPos += 1;

        // ��װ�䳤�����ݵ�Ԫ��ʶ�����ݵ�Ԫ��
        if(0 == psPack->usNum)
        {
            #ifdef MC_DBG
            MCDBG("emc_pack_base() usNum is 0!");
            #endif
            MC_FREE(pA2Cs);
            return MC_ERR_PROTO;
        }

        // ��װ����һ�����ݱ�ʶ�����ݵ�Ԫ���
        for(i = 0; i < psPack->usNum; i++)
        {
            for(j = 0; j < MC_PN_INDEX_MAX; j++)
            {
                sPnFn.usPn[j] =  psPack->sData[i].sPnFn.usPn[j];
                sPnFn.ucFn[j] =  psPack->sData[i].sPnFn.ucFn[j];
            }

            // ȷ��ÿ��Pn ������ͬһ����Ϣ����
            bSameTeam = bmc_same_team_pn(sPnFn.usPn, NULL);
            if(FALSE == bSameTeam)
            {
                #ifdef MC_DBG
                MCDBG("emc_pack_base() pn is not is same team!");
                #endif
                MC_FREE(pA2Cs);
                return MC_ERR_TEAM;
            }

            // ȷ��ÿ��Fn ������ͬһ����Ϣ����
            bSameTeam = bmc_same_team_fn(sPnFn.ucFn, NULL);
            if(FALSE == bSameTeam)
            {
                #ifdef MC_DBG
                MCDBG("emc_pack_base() Fn is not is same team!");
                #endif
                MC_FREE(pA2Cs);
                return MC_ERR_TEAM;
            }

            // ��������
            eAFN = psPack->sAc.eAfn;

            // ��װ���ݵ�Ԫ��ʶ
            pDaDt = (sMcDaDt*)(pA2Cs + usA2CsPos);
            eRet = emc_pnfn_to_dadt(&(sPnFn), pDaDt);
            if(MC_OK != eRet)
            {
                #ifdef MC_DBG
                MCDBG("emc_pack_base() emc_pnfn_to_dadt() failed %d %s!", eRet, smcGetErr(eRet));
                #endif
                MC_FREE(pA2Cs);
                return eRet;
            }

            usA2CsPos +=  sizeof(sMcDaDt);
            /*
                �����װ���64����Fn Pn���Ӧ�����ݵ�Ԫ
                ���ݵ�ԪΪ�����ݵ�Ԫ��ʶ����֯�����ݣ���������������ȡ�
                ������֯��˳������Ȱ�pn��С�����ٰ�Fn��С����Ĵ��򣬼������һ����Ϣ��pi
                ��������Ϣ��Fn�Ĵ�����ٽ�����һ��pi+1�Ĵ���
            */

            // ���������
            bP0 = bmc_is_p0(sPnFn.usPn);
            if(TRUE == bP0)
            {
                 ucPnNum = 1;               // 1 - p0
            }
            else
            {
                 ucPnNum = MC_PN_INDEX_MAX; // 2 - �������8��Pn
            }

            // Ӧ�ò�������
            for(pi = 0; pi < ucPnNum; pi++)
            {
                if(MC_PN_NONE != sPnFn.usPn[pi])
                {
                    for(fi = 0; fi < MC_FN_INDEX_MAX; fi++)
                    {
                        if(MC_FN_NONE != sPnFn.ucFn[fi])
                        {
                             // �ϳ�������
                            usCMD = (UINT16)((eAFN << 8) | (sPnFn.ucFn[fi]));
                            eCmd  = (eMcmd)usCMD;

                            // ���������Ϣ
                            eRet = eMcGetCmdInfor(eCmd, eDir, &sCmdInfor);
                            if(MC_OK != eRet)
                            {
                                #ifdef MC_DBG
                                MCDBG("emc_pack_base() eMcGetCmdInfor() failed %d %s!", eRet, smcGetErr(eRet));
                                #endif
                                MC_FREE(pA2Cs);
                                return eRet;
                            }

                            // ���ݵ�Ԫ
                            pData = (UINT8*)(pA2Cs + usA2CsPos);
                            pFunc = sCmdInfor.pFunc;
                            if(NULL != pFunc)
                            {
                                puData = (UINT8*)(psPack->sData[i].puApp[pi][fi]);
                                eRet = pFunc(MC_TRANS_U2F, puData, pData, &usfDataLen);
                                if(MC_OK != eRet)
                                {
                                    #ifdef MC_DBG
                                    MCDBG("emc_pack_base() transU2FpFunc() failed %d %s!", eRet, smcGetErr(eRet));
                                    #endif
                                    MC_FREE(pA2Cs);
                                    return eRet;
                                }

                                usA2CsPos += usfDataLen;
                            }
                        }
                    }
                }
            }
        }

        // ����
        #if MC_CFG_ENCRYPT
        if(NULL != g_peMcEncryptFunc)
        {
            pEncry_in  = pA2Cs;  // ������Ҫ�ٵ���,��ȷ����Ҫ���ܵĲ���
            nLen_in    = usA2CsPos;
            pEncry_out = (UINT8*)malloc(MC_A2CS_BYTE_MAX);
            if(!pEncry_out)
            {
                #ifdef MC_DBG
                MCDBG("emc_pack_base() malloc failed!");
                #endif
                MC_FREE(pA2Cs);
                return MC_ERR_IO;
            }

            eRet = g_peMcEncryptFunc(pEncry_in, nLen_in, pEncry_out, &nLen_out);
            if(MC_OK != eRet)
            {
                #ifdef MC_DBG
                MCDBG("emc_pack_base() encrypt failed! %d", eRet);
                #endif
                MC_FREE(pA2Cs);
                MC_FREE(pEncry_out);
                return MC_ERR_ENCRYPT;
            }

            // �滻������
            memcpy((void*)pA2Cs, (void*)pEncry_out, nLen_out);

            // ���³���
            usA2CsPos = nLen_out;

        }
        #endif

        /* ������Ϣ��AUX */
        // ����� EC (ֻ���������б�����)
        if(MC_DIR_S2M == eDir)
        {
            if(TRUE == psPack->sAc.bEc)
            {
                pData = (UINT8*)(pA2Cs + usA2CsPos);      
                memcpy((void*)pData, (void*)&g_sMcEc, sizeof(sMcEc));              
                usA2CsPos += sizeof(sMcEc);
            }
        }
        else
        {
            // ����� pw
            // pw������Ҫ�����б�����,����վ����,�ն���֤��ͨ����ִ��(16�ֽ�)
            if(TRUE == bmc_have_pw(eAFN, eDir))
            {
                pData = (UINT8*)(pA2Cs + usA2CsPos);
                memcpy((void*)pData, (void*)psPack->aPw, MC_PW_LEN);
                usA2CsPos += MC_PW_LEN;
            }
        }

        // ����� TP
        if(TRUE == psPack->sAc.bTp)
        {
            pData = (UINT8*)(pA2Cs + usA2CsPos);
            psfTp = (sMcTp_f *)pData;
            suTp  = psPack->sTp;
            (void)emc_trans_tp(MC_TRANS_U2F, &suTp, psfTp);
            usA2CsPos += sizeof(sMcTp_f);
        }
        
        // ��� MCMD_AFN_C_F1_FREZ_TEMP ��Ӧ��
        if(MC_AFN_13_ASKR == psPack->sAc.eAfn && 
           MC_PRM_A2P == psPack->sCtrl.ePRM)
        {
            psPack->sAc.eAfn = MC_AFN_12_ASKT;
        }
    }

    // �ܽ�����
    usA2CsLen               = usA2CsPos;
    sPackCommon.sAddress    = psPack->sAddress;
    sPackCommon.sCtrl       = psPack->sCtrl;;
    sPackCommon.usA2CsLen   = usA2CsLen;
    sPackCommon.pA2CsData   = pA2Cs;
    sPackCommon.bFixed      = psPack->bFixed;

    // ͨ��ͨ�÷������pack
    eRet = emc_pack_common(&sPackCommon, pusLen, pOutBuf);
    if(MC_OK != eRet)
    {
        #ifdef MC_DBG
        MCDBG("emc_pack_base() emc_pack_common failed:%s!", smcGetErr(eRet));
        #endif

        MC_FREE(pA2Cs);
        // �ͷż��ܲ���������ڴ�
        #if MC_CFG_ENCRYPT
        MC_FREE(pEncry_out);
        #endif
        return eRet;
    }

    MC_FREE(pA2Cs);

    // �ͷż��ܲ���������ڴ�
    #if MC_CFG_ENCRYPT
    MC_FREE(pEncry_out);
    #endif

    return MC_OK;
}

/*****************************************************************************
 �� �� ��  : vmc_free_base_data
 ��������  : �����ͷ�emc_unPack_base()�����֧��̬������ڴ�, �Է�ֹ�ڴ�й¶

 �������  : sMcBaseData* pBaseData
             INT32 Num
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  : emc_unPack_base

 �޸���ʷ      :
  1.��    ��   : 2013��10��28�� ����һ
    ��    ��   : liming
    �޸�����   : �����ɺ���

*****************************************************************************/
void vmc_free_base_data(sMcBaseData* pBaseData, INT32 Num)
{
    INT32  i       = 0;
    INT32  fi      = 0;
    INT32  pi      = 0;
    uMcApp *pFree = NULL;

    if(!pBaseData || Num <= 0)
    {
        return;
    }

    for(i = 0; i < Num; i++)
    {
       for(pi = 0; pi < 8; pi++)
       {
            for(fi = 0; fi < 8; fi++)
            {
                pFree = pBaseData[i].puApp[pi][fi];
                if(pFree != NULL)
                {
                    free(pFree);
                }
            }
        }
    }
}
/*****************************************************************************
 �� �� ��  : emc_unPack_base
 ��������  : ʵ�ֻ����ı��Ľ��װ, ��������㷨�ӿ�
             �ô���Ӧ�ò����ݽ��� ���ܺ���ܿ��ܻ�ı䳤��,
             ���ܵ�������������Ӧ�ò㹦���롢���ݵ�Ԫ��ʶ�����ݵ�Ԫ����
 �������  : smcBaskPack *psUnpack
             UINT8* pInBuf
             UINT16 usLen
 �������  : ��
 �� �� ֵ  :
 ���ú���  : emcUnPack
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��10��28�� ����һ
    ��    ��   : liming
    �޸�����   : �����ɺ���

*****************************************************************************/
eMcErr emc_unPack_base(smcBaskPack *psUnpack, UINT8* pInBuf, UINT16 usLen)
{
    eMcErr        eRet            = MC_OK;
    eMcDir        eDir            = MC_DIR_UNKOWN;
    eMcAFN        eAFN            = MC_AFN_NULL;
    eMcmd         eCmd            = MCMD_AFN_F_UNKOWN;
    BOOL          bP0             = FALSE;
    BOOL          bTp             = FALSE;
    BOOL          bEc             = FALSE;
    BOOL          bFixed          = FALSE;    // �Ƿ�Ϊ�̶�֡
    UINT8          ucFn           = 0;
    UINT8          ucPnCycMax     = 0;        // ��Pnѭ�������ֵ
    UINT8          ucAc_f         = 0;        // Ӧ�ÿ�����AC
    UINT16         usC_f          = 0;        // ������C
    UINT16         usPn           = 0;
    UINT16         usUsrdLen      = 0;        //�û�Ӧ��������֡����ֳ�
    UINT16         usUsrdLenTotal = 0;        //�û�Ӧ��������֡����ֳ�
    UINT16         usAuxLen       = 0;        // ������֡��EcPwTp֡��ļ�����Ĳ��ֳ�
    UINT16         usLenUserField = 0;        // �û�����������
    UINT16         usDataNum      = 0;        // ���ݵ�Ԫ��ĸ���
    INT32          nLenUserField  = 0;        // ÿ�ν���һ�����������ݵ�Ԫ����û��������ֳ�
    INT32          i              = 0;
    INT32          fi             = 0;        // Fn������
    INT32          pi             = 0;        // Pn������
    sMcfHeadFixed *psHeadFixed    = NULL;
    sMcfHeadAlter *psHeadAlter    = NULL;
    sMcDaDt       *pDaDt          = NULL;
    UINT8         *pucTemp        = NULL;     // ��������ָ��
    sMcEc         *psEC           = NULL;
    uMcApp        *puApp          = NULL;
    pMcFunc        pFunc          = NULL;
    sMcPnFn        sPnFn;
    sMcmdInfor     sCmdInfor;
    sMcA_f         sA_f;     

    if(!psUnpack || !pInBuf)
    {
        #ifdef MC_DBG
        MCDBG("emc_unPack_base() pointer is null!");
        #endif
        return MC_ERR_NULL;
    }

    if(TRUE != g_bMcInit)
    {
        #ifdef MC_DBG
        MCDBG("emc_unPack_base() protocol is not init!");
        #endif
        return MC_ERR_INIT;
    }

    if(usLen < MC_FRM_LEN_MIN)
    {
        #ifdef MC_DBG
        MCDBG("emc_unPack_base() input frame length is too short usLen = %d", usLen);
        #endif
        return MC_ERR_UNCOMP;
    }

    // �жϸ�֡�Ƿ���һ����Ч��֡
    eRet = emcIsValidPack(pInBuf, usLen, &bFixed);
    if(MC_OK != eRet)
    {
        #ifdef MC_DBG
        MCDBG("emc_unPack_base() input is not a valid pack eRet = %d", eRet);
        #endif
        return MC_ERR_PACK;
    }

    psUnpack->bFixed = bFixed;
    
    // �̶�֡
    if(TRUE == bFixed)
    {
        psHeadFixed = (sMcfHeadFixed *)pInBuf;

        // ������C
        usC_f = psHeadFixed->usC;
        eRet = emc_trans_ctrl(MC_TRANS_F2U, &(psUnpack->sCtrl), &usC_f);
        if(MC_OK != eRet)
        {
            #ifdef MC_DBG
            MCDBG("emc_unPack_base()-> emc_trans_ctrl() error eRet = %d", eRet);
            #endif
            return eRet;
        }

        // ��ַ��A
        sA_f = psHeadFixed->stA;
        eRet = emc_trans_address(MC_TRANS_F2U, &(psUnpack->sAddress), &sA_f);
        if(MC_OK != eRet)
        {
            #ifdef MC_DBG
            MCDBG("emc_unPack_base()-> emc_trans_address() error eRet = %d", eRet);
            #endif
            return eRet;
        }
    }
    // �ɱ�֡
    else
    {
        psHeadAlter = (sMcfHeadAlter *)pInBuf;

        // �û������ݳ���
        usLenUserField = psHeadAlter->usL1;

        // ������C
        usC_f = psHeadAlter->usC;
        eRet = emc_trans_ctrl(MC_TRANS_F2U, &(psUnpack->sCtrl), &usC_f);
        if(MC_OK != eRet)
        {
            #ifdef MC_DBG
            MCDBG("emc_unPack_base()-> emc_trans_ctrl() error eRet = %d", eRet);
            #endif
            return eRet;
        }

        // ��ַ��A
        sA_f = psHeadAlter->stA;
        eRet = emc_trans_address(MC_TRANS_F2U, &(psUnpack->sAddress), &sA_f);
        if(MC_OK != eRet)
        {
            #ifdef MC_DBG
            MCDBG("emc_unPack_base()-> emc_trans_address() error eRet = %d", eRet);
            #endif
            return eRet;
        }

        // Э���ʶ
        //psHeadAlter->ucV == MC_PROTO_VERSION ?

        // Ӧ�ÿ�����AC
        ucAc_f = psHeadAlter->ucAc;
        eRet = emc_trans_ac(MC_TRANS_F2U, &(psUnpack->sAc), &ucAc_f);
        if(MC_OK != eRet)
        {
            #ifdef MC_DBG
            MCDBG("emc_unPack_base()-> emc_trans_ac() error eRet = %d", eRet);
            #endif
            return eRet;
        }

        // ���AUX���ݳ���
        eDir = psUnpack->sCtrl.eDir;
        bEc  = psUnpack->sAc.bEc;
        bTp  = psUnpack->sAc.bTp;
        eAFN = psUnpack->sAc.eAfn;

        usAuxLen = usmc_get_aux_len(eAFN, eDir, bEc, bTp);

        // ������·�����ݳ���
        nLenUserField = (INT32)(usLenUserField - usAuxLen - MC_CA_LEN);

        // ��ȥ(Э���ʶ��Ӧ�ÿ�����AC�ĳ���)
        nLenUserField -= MC_VAC_LEN;

        // Ӧ�ò����� ���ݵ�Ԫ��ʶ�����ݵ�Ԫ��
        pucTemp = (UINT8*)((UINT8*)&(psHeadAlter->ucAc) + 1);
        while(nLenUserField > 0)
        {
            #if 0
            #ifdef MC_DBG
            MCDBG("emcBaseUnPack() nLenUserField = %d", nLenUserField);
            #endif
            #endif

            // ��ʼ��
            usUsrdLen = nLenUserField;

            // ���ݵ�Ԫ��ʶ
            pDaDt = (sMcDaDt*)pucTemp;
            eRet = emc_dadt_to_pnfn(pDaDt, &sPnFn);
            if(MC_OK != eRet)
            {
                #ifdef MC_DBG
                MCDBG("emc_unPack_base() -> emc_dadt_to_pnfn() error = %d\n", eRet);
                #endif
                return eRet;
            }

            pucTemp += sizeof(sMcDaDt);

            bP0 = bmc_is_p0(sPnFn.usPn);
            if(TRUE == bP0)
            {
                //P0���������ѭ��
                ucPnCycMax = 1;
            }
            else
            {
                // ����P0�������˫��ѭ��
                ucPnCycMax = 8;
            }

            psUnpack->sData[i].sPnFn = sPnFn;
            for(pi = 0; pi < ucPnCycMax; pi++)
            {
                usPn = sPnFn.usPn[pi];
                if(MC_PN_NONE == usPn)
                {
                    // �Ϸ���������, ��û�ж�Ӧλ�õ�PN
                }
                else if(usPn < MC_PN_MIN || usPn > MC_PN_MAX)
                {
                    // �Ƿ�Fn
                    #ifdef MC_DBG
                    MCDBG("emc_unPack_base() usPn error Pn = %d\n", usPn);
                    #endif
                    return MC_ERR_PARA;
                }
                else
                {
                    for(fi = 0; fi < 8; fi++)
                    {
                        ucFn = sPnFn.ucFn[fi];
                        if(MC_FN_NONE == ucFn)
                        {
                            // ���������û�и�FN, �Ϸ���������
                        }
                        else if(ucFn < MC_FN_MIN || ucFn > MC_FN_MAX)
                        {
                            // �Ƿ�Fn
                            #ifdef MC_DBG
                            MCDBG("emc_unPack_base() ucFn error Fn = %d\n", ucFn);
                            #endif
                            return MC_ERR_PARA;
                        }
                        else
                        {
                            eCmd = (eMcmd)((eAFN << 8) | (sPnFn.ucFn[fi]));
                            eRet = eMcGetCmdInfor(eCmd, eDir, &sCmdInfor);
                            if(MC_OK != eRet)
                            {
                                #ifdef MC_DBG
                                MCDBG("emc_unPack_base() eMcGetCmdInfor() failed %d %s!", eRet, smcGetErr(eRet));
                                #endif
                                return eRet;
                            }

                            pFunc = sCmdInfor.pFunc;
                            if(NULL != pFunc)
                            {
                                // �����ڴ�,���Ӧ�ò�����, �ɵ������ͷŸ��ڴ�, �ú����ڲ��ͷ�
                                puApp = (uMcApp*)malloc(sizeof(uMcApp));
                                if(!puApp)
                                {
                                    #ifdef MC_DBG
                                    MCDBG("emc_unPack_base() malloc failed!");
                                    #endif
                                    return MC_ERR_IO;
                                }

                                psUnpack->sData[i].puApp[pi][fi] = puApp;

                                eRet = pFunc(MC_TRANS_F2U, (void*)(psUnpack->sData[i].puApp[pi][fi]), (void*)pucTemp, &usUsrdLen);
                                if(eRet != MC_OK)
                                {
                                    #ifdef MC_DBG
                                    MCDBG("emc_unPack_base() transfunc() error = %d\n", eRet);
                                    #endif

                                    // �ͷ�֮�䶯̬������ڴ�ռ�
                                    vmc_free_base_data(psUnpack->sData, i+1);
                                    return eRet;
                                }

                                // ����ָ�����
                                pucTemp += usUsrdLen;

                                // ��¼�����ܳ�
                                usUsrdLenTotal += usUsrdLen;
                            }
                        }
                    }
                }
            }

            // �������
            usDataNum++;

            // ���ȼ���
            nLenUserField -= sizeof(sMcDaDt);
            nLenUserField -= usUsrdLenTotal;

            // ���ü���
            usUsrdLenTotal = 0;
            i++;
        }

        // �����EC
        if(TRUE == bEc)
        {
            psEC = (sMcEc*)pucTemp;
            psUnpack->sEc.usEC1 = psEC->usEC1;
            psUnpack->sEc.usEC2 = psEC->usEC2;
            pucTemp += sizeof(sMcEc);
        }

        // �����PW
        if(TRUE == bmc_have_pw(eAFN, eDir))
        {
            memcpy((void*)(psUnpack->aPw), (void*)pucTemp, MC_PW_LEN);
            pucTemp += MC_PW_LEN;
        }

        // �����TP
        if(TRUE == bTp)
        {
            eRet = emc_trans_tp(MC_TRANS_F2U, &(psUnpack->sTp), (sMcTp_f*)pucTemp);
            if(eRet != MC_OK)
            {
                #ifdef MC_DBG
                MCDBG("eMcUnpack() emc_trans_tp() error = %d\n", eRet);
                #endif
                return eRet;
            }

            //pucTemp += sizeof(sMtfTp);
        }

        psUnpack->usNum = usDataNum;
    }

    return MC_OK;
}

/*****************************************************************************
 �� �� ��  : emcPack
 ��������  : ��װ����(�߼��ӿ�)
 ʵ�ֹ���  : (1) ʵ����ɢ����Ϣ������Ϣ����Զ�����
             (2) �Զ�ȡ��ǰ��ʱ�����ϳ�tp
             (3) Ϊ�ϲ�������صĲ��� �繦�����

 �������  : smcPack* psPack

 �������  : UINT16* pusLen
             UINT8* pOutBuf
 �� �� ֵ  :
 ���ú���  : emc_pack_common()
 ��������  : emcPack()

 �޸���ʷ      :
  1.��    ��   : 2013��10��25�� ������
    ��    ��   : liming
    �޸�����   : �����ɺ���

*****************************************************************************/
eMcErr emcPack(smcPack* psPack, UINT8* pOutBuf, UINT16* pusLen)
{
    eMcErr         eRet         = MC_OK;
    eMcmd          eCmd         = MCMD_AFN_F_UNKOWN;
    eMcDir         eDir         = MC_DIR_UNKOWN;
    eMcAFN         eAFN         = MC_AFN_NULL;
    eMcAFN         eAFNCmd      = MC_AFN_NULL;  // �����Ӧ��AFN
    UINT8          ucTeamPn     = 0xFF;
    UINT8          ucTeamPnBase = 0xFF;
    UINT8          ucTeamFn     = 0xFF;
    UINT8          ucTeamFnBase = 0xFF;
    UINT8          ucFn         = 0;
    UINT16         usPn         = 0;
    INT32          FnIndex      = 0;
    INT32          PnIndex      = 0;
    INT32          i            = 0;
    INT32          j            = 0;
    INT32          k            = 0;
    INT32          nDaDtNum     = 0;      // ��װpackbase����Ϣ��ʶ��64�����ݵ�Ԫ����ܸ���
    INT32          nDaDtPos     = 0;      // ÿ��Ӧ����packbase����Ϣ��ʶ�������
    BOOL           bFindDaDt    = FALSE;  // �Ƿ��ҵ�֮ǰ���ڵ���
    BOOL           bInFn8       = FALSE;
    UINT8*         pMemBase     = NULL;
    smcBaskPack*   psBasePack   = NULL;
    sMcmdInfor     sCmdInfor;

    // �������
    if(!psPack || !pusLen || !pOutBuf)
    {
        #ifdef MC_DBG
        MCDBG("emcPack() pointer is null!");
        #endif
        return MC_ERR_NULL;
    }

    if(TRUE != g_bMcInit)
    {
        #ifdef MC_DBG
        MCDBG("emcPack() protocol is not init!");
        #endif
        return MC_ERR_INIT;
    }

    // Ϊ����psBasePack�����ڴ�
    pMemBase  = (UINT8*)malloc(MC_USER_MAX);
    if(!pMemBase)
    {
        #ifdef MC_DBG
        MCDBG("emcPack() malloc failed!");
        #endif
        return MC_ERR_IO;
    }

    psBasePack = (smcBaskPack*)pMemBase;

    // ��װ�� smcBaskPack ����
    psBasePack->sAddress = psPack->sAddress;
    psBasePack->sCtrl    = psPack->sCtrl;
    psBasePack->bFixed   = psPack->bFixed;
    eDir                 = psPack->sCtrl.eDir;

    // �̶�֡
    if(TRUE == psPack->bFixed)
    {

    }
    // �ɱ�֡
    else
    {
        psBasePack->sAc      = psPack->sAc;
        psBasePack->sEc      = psPack->sEc;
        psBasePack->sTp      = psPack->sTp;
        memcpy(psBasePack->aPw, psPack->aPw, MC_PW_LEN);
        eAFN = psPack->sAc.eAfn;

        // ����ɢ�����ݵ�Ԫ��ʶ�����ݵ�Ԫ��ϳ���
        for(i = 0; i < psPack->usNum; i++)
        {
            eCmd = psPack->sData[i].eCmd;

            // �жϸ������Ƿ��ǺϷ��ġ���֧�ֵ�
            eRet = eMcGetCmdInfor(eCmd, eDir, &sCmdInfor);
            if(eRet != MC_OK)
            {
                #ifdef MC_DBG
                MCDBG("emcPack() eMcGetCmdInfor() failed %d %s!", eRet, smcGetErr(eRet));
                #endif
                MC_FREE(pMemBase);
                return eRet;
            }

            // �жϸ������Ƿ�����AFN��������
            eAFNCmd = eMcGetCmdAfn(eCmd);
            if(eAFNCmd != eAFN)
            {
                MC_FREE(pMemBase);
                #ifdef MC_DBG
                MCDBG("emcPack() cmd is %04X", eCmd);
                MCDBG("emcPack() cmd is not is a same Afn eAFNCmd = %d eAFN = %d", eAFNCmd, eAFN);
                #endif
                return MC_ERR_TEAM;
            }

            usPn = psPack->sData[i].usPN;
            ucFn = ucMcGetCmdFn(eCmd);

            /*
                �жϸúϷ������ݵ�Ԫ��ʶ,�����ݵ�Ԫ�Ƿ��Ѿ�����Ӧ��λ�� psBasePack
                ����ظ�,���߸���ǰ��, Da2 �벻ͬ��Dt2���,
                �������ͬ�ı�ʶ�����ݵ�Ԫ��, ����nDaTaNum�ĸ���
            */

            nDaDtPos = nDaDtNum;

            // ��ʼ��PnFn��
            for(k = 0; k < 8; k++)
            {
                psBasePack->sData[nDaDtPos].sPnFn.ucFn[k] = MC_FN_NONE;
                psBasePack->sData[nDaDtPos].sPnFn.usPn[k] = MC_PN_NONE;
            }

            for(j = 0; j < nDaDtNum; j++)
            {
                // �ҵ���nDataPos���ҵ���λ��
                // ���ж�Pn�Ƿ���ͬһ��
                ucTeamPn     = ucmc_get_pn_team(usPn);
                ucTeamPnBase = ucmc_get_pn8_team(psBasePack->sData[j].sPnFn.usPn);

                if(ucTeamPn == ucTeamPnBase)
                {
                    // ���ж�Fn�Ƿ�����ͬһ����
                    ucTeamFn     = ucmc_get_fn_team(ucFn);
                    ucTeamFnBase = ucmc_get_fn8_team(psBasePack->sData[j].sPnFn.ucFn);

                    if(ucTeamFn == ucTeamFnBase)
                    {
                        //bInPn8 = bmt_in_pn8(usPn, psBasePack->sData[j].sPnFn.usPn);
                        bInFn8 = bmc_in_fn8(ucFn, psBasePack->sData[j].sPnFn.ucFn);

                        //if(TRUE == bInPn8 || TRUE == bInFn8)
                        if(TRUE == bInFn8)
                        {
                            bFindDaDt = TRUE;
                            nDaDtPos  = j;
                            break;
                        }
                    }
                }
            }

            // δ�ҵ���nDaTaNum++
            if(FALSE == bFindDaDt)
            {
                nDaDtNum  += 1; // ����һ��
            }

            // ���� DaTa�鼰���ݵ�Ԫ
            if(0 == usPn)
            {
                PnIndex = 0;

                for(k = 0; k < 8; k++)
                {
                    psBasePack->sData[nDaDtPos].sPnFn.usPn[k] = 0;
                }
            }
            else
            {
                PnIndex = (usPn - 1) % 8;
                psBasePack->sData[nDaDtPos].sPnFn.usPn[PnIndex] = usPn;
            }

            FnIndex = (ucFn - 1) % 8;
            psBasePack->sData[nDaDtPos].sPnFn.ucFn[FnIndex] = ucFn;

            // ���ݵ�Ԫ
            psBasePack->sData[nDaDtPos].puApp[PnIndex][FnIndex] = &(psPack->sData[i].uApp);

            // ����δ�ҵ�״̬
            bFindDaDt = FALSE;

        }

        psBasePack->usNum = nDaDtNum;
    }

    // ���� emc_pack_base()
    eRet = emc_pack_base(psBasePack , pOutBuf, pusLen);
    if(MC_OK != eRet)
    {
        #ifdef MC_DBG
        MCDBG("emcPack() emc_pack_base() failed! code : %d %s", eRet, smcGetErr(eRet));
        #endif
        MC_FREE(pMemBase);
        return eRet;
    }

    MC_FREE(pMemBase);
    return MC_OK;
}

/*****************************************************************************
 �� �� ��  : emcUnPack
 ��������  : Э�����(�߼��ӿ�)
             ��emc_unPack_base()������������ϢsmcBaskPack, ��װ�ɸ߼�smcPack

             (1)����Ҫ��Ϣ��ȡ
             (2)��PnFn���ݵ�Ԫ��ȡ����ɢ��

 �������  :  UINT8* pInBuf
              UINT16 usLen

 �������  : smcPack *psUnpack
 �� �� ֵ  :
 ���ú���  : emc_unPack_base()
 ��������  : emcUnPackCon()

 �޸���ʷ      :
  1.��    ��   : 2013��10��29�� ���ڶ�
    ��    ��   : liming
    �޸�����   : �����ɺ���

*****************************************************************************/
eMcErr emcUnPack(smcPack *psUnpack, UINT8* pInBuf, UINT16 usLen)
{
    eMcErr       eRet        = MC_OK;
    eMcmd        eCmd        = MCMD_AFN_F_UNKOWN;
    eMcAFN       eAFN        = MC_AFN_NULL;
    UINT8*       pMemBase    = NULL;
    smcBaskPack* pBaseUnpack = NULL;
    uMcApp      *puApp       = NULL;
    BOOL         bP0         = FALSE;
    INT32        i           = 0;
    INT32        j           = 0;
    INT32        fi          = 0;
    INT32        pi          = 0;
    INT32        PnCyc       = 0;
    UINT16       usPn        = 0;
    UINT8        ucFn        = 0;
    sMcmdInfor   sCmdInfor;

    if(!psUnpack || !pInBuf)
    {
        #ifdef MC_DBG
        MCDBG("emcUnPack() pointer is null!");
        #endif
        return MC_ERR_NULL;
    }

    if(TRUE != g_bMcInit)
    {
        #ifdef MC_DBG
        MCDBG("emcUnPack() protocol is not init!");
        #endif
        return MC_ERR_INIT;
    }

    // ��ʼ������
    memset(&sCmdInfor, 0, sizeof(sMcmdInfor));

    pMemBase = (UINT8*)malloc(MC_USER_MAX);
    if(!pMemBase)
    {
        #ifdef MC_DBG
        MCDBG("emcUnPack() malloc failed!");
        #endif
        return MC_ERR_IO;
    }

    memset(pMemBase, 0, MC_USER_MAX);
    
    pBaseUnpack = (smcBaskPack*)pMemBase;

    // ���ý�������
    eRet = emc_unPack_base(pBaseUnpack, pInBuf, usLen);
    if(MC_OK != eRet)
    {
        #ifdef MC_DBG
        MCDBG("emcUnPack() -> emc_unPack_base() failed! %d %s", eRet, smcGetErr(eRet));
        #endif
        MC_FREE(pMemBase);
        return eRet;
    }

    // �����ֶ�
    psUnpack->sAddress = pBaseUnpack->sAddress;
    psUnpack->sCtrl    = pBaseUnpack->sCtrl;
    psUnpack->bFixed   = pBaseUnpack->bFixed;

    // �̶�֡
    if(TRUE == pBaseUnpack->bFixed)
    {
        psUnpack->bPw   = FALSE;
        psUnpack->usNum = 1;
        psUnpack->sData[0].usPN = 0;
        psUnpack->sData[0].usPN = 0;
        psUnpack->sData[0].bApp = FALSE;

        if(MC_DIR_S2M == psUnpack->sCtrl.eDir)
        {
            switch(psUnpack->sCtrl.eFcode)
            {
                case MC_FCD_LOG_IN:
                    psUnpack->sData[0].eCmd = MCMD_AFN_2_F1_LOG_IN;
                    break;

                case MC_FCD_LOG_OUT:
                    psUnpack->sData[0].eCmd = MCMD_AFN_2_F2_LOG_OUT;
                    break;

                case MC_FCD_HEART_BEAT:
                    psUnpack->sData[0].eCmd = MCMD_AFN_2_F3_HEART_BEAT;
                    break;

                default:
                    #ifdef MC_DBG
                    MCDBG("emcUnPack() -> fixed frame's eFcode is error %d", psUnpack->sCtrl.eFcode);
                    #endif
                    MC_FREE(pMemBase);
                    return MC_ERR_FCODE;
                    // break;
            }
        }
        else
        {
            if(MC_FCD_LINK_OK == psUnpack->sCtrl.eFcode)
            {
                psUnpack->sData[0].eCmd = MCMD_AFN_2_F4_LINK_OK;
            }
            else
            {
                 #ifdef MC_DBG
                 MCDBG("emcUnPack() -> fixed frame's eFcode is error %d", psUnpack->sCtrl.eFcode);
                 #endif
                 MC_FREE(pMemBase);
                 return MC_ERR_FCODE;
            }
        }
    }
    // �ɱ�֡
    else
    {
        // ת�����ݽṹ
        psUnpack->sAc = pBaseUnpack->sAc;
        psUnpack->sEc = pBaseUnpack->sEc;
        psUnpack->sTp = pBaseUnpack->sTp;
        memcpy(psUnpack->aPw, pBaseUnpack->aPw, MC_PW_LEN);
        eAFN = psUnpack->sAc.eAfn;
        psUnpack->bPw = bmc_have_pw(eAFN, psUnpack->sCtrl.eDir);

        // Ӧ�ò�����
        for(i = 0; i < pBaseUnpack->usNum; i++)
        {
            bP0 = bmc_is_p0(pBaseUnpack->sData[i].sPnFn.usPn);
            PnCyc = ((bP0 == TRUE) ? 1 : 8);

            for(pi = 0; pi < PnCyc; pi++)
            {
                usPn = pBaseUnpack->sData[i].sPnFn.usPn[pi];
                if(MC_PN_NONE == usPn)
                {
                    // �Ϸ���������, ��û�ж�Ӧλ�õ�PN
                }
                else if(usPn < MC_PN_MIN || usPn > MC_PN_MAX)
                {
                    // �Ƿ�Fn
                    #ifdef MC_DBG
                    MCDBG("emcUnPack() usPn error Pn = %d\n", usPn);
                    #endif
                    MC_FREE(pMemBase);
                    return MC_ERR_PARA;
                }
                else
                {
                    #if 0
                    #ifdef MC_DBG
                    for(fi = 0; fi < 8; fi++)
                    {   ucFn = pUnpackBase->sData[i].sPnFn.ucFn[fi];
                        MCDBG("emcUnPack() sData[%d].sPnFn.ucFn[%d] = %d",i, fi, ucFn);
                    }
                    #endif
                    #endif

                    for(fi = 0; fi < 8; fi++)
                    {
                        ucFn = pBaseUnpack->sData[i].sPnFn.ucFn[fi];
                        if(MC_FN_NONE == ucFn)
                        {
                            // ���������û�и�FN, �Ϸ���������
                        }
                        else if(ucFn < MC_FN_MIN || ucFn > MC_FN_MAX)
                        {
                            // �Ƿ�Fn
                            #ifdef MC_DBG
                            MCDBG("emcUnPack() ucFn error Fn = %d\n", ucFn);
                            #endif
                            MC_FREE(pMemBase);
                            return MC_ERR_PARA;
                        }
                        else
                        {
                            eCmd = (eMcmd)((eAFN << 8) | ucFn);
                            eRet = eMcGetCmdInfor(eCmd, psUnpack->sCtrl.eDir, &sCmdInfor);
                            if(MC_OK != eRet)
                            {
                                #ifdef MC_DBG
                                MCDBG("emcUnPack() eMcGetCmdInfor() failed %d %s!", eRet, smcGetErr(eRet));
                                #endif
                                MC_FREE(pMemBase);
                                return eRet;
                            }

                            // һ����Ч�����ݵ�Ԫ��ʶ��
                            psUnpack->sData[j].eCmd  = eCmd;
                            psUnpack->sData[j].usPN  = usPn;

                            if(NULL != sCmdInfor.pFunc)
                            {
                                psUnpack->sData[j].bApp = TRUE;
                                puApp = pBaseUnpack->sData[i].puApp[pi][fi];
                                if(!puApp)
                                {
                                    #ifdef MC_DBG
                                    MCDBG("emcUnPack() app date is null");
                                    #endif
                                    MC_FREE(pMemBase);
                                    return MC_ERR_PARA;
                                }

                                memcpy((void*)&(psUnpack->sData[j].uApp), (void*)puApp, sizeof(uMcApp));
                                MC_FREE(puApp);
                            }
                            else
                            {
                                psUnpack->sData[j].bApp = FALSE;
                            }

                            j++;
                        }
                    }
                }
            }
        }

        // ������������
        psUnpack->usNum = j;
    }

    MC_FREE(pMemBase);
    return MC_OK;
}

/*****************************************************************************
 �� �� ��  : emcPackCon
 ��������  : �������� Э���װ(�߼��ӿ�)
             (1)���������಻���ĵ��ֶ�����
             (2)�������÷�װ��ȷ�Ĳ���
             (3)�õ�ǰ����ʱ���װTp
             (4)�õ�ǰ���¼���¼��Ec
             (5)����֡���к�

 �������  :  sMcPackCon* psPack


 �������  : UINT8* pOutBuf,
             UINT16* pusLen
 �� �� ֵ  :
 ���ú���  : emc_unPack_base()
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��10��29�� ���ڶ�
    ��    ��   : liming
    �޸�����   : �����ɺ���

*****************************************************************************/
eMcErr emcPackCon(sMcPackCon* psPack, UINT8* pOutBuf, UINT16* pusLen)
{
    smcPack  *psmcPack = NULL;
    UINT8    *pMemPack = NULL;
    eMcmd     eCmd     = MCMD_AFN_F_UNKOWN;
    eMcFcode  eFcode   = MC_FCD_MAX;
    eMcErr    eRet     = MC_OK;
    INT32     i        = 0;

    if(!psPack || !pOutBuf || !pusLen)
    {
        #ifdef MC_DBG
        MCDBG("emcPackCon() pointer is null!");
        #endif
        return MC_ERR_NULL;
    }

    pMemPack = (UINT8*)malloc(MC_USER_MAX);
    if(!pMemPack)
    {
        #ifdef MC_DBG
        MCDBG("emcPackCon() malloc failed!");
        #endif
        return MC_ERR_IO;
    }

    psmcPack = (smcPack *)pMemPack;

    // ȡ�õ�һ���������������
    eCmd = psPack->sData[0].eCmd;

    // �̶�֡
    if(MCMD_AFN_2_F1_LOG_IN     == eCmd ||
       MCMD_AFN_2_F2_LOG_OUT    == eCmd ||
       MCMD_AFN_2_F3_HEART_BEAT == eCmd ||
       MCMD_AFN_2_F4_LINK_OK    == eCmd)
    {
        // �����ֶβ�����
        psmcPack->bFixed       = TRUE;
        psmcPack->sAddress     = psPack->sAddress;

        // ������
        psmcPack->sCtrl.eDir   = MC_DIR_S2M;
        psmcPack->sCtrl.ePRM   = MC_PRM_A2P;
        //psmcPack->sCtrl.ucPSEQ = (++g_ucMcPseq % 31);
        psmcPack->sCtrl.ucRSEQ = 0;

        switch(eCmd)
        {
            case MCMD_AFN_2_F1_LOG_IN:
                psmcPack->sCtrl.eFcode = MC_FCD_LOG_IN;
                break;

            case MCMD_AFN_2_F2_LOG_OUT:
                psmcPack->sCtrl.eFcode = MC_FCD_LOG_OUT;
                break;

            case MCMD_AFN_2_F3_HEART_BEAT:
                psmcPack->sCtrl.eFcode = MC_FCD_HEART_BEAT;
                break;

            default:
                #ifdef MC_DBG
                MCDBG("emcPackCon() contrator don't suport cmd: MCMD_AFN_2_F4_LINK_OK!");
                #endif
                MC_FREE(pMemPack);
                return MC_ERR_PARA;
                break;
        }
    }
    // �ɱ�֡
    else
    {
        psmcPack->bFixed       = FALSE;
        psmcPack->sAddress     = psPack->sAddress;
        psmcPack->sCtrl.eDir   = MC_DIR_S2M;

         /*
           ��Ӧ֡��� RSEQ
            (1) ��Ӧ֡��� RSEQ �� PRM=0 ʱ�����Ӷ�֡����Ч��
                �ñ����ʾ 0~15�����ڶ���Ӷ�֡��Ӧһ������֡�Ĵ��䡣
            (2) ÿһ������վ�ʹӶ�վ֮����� 1 �������ļ�������
                ���ڼ�¼��ǰ RSEQ����ֻ��һ֡�Ӷ�֡��Ӧ����֡�ģ�
                RSEQ=0�������� n ��n��16��֡��Ӧ�ģ�RSEQ �� n-1 ��ݼ�������
                ÿ����һ֡�� 1��ֱ�����һ֡ RSEQ=0��
        */

        // ��ǰ���ǵ�֡�ظ�RSEQ = 0;
        
        // ����֡
        if(TRUE == psPack->bActive)
        {
            psmcPack->sCtrl.ePRM = MC_PRM_A2P;
            psmcPack->sCtrl.ucRSEQ = 0;

        }
        // ��վ֡
        else
        {
            psmcPack->sCtrl.ePRM   = MC_PRM_P2A;
            psmcPack->sCtrl.ucRSEQ = psPack->ucRSEQ;
        }
        
        // ������
        eRet = emc_get_fcode(eCmd, MC_DIR_S2M, psmcPack->sCtrl.ePRM, &eFcode);
        if(MC_OK != eRet)
        {
            #ifdef MC_DBG
            MCDBG("emcPackCon() emc_get_fcode error code %d!", eRet);
            #endif
            MC_FREE(pMemPack);
            return eRet;
        }

        psmcPack->sCtrl.eFcode = eFcode;

        // �������ֶ�
        psmcPack->sAc.eAfn = eMcGetCmdAfn(eCmd);

        // Ec
        if(MC_CFG_EC == 1)
        {
            psmcPack->sAc.bEc = bmc_have_ec(psmcPack->sAc.eAfn, MC_DIR_S2M);
        }
        else
        {
            psmcPack->sAc.bEc = FALSE;
        }

        psmcPack->sEc.usEC1 = g_sMcEc.usEC1;
        psmcPack->sEc.usEC2 = g_sMcEc.usEC2;

        // Tp
        psmcPack->sAc.bTp = bmc_have_tp(psmcPack->sAc.eAfn, MC_DIR_S2M);
      
        // ȡ�õ�ǰϵͳʱ��
        if(TRUE == psmcPack->sAc.bTp)
        {
            eRet = emc_get_tp(&psmcPack->sTp);
            if(MC_OK != eRet)
            {
                #ifdef MC_DBG
                MCDBG("emcPackCon() emc_get_tp() error code %d!", eRet);
                #endif
                MC_FREE(pMemPack);
                return eRet;
            }
        }

        // Ӧ�ò�����
        psmcPack->usNum = psPack->usNum;

        for(i =0; i < psPack->usNum; i++)
        {
            memcpy((void*)&(psmcPack->sData[i]), (void*)&(psPack->sData[i]), sizeof(sMcData));
        }
    }

    /*
        ����֡��� PSEQ
        �ñ����ʾ 0~31����������Ͷ�Ӧ����֡���Լ���ֹ��Ϣ����Ķ�ʧ���ظ�

        (1)ÿһ������վ�ʹӶ�վ֮����� 1 �������ļ����������ڼ�¼��ǰ PSEQ��
           ����վ��ͬһ�Ӷ�վ�����µĴ������ʱ��PSEQ+1��

        (2)����ʱδ�յ��Ӷ�վ�ı��ģ�����ճ��ֲ��������վ���ı�PSEQ��
           �ظ�ԭ���Ĵ������
    */

    if(FALSE == psPack->bReSend && TRUE == psPack->bActive)
    {
         g_ucMcPseq = (g_ucMcPseq+1) % 31;
    }

    psmcPack->sCtrl.ucPSEQ = g_ucMcPseq;

    #ifdef MC_DBG
    MCDBG("emcPackCon() send  ucPSEQ = %d!", g_ucMcPseq);
    #endif
        
    // ���ô������
    eRet = emcPack(psmcPack, pOutBuf, pusLen);
    if(MC_OK != eRet)
    {
        #ifdef MC_DBG
        MCDBG("emcPackCon() emcPack() error code %d!", eRet);
        #endif
        MC_FREE(pMemPack);
        return eRet;
    }
    
    MC_FREE(pMemPack);
    return MC_OK;
}

/*****************************************************************************
 �� �� ��  : emcUnPackCon
 ��������  : ��������Э�����(�߼��ӿ�)

             (1)������վ����������������֡
             (2)��һЩ��������ʼ�ļ��(����ʱ���ǩ�Ƿ�ʱ��pw�Ƿ�Ϸ���)
             (3)����֡���к�
             (4)���μ������಻���ĵ���Ϣ�ֶ�

 �������  :  UINT8* pInBuf
              UINT16 usLen

 �������  : sMcPackCon *psUnpack
 �� �� ֵ  :
 ���ú���  : emc_unPack_base()
 ��������  : emcUnPackCon()

 �޸���ʷ      :
  1.��    ��   : 2013��10��29�� ���ڶ�
    ��    ��   : liming
    �޸�����   : �����ɺ���
*****************************************************************************/
eMcErr emcUnPackCon(sMcPackCon *psUnpack, UINT8* pInBuf, UINT16 usLen)
{
    eMcErr       eRet        = MC_OK;
    UINT8*       pMemUnpack  = NULL;
    smcPack*     psmcUnpack  = NULL;
    BOOL         bTimeOut    = FALSE;
    INT32        i           = 0;

    pMemUnpack = (UINT8*)malloc(MC_USER_MAX);
    if(!pMemUnpack)
    {
        #ifdef MC_DBG
        MCDBG("emcUnPackCon() malloc failed!");
        #endif
        return MC_ERR_IO;
    }

    psmcUnpack = (smcPack*)pMemUnpack;

    eRet = emcUnPack(psmcUnpack, pInBuf, usLen);
    if(MC_OK != eRet)
    {
        #ifdef MC_DBG
        MCDBG("emcUnPackCon() emcUnPack() error code %d!", eRet);
        #endif
        MC_FREE(pMemUnpack);
        return eRet;
    }

    // �ֶκϷ��Լ��
    // ���ķ���
    if(MC_DIR_M2S != psmcUnpack->sCtrl.eDir)
    {
        #ifdef MC_DBG
        MCDBG("emcPackCon() frame direction is error! It is not master to contrator!");
        #endif
        MC_FREE(pMemUnpack);
        return MC_ERR_DIR;
    }

    // ֡���к�
    if(MC_PRM_A2P == psmcUnpack->sCtrl.ePRM)
    {
        g_ucMcPseq = psmcUnpack->sCtrl.ucPSEQ & 0x1F;
        psUnpack->bActive = TRUE;
        
        #ifdef MC_DBG
        MCDBG("emcUnPackCon() Recv ucPSEQ = %d", g_ucMcPseq);
        #endif
    }
    else
    {
        psUnpack->bActive = FALSE;
    }

    #if 0
    // ʱ���ǩ
    if(TRUE == psmcUnpack->sAc.bTp)
    {
        bTimeOut = bmc_tp_timeout(&(psmcUnpack->sTp));
        if(TRUE == bTimeOut)
        {
            #ifdef MC_DBG
            MCDBG("emcPackCon() frame is timeout!");
            #endif
            MC_FREE(pMemUnpack);
            return MC_ERR_TIMEOUT;
        }
    }
    #endif
    
    // Pw����
    // ��ʱû����֤����,Ԥ��

    // �������
    psUnpack->sAddress = psmcUnpack->sAddress;

    // ���ݿ���
    psUnpack->usNum = psmcUnpack->usNum;
    for(i = 0; i < psmcUnpack->usNum; i++)
    {
        psUnpack->sData[i] = psmcUnpack->sData[i];
    }

    MC_FREE(pMemUnpack);
    return MC_OK;
}

/*****************************************************************************
 �� �� ��  : emcPackMst
 ��������  : ��վ��װ֡�ӿ�
 �������  : sMcPackMst* psPack  
             UINT8* pOutBuf      
             UINT16* pusLen      
 �������  : ��
 �� �� ֵ  : 
 ���ú���  : 
 ��������  : 
 
 �޸���ʷ      :
  1.��    ��   : 2013��11��5��
    ��    ��   : liming
    �޸�����   : �����ɺ���

*****************************************************************************/
eMcErr emcPackMst(sMcPackMst* psPack, UINT8* pOutBuf, UINT16* pusLen)
{
    smcPack  *psmcPack = NULL;
    UINT8    *pMemPack = NULL;
    eMcmd     eCmd     = MCMD_AFN_F_UNKOWN;
    eMcFcode  eFcode   = MC_FCD_MAX;
    eMcErr    eRet     = MC_OK;
    INT32     i        = 0;

    if(!psPack || !pOutBuf || !pusLen)
    {
        #ifdef MC_DBG
        MCDBG("emcPackCon() pointer is null!");
        #endif
        return MC_ERR_NULL;
    }

    pMemPack = (UINT8*)malloc(MC_USER_MAX);
    if(!pMemPack)
    {
        #ifdef MC_DBG
        MCDBG("emcPackMst() malloc failed!");
        #endif
        return MC_ERR_IO;
    }

    psmcPack = (smcPack *)pMemPack;

    // ȡ�õ�һ���������������
    eCmd = psPack->sData[0].eCmd;

    // �̶�֡
    if(MCMD_AFN_2_F1_LOG_IN     == eCmd ||
       MCMD_AFN_2_F2_LOG_OUT    == eCmd ||
       MCMD_AFN_2_F3_HEART_BEAT == eCmd ||
       MCMD_AFN_2_F4_LINK_OK    == eCmd)
    {
        // �����ֶβ�����
        psmcPack->bFixed       = TRUE;
        psmcPack->sAddress     = psPack->sAddress;

        // ������
        psmcPack->sCtrl.eDir   = MC_DIR_M2S;
        psmcPack->sCtrl.ePRM   = MC_PRM_P2A;
        psmcPack->sCtrl.ucPSEQ = psPack->ucPSEQ;
        psmcPack->sCtrl.ucRSEQ = 0;

        switch(eCmd)
        {
            case MCMD_AFN_2_F4_LINK_OK:
                psmcPack->sCtrl.eFcode = MC_FCD_LINK_OK;
                break;
            
            default:
                #ifdef MC_DBG
                MCDBG("emcPackMst() contrator don't suport cmd: MCMD_AFN_2_F4_LINK_OK!");
                #endif
                MC_FREE(pMemPack);
                return MC_ERR_PARA;
                break;
        }
    }
    // �ɱ�֡
    else
    {
        psmcPack->bFixed       = FALSE;
        psmcPack->sAddress     = psPack->sAddress;
        psmcPack->sCtrl.eDir   = MC_DIR_M2S;

        // ��վ�����Ķ�������֡
        psmcPack->sCtrl.ePRM = MC_PRM_A2P;
        
        /*
            ����֡��� PSEQ
            �ñ����ʾ 0~31����������Ͷ�Ӧ����֡���Լ���ֹ��Ϣ����Ķ�ʧ���ظ�

            (1)ÿһ������վ�ʹӶ�վ֮����� 1 �������ļ����������ڼ�¼��ǰ PSEQ��
               ����վ��ͬһ�Ӷ�վ�����µĴ������ʱ��PSEQ+1��

            (2)����ʱδ�յ��Ӷ�վ�ı��ģ�����ճ��ֲ��������վ���ı�PSEQ��
               �ظ�ԭ���Ĵ������
        */

        psmcPack->sCtrl.ucPSEQ = psPack->ucPSEQ;
     
        /*
           ��Ӧ֡��� RSEQ
            (1) ��Ӧ֡��� RSEQ �� PRM=0 ʱ�����Ӷ�֡����Ч��
                �ñ����ʾ 0~15�����ڶ���Ӷ�֡��Ӧһ������֡�Ĵ��䡣
            (2) ÿһ������վ�ʹӶ�վ֮����� 1 �������ļ�������
                ���ڼ�¼��ǰ RSEQ����ֻ��һ֡�Ӷ�֡��Ӧ����֡�ģ�
                RSEQ=0�������� n ��n��16��֡��Ӧ�ģ�RSEQ �� n-1 ��ݼ�������
                ÿ����һ֡�� 1��ֱ�����һ֡ RSEQ=0��
        */
        
        psmcPack->sCtrl.ucRSEQ = 0;

        // ������
        eRet = emc_get_fcode(eCmd, MC_DIR_M2S, psmcPack->sCtrl.ePRM, &eFcode);
        if(MC_OK != eRet)
        {
            #ifdef MC_DBG
            MCDBG("emcPackMst() emc_get_fcode error code %d!", eRet);
            #endif
            MC_FREE(pMemPack);
            return eRet;
        }
        
        psmcPack->sCtrl.eFcode = eFcode;

        // �������ֶ�
        psmcPack->sAc.eAfn = eMcGetCmdAfn(eCmd);

        // Ec
        psmcPack->sAc.bEc = FALSE; 
         
        // Tp
        psmcPack->sAc.bTp = bmc_have_tp(psmcPack->sAc.eAfn, MC_DIR_M2S);

        // pw
        memcpy(psmcPack->aPw, psPack->aPw, MC_PW_LEN);

        // ȡ�õ�ǰϵͳʱ��
        if(TRUE == psmcPack->sAc.bTp)
        {
            eRet = emc_get_tp(&psmcPack->sTp);
            if(MC_OK != eRet)
            {
                #ifdef MC_DBG
                MCDBG("emcPackMst() emc_get_tp() error code %d!", eRet);
                #endif
                MC_FREE(pMemPack);
                return eRet;
            }
        }

        // Ӧ�ò�����
        psmcPack->usNum = psPack->usNum;

        for(i =0; i < psPack->usNum; i++)
        {
            memcpy((void*)&(psmcPack->sData[i]), (void*)&(psPack->sData[i]), sizeof(sMcData));
        }
    }

    // ���ô������
    eRet = emcPack(psmcPack, pOutBuf, pusLen);
    if(MC_OK != eRet)
    {
        #ifdef MC_DBG
        MCDBG("emcPackMst() emcPack() error code %d!", eRet);
        #endif
        MC_FREE(pMemPack);
        return eRet;
    }
    
    MC_FREE(pMemPack);
    return MC_OK;
}

