#include <cstring>
#include <iostream>
#include <stdexcept>
#include <vector>

#include "yaml-cpp/yaml.h"

#include "domain.h"

#include "include/yaml-c-wrap/api.h"


void* yaml_open_file(char* fpath)
{
    Domain* d = new Domain;
    d->container = new YAMLContainer;

    d->container->config = YAML::LoadFile(fpath);
    d->status = -9999;
    return d;
};


void yaml_close_file(void* d)
{
    Domain *domain = static_cast<Domain*>(d);
    delete domain->container;
     delete domain;
    return;
};
