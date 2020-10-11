#include <Ethernet.h>
#include <USB.h>

#define     MAX_NUM_OF_TRY              (1000000)
#define     UX_STORAGE_BUFFER_SIZE      (64*1024)

#define     EVENT_USB_PLUG_IN           (1UL << 0)
#define     EVENT_USB_PLUG_OUT          (1UL << 1)

UINT EthernetUDPInit(NX_IP *ip, NX_UDP_SOCKET *udp_sck, UINT port, VOID(*udp_receive_notify)(NX_UDP_SOCKET *socket_ptr));

void EthernetPrimarySend(char *data, unsigned int length, NX_UDP_SOCKET *udp_sck, ULONG ip_address, UINT port,
        TX_EVENT_FLAGS_GROUP *udp_echo_received);

UINT EthernetSecondarySend(char *data, unsigned int length, NX_UDP_SOCKET *udp_sck, ULONG ip_address, UINT port,
        TX_EVENT_FLAGS_GROUP *udp_echo_received);

UINT USBDeviceRead(UX_SLAVE_CLASS_CDC_ACM *g_cdc, char *rxBuff, UINT length, UINT *actual_length);

UINT usb_host_plug_event_notification(ULONG usb_event, UX_HOST_CLASS *host_class, VOID *instance);
