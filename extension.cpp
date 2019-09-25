/**
 * vim: set ts=4 :
 * =============================================================================
 * SourceMod Sample Extension
 * Copyright (C) 2004-2008 AlliedModders LLC.  All rights reserved.
 * =============================================================================
 *
 * This program is free software; you can redistribute it and/or modify it under
 * the terms of the GNU General Public License, version 3.0, as published by the
 * Free Software Foundation.
 * 
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
 * FOR A PARTICULAR PURPOSE.  See the GNU General Public License for more
 * details.
 *
 * You should have received a copy of the GNU General Public License along with
 * this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 * As a special exception, AlliedModders LLC gives you permission to link the
 * code of this program (as well as its derivative works) to "Half-Life 2," the
 * "Source Engine," the "SourcePawn JIT," and any Game MODs that run on software
 * by the Valve Corporation.  You must obey the GNU General Public License in
 * all respects for all other code used.  Additionally, AlliedModders LLC grants
 * this exception to all derivative works.  AlliedModders LLC defines further
 * exceptions, found in LICENSE.txt (as of this writing, version JULY-31-2007),
 * or <http://www.sourcemod.net/license.php>.
 *
 * Version: $Id$
 */

#include "extension.h"
#include <sys/socket.h>
#include <stdlib.h>
#include <string.h>
#include <sys/un.h>
#include <unistd.h>

cell_t OneIsOne(IPluginContext *pContext, const cell_t *params) {
    const cell_t one = 1;
    cell_t maybeone = params[1];
    return maybeone == one;
}

static const sp_nativeinfo_t Natives[] = {
    { "OneIsOne", OneIsOne },
    { NULL, NULL },
};

void Hackfortress::SDK_OnAllLoaded() {
    sharesys->AddNatives(myself, Natives);
}

bool Hackfortress::SDK_OnLoad(char *error, size_t maxlength, bool late) {
    int tmp_fd = socket(AF_UNIX, SOCK_STREAM, 0);
    if (tmp_fd < 0) {
        const char *err1 = "Can't open unix socket";
        if (maxlength >= strlen(err1)) {
            strcpy(error, err1);
        }
        return false;
    }
    this->unix_socket_fd = tmp_fd;

    struct sockaddr_un address = {};
    address.sun_family = AF_UNIX;
    snprintf(address.sun_path, 108, "/tmp/hackfortress-exchanger.sock");

    if (connect(this->unix_socket_fd, (struct sockaddr *) &address, sizeof(struct sockaddr_un))) {
        shutdown(this->unix_socket_fd, SHUT_RDWR);
        const char *err1 = "Can't connect unix socket";
        if (maxlength >= strlen(err1)) {
            strcpy(error, err1);
        }
        return false;
    }

    return true;
}

void Hackfortress::SDK_OnUnload() {
    shutdown(this->unix_socket_fd, SHUT_RDWR);
}

Hackfortress g_Hackfortress;		/**< Global singleton for extension's main interface */

SMEXT_LINK(&g_Hackfortress);
