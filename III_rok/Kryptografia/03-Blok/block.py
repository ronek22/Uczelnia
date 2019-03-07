from Crypto.Cipher import AES
from PIL import Image
from hashlib import md5
import os


def read_key():
    try:
        with open('key.txt', 'r') as keyfile:
            key = keyfile.read().splitlines()[0]
    except IOError:
        print("BRAK PLIKU Z KLUCZEM -> ZWRACAM DOMYSLNY")
        return "0123456789ABCDEF"

    if not len(key) in [16, 24, 32]:
        keyMD5 = md5(key).digest()
        return keyMD5
    return key

def encryptImage(img_file, mode, out, key):
    blSize = 16
    plain = open(img_file, 'rb')

    # otwieramy plik do zapisu w trybie binarym i kopiujemy naglowki z infromacjami o pliku
    crypted = open(out, 'wb')
    crypted.write(plain.read(14)) # pierwsze 14 bajtow, to naglowek BMP
    crypted.write(plain.read(40)) # kolejne 40 bajtow, to naglowek DIB

    width, height = Image.open(img_file).size # pobranie rozmiarow obrazka

    raw = plain.read(width * height * 3) # kazdy piksel jest opisany za pomoca trzech liczb(RGB)
    raw += (blSize - len(raw) % blSize ) * "!" # obrazek musi byc dopasowany do dlugosci bloku

    aes = AES.new(key, mode, os.urandom(16)) if mode == AES.MODE_CBC else AES.new(key, mode)
    enc = aes.encrypt(raw)
    crypted.write(enc)

    plain.close()
    crypted.close()
    tryb = "CBC" if mode == AES.MODE_CBC else "ECB"
    print("Szyfrowanie " + img_file + " za pomoca " + tryb + " do " + out + " zakonczone.")


if __name__ == "__main__":
    key = read_key()
    encryptImage("plain.bmp", AES.MODE_ECB, "ecb_crypto.bmp", key)
    encryptImage("plain.bmp", AES.MODE_CBC, "cbc_crypto.bmp", key)
    print("UKONCZONO!")
