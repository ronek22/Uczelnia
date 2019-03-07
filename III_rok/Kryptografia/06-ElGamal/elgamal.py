# JAKUB RONKIEWICZ
# SYSTEM ELGAMALA

from random import randint
from fractions import gcd
import binascii
import sys
# HELPERS
def mul_inv(a, b):
	    b0 = b
	    x0, x1 = 0, 1
	    if b == 1: return 1
	    while a > 1:
	        q = a / b
	        a, b = b, a%b
	        x0, x1 = x1 - q * x0, x0
	    if x1 < 0: x1 += b0
	    return x1

def stringToLong(s):
    return long(binascii.hexlify(s), 16)

def longToString(n):
    return binascii.unhexlify("%x" % n)

# KEY METHODS

def generate_prime():
	p = '1665997633093155705263923663680487185948531888850484859473375695734301776192932338784530163'
	q = '170057347237941209366519667629336535698946063913573988287540019819022183488419112350737049'
	with open('elgamal.txt', 'w') as f:
		f.write(p + "\n" + q)

def generate_keys():
    with open('elgamal.txt' , 'r') as f:
        lines = f.read().splitlines()
        p, g = map(int, lines)

    priv_b = randint(1, p) # klucz prywatny Bolka
    pub_b = pow(g, priv_b, p)

    with open('private.txt' , 'w') as f:
        f.write('%d\n%d\n%d' % (p, g, priv_b))

    with open('public.txt' , 'w') as f:
        f.write('%d\n%d\n%d' % (p, g, pub_b))

def encryption():
    with open('public.txt' , 'r') as f:
        lines = f.read().splitlines()
        p, g, pub_b = map(int, lines)

    with open('plain.txt', 'r') as f:
        m = f.read()

    m = stringToLong(m)
    if m >= p: raise ValueError("Wiadomosc jest za dluga, dla danej liczby pierwszej")

    with open('crypto.txt', 'w') as f:
        k = randint(0, p-1)
        r = pow(g, k, p)
        t = pow(pub_b, k, p) * m
        f.write(str(r)+' '+str(t)+'\n')

def decrypt():
    with open('crypto.txt') as f:
        cipher = f.read().splitlines()[0]

    with open('private.txt') as f:
        lines = f.read().splitlines()
        p, _, priv_b = map(int, lines)

    with open('decrypt.txt', 'w') as f:
            r, t = map(int, cipher.split())
            letter = t / pow(r,priv_b, p)
            f.write(longToString(letter))

def signature():
    with open('private.txt', 'r') as f:
        lines = f.read().splitlines()
        p, g, priv_b = map(int, lines)

    with open('message.txt', 'r') as f:
        message = f.read()
        m = stringToLong(message)

    while True:
        k = randint(3, p-1)
        if gcd(k, p-1) == 1: break

    if m >=p: raise ValueError("Wiadomosc jest za dluga, dla danej liczby pierwszej")

    r = pow(g, k, p)
    l = mul_inv(k,p-1)
    x = l*(m-priv_b*r)%(p-1)

    with open('signature.txt' , 'w') as f:
        f.write(str(r)+'\n'+str(x))

def verify():
    with open('signature.txt', 'r') as f:
        lines = f.read().splitlines()
        r, x = map(int, lines)

    with open('public.txt', 'r') as f:
        lines = f.read().splitlines()
        p, g, B = map(int, lines)

    with open('message.txt', 'r') as f:
        message = f.read()
        m = stringToLong(message)

    v1 = (pow(r, x, p) * pow(B, r, p))%p
    v2 = pow(g, m, p)

    result = v1 == v2
    with open('verify.txt', 'w') as f:
        f.write("Weryfikacja: %s" % result)

    print("Weryfikacja: %s" % result)

def main(argv):
    if(len(argv) != 2):
        raise ValueError("Prosze podac tylko 1 argument [-g -k -e -d -s -v]")
    operation = argv

    if operation == '-g':
        generate_prime()
        print("Generowanie p i g zakonczone.")
    elif operation == '-k':
        generate_keys()
        print("Generowanie kluczy zakonczone.")
    elif operation == '-e':
        encryption()
        print("Szyfrowanie zakonczone")
    elif operation == '-d':
        decrypt()
        print("Deszyfrowanie zakonczone")
    elif operation == '-s':
        signature()
        print("Podpis wygenerowany")
    elif operation == '-v':
        print("WERYFIKACJA:\n")
        verify()
    else:
        raise ValueError("Zly argument, dozwolone[-g -k -e -d -s -v].")

if __name__ == "__main__":
    if(len(sys.argv) != 2): raise ValueError("Musisz podac jeden argument [-g -k -e -d -s -v ].")
    main(sys.argv[1])
