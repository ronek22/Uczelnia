<?php

use yii\helpers\Html;

/* @var $this yii\web\View */
/* @var $model backend\models\Uprawnienia */

$this->title = 'Modyfikuj Uprawnienia: ' . $model->konto_id;
$this->params['breadcrumbs'][] = ['label' => 'Uprawnienia', 'url' => ['index']];
$this->params['breadcrumbs'][] = ['label' => $model->konto_id, 'url' => ['view', 'konto_id' => $model->konto_id, 'podkategoria_id' => $model->podkategoria_id]];
$this->params['breadcrumbs'][] = 'Zmień';
?>
<div class="uprawnienia-update">

    <h1><?= Html::encode($this->title) ?></h1>

    <?= $this->render('_form', [
        'model' => $model,
        'podkategoria' => $podkategoria,
        'konta' => $konta,
    ]) ?>

</div>
