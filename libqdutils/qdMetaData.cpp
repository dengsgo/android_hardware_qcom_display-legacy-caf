/*
 * Copyright (c) 2012, Code Aurora Forum. All rights reserved.

 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are
 * met:
 *   * Redistributions of source code must retain the above copyright
 *     notice, this list of conditions and the following disclaimer.
 *   * Redistributions in binary form must reproduce the above
 *     copyright notice, this list of conditions and the following
 *     disclaimer in the documentation and/or other materials provided
 *     with the distribution.
 *   * Neither the name of Code Aurora Forum, Inc. nor the names of its
 *     contributors may be used to endorse or promote products derived
 *     from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED "AS IS" AND ANY EXPRESS OR IMPLIED
 * WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS
 * BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR
 * BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE
 * OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN
 * IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include <string.h>
#include <sys/mman.h>
#include <cutils/log.h>
#include <gralloc_priv.h>
#include "qdMetaData.h"

int setMetaData(private_handle_t *handle, int paramType, float paramValue) {
    if (!handle) {
        ALOGE("%s: Private handle is null!", __func__);
        return -1;
    }
    if (handle->fd_metadata == -1) {
        ALOGE("%s: Bad fd for extra data!", __func__);
        return -1;
    }
    unsigned long size = ROUND_UP_PAGESIZE(sizeof(MetaData_t));
    void *base = mmap(NULL, size, PROT_READ|PROT_WRITE, MAP_SHARED,
        handle->fd_metadata, 0);
    if (!base) {
        ALOGE("%s: mmap() failed: Base addr is NULL!", __func__);
        return -1;
    }
    MetaData_t *data = reinterpret_cast <MetaData_t *>(base);
    data->paramType = paramType;
    data->paramValue = paramValue;
    if(munmap(base, size))
        ALOGE("%s: failed to unmap ptr 0x%x, err %d", __func__, (int)base, errno);
    return 0;
}
