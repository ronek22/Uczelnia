from string import lowercase
from operator import itemgetter
import sys

english_frequences = [
    0.08167, 0.01492, 0.02782, 0.04253, 0.12702, 0.02228, 0.02015,
    0.06094, 0.06966, 0.00153, 0.00772, 0.04025, 0.02406, 0.06749,
    0.07507, 0.01929, 0.00095, 0.05987, 0.06327, 0.09056, 0.02758,
    0.00978, 0.02360, 0.00150, 0.01974, 0.00074]


def prepare(orig='orig.txt'):
    
    with open(orig, 'r') as f:
        content = f.read()
    plain = ''
    content = content.lower()
    for x in content:
        if(x.isalpha()):
            plain += x

    with open('plain.txt', 'w') as f:
        f.write(plain)


def set_mode(m):
    if(m == 'e'):
        text_name = 'plain.txt'
        dest_name = 'crypto.txt'
    elif(m == 'd'):
        text_name = 'crypto.txt'
        dest_name = 'decrypt.txt'
    else:
        raise AttributeError("Nie obslugiwany tryb.")

    return (text_name, dest_name)


def crypto(mode, key_name='key.txt'):
    '''Module for encrypting and decrypting'''

    (text_name, dest_name) = set_mode(mode)

    with open(text_name, 'r') as f:
        text = f.read()

    with open(key_name, 'r') as f:
        key = f.read()

    len_key = len(key) - 1

    result = ""
    i = 0
    for x in text:
        ind_txt = ord(x) - 97  # pobranie numeru ASCII znaku
        ind_key = ord(key[i % len_key]) - 97
        i += 1

        cipher = ((ind_txt + ind_key) % 26) + \
            97 if mode == 'e' else ((ind_txt - ind_key) % 26) + 97
        result += chr(cipher)

    with open(dest_name, 'w') as f:
        f.write(result)


def crypto_analysis(target_freqs):

    with open('crypto.txt') as f:
        input = f.read()

    nchars = len(lowercase)  # 26
    ordA = ord('a')
    sorted_targets = sorted(target_freqs)  # sorted frequencies

    def frequency(input):
        result = [[c, 0.0] for c in lowercase]
        for c in input:
            result[c - ordA][1] += 1
        return result

    def correlation(input):
        result = 0.0
        freq = frequency(input)
        freq.sort(key=itemgetter(1))

        for i, f in enumerate(freq):
            result += f[1] * sorted_targets[i]
        return result

    cleaned = [ord(c) for c in input.lower()]  # numbers instead of letters
    best_len = 0
    best_corr = -100.0

    # Assume that if there are less than 20 characters
    # per column, the key's too long to guess
    for i in xrange(2, len(cleaned) // 20):
        pieces = [[] for _ in xrange(i)]
        for j, c in enumerate(cleaned):
            pieces[j % i].append(c)

        # The correlation seems to increase for smaller
        # pieces/longer keys, so weigh against them a little
        corr = -0.5 * i + sum(correlation(p) for p in pieces)

        if corr > best_corr:
            best_len = i
            best_corr = corr

    if best_len == 0:
        return ("Text is too short to analyze", "")

    pieces = [[] for _ in xrange(best_len)]
    for i, c in enumerate(cleaned):
        pieces[i % best_len].append(c)

    freqs = [frequency(p) for p in pieces]

    key = ""
    for fr in freqs:
        fr.sort(key=itemgetter(1), reverse=True)

        m = 0
        max_corr = 0.0
        for j in xrange(nchars):
            corr = 0.0
            c = ordA + j
            for frc in fr:
                d = (ord(frc[0]) - c + nchars) % nchars
                corr += frc[1] * target_freqs[d]

            if corr > max_corr:
                m = j
                max_corr = corr

        key += chr(m + ordA)

    r = (chr((c - ord(key[i % best_len]) + nchars) % nchars + ordA)
         for i, c in enumerate(cleaned))

    with open('key-crypto.txt', 'w') as f:
        f.write(key)


def main(argv):
    if(len(argv) != 1):
        raise ValueError("Prosze podac tylko 1 argument")
    operation = argv[0]

    if operation == 'p':
        prepare()
        print("Przygotowanie tekstu zakonczone")
    elif operation == 'e':
        crypto('e')
        print("Szyfrowanie zakonczone")
    elif operation == 'd':
        crypto('d')
        print("Deszyfrowanie zakonczone")
    elif operation == 'k':
        crypto_analysis(english_frequences)
        print("Kryptoanaliza zakonczona")
    else:
        raise ValueError("Zly argument, dozwolone[p e d k].")

if __name__ == "__main__":
    if(len(sys.argv) != 2): raise ValueError("Musisz podac jeden argument [ p e d k ].")
    main(sys.argv[1])
