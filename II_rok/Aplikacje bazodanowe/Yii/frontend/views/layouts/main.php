<?php

/* @var $this \yii\web\View */
/* @var $content string */

use yii\helpers\Html;
use yii\bootstrap\Nav;
use yii\bootstrap\NavBar;
use yii\widgets\Breadcrumbs;
use frontend\assets\AppAsset;
use common\widgets\Alert;

AppAsset::register($this);
?>
<?php $this->beginPage() ?>
<!DOCTYPE html>
<html lang="<?= Yii::$app->language ?>">
<head>
    <meta charset="<?= Yii::$app->charset ?>">
    <meta name="viewport" content="width=device-width, initial-scale=1">
    <link rel="stylesheet" type="text/css" href="//fonts.googleapis.com/css?family=Lato" />
    <?= Html::csrfMetaTags() ?>
    <title><?= Html::encode($this->title) ?></title>
<style>

    @import url('https://fonts.googleapis.com/css?family=Lato');
    @font-face {
        font-family: 'Roboto';
        font-style: normal;
        font-weight: 400;
        src: local('Roboto Regular'),
        local('Roboto-Regular'),
        url(http://themes.googleusercontent.com/static/fonts/roboto/v11/2UX7WLTfW3W8TclTUvlFyQ.woff)
        format('woff');
    }
    @font-face {
        font-family: 'Roboto';
        font-style: normal;
        font-weight: 700;
        src: local('Roboto Bold'),
        local('Roboto-Bold'),
        url(http://themes.googleusercontent.com/static/fonts/roboto/v11/d-6IYplOFocCacKzxwXSOD8E0i7KZn-EPnyo3HZu7kw.woff)
        format('woff');
    }
    @font-face {
        font-family: 'Roboto';
        font-style: italic;
        font-weight: 400;
        src: local('Roboto Italic'),
        local('Roboto-Italic'),
        url(http://themes.googleusercontent.com/static/fonts/roboto/v11/1pO9eUAp8pSF8VnRTP3xnvesZW2xOQ-xsNqO47m55DA.woff)
        format('woff');
    }

    body {
        font-family: 'Roboto', sans-serif;
        font-size: 13px;
    }

    h1 {
        font-family: 'Lato';
        font-size: 24px;
        font-style: normal;
        font-variant: normal;
        font-weight: bold;
        line-height: 36px;
    }

    h2{
        font-family: 'Lato';
        font-size: 21px;
        font-style: normal;
        font-variant: normal;
        font-weight: 800;
        line-height: 22px;
    }

    h3 {
        font-family: 'Lato';
        font-size: 18px;
        font-style: normal;
        font-variant: normal;
        font-weight: 600;
        line-height: 15.4px;
    }

    @keyframes fadein {
        from {
            opacity: 0;
        }
        to {
            opacity: 1;
        }
    }


    details {
        text-align: center !important;
        font-size:15px;
        font-weight: 600;
        border-radius: 1px;
        color: #f6f6f6;
        /*box-shadow: 0 3px 6px rgba(150,150,150,0.16), 0 3px 6px rgba(150,150,150,0.23);*/
        margin: 1em 0;

        background: #323268;

        -moz-box-shadow:    inset  0  8px 8px -8px #696868,
        inset  0 -8px 8px -8px #696868;
        -webkit-box-shadow: inset  0  8px 8px -8px #696868,
        inset  0 -8px 8px -8px #696868;
        box-shadow:        inset  0  8px 8px -8px #696868,
        inset  0 -8px 8px -8px #696868;

    }

    details[open] {
        animation: fadein 1000ms ease-out;
    }

    details[onclose]{
        animation: fadein 1000ms ease-out;
    }

    summary {
        box-shadow: 0 3px 6px rgba(100,100,100,0.16), 0 3px 6px rgba(100,100,100,0.23);

        background: #f7fffa;
        color: #271c3a;
        border-radius: 1px;
        margin-bottom: 10px;
        padding: 10px 10px;
        outline: none;
    }

    details p a{
        font-weight:400;
        line-height: 1px;
        color: #eeeeee;
        font-size:13px;
    }

    details a:hover {
        color:#f6f6f6;
    }

    details summary::-webkit-details-marker { display:none; }

    hr {

        border: 0;
        height: 0;
        border-top: 1px solid rgba(0, 0, 0, 0.1);
        border-bottom: 1px solid rgba(255, 255, 255, 0.3);

    }

</style>
    <?php $this->head() ?>
</head>
<body>
<?php $this->beginBody() ?>

<div class="wrap">
    <?php
    NavBar::begin([
        'brandLabel' => 'Fiszki',
        'brandUrl' => Yii::$app->homeUrl,
        'options' => [
            'class' => 'navbar-inverse navbar-fixed-top',
        ],
    ]);
    $menuItems = [
        ['label' => 'Strona główna', 'url' => ['/site/index']],
//        ['label' => 'O stronie', 'url' => ['/site/about']],
        //['label' => 'Kontakt', 'url' => ['/site/contact']],
    ];
    if (Yii::$app->user->isGuest) {
        $menuItems[] = ['label' => 'Zarejestruj się', 'url' => ['/site/signup']];
        $menuItems[] = ['label' => 'Zaloguj się', 'url' => ['/site/login']];
    } else {
        $menuItems[] = ['label' => 'Statystyki', 'url' => ['/site/user']];
        $menuItems[] = '<li>'
            . Html::beginForm(['/site/logout'], 'post')
            . Html::submitButton(
                'Wyloguj (' . Yii::$app->user->identity->username . ')',
                ['class' => 'btn btn-link logout']
            )
            . Html::endForm()
            . '</li>';
    }
    echo Nav::widget([
        'options' => ['class' => 'navbar-nav navbar-right'],
        'items' => $menuItems,
    ]);
    NavBar::end();
    ?>


    <div class="container<?=($this->context->id=='site' && $this->context->action->id=='index')?'-fluid':'';?>">
    <?= Breadcrumbs::widget([
            'links' => isset($this->params['breadcrumbs']) ? $this->params['breadcrumbs'] : [],
        ]) ?>
        <?= Alert::widget() ?>
        <?= $content ?>
    </div>
</div>

<footer class="footer">
    <div class="container">
        <p class="pull-left">&copy; Fiszki <?= date('Y') ?></p>

        <p class="pull-right"><?= Yii::powered() ?></p>
    </div>
</footer>

<?php $this->endBody() ?>
</body>
</html>
<?php $this->endPage() ?>
