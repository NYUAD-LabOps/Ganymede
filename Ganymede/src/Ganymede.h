#include <Ethernet.h>
#include <USB.h>

UINT EthernetUDPInit(NX_IP *ip, NX_UDP_SOCKET *udp_sck, UINT port, VOID(*udp_receive_notify)(NX_UDP_SOCKET *socket_ptr));

void EthernetPrimarySend(char *data, unsigned int length, NX_UDP_SOCKET *udp_sck, ULONG ip_address, UINT port,
        TX_EVENT_FLAGS_GROUP *udp_echo_received);

UINT EthernetSecondarySend(char *data, unsigned int length, NX_UDP_SOCKET *udp_sck, ULONG ip_address, UINT port,
        TX_EVENT_FLAGS_GROUP *udp_echo_received);

UINT USBDeviceRead(UX_SLAVE_CLASS_CDC_ACM *g_cdc, char *rxBuff, UINT length, UINT *actual_length);
