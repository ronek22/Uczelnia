<?php
#wczytanie headera
if(file_exists('header.php'))
	require 'header.php';
else
	die('Strona nie moze byc wczytana');?>

<!-- CONTENT -->
	<section id="content">
    <h2 class="abcd">Content</h2>
		<article>
			<?php
				$wpisy = 'wpisy/wpisy.txt';
				$array = file($wpisy);
				$ile = count($array);
				$ktory = 0;

				if($ile == 0){
					echo '<h2>Brak Newsów!</h2>';
				} else {
					foreach ($array as $wartosc) {
						$dane = explode('||', $wartosc);
						$ktory++;
						?>

			<h2><?php echo $dane[0] ?></h2>
			<?php
				if($dane[1]!="empty"){
			?>
			<img src=<?php echo $dane[1] ?> alt="błąd">
			<?php } ?>

			<?php if(strlen($dane[2])>200){
				$dane[2] = substr($dane[2],0,200).'...';
			?>
			<p><?php echo $dane[2]?></p>
			<a href=<?php echo 'wpis.php?news='.$ktory; ?> >czytaj wiecej...</a>
			<?php } else {?>
			<p><?php echo $dane[2]?></p><?php } ?>
			<?php
					}
				}
			?>


			<!-- <h2>Pierwszy wpis!</h2><hr>
			<img src="http://androidwallpape.rs/content/02-wallpapers/153-earthpattern4/iphone6plus-2.png" alt="costam">
			<p>Lorem ipsum dolor sit amet diam vel quam. Proin sed felis. Fusce ut lacus. Vivamus nibh. Ut sodales pede. Lorem ipsum primis in nunc. Maecenas eget elit at ipsum. Fusce ullamcorper ut, ultricies accumsan. Proin dapibus, ultricies urna augue, id sapien sodales lectus dapibus risus dictum accumsan faucibus. Sed ultricies porta. Sed scelerisque odio leo, pretium justo. Quisque neque ante ipsum dolor fermentum pede, at turpis. Nullam laoreet, purus eu nibh. Aliquam erat eget lectus. Nam scelerisque urna ut nibh. Morbi urna et purus sit amet augue. Pellentesque at lectus orci, sollicitudin fermentum, dui aliquam purus. Nulla facilisi. Nulla posuere.</p>
      <a href="wpis.php">czytaj wiecej...</a>

			<h2>Drugi wpis...</h2><hr>
			<img src="http://androidwallpape.rs/content/02-wallpapers/20-cold-evening-II/Cold_evening_II_1920_by_Hombre-cz.jpg" alt="blabla">
			<p>Lorem ipsum dolor sit amet dui dui, non luctus eu, faucibus lorem. Sed fringilla sem laoreet hendrerit nonummy. Phasellus adipiscing. Duis luctus elit, ut odio eget dolor lacus, ullamcorper quam. Nulla facilisi. Morbi tellus non erat eget nibh condimentum nec, ligula. Aliquam erat id lectus. In hac habitasse platea dictumst. Nulla iaculis nisl. Nulla venenatis. Morbi quis wisi. Integer lacinia ut, blandit ipsum, vel laoreet ante felis, dignissim vitae, vehicula elit at ipsum at porttitor vitae, pellentesque quis.</p>
			<a href="#">-starsze wpisy</a> -->
		</article>
	</section>

	<aside id="sidebar">
		<div id="logout">
			<a href="login.php">Zaloguj się!</a>
		</div>
	</aside>

	<div class="clr"></div>
</div><!--/wrapper-->
<!-- /CONTENT -->


<?php
#Wczytanie stopki
if(file_exists('footer.php'))
	require 'footer.php';
else
	die('Strona nie moze byc wczytana'); ?>
