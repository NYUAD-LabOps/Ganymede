/**************************************************************************/ 
/*                                                                        */ 
/*            Copyright (c) 1996-2019 by Express Logic Inc.               */ 
/*                                                                        */ 
/*  This software is copyrighted by and is the sole property of Express   */ 
/*  Logic, Inc.  All rights, title, ownership, or other interests         */ 
/*  in the software remain the property of Express Logic, Inc.  This      */ 
/*  software may only be used in accordance with the corresponding        */ 
/*  license agreement.  Any unauthorized use, duplication, transmission,  */ 
/*  distribution, or disclosure of this software is expressly forbidden.  */ 
/*                                                                        */
/*  This Copyright notice may not be removed or modified without prior    */ 
/*  written consent of Express Logic, Inc.                                */ 
/*                                                                        */ 
/*  Express Logic, Inc. reserves the right to modify this software        */ 
/*  without notice.                                                       */ 
/*                                                                        */ 
/*  Express Logic, Inc.                     info@expresslogic.com         */
/*  11423 West Bernardo Court               http://www.expresslogic.com   */
/*  San Diego, CA  92127                                                  */
/*                                                                        */
/**************************************************************************/


/**************************************************************************/
/**************************************************************************/
/**                                                                       */ 
/** USBX Component                                                        */ 
/**                                                                       */
/**   Storage Class                                                       */
/**                                                                       */
/**************************************************************************/
/**************************************************************************/


/**************************************************************************/ 
/*                                                                        */ 
/*  COMPONENT DEFINITION                                   RELEASE        */ 
/*                                                                        */ 
/*    ux_host_class_storage.h                             PORTABLE C      */ 
/*                                                           5.9          */ 
/*  AUTHOR                                                                */ 
/*                                                                        */ 
/*    Thierry Giron, Express Logic Inc.                                   */ 
/*                                                                        */ 
/*  DESCRIPTION                                                           */ 
/*                                                                        */ 
/*    This file contains all the header and extern functions used by the  */
/*    USBX storage class.                                                 */ 
/*                                                                        */ 
/*  RELEASE HISTORY                                                       */ 
/*                                                                        */ 
/*    DATE              NAME                      DESCRIPTION             */ 
/*                                                                        */ 
/*  07-01-2007     TCRG                     Initial Version 5.0           */ 
/*  07-04-2008     TCRG                     Modified comment(s),          */ 
/*                                            resulting in version 5.1    */ 
/*  11-11-2008     TCRG                     Modified comment(s),          */ 
/*                                            resulting in version 5.2    */ 
/*  07-10-2009     TCRG                     Modified comment(s), ensure   */ 
/*                                            the SCSI CBW and CSW buffers*/ 
/*                                            are aligned on 32bit and do */ 
/*                                            not rely on the compiler    */ 
/*                                            packing pragma some DMA     */ 
/*                                            engines of certain OHCI     */ 
/*                                            controllers (SH7727 in      */ 
/*                                            particular) requires all    */ 
/*                                            OHCI data buffers to be     */ 
/*                                            aligned on 32 bits even     */ 
/*                                            though OHCI does not demand */ 
/*                                            it, and added trace logic,  */ 
/*                                            resulting in version 5.3    */ 
/*  06-13-2010     TCRG                     Modified comment(s),          */ 
/*                                            resulting in version 5.4    */ 
/*  09-01-2011     TCRG                     Modified comment(s),          */ 
/*                                            resulting in version 5.5    */ 
/*  10-10-2012     TCRG                     Modified comment(s),          */ 
/*                                            resulting in version 5.6    */ 
/*  06-01-2014     TCRG                     Modified comment(s),          */ 
/*                                            resulting in version 5.7    */ 
/*  06-01-2017     TCRG                     Modified comment(s),          */ 
/*                                            resulting in version 5.8    */
/*  08-15-2019     TCRG                     Modified comment(s), and      */ 
/*                                            changed timeout value to    */ 
/*                                            units of millisecond,       */ 
/*                                            added keeping track of data */
/*                                            phase packet length,        */
/*                                            reduce device init delay,   */ 
/*                                            resulting in version 5.9    */ 
/*                                                                        */ 
/**************************************************************************/ 

#ifndef UX_HOST_CLASS_STORAGE_H
#define UX_HOST_CLASS_STORAGE_H


/* Include the FileX API or the FileX stub API in cases where FileX is not
   available.  */

#ifndef  UX_NO_FILEX
#include "fx_api.h"
#else
#include "filex_stub.h"
#endif

/* Define User configurable Storage Class constants.  */

#ifndef UX_MAX_HOST_LUN
#define UX_MAX_HOST_LUN                                     1
#endif

#ifndef UX_HOST_CLASS_STORAGE_MAX_MEDIA
#define UX_HOST_CLASS_STORAGE_MAX_MEDIA                     1
#endif

#ifndef UX_HOST_CLASS_STORAGE_MEMORY_BUFFER_SIZE
#define UX_HOST_CLASS_STORAGE_MEMORY_BUFFER_SIZE            (1024)
#endif

#ifndef UX_HOST_CLASS_STORAGE_MAX_TRANSFER_SIZE
#define UX_HOST_CLASS_STORAGE_MAX_TRANSFER_SIZE             (1024)
#endif

#ifndef UX_HOST_CLASS_STORAGE_THREAD_STACK_SIZE
#define UX_HOST_CLASS_STORAGE_THREAD_STACK_SIZE             UX_THREAD_STACK_SIZE
#endif

/* Define Storage Class constants.  */

#define UX_HOST_CLASS_STORAGE_DEVICE_INIT_DELAY             (200)
#define UX_HOST_CLASS_STORAGE_THREAD_SLEEP_TIME             (2000)
#define UX_HOST_CLASS_STORAGE_INSTANCE_SHUTDOWN_TIMER       (10)
#define UX_HOST_CLASS_STORAGE_THREAD_PRIORITY_CLASS         20
#define UX_HOST_CLASS_STORAGE_TRANSFER_TIMEOUT              10000
#define UX_HOST_CLASS_STORAGE_CBI_STATUS_TIMEOUT            3000
#define UX_HOST_CLASS_STORAGE_CLASS                         8
#define UX_HOST_CLASS_STORAGE_SUBCLASS_RBC                  1
#define UX_HOST_CLASS_STORAGE_SUBCLASS_SFF8020              2
#define UX_HOST_CLASS_STORAGE_SUBCLASS_UFI                  4
#define UX_HOST_CLASS_STORAGE_SUBCLASS_SFF8070              5
#define UX_HOST_CLASS_STORAGE_SUBCLASS_SCSI                 6

#define UX_HOST_CLASS_STORAGE_CBW_SIZE                      64

#define UX_HOST_CLASS_STORAGE_PROTOCOL_CBI                  0
#define UX_HOST_CLASS_STORAGE_PROTOCOL_CB                   1
#define UX_HOST_CLASS_STORAGE_PROTOCOL_BO                   0x50

#define UX_HOST_CLASS_STORAGE_DATA_OUT                      0
#define UX_HOST_CLASS_STORAGE_DATA_IN                       0x80

#define UX_HOST_CLASS_STORAGE_CSW_PASSED                    0
#define UX_HOST_CLASS_STORAGE_CSW_FAILED                    1
#define UX_HOST_CLASS_STORAGE_CSW_PHASE_ERROR               2

#define UX_HOST_CLASS_STORAGE_CBW_SIGNATURE_MASK            0x43425355
#define UX_HOST_CLASS_STORAGE_CBW_TAG_MASK                  0x55534243

#define UX_HOST_CLASS_STORAGE_MEDIA_NAME                    "usb disk"

#define UX_HOST_CLASS_STORAGE_MEDIA_REMOVABLE               0x80
#define UX_HOST_CLASS_STORAGE_MEDIA_UNKNOWN                 0
#define UX_HOST_CLASS_STORAGE_MEDIA_KNOWN                   1

#define UX_HOST_CLASS_STORAGE_MEDIA_FAT_DISK                0
#define UX_HOST_CLASS_STORAGE_MEDIA_CDROM                   5
#define UX_HOST_CLASS_STORAGE_MEDIA_OPTICAL_DISK            7
#define UX_HOST_CLASS_STORAGE_MEDIA_IOMEGA_CLICK            0x55

#define UX_HOST_CLASS_STORAGE_RESET                         0xff
#define UX_HOST_CLASS_STORAGE_GET_MAX_LUN                   0xfe

#define UX_HOST_CLASS_STORAGE_TRANSPORT_ERROR               1
#define UX_HOST_CLASS_STORAGE_COMMAND_ERROR                 2
#define UX_HOST_CLASS_STORAGE_SENSE_ERROR                   3

#define UX_HOST_CLASS_STORAGE_SECTOR_SIZE_FAT               512
#define UX_HOST_CLASS_STORAGE_SECTOR_SIZE_OTHER             2048

#define UX_HOST_CLASS_STORAGE_REQUEST_SENSE_RETRY           10

#define UX_HOST_CLASS_STORAGE_START_MEDIA                   1
#define UX_HOST_CLASS_STORAGE_STOP_MEDIA                    0


#define UX_HOST_CLASS_STORAGE_MEDIA_UNMOUNTED               0
#define UX_HOST_CLASS_STORAGE_MEDIA_MOUNTED                 1

/* Define Storage Class SCSI command constants.  */

#define UX_HOST_CLASS_STORAGE_SCSI_TEST_READY               0x00
#define UX_HOST_CLASS_STORAGE_SCSI_REQUEST_SENSE            0x03
#define UX_HOST_CLASS_STORAGE_SCSI_FORMAT                   0x04
#define UX_HOST_CLASS_STORAGE_SCSI_INQUIRY                  0x12
#define UX_HOST_CLASS_STORAGE_SCSI_MODE_SENSE_SHORT         0x1a
#define UX_HOST_CLASS_STORAGE_SCSI_START_STOP               0x1b
#define UX_HOST_CLASS_STORAGE_SCSI_READ_FORMAT_CAPACITY     0x23
#define UX_HOST_CLASS_STORAGE_SCSI_READ_CAPACITY            0x25
#define UX_HOST_CLASS_STORAGE_SCSI_READ16                   0x28
#define UX_HOST_CLASS_STORAGE_SCSI_WRITE16                  0x2a
#define UX_HOST_CLASS_STORAGE_SCSI_VERIFY                   0x2f
#define UX_HOST_CLASS_STORAGE_SCSI_MODE_SELECT              0x55
#define UX_HOST_CLASS_STORAGE_SCSI_MODE_SENSE               0x5a
#define UX_HOST_CLASS_STORAGE_SCSI_READ32                   0xa8 
#define UX_HOST_CLASS_STORAGE_SCSI_WRITE32                  0xaa


/* Define Storage Class SCSI command block wrapper constants.  */

#define UX_HOST_CLASS_STORAGE_CBW_SIGNATURE                 0
#define UX_HOST_CLASS_STORAGE_CBW_TAG                       4
#define UX_HOST_CLASS_STORAGE_CBW_DATA_LENGTH               8
#define UX_HOST_CLASS_STORAGE_CBW_FLAGS                     12
#define UX_HOST_CLASS_STORAGE_CBW_LUN                       13
#define UX_HOST_CLASS_STORAGE_CBW_CB_LENGTH                 14
#define UX_HOST_CLASS_STORAGE_CBW_CB                        15


/* Define Storage Class SCSI response status wrapper constants.  */

#define UX_HOST_CLASS_STORAGE_CSW_SIGNATURE                 0
#define UX_HOST_CLASS_STORAGE_CSW_TAG                       4
#define UX_HOST_CLASS_STORAGE_CSW_DATA_RESIDUE              8
#define UX_HOST_CLASS_STORAGE_CSW_STATUS                    12
#define UX_HOST_CLASS_STORAGE_CSW_LENGTH                    13


/* Define Storage Class SCSI inquiry command constants.  */ 

#define UX_HOST_CLASS_STORAGE_INQUIRY_OPERATION             0
#define UX_HOST_CLASS_STORAGE_INQUIRY_LUN                   1
#define UX_HOST_CLASS_STORAGE_INQUIRY_PAGE_CODE             2
#define UX_HOST_CLASS_STORAGE_INQUIRY_ALLOCATION_LENGTH     4
#define UX_HOST_CLASS_STORAGE_INQUIRY_COMMAND_LENGTH_UFI    12
#define UX_HOST_CLASS_STORAGE_INQUIRY_COMMAND_LENGTH_SBC    06


/* Define Storage Class SCSI inquiry response constants.  */

#define UX_HOST_CLASS_STORAGE_INQUIRY_RESPONSE_PERIPHERAL_TYPE          0
#define UX_HOST_CLASS_STORAGE_INQUIRY_RESPONSE_REMOVABLE_MEDIA          1
#define UX_HOST_CLASS_STORAGE_INQUIRY_RESPONSE_DATA_FORMAT              3
#define UX_HOST_CLASS_STORAGE_INQUIRY_RESPONSE_ADDITIONAL_LENGTH        4
#define UX_HOST_CLASS_STORAGE_INQUIRY_RESPONSE_VENDOR_INFORMATION       8
#define UX_HOST_CLASS_STORAGE_INQUIRY_RESPONSE_PRODUCT_ID               16
#define UX_HOST_CLASS_STORAGE_INQUIRY_RESPONSE_PRODUCT_REVISION         32
#define UX_HOST_CLASS_STORAGE_INQUIRY_RESPONSE_LENGTH                   36


/* Define Storage Class SCSI start/stop command constants.  */

#define UX_HOST_CLASS_STORAGE_START_STOP_OPERATION                      0
#define UX_HOST_CLASS_STORAGE_START_STOP_LBUFLAGS                       1
#define UX_HOST_CLASS_STORAGE_START_STOP_START_BIT                      4
#define UX_HOST_CLASS_STORAGE_START_STOP_COMMAND_LENGTH_UFI             12
#define UX_HOST_CLASS_STORAGE_START_STOP_COMMAND_LENGTH_SBC             12


/* Define Storage Class SCSI mode sense command constants.  */

#define UX_HOST_CLASS_STORAGE_MODE_SENSE_OPERATION                      0
#define UX_HOST_CLASS_STORAGE_MODE_SENSE_LUN                            1
#define UX_HOST_CLASS_STORAGE_MODE_SENSE_PC_PAGE_CODE                   2
#define UX_HOST_CLASS_STORAGE_MODE_SENSE_PARAMETER_LIST_LENGTH          7
#define UX_HOST_CLASS_STORAGE_MODE_SENSE_COMMAND_LENGTH_UFI             12
#define UX_HOST_CLASS_STORAGE_MODE_SENSE_COMMAND_LENGTH_SBC             12

/* Define Storage Class SCSI mode sense command constants.  */

#define UX_HOST_CLASS_STORAGE_MODE_SENSE_RESPONSE_MODE_DATA_LENGTH      0
#define UX_HOST_CLASS_STORAGE_MODE_SENSE_RESPONSE_MEDIUM_TYPE_CODE      2
#define UX_HOST_CLASS_STORAGE_MODE_SENSE_RESPONSE_ATTRIBUTES_SHORT      2
#define UX_HOST_CLASS_STORAGE_MODE_SENSE_RESPONSE_ATTRIBUTES            3
#define UX_HOST_CLASS_STORAGE_MODE_SENSE_RESPONSE_ATTRIBUTES_WP         0x80

/* Define Storage Class SCSI request sense command constants.  */

#define UX_HOST_CLASS_STORAGE_REQUEST_SENSE_OPERATION                   0
#define UX_HOST_CLASS_STORAGE_REQUEST_SENSE_LUN                         1
#define UX_HOST_CLASS_STORAGE_REQUEST_SENSE_ALLOCATION_LENGTH           4
#define UX_HOST_CLASS_STORAGE_REQUEST_SENSE_COMMAND_LENGTH_UFI          12
#define UX_HOST_CLASS_STORAGE_REQUEST_SENSE_COMMAND_LENGTH_SBC          12


/* Define Storage Class request sense response constants.  */

#define UX_HOST_CLASS_STORAGE_REQUEST_SENSE_RESPONSE_ERROR_CODE         0
#define UX_HOST_CLASS_STORAGE_REQUEST_SENSE_RESPONSE_SENSE_KEY          2
#define UX_HOST_CLASS_STORAGE_REQUEST_SENSE_RESPONSE_INFORMATION        3
#define UX_HOST_CLASS_STORAGE_REQUEST_SENSE_RESPONSE_ADD_LENGTH         7
#define UX_HOST_CLASS_STORAGE_REQUEST_SENSE_RESPONSE_CODE               12
#define UX_HOST_CLASS_STORAGE_REQUEST_SENSE_RESPONSE_CODE_QUALIFIER     13
#define UX_HOST_CLASS_STORAGE_REQUEST_SENSE_RESPONSE_LENGTH             18


/* Define Storage Class read format  command constants.  */

#define UX_HOST_CLASS_STORAGE_READ_FORMAT_OPERATION                     0
#define UX_HOST_CLASS_STORAGE_READ_FORMAT_LUN                           1
#define UX_HOST_CLASS_STORAGE_READ_FORMAT_LBA                           2
#define UX_HOST_CLASS_STORAGE_READ_FORMAT_PARAMETER_LIST_LENGTH         7
#define UX_HOST_CLASS_STORAGE_READ_FORMAT_COMMAND_LENGTH_UFI            12
#define UX_HOST_CLASS_STORAGE_READ_FORMAT_COMMAND_LENGTH_SBC            10
#define UX_HOST_CLASS_STORAGE_READ_FORMAT_RESPONSE_LENGTH               0xFC

/* Define Storage Class read capacity command constants.  */

#define UX_HOST_CLASS_STORAGE_READ_CAPACITY_OPERATION                   0
#define UX_HOST_CLASS_STORAGE_READ_CAPACITY_LUN                         1
#define UX_HOST_CLASS_STORAGE_READ_CAPACITY_LBA                         2
#define UX_HOST_CLASS_STORAGE_READ_CAPACITY_COMMAND_LENGTH_UFI          12
#define UX_HOST_CLASS_STORAGE_READ_CAPACITY_COMMAND_LENGTH_SBC          10
#define UX_HOST_CLASS_STORAGE_READ_CAPACITY_RESPONSE_LENGTH             8

#define UX_HOST_CLASS_STORAGE_READ_CAPACITY_DATA_LBA                    0
#define UX_HOST_CLASS_STORAGE_READ_CAPACITY_DATA_SECTOR_SIZE            4


/* Define Storage Class test unit read command constants.  */

#define UX_HOST_CLASS_STORAGE_TEST_READY_OPERATION                      0
#define UX_HOST_CLASS_STORAGE_TEST_READY_LUN                            1
#define UX_HOST_CLASS_STORAGE_TEST_READY_COMMAND_LENGTH_UFI             12
#define UX_HOST_CLASS_STORAGE_TEST_READY_COMMAND_LENGTH_SBC             6

/* Define Storage Class SCSI read command constants.  */

#define UX_HOST_CLASS_STORAGE_READ_OPERATION                            0
#define UX_HOST_CLASS_STORAGE_READ_LUN                                  1
#define UX_HOST_CLASS_STORAGE_READ_LBA                                  2
#define UX_HOST_CLASS_STORAGE_READ_TRANSFER_LENGTH                      7
#define UX_HOST_CLASS_STORAGE_READ_COMMAND_LENGTH_UFI                   12
#define UX_HOST_CLASS_STORAGE_READ_COMMAND_LENGTH_SBC                   10


/* Define Storage Class SCSI write command constants.  */

#define UX_HOST_CLASS_STORAGE_WRITE_OPERATION                           0
#define UX_HOST_CLASS_STORAGE_WRITE_LUN                                 1
#define UX_HOST_CLASS_STORAGE_WRITE_LBA                                 2
#define UX_HOST_CLASS_STORAGE_WRITE_TRANSFER_LENGTH                     7
#define UX_HOST_CLASS_STORAGE_WRITE_COMMAND_LENGTH_UFI                  12
#define UX_HOST_CLASS_STORAGE_WRITE_COMMAND_LENGTH_SBC                  10


/* Define Storage Class SCSI sense key definition constants.  */

#define UX_HOST_CLASS_STORAGE_SENSE_KEY_NO_SENSE                        0x0
#define UX_HOST_CLASS_STORAGE_SENSE_KEY_RECOVERED_ERROR                 0x1
#define UX_HOST_CLASS_STORAGE_SENSE_KEY_NOT_READY                       0x2
#define UX_HOST_CLASS_STORAGE_SENSE_KEY_MEDIUM_ERROR                    0x3
#define UX_HOST_CLASS_STORAGE_SENSE_KEY_HARDWARE_ERROR                  0x4
#define UX_HOST_CLASS_STORAGE_SENSE_KEY_ILLEGAL_REQUEST                 0x5
#define UX_HOST_CLASS_STORAGE_SENSE_KEY_UNIT_ATTENTION                  0x6
#define UX_HOST_CLASS_STORAGE_SENSE_KEY_DATA_PROTECT                    0x7
#define UX_HOST_CLASS_STORAGE_SENSE_KEY_BLANK_CHECK                     0x8
#define UX_HOST_CLASS_STORAGE_SENSE_KEY_ABORTED_COMMAND                 0x0b
#define UX_HOST_CLASS_STORAGE_SENSE_KEY_VOLUME_OVERFLOW                 0x0d
#define UX_HOST_CLASS_STORAGE_SENSE_KEY_MISCOMPARE                      0x0e

/* Define Mode Sense page codes. */
#define UX_HOST_CLASS_STORAGE_MODE_SENSE_RWER_PAGE                      0x01
#define UX_HOST_CLASS_STORAGE_MODE_SENSE_FD_PAGE                        0x05
#define UX_HOST_CLASS_STORAGE_MODE_SENSE_RBAC_PAGE                      0x1B
#define UX_HOST_CLASS_STORAGE_MODE_SENSE_TP_PAGE                        0x1C
#define UX_HOST_CLASS_STORAGE_MODE_SENSE_ALL_PAGE                       0x3F

/* Define Mode Sense page codes response length . */
#define UX_HOST_CLASS_STORAGE_MODE_SENSE_HEADER_PAGE_LENGTH             0x08
#define UX_HOST_CLASS_STORAGE_MODE_SENSE_RWER_PAGE_LENGTH               0x0c
#define UX_HOST_CLASS_STORAGE_MODE_SENSE_FD_PAGE_LENGTH                 0x20
#define UX_HOST_CLASS_STORAGE_MODE_SENSE_RBAC_PAGE_LENGTH               0x0c
#define UX_HOST_CLASS_STORAGE_MODE_SENSE_TP_PAGE_LENGTH                 0x08
#define UX_HOST_CLASS_STORAGE_MODE_SENSE_ALL_PAGE_LENGTH                0xC0

/* Define Storage Class useful error sense key/code constant.  */

#define UX_HOST_CLASS_STORAGE_ERROR_MEDIA_NOT_READ                      0x023A00


/* Define Storage Class MS-DOS partition entry constants.  */

#define UX_HOST_CLASS_STORAGE_PARTITION_SIGNATURE                       0xaa55
#define UX_HOST_CLASS_STORAGE_PARTITION_TABLE_START                     446

#define UX_HOST_CLASS_STORAGE_PARTITION_BOOT_FLAG                       0
#define UX_HOST_CLASS_STORAGE_PARTITION_START_HEAD                      1
#define UX_HOST_CLASS_STORAGE_PARTITION_START_SECTOR                    2
#define UX_HOST_CLASS_STORAGE_PARTITION_START_TRACK                     3
#define UX_HOST_CLASS_STORAGE_PARTITION_TYPE                            4
#define UX_HOST_CLASS_STORAGE_PARTITION_END_HEAD                        5
#define UX_HOST_CLASS_STORAGE_PARTITION_END_SECTOR                      6
#define UX_HOST_CLASS_STORAGE_PARTITION_END_TRACK                       7
#define UX_HOST_CLASS_STORAGE_PARTITION_SECTORS_BEFORE                  8
#define UX_HOST_CLASS_STORAGE_PARTITION_NUMBER_SECTORS                  12
#define UX_HOST_CLASS_STORAGE_PARTITION_TABLE_SIZE                      16

#define UX_HOST_CLASS_STORAGE_PARTITION_FAT_12                          1
#define UX_HOST_CLASS_STORAGE_PARTITION_FAT_16                          4
#define UX_HOST_CLASS_STORAGE_PARTITION_EXTENDED                        5
#define UX_HOST_CLASS_STORAGE_PARTITION_FAT_16L                         6
#define UX_HOST_CLASS_STORAGE_PARTITION_FAT_32_1                        0x0b
#define UX_HOST_CLASS_STORAGE_PARTITION_FAT_32_2                        0x0c
#define UX_HOST_CLASS_STORAGE_PARTITION_FAT_16_LBA_MAPPED               0x0e
#define UX_HOST_CLASS_STORAGE_PARTITION_EXTENDED_LBA_MAPPED             0x0f

/* Define Storage Class instance structure.  */

#define UX_HOST_CLASS_STORAGE_CBW_LENGTH                        31
#define UX_HOST_CLASS_STORAGE_CSW_LENGTH                        13
#define UX_HOST_CLASS_STORAGE_CBW_LENGTH_ALIGNED                64
#define UX_HOST_CLASS_STORAGE_CSW_LENGTH_ALIGNED                64


typedef struct UX_HOST_CLASS_STORAGE_STRUCT
{

    struct UX_HOST_CLASS_STORAGE_STRUCT  
                    *ux_host_class_storage_next_instance;
    UX_HOST_CLASS   *ux_host_class_storage_class;
    UX_DEVICE       *ux_host_class_storage_device;
    UX_INTERFACE    *ux_host_class_storage_interface;
    UX_ENDPOINT     *ux_host_class_storage_bulk_out_endpoint;
    UX_ENDPOINT     *ux_host_class_storage_bulk_in_endpoint;
    UX_ENDPOINT     *ux_host_class_storage_interrupt_endpoint;
    UCHAR           ux_host_class_storage_cbw[UX_HOST_CLASS_STORAGE_CBW_LENGTH_ALIGNED];
    UCHAR           ux_host_class_storage_saved_cbw[UX_HOST_CLASS_STORAGE_CBW_LENGTH_ALIGNED];
    UCHAR           ux_host_class_storage_csw[UX_HOST_CLASS_STORAGE_CSW_LENGTH_ALIGNED];
    UINT            ux_host_class_storage_state;
    UINT            ux_host_class_storage_media_type;
    UINT            ux_host_class_storage_lun_removable_media_flags[UX_MAX_HOST_LUN];
    UINT            ux_host_class_storage_write_protected_media;
    UINT            ux_host_class_storage_max_lun;
    UINT            ux_host_class_storage_lun;
    UINT            ux_host_class_storage_lun_types[UX_MAX_HOST_LUN];
    ULONG           ux_host_class_storage_sector_size;
    ULONG           ux_host_class_storage_data_phase_length;
    UINT            (*ux_host_class_storage_transport) (struct UX_HOST_CLASS_STORAGE_STRUCT *storage, UCHAR * data_pointer);
    ULONG           ux_host_class_storage_sense_code;
    UCHAR           *ux_host_class_storage_memory;
    TX_SEMAPHORE    ux_host_class_storage_semaphore;
} UX_HOST_CLASS_STORAGE;


/* Define Host Storage Class Media structure.  */

typedef struct UX_HOST_CLASS_STORAGE_MEDIA_STRUCT
{

    FX_MEDIA        ux_host_class_storage_media;
    ULONG           ux_host_class_storage_media_status;
    ULONG           ux_host_class_storage_media_lun;
    ULONG           ux_host_class_storage_media_partition_start;
    ULONG           ux_host_class_storage_media_sector_size;
    VOID            *ux_host_class_storage_media_memory;

} UX_HOST_CLASS_STORAGE_MEDIA;


/* Define Storage Class function prototypes.  */

UINT    _ux_host_class_storage_activate(UX_HOST_CLASS_COMMAND *command);
VOID    _ux_host_class_storage_cbw_initialize(UX_HOST_CLASS_STORAGE *storage, UINT direction,
                                       ULONG data_transfer_length, UINT command_length);
UINT    _ux_host_class_storage_configure(UX_HOST_CLASS_STORAGE *storage);
UINT    _ux_host_class_storage_deactivate(UX_HOST_CLASS_COMMAND *command);
UINT    _ux_host_class_storage_device_initialize(UX_HOST_CLASS_STORAGE *storage);
UINT    _ux_host_class_storage_device_reset(UX_HOST_CLASS_STORAGE *storage);
UINT    _ux_host_class_storage_device_support_check(UX_HOST_CLASS_STORAGE *storage);
VOID    _ux_host_class_storage_driver_entry(FX_MEDIA *media);
UINT    _ux_host_class_storage_endpoints_get(UX_HOST_CLASS_STORAGE *storage);
UINT    _ux_host_class_storage_entry(UX_HOST_CLASS_COMMAND *command);
UINT    _ux_host_class_storage_max_lun_get(UX_HOST_CLASS_STORAGE *storage);
UINT    _ux_host_class_storage_media_capacity_get(UX_HOST_CLASS_STORAGE *storage);
UINT    _ux_host_class_storage_media_characteristics_get(UX_HOST_CLASS_STORAGE *storage);
UINT    _ux_host_class_storage_media_format_capacity_get(UX_HOST_CLASS_STORAGE *storage);
UINT    _ux_host_class_storage_media_mount(UX_HOST_CLASS_STORAGE *storage, ULONG sector);
UINT    _ux_host_class_storage_media_open(UX_HOST_CLASS_STORAGE *storage, ULONG hidden_sectors);
UINT    _ux_host_class_storage_media_protection_check(UX_HOST_CLASS_STORAGE *storage);
UINT    _ux_host_class_storage_media_read(UX_HOST_CLASS_STORAGE *storage, ULONG sector_start,
                                        ULONG sector_count, UCHAR *data_pointer);
UINT    _ux_host_class_storage_media_recovery_sense_get(UX_HOST_CLASS_STORAGE *storage);
UINT    _ux_host_class_storage_media_write(UX_HOST_CLASS_STORAGE *storage, ULONG sector_start,
                                        ULONG sector_count, UCHAR *data_pointer);
UINT    _ux_host_class_storage_partition_read(UX_HOST_CLASS_STORAGE *storage, UCHAR *sector_memory, ULONG sector);
UINT    _ux_host_class_storage_request_sense(UX_HOST_CLASS_STORAGE *storage);
UINT    _ux_host_class_storage_sense_code_translate(UX_HOST_CLASS_STORAGE *storage, UINT status);
UINT    _ux_host_class_storage_start_stop(UX_HOST_CLASS_STORAGE *storage, 
                                            ULONG start_stop_signal);
VOID    _ux_host_class_storage_thread_entry(ULONG class_address);
UINT    _ux_host_class_storage_transport(UX_HOST_CLASS_STORAGE *storage, UCHAR *data_pointer);
UINT    _ux_host_class_storage_transport_bo(UX_HOST_CLASS_STORAGE *storage, UCHAR *data_pointer);
UINT    _ux_host_class_storage_transport_cb(UX_HOST_CLASS_STORAGE *storage, UCHAR *data_pointer);
UINT    _ux_host_class_storage_transport_cbi(UX_HOST_CLASS_STORAGE *storage, UCHAR *data_pointer);
UINT    _ux_host_class_storage_unit_ready_test(UX_HOST_CLASS_STORAGE *storage);

/* Define Storage Class API prototypes.  */

#define  ux_host_class_storage_entry                           _ux_host_class_storage_entry
#define  ux_host_class_storage_media_read                      _ux_host_class_storage_media_read
#define  ux_host_class_storage_media_write                     _ux_host_class_storage_media_write

#endif
