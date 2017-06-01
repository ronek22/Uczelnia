<?php session_start(); /* Rozpoczęcie sesji */

	/* Sprawdzenie czy wysłano formularz logowanie */
	if(isset($_POST['Submit'])){
		/* Tablica z użytkownikami i hasłami */
		$logins = array('admin' => 'pass1','username1' => 'password1');

		/* Wprowadzenie danych z formularza do zmiennych */
		$Username = isset($_POST['Username']) ? $_POST['Username'] : '';
		$Password = isset($_POST['Password']) ? $_POST['Password'] : '';

		/* Sprawdzenie czy wprowadzone dane istnieja w tablicy */
		if (isset($logins[$Username]) && $logins[$Username] == $Password){
			/* Powodzenie: Ustaw zmienna sesji i przekieruj do sekretnej strony  */
			$_SESSION['UserData']['Username']=$logins[$Username];
			header("location:dodaj.php");
			exit;
		} else {
			/*Nieudana proba: Wyświetl błąd */
			$msg="<span style='color:red'>Niepoprawne Dane!</span>";
		}
	}
?>


<!DOCTYPE html>
<html lang="pl">
<head>
  <meta charset="utf-8">
  <link rel="stylesheet" href="./css/login.css" />
  <title>Logowanie - Jakub Ronkiewicz</title>
</head>

<body>
  <div class="login-page">
    <div class="form">
      <form action="" method="post" class="login-form">
        <input name="Username" type="text" placeholder="login" />
        <input name="Password" type="password" placeholder="hasło" />
        <input name="Submit" type="submit" value="Zaloguj Się" class="button1">
        <?php if(isset($msg)){
          echo '<p class="message">'.$msg.'</p>';
        } else {
					echo '<p class="message">Login: admin Hasło: pass1</p>';
        }
        ?>

      </form>
    </div>
  </div>
</body>

</html>
