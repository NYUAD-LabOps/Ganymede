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
/**   Device Storage Class                                                */
/**                                                                       */
/**************************************************************************/
/**************************************************************************/


/**************************************************************************/
/*                                                                        */
/*  COMPONENT DEFINITION                                   RELEASE        */
/*                                                                        */
/*    ux_device_class_storage.h                           PORTABLE C      */
/*                                                           5.9          */
/*  AUTHOR                                                                */
/*                                                                        */
/*    Thierry Giron, Express Logic Inc.                                   */
/*                                                                        */
/*  DESCRIPTION                                                           */
/*                                                                        */
/*    This file contains all the header and extern functions used by the  */
/*    USBX device storage class.                                          */
/*                                                                        */
/*  RELEASE HISTORY                                                       */
/*                                                                        */
/*    DATE              NAME                      DESCRIPTION             */
/*                                                                        */
/*  07-01-2007     TCRG                     Initial Version 5.0           */
/*  11-11-2008     TCRG                     Modified comment(s), and      */
/*                                            added new read capacity     */
/*                                            response constants,         */
/*                                            resulting in version 5.2    */
/*  07-10-2009     TCRG                     Modified comment(s), and      */
/*                                            added trace logic,          */
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
/*  08-15-2019     TCRG                     Modified comment(s),          */
/*                                            Added support for           */
/*                                            insert/extract client event,*/
/*                                            added support for           */
/*                                            MODE SENSE WP bit, added    */
/*                                            uninitialize prototype,     */
/*                                            added support to customize  */
/*                                            vendor id, product id,      */
/*                                            product revision and        */
/*                                            product serial, through     */
/*                                            initialization parameter,   */
/*                                            added macros and callback   */
/*                                            for SYNCHRONIZE CACHE       */
/*                                            command, added phase error, */
/*                                            added status code for       */
/*                                            control request handling,   */
/*                                            added symbols for ModeSense */
/*                                            modes and operations,       */
/*                                            resulting in version 5.9    */
/*                                                                        */
/**************************************************************************/

#ifndef UX_DEVICE_CLASS_STORAGE_H
#define UX_DEVICE_CLASS_STORAGE_H

/* Define User configurable Storage Class constants.  */

#ifndef UX_MAX_SLAVE_LUN
#define UX_MAX_SLAVE_LUN                                            2
#endif

/* Define Storage Class USB Class constants.  */

#define UX_SLAVE_CLASS_STORAGE_CLASS                                8
#define UX_SLAVE_CLASS_STORAGE_SUBCLASS_RBC                         1
#define UX_SLAVE_CLASS_STORAGE_SUBCLASS_SFF8020                     2
#define UX_SLAVE_CLASS_STORAGE_SUBCLASS_UFI                         4
#define UX_SLAVE_CLASS_STORAGE_SUBCLASS_SFF8070                     5
#define UX_SLAVE_CLASS_STORAGE_SUBCLASS_SCSI                        6
#define UX_SLAVE_CLASS_STORAGE_PROTOCOL_CBI                         0
#define UX_SLAVE_CLASS_STORAGE_PROTOCOL_CB                          1
#define UX_SLAVE_CLASS_STORAGE_PROTOCOL_BO                          0x50

/* Define Storage Class USB MEDIA types.  */
#define UX_SLAVE_CLASS_STORAGE_MEDIA_FAT_DISK                       0
#define UX_SLAVE_CLASS_STORAGE_MEDIA_CDROM                          5
#define UX_SLAVE_CLASS_STORAGE_MEDIA_OPTICAL_DISK                   7
#define UX_SLAVE_CLASS_STORAGE_MEDIA_IOMEGA_CLICK                   0x55



/* Define Storage Class SCSI command constants.  */

#define UX_SLAVE_CLASS_STORAGE_SCSI_TEST_READY                      0x00
#define UX_SLAVE_CLASS_STORAGE_SCSI_REQUEST_SENSE                   0x03
#define UX_SLAVE_CLASS_STORAGE_SCSI_FORMAT                          0x04
#define UX_SLAVE_CLASS_STORAGE_SCSI_INQUIRY                         0x12
#define UX_SLAVE_CLASS_STORAGE_SCSI_MODE_SENSE_SHORT                0x1a
#define UX_SLAVE_CLASS_STORAGE_SCSI_START_STOP                      0x1b
#define UX_SLAVE_CLASS_STORAGE_SCSI_PREVENT_ALLOW_MEDIA_REMOVAL     0x1e
#define UX_SLAVE_CLASS_STORAGE_SCSI_READ_FORMAT_CAPACITY            0x23
#define UX_SLAVE_CLASS_STORAGE_SCSI_READ_CAPACITY                   0x25
#define UX_SLAVE_CLASS_STORAGE_SCSI_READ16                          0x28
#define UX_SLAVE_CLASS_STORAGE_SCSI_WRITE16                         0x2a
#define UX_SLAVE_CLASS_STORAGE_SCSI_VERIFY                          0x2f
#define UX_SLAVE_CLASS_STORAGE_SCSI_SYNCHRONIZE_CACHE               0x35
#define UX_SLAVE_CLASS_STORAGE_SCSI_READ_TOC                        0x43
#define UX_SLAVE_CLASS_STORAGE_SCSI_GET_CONFIGURATION               0x46
#define UX_SLAVE_CLASS_STORAGE_SCSI_GET_STATUS_NOTIFICATION         0x4A
#define UX_SLAVE_CLASS_STORAGE_SCSI_READ_DISK_INFORMATION           0x51
#define UX_SLAVE_CLASS_STORAGE_SCSI_MODE_SELECT                     0x55
#define UX_SLAVE_CLASS_STORAGE_SCSI_MODE_SENSE                      0x5a
#define UX_SLAVE_CLASS_STORAGE_SCSI_READ32                          0xa8
#define UX_SLAVE_CLASS_STORAGE_SCSI_REPORT_KEY                      0xa4
#define UX_SLAVE_CLASS_STORAGE_SCSI_WRITE32                         0xaa
#define UX_SLAVE_CLASS_STORAGE_SCSI_GET_PERFORMANCE                 0xac
#define UX_SLAVE_CLASS_STORAGE_SCSI_READ_DVD_STRUCTURE              0xad

/* Define Storage Class SCSI command block wrapper constants.  */

#define UX_SLAVE_CLASS_STORAGE_CBW_SIGNATURE_MASK                   0x43425355
#define UX_SLAVE_CLASS_STORAGE_CBW_SIGNATURE                        0
#define UX_SLAVE_CLASS_STORAGE_CBW_TAG                              4
#define UX_SLAVE_CLASS_STORAGE_CBW_DATA_LENGTH                      8
#define UX_SLAVE_CLASS_STORAGE_CBW_FLAGS                            12
#define UX_SLAVE_CLASS_STORAGE_CBW_LUN                              13
#define UX_SLAVE_CLASS_STORAGE_CBW_CB_LENGTH                        14
#define UX_SLAVE_CLASS_STORAGE_CBW_CB                               15
#define UX_SLAVE_CLASS_STORAGE_CBW_LENGTH                           31


/* Define Storage Class SCSI response status wrapper constants.  */

#define UX_SLAVE_CLASS_STORAGE_CSW_SIGNATURE_MASK                   0x53425355
#define UX_SLAVE_CLASS_STORAGE_CSW_SIGNATURE                        0
#define UX_SLAVE_CLASS_STORAGE_CSW_TAG                              4
#define UX_SLAVE_CLASS_STORAGE_CSW_DATA_RESIDUE                     8
#define UX_SLAVE_CLASS_STORAGE_CSW_STATUS                           12
#define UX_SLAVE_CLASS_STORAGE_CSW_LENGTH                           13


/* Define Storage Class SCSI inquiry command constants.  */

#define UX_SLAVE_CLASS_STORAGE_INQUIRY_OPERATION                    0
#define UX_SLAVE_CLASS_STORAGE_INQUIRY_LUN                          1
#define UX_SLAVE_CLASS_STORAGE_INQUIRY_PAGE_CODE                    2
#define UX_SLAVE_CLASS_STORAGE_INQUIRY_ALLOCATION_LENGTH            4
#define UX_SLAVE_CLASS_STORAGE_INQUIRY_COMMAND_LENGTH_UFI           12
#define UX_SLAVE_CLASS_STORAGE_INQUIRY_COMMAND_LENGTH_SBC           06


/* Define Storage Class SCSI inquiry response constants.  */

#define UX_SLAVE_CLASS_STORAGE_INQUIRY_RESPONSE_PERIPHERAL_TYPE     0
#define UX_SLAVE_CLASS_STORAGE_INQUIRY_RESPONSE_REMOVABLE_MEDIA     1
#define UX_SLAVE_CLASS_STORAGE_INQUIRY_RESPONSE_DATA_FORMAT         3
#define UX_SLAVE_CLASS_STORAGE_INQUIRY_RESPONSE_ADDITIONAL_LENGTH   4
#define UX_SLAVE_CLASS_STORAGE_INQUIRY_RESPONSE_VENDOR_INFORMATION  8
#define UX_SLAVE_CLASS_STORAGE_INQUIRY_RESPONSE_PRODUCT_ID          16
#define UX_SLAVE_CLASS_STORAGE_INQUIRY_RESPONSE_PRODUCT_REVISION    32
#define UX_SLAVE_CLASS_STORAGE_INQUIRY_RESPONSE_LENGTH              36
#define UX_SLAVE_CLASS_STORAGE_INQUIRY_RESPONSE_LENGTH_CD_ROM       0x5b


/* Define Storage Class SCSI start/stop command constants.  */

#define UX_SLAVE_CLASS_STORAGE_START_STOP_OPERATION                 0
#define UX_SLAVE_CLASS_STORAGE_START_STOP_LBUFLAGS                  1
#define UX_SLAVE_CLASS_STORAGE_START_STOP_START_BIT                 4
#define UX_SLAVE_CLASS_STORAGE_START_STOP_COMMAND_LENGTH_UFI        12
#define UX_SLAVE_CLASS_STORAGE_START_STOP_COMMAND_LENGTH_SBC        6


/* Define Storage Class SCSI mode sense command constants.  */

#define UX_SLAVE_CLASS_STORAGE_MODE_SENSE_OPERATION                  0
#define UX_SLAVE_CLASS_STORAGE_MODE_SENSE_LUN                        1
#define UX_SLAVE_CLASS_STORAGE_MODE_SENSE_PC_PAGE_CODE               2
#define UX_SLAVE_CLASS_STORAGE_MODE_SENSE_PARAMETER_LIST_LENGTH_6    4
#define UX_SLAVE_CLASS_STORAGE_MODE_SENSE_PARAMETER_LIST_LENGTH_10   7
#define UX_SLAVE_CLASS_STORAGE_MODE_SENSE_ALLOCATION_LENGTH_6        4
#define UX_SLAVE_CLASS_STORAGE_MODE_SENSE_ALLOCATION_LENGTH_10       7

#define UX_SLAVE_CLASS_STORAGE_MODE_SENSE_PARAMETER_MEDIUM_TYPE_6    1
#define UX_SLAVE_CLASS_STORAGE_MODE_SENSE_PARAMETER_MEDIUM_TYPE_10   2
#define UX_SLAVE_CLASS_STORAGE_MODE_SENSE_PARAMETER_HEADER_LENGTH_6  4
#define UX_SLAVE_CLASS_STORAGE_MODE_SENSE_PARAMETER_HEADER_LENGTH_10 8

#define UX_SLAVE_CLASS_STORAGE_MODE_SENSE_COMMAND_LENGTH_UFI         12
#define UX_SLAVE_CLASS_STORAGE_MODE_SENSE_COMMAND_LENGTH_SBC         12


/* Define Storage Class SCSI request sense command constants.  */

#define UX_SLAVE_CLASS_STORAGE_REQUEST_SENSE_OPERATION              0
#define UX_SLAVE_CLASS_STORAGE_REQUEST_SENSE_LUN                    1
#define UX_SLAVE_CLASS_STORAGE_REQUEST_SENSE_ALLOCATION_LENGTH      4
#define UX_SLAVE_CLASS_STORAGE_REQUEST_SENSE_COMMAND_LENGTH_UFI     12
#define UX_SLAVE_CLASS_STORAGE_REQUEST_SENSE_COMMAND_LENGTH_SBC     12


/* Define Storage Class request sense response constants.  */

#define UX_SLAVE_CLASS_STORAGE_REQUEST_SENSE_RESPONSE_ERROR_CODE     0
#define UX_SLAVE_CLASS_STORAGE_REQUEST_SENSE_RESPONSE_SENSE_KEY      2
#define UX_SLAVE_CLASS_STORAGE_REQUEST_SENSE_RESPONSE_INFORMATION    3
#define UX_SLAVE_CLASS_STORAGE_REQUEST_SENSE_RESPONSE_ADD_LENGTH     7
#define UX_SLAVE_CLASS_STORAGE_REQUEST_SENSE_RESPONSE_CODE           12
#define UX_SLAVE_CLASS_STORAGE_REQUEST_SENSE_RESPONSE_CODE_QUALIFIER 13
#define UX_SLAVE_CLASS_STORAGE_REQUEST_SENSE_RESPONSE_LENGTH         18
#define UX_SLAVE_CLASS_STORAGE_REQUEST_SENSE_RESPONSE_HEADER_LENGTH  8


/* Define Storage Class read capacity command constants.  */

#define UX_SLAVE_CLASS_STORAGE_READ_CAPACITY_OPERATION              0
#define UX_SLAVE_CLASS_STORAGE_READ_CAPACITY_LUN                    1
#define UX_SLAVE_CLASS_STORAGE_READ_CAPACITY_LBA                    2
#define UX_SLAVE_CLASS_STORAGE_READ_CAPACITY_COMMAND_LENGTH_UFI     12
#define UX_SLAVE_CLASS_STORAGE_READ_CAPACITY_COMMAND_LENGTH_SBC     10


/* Define Storage Class read capacity response constants.  */

#define UX_SLAVE_CLASS_STORAGE_READ_CAPACITY_RESPONSE_LAST_LBA      0
#define UX_SLAVE_CLASS_STORAGE_READ_CAPACITY_RESPONSE_BLOCK_SIZE    4
#define UX_SLAVE_CLASS_STORAGE_READ_CAPACITY_RESPONSE_LENGTH        8

/* Define Storage Class read capacity response constants.  */

#define UX_SLAVE_CLASS_STORAGE_READ_FORMAT_CAPACITY_RESPONSE_SIZE           0
#define UX_SLAVE_CLASS_STORAGE_READ_FORMAT_CAPACITY_RESPONSE_LAST_LBA       4
#define UX_SLAVE_CLASS_STORAGE_READ_FORMAT_CAPACITY_RESPONSE_DESC_CODE      8
#define UX_SLAVE_CLASS_STORAGE_READ_FORMAT_CAPACITY_RESPONSE_BLOCK_SIZE     8
#define UX_SLAVE_CLASS_STORAGE_READ_FORMAT_CAPACITY_RESPONSE_LENGTH         12

/* Define Storage Class test unit read command constants.  */

#define UX_SLAVE_CLASS_STORAGE_TEST_READY_OPERATION                 0
#define UX_SLAVE_CLASS_STORAGE_TEST_READY_LUN                       1
#define UX_SLAVE_CLASS_STORAGE_TEST_READY_COMMAND_LENGTH_UFI        12
#define UX_SLAVE_CLASS_STORAGE_TEST_READY_COMMAND_LENGTH_SBC        6


/* Define Storage Class SCSI read command constants.  */

#define UX_SLAVE_CLASS_STORAGE_READ_OPERATION                       0
#define UX_SLAVE_CLASS_STORAGE_READ_LUN                             1
#define UX_SLAVE_CLASS_STORAGE_READ_LBA                             2
#define UX_SLAVE_CLASS_STORAGE_READ_TRANSFER_LENGTH_32              6
#define UX_SLAVE_CLASS_STORAGE_READ_TRANSFER_LENGTH_16              7
#define UX_SLAVE_CLASS_STORAGE_READ_COMMAND_LENGTH_UFI              12
#define UX_SLAVE_CLASS_STORAGE_READ_COMMAND_LENGTH_SBC              10


/* Define Storage Class SCSI write command constants.  */

#define UX_SLAVE_CLASS_STORAGE_WRITE_OPERATION                      0
#define UX_SLAVE_CLASS_STORAGE_WRITE_LUN                            1
#define UX_SLAVE_CLASS_STORAGE_WRITE_LBA                            2
#define UX_SLAVE_CLASS_STORAGE_WRITE_TRANSFER_LENGTH_32             6
#define UX_SLAVE_CLASS_STORAGE_WRITE_TRANSFER_LENGTH_16             7
#define UX_SLAVE_CLASS_STORAGE_WRITE_COMMAND_LENGTH_UFI             12
#define UX_SLAVE_CLASS_STORAGE_WRITE_COMMAND_LENGTH_SBC             10


/* Define Storage Class SCSI sense key definition constants.  */

#define UX_SLAVE_CLASS_STORAGE_SENSE_KEY_NO_SENSE                   0x0
#define UX_SLAVE_CLASS_STORAGE_SENSE_KEY_RECOVERED_ERROR            0x1
#define UX_SLAVE_CLASS_STORAGE_SENSE_KEY_NOT_READY                  0x2
#define UX_SLAVE_CLASS_STORAGE_SENSE_KEY_MEDIUM_ERROR               0x3
#define UX_SLAVE_CLASS_STORAGE_SENSE_KEY_HARDWARE_ERROR             0x4
#define UX_SLAVE_CLASS_STORAGE_SENSE_KEY_ILLEGAL_REQUEST            0x5
#define UX_SLAVE_CLASS_STORAGE_SENSE_KEY_UNIT_ATTENTION             0x6
#define UX_SLAVE_CLASS_STORAGE_SENSE_KEY_DATA_PROTECT               0x7
#define UX_SLAVE_CLASS_STORAGE_SENSE_KEY_BLANK_CHECK                0x8
#define UX_SLAVE_CLASS_STORAGE_SENSE_KEY_ABORTED_COMMAND            0x0b
#define UX_SLAVE_CLASS_STORAGE_SENSE_KEY_VOLUME_OVERFLOW            0x0d
#define UX_SLAVE_CLASS_STORAGE_SENSE_KEY_MISCOMPARE                 0x0e


/* Define Storage Class SCSI sense key definition constants.  */

#define UX_SLAVE_CLASS_STORAGE_REQUEST_CODE_MEDIA_PROTECTED         0x27

/* Define Storage Class SCSI GET CONFIGURATION command constants.  */

#define UX_SLAVE_CLASS_STORAGE_GET_CONFIGURATION_OPERATION              0
#define UX_SLAVE_CLASS_STORAGE_GET_CONFIGURATION_RT                     1
#define UX_SLAVE_CLASS_STORAGE_GET_CONFIGURATION_STARTING_FEATURE       2
#define UX_SLAVE_CLASS_STORAGE_GET_CONFIGURATION_ALLOCATION_LENGTH      7
#define UX_SLAVE_CLASS_STORAGE_GET_CONFIGURATION_COMMAND_LENGTH_SBC     9

/* Define Storage Class SCSI ASC return codes.  */
#define UX_SLAVE_CLASS_STORAGE_ASC_KEY_INVALID_COMMAND              0x20

/* Define Storage Class CSW status.  */

#define UX_SLAVE_CLASS_STORAGE_CSW_PASSED                           0
#define UX_SLAVE_CLASS_STORAGE_CSW_FAILED                           1
#define UX_SLAVE_CLASS_STORAGE_CSW_PHASE_ERROR                      2

/* Define generic SCSI values.  */

#define UX_SLAVE_CLASS_STORAGE_REQUEST_SENSE_RESPONSE_ERROR_CODE_VALUE  0x70
#define UX_SLAVE_CLASS_STORAGE_INQUIRY_PAGE_CODE_STANDARD               0x00
#define UX_SLAVE_CLASS_STORAGE_INQUIRY_PAGE_CODE_SERIAL                 0x80
#define UX_SLAVE_CLASS_STORAGE_INQUIRY_PERIPHERAL_TYPE                  0x00
#define UX_SLAVE_CLASS_STORAGE_RESET                                    0xff
#define UX_SLAVE_CLASS_STORAGE_GET_MAX_LUN                              0xfe
#define UX_SLAVE_CLASS_STORAGE_MAX_LUN                                  0
#define UX_SLAVE_CLASS_STORAGE_RESPONSE_LENGTH                          64

/* Define Storage Class SCSI read disk information command constants.  */

#define UX_SLAVE_CLASS_STORAGE_READ_DISK_INFORMATION_OPERATION          0
#define UX_SLAVE_CLASS_STORAGE_READ_DISK_INFORMATION_STATUS             2
#define UX_SLAVE_CLASS_STORAGE_READ_DISK_INFORMATION_ALLOCATION_LENGTH  7
#define UX_SLAVE_CLASS_STORAGE_READ_DISK_INFORMATION_LENGTH             10

/* Define Storage Class Feature Descriptor generic format.  */

#define USBX_DEVICE_CLASS_STORAGE_FEATURE_DESCRIPTOR_FEATURE_CODE       0
#define USBX_DEVICE_CLASS_STORAGE_FEATURE_DESCRIPTOR_FEATURE_PARAMETER  2
#define USBX_DEVICE_CLASS_STORAGE_FEATURE_DESCRIPTOR_FEATURE_ADD_LENGTH 3
#define USBX_DEVICE_CLASS_STORAGE_FEATURE_DESCRIPTOR_FEATURE_LENGTH     4


/* Define Storage Class SCSI REPORT_KEY command constants.  */

#define UX_SLAVE_CLASS_STORAGE_REPORT_KEY_OPERATION                    0
#define UX_SLAVE_CLASS_STORAGE_REPORT_KEY_ALLOCATION_LENGTH            8
#define UX_SLAVE_CLASS_STORAGE_REPORT_KEY_FORMAT                       10

#define UX_SLAVE_CLASS_STORAGE_REPORT_KEY_ANSWER_LENGTH                8
#define UX_SLAVE_CLASS_STORAGE_REPORT_KEY_ANSWER_PAYLOAD               6
#define UX_SLAVE_CLASS_STORAGE_REPORT_KEY_ANSWER_RESET_FIELD           4
#define UX_SLAVE_CLASS_STORAGE_REPORT_KEY_ANSWER_REGION_MASK           5
#define UX_SLAVE_CLASS_STORAGE_REPORT_KEY_ANSWER_RPC_SCHEME            6


#define UX_SLAVE_CLASS_STORAGE_REPORT_KEY_FORMAT_AGID                  0
#define UX_SLAVE_CLASS_STORAGE_REPORT_KEY_FORMAT_CHALLENGE             1
#define UX_SLAVE_CLASS_STORAGE_REPORT_KEY_FORMAT_KEY2                  2
#define UX_SLAVE_CLASS_STORAGE_REPORT_KEY_FORMAT_TITLE                 4
#define UX_SLAVE_CLASS_STORAGE_REPORT_KEY_FORMAT_RPC                   8

/* Define Storage Class SCSI get event status notification command constants.  */

#define UX_SLAVE_CLASS_STORAGE_EVENT_NOTIFICATION_OPCODE                0
#define UX_SLAVE_CLASS_STORAGE_EVENT_NOTIFICATION_IMMEDIATE             1
#define UX_SLAVE_CLASS_STORAGE_EVENT_NOTIFICATION_CLASS_REQUEST         4
#define UX_SLAVE_CLASS_STORAGE_EVENT_NOTIFICATION_ALLOCATION_LENGTH     7
#define UX_SLAVE_CLASS_STORAGE_EVENT_NOTIFICATION_LENGTH                10

/* Define Storage Class SCSI read toc command constants.  */

#define UX_SLAVE_CLASS_STORAGE_READ_TOC_OPCODE                          0
#define UX_SLAVE_CLASS_STORAGE_READ_TOC_FORMAT                          2
#define UX_SLAVE_CLASS_STORAGE_READ_TOC_TRACK_NUMBER                    6
#define UX_SLAVE_CLASS_STORAGE_READ_TOC_ALLOCATION_LENGTH               7

/* Define Storage Class SCSI read DVD structure command constants.  */

#define UX_SLAVE_CLASS_STORAGE_READ_DVD_STRUCTURE_OPCODE                0
#define UX_SLAVE_CLASS_STORAGE_READ_DVD_STRUCTURE_ADDRESS               2
#define UX_SLAVE_CLASS_STORAGE_READ_DVD_STRUCTURE_FORMAT                7
#define UX_SLAVE_CLASS_STORAGE_READ_DVD_STRUCTURE_ALLOCATION_LENGTH     8

#define UX_SLAVE_CLASS_STORAGE_READ_DVD_STRUCTURE_RESP_LENGTH           0
#define UX_SLAVE_CLASS_STORAGE_READ_DVD_STRUCTURE_BOOK_TYPE             4
#define UX_SLAVE_CLASS_STORAGE_READ_DVD_STRUCTURE_DS_MR                 5


/* Define Storage Class SCSI get performance command constants.  */

#define UX_SLAVE_CLASS_STORAGE_GET_PERFORMANCE_PAGE                     1
#define UX_SLAVE_CLASS_STORAGE_GET_PERFORMANCE_PAGE_14                  0x14
#define UX_SLAVE_CLASS_STORAGE_GET_PERFORMANCE_PAGE_0                   0x00
#define UX_SLAVE_CLASS_STORAGE_GET_PERFORMANCE_PAYLOAD_LENGTH           4
#define UX_SLAVE_CLASS_STORAGE_GET_PERFORMANCE_RESPONSE_LENGTH          8
#define UX_SLAVE_CLASS_STORAGE_GET_PERFORMANCE_PAYLOAD                  0x20000000

/* Define buffer length for IN/OUT pipes.  This should match the size of the endpoint maximum buffer size. */

#define UX_SLAVE_CLASS_STORAGE_BUFFER_SIZE                              UX_SLAVE_REQUEST_DATA_MAX_LENGTH


/* Define MMC2 CD-ROM / DVD-ROM bit fields */

#define UX_SLAVE_CLASS_STORAGE_MMC2_DISK_STATUS_EMPTY                   0
#define UX_SLAVE_CLASS_STORAGE_MMC2_DISK_STATUS_INCOMPLETE              1
#define UX_SLAVE_CLASS_STORAGE_MMC2_DISK_STATUS_COMPLETE                2
#define UX_SLAVE_CLASS_STORAGE_MMC2_DISK_STATUS_OTHERS                  3

#define UX_SLAVE_CLASS_STORAGE_MMC2_LAT_SESSION_EMPTY                   0
#define UX_SLAVE_CLASS_STORAGE_MMC2_LAT_SESSION_INCOMPLETE              1
#define UX_SLAVE_CLASS_STORAGE_MMC2_LAT_SESSION_COMPLETE                3


/* Define Storage Class SCSI synchronize cache constants.  */

#define UX_SLAVE_CLASS_STORAGE_SYNCHRONIZE_CACHE_FLAGS                  1
#define UX_SLAVE_CLASS_STORAGE_SYNCHRONIZE_CACHE_LBA                    2
#define UX_SLAVE_CLASS_STORAGE_SYNCHRONIZE_CACHE_NUMBER_OF_BLOCKS       7

#define UX_SLAVE_CLASS_STORAGE_SYNCHRONIZE_CACHE_FLAGS_IMMED            0x02


/* Define MODE SENSE Page Codes.  */
#define UX_SLAVE_CLASS_STORAGE_MMC2_PAGE_CODE_CDROM                     0x2a

#define UX_SLAVE_CLASS_STORAGE_PAGE_CODE_CACHE                          0x08
#define UX_SLAVE_CLASS_STORAGE_PAGE_CODE_IEC                            0x1C
#define UX_SLAVE_CLASS_STORAGE_PAGE_CODE_ALL                            0x3F


/* Define Slave Storage Class LUN structure.  */

typedef struct UX_SLAVE_CLASS_STORAGE_LUN_STRUCT
{
    ULONG           ux_slave_class_storage_media_last_lba;
    ULONG           ux_slave_class_storage_media_block_length;
    ULONG           ux_slave_class_storage_media_type;
    ULONG           ux_slave_class_storage_media_removable_flag;
    ULONG           ux_slave_class_storage_media_read_only_flag;
    ULONG           ux_slave_class_storage_media_id;
    ULONG           ux_slave_class_storage_scsi_tag;
    UCHAR           ux_slave_class_storage_request_sense_key;
    UCHAR           ux_slave_class_storage_request_code;
    UCHAR           ux_slave_class_storage_request_code_qualifier;
    ULONG           ux_slave_class_storage_disk_status;
    ULONG           ux_slave_class_storage_last_session_state;
    UINT            (*ux_slave_class_storage_media_read)(VOID *storage, ULONG lun, UCHAR *data_pointer, ULONG number_blocks, ULONG lba, ULONG *media_status);
    UINT            (*ux_slave_class_storage_media_write)(VOID *storage, ULONG lun, UCHAR *data_pointer, ULONG number_blocks, ULONG lba, ULONG *media_status);
    UINT            (*ux_slave_class_storage_media_flush)(VOID *storage, ULONG lun, ULONG number_blocks, ULONG lba, ULONG *media_status);
    UINT            (*ux_slave_class_storage_media_status)(VOID *storage, ULONG lun, ULONG media_id, ULONG *media_status);
    UINT            (*ux_slave_class_storage_media_notification)(VOID *storage, ULONG lun, ULONG media_id, ULONG notification_class, UCHAR **media_notification, ULONG *media_notification_length);
} UX_SLAVE_CLASS_STORAGE_LUN;

/* Define Slave Storage Class structure.  */

typedef struct UX_SLAVE_CLASS_STORAGE_STRUCT
{
    UX_SLAVE_INTERFACE          *ux_slave_class_storage_interface;
    ULONG                       ux_slave_class_storage_number_lun;
    UX_SLAVE_CLASS_STORAGE_LUN  ux_slave_class_storage_lun[UX_MAX_SLAVE_LUN];
    ULONG                       ux_slave_class_storage_phase_error;
    VOID                        (*ux_slave_class_storage_instance_activate)(VOID *);
    VOID                        (*ux_slave_class_storage_instance_deactivate)(VOID *);
    UCHAR                       *ux_slave_class_storage_vendor_id;
    UCHAR                       *ux_slave_class_storage_product_id;
    UCHAR                       *ux_slave_class_storage_product_rev;
    UCHAR                       *ux_slave_class_storage_product_serial;

} UX_SLAVE_CLASS_STORAGE;

/* Define Slave Storage Class Calling Parameter structure */

typedef struct UX_SLAVE_CLASS_STORAGE_PARAMETER_STRUCT
{
    VOID                        (*ux_slave_class_storage_instance_activate)(VOID *);
    VOID                        (*ux_slave_class_storage_instance_deactivate)(VOID *);
    ULONG                       ux_slave_class_storage_parameter_number_lun;
    UX_SLAVE_CLASS_STORAGE_LUN  ux_slave_class_storage_parameter_lun[UX_MAX_SLAVE_LUN];
    UCHAR                       *ux_slave_class_storage_parameter_vendor_id;
    UCHAR                       *ux_slave_class_storage_parameter_product_id;
    UCHAR                       *ux_slave_class_storage_parameter_product_rev;
    UCHAR                       *ux_slave_class_storage_parameter_product_serial;

} UX_SLAVE_CLASS_STORAGE_PARAMETER;

/* Define Device Storage Class prototypes.  */

UINT    _ux_device_class_storage_initialize(UX_SLAVE_CLASS_COMMAND *command);
UINT    _ux_device_class_storage_uninitialize(UX_SLAVE_CLASS_COMMAND *command);
UINT    _ux_device_class_storage_activate(UX_SLAVE_CLASS_COMMAND *command);
UINT    _ux_device_class_storage_control_request(UX_SLAVE_CLASS_COMMAND *command);
UINT    _ux_device_class_storage_csw_send(UX_SLAVE_CLASS_STORAGE *storage, ULONG lun, UX_SLAVE_ENDPOINT *endpoint_in, UCHAR csw_status);
UINT    _ux_device_class_storage_deactivate(UX_SLAVE_CLASS_COMMAND *command);
UINT    _ux_device_class_storage_entry(UX_SLAVE_CLASS_COMMAND *command);
UINT    _ux_device_class_storage_format(UX_SLAVE_CLASS_STORAGE *storage, ULONG lun, UX_SLAVE_ENDPOINT *endpoint_in,
                    UX_SLAVE_ENDPOINT *endpoint_out, UCHAR *cbwcb);
UINT    _ux_device_class_storage_inquiry(UX_SLAVE_CLASS_STORAGE *storage, ULONG lun, UX_SLAVE_ENDPOINT *endpoint_in,
                    UX_SLAVE_ENDPOINT *endpoint_out, UCHAR *cbwcb);
UINT    _ux_device_class_storage_mode_select(UX_SLAVE_CLASS_STORAGE *storage, ULONG lun, UX_SLAVE_ENDPOINT *endpoint_in,
                    UX_SLAVE_ENDPOINT *endpoint_out, UCHAR *cbwcb);
UINT    _ux_device_class_storage_mode_sense(UX_SLAVE_CLASS_STORAGE *storage, ULONG lun, UX_SLAVE_ENDPOINT *endpoint_in,
                    UX_SLAVE_ENDPOINT *endpoint_out, UCHAR *cbwcb);
UINT    _ux_device_class_storage_prevent_allow_media_removal(UX_SLAVE_CLASS_STORAGE *storage, ULONG lun,
                    UX_SLAVE_ENDPOINT *endpoint_in, UX_SLAVE_ENDPOINT *endpoint_out, UCHAR * cbwcb);
UINT    _ux_device_class_storage_read(UX_SLAVE_CLASS_STORAGE *storage, ULONG lun, UX_SLAVE_ENDPOINT *endpoint_in,
                    UX_SLAVE_ENDPOINT *endpoint_out, UCHAR *cbwcb, UCHAR scsi_command);
UINT    _ux_device_class_storage_read_capacity(UX_SLAVE_CLASS_STORAGE *storage, ULONG lun, UX_SLAVE_ENDPOINT *endpoint_in,
                    UX_SLAVE_ENDPOINT *endpoint_out, UCHAR *cbwcb);
UINT    _ux_device_class_storage_read_format_capacity(UX_SLAVE_CLASS_STORAGE *storage, ULONG lun, UX_SLAVE_ENDPOINT *endpoint_in,
                    UX_SLAVE_ENDPOINT *endpoint_out, UCHAR *cbwcb);
UINT    _ux_device_class_storage_read_toc(UX_SLAVE_CLASS_STORAGE *storage, ULONG lun, UX_SLAVE_ENDPOINT *endpoint_in,
                                            UX_SLAVE_ENDPOINT *endpoint_out, UCHAR * cbwcb);
UINT    _ux_device_class_storage_request_sense(UX_SLAVE_CLASS_STORAGE *storage, ULONG lun, UX_SLAVE_ENDPOINT *endpoint_in,
                    UX_SLAVE_ENDPOINT *endpoint_out, UCHAR *cbwcb);
UINT    _ux_device_class_storage_start_stop(UX_SLAVE_CLASS_STORAGE *storage, ULONG lun, UX_SLAVE_ENDPOINT *endpoint_in,
                    UX_SLAVE_ENDPOINT *endpoint_out, UCHAR *cbwcb);
UINT    _ux_device_class_storage_test_ready(UX_SLAVE_CLASS_STORAGE *storage, ULONG lun, UX_SLAVE_ENDPOINT *endpoint_in,
                    UX_SLAVE_ENDPOINT *endpoint_out, UCHAR *cbwcb);
VOID    _ux_device_class_storage_thread(ULONG storage_instance);
UINT    _ux_device_class_storage_verify(UX_SLAVE_CLASS_STORAGE *storage, ULONG lun, UX_SLAVE_ENDPOINT *endpoint_in,
                    UX_SLAVE_ENDPOINT *endpoint_out, UCHAR *cbwcb);
UINT    _ux_device_class_storage_write(UX_SLAVE_CLASS_STORAGE *storage, ULONG lun, UX_SLAVE_ENDPOINT *endpoint_in,
                    UX_SLAVE_ENDPOINT *endpoint_out, UCHAR *cbwcb, UCHAR scsi_command);
UINT    _ux_device_class_storage_synchronize_cache(UX_SLAVE_CLASS_STORAGE *storage, ULONG lun, UX_SLAVE_ENDPOINT *endpoint_in,
                    UX_SLAVE_ENDPOINT *endpoint_out, UCHAR *cbwcb, UCHAR scsi_command);
UINT    _ux_device_class_storage_read_disk_information(UX_SLAVE_CLASS_STORAGE *storage, ULONG lun,
                                            UX_SLAVE_ENDPOINT *endpoint_in,
                                            UX_SLAVE_ENDPOINT *endpoint_out, UCHAR *cbwcb);

UINT    _ux_device_class_storage_get_configuration(UX_SLAVE_CLASS_STORAGE *storage, ULONG lun,
                                            UX_SLAVE_ENDPOINT *endpoint_in,
                                            UX_SLAVE_ENDPOINT *endpoint_out, UCHAR *cbwcb);
UINT    _ux_device_class_storage_get_status_notification(UX_SLAVE_CLASS_STORAGE *storage, ULONG lun,
                                            UX_SLAVE_ENDPOINT *endpoint_in,
                                            UX_SLAVE_ENDPOINT *endpoint_out, UCHAR *cbwcb);
UINT    _ux_device_class_storage_report_key(UX_SLAVE_CLASS_STORAGE *storage,
                                            ULONG               lun,
                                            UX_SLAVE_ENDPOINT   *endpoint_in,
                                            UX_SLAVE_ENDPOINT   *endpoint_out,
                                            UCHAR               *cbwcb);

UINT    _ux_device_class_storage_get_performance(UX_SLAVE_CLASS_STORAGE *storage,
                                            ULONG               lun,
                                            UX_SLAVE_ENDPOINT   *endpoint_in,
                                            UX_SLAVE_ENDPOINT   *endpoint_out,
                                            UCHAR               *cbwcb);
UINT    _ux_device_class_storage_read_dvd_structure(UX_SLAVE_CLASS_STORAGE *storage, ULONG lun,
                                            UX_SLAVE_ENDPOINT *endpoint_in,
                                            UX_SLAVE_ENDPOINT *endpoint_out, UCHAR *cbwcb);

/* Define Device Storage Class API prototypes.  */

#define ux_device_class_storage_entry        _ux_device_class_storage_entry

#endif
