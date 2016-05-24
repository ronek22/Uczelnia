# Baza Danych : Rozgrywki Piłkarskie

### [PostgreSQL] Utworzenie bazy danych i dodanie rekordów
```sql
CREATE TABLE typ_sedziego (
	id_typ_sedziego SERIAL PRIMARY KEY,
	nazwa varchar(30) UNIQUE NOT NULL
);

CREATE TABLE sedzia (
	id_sedzia SERIAL PRIMARY KEY,
	id_typ_sedziego INT NOT NULL,
	imie varchar(20) NOT NULL,
	nazwisko varchar(30) NOT NULL,
	data_urodzenia DATE NOT NULL,
	FOREIGN KEY(id_typ_sedziego) REFERENCES typ_sedziego(id_typ_sedziego)
);

CREATE TABLE kraj (
	id_kraj SERIAL PRIMARY KEY,
	nazwa varchar(20) UNIQUE NOT NULL
);

CREATE TABLE miasto (
	id_miasto SERIAL PRIMARY KEY,
	id_kraj INT NOT NULL,
	nazwa varchar(30) UNIQUE NOT NULL,
	FOREIGN KEY (id_kraj) REFERENCES kraj(id_kraj) ON UPDATE CASCADE
);

CREATE TABLE stadion (
	id_stadion SERIAL PRIMARY KEY,
	id_miasto INT NOT NULL,
	nazwa varchar(30) UNIQUE NOT NULL,
	FOREIGN KEY(id_miasto) REFERENCES miasto(id_miasto)
);

CREATE TABLE trener (
	id_trener SERIAL PRIMARY KEY,
	imie varchar(20) NOT NULL,
	nazwisko varchar(30) NOT NULL,
	data_urodzenia DATE NOT NULL
);

CREATE TABLE zespol (
	id_zespol SERIAL PRIMARY KEY,
	id_trener INT NOT NULL,
	nazwa varchar(30) UNIQUE NOT NULL,
	FOREIGN KEY (id_trener) REFERENCES trener(id_trener) ON UPDATE CASCADE
);

CREATE TABLE liga (
	id_liga SERIAL PRIMARY KEY,
	id_kraj INT NOT NULL,
	nazwa varchar(30) UNIQUE NOT NULL,
	FOREIGN KEY (id_kraj) REFERENCES kraj(id_kraj)
);

CREATE TABLE pozycja_pilkarza (
	id_pozycja_pikarza SERIAL PRIMARY KEY,
	nazwa varchar(30) NOT NULL
);

CREATE TABLE pilkarz (
	id_pilkarz SERIAL PRIMARY KEY,
	id_zespol INT NOT NULL REFERENCES zespol(id_zespol),
	id_pozycja_pilkarza INT NOT NULL REFERENCES pozycja_pilkarza(id_pozycja_pikarza),
	id_kraj INT NOT NULL REFERENCES kraj(id_kraj),
	imie varchar(20) NOT NULL,
	nazwisko varchar(30) NOT NULL,
	data_urodzenia DATE NOT NULL,
	wzrost DECIMAL(4,1),
	waga DECIMAL(4,1)
);

CREATE TABLE sezon (
	id_sezon SERIAL PRIMARY KEY,
	id_liga INT NOT NULL REFERENCES liga(id_liga),
	nazwa_sezonu varchar(30) NOT NULL,
	data_startu DATE NOT NULL,
	data_konca DATE
);

CREATE TABLE zespol_w_sezonie (
	id_zespol INT NOT NULL,
	id_sezon INT NOT NULL,
	PRIMARY KEY(id_zespol,id_sezon),
	FOREIGN KEY (id_zespol) REFERENCES zespol(id_zespol),
	FOREIGN KEY (id_sezon) REFERENCES sezon(id_sezon)
);

CREATE TABLE mecz (
	id_mecz SERIAL PRIMARY KEY,
	id_stadion INT NOT NULL REFERENCES stadion(id_stadion),
	id_sezon INT NOT NULL REFERENCES sezon(id_sezon),
	data_meczu DATE NOT NULL,
	widzowie INT CHECK (widzowie>=0)
);

CREATE TABLE sedziowie_w_meczu (
	id_sedzia INT NOT NULL,
	id_mecz INT NOT NULL,
	PRIMARY KEY(id_sedzia,id_mecz),
	FOREIGN KEY (id_sedzia) REFERENCES sedzia(id_sedzia),
	FOREIGN KEY (id_mecz) REFERENCES mecz(id_mecz)
);

CREATE TABLE zespoly_w_meczu (
	id_zespol INT NOT NULL,
	id_mecz INT NOT NULL,
	PRIMARY KEY(id_zespol,id_mecz),
	FOREIGN KEY (id_zespol) REFERENCES zespol(id_zespol),
	FOREIGN KEY (id_mecz) REFERENCES mecz(id_mecz)
);

CREATE TABLE statystyki_pilkarza (
	id_pilkarz INT NOT NULL,
	id_mecz INT NOT NULL,
	ilosc_bramek INT DEFAULT 0 NOT NULL CHECK (ilosc_bramek>=0),
	ilosc_asyst INT DEFAULT 0 NOT NULL CHECK (ilosc_asyst>=0),
	ilosc_minut INT DEFAULT 0 NOT NULL CHECK (ilosc_minut>=0 AND ilosc_minut <=120),
	PRIMARY KEY(id_pilkarz, id_mecz),
	FOREIGN KEY (id_pilkarz) REFERENCES pilkarz(id_pilkarz),
	FOREIGN KEY (id_mecz) REFERENCES mecz(id_mecz)
);

INSERT INTO typ_sedziego (nazwa) VALUES ('glowny'),('liniowy');

INSERT INTO sedzia (id_typ_sedziego,imie,nazwisko,data_urodzenia)
VALUES
(1,'Carlos','Amarilla','26-10-1970'),
(1,'Pierluigi','Collina','13-02-1960'),
(1,'Anders','Frisk','18-02-1963'),
(1,'Massimo','Busacca','6-02-1969'),
(2,'Urs','Meier','22-01-1959'),
(2,'Markus','Merk','15-03-1962'),
(2,'Graham','Poll','29-07-1963'),
(2,'Herbert','Fandel','9-03-1964');

INSERT INTO kraj (nazwa) VALUES ('Polska'),('Anglia'),('Niemcy'),('Francja'),('Włochy'),
('Słowacja'),('Czechy'),('Hiszpania'),('Holandia'),('Belgia'),('Chorwacja'),
('Serbia'),('Portugalia'),('Bośnia i Hercegowina'),('Węgry'),('Ghana'),('Brazylia'),
('Walia'),('Chile'),('Kostaryka'),('Kolumbia'),('Argentyna'),('Urugwaj');

INSERT INTO miasto (id_kraj,nazwa) VALUES (1,'Gdańsk'),(1,'Warszawa'),(1,'Poznań'),
(1,'Kraków'),(2,'Londyn'),(2,'Liverpool'),(2,'Manchester'),(8,'Madryt'),(8,'Barcelona');


INSERT INTO stadion (id_miasto,nazwa) VALUES
(1,'Energa Gdańsk'),(2,'Wojska Polskiego'),(2,'PGE Narodowy'),(3,'Inea Stadion'),
(4,'Stadion Miejski'),(5,'Stamford Bridge'),(5,'Emirates Stadium'),(6,'Anfield'),
(6,'Goodison Park'),(7,'Old Trafford'),(7,'City of Manchester'),(8,'Estadio Santiago Bernabéu'),
(8,'Estadio Vicente Calderón'),(9,'Camp Nou');

INSERT INTO trener (imie,nazwisko,data_urodzenia) VALUES
('Thomas','von Hessen','1-10-1961'),
('Stanisław', 'Czerczesow','2-09-1963'),
('Jan', 'Urban','14-05-1962'),
('Dariusz', 'Wdowczyk','25-09-1962'),('Guus','Hiddink','8-11-1946'),
('Arsène', 'Wenger','22-10-1949'), ('Jürgen', 'Klopp','16-06-1967'),
('Roberto','Martínez','13-07-1973'),('Louis','van Gaal','8-08-1951'),
('Manuel','Pellegrini','16-09-1953'),('Zinédine','Zidane','23-06-1972'),
('Diego','Simeone','28-04-1970'),('Luis','Enrique','8-05-1970'),
('José','Mourinho','26-01-1963');

INSERT INTO zespol (id_trener,nazwa) VALUES
(1,'Lechia Gdańsk'),(2,'Legia Warszawa'),(3,'Lech Poznań'),(4,'Wisła Kraków'),(5,'Chelsea Londyn'),(6,'Arsenal Londyn'),(7,'Liverpool F.C.'),
(8,'Everton F.C.'),(9,'Manchester United'),(10,'Manchester City'),(11,'Real Madryt'),(12,'Atletico Madryt'),(13,'F.C. Barcelona');

INSERT INTO liga (id_kraj,nazwa) VALUES
(1,'Ekstraklasa'),(2,'Barclays Premier League'),(3,'Bundesliga'),(8,'Primera Division');

INSERT INTO pozycja_pilkarza (nazwa) VALUES
('Bramkarz'),('Stoper'),
('Lewy Obrońca'),('Środkowy Obrońca'),('Prawy Obrońca'),
('Lewy Pomocnik'),('Środkowy Pomocnik'),('Prawy Pomocnik'),
('Wysunięty Napastnik'),('Cofnięty Napastnik'),('Skrzydłowy Napastnik');


INSERT INTO pilkarz (id_zespol,id_pozycja_pilkarza,id_kraj,imie,nazwisko,data_urodzenia,wzrost,waga) VALUES
(1,1,11,'Marko','Maric','3-01-1996',191,89),
(1,4,1,'Rafał','Janicki','5-07-1992',188,83),
(1,4,11,'Mario','Maloca','4-05-1989',190,82),
(1,3,1,'Jakub','Wawrzyniak','7-07-1983',188,84),
(1,5,1,'Paweł','Stolarski','28-01-1996',181,74),
(1,5,1,'Grzegorz','Wojtkowiak','26-01-1984',184,75),
(1,2,12,'Aleksandar','Kovačević','9-01-1992',173,70),
(1,2,1,'Daniel','Łukasik','28-04-1991',179,73),
(1,7,1,'Sebastian','Mila','10-07-1982',178,67),
(1,11,1,'Michał','Mak','14-07-1991',177,63),
(1,11,13,'Flávio','Paixão','19-09-1984',184,75),
(3,1,14,'Jasmin','Buric','18-02-1987',193,88),
(3,4,1,'Marcin','Kamiński','15-01-1992',192,87),
(3,3,15,'Tamás','Kádár','14-03-1990',188,75),
(3,5,1,'Tomasz','Kedziora','11-06-1994',183,70),
(3,2,16,'Abdul','Tetteh','25-05-1990',184,75),
(3,2,1,'Łukasz','Trałka','11-05-1984',186,77),
(3,7,1,'Karol','Linetty','2-02-1995',176,68),
(3,7,1,'Maciej','Gajos','19-03-1991',174,65),
(3,11,1,'Szymon','Pawłowski','4-11-1986',175,69),
(3,11,15,'Gergő','Lovrencsics','1-09-1988',177,72),
(3,9,1,'Dawid','Kownacki','14-03-1997',185,80),
(5,1,10,'Thibaut','Courtois','11-05-1992',199,90),
(5,4,2,'Gary','Cahill','19-12-1985',193,90),
(5,4,2,'John','Terry','7-12-1980',187,88),
(5,5,8,'César','Azpilicueta','28-08-1989',178,74),
(5,7,8,'Cesc','Fàbregas','4-05-1987',175,70),
(5,11,10,'Eden','Hazard','7-01-1991',173,72),
(5,11,17,'Willian','Borges Da Silva','9-08-1988',174,70),
(5,11,8,'Pedro','Ledesma','28-07-1987',167,64),
(5,9,8,'Diego','Costa','7-10-1988',188,80),
(5,9,8,'Radamel','Falcao','10-02-1986',177,75),
(5,10,17,'Alexandre','Pato','2-09-1989',180,77),
(6,1,7,'Petr','Cech','20-05-1982',196,95),
(6,4,4,'Laurent','Koscielny','10-09-1985',186,85),
(6,4,3,'Per','Mertesacker','29-09-1984',198,90),
(6,3,8,'Nacho','Monreal','26-02-1986',179,77),
(6,5,8,'Héctor','Bellerín','19-03-1995',178,70),
(6,2,4,'Francis','Coquelin','13-05-1991',178,72),
(6,7,18,'Aaron','Ramsey','26-12-1990',182,74),
(6,7,2,'Jack','Wilshere','1-01-1992',172,68),
(6,8,3,'Mesut','Özil','15-10-1988',183,78),
(6,11,2,'Alex','Oxlade-Chamberlain','15-08-1993',180,77),
(6,11,19,'Alexis','Sánchez','19-12-1988',169,64),
(11,1,20,'Keylor','Navas','15-12-1986',185,80),
(11,4,8,'Sergio','Ramos','30-03-1986',183,82),
(11,4,4,'Raphaël','Varane','25-04-1993',191,85),
(11,3,17,'Marcelo','da Silva Júnior','12-05-1988',174,70),
(11,5,8,'Daniel','Carvajal','11-01-1992',173,72),
(11,7,3,'Toni','Kroos','4-01-1990',182,80),
(11,2,17,'Carlos','Casemiro','23-02-1992',184,82),
(11,8,21,'James','Rodríguez','12-07-1991',180,75),
(11,11,13,'Cristiano','Ronaldo','5-02-1985',185,88),
(11,8,18,'Gareth','Bale','16-07-1989',183,87),
(11,9,4,'Karim','Benzema','19-12-1987',187,90),
(13,1,3,'Marc-André','ter Stegen','30-04-1992',187,90),
(13,4,8,'Gerard','Piqué','2-02-1987',193,95),
(13,4,22,'Javier','Mascherano','8-06-1984',174,70),
(13,3,8,'Jordi','Alba','21-03-1989',170,67),
(13,5,8,'Aleix','Vidal','21-08-1989',176,72),
(13,2,8,'Sergio','Busquets','16-07-1988',189,88),
(13,7,8,'Andrés','Iniesta','11-05-1984',171,68),
(13,7,17,'Rafael','Nascimento','12-02-1993',174,65),
(13,11,17,'Neymar','Da Silva','5-02-1992',174,67),
(13,11,22,'Lionel','Messi','24-06-1987',170,67),
(13,9,23,'Luis','Suárez','24-01-1987',182,75);


INSERT INTO sezon (id_liga,nazwa_sezonu,data_startu,data_konca) VALUES
(1,'Ekstraklasa 2014/15','18-07-2014','29-04-2015'),
(1,'Ekstraklasa 2015/16','17-07-2015','15-05-2016'),
(2,'Premier League 2015/16','08-08-2015','15-05-2016'),
(3,'Bundesliga 2015/16','14-08-2015','14-05-2016'),
(4,'Primera Division 2015/16','21-08-2015','15-05-2016');

INSERT INTO zespol_w_sezonie(id_zespol,id_sezon) VALUES
(1,1),(1,2),(2,1),(2,2),(3,1),(3,2),(4,1),(4,2),
(5,3),(6,3),(7,3),(8,3),(9,3),(10,3),(11,5),(12,5),(13,5);

INSERT INTO mecz (id_stadion,id_sezon,data_meczu) VALUES
(2,2,'29-11-2015'),
(7,3,'24-01-2016'),
(6,3,'19-09-2015'),
(12,5,'21-11-2015'),
(14,5,'2-04-2016');

INSERT INTO sedziowie_w_meczu (id_sedzia,id_mecz) VALUES
(1,1),(5,1),(6,1),
(2,2),(7,2),(8,2),
(3,3),(6,3),(7,3),
(4,4),(5,4),(6,4),
(2,5),(5,5),(8,5);

INSERT INTO zespoly_w_meczu (id_zespol,id_mecz) VALUES
(1,1),(3,1),
(6,2),(5,2),
(5,3),(6,3),
(11,4),(13,4),
(13,5),(11,5);

INSERT INTO statystyki_pilkarza (id_pilkarz,id_mecz,ilosc_bramek,ilosc_asyst,ilosc_minut) VALUES
(1,1,0,0,90),(2,1,0,0,90),(3,1,0,0,90),(4,1,0,0,90),(5,1,0,0,90),(6,1,0,0,90),(7,1,0,0,90),(8,1,0,0,90),(9,1,0,0,90),(10,1,0,0,90),(11,1,0,0,90),
(13,1,0,0,90),(14,1,0,0,90),(15,1,0,0,90),(16,1,0,0,90),(17,1,0,0,90),(18,1,0,0,90),(19,1,0,0,90),(20,1,0,0,90),(21,1,0,0,90),(22,1,1,0,90),

(23,2,0,0,90),(24,2,0,0,90),(25,2,0,0,90),(26,2,0,0,90),(27,2,0,0,90),(28,2,0,0,90),(29,2,0,0,90),(30,2,0,0,90),(31,2,1,0,90),(32,2,0,0,90),(33,2,0,0,90),
(34,2,0,0,90),(35,2,0,0,90),(36,2,0,0,90),(37,2,0,0,90),(38,2,0,0,90),(39,2,0,0,90),(40,2,0,0,90),(41,2,0,0,90),(42,2,0,0,90),(43,2,0,0,90),(44,2,0,0,90),

(23,3,0,0,90),(24,3,0,0,90),(25,3,0,0,90),(26,3,0,0,90),(27,3,0,0,90),(28,3,1,1,90),(29,3,0,0,90),(30,3,0,0,90),(31,3,0,0,90),(32,3,1,0,90),(33,3,0,0,90),
(34,3,0,0,90),(35,3,0,0,90),(36,3,0,0,90),(37,3,0,0,90),(38,3,0,0,90),(39,3,0,0,90),(40,3,0,0,90),(41,3,0,0,90),(42,3,0,0,90),(43,3,0,0,90),(44,3,0,0,90),

(45,4,0,0,90),(46,4,0,0,90),(47,4,0,0,90),(48,4,0,0,90),(49,4,0,0,90),(50,4,0,0,90),(51,4,0,0,90),(52,4,0,0,90),(53,4,0,0,90),(54,4,0,0,90),(55,4,0,0,90),
(56,4,0,0,90),(57,4,0,0,90),(58,4,0,0,90),(59,4,0,0,90),(60,4,0,0,90),(61,4,0,0,90),(62,4,1,0,90),(63,4,0,0,90),(64,4,1,0,90),(65,4,0,0,90),(66,4,2,0,90),

(45,5,0,0,90),(46,5,0,0,90),(47,5,0,0,90),(48,5,0,0,90),(49,5,0,0,90),(50,5,0,0,90),(51,5,0,0,90),(52,5,0,0,90),(53,5,1,0,90),(54,5,0,0,90),(55,5,1,0,90),
(56,5,0,0,90),(57,5,1,0,90),(58,5,0,0,90),(59,5,0,0,90),(60,5,0,0,90),(61,5,0,0,90),(62,5,0,0,90),(63,5,0,0,90),(64,5,0,0,90),(65,5,0,0,90),(66,5,0,0,90);


```


### [PostgreSQL] Widoki, funkcje, procedury
```sql
--Imię i nazwisko: Jakub Ronkiewicz
--Temat bazy danych: Rozgrywki piłkarskie

--1a) Tworzymy widok
--Widok tworzący ranking(punktacje_kanadyjska) wszystkich pilkarzy,
--uwzgledniajac rozne sezony w rankingu nie znajda sie pilkarze
--majacy 0 goli i 0 bramek.
CREATE VIEW punktacja_kanadyjska
AS
SELECT p.imie,p.nazwisko,z.nazwa AS klub,s.nazwa_sezonu AS Liga_sezon, SUM(sp.ilosc_bramek+sp.ilosc_asyst) AS punktacja_kanadyjska, SUM(sp.ilosc_bramek) AS bramki,
SUM(sp.ilosc_asyst) AS asysty
FROM pilkarz p JOIN statystyki_pilkarza sp
    ON p.id_pilkarz=sp.id_pilkarz JOIN zespol z
        ON p.id_zespol=z.id_zespol JOIN zespol_w_sezonie zs
         ON zs.id_zespol=z.id_zespol JOIN sezon s
            ON s.id_sezon=zs.id_sezon
GROUP BY p.imie,p.nazwisko,z.nazwa,s.nazwa_sezonu
HAVING SUM(sp.ilosc_bramek+sp.ilosc_asyst)>0;

--1b) Sprawdzenie, że widok działa
SELECT * FROM punktacja_kanadyjska ORDER BY punktacja_kanadyjska DESC, bramki DESC;

--2a) Tworzymy funkcję 1
--Funkcja liczace wszystkie gole zdobyte dla danego zespolu przez caly czas
CREATE FUNCTION gole_zespol(zespol varchar(20),OUT ile INT)
RETURNS INT AS $$
BEGIN
  SELECT INTO ile SUM(bramki) FROM punktacja_kanadyjska WHERE zespol=klub GROUP BY klub;
END;
$$ LANGUAGE PLPGSQL;

--2b) Sprawdzenie, że funkcja 1 działa
SELECT gole_zespol('F.C. Barcelona');

--3a) Tworzymy funkcję 2
--Zwraca ilosc wystąpien sedziego
CREATE FUNCTION wystepy_sedziego(p_imie varchar(20), p_nazwisko varchar(30), OUT ilosc INT)
RETURNS INT AS $$
BEGIN
SELECT INTO ilosc COUNT(*) FROM sedziowie_w_meczu WHERE id_sedzia IN (SELECT id_sedzia FROM sedzia WHERE p_imie=imie AND p_nazwisko=nazwisko);
END;
$$ LANGUAGE PLPGSQL;

--3b) Sprawdzenie, że funkcja 2 działa
SELECT wystepy_sedziego('Pierluigi','Collina');

--4a) Tworzymy procedurę 1
--Procedura umozliwia dodanie pilkarza,
--trzeba bezpośrednio podawać np.kraj wpisujemy Brazylia,
--a nie nr 17
CREATE FUNCTION dodaj_pilkarza(p_zespol varchar(30), p_pozycja varchar(30), p_kraj varchar(30), p_imie varchar(20),p_nazwisko varchar(30), p_data_ur DATE, p_wzrost DECIMAL(4,1), p_waga DECIMAL (4,1))
RETURNS VOID AS $$
BEGIN
INSERT INTO pilkarz (id_zespol,id_pozycja_pilkarza,id_kraj,imie,nazwisko,data_urodzenia,wzrost,waga) VALUES
((SELECT id_zespol FROM zespol WHERE p_zespol=nazwa),(SELECT id_pozycja_pikarza FROM pozycja_pilkarza WHERE p_pozycja=nazwa),
(SELECT id_kraj FROM kraj WHERE p_kraj=nazwa),p_imie,p_nazwisko,p_data_ur,p_wzrost,p_waga);
END;
$$ LANGUAGE PLPGSQL;

--4b) Sprawdzenie, że procedura 1 działa
SELECT * FROM dodaj_pilkarza('F.C. Barcelona','Skrzydłowy Napastnik','Brazylia','Ronaldinho','Gaucho','21-03-1980','181','80');

--5a) Tworzymy procedurę 2
--Procedura wyświetla wszystkich pilkarzy z danego kraju razem z ich klubami
CREATE FUNCTION kraj_pilkarze(p_kraj varchar(30)) RETURNS VOID AS $$
DECLARE
  _r RECORD;
BEGIN
  FOR _r IN
    SELECT imie, nazwisko, id_zespol, id_kraj, (SELECT nazwa FROM zespol WHERE id_zespol = p.id_zespol) AS nazwa
    FROM pilkarz p WHERE id_kraj = (SELECT id_kraj FROM kraj WHERE nazwa = $1)
  LOOP
    RAISE NOTICE '% %, %', _r.imie, _r.nazwisko, _r.nazwa;
  END LOOP;
END;
$$ LANGUAGE PLPGSQL;

--5b) Sprawdzenie, że procedura 2 działa
SELECT * FROM kraj_pilkarze('Polska');

--6a) Tworzymy wyzwalacz 1
--Ograniczenie do trzech sedziow w jednym meczu
CREATE OR REPLACE FUNCTION ogr_mecz_sedzia() RETURNS TRIGGER AS $$
BEGIN
	IF EXISTS(
	    SELECT 1
	    FROM sedziowie_w_meczu
	    WHERE id_mecz = NEW.id_mecz
	    GROUP BY sedziowie_w_meczu.id_mecz
	    HAVING COUNT(*) > 3
	) THEN
	RAISE 'Meczu nie moze sedziowac wiecej niz 3 sedziów';
	ELSE
	RETURN NEW;
	END IF;
END;
$$ LANGUAGE PLPGSQL;

CREATE TRIGGER trig_1
	AFTER INSERT OR UPDATE
	ON sedziowie_w_meczu
	FOR EACH ROW
	EXECUTE PROCEDURE ogr_mecz_sedzia();

--6b) Sprawdzenie, że wyzwalacz 1 działa
INSERT INTO sedziowie_w_meczu VALUES (4,1);
UPDATE sedziowie_w_meczu SET id_mecz=1 WHERE id_sedzia=2 AND id_mecz=2;

--7a) Tworzymy wyzwalacz 2
--Ograniczenie do dwoch zespolow w jednym meczu
CREATE OR REPLACE FUNCTION ogr_mecz_zesp() RETURNS TRIGGER AS $$
BEGIN
	IF EXISTS(
	    SELECT 1
	    FROM zespoly_w_meczu
	    WHERE id_mecz=NEW.id_mecz
	    GROUP BY zespoly_w_meczu.id_mecz
	    HAVING COUNT(*) > 2
	) THEN
	RAISE 'W meczu nie może brać udziału więcej niż dwa zespoly';
	ELSE
	RETURN NEW;
	END IF;
END;
$$ LANGUAGE PLPGSQL;

CREATE TRIGGER trig_2
	AFTER INSERT OR UPDATE
	ON zespoly_w_meczu
	FOR EACH ROW
	EXECUTE PROCEDURE ogr_mecz_zesp();

--7b) Sprawdzenie, że wyzwalacz 2 działa
INSERT INTO zespoly_w_meczu VALUES (4,1);

--8a) Tworzymy wyzwalacz 3
--W meczu nie moga brac udzialu zespoly z innych sezonow
CREATE OR REPLACE FUNCTION ogr_sezon_mecz() RETURNS TRIGGER AS $$
DECLARE
	p_id_mecz INT;
	p_id_zespol INT;
	sezon_dod_zespolu INT;
	sezon_mecz INT;
BEGIN
	SELECT id_zespol, id_mecz INTO p_id_zespol,p_id_mecz FROM zespoly_w_meczu WHERE (id_mecz=NEW.id_mecz AND id_zespol=NEW.id_zespol);
	SELECT id_sezon INTO sezon_mecz FROM mecz WHERE p_id_mecz=id_mecz;
	SELECT id_sezon INTO sezon_dod_zespolu FROM zespol_w_sezonie WHERE p_id_zespol=id_zespol;
	IF (sezon_mecz != sezon_dod_zespolu) THEN
	RAISE 'Zespol nie gra w tej lidze i tym sezonie, nie mozna dodac!';
	ELSE
	RETURN NEW;
	END IF;
END;
$$ LANGUAGE PLPGSQL;

CREATE TRIGGER trig_3
    AFTER INSERT OR UPDATE
    ON zespoly_w_meczu
    FOR EACH ROW
    EXECUTE PROCEDURE ogr_sezon_mecz();

--8b) Sprawdzenie, że wyzwalacz 3 działa
INSERT INTO mecz (id_mecz,id_stadion,id_sezon,data_meczu) VALUES
(6,3,3,'10-10-2015');
INSERT INTO zespoly_w_meczu (id_zespol,id_mecz) VALUES (5,6);
INSERT INTO zespoly_w_meczu (id_zespol,id_mecz) VALUES (3,6);

--9a) Tworzymy wyzwalacz 4
--Wyzwalacz blokuje zmiane zespolu przez pilkarzy, gdy nie ma okna transferowego
CREATE OR REPLACE FUNCTION ogr_upd_pikarz() RETURNS trigger AS $$
BEGIN
	NEW.id_zespol = OLD.id_zespol;
	RAISE NOTICE 'Nie mozna zmieniac zespolu, zmiana nie zostala wprowadzona';
	RETURN NEW;
END;
$$ LANGUAGE PLPGSQL;

--9b) Sprawdzenie, że wyzwalacz 4 działa
CREATE TRIGGER trig_4 BEFORE UPDATE ON pilkarz
FOR EACH ROW 
EXECUTE PROCEDURE ogr_upd_pikarz();

--10) Tworzymy tabelę przestawną
--Widok pomocniczy
CREATE VIEW pivot_t
AS
SELECT date_part('year',m.data_meczu) AS rok , m.id_mecz,s.nazwa 
FROM mecz m JOIN stadion s ON m.id_stadion=s.id_stadion;

--Tabela przestna bez użycia crosstab'a
SELECT nazwa,
SUM(CASE WHEN rok='2015' THEN 1 ELSE 0 END) AS rok2015,
SUM(CASE WHEN rok='2016' THEN 1 ELSE 0 END) AS rok2016
FROM pivot_t
GROUP BY nazwa
ORDER BY nazwa;
```
