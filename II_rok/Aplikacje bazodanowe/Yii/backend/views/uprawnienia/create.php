<?php

use yii\helpers\Html;


/* @var $this yii\web\View */
/* @var $model backend\models\Uprawnienia */

$this->title = 'Utwórz Uprawnienia';
$this->params['breadcrumbs'][] = ['label' => 'Uprawnienia', 'url' => ['index']];
$this->params['breadcrumbs'][] = $this->title;
?>
<div class="uprawnienia-create">

    <h1><?= Html::encode($this->title) ?></h1>

    <?= $this->render('_form', [
        'model' => $model,
        'podkategoria' => $podkategoria,
        'konta' => $konta,
    ]) ?>

</div>
