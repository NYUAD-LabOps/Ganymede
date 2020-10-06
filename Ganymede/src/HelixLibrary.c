#include "HelixLibrary.h"

void EthernetMasterSend(char *data, unsigned int length, NX_UDP_SOCKET *udp_sck, ULONG ip_address, UINT port,
        TX_EVENT_FLAGS_GROUP *udp_echo_received)
{
    UINT status;
    ULONG tmp = 0;
    char echoACK = 0;
    ioport_level_t level;
    NX_PACKET *my_packet;
    do
    {
        status = nx_packet_allocate (&g_packet_pool0, &my_packet, NX_UDP_PACKET, NX_WAIT_FOREVER);
        /* Check for error.  */
        nx_packet_data_append (my_packet, data, length, &g_packet_pool0, NX_WAIT_FOREVER);

//            if (DEBUG)
//            {
//                printf ("\nSending:%s...", machineGlobalsBlock->UDPBuffer);
//            }

        status = nx_udp_socket_send(udp_sck, my_packet, ip_address, ip_address);

        if (NX_SUCCESS == status)
        {
//                if (DEBUG)
//                {
//                    printf ("\nSend success.");
//                }
        }
        else
        {
//                if (DEBUG)
//                {
//                    printf ("\nSend fail.");
//                }
            nx_packet_release(my_packet);
        }

        //        machineGlobalsBlock->echoWaitStart = 1;
        status = tx_event_flags_get (udp_echo_received, 1, TX_AND_CLEAR, &tmp, 300);
    }
    while (tmp == 0);
//        if (DEBUG)
//        {
//            printf ("\nSend complete.");
//        }
//        memset (machineGlobalsBlock->UDPBuffer, 0, UDPMSGLENGTH);
}
