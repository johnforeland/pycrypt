#!/usr/bin/env python3

from pycrypt import pycrypt

expected_two = b"\x00\x01\xe2@\xe5N\xe1W\x06\xdcd\xa5\xd9;\xe3Siz\x0bq`\xf8\x18!\xdfB\x89\xa7\x1e\x9dv\x12\xf3\x7f\x93\xfe\x9c![\xab\x85\xa7\n\xad2@\x14\xf8s/P\xbda\xfd\x07E\xe9v5\xad\xc8\x0c\xb7\x18\x98\x8b\xd7\xe6\xf3\xcaA[Y\xa4\x8aA\x8dK\xc4\xa8\xf3\x9bm\xf4\x02XR\x0c2\x0ee7,\xf2\n\xcf?fDY\xbaF\xf5+RG\xb0\xbeq{\xb5\xa7w\x85\xdbk\x03%y\xca{j\xad*\xbd\xa2>0\xf1\x89\xfde\xe4[UkG\xda\xabk\xd8\xc3\xa7\x83\xac\x12\x81t<rN\xb3Y\xe9\xc8\x19\xc7\xa7#\xf7\xff\xd9\x1a\xad\x13\xccp\xb8\x17\xc3QI=(\x1e\x16Ct\xa9:\x03{(\xc4\xd9'\xe2mO@\xbeM\x08r\xdc\xcb\xed\xd1\xfcE:\xa1\xb3a\xef\xff\x9e}\x06`/\x9eW2\xe2I\xa9J2'\x88^\xa5\xe9N\xf8Ox5\xe6\xce\xe6N\x8fW\x95-\xfab[\x17 \xb9\xce{O\xabN[l(\xa6\xaf\xe2\x12\xfd\xc8\xe4\xe7Rh"

expected_three = b'\x00\x00\x00\x07\x9a\xdb\x9cKq\x05)q?j\xc1\x03\x08\xd5\x94\xd06{\x1dy\x9b\x9b^\xe6\xb3\x1b\xef\xf4\xd3\xa4\x9c\xa1\xdb\xa5\xc5\xdc\xf47CT\x8bb\xc3\xca\xe3w{0\x150\xde\xbc\xc7\xfee93#\x17\xcaI<\xa6\x1f\xc2\xeb\xa6\x16{}\xa7\x96\x9aOd6Y\xc3\x04\xb3\xd6"~B\x9a\xbd\xd2\xa5\xf4l\xdaV\x9dL8\xf0n\x80j\x1d\x7f\xc0\x81b\xb7\x04\x15\xd4\xfd\xf9\xbf\xae\x81:\x9a\x9a\xbc\xa7\x93\xbd\x85\xae\xd0\xfa0\x16\xd9M\xfcP\xfa\x1f\xc2Ae\xe4\xa5I\x83!S\xa1+\x86QxY7\xe1\xd7\x16\xd9\x95{\xfc\xd7\xec?\x8a\xe1\xa8\x88\x8a@\xc2\xa5O\xb2\x1b$\x94\x82_?\x0e\x1b/\xb2@0*k\xae\xfd\xde\x88\xc8\x93\xc8P|m\xca\xfdX\x1d\x9f\xb9\x97\x04\xe4\x07\x12\xbb\xf5\xba\x1fvB\x97\xc6\x8c\xadZ\xa1\x13\x10\'\xe8|\x99\xf4\xdd\xd2\xad\x08\xfb\x04\xca`S\x19\xe0)\xabZ\xa4\xde\xb7\x0f\xbd\\\x1cK\x9e\xa3\xbb\x98X\xab\x1a\xbe\xb17z\x17\xf0'

two = pycrypt(b'noctem', 123456, 2)
three = pycrypt(b'noctem', 7, 3)

assert two == expected_two
assert three == expected_three
