'''
Jakub Ronkiewicz, 238155
Bledne powtorzenie klucza jednorazowe
Prosze wywolywac program w nastepujacy sposob:
python xor.py x
gdzie:
x = {
    p - przygotowanie tekstu do przykladu dzialania,
    e - szyfrowanie,
    k - kryptoanaliza wylacznie w oparciu o kryptogram,
}
'''
from itertools import cycle
import sys
KEY_LEN = 0

def set_keylen():
    global KEY_LEN
    with open('key.txt') as f:
        KEY_LEN = len(f.read()) - 1

def prepare_text():
    set_keylen();
    plain = ''

    with open('orig.txt', 'r') as f:
        orig = f.read()

    orig = orig.lower()
    for x in orig:
        if(x.isalpha() or x.isspace()):
            plain += x

    dest = open('plain.txt', 'w')
    for x in range(len(plain)):
        dest.write(plain[x])
        if((x+1)%KEY_LEN == 0 and x!=0): dest.write('\n')

def encrypt():
    with open('key.txt', 'r') as f:
        key = f.read()

    with open('plain.txt', 'r') as f:
        plain = f.read()

    cyphered = ' '.join(str(ord(c)^ord(k)) for c,k in zip(plain, cycle(key)))

    with open('crypto.txt', 'w') as f:
        f.write(cyphered)

def analysis():
    set_keylen()

    with open('crypto.txt', 'r') as f:
        crypted = f.read().split(' ')
    key = [0] * KEY_LEN
    crypted = list(map(int, crypted))
    crypted = crypted[:-1]



    ind = 0
    for x in crypted:
        if ind == KEY_LEN:
            ind = 0
            continue
        # jesli trafilismy na spacje to musi byc wieksze niz 32, bo xor litery z litera jest mniejszy niz 32
        if x > 32:
            key[ind] = x ^ 32
        ind += 1
    key.append(10)


    if 0 in key:
        print("Nie udalo sie zlamac klucza (Mozliwe powody):\n\tZa krotki tekst w stosunku do klucza\n\tZa malo spacji w tekscie\nTam gdzie mamy spacje nie udalo sie znalezc znaku klucza (mozliwe zlamanie klucza BruteForcem)\n")
        not_entire_key = ''.join(chr(x) for x in key)
        not_entire_key = not_entire_key.replace(chr(0), '_')
        print(not_entire_key)
    else:
        print("Znaleziono klucz:\n\n" + ''.join(chr(x) for x in key))
        print("Proba odszyfrowania tekstu:")
        decrypted = ''.join(chr(c^k) for c,k in zip(crypted, cycle(key)))
        with open('decrypt.txt', 'w') as f:
            f.write(decrypted)
        print("Zakonczona powodzeniem.")

def main(argv):
    if(len(argv) != 1):
        raise ValueError("Prosze podac tylko 1 argument")
    operation = argv[0]

    if operation == 'p':
        prepare_text()
        print("Przygotowanie tekstu zakonczone")
    elif operation == 'e':
        encrypt()
        print("Szyfrowanie zakonczone")
    elif operation == 'k':
        analysis()
        print("Kryptoanaliza zakonczona")
    else:
        raise ValueError("Zly argument, dozwolone[p e k].")

if __name__ == "__main__":
    if(len(sys.argv) != 2): raise IndexError("Musisz podac jeden argument [ p e k ].")
    main(sys.argv[1])
