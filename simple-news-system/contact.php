<?php
#wczytanie headera
if(file_exists('header.php'))
	require 'header.php';
else
	die('Strona nie moze byc wczytana');?>

	<section id="content">
    <h2 class="abcd">Content</h2>
		<article>
			<h2>Kontakt</h2><hr>
			<img src="images/contact.jpg" alt="costam">

      <form action="mail.php" class="form_des"  method="post">
        <h3>Masz pytania? Pisz śmiało.</h3>
        <h4>Wypełnij poniższy formularz</h4>
        <fieldset>
          <input name="name" placeholder="Imie i Nazwisko" type="text" tabindex="1" required autofocus>
        </fieldset>
        <fieldset>
          <input name="email" placeholder="Twój adres e-mail" type="email" tabindex="2" required>
        </fieldset>
        <fieldset>
          <input name="phoneNumber" placeholder="Twój numer telefonu" type="tel" tabindex="3">
        </fieldset>
        <fieldset>
          <textarea name="message" placeholder="Tu napisz swoją wiadomość..." tabindex="5" required></textarea>
        </fieldset>
        <fieldset>
          <button name="submit" type="submit" id="contact-submit" data-submit="...Sending">Wyślij</button>
        </fieldset>
  </form>
		</article>
	</section>

	<aside id="sidebar">

	</aside>

	<div class="clr"></div>
</div><!--/wrapper-->

<?php
#Wczytanie stopki
if(file_exists('footer.php'))
  require 'footer.php';
else
  die('Strona nie moze byc wczytana'); ?>
