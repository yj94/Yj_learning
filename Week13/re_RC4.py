def init(box, key):
    for i in range(256):
        box[i] = i
    j = 0
    for i in range(256):
        j = (j + box[i] + key[i % len(key)]) % 256
        box[i], box[j] = box[j], box[i]

def crypt(box, input):
    output = []
    k = 0
    for i in range(len(input)):
        j = (i + 1) % 256
        k = (box[j] + k) % 256
        box[k], box[j] = box[j], box[k]
        output.append(box[(box[j] + box[k]) % 256] ^ input[i])
    return bytes(output)

data = [0xC3,0x82,0xA3,0x25,0xF6,0x4C, 0x36,0x3B,0x59,0xCC,0xC4,0xE9,0xF1,0xB5,0x32,0x18,0xB1, 0x96,0xAe,0xBF,0x08,0x35]
box = [0] * 256
init(box, b'[Warnning]Access_Unauthorized')
print(crypt(box, data)) 