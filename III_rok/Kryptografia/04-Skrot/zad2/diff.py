import sys

def diff(hex1, hex2):

	bin1 = bin(int(hex1, 16))[2:]
	bin2 = bin(int(hex2, 16))[2:]

	dlugosc = len(bin1)
	roznica = ([x == y for (x, y) in zip(bin1, bin2)].count(False))
	procent = (float(roznica)/float(dlugosc))*100

	return "Liczba rozniacych sie bitow: %d z %d, procentowo: %2.f%%." % (roznica, dlugosc, procent)

def print_command(mode):
    return "cat hash.pdf personal.txt | " + mode + "\n" + "cat hash.pdf personal_.txt | " + mode + "\n"

def main():
    commands = ['md5sum', 'sha1sum', 'sha224sum', 'sha256sum', 'sha384sum', 'sha512sum']
    with open('hash.txt') as f:
        results = f.read().splitlines()

    wynik = open('diff.txt', 'w')

    for i in range(0, 12, 2):
        wynik.write(print_command(commands[i/2]))
        wynik.write(results[i]+"\n" + results[i+1] + "\n")
        wynik.write(diff(results[i], results[i+1]))
        wynik.write('\n\n')

    wynik.close()



main()
