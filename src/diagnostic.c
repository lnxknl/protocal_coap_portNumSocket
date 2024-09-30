#include "coap.h"
#include <inttypes.h>

char* InteractionRoleToString(CoAP_InteractionRole_t role) {
	switch (role) {
	case COAP_ROLE_NOT_SET:
		return "NOT_SET";
	case COAP_ROLE_SERVER:
		return "SERVER";
	case COAP_ROLE_NOTIFICATION:
		return "NOTIFICATION";
	case COAP_ROLE_CLIENT:
		return "CLIENT";
	default:
		return "UNKNOWN_ROLE";
	}
}

char* InteractionStateToString(CoAP_InteractionState_t state) {
	switch (state) {
	case COAP_STATE_NOT_SET:
		return "NOT_SET";
	case COAP_STATE_HANDLE_REQUEST:
		return "HANDLE_REQUEST";
	case COAP_STATE_RESOURCE_POSTPONE_EMPTY_ACK_SENT:
		return "RESOURCE_POSTPONE_EMPTY_ACK_SENT";
	case COAP_STATE_RESPONSE_SENT:
		return "RESPONSE_SENT";
	case COAP_STATE_RESPONSE_WAITING_LEISURE:
		return "RESPONSE_WAITING_LEISURE";
	case COAP_STATE_READY_TO_NOTIFY:
		return "READY_TO_NOTIFY";
	case COAP_STATE_NOTIFICATION_SENT:
		return "NOTIFICATION_SENT";
	case COAP_STATE_READY_TO_REQUEST:
		return "READY_TO_REQUEST";
	case COAP_STATE_WAITING_RESPONSE:
		return "WAITING_RESPONSE";
	case COAP_STATE_HANDLE_RESPONSE:
		return "HANDLE_RESPONSE";
	case COAP_STATE_FINISHED:
		return "FINISHED";
	default:
		return "UNKNOWN_STATE";
	}
}

char* ResultToString(CoAP_Result_t res) {
	switch (res) {
	case COAP_OK:
		return "COAP_OK";
	case COAP_NOT_FOUND:
		return "COAP_NOT_FOUND";
	case COAP_PARSE_DATAGRAM_TOO_SHORT:
		return "COAP_PARSE_DATAGRAM_TOO_SHORT";
	case COAP_PARSE_UNKOWN_COAP_VERSION:
		return "COAP_PARSE_UNKOWN_COAP_VERSION";
	case COAP_PARSE_MESSAGE_FORMAT_ERROR:
		return "COAP_PARSE_MESSAGE_FORMAT_ERROR";
	case COAP_PARSE_TOO_MANY_OPTIONS:
		return "COAP_PARSE_TOO_MANY_OPTIONS";
	case COAP_PARSE_TOO_LONG_OPTION:
		return "COAP_PARSE_TOO_LONG_OPTION";
	case COAP_PARSE_TOO_MUCH_PAYLOAD:
		return "COAP_PARSE_TOO_MUCH_PAYLOAD";
	case COAP_PACK_TOO_MANY_OPTIONS:
		return "COAP_PACK_TOO_MANY_OPTIONS";
	case COAP_PACK_TOO_LONG_OPTION:
		return "COAP_PACK_TOO_LONG_OPTION";
	case COAP_ERR_ARGUMENT:
		return "COAP_ERR_ARGUMENT";
	case COAP_ERR_SOCKET:
		return "COAP_ERR_SOCKET";
	case COAP_ERR_NETWORK:
		return "COAP_ERR_NETWORK";
	case COAP_ERR_OUT_OF_MEMORY:
		return "COAP_ERR_OUT_OF_MEMORY";
	case COAP_ERR_TOO_LONG_URI_PATH:
		return "COAP_ERR_TOO_LONG_URI_PATH";
	case COAP_ERR_NOT_FOUND:
		return "COAP_ERR_NOT_FOUND";
	case COAP_ERR_WRONG_OPTION:
		return "COAP_ERR_WRONG_OPTION";
	case COAP_ERR_EXISTING:
		return "COAP_ERR_EXISTING";
	case COAP_TRUE:
		return "COAP_TRUE";
	case COAP_FALSE:
		return "COAP_FALSE";
	case COAP_ERR_WRONG_REQUEST:
		return "COAP_ERR_WRONG_REQUEST";
	case COAP_BAD_OPTION_VAL:
		return "COAP_BAD_OPTION_VAL";
	case COAP_BAD_OPTION_LEN:
		return "COAP_BAD_OPTION_LEN";
	case COAP_REMOVED:
		return "COAP_REMOVED";
	case COAP_ERR_UNKNOWN:
		return "COAP_ERR_UNKNOWN";
	case COAP_ERR_REMOTE_RST:
		return "COAP_ERR_REMOTE_RST";
	case COAP_ERR_OUT_OF_ATTEMPTS:
		return "COAP_ERR_OUT_OF_ATTEMPTS";
	case COAP_ERR_TIMEOUT:
		return "COAP_ERR_TIMEOUT";
	case COAP_WAITING:
		return "COAP_WAITING";
	case COAP_HOLDING_BACK:
		return "COAP_HOLDING_BACK";
	case COAP_RETRY:
		return "COAP_RETRY";
	default:
		return "UNKNOWN_RESULT";
	}
}

char* ReliabilityStateToString(CoAP_ConfirmationState_t state) {
	switch (state) {
	case NOT_SET:
		return "NOT_SET";
	case ACK_SEND:
		return "ACK_SET";
	case RST_SEND:
		return "RST_SET";
	default:
		return "UNKNOWN_STATE";
	}
}

void _rom PrintEndpoint(const NetEp_t* ep) {
	switch (ep->NetType) {
	case EP_NONE:
		INFO("NONE");
		break;
	case IPV6:
		INFO("IPv6, [");
		PRINT_IPV6(ep->NetAddr.IPv6);
		INFO("]: %u", ep->NetPort);
		break;
	case IPV4:
		INFO("IPv4, %d.%d.%d.%d:%d",
				ep->NetAddr.IPv4.u8[0], ep->NetAddr.IPv4.u8[1], ep->NetAddr.IPv4.u8[2], ep->NetAddr.IPv4.u8[3],
				ep->NetPort);
		break;
	case BTLE:
		INFO("BTLE");
		break;
	case UART:
		INFO("UART, COM%d", ep->NetAddr.Uart.ComPortID);
		break;
	default:
		INFO("UNKNOWN_EP (%d)", ep->NetType);
	}
}

void PrintToken(CoAP_Token_t* token) {
	uint8_t tokenBytes = token->Length;
	if (tokenBytes > 0) {
		INFO("%u Byte -> 0x", tokenBytes);
		int i;
		for (i = 0; i < tokenBytes; i++) {
			INFO("%02x", token->Token[i]);
		}
	} else {
		INFO("%u Byte -> 0x0", tokenBytes);
	}
}

void _rom PrintInteractions(CoAP_Interaction_t *pInteractions) {
	(void)pInteractions;
	int cnt = 0;
	for (CoAP_Interaction_t* pIA = CoAP.pInteractions; pIA != NULL; pIA = pIA->next) {
		cnt++;
	}

	INFO("Interactions: %d\n", cnt);
	INFO("-------------\n");
	for (CoAP_Interaction_t* pIA = CoAP.pInteractions; pIA != NULL; pIA = pIA->next) {
		INFO("- Role: %s, State: %s\n",
				InteractionRoleToString(pIA->Role), InteractionStateToString(pIA->State));
		INFO("RetransCnt: %u, SleepUntil %"PRIu32", AckTimeout: %"PRIu32"\n", pIA->RetransCounter, pIA->SleepUntil, pIA->AckTimeout);
		INFO("Socket: %p, RemoteEp: ", pIA->socketHandle);
		PrintEndpoint(&pIA->RemoteEp);
		INFO("\n");
		INFO("ReqReliabilityState: %s\n", ReliabilityStateToString(pIA->ReqConfirmState));
		INFO("RespReliabilityState: %s\n", ReliabilityStateToString(pIA->ResConfirmState));

		INFO("Observer: ");
		if (pIA->pObserver != NULL) {
			PrintEndpoint(&pIA->pObserver->Ep);
			INFO(", Socket: %p, FailCnt: %d, Token: ", pIA->pObserver->socketHandle, pIA->pObserver->FailCount);
			PrintToken(&pIA->pObserver->Token);
			INFO("\n");
		} else {
			INFO("NONE\n");
		}

		if (pIA->UpdatePendingNotification) {
			INFO("Update Pending Notifications\n");
		}

		// TODO: Consider: Resource description and observers
	}
	INFO("-------------\n\n");
}
