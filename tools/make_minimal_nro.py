#!/usr/bin/env python3
import struct
out = bytearray(0x200)
out[0:3] = b'NRO'
struct.pack_into('<I', out, 4, 0x1000)  # size
struct.pack_into('<Q', out, 0x100, 0x80020000)  # entry
open('/tmp/minimal.nro', 'wb').write(out)
print('minimal.nro created')
