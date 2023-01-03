#!/usr/bin/env python
# -*- coding: utf-8 -*-
import moor_ai.api as api


if __name__ == '__main__':
    item = api.Interface()
    item.allocate()
    # item.flush_message()
    item.free()
