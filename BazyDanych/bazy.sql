--1.2
SELECT imie FROM pracownik
--1.3
SELECT imie,nazwisko,dzial FROM pracownik
--2.2
SELECT nazwisko,imie FROM pracownik ORDER BY nazwisko ASC,imie ASC
--2.3
SELECT nazwisko,dzial,stanowisko FROM pracownik ORDER BY dzial ASC, stanowisko DESC
--3.2
SELECT DISTINCT dzial,stanowisko FROM pracownik
--3.3
SELECT DISTINCT dzial,stanowisko FROM pracownik ORDER BY dzial DESC,stanowisko DESC
--4.2
SELECT imie,nazwisko FROM pracownik WHERE stanowisko LIKE 'sprzedawca'
--4.3
SELECT imie,nazwisko,pensja FROM pracownik WHERE pensja>1500 ORDER BY pensja DESC
--5.2
SELECT imie,nazwisko,dzial,stanowisko FROM pracownik WHERE dzial='techniczny' AND (stanowisko='kierownik' OR stanowisko='sprzedawca')
--5.3
SELECT * FROM samochod WHERE marka!='Fiat' AND marka!='Ford'
--6.2
SELECT imie,nazwisko,data_zatr FROM pracownik WHERE imie IN('Anna','Marzena','Alicja')
--6.3
SELECT imie,nazwisko,miasto FROM klient WHERE miasto NOT IN('Warszawa','Wrocław')
--7.2
SELECT imie,nazwisko FROM klient WHERE nazwisko LIKE 'D%ski'
--7.3
SELECT imie,nazwisko FROM klient WHERE nazwisko LIKE '_o%' OR nazwisko LIKE '_a%'
--8.2
SELECT * FROM pracownik WHERE data_zatr BETWEEN '1997-01-10' AND '1997-12-31'
--8.3
SELECT * FROM samochod WHERE (przebieg BETWEEN 10000 AND 20000) OR (przebieg BETWEEN 30000 AND 40000)
--9.2
SELECT * FROM klient WHERE nr_karty_kredyt IS NOT NULL
--9.3
SELECT imie,nazwisko,COALESCE(dodatek,'0') AS wysokosc_dodatku FROM pracownik
--10.2
SELECT imie,nazwisko,pensja+0.5*pensja AS nowa_pensja FROM pracownik
--10.3
SELECT imie,nazwisko, 0.01*(pensja+COALESCE(dodatek,0)) AS procent FROM pracownik ORDER BY procent ASC
--11.2
SELECT TOP 4 * FROM pracownik ORDER BY nazwisko ASC,imie ASC
--11.3
SELECT TOP 1 * FROM wypozyczenie ORDER BY data_wyp DESC
--12.2
SELECT imie,nazwisko, DATEDIFF(day,data_zatr,GETDATE()) AS ilosc_dni FROM pracownik ORDER BY ilosc_dni DESC
--12.3
SELECT marka,typ,DATEDIFF(year,data_prod,GETDATE()) AS lata_od_produkcji FROM samochod ORDER BY lata_od_produkcji DESC
--13.2
SELECT UPPER(LEFT(imie,1))+LOWER(SUBSTRING(imie,2,LEN(imie))) AS imie,
UPPER(LEFT(nazwisko,1))+LOWER(SUBSTRING(nazwisko,2,LEN(nazwisko))) AS nazwisko FROM pracownik
--13.3
SELECT imie,nazwisko,STUFF(nr_karty_kredyt,LEN(nr_karty_kredyt)-6,LEN(nr_karty_kredyt),'xxxxxx') AS karta_kredyt FROM klient
--14.2
UPDATE klient SET imie='Jerzy',nazwisko='Nowak' WHERE id_klient=10
--14.3
UPDATE pracownik SET dodatek=dodatek+100 WHERE pensja<1500
--15.2
DELETE FROM wypozyczenie WHERE id_klient=17
--15.3
DELETE FROM samochod WHERE przebieg>60000
--16.2
INSERT INTO samochod(id_samochod,marka,typ,kolor,poj_silnika,data_prod,przebieg) VALUES
(50,'Skoda','Octavia','srebrny',1896,'2012-09-01',5000)
--16.3
INSERT INTO pracownik(id_pracownik,imie,nazwisko,data_zatr,dzial,stanowisko,pensja,dodatek,telefon,id_miejsce) VALUES
(12,'Alojzy','Mikos','2010-08-11','zaopatrzenie','magazynier',3000,50,'501-501-501',1)
--17.2
SELECT * FROM klient k
INNER JOIN wypozyczenie w ON k.id_klient=w.id_klient
WHERE w.data_odd IS NULL
ORDER BY k.nazwisko ASC, k.imie ASC
--17.3
SELECT k.imie,k.nazwisko,w.data_wyp AS data_wpl_kaucji, w.kaucja FROM wypozyczenie w
INNER JOIN klient k ON k.id_klient=w.id_klient
WHERE w.kaucja IS NOT NULL
--18.2
SELECT m.ulica,m.numer, s.marka, s.typ FROM wypozyczenie w INNER JOIN samochod s
ON w.id_samochod=s.id_samochod INNER JOIN miejsce m ON m.id_miejsce=w.id_miejsca_wyp
ORDER BY m.ulica ASC, m.numer ASC, s.marka ASC, s.typ
--18.3
SELECT s.id_samochod, s.marka, s.typ, k.imie, k.nazwisko FROM samochod s INNER JOIN wypozyczenie w
ON s.id_samochod=w.id_samochod INNER JOIN klient k ON k.id_klient=w.id_klient
ORDER BY s.id_samochod ASC
--19.2
SELECT AVG(pensja) AS srednia_pensja FROM pracownik
--19.3
SELECT MIN(data_prod) AS data_produkcji FROM samochod
--20.2
SELECT s.id_samochod,s.marka, s.typ, COUNT(w.id_samochod) AS ilosc_wyp
FROM samochod s LEFT JOIN wypozyczenie w
ON s.id_samochod=w.id_samochod
GROUP BY s.id_samochod,s.marka, s.typ
ORDER BY ilosc_wyp ASC
--20.3
SELECT p.imie,p.nazwisko, COUNT(w.id_wypozyczenie) AS ilosc_wyp
FROM pracownik p LEFT JOIN wypozyczenie w
ON p.id_pracownik=w.id_pracow_wyp
GROUP BY p.id_pracownik,p.imie,p.nazwisko
ORDER BY ilosc_wyp DESC
--21.2
SELECT s.id_samochod,s.marka, s.typ, COUNT(w.id_samochod) AS ilosc_wyp
FROM samochod s LEFT JOIN wypozyczenie w
ON s.id_samochod=w.id_samochod
GROUP BY s.id_samochod,s.marka, s.typ
HAVING COUNT(w.id_samochod)>=5
ORDER BY s.marka ASC, s.typ ASC
--21.3
SELECT p.imie,p.nazwisko, COUNT(w.id_wypozyczenie) AS ilosc_wyp
FROM pracownik p LEFT JOIN wypozyczenie w
ON p.id_pracownik=w.id_pracow_wyp
GROUP BY p.id_pracownik,p.imie,p.nazwisko
HAVING COUNT(w.id_wypozyczenie)<=20
ORDER BY ilosc_wyp ASC, p.nazwisko ASC, p.imie ASC
--22.2
SELECT imie,nazwisko,pensja FROM pracownik WHERE pensja>(SELECT AVG(pensja) FROM pracownik)
--22.3
SELECT marka,typ,data_prod FROM samochod WHERE data_prod=(SELECT MIN(data_prod) FROM samochod)
--23.2
SELECT imie,nazwisko FROM klient WHERE id_klient NOT IN(SELECT DISTINCT id_klient FROM wypozyczenie) ORDER BY nazwisko ASC, imie ASC
--23.3
SELECT imie,nazwisko FROM pracownik WHERE id_pracownik NOT IN(SELECT DISTINCT id_pracow_wyp FROM wypozyczenie)
--24.2
SELECT k.id_klient,k.imie,k.nazwisko
FROM klient k JOIN wypozyczenie w
ON k.id_klient=w.id_klient
GROUP BY k.id_klient,k.imie,k.nazwisko
HAVING COUNT(w.id_klient)=
(
	SELECT TOP 1 COUNT(w.id_klient) AS ilosc
	FROM wypozyczenie w
	GROUP BY w.id_klient
	ORDER BY ilosc ASC
)
ORDER BY k.nazwisko ASC, k.imie ASC
--24.3
SELECT p.id_pracownik,p.nazwisko,p.imie
FROM pracownik p JOIN wypozyczenie w
ON p.id_pracownik=w.id_pracow_wyp
GROUP BY p.id_pracownik,p.nazwisko,p.imie
HAVING COUNT(w.id_pracow_wyp) =
(
	SELECT TOP 1 COUNT(w.id_pracow_wyp) AS ilosc
	FROM wypozyczenie w
	GROUP BY w.id_pracow_wyp
	ORDER BY ilosc DESC
)
ORDER BY p.nazwisko ASC, p.imie ASC
--25.2
UPDATE pracownik SET dodatek=dodatek+10 WHERE id_pracownik IN (SELECT DISTINCT id_pracow_wyp FROM wypozyczenie WHERE MONTH(data_wyp)=5)
--25.3
UPDATE pracownik SET pensja=0.95*pensja WHERE id_pracownik NOT IN(SELECT DISTINCT id_pracow_wyp FROM wypozyczenie WHERE YEAR(data_wyp)=1999)
--26.2
DELETE FROM samochod WHERE id_samochod NOT IN(SELECT DISTINCT id_samochod FROM wypozyczenie)
--26.3
DELETE FROM pracownik WHERE id_pracownik NOT IN(SELECT DISTINCT id_pracow_wyp FROM wypozyczenie)
--27.2
SELECT imie,nazwisko FROM klient
INTERSECT
SELECT imie,nazwisko FROM pracownik
--27.3
SELECT imie,nazwisko FROM klient
EXCEPT
SELECT imie,nazwisko FROM pracownik
ORDER BY 2, 1

--ZADANIA Z KOLOSA
--Znajdź klientów (id_klient, imie, nazwisko), którzy mają rabat
--wyższy niż 2%, ale niższy niż 6%.
--Wynik posortuj leksykograficznie w/g nazwiska i imienia. --Rozwiązanie:
SELECT id_klient,imie,nazwisko FROM klient WHERE rabat>2 AND rabat<6 ORDER BY nazwisko ASC, imie ASC

--Zwiększ o 20% pensje pracownikom, ktorzy pracuja co najmniej 8 (pelnych) lat.
UPDATE pracownik SET pensja=pensja+(pensja*0.2) WHERE  DATEDIFF(yy,data_zatrudnienia,GETDATE())>=8

--Usuń klientów, którzy nie złożyli żadnego zamówienia.
DELETE klient
FROM klient k
LEFT JOIN zamowienie z ON k.id_klient=z.id_klient
WHERE z.data_zamowienia IS NULL

--Dla każdego pracownika (nazwisko i imię), wyświetl informację ile przyjął on zamówień.
--Uwzględnij też tych pracowników, którzy nie przyjęli żadnego zamówienia.
--Wynik posortuj malejąco po ilości przyjętych zamówień, a dla takiej samej
--ilości zamówień leksykograficznie po nazwisku i imieniu.
--Uwaga: dwóch pracowników może posiadać to samo imię i nazwisko.

SELECT p.nazwisko,p.imie,COUNT(z.id_pracownik) AS ilosc
FROM pracownik p
LEFT JOIN zamowienie z ON p.id_pracownik=z.id_pracownik
GROUP BY p.id_pracownik,p.imie,p.nazwisko
ORDER BY ilosc DESC, p.nazwisko ASC, p.imie ASC

--Znajdź nazwę kategorii (jednej lub kilku), w której znajduje się największa
--liczba produktów.
--Proszę nie używać konstrukcji TOP 1 WITH TIES.

SELECT k.nazwa, COUNT(pk.id_kategoria) as ilosc_prod FROM kategoria k
JOIN podkategoria pk ON k.id_kategoria=pk.id_kategoria
JOIN produkt p ON pk.id_podkategoria=p.id_podkategoria
GROUP BY k.id_kategoria, k.nazwa
HAVING COUNT(pk.id_kategoria) =
(
	SELECT TOP 1 COUNT(pk.id_kategoria) AS ilosc
	FROM podkategoria pk
	GROUP BY pk.id_kategoria
	ORDER BY ilosc DESC
)
