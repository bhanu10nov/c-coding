/*
 * @file my_nl_route_modify.c
 *
 * @brief The file implements route modification.
 *
 * @author Bhanu Jha (bhanujha@gmail.com)
 */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <netlink/netlink.h>
#include <netlink/addr.h>
#include <netlink/cache.h>
#include <netlink/route/link.h>
#include <netlink/route/addr.h>
#include <netlink/route/route.h>
#include <arpa/inet.h>
#include <sys/socket.h>

typedef enum bRouteOperationCode_e {
	ROUTE_ADD =    0,  /**< Route Add    */
	ROUTE_DELETE = 1,  /**< Route Delete */
	LAST               /**< LAST */
} bRouteOperationCode;

typedef enum bRouteCallbackRet_e {
	SUCCESS =    0,  /**< SUCCESS    */
	FAILURE =    1   /**< FAILURE */
} bRouteCallbackRet;

typedef struct bRouteCallbackData_s {
	struct nl_sock *sock;
	bRouteCallbackRet ret;
} bRouteCallbackData;

void usage()
{
	printf("my-nl-route-modify.out <add(0)/delete(1)> <dst> <gw> <dev> <tableno>\n");
	printf("Ex : ./my-nl-route-modify.out 0 192.168.0.0 192.168.0.1 ens33 7\n");
}

static void delete_cb(struct nl_object *obj, void *arg)
{
	int err = 0;
	struct rtnl_route *route = (struct rtnl_route *) obj;
	bRouteCallbackData* callbackData =  (bRouteCallbackData *)arg;
	if (callbackData == NULL) {
		printf("CallbackData is NULL\n");
		return;
	}

	err = rtnl_route_delete(callbackData->sock, route, 0);
	if (err < 0) {
		printf("Error - route delete failed\n");
	} else {
		callbackData->ret = SUCCESS;
	}
}
int route_modify(bRouteOperationCode op, const char *dst, const char *gw,
		const char *dev, const int table)
{
	int err = 0;
	struct rtnl_route *route = NULL;
	struct nl_addr *nl_dst = NULL;
	struct nl_addr *nl_gw = NULL;
	int family = 0;
	int ival = 0;
	struct rtnl_nexthop *nh = NULL;
	static struct nl_sock *sock = NULL;
	static struct nl_cache *link_cache = NULL;
	static struct nl_cache *route_cache = NULL;
	bRouteCallbackData callbackData;

	memset(&callbackData, 0, sizeof(callbackData));

	/* Allocate Socket */
	sock = nl_socket_alloc();
	if (NULL == sock) {
		printf("sock is NULL\n");
		return -1;
	}

	/* Connect Socket */
	err = nl_connect(sock, NETLINK_ROUTE);
	if (0 != err) {
		printf("Error during nl connect\n");
	}

	/* Allocate link cache */
	err = rtnl_link_alloc_cache(sock, AF_UNSPEC, &link_cache);
	if (0 != err) {
		printf("Error during cache allocation\n");
		nl_socket_free(sock);
		return -1;
	}

	nl_cache_mngt_provide(link_cache);

	/* Allocate route cache */
	err = rtnl_route_alloc_cache(sock, AF_UNSPEC, 0, &route_cache);
	if (0 != err) {
		printf("Error during route allocation\n");
		nl_socket_free(sock);
		nl_cache_free(link_cache);
		return -1;
	}

	nl_cache_mngt_provide(route_cache);


	route = rtnl_route_alloc();
	if (!route) {
		printf("Unable to allocate route object\n");
		nl_socket_free(sock);
		nl_cache_free(link_cache);
		nl_cache_free(route_cache);
		return -1;
	}

	family = rtnl_route_get_family(route);

	printf("route family : %d\n", family);

	err = nl_addr_parse(dst, family, &nl_dst);
	if (0 != err) {
		printf("nl_dst - Error nl_addr_parse\n");
		nl_socket_free(sock);
		nl_cache_free(link_cache);
		nl_cache_free(route_cache);
		return -1;
	}

	err = rtnl_route_set_dst(route, nl_dst);
	if (0 != err) {
		printf("Error rtnl_route_set_dst\n");
		nl_socket_free(sock);
		nl_cache_free(link_cache);
		nl_cache_free(route_cache);
		nl_addr_put(nl_dst);
		return -1;
	}

	nl_addr_put(nl_dst);

	if (NULL != gw || NULL != dev) {
		printf("Bhanu Debug : %s : %d\n", __FUNCTION__, __LINE__);
		nh = rtnl_route_nh_alloc();
		if (NULL == nh) {
			printf("Next hop can't be allocated\n");
			printf("Error rtnl_route_set_dst\n");
			nl_socket_free(sock);
			nl_cache_free(link_cache);
			nl_cache_free(route_cache);
			return -1;
		}
		/* Logic for Gateway */
		if (NULL != gw) {
			printf("Bhanu Debug : %s : %d\n", __FUNCTION__, __LINE__);
			err = nl_addr_parse(gw, family, &nl_gw);
			if (0 != err) {
				printf("nl_gw - Error nl_addr_parse : %d\n", err);
				nl_socket_free(sock);
				nl_cache_free(link_cache);
				nl_cache_free(route_cache);
				return -1;
			}
			rtnl_route_nh_set_gateway(nh, nl_gw);
			nl_addr_put(nl_gw);

		}

		/* Logic for Device */
		if (NULL != dev) {
			printf("Bhanu Debug : %s : %d\n", __FUNCTION__, __LINE__);
			ival = rtnl_link_name2i(link_cache, dev);
			if (0 == ival) {
				printf("Match not found\n");
			}
			printf("Ival : %d\n", ival);
			rtnl_route_nh_set_ifindex(nh, ival);

		}

		rtnl_route_add_nexthop(route, nh);
	}

	if (table != 0) {
		rtnl_route_set_table(route, table);
	}

	if (op == ROUTE_ADD) {
		/* Route Add */
		err = rtnl_route_add(sock, route, NLM_F_EXCL);
		if (err < 0) {
			printf("Unable to add route: %d\n", err);
		} else {
			printf("Added \n");
		}
	} else {
		callbackData.sock = sock;
		callbackData.ret = FAILURE;
		/* Route Delete */
		nl_cache_foreach_filter(route_cache, OBJ_CAST(route), delete_cb, &callbackData);
		if (callbackData.ret == SUCCESS) {
			printf("Deleted \n");
		}
	}

	nl_cache_free(link_cache);
	nl_socket_free(sock);
	return 0;
}

/* my-nl-route-modify.out <op> <dst> <gw> <dev> <tableno>*/
int main(int argc, char *argv[])
{
	printf("Argc : %d\n", argc);
	if (argc != 6) {
		printf("Invalid argument\n");
		usage();
		return -1;
	}
	int opcode = atoi(argv[1]);
	char *dst = argv[2];
	char *gw = argv[3];
	char *dev = argv[4];
	int tableno = atoi(argv[5]);
	printf("opcode : %d, dst : %s, table : %d\n",
			opcode, dst, tableno);
	if ((strcmp(gw, "NULL") == 0) && (strcmp(dev, "NULL") == 0)) {
		route_modify(opcode, dst, NULL, NULL, tableno);
	} else {
		if (strcmp(gw, "NULL") == 0) {
			printf("dev : %s\n", dev);
			route_modify(opcode, dst, NULL, dev, tableno);
		} else if (strcmp(dev, "NULL") == 0) {
			printf("gw : %s\n", gw);
			route_modify(opcode, dst, gw, NULL, tableno);
		} else {
			printf("gw : %s, dev : %s\n", gw, dev);
			route_modify(opcode, dst, gw, dev, tableno);
		}
	}

	return 0;
}
