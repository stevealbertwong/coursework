unsigned short checksum(unsigned short *buf, int nwords)
{       
        unsigned long sum;
        for(sum=0; nwords>0; nwords--)
                sum += *buf++;
        sum = (sum >> 16) + (sum &0xffff);
        sum += (sum >> 16);
        return (unsigned short)(~sum);
}
struct ipheader {
 unsigned char      iph_ihl:5, iph_ver:4;
 unsigned char      iph_tos;
 unsigned short int iph_len;
 unsigned short int iph_ident;
 unsigned char      iph_flag;
 unsigned short int iph_offset;
 unsigned char      iph_ttl;
 unsigned char      iph_protocol;
 unsigned short int iph_chksum;
 unsigned int       iph_sourceip;
 unsigned int       iph_destip;
};
struct udpheader {
 unsigned short int udph_srcport;
 unsigned short int udph_destport;
 unsigned short int udph_len;
 unsigned short int udph_chksum;
};
char buffer[PCKT_LEN];
struct ipheader *ip = (struct ipheader *) buffer;
struct udpheader *udp = (struct udpheader *) (buffer + 
	sizeof(struct ipheader));
memset(buffer, 0, PCKT_LEN);
// Writing into buffer => No data/payload just datagram
ip->iph_ihl = 5;
ip->iph_ver = 4;
ip->iph_tos = 16; // Low delay
ip->iph_len = sizeof(struct ipheader) + sizeof(struct udpheader);
ip->iph_ident = htons(54321);
ip->iph_ttl = 64; // hops
ip->iph_protocol = 17; // UDP
ip->iph_sourceip = inet_addr(argv[1]);
ip->iph_destip = inet_addr(argv[3]);
udp->udph_srcport = htons(atoi(argv[2]));
udp->udph_destport = htons(atoi(argv[4]));
udp->udph_len = htons(sizeof(struct udpheader));
ip->iph_chksum = checksum((unsigned short *)buffer, 
	sizeof(struct ipheader) + sizeof(struct udpheader));
sd = socket(PF_INET, SOCK_RAW, IPPROTO_UDP);
sendto(sd, buffer, ip->iph_len, 0, (struct sockaddr *)&sin, sizeof(sin));