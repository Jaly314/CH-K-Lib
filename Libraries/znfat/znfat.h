#ifndef __ZNFAT_H__
#define __ZNFAT_H__

#include "mytype.h" //���������ض��壬�����Ŀ��ƽ̨���ж��� 
#include "config.h" //znFAT�������ļ�
#include "cc_macro.h" //��ͷ�ļ��ж�����znFAT�и��ֺ���֮���������ϵ����֮������ƿ�ʵ�ֹ��ܺ����Ĳü����ɼ��ٳ���洢����ʹ����

/*==================================================================================
  ���ϵ�znFAT һ�ֽ�Ϊ�걸��Ƕ��ʽƽ̨�ϵ�FAT32�ļ�ϵͳ������� V10.89
  �����ע ���ϵ�znFAT ��վ www.znfat.com
  �����ע ���ϵ�znFAT ��վ www.znfat.com
===================================================================================*/

#define MBR_SECTOR (0) //MBR����
#define DBR_MARK (0XEB) //DBR�ı�־��

#define FDI_NBYTES (32) //�ļ�Ŀ¼����ռ�ֽ��� 
#define NFDI_PER_SEC (16) //ÿ�������ļ�Ŀ¼����

#define ZNFAT_BUF_SIZE (512) //znFAT�ڲ���������С 

#define SOC(c)  (((c-2)*(pInit_Args->SectorsPerClust))+(pInit_Args->FirstDirSector)) //����صĿ�ʼ���� Start Sector Of Cluster

#define NFATITEMBYTES   (4)    //FAT������ռ�õ��ֽ���
#define NITEMSINFATSEC  (128)  //FAT��һ�������а����ı�����

#define IS_END_CLU(cluster) ((0X0FFFFFFF)==(cluster)) //�ж�һ�������ֵ�Ƿ��ǽ�����
#define IS_END_SEC_OF_CLU(sec,cluster) ((sec-SOC(cluster))==(pInit_Args->SectorsPerClust-1)) //�ж��Ƿ��Ǵص����һ������
#define LAST_SEC_OF_CLU(cluster) (SOC(cluster)+(pInit_Args->SectorsPerClust-1)) //�ص����һ�������ĵ�ַ
#define IS_FAT32_TYPE(FST) (('F'==(FST[0])) && ('A'==(FST[1])) && ('T'==(FST[2])) && ('3'==(FST[3])) && ('2'==(FST[4]))) //�����ļ�ϵͳ�Ƿ�FAT32 

#define CHK_ATTR_FILE(attr) ((!((attr&0X10)!=0X00)) && (0X0F!=attr) && (0X00!=attr) && (0X08!=attr)) //�����ֽڵ�4λΪ0��ͬʱ���ǳ�������0X0F���������� 
#define CHK_ATTR_DIR(attr) ((attr&0X10)!=0X00) //�����ֽڵ�4λΪ1��������ΪĿ¼
#define CHK_ATTR_LFN(attr) (0X0F==attr) //�����ֽ�Ϊ0X0F����Ϊ������

#define Lower2Up(c) ((c>='a' && c<='z')?(c-32):c)
#define Upper2Low(C) ((C>='A' && C<='Z')?(C+32):C)
#define WLower2Up(c) ((c>=(UINT16)'a' && c<=(UINT16)'z')?(c-32):c)
#define WUpper2Low(C) ((C>=(UINT16)'A' && C<=(UINT16)'Z')?(C+32):C)
#define IS_ASC(c) ((c&0X80)==0)

#define MAKE_TIME(h,m,s) ((((UINT16)h)<<11)+(((UINT16)m)<<5)+(((UINT16)s)>>1))	//��ʱ���λ�ζ���ϳ�ʱ����
#define MAKE_DATE(y,m,d) (((((UINT16)(y%100))+20)<<9)+(((UINT16)m)<<5)+((UINT16)d))	//�����ڵ�λ�ζ���ϳ�������

#define BOOL_TRUE     (1) 
#define BOOL_FALSE    (0)
#define NUL_RET  (0)
#define NUL_PTR  ((void *)0)

//=====macro for format function========
#define NSECPERTRACK (63)
#define NHEADER      (255)
#define NSECPERCYLINDER (((UINT32)NSECPERTRACK)*((UINT32)NHEADER))
//==============================================

//==========================================================================================================================
//���º������ڴ�FLASHROM�ж�ȡ��Ӧ���͵�����

#define GET_PGM_BYTE(u)    (PGM_BYTE_FUN(u))   
#define GET_PGM_WORD(u)    (PGM_WORD_FUN(u))  
#define GET_PGM_DWORD(u)   (PGM_DWORD_FUN(u))  

//===========================================================================================================================

//=================ERR code====������==========
#define ERR_SUCC                  (0)
#define ERR_FAIL                  (1)

#define FSTYPE_NOT_FAT32          (2)

#define ERR_NO_FILE               (3)
#define ERR_NO_DIR                (4)

#define ERR_FDI_ALREADY_EXISTING  (5)
#define ERR_FDI_NO_SPARE_SPACE    (6)

#define ERR_NO_SPACE              (7)

#define ERR_ILL_CHAR              (8)

#define ERR_SFN_ILL_LEN    	      (9)
#define ERR_SFN_DOT               (10)

#define ERR_SFN_SPEC_CHAR         (11)
#define ERR_SFN_ILL_LOWER         (12)

#define ERR_DIR_ALREADY_EXISTING  (13)

#define ERR_FMT_TOO_LOW_VOLUME    (14)

#define ERR_LFN_BUF_OUT           (15)
#define ERR_OEM_CHAR_NOT_COMPLETE (16)

#define ERR_FS_DIR                (17)

#define ERR_DEVICE_IO             (18)

//================================================

//DPT:��������¼�ṹ����
struct DPT_Item
{
 UINT8 Active;         //0x80��ʾ�˷�����Ч
 UINT8 StartHead;      //�����Ŀ�ʼ��ͷ
 UINT8 StartSect;      //��ʼ����
 UINT8 StartCyl;       //��ʼ����
 UINT8 PartType;       //��������
 UINT8 EndHead;        //�����Ľ���ͷ
 UINT8 EndSect;        //��������
 UINT8 EndCyl;         //��������
 UINT8 StartLBA[4];    //�����ĵ�һ������
 UINT8 Size[4];        //�����Ĵ�С����������
};

//MBR����������0��������������
struct MBR
{
 UINT8 PartCode[446]; //MBR����������
 struct DPT_Item Part[4]; //4��������¼
 UINT8 BootSectSig0;  //55
 UINT8 BootSectSig1;  //AA
};

//znFAT�ж�DBR�Ķ�������  һ��ռ��90���ֽ�
struct DBR
{
 UINT8 BS_jmpBoot[3];     //��תָ��            offset: 0
 UINT8 BS_OEMName[8];     //OEM����             offset: 3

 UINT8 BPB_BytesPerSec[2];//ÿ�����ֽ���        offset:11
 UINT8 BPB_SecPerClus;    //ÿ��������          offset:13
 UINT8 BPB_RsvdSecCnt[2]; //����������Ŀ        offset:14
 UINT8 BPB_NumFATs;       //�˾���FAT����       offset:16
 UINT8 BPB_RootEntCnt[2]; //FAT32Ϊ0            offset:17
 UINT8 BPB_TotSec16[2];   //FAT32Ϊ0            offset:19
 UINT8 BPB_Media;         //�洢����            offset:21
 UINT8 BPB_FATSz16[2];    //FAT32Ϊ0            offset:22
 UINT8 BPB_SecPerTrk[2];  //�ŵ�������          offset:24
 UINT8 BPB_NumHeads[2];   //��ͷ��              offset:26
 UINT8 BPB_HiddSec[4];    //FAT��ǰ��������     offset:28
 UINT8 BPB_TotSec32[4];   //�þ���������        offset:32
 UINT8 BPB_FATSz32[4];    //һ��FAT��������     offset:36
 UINT8 BPB_ExtFlags[2];   //FAT32����           offset:40
 UINT8 BPB_FSVer[2];      //FAT32����           offset:42
 UINT8 BPB_RootClus[4];   //��Ŀ¼�غ�          offset:44
 UINT8 FSInfo[2];         //��������FSINFO������offset:48
 UINT8 BPB_BkBootSec[2];  //ͨ��Ϊ6             offset:50
 UINT8 BPB_Reserved[12];  //��չ��              offset:52
 UINT8 BS_DrvNum;         //                    offset:64
 UINT8 BS_Reserved1;      //                    offset:65
 UINT8 BS_BootSig;        //                    offset:66
 UINT8 BS_VolID[4];       //                    offset:67
 UINT8 BS_FilSysType[11]; //	                offset:71
 UINT8 BS_FilSysType1[8]; //"FAT32    "         offset:82
};

//znFAT�ж��ļ�Ŀ¼��(���Ͻ���FDI)�Ķ�������  һ��ռ��32���ֽ�
struct FDI
{
 UINT8 Name[8];         // �ļ��������㲿���Կո񲹳�
 UINT8 Extension[3]; 	// ��չ�������㲿���Կո񲹳�
 UINT8 Attributes;   	// �ļ�����
 UINT8 LowerCase;    	// 0
 UINT8 CTime10ms;   	// ����ʱ���10����λ
 UINT8 CTime[2];     	// ����ʱ��
 UINT8 CDate[2];     	// ��������
 UINT8 ADate[2];     	// ��������
 UINT8 HighClust[2];    // ��ʼ�صĸ���
 UINT8 MTime[2];     	// ������޸�ʱ��
 UINT8 MDate[2];     	// ������޸�����
 UINT8 LowClust[2]; 	// ��ʼ�صĵ���
 UINT8 FileSize[4];     // �ļ���С
};

struct LFN_FDI //�������ļ�Ŀ¼��ṹ����
{
 UINT8 AttrByte[1]; //�����ֽ�
 UINT8 Name1[10];   //��һ���ֳ���
 UINT8 LFNSign[1];  //�������־
 UINT8 Resv[1];     //����
 UINT8 ChkVal[1];   //����ֵ����SFN�İ�У��
 UINT8 Name2[12];   //�ڶ����ֳ���
 UINT8 StartClu[2]; //ȡ0
 UINT8 Name3[4];    //�������ֳ���
};

struct FSInfo //znFAT�ж��ļ�ϵͳ��Ϣ�ṹ�Ķ���
{
 UINT8 Head[4]; //"RRaA"
 UINT8 Resv1[480];
 UINT8 Sign[4]; //"rrAa"
 UINT8 Free_Cluster[4]; //ʣ��մ���
 UINT8 Next_Free_Cluster[4]; //��һ�մزο�ֵ
 UINT8 Resv2[14]; 
 UINT8 Tail[2]; //"55 AA"
};

struct FDIesInSEC
{
 struct FDI FDIes[NFDI_PER_SEC]; //�����е��ļ�Ŀ¼������
};

struct Date	 //���ڴ洢������Ϣ
{
 UINT16 year;
 UINT8 month;
 UINT8 day;
};

struct Time	 //���ڴ洢ʱ����Ϣ
{
 UINT8 hour;
 UINT8 min;
 UINT8 sec;
};

struct DateTime //������ʱ��
{
 struct Date date; //����
 struct Time time; //ʱ��
};

struct FAT_Item  //znFAT�ж�FAT����Ľṹ����
{
 UINT8 Item[NFATITEMBYTES]; //FAT32��FAT����ռ��4���ֽڣ���32λ
};
	
struct FAT_Sec	//znFAT�ж�FAT�������ṹ�Ķ���
{
 struct FAT_Item items[NITEMSINFATSEC]; //FAT��������128��FAT����
	                                //FAT�����Ľṹ������128��FAT�������͵�����
};
    
#define DATE_YEAR_BASE (1980)

#define TIME_HOUR_MARK  (0X001F)
#define TIME_MIN_MARK   (0X002F)
#define TIME_SEC_MARK   (0X001F)

#define DATE_YEAR_MARK  (0X007F)
#define DATE_MONTH_MARK (0X000F)
#define DATE_DAY_MARK   (0X001F) 

#define TIME_HOUR_NBITS   (5)
#define TIME_MIN_NBITS    (6)
#define TIME_SEC_NBITS    (5)

#define DATE_YEAR_NBITS   (7)
#define DATE_MONTH_NBITS  (4)
#define DATE_DAY_NBITS    (5)

//============================================================================== 

//znFAT��ʼ��ʱ��ʼ����װ�����½ṹ����
struct znFAT_Init_Args
{
 UINT32 BPB_Sector_No;   //DBR(BPB)����������

 UINT32 Total_SizeKB;    //���̵�����������λΪKB
 UINT32 BytesPerSector;	 //ÿ���������ֽ���
 UINT32 FATsectors;      //FAT����ռ������
 UINT32 SectorsPerClust; //ÿ�ص�������
 UINT32 FirstFATSector;	 //��һ��FAT����������
 UINT32 FirstDirSector;	 //��һ��Ŀ¼��������

 UINT32 FSINFO_Sec;      //FSINFO�������ڵ�����
 UINT32 Free_nCluster;   //���дصĸ���
 UINT32 Next_Free_Cluster; //��һ�մ�
};

//znFAT�ж��ļ���Ϣ���ϵĶ���
struct FileInfo
{
 INT8 File_Name[13];	    //�����ļ��������ļ�������չ�ļ�����
 INT8 File_Attr;		    //�ļ�����
 struct Time File_CTime;    //�ļ�����ʱ��
 struct Date File_CDate;    //�ļ���������
 //struct Date File_ADate;    //�ļ���������
 //struct Time File_MTime;	//�ļ��޸�ʱ��
 //struct Date File_MDate;	//�ļ��޸�����
 UINT32 File_StartClust;    //�ļ���ʼ��
 UINT32 File_Size;		    //�ļ���С

 UINT32 File_CurClust;   //�ļ���ǰ��
 UINT32 File_CurSec;     //�ļ���ǰ����
 UINT16 File_CurPos;	 //�ļ���ǰ����ƫ����

 UINT8  File_IsEOF;      //�ļ��Ƿ񵽴����λ��

 UINT32 File_CurOffset;	 //�ļ���ǰƫ����

 UINT32 FDI_Sec; //�ļ�Ŀ¼�����ڵ�����
 UINT8  nFDI; //�ļ�Ŀ¼���������е�����

 #ifdef USE_LFN //���ʹ�ó��������ļ���Ϣ���ϰ�������������¶��� 
 UINT8 have_lfn; //��ʾ���ļ��Ƿ��г���
 UINT16 longname[MAX_LFN_LEN+1]; //����װ�س�����UNICODE�룬���ʵ���ļ��ĳ�������MAX_LFN_LEN����ֱ�ӽض�
 #endif

 //----ACCCB��ر�������-----
 #ifndef RT_UPDATE_CLUSTER_CHAIN
 #ifdef USE_ALONE_CCCB
 UINT32 acccb_buf[CCCB_LEN]; //ACCCB�Ļ��������������ضεķ�ʽ����¼����
 UINT8  acccb_counter; 
 UINT32 acccb_curval;
 #endif
 #endif
 //----------------------------

 #ifdef USE_EXCHANGE_BUFFER
 #ifdef USE_ALONE_EXB
 UINT8 exb_buf[ZNFAT_BUF_SIZE];
 UINT32 exb_cursec;
 #endif
 #endif
};

//�����Ƕ��û����õĺ���������

UINT8 znFAT_Device_Init(void); //�洢�豸��ʼ�����ײ������ӿ� 
UINT8 znFAT_Init(void); //�ļ�ϵͳ��ʼ�� 
UINT8 znFAT_Select_Device(UINT8 devno,struct znFAT_Init_Args *pinitargs); //�ڶ��豸����£�����ѡ��ĳһ���豸 

UINT32 znFAT_ReadData(struct FileInfo *pFI,UINT32 offset,UINT32 len,UINT8 *app_Buffer); //���ݶ�ȡ 
UINT32 znFAT_ReadDataX(struct FileInfo *pfi,UINT32 offset,UINT32 len);
UINT8 znFAT_Seek(struct FileInfo *pFI,UINT32 offset); //�ļ���λ 
UINT8 znFAT_Open_File(struct FileInfo *pFI,INT8 *filepath,UINT32 n,UINT8 is_file); //�ļ��� 
UINT8 znFAT_Enter_Dir(INT8 *dirpath,UINT32 *pCluster,UINT32 *pos); //����Ŀ¼ 
UINT8 znFAT_Create_File(struct FileInfo *pfi,INT8 *pfn,struct DateTime *pdt); //�����ļ� 
UINT8 znFAT_Create_Dir(INT8 *pdp,struct DateTime *pdt); //����Ŀ¼ 
UINT8 znFAT_Delete_Dir(INT8 *dirpath); //ɾ��Ŀ¼ 
UINT8 znFAT_Delete_File(INT8 *filepath); //ɾ���ļ� 
UINT8 znFAT_Make_FS(UINT32 tt_sec,UINT16 clu_sz); //��ʽ�� 

UINT32 znFAT_WriteData(struct FileInfo *pfi,UINT32 len,UINT8 *pbuf); //д������ 
UINT8 znFAT_Dump_Data(struct FileInfo *pfi,UINT32 offset); //�ض��ļ����� 

UINT8 znFAT_Prepare_Space_For_File(struct FileInfo *pfi,UINT32 datalen); //��ģʽ�е�Ԥ��Ϊ�ļ�׼���ռ� 
UINT32 znFAT_WriteData_Large(struct FileInfo *pfi,UINT32 offset,UINT32 nSec,UINT8 *pbuf); //��ģʽ�е����ļ�������д������ 

UINT8 znFAT_Close_File(struct FileInfo *pfi); //�ر��ļ������������û�д�ʵʱ�ļ���С���£����ļ��������������д��͸��Ĳ�����������ô˺��� 
UINT8 znFAT_Flush_FS(void); //ˢ���ļ�ϵͳ�����Ϣ�����������û�д�ʵʱ�ļ�ϵͳ��Ϣ���£����ڳ�����һ��Ҫ���ô˺��������򽫵����ļ�ϵͳ��ز�������
//======================

#endif