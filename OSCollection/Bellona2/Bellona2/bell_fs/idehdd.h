#ifndef VFS_IDE_HDD_BLK_DEV_HEADER_jj
#define VFS_IDE_HDD_BLK_DEV_HEADER_jj

#include "hddpart.h"

typedef struct MBSTag{	// �ϵ��ũ�� �����ͺ�Ʈ ����
    char			rsv[0x1BE];
    PartitionStt    part[4];
    unsigned short  wSignature;
}MBSStt;

typedef struct IDEHddTag {
	int				nDrive;
	MBSStt			mbs;
	BlkDevObjStt	part_dev_obj[4];
}IDEHddStt;
					
extern int init_ide_hdd_driver();
extern int close_ide_hdd_driver();

#endif