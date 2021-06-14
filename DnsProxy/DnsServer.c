/*
 * DnsServer.c
 *
 *  Created on: Jun 2, 2021
 *      Author: zeus
 */
#include "../DnsProxy/DnsServer.h"

#include <log/log.h>
#include <unistd.h>  	/*Header file for sleep(). man 3 sleep for details.*/
#include <pthread.h>	/* http://www.csc.villanova.edu/~mdamian/threads/posixthreads.html */
#include <stdlib.h>
#include "../DnsProxy/dnsproxy.h"

void *dnsserver_HandleIncomingConnection(void *vargp);

void dnsserver_init(dnshost_t *config)
{
	/*make thread for dns server*/
	pthread_t thread_id;
	pthread_create(&thread_id, NULL, dnsserver_HandleIncomingConnection, (void*)config);
}

void *dnsserver_HandleIncomingConnection(void *vargp)
{
	dnshost_t *conf = (dnshost_t*)vargp;

	dnsserver_t *dns = localdns_init_config(conf);
	if(!dns)
	{
		log_error("dns server config error...");
		pthread_exit(0);
	}

	if(!localdns_init_sockets(dns))
	{
		localdns_free(dns);
		log_error("dns server socket error.");
		pthread_exit(0);
	}

	log_info("dns server start on %s:%d",conf->host,conf->port);

	while(1)
	{
		if(!localdns_pull(dns))
			break;
	}

	log_error("dns server crashed.");
	localdns_free(dns);
	pthread_exit(0);
}

