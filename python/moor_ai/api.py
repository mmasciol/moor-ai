#!/usr/bin/env python
# -*- coding: utf-8 -*-
from ctypes import (
    byref,
    c_char_p,
    cdll,
    c_int,
    POINTER,
    Structure
)
import os
import platform
import sys


if platform.system() == 'Linux':
    ext = '.so'
elif platform.system() == 'Darwin':
    ext = '.dylib'
else:
    raise OSError('Unsupported operating system')


lib_name = 'libmoor-ai{}'.format(ext)


class DomainTag(Structure):
    def __init__(self, obj, name=''):
        self.obj = obj
    _fields_ = [('label', POINTER(c_char_p))]


class Domain(object):
    # domain = POINTER(DomainTag)
    domain = (POINTER(DomainTag) * 1)()

    try:
        _lib = cdll.LoadLibrary(os.path.join(sys.prefix, lib_name))
    except OSError:
        _lib = cdll.LoadLibrary(os.path.join('./bin/', lib_name))

    _lib.api_allocate_domain.restype = c_int
    _lib.api_free_domain.restype = c_int

    _lib.api_allocate_domain.argtype = [POINTER(DomainTag)]  # type: ignore
    _lib.api_free_domain.argtype = [POINTER(DomainTag)]  # type: ignore

    def allocate(self) -> None:
        size = self._lib.api_allocate_domain(byref(self.domain))
        print(size)

    def free(self) -> None:
        size = self._lib.api_free_domain(byref(self.domain))
        print(size)
