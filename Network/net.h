/*
 * net.h
 *
 *  Created on: Feb 9, 2020
 *      Author: zeus
 */

#ifndef NET_H_
#define NET_H_
#include <stdbool.h>
#include <stdint.h>
#include <log/log.h>
#include <netinet/in.h>
#include <sys/socket.h> /*Lib Socket*/
#include <sys/types.h>

/* Listen ipv4
 * addr -> Ip Address For Listen
 * Port -> Port Number
 * sockfd -> Store Socket fd in this Pointer
 */
bool net_ListenIp4(in_addr_t addr, uint16_t Port,int *sockfd);

/* connect to host
 * host -> adress of host
 * Port -> Port Number
 * sockfd -> Store Socket fd in this Pointer
 */
bool net_connect(int *sockfd,const char *hostname, uint16_t port);

/*
 * net_GetHost is smart function for extract host name from http/https packet
 */
bool net_GetHost(uint8_t *buf,uint32_t len,char *HostName,uint16_t MaxHostName);

/*
 * Get String and check it's IP or Not
 */
bool isTrueIpAddress(char *ipAddress);


bool net_GetHttpHost(uint8_t *buf,uint32_t len,char *HostName,uint16_t MaxHostName);
bool net_GetHttpsHost(uint8_t *buf,uint32_t len,char *HostName,uint16_t MaxHostName);

#endif /* NET_H_ */
