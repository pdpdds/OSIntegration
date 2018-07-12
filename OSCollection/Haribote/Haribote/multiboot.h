#pragma once
#include "Types.h"

/*   _emit is DB equivalent but not DD equivalent exist
so we define it ourself */
#define dd(x)                            \
        __asm _emit     (x)       & 0xff \
        __asm _emit     (x) >> 8  & 0xff \
        __asm _emit     (x) >> 16 & 0xff \
        __asm _emit     (x) >> 24 & 0xff

#define KERNEL_STACK			0x0040000

/*  This is the one of most important thing to be able to load a PE kernel
with GRUB. Because PE header are in the begining of the file, code section
will be shifted. The value used to shift the code section is the linker
align option /ALIGN:value. Note the header size sum is larger than 512,
so ALIGN value must be greater */
#define   ALIGN               0x400

/*   Must be >= 1Mb for GRUB
Base adress from advanced linker option
*/
#define KERNEL_LOAD_ADDRESS            0x100000
#define KERNEL_END_ADDRESS             0x300000


#define   HEADER_ADRESS         KERNEL_LOAD_ADDRESS+ALIGN

#define MULTIBOOT_HEADER_MAGIC         0x1BADB002
#define MULTIBOOT_BOOTLOADER_MAGIC      0x2BADB002
#define MULTIBOOT_HEADER_FLAGS         0x00010003 
#define MULTIBOOT_HEADER_FLAGS_GUI         0x00010007 
#define STACK_SIZE              0x4000    
#define CHECKSUM            -(MULTIBOOT_HEADER_MAGIC + MULTIBOOT_HEADER_FLAGS)
#define CHECKSUM_GUI            -(MULTIBOOT_HEADER_MAGIC + MULTIBOOT_HEADER_FLAGS_GUI)


/* How many bytes from the start of the file we search for the header.  */
#define MULTIBOOT_SEARCH            8192
#define MULTIBOOT_HEADER_ALIGN          4

/* The magic field should contain this.  */
#define MULTIBOOT_HEADER_MAGIC          0x1BADB002

/* This should be in %eax.  */
#define MULTIBOOT_BOOTLOADER_MAGIC      0x2BADB002

/* Alignment of multiboot modules.  */
#define MULTIBOOT_MOD_ALIGN         0x00001000

/* Alignment of the multiboot info structure.  */
#define MULTIBOOT_INFO_ALIGN            0x00000004

/* Flags set in the 'flags' member of the multiboot header.  */

/* Align all boot modules on i386 page (4KB) boundaries.  */
#define MULTIBOOT_PAGE_ALIGN            0x00000001

/* Must pass memory information to OS.  */
#define MULTIBOOT_MEMORY_INFO           0x00000002

/* Must pass video information to OS.  */
#define MULTIBOOT_VIDEO_MODE            0x00000004

/* This flag indicates the use of the address fields in the header.  */
#define MULTIBOOT_AOUT_KLUDGE           0x00010000

/* Flags to be set in the 'flags' member of the multiboot info structure.  */

/* is there basic lower/upper memory information? */
#define MULTIBOOT_INFO_MEMORY           0x00000001
/* is there a boot device set? */
#define MULTIBOOT_INFO_BOOTDEV          0x00000002
/* is the command-line defined? */
#define MULTIBOOT_INFO_CMDLINE          0x00000004
/* are there modules to do something with? */
#define MULTIBOOT_INFO_MODS         0x00000008

/* These next two are mutually exclusive */

/* is there a symbol table loaded? */
#define MULTIBOOT_INFO_AOUT_SYMS        0x00000010
/* is there an ELF section header table? */
#define MULTIBOOT_INFO_ELF_SHDR         0X00000020

/* is there a full memory map? */
#define MULTIBOOT_INFO_MEM_MAP          0x00000040

/* Is there drive info?  */
#define MULTIBOOT_INFO_DRIVE_INFO       0x00000080

/* Is there a config table?  */
#define MULTIBOOT_INFO_CONFIG_TABLE     0x00000100

/* Is there a boot loader name?  */
#define MULTIBOOT_INFO_BOOT_LOADER_NAME     0x00000200

/* Is there a APM table?  */
#define MULTIBOOT_INFO_APM_TABLE        0x00000400

/* Is there video information?  */
#define MULTIBOOT_INFO_VBE_INFO             0x00000800
#define MULTIBOOT_INFO_FRAMEBUFFER_INFO         0x00001000

#pragma pack(push,1)
struct MULTIBOOT_HEADER {
	unsigned int magic;
	unsigned int flags;
	unsigned int checksum;
	unsigned int header_addr;
	unsigned int load_addr;
	unsigned int load_end_addr;
	unsigned int bss_end_addr;
	unsigned int entry_addr;
};

typedef struct tag_ELFHeaderTable
{
	unsigned int num;
	unsigned int size;
	unsigned int addr;
	unsigned int shndx;
}ELFHeaderTable;
typedef struct multiboot_elf_section_header_table multiboot_elf_section_header_table_t;

typedef struct tag_AOUTSymbolTable
{
	unsigned int tabsize;
	unsigned int strsize;
	unsigned int addr;
	unsigned int reserved;
}AOUTSymbolTable;

//Bochs 2.4 doesn't provide a ROM configuration table. Virtual PC does.
struct ROMConfigurationTable
{
	unsigned short Length;
	unsigned char Model;
	unsigned char Submodel;
	unsigned char BiosRevision;
	BOOL DualBus : 1;
	BOOL MicroChannelBus : 1;
	BOOL EBDAExists : 1;
	BOOL WaitForExternalEventSupported : 1;
	BOOL Reserved0 : 1;
	BOOL HasRTC : 1;
	BOOL MultipleInterruptControllers : 1;
	BOOL BiosUsesDMA3 : 1;
	BOOL Reserved1 : 1;
	BOOL DataStreamingSupported : 1;
	BOOL NonStandardKeyboard : 1;
	BOOL BiosControlCpu : 1;
	BOOL BiosGetMemoryMap : 1;
	BOOL BiosGetPosData : 1;
	BOOL BiosKeyboard : 1;
	BOOL DMA32Supported : 1;
	BOOL ImlSCSISupported : 1;
	BOOL ImlLoad : 1;
	BOOL InformationPanelInstalled : 1;
	BOOL SCSISupported : 1;
	BOOL RomToRamSupported : 1;
	BOOL Reserved2 : 3;
	BOOL ExtendedPOST : 1;
	BOOL MemorySplit16MB : 1;
	unsigned char Reserved3 : 1;
	unsigned char AdvancedBIOSPresence : 3;
	BOOL EEPROMPresent : 1;
	BOOL Reserved4 : 1;
	BOOL FlashEPROMPresent : 1;
	BOOL EnhancedMouseMode : 1;
	unsigned char Reserved5 : 6;
};

struct Module
{
	intptr_t ModuleStart;
	intptr_t ModuleEnd;
	intptr_t Name;
	unsigned int Reserved;
};

struct multiboot_mmap_entry
{
	unsigned int size;
	__int64 addr;
	__int64 len;
#define MULTIBOOT_MEMORY_AVAILABLE              1
#define MULTIBOOT_MEMORY_RESERVED               2
	unsigned int type;
};
typedef struct multiboot_mmap_entry multiboot_memory_map_t;

/* Drive Info structure.  */
struct drive_info
{
	/* The size of this structure.  */
	unsigned int size;

	/* The BIOS drive number.  */
	unsigned char drive_number;

	/* The access mode (see below).  */
	unsigned char drive_mode;

	/* The BIOS geometry.  */
	unsigned short drive_cylinders;
	unsigned char drive_heads;
	unsigned char drive_sectors;

	/* The array of I/O ports used for the drive.  */
	unsigned short drive_ports;
};

struct multiboot_color
{
	unsigned char red;
	unsigned char green;
	unsigned char blue;
};

struct APMTable
{
	unsigned short Version;
	unsigned short CS;
	unsigned int Offset;
	unsigned short CS16Bit;	//This is the 16-bit protected mode code segment
	unsigned short DS;
	unsigned short Flags;
	unsigned short CSLength;
	unsigned short CS16BitLength;
	unsigned short DSLength;
};

struct VbeInfoBlock
{
	char Signature[4];
	unsigned short Version;
	short OEMString[2];
	unsigned char Capabilities[4];
	short VideoModes[2];
	short TotalMemory;
};

struct VbeModeInfo
{
	unsigned short Attributes;
	unsigned char WinA;
	unsigned char WinB;
	unsigned short Granularity;
	unsigned short WinSize;
	unsigned short SegmentA;
	unsigned short SegmentB;
	unsigned short WindowFunctionPointer[2];
	unsigned short Pitch;
	unsigned short XResolution;
	unsigned short YResolution;
	unsigned char CharacterWidth;
	unsigned char CharacterHeight;
	unsigned char Planes;
	unsigned char BitsPerPixel;
	unsigned char Banks;
	unsigned char MemoryModel;
	unsigned char BankSize;
	unsigned char ImagePages;
	unsigned char Reserved;

	unsigned char RedMask;
	unsigned char RedPosition;

	unsigned char GreenMask;
	unsigned char GreenPosition;

	unsigned char BlueMask;
	unsigned char BluePosition;

	unsigned char ReservedMask;
	unsigned char ReservedPosition;

	unsigned char DirectColorAttributes;

	unsigned int FrameBuffer;
};

/*struct VbeModeInfo
{
	UINT16 ModeAttributes;
	char WinAAttributes;
	char WinBAttributes;
	UINT16 WinGranularity;
	UINT16 WinSize;
	UINT16 WinASegment;
	UINT16 WinBSegment;
	UINT32 WinFuncPtr;
	short BytesPerScanLine;
	short XRes;
	short YRes;
	char XCharSize;
	char YCharSize;
	char NumberOfPlanes;
	char BitsPerPixel;
	char NumberOfBanks;
	char MemoryModel;
	char BankSize;
	char NumberOfImagePages;
	char res1;
	char RedMaskSize;
	char RedFieldPosition;
	char GreenMaskSize;
	char GreenFieldPosition;
	char BlueMaskSize;
	char BlueFieldPosition;
	char RsvedMaskSize;
	char RsvedFieldPosition;
	char DirectColorModeInfo; 

	UINT32 PhysBasePtr;
	UINT32 OffScreenMemOffset;
	short OffScreenMemSize;
	//VBE 2.1
	short LinbytesPerScanLine;
	char BankNumberOfImagePages;
	char LinNumberOfImagePages;
	char LinRedMaskSize;
	char LinRedFieldPosition;
	char LingreenMaskSize;
	char LinGreenFieldPosition;
	char LinBlueMaskSize;
	char LinBlueFieldPosition;
	char LinRsvdMaskSize;
	char LinRsvdFieldPosition;
	char res2[194];
}*/

typedef struct {
	unsigned short	Offset;
	unsigned short	Segment;
}	t_farptr;

struct VesaControllerInfo {
	char	Signature[4];	// == "VBE2"
	unsigned short	Version;	// == 0x0300 for Vesa 3.0
	t_farptr	OemString;	// isa vbeFarPtr
	unsigned char	Capabilities[4];
	t_farptr	Videomodes;	// isa vbeParPtr
	unsigned short	TotalMemory;// as # of 64KB blocks
};

typedef struct tag_multiboot_info
{
	/* Multiboot info version number */
	unsigned int flags;

	/* Available memory from BIOS */
	unsigned int mem_lower;
	unsigned int mem_upper;

	/* "root" partition */
	unsigned int boot_device;

	/* Kernel command line */
	intptr_t cmdline;

	/* Boot-Module list */
	unsigned int mods_count;
	intptr_t Modules;

	union
	{
		AOUTSymbolTable AOUTTable;
		ELFHeaderTable ELFTable;
	} SymbolTables;

	/* Memory Mapping buffer */
	unsigned int mmap_length;
	unsigned int mmap_addr;

	/* Drive Info buffer */
	unsigned int drives_length;
	intptr_t drives_addr;

	/* ROM configuration table */
	intptr_t ConfigTable;

	/* Boot Loader Name */
	intptr_t boot_loader_name;

	/* APM table */
	intptr_t APMTable;

	/* Video */
	intptr_t vbe_control_info;
	intptr_t vbe_mode_info;
	unsigned short vbe_mode;
	unsigned short vbe_interface_seg;
	unsigned short vbe_interface_off;
	unsigned short vbe_interface_len;

//GRUB2
	__int64 framebuffer_addr;	
	unsigned int framebuffer_pitch;
	unsigned int framebuffer_width;
	unsigned int framebuffer_height;
	unsigned char framebuffer_bpp;
#define MULTIBOOT_FRAMEBUFFER_TYPE_INDEXED 0
#define MULTIBOOT_FRAMEBUFFER_TYPE_RGB     1
#define MULTIBOOT_FRAMEBUFFER_TYPE_EGA_TEXT     2
	unsigned char framebuffer_type;
	union
	{
		struct
		{
			unsigned int framebuffer_palette_addr;
			unsigned short framebuffer_palette_num_colors;
		}framebuffer_palette;
		struct
		{
			unsigned char framebuffer_red_field_position;
			unsigned char framebuffer_red_mask_size;
			unsigned char framebuffer_green_field_position;
			unsigned char framebuffer_green_mask_size;
			unsigned char framebuffer_blue_field_position;
			unsigned char framebuffer_blue_mask_size;
		}framebuffer_MASK;
	};
}multiboot_info;
//typedef struct multiboot_info multiboot_info_t;

#pragma pack(pop)
