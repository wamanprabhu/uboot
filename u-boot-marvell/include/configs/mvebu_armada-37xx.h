/*
 * Copyright (C) 2016 Stefan Roese <sr@denx.de>
 *
 * SPDX-License-Identifier:	GPL-2.0+
 */

#ifndef _CONFIG_MVEBU_ARMADA_37XX_H
#define _CONFIG_MVEBU_ARMADA_37XX_H

#include <asm/arch/soc.h>

/*
 * High Level Configuration Options (easy to change)
 */

#define	CONFIG_SYS_TEXT_BASE	0x00000000

/* additions for new ARM relocation support */
#define CONFIG_SYS_SDRAM_BASE	0x00000000

#define CONFIG_NR_DRAM_BANKS	4

/* auto boot */
#define CONFIG_PREBOOT

#define CONFIG_BAUDRATE			115200
#define CONFIG_SYS_BAUDRATE_TABLE	{ 9600, 19200, 38400, 57600, \
					  115200, 230400, 460800, 921600 }

/*
 * For booting Linux, the board info and command line data
 * have to be in the first 8 MB of memory, since this is
 * the maximum mapped by the Linux kernel during initialization.
 */
#define CONFIG_CMDLINE_TAG		/* enable passing of ATAGs  */
#define CONFIG_INITRD_TAG		/* enable INITRD tag */
#define CONFIG_SETUP_MEMORY_TAGS	/* enable memory tag */

#define	CONFIG_SYS_CBSIZE	1024	/* Console I/O Buff Size */
#define	CONFIG_SYS_PBSIZE	(CONFIG_SYS_CBSIZE \
		+sizeof(CONFIG_SYS_PROMPT) + 16)	/* Print Buff */

/*
 * Size of malloc() pool
 */
#define CONFIG_SYS_MALLOC_LEN	(4 << 20) /* 4MiB for malloc() */

/*
 * Other required minimal configurations
 */
#define CONFIG_SYS_LONGHELP
#define CONFIG_AUTO_COMPLETE
#define CONFIG_CMDLINE_EDITING
#define CONFIG_ARCH_CPU_INIT		/* call arch_cpu_init() */
#define CONFIG_SYS_LOAD_ADDR	0x00800000	/* default load adr- 8M */
#define CONFIG_SYS_MEMTEST_START 0x00800000	/* 8M */
#define CONFIG_SYS_MEMTEST_END	0x00ffffff	/*(_16M -1) */
#define CONFIG_SYS_RESET_ADDRESS 0xffff0000	/* Rst Vector Adr */
#define CONFIG_SYS_MAXARGS	32	/* max number of command args */

#define CONFIG_SYS_ALT_MEMTEST

/* End of 16M scrubbed by training in bootrom */
#define CONFIG_SYS_INIT_SP_ADDR         (CONFIG_SYS_TEXT_BASE + 0xFF0000)

/*
 * I2C
 */
#define CONFIG_I2C_MV
#define CONFIG_SYS_I2C_SLAVE		0x0
/*
 * The EEPROM ST M24C64 has 32 byte page write mode and takes up to 10 msec.
 */
#define CONFIG_SYS_EEPROM_PAGE_WRITE_DELAY_MS 10

/*
 * SPI Flash configuration
 */
#define CONFIG_ENV_SPI_BUS		0
#define CONFIG_ENV_SPI_CS		0

/* SPI NOR flash default params, used by sf commands */
#define CONFIG_SF_DEFAULT_SPEED		1000000
#define CONFIG_SF_DEFAULT_MODE		SPI_MODE_0
#define CONFIG_ENV_SPI_MODE		CONFIG_SF_DEFAULT_MODE

/* Environment in SPI NOR flash */
#define CONFIG_ENV_IS_IN_SPI_FLASH
#define CONFIG_ENV_OFFSET		0x180000 /* as Marvell U-Boot version */
#define CONFIG_ENV_SIZE			(64 << 10) /* 64KiB */
#define CONFIG_ENV_SECT_SIZE		(64 << 10) /* 64KiB sectors */

/* Environment in MMC */
#define CONFIG_SYS_MMC_ENV_DEV		1 /* 0 means sdio, 1 means mmc. */
/* partition 0: user data partition.
 * partition 1: boot partition 1 (BOOT0).
 * partition 2: boot partition 2 (BOOT1).
 */
#define CONFIG_SYS_MMC_ENV_PART		1

/*
 * Ethernet Driver configuration
 */
#define CONFIG_MVNETA		/* Enable Marvell Gbe Controller Driver */
#define CONFIG_ENV_OVERWRITE	/* ethaddr can be reprogrammed */
#define CONFIG_PHY_GIGE		/* GbE speed/duplex detect */
#define CONFIG_ARP_TIMEOUT	200
#define CONFIG_NET_RETRY_COUNT	50
#define CONFIG_PHY_MARVELL

/* USB 2.0 */
#define CONFIG_SYS_USB_EHCI_MAX_ROOT_PORTS 3

/* USB 3.0 */
#define CONFIG_SYS_USB_XHCI_MAX_ROOT_PORTS 3

#define CONFIG_USB_MAX_CONTROLLER_COUNT (CONFIG_SYS_USB_EHCI_MAX_ROOT_PORTS + \
					 CONFIG_SYS_USB_XHCI_MAX_ROOT_PORTS)

/* USB ethernet */
#define CONFIG_USB_HOST_ETHER
#define CONFIG_USB_ETHER_ASIX
#define CONFIG_USB_ETHER_MCS7830
#define CONFIG_USB_ETHER_RTL8152
#define CONFIG_USB_ETHER_SMSC95XX

/*
 * SATA/SCSI/AHCI configuration
 */
#define CONFIG_SCSI
#define CONFIG_SCSI_AHCI
#define CONFIG_SCSI_AHCI_PLAT
#define CONFIG_LIBATA
#define CONFIG_LBA48
#define CONFIG_SYS_64BIT_LBA

#define CONFIG_SYS_SCSI_MAX_SCSI_ID	2
#define CONFIG_SYS_SCSI_MAX_LUN		1
#define CONFIG_SYS_SCSI_MAX_DEVICE	(CONFIG_SYS_SCSI_MAX_SCSI_ID * \
					 CONFIG_SYS_SCSI_MAX_LUN)

/* MMC/SD IP block */
#define CONFIG_SUPPORT_VFAT

/*
 * PCI configuration
 */
#ifdef CONFIG_PCIE_ADVK
#define CONFIG_E1000
#define CONFIG_CMD_PCI
#endif

#define CONFIG_DEFAULT_CONSOLE		"console=ttyMV0,115200 "	\
					"earlycon=ar3700_uart,0xd0012000"
/* Add network parameters when network command is enabled */
#ifdef CONFIG_CMD_NET
/* Environment */
#define CONFIG_IPADDR			192.168.1.101	/* In order to cause an error */
#define CONFIG_SERVERIP			192.168.1.100	/* In order to cause an error */
#define CONFIG_NETMASK			255.255.255.0
#define CONFIG_GATEWAYIP		192.168.1.1
#define CONFIG_ETHPRIME			"eth0"
#endif /* CONFIG_CMD_NET */

/* Default Env vars */
/* Boot Argument Buffer Size */
#define CONFIG_SYS_BARGSIZE             CONFIG_SYS_CBSIZE
/* Default Dir for NFS */
#define CONFIG_ROOTPATH                 "/srv/nfs/"
#define CONFIG_EXTRA_ENV_SETTINGS	"kernel_addr=0x2000000\0"	\
					"offset_kernel 0x200000"	\
					"initrd_addr=0xa00000\0"	\
					"initrd_size=0x2000000\0"	\
					"fdt_addr=0x1000000\0"		\
					"offset_dtb 0xd00000\0"		\
					"loadaddr=0x2000000\0"		\
					"fdt_high=0xffffffffffffffff\0"	\
					"hostname=uDPU\0"		\
					"ramfs_addr=0x3000000\0"	\
					"offset_ramfs 0xd10000\0"	\
					"ramfs_name=-\0"		\
					"ramfs_image_size=-\0"		\
					"fdt_name=armada-3720-db-sfp.dtb\0"		\
					"dtb_size=-\0"			\
					"netdev=eth0\0"			\
					"image_name=openwrt-armada-3720-db-Image\0"		\
					"kernel_image_size=-\0"		\
					"get_ramfs=if test \"${ramfs_name}\" "\
					"!= \"-\"; then setenv ramfs_addr "\
					"0x3000000; tftpboot ${ramfs_addr} "\
					"${ramfs_name}; else setenv "	\
					"ramfs_addr -;fi\0"		\
					"get_images_spi=sf probe; sf read ${kernel_addr} "\
					"${offset_kernel} ${kernel_image_size}; sf read ${fdt_addr} "\
					"${offset_dtb} ${dtb_size}; sf read "\
					"$ramfs_addr $offset_ramfs $ramfs_image_size'\0"	\
					"console=" CONFIG_DEFAULT_CONSOLE "\0"\
					"root=root=/dev/mtdblock2 rw\0"	\
					"set_bootargs=setenv bootargs "	\
					"${console} ${root} ip=${ipaddr}"\
					":${serverip}:${gatewayip}:"	\
					"${netmask}:${hostname}"	\
					":${netdev}:none nfsroot=${serverip}"\
					":${rootpath} ${extra_params}"

#define CONFIG_BOOTCOMMAND		"run set_bootargs; "\
					"booti ${kernel_addr} - "\
					"${fdt_addr}"

#endif /* _CONFIG_MVEBU_ARMADA_37XX_H */
