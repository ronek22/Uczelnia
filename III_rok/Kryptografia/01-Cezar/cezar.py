'''
Jakub Ronkiewicz, 238155
Szyfr Cezara i Afiniczny
Proszę wywolywac program w nastepujacy sposob:
python cezar.py xy
gdzie:
x = {c - szyfr cezara, a - szyfr afiniczny}
y = {
    e - szyfrowanie,
    d - odszyfrowanie,
    j - analiza z tekstem jawnym,
    k - analiza w oparciu o kryptogram
}
'''
import sys
from fractions import gcd
# HELPERS
def check_big_small(x):
    ''' Check if the character is big or small '''
    if(x >= 97 and x <= 122):
        return 97
    elif(x >= 65 and x <= 90):
        return 65
    else:
        return 0
def check_key(cezar):
    with open('key.txt', 'r') as f:
        b, a = map(int, f.readline().split(' '))
        if cezar:
            a, a_inv = 1, 1
        elif gcd(a, 26) != 1:
            raise ValueError("BLAD KLUCZA\na - Musi byc liczba pierwsza")
        else:
            a_inv = mulinv(a, 26)
            if not a_inv:
                raise ValueError("BLAD KLUCZA\nNie udalo sie znalezc a^(-1)")
        return a, b, a_inv
def xgcd(b, n):
    x0, x1, y0, y1 = 1, 0, 0, 1
    while n != 0:
        q, b, n = b // n, n, b % n
        x0, x1 = x1, x0 - q * x1
        y0, y1 = y1, y0 - q * y1
    return  b, x0, y0
def mulinv(b, n):
    g, x, _ = xgcd(b, n)
    if g == 1:
        return x % n

# MAIN FUNCTIONS
def encrypt(cezar, text = 'plain.txt'):
    ''' Funkcja szyfrująca,
    a - wspł. afiniczny, b - klucz, text - tekst jawny'''

    crypt = ''
    with open(text, 'r') as f:
        plain = f.readline()

    # pierszsza przesuniecie, druga wspolczynnik
    a, b, a_inv = check_key(cezar)

    for x in plain:
        ind = ord(x) # pobranie numeru ASCII znaku
        fix = check_big_small(ind); ind -= fix
        if fix:
            funct = ((a * ind + b) % 26) + fix
            crypt += chr(funct)
        else:
            crypt += x
    with open('crypto.txt', 'w') as f:
        f.write(crypt)

def decrypt(cezar, text = 'crypto.txt'):
    ''' Funkcja deszyfrujaca,
    a - wspł. afiniczny, b - klucz, text - tekst jawny'''
    decrypted=''
    with open(text, 'r') as f:
        crypt = f.readline()

    a, b, a_inv = check_key(cezar)

    for x in crypt:
        ind = ord(x) # pobranie numeru ASCII znaku
        fix = check_big_small(ind); ind -= fix
        if fix:
            funct = ((a_inv * (ind - b)) % 26) + fix
            decrypted += chr(funct)
        else:
            decrypted += x

    with open('decrypt.txt', 'w') as f:
        f.write(decrypted)

def crack_cipher_with_cryptogram(cezar = True):
        ''' Funkcja łamiąca szyfr bez pomocy tekstu jawnego,
        a - wspł. afiniczny, b - klucz'''
        with open('crypto.txt', 'r') as f:
            crypt = f.readline()

        f = open('decrypt.txt', 'w')

        if cezar:
            a = 1
            for b in range(26):
                decrypted=''
                for x in crypt:
                    ind = ord(x) # pobranie numeru ASCII znaku
                    fix = check_big_small(ind); ind -= fix
                    if fix:
                        funct = ((a * (ind - b)) % 26) + fix
                        decrypted += chr(funct)
                    else:
                        decrypted += x
                f.write(decrypted)
        else:
            for a in range(26):
                a_inv = mulinv(a, 26)
                if not a_inv:
                    continue
                for b in range(26):
                    decrypted=''
                    for x in crypt:
                        ind = ord(x) # pobranie numeru ASCII znaku
                        fix = check_big_small(ind); ind -= fix
                        if fix:
                            funct = ((a_inv * (ind - b)) % 26) + fix
                            decrypted += chr(funct)
                        else:
                            decrypted += x
                    f.write(decrypted)
        f.close()

def crack_cipher_with_plaintext():
    decrypted = ''
    with open('extra.txt', 'r') as f:
        extra = f.readline()

    length = len(extra) - 1

    if length < 2:
        raise ValueError("Za krotki tekst jawny.")


    with open('crypto.txt', 'r') as f:
        crypto = f.readline()

    x = [] # x - plain text numbers, y - cipher text numbers
    y = [] # y = a*x + b


    for i in range(length):
        temp_x = ord(extra[i])
        temp_x -= check_big_small(temp_x)
        x.append(temp_x)

        temp_y = ord(crypto[i])
        temp_y -= check_big_small(temp_y)
        y.append(temp_y)

    # ROZWIAZYWANIE UKLADU ROWNAN MODULO
    x_subtract = x[0] - x[1]
    y_subtract = y[0] - y[1]

    if (x_subtract < 0):
        x_subtract *= -1
        y_subtract *= -1

    if(y_subtract < 0):
        y_subtract += 26

    a = (y_subtract * mulinv(x_subtract, 26)) % 26
    b = y[0] - a*x[0]
    a_inv = mulinv(a,26)

    for x in crypto:
        ind = ord(x) # pobranie numeru ASCII znaku
        fix = check_big_small(ind); ind -= fix
        if fix:
            funct = ((a_inv * (ind - b)) % 26) + fix
            decrypted += chr(funct)
        else:
            decrypted += x

    with open('key-new.txt', 'w') as f:
        f.write(str(b)+' '+str(a))

    with open('decrypt.txt', 'w') as f:
        f.write(decrypted)

def main(argv):
    if(len(argv) != 2):
        raise ValueError("Prosze podac tylko 2 argumenty.")
    if not(argv[0] in 'ca'):
        raise ValueError("Zły pierwszy argument, dozwolone[c - cezar,a - afiniczny]")
    if not(argv[1] in 'edjk'):
        raise ValueError("Dozwolne argumenty [e,d,j,k]\ne - szyfrowanie\nd - deszyfrowanie\nj - kryptoanaliza z tekstem jawnym\nk - kryptoanaliza z kryptogramem")

    cezar = argv[0]
    if cezar == 'a':
        cezar = False
    else:
        cezar = True

    # metody
    if argv[1] == 'e':
        encrypt(cezar)
        print("Szyfrowanie zakończone.\n")
    elif argv[1] == 'd':
        decrypt(cezar)
        print("Odszyfrowanie zakończone.\n")
    elif argv[1] == 'j':
        crack_cipher_with_plaintext()
        print("Kryptoanaliza z tekstem jawnym zakończona.\n")
    else:
        crack_cipher_with_cryptogram(cezar)
        print("Kryptoanaliza wyłącznie w oparciu o kryptogram zakończona.\n")

if __name__ == '__main__':
    main(sys.argv[1:2][0])
