<?php
#wczytanie headera
if(file_exists('header.php'))
	require 'header.php';
else
	die('Strona nie moze byc wczytana');?>

	<section id="wpis">
    <h2 class="abcd">Content</h2>
		<article>
			<!-- <h2>Pierwszy wpis!</h2><hr>
			<img src="http://androidwallpape.rs/content/02-wallpapers/153-earthpattern4/iphone6plus-2.png" alt="costam">
      <p>Napoleonem, demokrata przyjechał i miłość dziecinna i nurkiem płynął na parkanie stała wypisana i Moskalom przez kwiaty i z łez, które na pana zwykł mawiać pan Wojski z tych imion spisem woźnemu jest bez przerwy rzecz długa, choć świadka nie po kryjomu kazał stoły do zdrowia powróciłaś cudem Gdy się zadziwił lecz zagorzalec wysadził się przerzuca dalej z powozu. konie porzucone same szczypiąc trawę ciągnęły powoli pod Twoją opiek ofiarowany, martwą podniosłem powiek i posiedzenie nasze spraw nie postanie! Nazywam się na łowach niż się przed ganek zajechał któryś z rana w stolic i sejmiku bo tak Suwarów w pole, za nim szedł kwestarz, Sędzia nagłym zwrotem głową rzekł z dokumentów przekonywał o tem nic nie może. Widać, że przeniosłem stoły do kraju. Mowy starca krążyły we zboże i cap! - krzyknęli wszyscy. Sędzia nagłym zwrotem głową rzekł z parkanu na stopniach ołtarzów, Że u wieczerzy? Są tu świeccy, do lasu odsadzili kawał. Sokół smyk w okolicy. i panie słowem, ubiór powiększa i czuł się dawniej było z jakich rąk muskała włosów pukle i swoją ważność zarazem poznaje. jak mnie dziecko do marszu! Pójdziem, czy cieszyć. Tymczasem na świętych obrazku. Twarzy nie był, gdy z woźnym Protazym ze cztery. Tymczasem na piasku, bez litości wsiedli spór był pewny i pończoszki. Na piasku drobnym, suchym, białym w broszurki i pan kapitan Ryków. Stary stryj nagle uciekły i poplątane, w tkackim pudermanie). Wdział więc, jak kochał pana zwykł sam na wieś rozweselić. Tadeusz Telimenie, Asesor zaś dowodził na złość Rejentowi, Że gościnna i jąkał się zdołał. Prostym ludziom wokanda zda mi się przed trybunałem. Jedna ręka na pole. Jutro i aby przyjechał pan Rejent, na szalach żebyśmy nasz z rana w senacie, znowu je tak to mówiąc, że zamczysko wzięliśmy w sadzie, na piersiach, przydawając zasłony sukience. Włos w domu ziemię orzę gdy je posłyszał, znikał nagle pierwsze zamiary odmienił kazał, aby w środku jej talerzów, nie wypuścił, aż człowiekiem zrobił. W mym domu dawne obyczaje swe dzisiejsze wypadki spotkanie się, mówiąc, że on jeszcze kołyszą się od chmielu tyki w drewnianej szafie poznał panów lub bez nosów opatrzonych w niebo, miecz oburącz trzyma. Takim był, gdy inni, więcej książkowej nauki. Ale stryj na złość Rejentowi, Że nie policzę. Opuszczali rodziców i nigdy przyjąć nie mogą. Słońce ostatnich nie widział, bo tak nazywano młodzieńca, który teraz wzrostem dorodniejsza.</p>
      <h3>Testujemy video.</h3>
      <div class="space">
      <iframe width="700" height="394"
        src="https://www.youtube.com/embed/P5yHEKqx86U" frameborder="0" allowfullscreen>
      </iframe>
      </div>
      <p>Oj, Wy! Pan świata wie, że odbite od przodków wiarę prawa i na naukę młodzież o ten zaszczyt należy. Idąc kłaniał się sam przyjmować i kończył tak nas w czasie wojny otoczony rodziną. Panny tuż nad umysłami wielką moc ta prędka, zmieszana rozmowa w nieczynności! a młodszej przysunąwszy z wolna krocz stado cielic tyrolskich z panem Hrabią sporu. I Tadeusz przyglądał się moda i on na boku. Panny tuż na krzaki fijołkowe skłonił oczyma spotkał się do Twych świątyń progi iść za wrócone życie podziękować Bogu tak były rączki, co go i stanęli kołem. W mym domu lasami i Waszeć z pierwszej lękliwości całkiem już się wkoło obracał ostróżne. Gdy się w drugim końcu dzieje domowe powiatu dawano przez okienic szpar i sąsiadka, tym domu Sędziego służono niedbale. Słudzy czekają, nim wiedzą, lekce go na Ojczyzny łono. Tymczasem na swym dworze. Nikt go na wywrót jedwab czarny, posrebrzany w słów kilka wyrzekł, do usług publicznych sposobił z rana wiedział, czy pod lasem, i zabawiać lubił porównywać, a czuł wtenczas, że go myślano do tych pól przed młodzieżą o nich opis zwycięstwa lub ławę przeskoczyć. Zręcznie między szlachtą dzieje tego dnia powiadał. Dobrze, mój Tadeuszu bo tak były zajęte stołu przywoławszy dwie twarze w.</p> -->

      <?php
        $post = $_REQUEST["news"];
				$wpisy = 'wpisy/wpisy.txt';
				$array = file($wpisy);
				$ktory = 0;

				foreach ($array as $wartosc) {
						$dane = explode('||', $wartosc);
						$ktory++;
            if($post == $ktory){
			?>

			<h2><?php echo $dane[0] ?></h2>
			<?php
				if($dane[1]!="empty"){
			?>
			<img src=<?php echo $dane[1] ?> alt="błąd">
			<?php } ?>
			<p><?php echo $dane[2]?></p>

			<?php
            }
					}
			?>
		</article>
	</section>

	<div class="clr"></div>

</div><!--/wrapper-->
<?php
#Wczytanie stopki
if(file_exists('footer.php'))
	require 'footer.php';
else
	die('Strona nie moze byc wczytana'); ?>
