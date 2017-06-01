<?php session_start(); /* Starts the session */

if(!isset($_SESSION['UserData']['Username'])){
	header("location:login.php");
	exit;
}

if (isset($_SESSION['LAST_ACTIVITY']) && (time() - $_SESSION['LAST_ACTIVITY'] >= 300)) {
    // last request was more than 30 minutes ago
    header("location:index.php");
}
$_SESSION['LAST_ACTIVITY'] = time(); // update last activity time stamp
?>

<?php
#wczytanie headera
if(file_exists('header.php'))
	require 'header.php';
else
	die('Strona nie moze byc wczytana');
?>

  <!-- CONTENT -->
  <section id="content">
    <h2 class="abcd">Content</h2>
    <article>
      <h2>Dodaj Newsa</h2>
      <hr>
      <img src="images/contact.jpg" alt="costam">

      <form class="form_des" action="" method="post" enctype="multipart/form-data">
        <h3>Aby dodać news wypełnij wszystkie rubryki</h3>
        <fieldset>
          <input placeholder="Tytuł" type="text" name="tytul" required>
        </fieldset>
        <fieldset>
          <input type="file" name="image" accept="image/gif, image/jpeg, image/png">
        </fieldset>
        <fieldset>
          <textarea placeholder="Tu napisz swoją wiadomość..." name="tresc" required></textarea>
        </fieldset>
        <fieldset>
          <button name="submit" type="submit" id="contact-submit">Wyślij</button>
        </fieldset>
      </form>

			<?php
			$bool_img = 0;


			if(isset($_FILES['image'])){
				//Sprawdzenie czy dodawac zdjecie w htmlu
				if(file_exists($_FILES['image']['tmp_name']) || is_uploaded_file($_FILES['image']['tmp_name'])) {
						$bool_img = 1;
				}

				$file_name = $_FILES['image']['name'];
				$file_tmp = $_FILES['image']['tmp_name'];
				$img_path = "images/".$file_name;
				move_uploaded_file($file_tmp,$img_path);
			}



			if(isset($_POST['tytul']) && isset($_POST['tresc'])){
				$tytul = $_POST['tytul'];
				$tresc = $_POST['tresc'];

				if (!empty($tytul) && !empty($tresc)) {
					$plik = 'wpisy/wpisy.txt';
					$tresc = str_replace("\n", '<br/>', $tresc);

					if($bool_img==1){
						$zapis = $tytul .'||'. $img_path .'||'. $tresc;
					}else{
						$zapis = $tytul .'||empty||'. $tresc;
					}

					$noweDane = $zapis. "\n"; //tworzenie nowych danych
					// Wczytanie starych danych

					if(filesize($plik)>0){
						$fp = fopen($plik, "r"); // otwarcie pliku do odczytu
						$stareDane = fread($fp, filesize($plik)); //odczytanie danych
						fclose($fp); //zamkniecie pliku
						$noweDane .= $stareDane;
					}

					$fp = fopen($plik,"w"); //otwarcie do zapisu
					if(fputs($fp, $noweDane)) {
						echo '<p>News został poprawnie dodany</p>';
					} else {
						echo '<p>Wystąpił błąd!</p>';
					}
					fclose($fp);
				}
			}

			?>
    </article>
  </section>

  <aside id="sidebar">
    <div id="logout">
      <a href="logout.php">Wyloguj się!</a>
      <div id="timer_div">
      </div>
    </div>
  </aside>

  <div class="clr"></div>
  </div>
  <!--/wrapper-->
  <!-- /CONTENT -->



  <?php
  #Wczytanie stopki
  if(file_exists('footer.php'))
  	require 'footer.php';
  else
  	die('Strona nie moze byc wczytana'); ?>
