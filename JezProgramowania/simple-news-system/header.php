<!DOCTYPE HTML>
<html lang="pl">
<head>
 <meta charset="utf-8" >
  <title>Ronek - Coding</title>
  <link rel="stylesheet" type="text/css" href="css/style.css" media="screen">
<!--[if lt IE 9]>
<script src="js/html5shiv.js"></script>
<![endif]-->
<?php
$refresh = <<<MY_MARKER
<script type="text/javascript">
  var timeout = setTimeout("location.reload(true);",300000);
  function resetTimeout() {
    clearTimeout(timeout);
    timeout = setTimeout("location.reload(true);",300000);
}
</script>
MY_MARKER;

if(isset($_SESSION['UserData']['Username'])){
  echo $refresh;
}
?>
<script>
var seconds_left = 300;
var interval = setInterval(function() {
    document.getElementById('timer_div').innerHTML = --seconds_left;

    if (seconds_left <= 0)
    {
       clearInterval(interval);
    }
}, 1000);
</script>
</head>
<body>

<div class="wrapper">

	<header>

		<div id="social">
			<a href="http://www.facebook.com/ronek22">
				<img src="images/Facebook.png" alt="fb"></a>
			<a href="https://plus.google.com/114778939422125745123/posts">
				<img src="images/Google+.png" alt="g+"></a>
			<a href="https://twitter.com/KubaRonkiewicz">
				<img src="images/Twitter.png" alt="twit"></a>
		</div>
		<hr>
    <h1>
		<img src="images/Logo.png" id="logo" alt="logo2">
    <span class="abcd">Logo</span>
		</h1><!--/logo-->
    <?php
      $activePage = basename($_SERVER['PHP_SELF'], ".php");
    ?>
		<nav id="mainmenu">
			<ul>
				<li><a class="<?= ($activePage == 'index') ? 'active':''; ?>" href="index.php">BLOG</a></li>
				<li><a class="<?= ($activePage == 'contact') ? 'active':''; ?>" href="contact.php">KONTAKT</a></li>
			</ul>
		</nav><!--/mainmenu-->
		<div class="clr"></div>
	</header>
