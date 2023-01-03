#!/usr/bin/env python
# -*- coding: utf-8 -*-
from ctypes import (
    byref,
    c_char_p,
    cdll,
    c_int,
    c_void_p,
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
    raise OSError(
        'Unsupported operating system')


lib_name = 'libmoor-ai{}'.format(
    ext)


class Domain(Structure):
    def __init__(self, obj, name=''):
        self.obj = obj
    _fields_ = [
        ('label', POINTER(c_char_p))]


class Interface(object):
    domain = (c_void_p * 1)()

    try:
        _lib = cdll.LoadLibrary(os.path.join(sys.prefix, lib_name))
    except OSError:
        _lib = cdll.LoadLibrary(
            os.path.join('../bin/', lib_name))

    _lib.api_allocate_domain.restype = c_int
    _lib.api_free_domain.restype = c_int

    _lib.api_allocate_domain.argtype = [  # type: ignore
        POINTER(Domain), c_char_p]
    _lib.api_free_domain.argtype = [POINTER(Domain), c_char_p]  # type: ignore

    def allocate(self) -> None:
        size = self._lib.api_allocate_domain(byref(self.domain))
        print(size)

    def free(self) -> None:
        size = self._lib.api_free_domain(byref(self.domain))
        print(size)
