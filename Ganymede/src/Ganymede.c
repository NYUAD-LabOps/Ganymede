#include <Ganymede.h>

///The primary controller initiates all communications. Each packet must be echoed by the secondary. This is performed to ensure 100% packet delivery.
/// It guarantees that each packet is delivered at least once. This interaction is performed via the UDP protocol. This system was chosen, as opposed to
/// TCP/IP, which guarantees packet delivery in both directions, for a variety of reasons.
///
/// First, UDP has less latency than TCP/IP, having less overhead. Two, a variety of reliability issues were encountered when attempting to set up
/// TCP/IP communications between the primary and secondary. Three, it is critical that every machine instruction from the primary is sent at least once.
/// Failure to do this could result in hardware damage. An example being failing to turn on a cutting tool. While it is true that echoing every packet in its entirety
/// results in doubling the volume of communications, this was selected over the use of a CRC check, as in TCP/IP, because it was predicted that the latency involved
/// in calculating and verifying a CRC value would be greater than the latency required to echo these small packets. At this point, packets are a mere 10 bytes long,
/// and the round-trip-time without echo has been measured at 70us.
///
/// All things considered, it is possible that TCP/IP would be faster and more reliable, in theory, than this UDP implementation. However, the final reason for choosing
/// this was that difficulties were encountered while attempting to set up TCP/IP. Despite the fact that TCP/IP is supposed to guarantee packet delivery, the Renesas API
/// would often time out and fail to deliver packets. It's possible there may have been some other issue responsible for this. It is recommended that TCP/IP be investigated
/// further in the future.
void EthernetPrimarySend(char *data, unsigned int length, NX_UDP_SOCKET *udp_sck, ULONG ip_address, UINT port,
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