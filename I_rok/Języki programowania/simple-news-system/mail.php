<?php
$name = $_POST['name'];
$email = $_POST['email'];
$phone = $_POST['phoneNumber'];
$msg = $_POST['message'];

$formcontent = "Od: $name \nTelefon: $phone \n$msg";
$recipient = "jronek3010@gmail.com";
$subject = "Contact Form";
$mailheader = "From: $email \r\n";
mail($recipient,$subject,$formcontent,$mailheader) or die("Błąd");
echo "Dziekuje";
?>
