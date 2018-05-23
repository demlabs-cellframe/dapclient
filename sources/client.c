/*
 Copyright (c) 2017-2018 (c) Project "DeM Labs Inc" https://github.com/demlabsinc
  All rights reserved.

 This file is part of DAP (Deus Applications Prototypes) the open source project

    DAP (Deus Applicaions Prototypes) is free software: you can redistribute it and/or modify
    it under the terms of the GNU Lesser General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    DAP is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU Lesser General Public License for more details.

    You should have received a copy of the GNU Lesser General Public License
    along with any DAP based project.  If not, see <http://www.gnu.org/licenses/>.
*/

#include <errno.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "dap_client.h"
#include "dap_common.h"

#define LOG_TAG "Client"
#define DAP_TEST_ADDR  "127.0.0.1"
#define DAP_TEST_PORT  56001

void client_stage_end_callback(dap_client_t * a_client, void * a_arg )
{
    (void) a_client;
    (void) a_arg;
    log_it(L_INFO, "End stage achieved");
}

/**
 * @brief client_stage_status_callback
 * @param a_client
 * @param a_arg
 */
void client_stage_status_callback(dap_client_t * a_client, void * a_arg )
{
    dap_client_stage_t l_stage = dap_client_get_stage(a_client);
    dap_client_stage_status_t l_stage_status = dap_client_get_stage_status(a_client);
    if(l_stage_status == DAP_CLIENT_STAGE_STATUS_ERROR){
        log_it(L_ERROR,"Error %s on stage %s", dap_client_error_str((dap_client_error_t)(long) a_arg),
               dap_client_get_stage_str(a_client));
    }else{
        (void) a_arg;
        log_it(L_INFO,"Stage %s status %s", dap_client_get_stage_str(a_client),
               dap_client_get_stage_status_str(a_client));
        if ( l_stage_status == DAP_CLIENT_STAGE_STATUS_DONE ){ // Stage complete
            switch ( l_stage ) {
                case DAP_CLIENT_STAGE_ENC : { // Encryption initialized
                   // sap_client_request_enc(a_client, SAP_C);
                }break;
                default: log_it (L_DEBUG, "Nothing to do");
            }
        }
    }
}

/**
 * @brief client_stage_status_error_callback
 * @param a_client
 * @param a_arg
 */
void client_stage_status_error_callback(dap_client_t * a_client, void * a_arg )
{
    log_it(L_ERROR, "Got an error state %s",dap_client_get_error_str(a_client) );
}


int main(int argc, char **argv) {
    puts("Client starts");
    dap_client_remote_init();
    dap_enc_init();
    dap_enc_key_init();
    dap_client_init();
    dap_client_t * s_client;
    s_client = dap_client_new(client_stage_status_callback,client_stage_status_error_callback);

    dap_client_set_uplink(s_client,DAP_TEST_ADDR, DAP_TEST_PORT);
    dap_client_go_stage(s_client, DAP_CLIENT_STAGE_ENC,client_stage_end_callback);

    sleep(1000);

    return 0;
}