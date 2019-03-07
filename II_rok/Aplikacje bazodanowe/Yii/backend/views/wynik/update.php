<?php

use yii\helpers\Html;

/* @var $this yii\web\View */
/* @var $model backend\models\Wynik */

$this->title = 'Modyfikuj Wynik: ' . $model->id;
$this->params['breadcrumbs'][] = ['label' => 'Wynik', 'url' => ['index']];
$this->params['breadcrumbs'][] = ['label' => $model->id, 'url' => ['view', 'id' => $model->id]];
$this->params['breadcrumbs'][] = 'Zmień';
?>
<div class="wynik-update">

    <h1><?= Html::encode($this->title) ?></h1>

    <?= $this->render('_form', [
        'model' => $model,
        'konta' => $konta,
        'zestaw' => $zestaw,
    ]) ?>

</div>
