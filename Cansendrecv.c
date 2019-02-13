#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <net/if.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/ioctl.h>
#include <sys/epoll.h>
#include <linux/can.h>
#include <linux/can/raw.h>

#define True 1
//#define MAX_EVENTS 5

static int epfd;
static struct epoll_event events;

int can_init()
{
    printf("CAN has been Initialized\n");
    
        int usleep(useconds_t usec);
        int s;
	    int s2;
        int nbytes;
        struct sockaddr_can addr;
        struct can_frame frame;
        struct ifreq ifr;
        struct can_filter filterID[4];
        struct can_filter
        {
        canid_t can_id;
        canid_t can_mask;
        };
    

    const char *ifname = "can0";
    
    if ((s = socket(PF_CAN, SOCK_RAW, CAN_RAW)) < 0)
    {
        perror("Error while opening socket");
        return -1;
    }
    
    strcpy(ifr.ifr_name, ifname);
    ioctl(s, SIOCGIFINDEX, &ifr);
    
    addr.can_family = AF_CAN;
    addr.can_ifindex = ifr.ifr_ifindex;
    //  setsockopt(s, SOL_CAN_RAW, CAN_RAW_FILTER, &rfilter, sizeof(rfilter));
    printf("%s at index %d\n", ifname, ifr.ifr_ifindex);
    
    if (bind(s, (struct sockaddr *)&addr, sizeof(addr)) < 0)
    {
        perror("Error in socket bind");
        return -2;
    }
    
    frame.can_dlc = 8;
    
    // The fileters have been addeed, reciving data will be only from designated can ID numbers
    filterID[0].can_id = 0x202;
    filterID[0].can_mask = CAN_EFF_MASK;
    filterID[1].can_id = 0x182;
    filterID[1].can_mask = CAN_EFF_MASK;
    filterID[2].can_id = 0x105;
    filterID[2].can_mask = CAN_EFF_MASK;
    filterID[3].can_id = 0x10B;
    filterID[3].can_mask = CAN_EFF_MASK;
    //Filters have been applied on the socket
    setsockopt(s, SOL_CAN_RAW, CAN_RAW_FILTER, &filterID, sizeof(filterID));
   // printf("%s\n",s);

return s;
}


void can_recv(int s, int id, unsigned char * value){
//     printf("%s","Inside can recieve ");
   	int nbytes;
	struct can_frame frame;
	int nfd;
    nbytes = read(s, &frame, sizeof(struct can_frame));
#if defined(TEST)
   // printf("Reciving Data: ID:%x -  %x %x %x %x %x %x %x %x \n",
   // frame.can_id, frame.data[0], frame.data[1], frame.data[2],
   // frame.data[3], frame.data[4], frame.data[5], frame.data[6], frame.data[7]);
#endif
}


void can_send(int s, int id,unsigned char* value){
  	int nbytes;
	struct can_frame frame;

	frame.can_id=id;

	frame.can_id=id;
	frame.can_dlc=8;
	frame.data[0]=value[0];
	frame.data[1]=value[1];
	frame.data[2]=value[2];
	frame.data[3]=value[3];
	frame.data[4]=value[4];
	frame.data[5]=value[5];
	frame.data[6]=value[6];
	frame.data[7]=value[7];

	write(s,&frame,sizeof(struct can_frame));

}





