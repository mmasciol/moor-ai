#ifndef _YAML_C_WRAP_API_H
#define _YAML_C_WRAP_API_H


#pragma once
#ifdef __cplusplus
extern "C" {
#endif
    void* yaml_open_file(char* fpath);
    void yaml_close_file(void* d);
#ifdef __cplusplus
}
#endif


#endif /* _YAML_C_WRAP_API_H */
