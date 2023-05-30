from Crypto.Cipher import AES
from hashlib import *
from pwn import *

f = open('./flag.txt.enc', 'rb')
prg = f.read()

input1 = 'recis'
input2 = 'cannibalization'

key = bytes.fromhex(sha256(input1.encode()).hexdigest())

iv = bytes.fromhex(md5(input2.encode()).hexdigest())

text = prg

cipher = AES.new(key, AES.MODE_CBC, iv)

plaintext = cipher.decrypt(text)

print (plaintext)
