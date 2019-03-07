<?php
if (Yii::$app->user->isGuest) {
    exit('Gość nie ma zapisywanych statystyk');
}
$this -> title = "Mój profil";
?>
<div class="row">
    <h1>Panel użytkownika</h1>

</div>