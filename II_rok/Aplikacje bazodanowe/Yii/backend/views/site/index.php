<?php

/* @var $this yii\web\View */

use yii\helpers\Html;
$this->title = 'Fiszki';
?>
<div class="site-index">

    <div class="jumbotron">
        <h1>Gratulacje!</h1>

        <p class="lead">Udało ci się zalogować do panelu administratora.</p>

        <p>Poniżej znajdują się linki do CRUD'ów.</p>
    </div>

    <div class="body-content">

        <div class="row">
            <div class="col-lg-3">
                <h2><?= HTML::a('Konto', '?r=konto'); ?></h2>

            </div>
            <div class="col-lg-3">
                <h2><?= HTML::a('Kategoria', '?r=kategoria'); ?></h2>
            </div>
            <div class="col-lg-3">
                <h2><?= HTML::a('Jezyk', '?r=jezyk'); ?></h2>
            </div>
            <div class="col-lg-3">
                <h2><?= HTML::a('Zestaw', '?r=zestaw'); ?></h2>
            </div>
        </div>
        <div class="row">
            <div class="col-lg-3">
                <h2><?= HTML::a('Rola', '?r=rola'); ?></h2>
            </div>
            <div class="col-lg-3">
                <h2><?= HTML::a('Podkategoria', '?r=podkategoria'); ?></h2>
            </div>
            <div class="col-lg-3">
                <h2><?= HTML::a('Uprawnienia', '?r=uprawnienia'); ?></h2>
            </div>
            <div class="col-lg-3">
                <h2><?= HTML::a('Wynik', '?r=wynik'); ?></h2>
            </div>
        </div>

    </div>
</div>
