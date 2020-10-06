#include "./synergy_gen/Ethernet.h"

void EthernetMasterSend(char *data, unsigned int length, NX_UDP_SOCKET *udp_sck, ULONG ip_address, UINT port,
        TX_EVENT_FLAGS_GROUP *udp_echo_received);
